bool is_prime[maxn];
int phi[maxn];
int prime[maxn];
void pre() {
    for (int i = 1; i <= 5000000; i++) {
        is_prime[i] = 1;
    }
    int cnt = 0;
    is_prime[1] = 0;
    phi[1] = 1;
    for (int i = 2; i <= 5000000; i++) {
        if (is_prime[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= 5000000; j++) {
            is_prime[i * prime[j]] = 0;
            if (i % prime[j])
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
}
