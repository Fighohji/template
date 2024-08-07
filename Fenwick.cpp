struct Fenwick {
    int MX;
    vector<ll> sum;
    Fenwick() {}
    Fenwick(int _MX) : MX(_MX) { sum = vector<ll>(_MX + 1); }
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
    int find(int kth) { // 查全局第k小
        int tot = 0, x = 0;
        for (int i = __lg(MX); ~i; --i) {
            x += 1 << i;
            if (x >= MX || tot + sum[x] >= kth)
                x -= 1 << i;
            else
                tot += sum[x];
        }
        return x + 1;
    }
};
