int block;

struct node {
    int l, r, id;
} qry[N];

bool cmp(node a, node b) {
    int x = a.l / block, y = b.l / block;
    if (x != y) return x < y;
    if (x & 1) return a.r > b.r;
    return a.r < b.r;
}
