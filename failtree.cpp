int n;
char s[N];
vector<int> e[N];
int len;
int nxt[N];
int parent[30][N];
int depth[N];
void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for (auto i : e[v])
        if (i != p) dfs(i, v, d + 1);
}

void init() {
    dfs(0, -1, 0);
    for (int k = 0; k < 29; ++k)
        for (int v = 1; v <= len; ++v) {
            if (parent[k][v] <= 0)
                parent[k + 1][v] = 0;
            else
                parent[k + 1][v] = parent[k][parent[k][v]];
        }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < 29; ++k)
        if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
    for (int k = 28; k >= 0; --k)
        if (parent[k][u] != parent[k][v]) u = parent[k][u], v = parent[k][v];
    return parent[0][u];
}
void getNXT() {
    int i, j = 0;
    nxt[1] = 0;
    e[0].push_back(1);
    for (int i = 2; i <= len; ++i) {
        while (j > 0 && s[j + 1] != s[i])
            j = nxt[j];
        if (s[j + 1] == s[i]) j++;
        nxt[i] = j;
        e[j].push_back(i);
    }
}
void solve(int cas) {
    cin >> s + 1 >> n;
    len = strlen(s + 1);
    getNXT();
    init();
    while (n--) {
        int a, b;
        cin >> a >> b;
        int k = lca(a, b);
        cout << k << '\n';
    }
}
