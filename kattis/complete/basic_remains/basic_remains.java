import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            int b = sc.nextInt();
            if (b == 0) break;
            BigInteger p = new BigInteger(sc.next(), b);
            BigInteger m = new BigInteger(sc.next(), b);
            System.out.println(p.mod(m).toString(b));
        }
        sc.close();
    }
}
