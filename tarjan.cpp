
vector<int>e[maxn];
vector<int>scm[maxn];
int stk[maxn],top,dfn[maxn],low[maxn],scc[maxn],sccnum,id;
void tarjan(int u)
{
    if(dfn[u]!=0)return ;
    dfn[u]=low[u]=++id;
    stk[++top]=u;
    for(auto v:e[u]) 
    {
        if(dfn[v]==0)
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(scc[v]==0)
            low[u]=min(dfn[v],low[u]);
    }
    if(dfn[u]==low[u])
    {
        sccnum++;
        while(1)
        {
            scm[sccnum].push_back(stk[top]);
            scc[stk[top--]]=sccnum;
            if(stk[top+1]==u)break;
        }
    }
}