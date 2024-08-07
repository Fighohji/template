vector<int> getNxt(string &s) {
    vector<int> nxt(s.length());
    int cur = 0;
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == s[cur]) {
            nxt[i] = ++cur;
        } else if (cur != 0) {
            cur = nxt[cur - 1];
            i--;
        } else {
            nxt[i] = 0;
        }
    }
    return nxt;
}
