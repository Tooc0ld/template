//倍增
namespace LCA {
    //dep[rt] = 1, fa[rt] = 0;
    int dep[N], Log[N], p[N][20];
    void Log_init() { Log[0] = -1; for(int i = 1; i < N; i++) Log[i] = Log[i>>1]+1; } //请使用
    void init(int n) {
        for(int j = 1; j < 20; j++)
        for(int i = 1; i <= n; i++)
            p[i][j] = p[p[i][j-1]][j-1];
    }//不适用dfs的构造
    void dfs(int u, int fa) {
        p[u][0] = fa, dep[u] = dep[fa]+1;
        for(int i = 1; i < 20; i++) p[u][i] = p[p[u][i-1]][i-1];
        for(int v:G[u]) if(v != fa) dfs(v, u);
    }
    I int kfa(int x, int k) { for(; k; x = p[x][Log[k]], k -= 1<<Log[k]); return x; }
    I int lca(int x, int y) {
        if(dep[x] < dep[y]) swap(x, y);
        x = kfa(x, dep[x]-dep[y]);
        if(x == y) return x;
        for(int k = Log[dep[x]-1]; k >= 0; k--)
            if(p[x][k] != p[y][k]) x = p[x][k], y = p[y][k];
        return p[x][0];
    }
}

//欧拉序+ST表
namespace LCA {
    int f[N<<1][25], Log[N<<1];
    void Log_init() { Log[0] = -1; for(int i = 1; i < (N<<1); i++) Log[i] = Log[i>>1]+1; } //请使用

    int dep[N], p[N], q[N<<1], tot;
    void init(int rt) { tot = 0; dfs(rt, 0); RMQ(); }
    void dfs(int u, int fa) {
        q[++tot] = u;
        p[u] = tot; dep[u] = dep[fa]+1;
        for(int v:G[u]) if(v != fa) {
            dfs(v, u);
            q[++tot] = u;
        }
    }
    I void RMQ() {
        for(int i = 1; i <= tot; i++) f[i][0] = q[i];
        for(int j = 1; (1<<j) <= tot; j++)
        for(int i = 1; i+(1<<j)-1 <= tot; i++) {
            if(dep[f[i][j-1]] < dep[f[i+(1<<j-1)][j-1]]) f[i][j] = f[i][j-1];
            else f[i][j] = f[i+(1<<j-1)][j-1];
        }
    }
    I int lca(int x, int y) {
        if(p[x] > p[y]) swap(x, y);
        int k = Log[p[y]-p[x]+1];
        x = f[p[x]][k], y = f[p[y]-(1<<k)+1][k];
        return dep[x]<dep[y]?x:y;
    }
}
