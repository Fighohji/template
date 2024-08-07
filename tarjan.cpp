struct Tarjan {
    vector<vector<int>> G, scm;
    vector<int> stk, dfn, low, scc;
    int sccnum, idx, top;
    Tarjan(const vector<vector<int>> &e, int n) {
        sccnum = 0, idx = 0, top = 0;
        G = e;
        scm.resize(n + 1);
        stk.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
    }
    void dfs(int u) {
        if (dfn[u] != 0) return;
        dfn[u] = low[u] = ++idx;
        stk[++top] = u;
        for (auto v : G[u]) {
            if (dfn[v] == 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (scc[v] == 0)
                low[u] = min(dfn[v], low[u]);
        }
        if (dfn[u] == low[u]) {
            sccnum++;
            while (1) {
                scm[sccnum].push_back(stk[top]);
                scc[stk[top--]] = sccnum;
                if (stk[top + 1] == u) break;
            }
        }
    }
};
