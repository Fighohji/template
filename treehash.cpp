bool vis[N];
int prime[N]; // 素数数量要>n
int cnt;
void isprime(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
int sz[N];
ull hs[N];
vector<int> e[N];
bool f;
int n;
void dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : e[u])
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
            hs[u] += hs[v] * (ull)prime[sz[v]] * 487ull;
        }
}
