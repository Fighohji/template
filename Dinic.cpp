struct edge {
    int v, cap, rev;
};
int level[N]; // 距离标号
int iter[N];  // 当前弧
vector<edge> e[N];

void add_edge(int u, int v, int cap) {
    e[u].push_back((edge){v, cap, (int)e[v].size()});
    e[v].push_back((edge){u, 0, (int)e[u].size() - 1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int i = 0; i < e[v].size(); ++i) {
            edge &tmp = e[v][i];
            if (tmp.cap > 0 && level[tmp.v] < 0) {
                level[tmp.v] = level[v] + 1;
                que.push(tmp.v);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < e[v].size(); ++i) {
        edge &tmp = e[v][i];
        if (tmp.cap > 0 && level[v] < level[tmp.v]) {
            int d = dfs(tmp.v, t, min(f, tmp.cap));
            if (d > 0) {
                tmp.cap -= d;
                e[tmp.v][tmp.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    for (;;) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, inf)) > 0)
            flow += f;
    }
}
