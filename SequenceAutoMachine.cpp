struct SequenceAutoMachine
{
    vector<vector<int> > nxt;
    string s;
    void init(int n, int char_size)
    {
        nxt.resize(n + 1, vector<int>(char_size, INF));
        for (int i = n - 1; i >= 0; --i) {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i] - 'a'] = i;
        }
    }
    bool find(string t) // 子序列
    {
        int p = -1, len_t = SZ(t);
        for (int i = 0; i < len_t; ++i) {
            p = nxt[p + 1][t[i] - 'a'];
            if (p == -1) return 0;
        }
        return 1;
    }
};