int fa[N], val[N], ch[N][2], rt, idx, siz[N], cnt[N];
void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = cnt[x] = siz[x] = val[x] = 0; }
int get(int x) { return ch[fa[x]][1] == x; }
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x]; }
void rotate(int x) {
    int y = fa[x], z = fa[y], c = get(x);
    if (z) ch[z][y == ch[z][1]] = x;
    ch[y][c] = ch[x][c ^ 1];
    if (ch[x][c ^ 1]) fa[ch[x][c ^ 1]] = y;
    ch[x][c ^ 1] = y;
    fa[y] = x, fa[x] = z;
    // 先更新孩子 再更新父亲
    pushup(y);
    pushup(x);
}
void splay(int x, int tar = 0) {
    if (x == tar) return;
    for (; fa[x] != tar; rotate(x)) {
        if (fa[fa[x]] != tar)
            rotate(get(x) == get(fa[x]) ? fa[x] : x);
    }
    if (!tar) rt = x;
}
void ins(int x) {
    if (!rt) {
        // 更新插入节点信息
        val[++idx] = x;
        cnt[idx]++;
        rt = idx;
        pushup(rt);
        return;
    }
    int cur = rt, par = 0;
    while (cur && val[cur] != x) {
        par = cur;
        cur = ch[cur][val[cur] < x];
    }
    if (!cur) {
        val[++idx] = x;
        fa[idx] = par;
        ch[par][val[par] < x] = idx;
        cur = idx;
    }
    cnt[cur]++;
    pushup(cur);
    pushup(par);
    splay(cur);
}
int getRank(int x) {
    int res = 0, cur = rt, las = cur;
    while (cur) {
        if (val[cur] > x) {
            las = cur;
            cur = ch[cur][0];
        } else {
            res += siz[ch[cur][0]];
            if (x == val[cur]) break;
            res += cnt[cur];
            las = cur;
            cur = ch[cur][1];
        }
    }
    splay(cur ? cur : las);
    return res + 1;
}

int getKth(int kth) {
    if (siz[rt] < kth) return -1;
    int cur = rt;
    while (kth > 0) {
        if (siz[ch[cur][0]] >= kth) {
            cur = ch[cur][0];
        } else {
            kth -= siz[ch[cur][0]] + cnt[cur];
            if (kth > 0) cur = ch[cur][1];
        }
    }
    splay(cur);
    return val[cur];
}

// find current root's prev
int findPre() {
    int cur = ch[rt][0];
    if (!cur) return cur;
    while (ch[cur][1]) cur = ch[cur][1];
    splay(cur);
    return cur;
}

// find current root's next
int findNxt() {
    int cur = ch[rt][1];
    if (!cur) return cur;
    while (ch[cur][0]) cur = ch[cur][0];
    splay(cur);
    return cur;
}

void del(int x) {
    getRank(x);
    if (--cnt[rt]) {
        pushup(rt);
        return;
    }
    if (!ch[rt][0] && !ch[rt][1]) {
        clear(rt);
        rt = 0;
        return;
    }
    if (!ch[rt][0]) {
        int cur = rt;
        rt = ch[rt][1];
        fa[rt] = 0;
        clear(cur);
        return;
    }
    if (!ch[rt][1]) {
        int cur = rt;
        rt = ch[rt][0];
        fa[rt] = 0;
        clear(cur);
        return;
    }
    int cur = rt, t = findPre();
    fa[rt] = 0;
    fa[ch[cur][1]] = t;
    ch[t][1] = ch[cur][1];
    clear(cur);
    pushup(rt);
}

/*-----------------------------------*/
int lazy[N];
//区间翻转
//注意有lazy标记则在访问每一个节点之前都要pushdown_down
void apply(int p) {
    lazy[p] ^= 1;
    swap(ch[p][0], ch[p][1]);
}

void pushdown(int p) {
    if (lazy[p]) {
        apply(ch[p][0]);
        apply(ch[p][1]);
        lazy[p] = 0;
    }
}
void build(int &p, int l, int r, int f, const vector<int> &vec) {
    if (l > r) return;
    p = ++idx;
    int mid = (l + r) >> 1;
    val[p] = vec[mid], fa[p] = f, cnt[p] = 1;
    build(ch[p][0], l, mid - 1, p, vec); // !!! 注意平衡树和线段树不一样，平衡树每个节点都会插入mid这个点
    build(ch[p][1], mid + 1, r, p, vec);
    pushup(p);
}
int getKth(int kth) {
    if (siz[rt] < kth) return -1;
    int cur = rt;
    while (kth > 0) {
        pushdown(cur);
        if (siz[ch[cur][0]] >= kth) {
            cur = ch[cur][0];
        } else {
            kth -= siz[ch[cur][0]] + cnt[cur];
            if (kth > 0) cur = ch[cur][1];
        }
    }
    splay(cur);
    return cur;
}
void update(int l, int r) {
    // int L = getKth(l), R = getKth(r + 2); // 插入了0，所以l和r都要+1
    // splay(L), splay(R, L);

    int R = getKth(r + 2), L = getKth(l);
    splay(R, L);
    int p = ch[ch[rt][1]][0];
    update(p);
}
void solve() {
    int n;
    cin >> n;
    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            ins(x);
        } else if (opt == 2) {
            del(x);
        } else if (opt == 3) {
            cout << getRank(x) << '\n';
        } else if (opt == 4) {
            cout << getKth(x) << '\n';
        } else if (opt == 5) {
            ins(x);
            findPre();
            cout << val[rt] << '\n';
            del(x);
        } else {
            ins(x);
            findNxt();
            cout << val[rt] << '\n';
            del(x);
        }
    }
}
