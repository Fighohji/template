struct node {
    int v, w;
};
vector<node> e[N];
int dis[N], vis[N];

bool spfa(int n) {
    queue<int> q;
    vector<int> pre(n, -1);
    int idx = 0;

    for (int i = 0; i < n; ++i)
        vis[i] = 0;
    for (int i = 0; i < n; ++i) {
        q.push(i);
        vis[i] = 1;
    }

    auto detectCycle = [&]() {
        vector<int> vec;
        vector<bool> inStack(n, 0);
        vector<bool> VIS(n, 0);
        for (int i = 0; i < n; ++i) {
            if (!VIS[i]) {
                for (int j = i; j != -1; j = pre[j]) {
                    if (!VIS[j]) {
                        VIS[j] = 1;
                        vec.pb(j);
                        inStack[j] = 1;
                    } else {
                        if (inStack[j]) return 1;
                        break;
                    }
                }
                for (int j : vec)
                    inStack[j] = 0;
                vec.clear();
            }
        }
        return 0;
    };

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pre[v] = u;
                if (++idx == n) {
                    idx = 0;
                    if (detectCycle()) return 1;
                }
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }

    if (detectCycle()) return 1;
    return 0;
}
