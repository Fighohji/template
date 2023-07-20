struct Hash
{
    ull seed = 131, p;
    ull hash[105], power[105];
    void init(string &s, ull P = UINT64_MAX)
    {
        p = P;
        power[0] = 1;
        for (int i = 1; i <= s.length(); ++i) {
            hash[i] = (hash[i - 1] * seed % p + s[i - 1]) % p;
            power[i] = power[i - 1] * seed % p;
        }
    }
    ull get_hash(int l, int r)
    {
        l++, r++;
        ull a = hash[r];
        ull b = hash[l - 1] * power[r - l + 1] % p;
        return (a - b + p) % p;
    }
};