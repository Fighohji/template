bool vis[N];
int prime[N];
int cnt;
void isprime(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
