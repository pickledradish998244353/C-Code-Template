#include <bits/stdc++.h>

#define x first
#define y second
#define all(x) x.begin(), x.end()
#define pop_cnt(x) __builtin_popcountll((unsigned long long)(x))
#define bcnt32(x) ((x) == 0 ? 0 : 32 - __builtin_clz((unsigned int)(x)))
#define bcnt64(x) ((x) == 0 ? 0 : 64 - __builtin_clzll((unsigned long long)(x)))

using namespace std;
using i128 = __int128;
using u128 = unsigned __int128;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;

const int N = 1e5 + 10, MOD = 998244353;
const int inf = 1e9;
const ll ll_inf = 2e18;
const ld EPS = 1e-11;
const int dx4[] = {-1, 0, 1, 0}, dy4[] = {0, 1, 0, -1};
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int hx[] = {-2, -2, -1, -1, 1, 1, 2, 2}, hy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

istream& operator>>(istream& is, i128& val) {
    string str;
    is >> str;
    val = 0;
    bool flag = false;
    if (str[0] == '-') flag = true, str = str.substr(1);
    for (char& c : str) val = val * 10 + c - '0';
    if (flag) val = -val;
    return is;
}

ostream& operator<<(ostream& os, i128 val) {
    if (val < 0) os << "-", val = -val;
    if (val > 9) os << val / 10;
    os << static_cast<char>(val % 10 + '0');
    return os;
}

template <class T>
auto vec(size_t n) {
    return vector<T>(n);
}

template <class T, class... Args>
auto vec(size_t n, Args... args) {
    return vector<decltype(vec<T>(args...))>(n, vec<T>(args...));
}

ll qpow(ll a, ll b) {
    ll ans = 1;
    a %= MOD;
    while (b) {
        if (b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

template <typename Cap = ll, typename Cost = ll>
struct MCMF {
    struct Edge {
        int to;
        Cap cap;
        Cost cost;
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<Cost> dist;
    vector<int> cur;
    vector<bool> in_q;
    vector<bool> vis;
    Cost total_cost;

    MCMF(int n) : n(n), adj(n + 1), dist(n + 1), cur(n + 1), in_q(n + 1), vis(n + 1) {
    }

    void add_edge(int u, int v, Cap cap, Cost cost) {
        adj[u].push_back({v, cap, cost, (int)adj[v].size()});
        adj[v].push_back({u, 0, -cost, (int)adj[u].size() - 1});
    }

    bool spfa(int s, int t) {
        fill(dist.begin(), dist.end(), ll_inf);
        fill(in_q.begin(), in_q.end(), false);
        queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_q[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_q[u] = false;

            for (auto& e : adj[u]) {
                if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    if (!in_q[e.to]) {
                        q.push(e.to);
                        in_q[e.to] = true;
                    }
                }
            }
        }
        return dist[t] != ll_inf;
    }

    Cap dfs(int u, int t, Cap flow) {
        if (u == t) return flow;
        vis[u] = true;
        Cap pushed = 0;

        for (int& i = cur[u]; i < (int)adj[u].size(); ++i) {
            auto& e = adj[u][i];
            if (!vis[e.to] && e.cap > 0 && dist[e.to] == dist[u] + e.cost) {
                Cap tr = dfs(e.to, t, min(flow - pushed, e.cap));
                if (tr > 0) {
                    e.cap -= tr;
                    adj[e.to][e.rev].cap += tr;
                    pushed += tr;
                    total_cost += tr * e.cost;
                    if (pushed == flow) break;
                }
            }
        }
        vis[u] = false;
        return pushed;
    }

    pair<Cap, Cost> work(int s, int t) {
        Cap flow = 0;
        total_cost = 0;
        while (spfa(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            fill(vis.begin(), vis.end(), false);
            Cap pushed;
            while ((pushed = dfs(s, t, numeric_limits<Cap>::max())) > 0) {
                flow += pushed;
            }
        }
        return {flow, total_cost};
    }
};
void solve() {

/**/ #ifdef LOCAL
    cout << flush;
/**/ #endif
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T--) solve();
    cout << fixed << setprecision(15);

    return 0;
}