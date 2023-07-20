int st_min[20][maxm], st_max[20][maxm];

int lg[maxm];

void build_st() {
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
        st_min[0][i] = st_max[0][i] = in[a[i]];
    for (int j = 1; j <= 18; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st_min[j][i] = min(st_min[j - 1][i], st_min[j - 1][i + (1 << (j - 1))]),
            st_max[j][i] = max(st_max[j - 1][i], st_max[j - 1][i + (1 << (j - 1))]);
}

int query_min(int l, int r) {
    int k = lg[r - l + 1];
    return min(st_min[k][l], st_min[k][r - (1 << k) + 1]);
}

int query_max(int l, int r) {
    int k = lg[r - l + 1];
    return max(st_max[k][l], st_max[k][r - (1 << k) + 1]);
}
