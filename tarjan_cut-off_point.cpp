struct Tarjan {
    vector<bool> vis, flag;
    vector<int> dfn, low;
    int idx, cnt;
    vector<vector<int>> G;
    Tarjan(const vector<vector<int>> &g, int n) {
        idx = 0, cnt = 0;
        vis.resize(n + 1);
        flag.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        G = g;
    }
    void dfs(int u, int p) {
        vis[u] = true;
        low[u] = dfn[u] = ++idx;
        int ch = 0;
        for (auto v : G[u]) {
            if (!vis[v]) {
                ch++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (p != u && low[v] >= dfn[u] && !flag[u]) {
                    flag[u] = true;
                    cnt++;
                }
            } else if (v != p) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (p == u && ch >= 2 && !flag[u]) {
            flag[u] = true;
            cnt++;
        }
    }
    void work(int n) {
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                idx = 0;
                dfs(i, i);
            }
        }
    }
};

