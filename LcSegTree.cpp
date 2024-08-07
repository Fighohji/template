
using pdi = pair<double, int>;
int dcmp(db x, db y) {
    if (x - y > eps) return 1;
    if (y - x > eps) return -1;
    return 0;
}
pdi pmax(pdi x, pdi y) {
    if (dcmp(x.fir, y.fir) == -1) return y;
    if (dcmp(x.fir, y.fir) == 1) return x;
    return x.sec < y.sec ? x : y;
}
int cnt;
struct Line {
    db k, b;
    Line() {}
    Line(db _k, db _b) : k(_k), b(_b) {}
    db getY(int x) { return k * x + b; }
} s[maxn];
void add(int x0, int y0, int x1, int y1) { //线段 -> 点斜式
    db k = 0, b = 0;
    if (x0 != x1) {
        k = 1.0 * (y0 - y1) / (x0 - x1);
        b = y0 - k * x0;
    } else b = abs(y0 - y1);
    s[++cnt] = Line(k, b);
}

struct LcSeg {
    int node[maxn << 2];
    
    void upd(int p, int l, int r, int u) {
        int &v = node[p], mid = l + r >> 1;
        int flag = dcmp(s[u].getY(mid), s[v].getY(mid)); //判断中点
        if (flag == 1 || (!flag && u < v)) swap(u, v);
        int flagl = dcmp(s[u].getY(l), s[v].getY(l)), flagr = dcmp(s[u].getY(r), s[v].getY(r));
        if (flagl == 1 || (!flagl && u < v)) upd(p << 1, l, mid, u);
        if (flagr == 1 || (!flagr && u < v)) upd(p << 1 | 1, mid + 1, r, u);
    }
    void update(int p, int l, int r, int ql, int qr, int u) {
        if (ql <= l && r <= qr) {
            upd(p, l, r, u);
            return ;
        }
        int mid = l + r >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, u);
        if (mid < qr) update(p << 1 | 1, mid + 1, r, ql, qr, u);
    }
    pdi query(int p, int l, int r, int x) {
        if (r < x || x < l) return {0, 0};
        int mid = l + r >> 1;
        db res = s[node[p]].getY(x);
        if (l == r) return {res, node[p]};
        return pmax({res, node[p]}, pmax(query(p << 1, l, mid, x),
                                        query(p << 1 | 1, mid + 1, r, x)));
    }
} Seg;



#define int long long
int CNT;
struct Line {
    int k, b;
    Line() {}
    Line(int _k, int _b) : k(_k), b(_b) {}
    int getY(int x) { return k * x + b; }
} s[maxn];

// using pdi = pair<double, int>;
int cmp(int x, int y) {
    if (x > y) return 1;
    if (y > x) return -1;
    return 0;
}
pii pmax(pii x, pii y) {
    if (x.fir < y.fir) return y;
    if (x.fir > y.fir) return x;
    return x.sec < y.sec ? x : y;
}

void add(int k, int b) { s[++CNT] = Line(k, b); }

struct LcSeg {
    int node[maxn << 2];
    
    void upd(int p, int l, int r, int u) {
        int &v = node[p], mid = l + r >> 1;
        int flag = cmp(s[u].getY(mid), s[v].getY(mid)); //判断中点
        if (flag == 1 || (!flag && u < v)) swap(u, v);
        int flagl = cmp(s[u].getY(l), s[v].getY(l)), flagr = cmp(s[u].getY(r), s[v].getY(r));
        if (flagl == 1 || (!flagl && u < v)) upd(p << 1, l, mid, u);
        if (flagr == 1 || (!flagr && u < v)) upd(p << 1 | 1, mid + 1, r, u);
    }
    void update(int p, int l, int r, int ql, int qr, int u) {
        if (ql <= l && r <= qr) {
            upd(p, l, r, u);
            return ;
        }
        int mid = l + r >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, u);
        if (mid < qr) update(p << 1 | 1, mid + 1, r, ql, qr, u);
    }
    pii query(int p, int l, int r, int x) {
        if (r < x || x < l) return {0, 0};
        int mid = l + r >> 1;
        int res = s[node[p]].getY(x);
        if (l == r) return {res, node[p]};
        return pmax({res, node[p]}, pmax(query(p << 1, l, mid, x),
                                        query(p << 1 | 1, mid + 1, r, x)));
    }
} Seg[4];
