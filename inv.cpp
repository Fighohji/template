inv[i] = (p - p / i) * inv[p % i] % p;

il ll inv(ll x) { return qpow(x, mod - 2); }
