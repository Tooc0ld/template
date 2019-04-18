//边双连通分量
int dfn[N], low[N], bccno[N];
int dfs_cnt, bcc_cnt;
stack<int> S;
vector<int> G[N], bcc[N];

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++dfs_cnt;
    S.push(u);
    for(int v:G[u]) if(v != fa) { //有重边时改成判边
        if(!dfn[v]) dfs(v, u), low[u] = min(low[u], low[v]);
        else if(dfn[v] < dfn[u]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) { //该点是割点
        bcc_cnt++;
        bcc[bcc_cnt].clear();
        for(;;) {
            int x = S.top(); S.pop();
            bcc[bcc_cnt].pb(x);
            bccno[x] = bcc_cnt;
            if(x == u) break;
        }
    }
}

//点双连通分量
int dfn[N], low[N];
int dfs_cnt;
stack<PII> S;
vector<int> G[N];

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++dfs_cnt;
    for(int v:G[u]) if(v != fa) {
        if(!dfn[v]) {
            S.push({u, v});
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[u] >= dfn[u]) { //该点是割点
                for(;;) {
                    PII e = S.top(); S.pop();
                    if(e.fi==u && e.se==v) break;
                }
            }
        }
        else if(dfn[v] < dfn[u]) {
            S.push{u, v};
            low[u] = min(low[u], dfn[v]);
        }
    }
}

//强连通分量
int dfn[N], low[N], sccno[N];
int dfs_cnt, scc_cnt;
stack<int> S;
vector<int> G[N], scc[N];

void dfs(int u) {
    dfn[u] = low[u] = ++dfs_cnt;
    S.push(u);
    for(int v:G[u]) if(v != fa) {
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!sccno[v]) low[u] = min(low[u], dfn[v]);
        //不属于其他scc的点
    }
    if(low[u] == dfn[u]) {
        scc_cnt++;
        scc[scc_cnt].clear();
        for(;;) {
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            scc[scc_cnt].pb(x);
            if(x == u) break;
        }
    }
}
