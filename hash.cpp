struct Hash {
    ll seed, p;
    vector<ll> power, hash;
    Hash(const string &s, ll sd = 131, ll P = 1e9 + 7) {
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

class hashVal {
    vector<long long> vec;
    int M;
    hashVal(int n) {
        vec.clear();
        M = n;
        vec.resize(n);
    }
    hashVal operator+(int val) {
        for (int i = 0; i < M; ++i)
            vec[i] = (vec[i] + val) % p;
    }
}
class Hash {
    #define hashVal vector<long long>
    int M = 1;
    hashVal seed, p;
    vector<hashVal> power, hash;
    
    hashVal operator+(const hashVal &lsh, int val) {
    }
    Hash(string &s, const hashVal &sd = {131}, const hashVal  &P = {1000000007}, const int m = 1) {
        M = m;
        seed = sd, p = P;
        power.resize(s.length() + 1, hashVal(M));
        hash.resize(s.length() + 1, hashVal(M));
        power[0] = 1;
        for (int i = 1; i <= s.length(); ++i) {
            for (int j = 0; j < M; ++j) {
                hash[i][j] = (hash[i - 1][j] * seed[j] % p[j] + s[i - 1]) % p[j];
                power[i][j] = power[i - 1][j] * seed[j] % p[j];
            }
        }
    }
    hashVal get_hash(int l, int r) {
        l++, r++;
        hashVal a = hash[r];
        hashVal b = hash[l - 1] * power[r - l + 1] % p;
        return (a - b + p) % p;
    }
};
