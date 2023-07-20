
//普通线段树
int n, m;
ll a[maxn];
ll sum[maxn << 2], lazy[maxn << 2];
void push_up(int p) {
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}
void push_down(int p, int l, int r) {
    if (lazy[p]) {
        int mid = l + r >> 1;
        sum[p << 1] += lazy[p] * (mid - l + 1);
        sum[p << 1 | 1] += lazy[p] * (r - mid);
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
    }
}
void build(int p, int l, int r) {
    //lazy[p] = sum[p] = 0 注意清空！！！
    if (l == r) {
        sum[p] = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}
void update(int p, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        sum[p] += val * (r - l + 1);
        lazy[p] += val;
        return ;
    }
    push_down(p, l, r);
    int mid = l + r >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
    if (mid < qr) update(p << 1 | 1, mid + 1, r, ql, qr, val);
    push_up(p);
}
ll query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum[p];
    push_down(p, l, r);
    int mid = l + r >> 1;
    ll ans = 0;
    if (ql <= mid) ans += query(p << 1, l, mid, ql, qr);
    if (mid < qr) ans += query(p << 1 | 1, mid + 1, r, ql, qr);
    return ans;
}



//可持久化线段树
void update(int rtu, int &rtv, int l, int r, int pos) {
    rtv = ++idx;
    ls[rtv] = ls[rtu], rs[rtv] = rs[rtu], cnt[rtv] = cnt[rtu];
    if (l == r) {
        cnt[rtv]++;
        return ;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(ls[rtu], ls[rtv], l, mid, pos);
    else update(rs[rtu], rs[rtv], mid + 1, r, pos);
    cnt[rtv] = cnt[ls[rtv]] + cnt[rs[rtv]];
}

int query(int rtu, int rtv, int l, int r, int kth) {
    if (kth > cnt[rtv] - cnt[rtu]) return -1;
    if (l == r) return l;
    int mid = l + r >> 1;
    int now = cnt[rs[rtv]] - cnt[rs[rtu]];
    if (now >= kth) return query(rs[rtu], rs[rtv], mid + 1, r, kth);
    else return query(ls[rtu], ls[rtv], l, mid, kth - now);
}




//动态区间第k小树状数组套线段树(主席树是个前缀和，单点修改就直接类似与树状数组单点修改即可)

void update(int &rtv, int l, int r, int pos, int val)
{
    if (!rtv) rtv = ++idx;
    if (l == r) {
        cnt[rtv] += val;
        return ;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(ls[rtv], l, mid, pos, val);
    else update(rs[rtv], mid + 1, r, pos, val);
    cnt[rtv] = cnt[ls[rtv]] + cnt[rs[rtv]];
}

int query(int l, int r, int kth)
{
    if (l == r) return l;
    int sum = 0;
    int mid = l + r >> 1;
    for (int i = bit[0]; i; --i) sum -= cnt[ls[temp[0][i]]];
    for (int i = bit[1]; i; --i) sum += cnt[ls[temp[1][i]]];
    // cout << sum << '\n';
    if (kth <= sum) {
        for (int i = bit[0]; i; --i) temp[0][i] = ls[temp[0][i]];
        for (int i = bit[1]; i; --i) temp[1][i] = ls[temp[1][i]];
        return query(l, mid, kth);
    } else {
        for (int i = bit[0]; i; --i) temp[0][i] = rs[temp[0][i]];
        for (int i = bit[1]; i; --i) temp[1][i] = rs[temp[1][i]];
        return query(mid + 1, r, kth - sum);
    }
}

void add(int x, int pos, int val) { for (int i = pos; i <= len; i += lowbit(i)) update(rt[i], 0, len, x, val); }

int ask(int l, int r,int kth)
{
    bit[0] = bit[1] = 0;
    for (int i = l; i; i -= lowbit(i)) temp[0][++bit[0]] = rt[i];
    for (int i = r; i; i -= lowbit(i)) temp[1][++bit[1]] = rt[i];
    return query(0, len, kth);
}






//线段树分裂，合并，动态开点的空间重复利用
int totnd, totrt, rt[maxn], ls[maxn << 2], rs[maxn << 2];
ll sum[maxn << 2];
int rb[maxn << 2], totrb;

void del(int &p)
{
    rb[++totrb] = p;
    sum[p] = 0;
    ls[p] = 0, rs[p] = 0;
    p = 0;
}

int newnode()
{
    if (totrb) return rb[totrb--];
    return  ++totnd;
}

void update(int &root, int l, int r, int pos, int val)
{
    if (!root) root = newnode();
    if (l == r) {
        sum[root] += val;
        return ;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(ls[root], l, mid, pos, val);
    else update(rs[root], mid + 1, r, pos, val);
    sum[root] = sum[ls[root]] + sum[rs[root]];
}

ll query_sum(int root, int l, int r, int ql, int qr)
{
    if (!root) return 0;
    if (ql <= l && r <= qr) return sum[root];
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query_sum(ls[root], l, mid, ql, qr);
    if (qr > mid) res += query_sum(rs[root], mid + 1, r, ql, qr);
    return res;
}

int query_kth(int root, int l, int r, int k)
{
    int res = -1;
    if (!root || sum[root] < k) return res;
    if (l == r && sum[root] >= k) return l;
    int mid = l + r >> 1;
    if (sum[ls[root]] >= k) res = query_kth(ls[root], l, mid, k);
    else res = query_kth(rs[root], mid + 1, r, k - sum[ls[root]]);
    return res;
}

void merge(int &rtu, int &rtv)
{
    if (!rtv) return ;
    if (!rtu) {
        rtu = rtv;
        return ;
    }
    sum[rtu] += sum[rtv];
    merge(ls[rtu], ls[rtv]);
    merge(rs[rtu], rs[rtv]);
    del(rtv);
}

void split(int &rtu, int &rtv, int l, int r, int ql, int qr)
{
    if (!rtu) return ;
    if (ql <= l && r <= qr) {
        rtv = rtu;
        rtu = 0;
        return ;
    }
    if (!rtv) rtv = newnode();
    int mid = l + r >> 1;
    if (ql <= mid) split(ls[rtu], ls[rtv], l, mid, ql, qr);
    if (qr > mid) split(rs[rtu], rs[rtv], mid + 1, r, ql, qr);
    sum[rtu] = sum[ls[rtu]] + sum[rs[rtu]];
    sum[rtv] = sum[ls[rtv]] + sum[rs[rtv]];
}


//树上三维问题（可以想一下可持久化 + 自底向上合并线段树）


//可持久化0-1trie

void insert(int x, int lst, int now)
{
    for (int i = 24; i >= 0; --i) {
        int c = ((x >> i) & 1);
        trie[now][c ^ 1] = trie[lst][c ^ 1];
        trie[now][c] = ++idx;
        lst = trie[lst][c];
        now = trie[now][c];
        cnt[now] = cnt[lst] + 1;
    }
}

int query(int x, int ls, int rs)
{
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



