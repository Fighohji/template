int len;
string s;
int Sa[N];
int Rank[N];
int tmp[N];

il bool Sa_cmp(int i, int j) {
    if (Rank[i] != Rank[j]) return Rank[i] < Rank[j];
    int ri = (i + k <= len ? Rank[i + k] : -1);
    int rj = (j + k <= len ? Rank[j + k] : -1);
    return ri < rj;
}

il void init_Sa(string S) {
    len = S.length();
    for (int i = 0; i <= len; ++i)
        Sa[i] = i, Rank[i] = (i < len ? S[i] : -1);
    for (k = 1; k <= len; k <<= 1) {
        sort(Sa, Sa + len + 1, Sa_cmp);
        tmp[Sa[0]] = 0;
        for (int i = 1; i <= len; ++i)
            tmp[Sa[i]] = tmp[Sa[i - 1]] + Sa_cmp(Sa[i - 1], Sa[i]);
        for (int i = 0; i <= len; ++i)
            Rank[i] = tmp[i];
    }
}

