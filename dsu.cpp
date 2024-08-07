struct DSU {
    vector<int> fa;
    DSU() {}
    DSU(int n) {
        fa.resize(n + 1);
        iota(all(fa), 0);
    }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) {
        int xx = find(x), yy = find(y);
        if (xx == yy) return;
        fa[yy] = xx;
    }
};
