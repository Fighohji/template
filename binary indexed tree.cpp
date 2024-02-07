struct BIT {
    int MX;
    vector<ll> sum;
    BIT() {}
    BIT(int _MX) : MX(_MX) {
        sum = vector<ll>(_MX + 1);
    }
    void upd(int x, int val) {
        while (x <= MX) {
            sum[x] += val;
            x += lowbit(x);
        }
    }
    ll qry(int x) {
        ll res = 0;
        while (x) {
            res += sum[x];
            x -= lowbit(x);
        }
        return res;
    }
} bit;
