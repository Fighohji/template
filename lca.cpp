int fa[N][18], dep[N];
void dfs(int u, int p) {
    fa[u][0] = p;
    dep[u] = dep[p] + 1;
    for (auto v : e[u])
        if (v != p) dfs(v, u);
}
void init_lca(int n) {
    for (int j = 1; j < 18; ++j)
        for (int i = 1; i <= n; ++i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int get_lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = 17; i >= 0; --i)
        if (dep[v] - dep[u] >= (1 << i)) v = fa[v][i];
    if (u == v) return u;
    for (int i = 17; i >= 0; --i)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

struct STLCA {
    int dfn, LG;
    vector<int> id, euler, dep, lg;
    vector<vector<int>> st, g;
    STLCA(int n, const vector<vector<int>> &G) {
        dfn = 0;
        g = G;
        id.resize(n);
        euler.resize(2 * n + 1);
        dep.resize(2 * n + 1);
        st.resize(2 * n + 1);
    }
    void dfs(int u, int p, int d) {
        id[u] = ++dfn;
        euler[dfn] = u;
        dep[dfn] = d;
        for (auto v : g[u])
            if (v != p) {
                dfs(v, u, d + 1);
                euler[++dfn] = u;
                dep[dfn] = d;
            }
    }
    void init_lca() { // 记得初始化！！
        lg.resize(dfn + 1);
        for (int i = 2; i <= dfn; ++i)
            lg[i] = lg[i >> 1] + 1;
        LG = lg[dfn];
        fill(all(st), vector<int>(LG + 1));
        int x, y;
        for (int i = 1; i <= dfn; ++i)
            st[i][0] = i;
        for (int j = 1; j <= LG; ++j)
            for (int i = 1; i + (1 << j) - 1 <= dfn; ++i) {
                x = st[i][j - 1];
                y = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = dep[x] < dep[y] ? x : y;
            }
    }
    void init(int u) {
        dfs(u, 0, 0);
        init_lca();
    }
    int get_lca(int u, int v) {
        u = id[u], v = id[v];
        if (u > v) swap(u, v);
        int k = lg[v - u + 1];
        int x = st[u][k], y = st[v - (1 << k) + 1][k];
        return dep[x] < dep[y] ? euler[x] : euler[y];
    }
};
