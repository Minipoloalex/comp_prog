import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;

public class Main {
     static class TaskE {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = Integer.parseInt(in.next());
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = Integer.parseInt(in.next()) - 1;

            boolean[][] good = new boolean[n][n];
            int[] cnt = new int[n];
            for (int i = 0; i < n; i++) {
                int mn = Integer.MAX_VALUE, mx = Integer.MIN_VALUE;
                for (int j = 0; j < n; j++) cnt[j] = 0;
                for (int j = i; j < n; j++) {
                    mn = Math.min(mn, a[j]);
                    mx = Math.max(mx, a[j]);
                    if (cnt[a[j]]++ == 1) {
                        break;
                    }
                    int sz = j - i + 1;
                    if (mx - mn + 1 == sz) {
                        good[mn][mx] = true;
                    }
                }
            }
            int ans = 0;
            for (int i = n/2; i > 0; i--) {
                for (int j = 0; j+i+i-1 < n; j++) {
                    if (good[j][j+i-1] && good[j+i][j+i+i-1]) {
                        ans = i;
                        break;
                    }
                }
                if (ans == i) break;
            }
            out.println(ans);
        }
    }
    public static void main(String args[]) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        TaskE solver = new TaskE();
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
