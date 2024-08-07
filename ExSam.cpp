struct ExSAM {
    vector<int> len, link;
    vector<vector<int>> nxt;
    int CHRSIZE, cnt;
    void init(int strlen, int chrsize) {
        CHRSIZE = chrsize;
        len.clear(), link.clear(), nxt.clear();
        len.resize((1 + strlen) << 1);
        link.resize((1 + strlen) << 1);
        nxt.resize((1 + strlen) << 1, vector<int>(chrsize));
        cnt = 1;
    }
    int addSam(int last, int c) {
        int cur = nxt[last][c];
        if (len[cur]) return cur;
        len[cur] = len[last] + 1;
        int p = link[last];
        while (p && !nxt[p][c]) {
            nxt[p][c] = cur;
            p = link[p];
        }
        if (!p) {
            link[cur] = 1;
            return cur;
        }
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            return cur;
        }
        int cl = ++cnt;
        for (int i = 0; i < CHRSIZE; ++i)
            nxt[cl][i] = len[nxt[q][i]] != 0 ? nxt[q][i] : 0;
        len[cl] = len[p] + 1;
        link[cl] = link[q];
        link[cur] = link[q] = cl;
        while (p && nxt[p][c] == q) {
            nxt[p][c] = cl;
            p = link[p];
        }
        return cur;
    }
    int addTrie(int cur, int c) {
        if (nxt[cur][c]) return nxt[cur][c];
        return nxt[cur][c] = ++cnt;
    }
    void add(const string &s) {
        int now = 1;
        for (auto &i : s)
            now = addTrie(now, i - 'a');
    }
    void build() {
        queue<pii> q;
        for (int i = 0; i < 26; ++i)
            if (nxt[1][i]) q.push({i, 1});
        while (!q.empty()) {
            auto [ch, las] = q.front();
            q.pop();
            int last = addSam(las, ch);
            for (int i = 0; i < CHRSIZE; ++i) {
                if (nxt[last][i]) q.push({i, last});
            }
        }
    }
} exsam;

string s[N];
int tot;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        tot += s[i].length();
    }
    exsam.init(tot, 26);
    for (int i = 0; i < n; ++i) {
        exsam.add(s[i]);
    }
    exsam.build();
    ll ans = 0;
    for (int i = 1; i <= exsam.cnt; ++i) {
        ans += exsam.len[i] - exsam.len[exsam.link[i]];
    }
    cout << ans << '\n' << exsam.cnt << '\n';
}
