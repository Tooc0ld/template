//clear d:array and g:vector
void dijsktra(int s, int t)
{
    priority_queue<PII, vector<PII>, greater<PII>> Q;
    Q.emplace(0, s);

    while (!Q.empty())
    {
        int u = Q.top().se, dis = Q.top().fi;
        Q.pop();

        if (dis != d[u])
            continue;

        for (PII it : g[u])
        {
            int v = it.fi;
            if (d[v] > d[u] + it.se)
            {
                d[v] = d[u] + it.se;
                Q.emplace(d[v], v);
            }
        }
    }
}
