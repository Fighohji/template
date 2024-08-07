ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll g = ex_gcd(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

// 中国剩余定理
// (∑ai*Mi*Mi−1​)%M
