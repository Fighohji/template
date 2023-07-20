
// int n,m,block,sum=0;

// struct node
// {
// 	int l,r,id;
// }qry[maxn];

// int a[maxn],tmp[maxn],cnt[maxn]={0},ans[maxn];

// bool cmp(node a,node b)
// {
// 	int x=a.l/block,y=b.l/block;
// 	if(x!=y)return x<y;
// 	if(x&1) return a.r>b.r;
// 	return a.r<b.r;
// }

// inline void add(int x)
// {
// 	if(cnt[a[x]]==2)sum--;
// 	cnt[a[x]]++;
// 	if(cnt[a[x]]==2)sum++;
// }

// inline void del(int x)
// {
// 	if(cnt[a[x]]==2)sum--;
// 	cnt[a[x]]--;
// 	if(cnt[a[x]]==2)sum++;
// }

// int main()
// {	 
//     ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//     cin>>n>>m;
//     for(int i=1;i<=n;++i)
// 	{
// 		cin>>a[i];
// 		tmp[i]=a[i];
// 	}
//     sort(tmp+1,tmp+1+n);
//     int len=unique(tmp+1,tmp+1+n)-tmp-1;
//     for(int i=1;i<=n;++i)a[i]=lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
//     block=sqrt(m);
//     for(int i=1;i<=m;++i)
// 	{
//     	cin>>qry[i].l>>qry[i].r;
//     	qry[i].id=i;
// 	}
//     sort(qry+1,qry+1+m,cmp);
//     int l=1,r=0;
//     for(int i=1;i<=m;++i)
//     {
//     	//expand
// 		while(qry[i].l<l)add(--l);
// 		while(qry[i].r>r)add(++r);
//     	//narrow
// 		while(qry[i].l>l)del(l++);
//     	while(qry[i].r<r)del(r--);
//     	ans[qry[i].id]=sum;
// 	}
// 	for(int i=1;i<=m;++i)cout<<ans[i]<<'\n';
// 	return 0;
// }