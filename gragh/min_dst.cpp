vector<ll> dijkstra(int n, int st, const vector<vector<pii>>& g) {
    vector<ll> d(n + 1, ll_inf);
    d[st] = 0;
    struct F {
        ll d;
        int u;
        bool operator<(const F& f) const {
            return d > f.d;
        };
    };
    priority_queue<F> q;
    q.push({0, st});
    while (!q.empty()) {
        auto [dis, u] = q.top();
        q.pop();
        if (dis > d[u]) continue;
        for (auto& e : g[u]) {
            int v = e.x;
            int w = e.y;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    return d;
}