// 线形基
struct Base
{
    int lim = 32;
    vector<ll> pos;
    Base() { pos.resize(lim + 1, 0); }
    bool insert(ll p)
    {
        for (int i = lim; i >= 0; --i) {
            if (p & 1 << i) {
                if (!pos[i]) {
                    pos[i] = p;
                    return 1;
                }
                p ^= pos[i];
            }
        }
        return 0;
    }
};