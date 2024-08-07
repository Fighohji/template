int n, cnt = 1;
char s[N];
int len[N];
void manaqr() {
    char c = getchar();
    s[0] = '~', s[cnt] = '|';
    while (c < 'a' || c > 'z')
        c = getchar();
    while (c >= 'a' && c <= 'z')
        s[++cnt] = c, s[++cnt] = '|', c = getchar();
    s[cnt + 1] = 0;
}
int ans;
void manacher() {
    manaqr();
    for (int t = 1, r = 0, mid = 0; t <= cnt; ++t) {
        if (t <= r) len[t] = min(len[(mid << 1) - t], r - t + 1);
        while (s[t - len[t]] == s[t + len[t]])
            ++len[t];
        if (len[t] + t > r) r = len[t] + t - 1, mid = t;
        if (len[t] - 1 > ans) ans = len[t] - 1;
    }
    cout << ans;
}
