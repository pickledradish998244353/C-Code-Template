struct Primes {
    int n;
    vector<int> ps;
    vector<int> vis;

    Primes(int _n) : n(_n), vis(_n + 1) {
        for (int i = 2; i <= n; ++i) {
            if (!vis[i]) {
                ps.push_back(i);
            }
            for (int j : ps) {
                if (1ll * j * i > n) break;
                vis[i * j] = 1;
                if (i % j == 0) break;
            }
        }
    };
};