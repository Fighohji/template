namespace DSU 
{
    int fa[maxn];
    ll sz[maxn];
    void init(int n) { for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1; }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y)
    {
        int xx = find(x), yy = find(y);
        if (xx == yy) return;
        fa[yy] = xx;
        sz[xx] += sz[yy];
    }
}
using namespace DSU;