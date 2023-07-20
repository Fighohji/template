struct BIT
{
	int MX;
	ll tr[maxn];
	void update(int x, int val)
	{
		while (x <= n) {
			tr[x] += val;
			x += lowbit(x);
		}
	}
	ll query(int x)
	{
		ll sum = 0;
		while (x) {
			sum += tr[x];
			x -= lowbit(x);
		}
		return sum;
	}
}