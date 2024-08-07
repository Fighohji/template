map<ll, ll> mp;
int BSGS(ll a, ll b, ll p) {
    ll t = ceil(sqrt(p));
    b %= p;
    int t = (int)sqrt(p) + 1;
    for (int j = 0; j < t; ++j) {
        ll val = (ll)b * qpow(a, j, p) % p;
        mp[val] = j;
    }
    a = qpow(a, t, p);
    if (a == 0) return b == 0 ? 1 : -1;
    for (int i = 0; i <= t; ++i) {
        ll val = qpow(a, i, p);
        int j = mp.find(val) == mp.end() ? -1 : mp[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}
