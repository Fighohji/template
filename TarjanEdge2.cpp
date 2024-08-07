vector<Nxt> G[maxn];
bool inStk[maxn];
int low[maxn], stk[maxn], dfn[maxn], belong[maxn], clk, top, blockCnt;
void tarjan(int u, int p) {
    if (dfn[u]) return ;
    low[u] = dfn[u] = ++clk;
    stk[++top] = u; inStk[u] = 1;
    for (auto [v, id] : G[u]) {
        if (p == id) continue;
        if (!dfn[v]) {
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
        } else if (inStk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        blockCnt++;
        while (stk[top] != u) {
            belong[stk[top]] = blockCnt;
            inStk[stk[top--]] = 0;
        }
        belong[u] = blockCnt;
        inStk[u] = 0;
        top--;
    }
}
