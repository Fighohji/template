// 线形基
struct Base {
    int lim = 32;
    vector<ll> pos;
    Base() { pos.resize(lim + 1, 0); }
    bool insert(ll p) {
        for (int i = lim; i >= 0; --i) {
            if (p & 1 << i) {
                if (!pos[i]) {
                    pos[i] = p;
                    return 1;
                }
                p ^= pos[i];
            }
        }
        return 0;
    }
};

// 区间线性基 （l->r Max）
struct PrefixLinearBasis {
    int Mx = 20;
    vector<ll> p, pos;
    PrefixLinearBasis() {
        p.resize(Mx + 1);
        pos.resize(Mx + 1);
    }
    void ins(PrefixLinearBasis pre, ll idx, ll val) {
        *this = pre;
        for (int i = Mx; i >= 0; --i) {
            if (val >> i & 1) {
                if (!p[i]) {
                    p[i] = val;
                    pos[i] = idx;
                    return;
                } else if (pos[i] < idx) {
                    swap(pos[i], idx);
                    swap(p[i], val);
                }
                val ^= p[i];
            }
        }
    }
    // query l-> i Max;
    ll queryMax(int l) {
        ll ans = 0;
        for (int i = Mx; i >= 0; --i) {
            if (p[i] && pos[i] >= l) ans = max(ans, ans ^ p[i]);
        }
        return ans;
    }
} bas[500005];

// 树上区间线性基

int dep[200001];
ll a[200001];
vector<int> G[200001];
struct LinearBasis {
    int Mx = 20;
    vector<ll> p, pos; // p是线性基每一位的元素， pos 是数组中的位置
    LinearBasis() {
        p.resize(Mx + 1);
        pos.resize(Mx + 1);
    }
    void ins(ll x) {
        ll val = a[x];
        if (!val) return;
        for (int i = Mx; i >= 0; --i) {
            if (val >> i & 1) {
                if (!p[i]) {
                    p[i] = val;
                    break;
                }
                val ^= p[i];
            }
        }
    }
    void ins(const LinearBasis &pre, ll x) { // x是数组中的位置
        *this = pre;
        ll val = a[x];
        if (!val) return;
        for (int i = Mx; i >= 0; --i) {
            if (val >> i & 1) {
                if (!p[i]) {
                    p[i] = val;
                    pos[i] = x;
                    break;
                }
                if (dep[x] > dep[pos[i]]) swap(pos[i], x), swap(p[i], val);
                val ^= p[i];
            }
        }
    }
    LinearBasis merge(const LinearBasis &y, int lim) {
        LinearBasis res = LinearBasis();
        for (int i = Mx; i >= 0; --i) {
            if (dep[this->pos[i]] >= lim) res.p[i] = this->p[i];
        }
        for (int i = Mx; i >= 0; --i) {
            if (dep[y.pos[i]] >= lim) res.ins(y.pos[i]);
        }
        return res;
    }
    ll queryMax() {
        ll res = 0;
        for (int i = Mx; i >= 0; --i) {
            if ((res ^ p[i]) > res) res ^= p[i];
        }
        return res;
    }
    bool queryExist(ll val) {
        if (!val) return 1;
        for (int i = Mx; i >= 0; --i) {
            if (val >> i & 1) {
                val ^= p[i];
                if (!val) return 1;
            }
        }
        return 0;
    }
} bas[200001];

int fa[200001][18];
void dfs(int u, int p) {
    fa[u][0] = p;
    dep[u] = dep[p] + 1;
    bas[u].ins(bas[p], u);
    for (auto v : G[u])
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
