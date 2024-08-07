int n, k, m, p;
vector<int> e[N];
int ans;
int match[N];
bool used[N];
bool dfs(int u) {
    for (int v : e[u]) {
        if (!used[v]) {
            used[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
