struct Hash {
    ll seed, p;
    vector<ll> power, hash;
    void init(string &s, ll sd = 131, ll P = 1e9 + 7) {
        seed = sd, p = P;
        power.resize(s.length() + 1);
        hash.resize(s.length() + 1);
        power[0] = 1;
        for (int i = 1; i <= s.length(); ++i) {
            hash[i] = (hash[i - 1] * seed % p + s[i - 1]) % p;
            power[i] = power[i - 1] * seed % p;
        }
    }
    ll get_hash(int l, int r) {
        l++, r++;
        ll a = hash[r];
        ll b = hash[l - 1] * power[r - l + 1] % p;
        return (a - b + p) % p;
    }
};
// 99999991072401712
