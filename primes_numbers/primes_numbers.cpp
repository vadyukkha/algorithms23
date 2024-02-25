#include <iostream>
#include <cmath>

using namespace std;

int gcd(int a, int b){
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int fast_pow(int base, int t, int mod) {
    int r = 1;
    while (t) {
        if (t & 1) {
            r = (r * base) % mod;
        }
        base = (base * base) % mod;
        t /= 2;
    }
    return r;
}

bool Miller_Rabin(int num) {
    if ((num % 2 == 0 && num != 2) || num < 2) {
        return false;
    }
    int t = num - 1;
    int s = 0;

    while (t % 2 == 0) {
        t = t / 2;
        s++;
    }

    for (int i = 1; i < num; i++) {
        int xn = fast_pow(i, t, num);

        if (xn == 1 || xn == num - 1) {
            continue;
        }

        for (int j = 1; j < s; j++) {
            xn = fast_pow(xn, 2, num);

            if (xn == 1)
                return false;

            if (xn == num - 1) {
                break;
            }

        }
        if (xn != num - 1) {
            return false;
        }
    }
    return true;
}

bool Ferma(int num) {
    for (int a = 2; a < num; a++) {
        if (gcd(a, num) != 1) {
            return false;
        }
        if (fast_pow(a, num - 1, num) != 1) {
            return false;
        }
    }
    return true;
}

void sieve(int n) {
    int *arr = new int[n + 1];
    for (int i = 0; i <= n; i++) {
        arr[i] = 0;
    }
    arr[1] = 1;
    for (int j = 2; j * j <= n; j++) {
        for (int i = j * 2; i <= n; i += j) {
            if (arr[i] == 0 && arr[j] == 0) {
                arr[i] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (arr[i] == 0) {
            cout << i << ' ';
        }
    }
}

bool simpleCheck(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    cin >> num;
    // composite number - 0 and prime number - 1
    cout << "Simple test : " << simpleCheck(num) << endl;
    cout << "Miller-Rabin test : " << Miller_Rabin(num) << endl;
    cout << "Ferma test : " << Ferma(num) << endl;
    cout << "Sieve of Eratosthenes : ";
    sieve(num); 
    return 0;
}