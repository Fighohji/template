int n,m,root;//n个结点m条有向边，以root为根。
int u,v,w;
int g[N][N],inCost[N],pre[N];//inCost[u]存储u的最小入边花费。pre[u]存储u的前驱结点。
int id[N],vis[N];//id[u]表示u重新编号的点，这个数组是为了处理有向环的。vis[u]表示u是通过vis[u]来访问的。
struct node{
    int u,v,w;
}edges[N];
int zhuliu(){
    ll res = 0;//res统计边权和。
    while(true){
        for(int i = 1; i <= n; ++ i)inCost[i] = INF, id[i] = vis[i] = -1;//初始化入边消耗等。
        for(int i = 0; i < m; ++ i){
            u = edges[i].u, v = edges[i].v, w = edges[i].w;
            if(u != v && w < inCost[v]){
                inCost[v] = w;
                pre[v] = u;
            }
        }
        for(int i = 1; i <= n; ++ i){
            if(i != root && inCost[i] == INF){
                //说明不存在入边，无法构成树形图。
                return -1;
            }
        }
        inCost[root] = 0;
        int tn = 0;//新的编号。
        for(int i = 1; i <= n; ++ i){
            res += inCost[i];//统计入边消耗。
            v = i;
            while(vis[v] != i && id[v] == -1 && v != root){
                vis[v] = i;
                v = pre[v];//不断迭代前驱结点，知道更新到根结点。若是环，当处于vis[v] = i时即会退出，即回到起点。
            }
            if(v != root && id[v] == -1){
                //说明不是以root为根结点。即出现了有向环
                id[v] = ++tn;
                for(u = pre[v]; u != v; u = pre[u])id[u] = tn;//重新给有向环编号，便于之后缩点。
            }
        }
        if(tn == 0)break;//说明没有重新编号，即不存在有向环。
        for(int i = 1; i <= n; ++ i){
            if(id[i] == -1){
                id[i] = ++tn;//给未重新编号的也重新编号，便于处理。
            }
        }
        int i = 0;
        while(i < m){
            int vv = edges[i].v;//由于入边还存着是原来的编号，所以这里取出入边终点。
            //获取重新的编号。
            edges[i].u = id[edges[i].u], edges[i].v = id[edges[i].v];
            if(edges[i].u != edges[i].v){
                //这里看做是环外一点入环内的v点，所以我们需要减去环内入边权。
                //这样可以避免重复计算。
                edges[i ++].w -= inCost[vv];//更新权值，因为这个已经被累加了。
            }
            else{
                //将有向环环边抛出。
                swap(edges[i],edges[-- m]);
            }
        }
        n = tn;//更新新的结点数量。
        root = id[root];//更新根结点编号。
    }
    return res;
}
void solve(){
    cout<<zhuliu()-inf<<'\n';
}

int main()
{	
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;root=n+1;n++;
    for(int i = 1; i <= n; ++ i)for(int j = 1; j <= n; ++ j)g[i][j] = INF;
    for(int i=1;i<=m;++i)
    {
        cin>>u>>v>>w;
        if(u == v)continue;
        g[u][v] = min(g[u][v],w);
    }
    for(int i=1;i<n;++i)
    {
        g[n][i]=inf;
    }
    m = 0;
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= n; ++ j){
            //将边存储起来。
            if(g[i][j] != INF){
                edges[m].u = i,edges[m].v = j,edges[m ++].w = g[i][j];
            }
        }
    }
    solve();
    return 0;
}
