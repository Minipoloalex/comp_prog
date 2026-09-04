import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.ArrayList;

public class E {
    static int[] dep;
    static int[] par;
    static boolean[] hasDepCh;

    static ArrayList<Integer>[] g;

    static boolean[] xs, ys;

    static void dfs(int u, int p, int d) {
        for (int v: g[u]) {
            if (v == p) continue;
            par[v] = u;
            dfs(v, u, d + 1);
        }
        dep[u] = d;
    }
    static void dfsFinal(int u, int p, int d, int tgt, boolean[] possible) {
        int cnt = 0;
        for (int v: g[u]) {
            if (v == p) continue;
            dfsFinal(v, u, d + 1, tgt, possible);
            if (hasDepCh[v]) {
                cnt++;
            }
        }
        hasDepCh[u] = cnt > 0 || d == tgt;
        possible[d] = possible[d] || cnt >= 2 || d == tgt;
    }

    @SuppressWarnings("unchecked")
    static void solve() throws IOException {
        int n = reader.nextInt();
        dep = new int[n];
        par = new int[n];
        hasDepCh = new boolean[n];
        xs = new boolean[n];
        ys = new boolean[n];
        
        g = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            g[i] = new ArrayList<>();
        }

        for (int i = 0; i < n - 1; i++) {
            int u = reader.nextInt(), v = reader.nextInt();
            u--; v--;
            g[u].add(v);
            g[v].add(u);
        }
        dfs(0, -1, 0);
        int mx = -1;
        int x = -1;
        for (int i = 0; i < n; i++) {
            if (dep[i] > mx) {
                mx = dep[i];
                x = i;
            }
        }

        dfs(x, -1, 0);

        mx = -1;
        int y = -1; // int y = dep.indexOf(mx);
        for (int i = 0; i < n; i++) {
            if (dep[i] > mx) {
                mx = dep[i];
                y = i;
            }
        }

        assert((mx & 1) == 1); // must be odd
        int D = mx / 2;
        int v = y;
        for (int i = 0; i < D; i++) {
            v = par[v];
        }
        int u = par[v];

        dfsFinal(u, v, 0, D, xs);
        dfsFinal(v, u, 0, D, ys);
        ArrayList<Integer> l = new ArrayList<>(), r = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (xs[i]) l.add(i);
            if (ys[i]) r.add(i);
        }
        boolean ans[] = new boolean[n];
        for (int lval: l) {
            for (int rval: r) {
                ans[lval + rval + 1] = true;
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) { // with n nodes, diameter is at most n-1
            if (ans[i]) cnt++;
        }
        out.print(cnt);
        for (int i = 0; i < n; i++) {
            if (ans[i]) {
                out.print(" ");
                out.print(i);
            }
        }
        out.println();
    }

    static FastScanner reader = new FastScanner(System.in);
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        // some gemini things
        new Thread(null, () -> {
            try {
                int t = reader.nextInt();
                while (t-- > 0) {
                    solve();
                }
                out.flush();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }, "CP-Thread", 1 << 28).start();
    }
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int head = 0, tail = 0;

        public FastScanner(InputStream in) { this.in = in; }

        private int read() throws IOException {
            if (head >= tail) {
                head = 0;
                tail = in.read(buffer, 0, buffer.length);
                if (tail <= 0) return -1;
            }
            return buffer[head++];
        }

        public int nextInt() throws IOException {
            int c = read();
            while (c <= ' ') {
                if (c == -1) return -1;
                c = read();
            }
            int res = 0;
            while (c > ' ') {
                if (c >= '0' && c <= '9') {
                    res = res * 10 + (c - '0');
                }
                c = read();
            }
            return res;
        }
    }
}
