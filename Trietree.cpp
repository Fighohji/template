int getnum(char x) {
    if (x >= 'A' && x <= 'Z')
        return x - 'A';
    else if (x >= 'a' && x <= 'z')
        return x - 'a' + 26;
    else
        return x - '0' + 52;
}
int T[N][26], idx = 1;
void ins(const string &s) {
    int u = 1;
    for (auto i : s) {
        if (!T[u][i - 'a'])
            T[u][i - 'a'] = ++idx;
        u = T[u][i - 'a'];
    }
}
