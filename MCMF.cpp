struct MCMF {
    struct E {
        int from, to;
        ll cap, v;
        E() {}
        E(int f, int t, ll cap, ll v) : from(f), to(t), cap(cap), v(v) {}
    };
    int n, m, s, t;
    vector<E> edges;
    vector<int> G[N];
    bool inq[N];
    ll dis[N], pre[N], a[N];
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        for (int i = 0; i <= n; i++)
            G[i].clear();
        edges.clear();
        m = 0;
    }
    void add(int from, int to, ll cap, ll cost) {
        edges.emplace_back(from, to, cap, cost);
        edges.emplace_back(to, from, 0, -cost);
        G[from].push_back(m++);
        G[to].push_back(m++);
    }
    bool spfa() {
        for (int i = 0; i <= n; i++) {
            dis[i] = LINF;
            pre[i] = -1;
            inq[i] = false;
        }
        dis[s] = 0, a[s] = LINF, inq[s] = true;
        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for (int &idx : G[u]) {
                E &e = edges[idx];
                if (e.cap && dis[e.to] > dis[u] + e.v) {
                    dis[e.to] = dis[u] + e.v;
                    pre[e.to] = idx;
                    a[e.to] = min(a[u], e.cap);
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        Q.push(e.to);
                    }
                }
            }
        }
        return pre[t] != -1;
    }
    ll solve() {
        ll flow = 0, cost = 0;
        while (spfa()) {
            flow += a[t];
            cost += a[t] * dis[t];
            int u = t;
            while (u != s) {
                edges[pre[u]].cap -= a[t];
                edges[pre[u] ^ 1].cap += a[t];
                u = edges[pre[u]].from;
            }
        }
        return cost;
    }
} flow;
