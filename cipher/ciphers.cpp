#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <bitset>

class Pair {
public:
    std::string encrypt;
    std::string decrypt;

    Pair(const std::string& encrypt, const std::string& decrypt) : encrypt(encrypt), decrypt(decrypt) {}
};

// Класс регистра сдвига с линейной обратной связью (LFSR)
class LFSR {
private:
    uint8_t lfsr;

public:
    LFSR(uint8_t start_state) : lfsr(start_state) {}

    uint8_t generateBit() {
        // Генерация следующего бита с использованием XOR операции над определенными битами текущего состояния
        uint8_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1u;
        // Сдвигаем регистр на один бит вправо и добавляем сгенерированный бит в старший разряд
        lfsr = (lfsr >> 1) | (bit << 7);
        return bit;
    }
};

class OneTimePad {
public:
    // Метод для шифрования и дешифрования текста по ключу методом XOR
    void encryptDecrypt(std::string& input, const std::string &key, size_t length) {
        for (size_t i = 0; i < length; ++i) {
            input[i] ^= key[i]; // Применяем операцию XOR к каждому символу текста и ключа
        }
    }
};

// Класс шифра подстановки
class SubstitutionCipher {
private:
    const size_t alphabet_len = 26;
    std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                                't', 'u', 'v', 'w', 'x', 'y', 'z'};

public:
    size_t findCharacterIndex(char c) const {
        for (size_t i = 0; i < alphabet_len; ++i) {
            if (c == alphabet[i]) {
                return i;
            }
        }
        return -1;
    }

    std::string encrypt(const std::string& input, size_t shift) const {
        std::string result = input;
        for (char& c : result) {
            size_t indexInAlphabet = findCharacterIndex(c);
            if (0 <= indexInAlphabet && indexInAlphabet <= 25) {
                size_t encryptedIndex = (indexInAlphabet + shift) % alphabet_len;
                c = alphabet[encryptedIndex];
            }
        }
        return result;
    }

    std::string decrypt(const std::string& input, size_t shift) const {
        std::string result = input;
        for (char& c : result) {
            size_t indexInAlphabet = findCharacterIndex(c);
            if (0 <=indexInAlphabet && indexInAlphabet <= 25) {
                int32_t decryptedIndex = (indexInAlphabet - shift) % alphabet_len;
                if (decryptedIndex < 0) {
                    decryptedIndex += indexInAlphabet;
                }
                c = alphabet[decryptedIndex];
            }   
        }
        return result;
    }
};

// Класс RSA (алгоритм шифрования с открытым ключом)
class RivestShamirAdleman {
private:
    int64_t gcd(int64_t a, int64_t b) const {
        if (b == 0) return a;
        return gcd(b, a%b);
    }

    // Метод для возведения в степень по модулю
    int64_t binPowModulo(int64_t base, int64_t exp, int64_t mod) {
        int64_t res = 1;
        while (exp > 0) {
            if (exp%2 == 1) {
                res = ((res % mod) * (base % mod)) % mod;
            }
            base = ((base % mod) * (base % mod)) % mod;
            exp /= 2;
        }
        return res;
    }

    // Метод для вычисления модулярного обратного
    int64_t modInverse(int64_t A, int64_t M) {
        int64_t m0 = M;
        int64_t y = 0, x = 1;
        if (M == 1) return 0;

        while (A > 1) {
            int64_t q = A / M;
            int64_t t = M;
            M = A % M, A = t;
            t = y;
    
            y = x - q * y;
            x = t;
        }
        if (x < 0)
            x += m0;
        return x;
    }

public:
    // Preferably to use p = 7919 and q = 7907 as random large primes
    Pair RSA(const std::string& message, int64_t p = 7919, int64_t q = 7907, int64_t e = 2) {
        int64_t n = p * q;
        int64_t phi = (p-1)*(q-1);

        // Выбор открытой экспоненты e
        while (e < phi) {
            if (gcd(e, phi) == 1) break;
            else e++;
        }

        // Преобразование сообщения в бинарную строку
        std::string binaryStr = "";
        for (char c : message) {
            std::string buff = std::bitset<8>(c).to_string();
            binaryStr += buff;
        }
        int64_t msg = std::bitset<64>(binaryStr).to_ullong();

        // Вычисление секретного ключа d
        int64_t d = modInverse(e, phi);

        // Шифрование сообщения
        int64_t encrypt = binPowModulo(msg, e, n);
        int64_t encryptCopy = encrypt;

        std::string encryptedBytes = "";
        while (encryptCopy > 0) {
            encryptedBytes = std::to_string(encryptCopy % 256) + " " + encryptedBytes;
            encryptCopy /= 256;
        }

        // Дешифрование зашифрованного сообщения (unstable)
        int64_t decrypt = binPowModulo(encrypt, d, n);
        int64_t decryptCopy = decrypt;

        std::string decryptedMessage = "";
        for (size_t i = 0; i < binaryStr.length(); i += 8) {
            std::string byte = binaryStr.substr(i, 8);
            char c = static_cast<char>(std::bitset<8>(byte).to_ulong());
            decryptedMessage += c;
        }

        return Pair(encryptedBytes, decryptedMessage);
    }
};

int main() {
    std::string text = "Hello world!";;
    std::string key;

    std::cout << "Input text: " << text << std::endl;
    size_t input_length = text.length();

    // lfsr
    LFSR lfsr(0b01010101);
    std::cout << "Generated key:" << std::endl;
    for (size_t i = 0; i < input_length; ++i) {
        key += std::to_string(lfsr.generateBit());
    }
    std::cout << key << std::endl;

    // otp
    OneTimePad otp;
    otp.encryptDecrypt(text, key, input_length);
    std::cout << "\nEncrypted text:" << std::endl << text << std::endl;

    // Для дешифрования используем ту же функцию
    otp.encryptDecrypt(text, key, input_length); 
    std::cout << "Decrypted text:" << std::endl << text << std::endl;

    // Substitution Cipher
    SubstitutionCipher subCipher;
    size_t shift = 4;
    std::string encryptedText = subCipher.encrypt(text, shift);
    std::cout << "\nEncrypted text using Substitution Cipher:" << std::endl << encryptedText << std::endl;

    std::string decryptedText = subCipher.decrypt(encryptedText, shift);
    std::cout << "Decrypted text using Substitution Cipher:" << std::endl << decryptedText << std::endl;

    // RSA 
    RivestShamirAdleman rsa;
    text = "accu";
    Pair answer = rsa.RSA(text, 793, 345, 56);
    std::cout << "\nEcrypted bytes using RSA: " << std::endl << answer.encrypt << std::endl;
    std::cout << "Decrypted message using RSA: " << std::endl << answer.decrypt << std::endl;

    return 0;
}