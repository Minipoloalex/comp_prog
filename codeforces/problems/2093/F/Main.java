import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
     static class TaskF {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = Integer.parseInt(in.next());
            int m = Integer.parseInt(in.next());
            String[] a = new String[n];
            for (int i = 0; i < n; i++) a[i] = in.next();

            // yes, var names are weird
            int maxCommon = 0;
            boolean[] isGood = new boolean[n];
            for (int j = 0; j < m; j++) {
                int curCommon = 0;
                for (int i = 0; i < n; i++) {
                    String bji = in.next();
                    boolean isCorrect = a[i].equals(bji);
                    if (isCorrect) {
                        isGood[i] = true;
                        curCommon++;
                    }
                }
                maxCommon = Math.max(maxCommon, curCommon);
            }
            int ans = n + 2 * (n - maxCommon);
            for (int i = 0; i < n; i++) {
                if (!isGood[i]) {
                    ans = -1;
                    break;
                }
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
        TaskF solver = new TaskF();
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
