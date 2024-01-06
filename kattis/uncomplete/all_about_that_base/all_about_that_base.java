import java.math.BigInteger;
import java.util.Scanner;
import java.util.ArrayList;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        BigInteger lower_limit = new BigInteger("0");
        BigInteger upper_limit = new BigInteger("FFFFFFFF", 16);
        while (n-- > 0) {
            String x = sc.next();
            String y = sc.next();
            char c = sc.next().charAt(0);
            String z = sc.next();
            
            ArrayList<String> bases = new ArrayList<String>();
            for (int base = 1; base <= 36; base++) {
                System.out.println("Trying base " + base);
                BigInteger a = new BigInteger(x, base);
                if (a.compareTo(lower_limit) == -1 || a.compareTo(upper_limit) == 1) continue;
                
                BigInteger b = new BigInteger(y, base);
                if (b.compareTo(lower_limit) == -1 || b.compareTo(upper_limit) == 1) continue;
                
                BigInteger d = new BigInteger(z, base);
                if (d.compareTo(lower_limit) == -1 || d.compareTo(upper_limit) == 1) continue;

                switch (c) {
                    case '+':
                        if (a.add(b).compareTo(d) == 0) bases.add(Integer.toString(base, 36));
                        break;
                    case '-':
                        if (a.subtract(b).compareTo(d) == 0) bases.add(Integer.toString(base, 36));
                        break;
                    case '*':
                        if (a.multiply(b).compareTo(d) == 0) bases.add(Integer.toString(base, 36));
                        break;
                    case '/':
                        if (a.divide(b).compareTo(d) == 0) bases.add(Integer.toString(base, 36));
                        break;
                }
            }
            for (String base : bases) System.out.print(base);
            System.out.println();
        }
        sc.close();
    }
}