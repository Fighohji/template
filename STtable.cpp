struct STTable {
    vector<vector<int>> st_max;
    vector<vector<int>> st_min;
    vector<int> lg;

    void build_st(int n, const vector<int> &a) {
        lg.resize(n + 1);
        int LG = 1;
        while ((1 << LG) < n)
            LG++;
        st_max.resize(LG + 1, vector<int>(n + 1));
        st_min.resize(LG + 1, vector<int>(n + 1));
        for (int i = 2; i <= n; ++i)
            lg[i] = lg[i >> 1] + 1;
        for (int i = 1; i <= n; ++i)
            st_min[0][i] = st_max[0][i] = a[i];
        for (int j = 1; j <= LG; ++j)
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
};
