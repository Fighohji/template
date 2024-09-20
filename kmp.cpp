vector<int> getNxt(const string &s) {
    vector<int> nxt(s.length());
    for (int i = 1; i < s.length(); i++) {
        int j = nxt[i - 1];
        while (j > 0 && s[i] != s[j]) j = nxt[j - 1];
        j += s[i] == s[j];
        nxt[i] = j;
    }
    return nxt;
}
