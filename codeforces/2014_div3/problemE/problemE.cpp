#include <bits/stdc++.h>
using namespace std;

using iii = tuple<int, int, int>;
using viii = vector<iii>;

using ii = pair<int, int>;
using vii = vector<ii>;

vector<vii> el;
const int MAX_N = int(2e5) + 10;
bitset<MAX_N> horse;

void dijkstra(int st, vector<int> &normalDist, vector<int> &horseDist) {
    normalDist[st] = 0;
    if (horse[0]) horseDist[0] = 0;
    set<iii> pq;
    pq.emplace(0, st, horse[0]);
    

    while (!pq.empty()) {
        auto it = pq.begin();
        auto [d, u, hasHorse] = *it;
        pq.erase(it);

        if (hasHorse && d > horseDist[u]) continue;
        if (!hasHorse && d > normalDist[u]) continue;

        for (auto [v, w]: el[u]) {
            if (hasHorse) {
                w /= 2;
                if (horseDist[v] != -1) {
                    // may need to erase
                    if (horseDist[u] + w < horseDist[v]) {
                        auto erase_it = pq.find({horseDist[v], v, true});
                        if (erase_it != pq.end()) pq.erase(erase_it);
                        horseDist[v] = horseDist[u] + w;
                        pq.emplace(horseDist[v], v, true);
                    }
                }
                else {
                    horseDist[v] = horseDist[u] + w;
                    pq.emplace(horseDist[v], v, true);
                }
            }
            else {  // No horse
                if (normalDist[v] != -1) {
                    if (normalDist[u] + w < normalDist[v]) {
                        auto erase_it = pq.find({normalDist[v], v, false});
                        if (erase_it != pq.end()) pq.erase(erase_it);
                        normalDist[v] = normalDist[u] + w;
                        if (horse[v]) {
                            if (horseDist[v] == -1) {
                                horseDist[v] = normalDist[v];
                                pq.emplace(horseDist[v], v, 1);
                            }
                            else if (normalDist[u] + w < horseDist[v]) {
                                auto erase_it = pq.find({horseDist[v], v, 1});
                                if (erase_it != pq.end()) pq.erase(erase_it);
                                horseDist[v] = normalDist[v];
                                pq.emplace(normalDist[v], v, 1);
                            }
                        }
                        else {
                            pq.emplace(normalDist[v], v, 0);
                        }
                    }
                }
                else {
                    normalDist[v] = normalDist[u] + w;
                    if (horse[v]) {
                        if (horseDist[v] == -1) {
                            horseDist[v] = normalDist[v];
                            pq.emplace(normalDist[v], v, 1);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, h;
        cin >> n >> m >> h;
        el.assign(n, vii());
        for (int i = 0; i < h; i++) {
            int ai;
            cin >> ai;
            horse.set(ai - 1);
        }
        for (int i = 0; i < m; i++) {
            int ui, vi, wi;
            cin >> ui >> vi >> wi;
            ui--;vi--;
            el[ui].emplace_back(vi, wi);
            el[vi].emplace_back(ui, wi);
        }
        vector<int> distFrom1(n, -1), withHorse1(n, -1);
        vector<int> distFromN(n, -1), withHorseN(n, -1);
        dijkstra(0, distFrom1, withHorse1);
        dijkstra(n - 1, distFromN, withHorseN);
    }
    return 0;
}
