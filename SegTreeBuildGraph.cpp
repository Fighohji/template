struct nxt { int v; int w; };
int id[N << 3];
vector<nxt> G[N << 3];
struct SegTreeGraph {
#define mid ((l + r) >> 1)
    const bool IN = false, OUT = true;
    int idx, ls[N << 3], rs[N << 3], rootIn, rootOut;
    void build(int &p, int l, int r, bool type) {
        p = ++idx;
        if (l == r) {
            if (type) p = id[l];
            else id[l] = p;
            return ;
        }
        // if (type) p = ++idx;
        build(ls[p], l, mid, type);
        build(rs[p], mid + 1, r, type);
        type ? G[ls[p]].eb(p, 0) : G[p].eb(ls[p], 0);
        type ? G[rs[p]].eb(p, 0) : G[p].eb(rs[p], 0);
    }
    void upd(int p, int l, int r, int ql, int qr, int qp, int w, bool type, int np = 0) {
        /* if seg -> seg create virtual point */
        if (ql <= l && r <= qr) {
            // 0 p -> seg 1 seg -> p
            type ? G[p].eb(qp, w) : G[qp].eb(p, w);
            return ;
        }
        if (ql <= mid) upd(ls[p], l, mid, ql, qr, qp, w, type);
        if (mid < qr) upd(rs[p], mid + 1, r, ql, qr, qp, w, type);
    }
#undef mid
} T;
int dis[N << 3];
bool vis[N << 3];
struct node {
    int u;
    bool operator<(const node &t) const {
        return dis[u] > dis[t.u];
    }
};
void dij(int S) {
    priority_queue<node> q;
    for (int i = 1; i <= T.idx; ++i) dis[i] = INF;
    dis[S] = 0;
    q.push({S});
    while (!q.empty()) {
        auto [u] = q.top(); q.pop();
        // if (vis[u]) continue;
        // vis[u] = true;
        for (auto &[v, w] : G[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({v});
            }
        }
    }
}

void solve() {
    int n, q, s; cin >> n >> q >> s;
    T.build(T.rootIn, 1, n, 0);
    T.build(T.rootOut, 1, n, 1);
    while(q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int np = ++T.idx;
        T.upd(T.rootOut, 1, n, a, b, np, 1, 1);
        T.upd(T.rootIn, 1, n, c, d, np, 0, 0);
        np = ++T.idx;
        T.upd(T.rootOut, 1, n, c, d, np, 1, 1);
        T.upd(T.rootIn, 1, n, a, b, np, 0, 0);
    }
    dij(id[s]);
    for (int i = 1; i <= n; ++i) {
        cout << (dis[id[i]] == LINF ? -1 : dis[id[i]]) << "\n";
    }
}
