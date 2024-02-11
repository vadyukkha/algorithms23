import java.math.BigInteger;
import java.util.Scanner;

public class contest3_C {

    public static BigInteger gcd(BigInteger a, BigInteger b) {
        if (b.equals(BigInteger.ZERO)) return a;
        return gcd(b, a.mod(b));
    }

    public static BigInteger powerMod(BigInteger base, BigInteger exp, BigInteger mod) {
        BigInteger res = BigInteger.ONE;
        while (exp.compareTo(BigInteger.ZERO) > 0) {
            if (exp.testBit(0)) {
                res = res.multiply(base).mod(mod);
            }
            base = base.multiply(base).mod(mod);
            exp = exp.divide(BigInteger.valueOf(2));
        }
        return res;
    }

    public static void RSA(BigInteger p, BigInteger q, BigInteger e, BigInteger msg, String save) {
        BigInteger n = p.multiply(q);
        BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));

        while (e.compareTo(phi) < 0) {
            if (e.gcd(phi).equals(BigInteger.ONE)) {
                break;
            } else {
                e = e.add(BigInteger.ONE);
            }
        }

        BigInteger d = e.modInverse(phi);
        System.out.println("Private: " + d + " " + n);
        System.out.println("Public: " + e + " " + n);
        System.out.println("Initial bytes: " + save);
        BigInteger tempRes = powerMod(msg, e, n);
        String encryptedBytes = "";
        while (tempRes.compareTo(BigInteger.ZERO) > 0) {
            encryptedBytes = tempRes.mod(BigInteger.valueOf(256)) + " " + encryptedBytes;
            tempRes = tempRes.divide(BigInteger.valueOf(256));
        }
        System.out.println("Encrypted bytes: " + encryptedBytes);
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        BigInteger p = scan.nextBigInteger();
        BigInteger q = scan.nextBigInteger();
        BigInteger e = scan.nextBigInteger();
        String input = scan.next();
        scan.close();
        String binaryStr = "";
        String save = "";
        for (int i = 0; i < input.length(); i++) {
            String buff = BigInteger.valueOf(input.charAt(i)).toString(2);
            save += Integer.toString(input.charAt(i)) + " ";
            while (buff.length() < 8) {
                buff = "0" + buff;
            }
            binaryStr += buff;
        }
        BigInteger msg = new BigInteger(binaryStr, 2);
        RSA(p, q, e, msg, save);
    }
}