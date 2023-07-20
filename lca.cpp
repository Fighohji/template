int fa[maxn][18], dep[maxn];
void dfs(int u, int p)
{
    fa[u][0] = p;
    dep[u] = dep[p] + 1;
    for (auto v : e[u])
        if (v != p)
            dfs(v, u);
}
void init_lca(int n)
{
    for (int j = 1; j < 18; ++j)
        for (int i = 1; i <= n; ++i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int get_lca(int u, int v)
{
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = 17; i >= 0; --i)
        if (dep[v] - dep[u] >= (1 << i))
            v = fa[v][i];
    if (u == v) return u;
    for (int i = 17; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}


/*  int dfn, id[maxn]; // st表求lca,能快一点,费空间
    int euler[maxn << 1], dep[maxn << 1];
    int st[maxn << 1][20], lg[maxn << 1];
    void dfs(int u, int p, int d) {
        id[u] = ++dfn;
        euler[dfn] = u;
        dep[dfn] = d;
        for (auto [v, w] : g[u])
            if (v != p) {
                dfs(v, u, d + 1);
                euler[++dfn] = u;
                dep[dfn] = d;
            }
    }
    void init_lca() {//记得初始化！！
        for (int i = 2; i <= dfn; ++i)
            lg[i] = lg[i >> 1] + 1;
        for (int i = 1; i <= dfn; ++i)
            st[i][0] = i;
        int x, y;
        for (int j = 1; j <= lg[dfn]; ++j)
            for (int i = 1; i + (1 << j) - 1 <= dfn; ++i) {
                x = st[i][j - 1];
                y = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = dep[x] < dep[y] ? x : y;
            }
    }
    int get_lca(int u, int v) {
        u = id[u], v = id[v];
        if (u > v) swap(u, v);
        int k = lg[v - u + 1];
        int x = st[u][k], y = st[v - (1 << k) + 1][k];
        return dep[x] < dep[y] ? euler[x] : euler[y];
    }*/
