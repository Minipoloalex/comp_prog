import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.TreeMap;
import java.util.TreeSet;
import java.io.IOException;

public class Main {
    static class TaskA1 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = Integer.parseInt(in.next());
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(in.next());
            }
            int ans = 1;
            int base = a[0];
            int prv = a[0];
            for (int i = 1; i < n; i++) {
                if (a[i] == prv + 1) {
                    prv = a[i];
                }
                else if (a[i] > base && a[i] <= prv) {
                    prv = a[i];
                }
                else {
                    ans++;
                    base = prv = a[i];
                }
            }
            out.println(ans);
        }
    }
     static class TaskA2 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = Integer.parseInt(in.next());
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(in.next());
            }

            long ans = n;
            int base = a[0];
            int prv = a[0];
            TreeMap<Integer, Integer> loc = new TreeMap<>();
            loc.put(a[0], 0);
            for (int i = 1; i < n; i++) {
                int idx = -1;
                if (a[i] > base && a[i] <= prv + 1) {
                    prv = a[i];
                    idx = loc.get(a[i]-1);
                }
                else {
                    base = prv = a[i];
                    loc.clear();
                }
                ans += (long)(n - i) * (long)(i - idx);
                loc.put(a[i], i);
            }
            out.println(ans);
        }
    }
    public static void main(String args[]) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        // TaskA1 solver = new TaskA1();
        TaskA2 solver = new TaskA2();
        int testCount = 1;
        testCount = Integer.parseInt(in.next());
        for (int i = 1; i <= testCount; i++) {
            solver.solve(i, in, out);
        }
        out.close();
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;
 
        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }
 
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }
 
    }
}