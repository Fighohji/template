multiset<int> to[200];
int stk[N], top;
int deg[200];
void findeuler(int u) {
    while (to[u].size()) {
        int v = *to[u].begin();
        to[u].erase(to[u].begin());
        to[v].erase(to[v].find(u));
        findeuler(v);
    }
    stk[++top] = u;
}

// 无向图
// 一个无向图存在欧拉回路，当且仅当该图所有顶点度数都为偶数,且该图是连通图。
// 一个无向图存在欧拉路径，当且仅当该图所有顶点度数为奇数(作为起点和终点)的点只有0个或2个,且该图是连通图。
// 有向图
// 一个有向图存在欧拉回路，当且仅当所有顶点的入度等于出度且该图是连通图。
// 一个有向图存在欧拉路径，当只有一个点(起点)出度=入度+1和一个点入度=出度+1(终点),
// 或者直接存在欧拉回路
