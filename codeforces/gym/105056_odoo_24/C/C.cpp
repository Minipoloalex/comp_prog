#include <bits/stdc++.h>
using namespace std;

struct Modl
{
    int cap, pos;
    string name;

    Modl() {}

    bool operator<(const Modl &o) const
    {
        return pos > o.pos;
    }
};

struct Vrs
{
    int id, pos;
    vector<int> cap;

    Vrs() {}

    bool operator<(const Vrs &o) const
    {
        return pos < o.pos;
    }
};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<Modl> mods(n);

    for (int i = 0; i < n; i++)
    {
        cin >> mods[i].name >> mods[i].cap >> mods[i].pos;
    }

    sort(mods.begin(), mods.end());

    vector<Vrs> virus(m);
    map<int, int> virus_id_to_idx;
    for (int i = 0; i < m; i++)
    {
        cin >> virus[i].id >> virus[i].pos;
        virus[i].cap.resize(n);
    }

    sort(virus.begin(), virus.end());

    for (int i = 0; i < m; i++)
    {
        virus_id_to_idx[virus[i].id] = i;
    }

    {
        map<string, int> mod_name_to_idx;
        for (int i = 0; i < n; i++) {
            mod_name_to_idx[mods[i].name] = i;
        }

        for (int i = 0; i < q; i++)
        {
            int id;
            cin >> id;
            string mod;
            cin >> mod;
            int cap;
            cin >> cap;

            virus[virus_id_to_idx[id]].cap[mod_name_to_idx[mod]] = cap;
        }
    }

    vector<bool> alive(m, 1);
    vector<int> ans;

    for (int i = 0; i < n; i++)
    {
        const int m_pos = mods[i].pos;
        int &m_cap = mods[i].cap;

        for (int j = 0; j < m; j++)
        {
            int v_pos = virus[j].pos;
            int v_cap = virus[j].cap[i];

            if (v_pos < m_pos || v_cap == 0 || !alive[j])
                continue;

            if (v_cap > m_cap)
            {
                goto end;
            }
            alive[j] = 0;
            if (v_cap == m_cap)
                goto end;

            m_cap -= v_cap;
        }

        ans.push_back(i);
    end:
    }

    int sz = int(ans.size());
    cout << sz << '\n';
    for (int i = 0; i < sz; i++)
        cout << mods[ans[i]].name << " \n"[i == sz - 1];
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
