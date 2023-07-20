map<vector<int>, int> hssym;
map<int, bool> issym;
int idx;
int dfs(int u, int p, vector<vector<int> > &e)
{
    vector<int> tmp;
    for (auto v : e[u]) {
        if (v == p) continue;
        tmp.pb(dfs(v, u, e));
    }
    sort(all(tmp));
    if (!hssym.count(tmp)) {
        map<int, int> cnt;
        for (auto v : tmp) {
            cnt[v]++;
        }
        int odd = 0, bad = 0;
        for (auto i : cnt) {
            if (i.sec & 1) {
                odd++;
                bad += !issym[i.fir];
            }
        }
        hssym[tmp] = ++idx;
        issym[idx] = odd < 2 && bad == 0;
    }
    return hssym[tmp];
}