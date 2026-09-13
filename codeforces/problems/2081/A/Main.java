import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.lang.StringBuilder;
import java.io.IOException;

public class Main {
    static class TaskA {
        static final long MOD = (int)1e9 + 7;
        static final long inv2 = invmod(2);
        static  private long powmod(long a, long b) {
            long ans = 1;
            while (b > 0) {
                if ((b & 1) == 1) {
                    b--;
                    ans *= a;
                    ans %= MOD;
                }
                a *= a;
                b /= 2;
                a %= MOD;
            }
            return ans;
        }
        static private long invmod(long nr) {
            return powmod(nr, MOD-2);
        }

        private long go(StringBuilder sb, int i, int chg, int n) {
            if (i == n) return 0;
            if (i == n - 1) return 0;
            if (dp[i][chg] != -1) {
                return dp[i][chg];
            }
            int c = chg ^ (sb.charAt(i) - '0');
            long ans = 0;
            if (c == 0) {
                ans = (1 + go(sb, i+1, 0, n));
            }
            else {
                assert(c == 1);
                ans = (1 + go(sb, i+1, 0, n)) * inv2 + (nxt[i] - i + 1 + go(sb, nxt[i]+1, 1, n)) * inv2;
            }
            dp[i][chg] = ans % MOD;
            return dp[i][chg];
        }

        long[][] dp;
        int[] nxt;
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = Integer.parseInt(in.next());
            StringBuilder sb = new StringBuilder(in.next());
            sb.reverse();
            nxt = new int[n];
            int cur = -1;
            for (int i = n-1; i >= 0; i--) {
                char c = sb.charAt(i);
                if (c == '1') {
                    assert(c == '1');
                    cur = Math.max(cur, i);
                }
                if (cur == -1) {
                    nxt[i] = i;
                }
                else nxt[i] = cur;
                if (c == '0') {
                    cur = -1;
                }
            }

            dp = new long[n][2];
            for (int i = 0; i < n; i++) {
                dp[i][0] = -1;
                dp[i][1] = -1;
            }
            long ans = go(sb, 0, 0, n);
            out.println(ans);
        }
    }
    public static void main(String args[]) {
        new Thread(null, () -> {
            try {
                InputStream inputStream = System.in;
                OutputStream outputStream = System.out;
                InputReader in = new InputReader(inputStream);
                PrintWriter out = new PrintWriter(outputStream);

                TaskA solver = new TaskA();
                int testCount = 1;
                testCount = Integer.parseInt(in.next());
                for (int i = 1; i <= testCount; i++) {
                    solver.solve(i, in, out);
                }
                out.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }, "CP-Thread", 1 << 26).start();
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
