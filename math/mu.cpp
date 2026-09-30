struct Mu {
    int n;
    vector<int> ps;
    vector<int> vis;
    vector<int> mu;
    Mu(int _n) : n(_n), vis(_n + 1), mu(_n + 1) {
        mu[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!vis[i]) {
                ps.push_back(i);
                mu[i] = -1;
            }
            for (int j : ps) {
                if (1ll * j * i > n) break;
                vis[i * j] = 1;
                if (i % j == 0) {
                    mu[i * j] = 0;
                    break;
                }
                mu[i * j] = -mu[i];
            }
        }
    };
};