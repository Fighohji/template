// 普通线段树
struct Info {
    Info() {}
    Info operator+(const Info &t) const {
        Info i = *this;
        return i;
    }
};

struct Tag {
    Tag() {}
};

void apply(Info &p, Tag &tag, const Tag &val) {}

struct SegTree {
    vector<Info> node;
    vector<Tag> tag;
    SegTree(const vector<Info> &vec) {
        int n = vec.size();
        node.assign((n << 2) + 1, Info());
        tag.assign((n << 2) + 1, Tag());
        auto build = [&](auto self, int p, int l, int r) -> void {
            if (l == r) {
                node[p] = vec[l - 1];
                return;
            }
            int mid = (l + r) >> 1;
            self(self, p << 1, l, mid);
            self(self, p << 1 | 1, mid + 1, r);
            node[p] = node[p << 1] + node[p << 1 | 1];
        };
        build(build, 1, 1, n);
    }
    void push(int p) {
        apply(node[p << 1], tag[p << 1], tag[p]);
        apply(node[p << 1 | 1], tag[p << 1 | 1], tag[p]);
        tag[p] = Tag();
    }
    void upd(int p, int l, int r, int ql, int qr, const Tag &val) {
        if (ql > qr) return;
        if (ql <= l && r <= qr) {
            apply(node[p], tag[p], val);
            return;
        }
        push(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) upd(p << 1, l, mid, ql, qr, val);
        if (mid < qr) upd(p << 1 | 1, mid + 1, r, ql, qr, val);
        node[p] = node[p << 1] + node[p << 1 | 1];
    }
    void upd(int p, int l, int r, int pos, const Info &val) {
        if (l == r) {
            node[p] = val;
            return;
        }
        int mid = (l + r) >> 1;
        push(p);
        if (pos <= mid)
            upd(p << 1, l, mid, pos, val);
        else
            upd(p << 1 | 1, mid + 1, r, pos, val);
        node[p] = node[p << 1] + node[p << 1 | 1];
    }
    Info qry(int p, int l, int r, int ql, int qr) {
        if (ql > qr) return Info();
        if (ql <= l && r <= qr) return node[p];
        push(p);
        int mid = (l + r) >> 1;
        Info res = Info();
        if (ql <= mid) res = res + qry(p << 1, l, mid, ql, qr);
        if (mid < qr) res = res + qry(p << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
    Info qry(int p, int l, int r, int pos) {
        if (l == r) return node[p];
        push(p);
        int mid = (l + r) >> 1;
        if (pos <= mid) return qry(p << 1, l, mid, pos);
        return qry(p << 1 | 1, mid + 1, r, pos);
    }
};

// 可持久化线段树
void update(int rtu, int &rtv, int l, int r, int pos) {
    rtv = ++idx;
    ls[rtv] = ls[rtu], rs[rtv] = rs[rtu], cnt[rtv] = cnt[rtu];
    if (l == r) {
        cnt[rtv]++;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(ls[rtu], ls[rtv], l, mid, pos);
    else
        update(rs[rtu], rs[rtv], mid + 1, r, pos);
    cnt[rtv] = cnt[ls[rtv]] + cnt[rs[rtv]];
}

int query(int rtu, int rtv, int l, int r, int kth) {
    if (kth > cnt[rtv] - cnt[rtu]) return -1;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int now = cnt[rs[rtv]] - cnt[rs[rtu]];
    if (now >= kth)
        return query(rs[rtu], rs[rtv], mid + 1, r, kth);
    else
        return query(ls[rtu], ls[rtv], l, mid, kth - now);
}

// query-first 线段树上区间二分
int qry(int p, int l, int r, int ql, int qr, int k, int &pre) {
    if (ql <= l && r <= qr && sum[p] + pre < k) {
        pre += sum[p];
        return INF;
    }
    int mid = (l + r) >> 1;
    if (ql <= l && r <= qr) {
        if (l == r && (pre += sum[p]) == k) { return l; }
        if (sum[ls[p]] + pre >= k)
            return qry(ls[p], l, mid, ql, qr, k, pre);
        else
            return qry(rs[p], mid + 1, r, ql, qr, k, pre += sum[ls[p]]);
    }
    int pos = INF;
    if (ql <= mid) pos = qry(ls[p], l, mid, ql, qr, k, pre);
    if (pos == INF && mid < qr) return qry(rs[p], mid + 1, r, ql, qr, k, pre);
    return pos;
}
// 动态区间第k小树状数组套线段树(主席树是个前缀和，单点修改就直接类似与树状数组单点修改即可)

void update(int &rtv, int l, int r, int pos, int val) {
    if (!rtv) rtv = ++idx;
    if (l == r) {
        cnt[rtv] += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(ls[rtv], l, mid, pos, val);
    else
        update(rs[rtv], mid + 1, r, pos, val);
    cnt[rtv] = cnt[ls[rtv]] + cnt[rs[rtv]];
}

int query(int l, int r, int kth) {
    if (l == r) return l;
    int sum = 0;
    int mid = (l + r) >> 1;
    for (int i = bit[0]; i; --i)
        sum -= cnt[ls[temp[0][i]]];
    for (int i = bit[1]; i; --i)
        sum += cnt[ls[temp[1][i]]];
    if (kth <= sum) {
        for (int i = bit[0]; i; --i)
            temp[0][i] = ls[temp[0][i]];
        for (int i = bit[1]; i; --i)
            temp[1][i] = ls[temp[1][i]];
        return query(l, mid, kth);
    } else {
        for (int i = bit[0]; i; --i)
            temp[0][i] = rs[temp[0][i]];
        for (int i = bit[1]; i; --i)
            temp[1][i] = rs[temp[1][i]];
        return query(mid + 1, r, kth - sum);
    }
}

void add(int x, int pos, int val) {
    for (int i = pos; i <= len; i += lowbit(i))
        update(rt[i], 0, len, x, val);
}

int ask(int l, int r, int kth) {
    bit[0] = bit[1] = 0;
    for (int i = l; i; i -= lowbit(i))
        temp[0][++bit[0]] = rt[i];
    for (int i = r; i; i -= lowbit(i))
        temp[1][++bit[1]] = rt[i];
    return query(0, len, kth);
}

// 线段树分裂，合并，动态开点的空间重复利用
int totnd, totrt, rt[N], ls[N << 2], rs[N << 2];
ll sum[N << 2];
int rb[N << 2], totrb;

void del(int &p) {
    rb[++totrb] = p;
    sum[p] = 0;
    ls[p] = 0, rs[p] = 0;
    p = 0;
}

int newnode() {
    if (totrb) return rb[totrb--];
    return ++totnd;
}

void update(int &root, int l, int r, int pos, int val) {
    if (!root) root = newnode();
    if (l == r) {
        sum[root] += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(ls[root], l, mid, pos, val);
    else
        update(rs[root], mid + 1, r, pos, val);
    sum[root] = sum[ls[root]] + sum[rs[root]];
}

ll query_sum(int root, int l, int r, int ql, int qr) {
    if (!root) return 0;
    if (ql <= l && r <= qr) return sum[root];
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) res += query_sum(ls[root], l, mid, ql, qr);
    if (qr > mid) res += query_sum(rs[root], mid + 1, r, ql, qr);
    return res;
}

int query_kth(int root, int l, int r, int k) {
    int res = -1;
    if (!root || sum[root] < k) return res;
    if (l == r && sum[root] >= k) return l;
    int mid = (l + r) >> 1;
    if (sum[ls[root]] >= k)
        res = query_kth(ls[root], l, mid, k);
    else
        res = query_kth(rs[root], mid + 1, r, k - sum[ls[root]]);
    return res;
}

void merge(int &rtu, int &rtv) {
    if (!rtv) return;
    if (!rtu) {
        rtu = rtv;
        return;
    }
    sum[rtu] += sum[rtv];
    merge(ls[rtu], ls[rtv]);
    merge(rs[rtu], rs[rtv]);
    del(rtv);
}

void split(int &rtu, int &rtv, int l, int r, int ql, int qr) {
    if (!rtu) return;
    if (ql <= l && r <= qr) {
        rtv = rtu;
        rtu = 0;
        return;
    }
    if (!rtv) rtv = newnode();
    int mid = (l + r) >> 1;
    if (ql <= mid) split(ls[rtu], ls[rtv], l, mid, ql, qr);
    if (qr > mid) split(rs[rtu], rs[rtv], mid + 1, r, ql, qr);
    sum[rtu] = sum[ls[rtu]] + sum[rs[rtu]];
    sum[rtv] = sum[ls[rtv]] + sum[rs[rtv]];
}

// 树上三维问题（可以想一下可持久化 + 自底向上合并线段树）

// 可持久化0-1trie

void insert(int x, int lst, int now) {
    for (int i = 24; i >= 0; --i) {
        int c = ((x >> i) & 1);
        trie[now][c ^ 1] = trie[lst][c ^ 1];
        trie[now][c] = ++idx;
        lst = trie[lst][c];
        now = trie[now][c];
        cnt[now] = cnt[lst] + 1;
    }
}

int query(int x, int ls, int rs) {
    int ans = 0;
    for (int i = 24; i >= 0; --i) {
        int c = ((x >> i) & 1);
        if (cnt[trie[rs][c ^ 1]] > cnt[trie[ls][c ^ 1]]) {
            ans |= (1 << i);
            c ^= 1;
        }
        ls = trie[ls][c];
        rs = trie[rs][c];
    }
    return ans;
}

