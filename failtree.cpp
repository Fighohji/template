int n;
char s[maxn];
vector<int>e[maxn];int len;
int nxt[maxn];
int parent[30][maxn];int depth[maxn];
il void dfs(int v,int p,int d)
{
    parent[0][v]=p;
    depth[v]=d;
    for(auto i:e[v])
        if(i!=p)
            dfs(i,v,d+1);
}

il void init()
{
    dfs(0,-1,0);
    for(int k=0;k<29;++k)
        for(int v=1;v<=len;++v)
        {
            if(parent[k][v]<=0)parent[k+1][v]=0;
            else parent[k+1][v]=parent[k][parent[k][v]];
        }
}

il int lca(int u,int v)
{
 //if(u==v)return parent[0][u];
    if(depth[u]>depth[v])swap(u,v);
    for(int k=0;k<29;++k)
        if((depth[v]-depth[u])>>k&1)
            v=parent[k][v];
    //if(u==v)return u;
    for(int k=28;k>=0;--k)
        if(parent[k][u]!=parent[k][v])
            u=parent[k][u],v=parent[k][v];
    return parent[0][u];
}
il void getNXT()
{
 int i,j=0;
 nxt[1]=0;
 e[0].push_back(1);
 for(int i=2;i<=len;++i)
 {
     while(j>0&&s[j+1]!=s[i])j=nxt[j];
     if(s[j+1]==s[i])j++;
     nxt[i]=j;
     e[j].push_back(i);
 }
}
il void solve(int cas)
{
 cin>>s+1>>n;
 len=strlen(s+1);
 getNXT();
 init();
 while(n--)
 {
     int a,b;cin>>a>>b;
     int k=lca(a,b);
     // if(k==a||k==b)
     //  k=parent[0][k];
     cout<<k<<'\n';
 }
}
