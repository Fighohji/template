int fa[N], val[N], ch[N][2], idx, siz[N], cnt[N], Xor[N], tag[N];

int get(int x) { return ch[fa[x]][1] == x; }

int isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p) {
    siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + cnt[p];
    Xor[p] = Xor[ch[p][0]] ^ Xor[ch[p][1]] ^ val[p];
}

void apply(int p) {
    if (!p) return;
    tag[p] ^= 1;
    swap(ch[p][0], ch[p][1]);
}
// !!! 注意修改的时候不要只改lazy
void pushdown(int p) {
    if (tag[p]) {
        apply(ch[p][0]);
        apply(ch[p][1]);
        tag[p] = 0;
    }
}

void pushdown_rt(int p) {
    if (!isRoot(p)) pushdown_rt(fa[p]);
    pushdown(p);
}

void rotate(int x) {
    int y = fa[x], z = fa[y], c = get(x);
    // 保证虚边单向连通
    if (!isRoot(y)) ch[z][y == ch[z][1]] = x;
    ch[y][c] = ch[x][c ^ 1];
    if (ch[x][c ^ 1]) fa[ch[x][c ^ 1]] = y;
    ch[x][c ^ 1] = y;
    fa[y] = x, fa[x] = z;
    // 先更新孩子 再更新父亲
    pushup(y);
    pushup(x);
}

void splay(int x) {
    pushdown_rt(x);
    for (; !isRoot(x); rotate(x)) {
        if (!isRoot(fa[x]))
            rotate(get(x) == get(fa[x]) ? fa[x] : x);
    }
}

// 将x到原树的根放到一条实链中
int access(int x) {
    int p;
    for (p = 0; x; x = fa[x]) {
        splay(x);
        ch[x][1] = p, p = x;
        pushup(x); // 必须要写，因为右儿子变化
    }
    return p;
}

// 成为原树的根
void makeRoot(int p) {
    p = access(p);
    apply(p);
}

// 找到p所在原树的根，可用于判连通性
int findRoot(int p) {
    int _ = access(p);
    splay(p);
    pushdown(p);
    while (ch[p][0]) {
        p = ch[p][0];
        pushdown(p);
    }
    splay(p);
    return p;
}

void link(int x, int y) {
    makeRoot(x);
    splay(x);
    if (findRoot(y) != x) fa[x] = y;
}

// makeRoot + findRoot 
// 相当于做了一个split的操作
// 但是这里写法在findRoot最后的时候又把x转了上去
// 还是不完全相同的
// 不过由于如果有连边这条实链长度为2所以没有影响
void cut(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x && fa[y] == x && !ch[y][0]) {
        ch[x][1] = 0;
        fa[y] = 0;
        pushup(x);
    }
}

// 提取x到y的路径信息，返回包含信息之和的节点
int split(int x, int y) {
    makeRoot(x);
    return access(y);
}

// 单点修改
void change(int x, int y) {
    splay(x);
    val[x] = y;
    pushup(x);
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> val[i];

    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) {
            cout << Xor[split(x, y)] << '\n';
        } else if (op == 1) {
            link(x, y);
        } else if (op == 2) {
            cut(x, y);
        } else {
            change(x, y); 
        }
    }
}
