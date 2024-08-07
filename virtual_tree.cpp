struct Virtual_Tree {
    vector<pii> g[N];
    int dfn, id[N];
    int fa[N][18], dep[N];
    void dfs(int u, int p) {
        id[u] = ++dfn;
        fa[u][0] = p;
        dep[u] = dep[p] + 1;
        for (auto [v, w] : g[u])
            if (v != p) { dfs(v, u); }
    }
    void init_lca(int n) { // 记得初始化！！
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

    int cnt, head[N], nxt[N], e[N];
    int stk[N], top, tmp[N];
    void add_edge(int u, int v) {
        e[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }
    void build(int k) {
        sort(tmp + 1, tmp + 1 + k, [&](int x, int y) {
            return id[x] < id[y];
        });
        stk[top = 1] = 1;
        cnt = 0;
        head[1] = 0; // 放入根节点
        for (int i = (tmp[1] == 1 ? 2 : 1), l; i <= k;
             ++i) { // 根节点不要重复添加
            l = get_lca(tmp[i], stk[top]);
            if (l != stk[top]) {
                while (id[l] < id[stk[top - 1]])
                    add_edge(stk[top - 1], stk[top]), top--;
                if (id[l] > id[stk[top - 1]])
                    head[l] = 0, add_edge(l, stk[top]), stk[top] = l;
                else
                    add_edge(l, stk[top--]);
            }
            head[tmp[i]] = 0, stk[++top] = tmp[i];
        }
        for (int i = 1; i < top; ++i)
            add_edge(stk[i], stk[i + 1]);
    }
};
