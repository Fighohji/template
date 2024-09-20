int n, cnt = 1;
char s[N];
int len[N]; // 原串中以i为中心最长回文串长度加1，拓展串中以i为中心的最长回文半径
void manaqr() {
    char c = getchar();
    s[0] = '~', s[cnt] = '|';
    while (c < 'a' || c > 'z')
        c = getchar();
    while (c >= 'a' && c <= 'z')
        s[++cnt] = c, s[++cnt] = '|', c = getchar();
    s[cnt + 1] = 0;
}
void manacher() {
    manaqr();
    // t是当前枚举的回文中心，mid是上一个进行暴力拓展的位置，r是上一个进行拓展的回文串的最大回文半径
    for (int t = 1, r = 0, mid = 0; t <= cnt; ++t) {
        if (t <= r) len[t] = min(len[(mid << 1) - t], r - t + 1);
        while (s[t - len[t]] == s[t + len[t]])
            ++len[t];
        if (len[t] + t > r) r = len[t] + t - 1, mid = t;
    }
}
