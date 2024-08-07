int n, m, match[305], pre[305];
bool vis[305];
int mp[305][305];
int val1[305], val2[305], slack[305];

il void bfs(int p) {
    memset(pre, 0, sizeof(pre));
    memset(slack, inf, sizeof(slack));
    match[0] = p;
    int x = 0, nex = 0;
    do {
        vis[x] = true;
        int y = match[x], d = inf;
        for (int i = 1; i <= m; ++i) {
            if (!vis[i]) {
                if (slack[i] > val1[y] + val2[i] - mp[y][i]) {
                    slack[i] = val1[y] + val2[i] - mp[y][i];
                    pre[i] = x;
                }
                if (slack[i] < d) {
                    d = slack[i];
                    nex = i;
                }
            }
        }
        for (int i = 0; i <= m; ++i) {
            if (vis[i])
                val1[match[i]] -= d, val2[i] += d;
            else
                slack[i] -= d;
        }
        x = nex;
    } while (match[x]);
    while (x) {
        match[x] = match[pre[x]];
        x = pre[x];
    }
}

il int KM() {
    memset(match, 0, sizeof(match));
    memset(val1, 0, sizeof(val1));
    memset(val2, 0, sizeof(val2));
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        bfs(i);
    }
    int res = 0;
    for (int i = 1; i <= m; ++i)
        res += mp[match[i]][i];
    return res;
}
