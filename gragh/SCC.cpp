#include <bits/stdc++.h>

#define x first
#define y second
#define all(x) x.begin(), x.end()
#define vec1(T, name, n, val) vector<T> name(n, val)
#define vec2(T, name, n, m, val) vector<vector<T>> name(n, vector<T>(m, val))
#define vec3(T, name, n, m, k, val) vector<vector<vector<T>>> name(n, vector<vector<T>>(m, vector<T>(k, val)))
#define vec4(T, name, n, m, k, p, val) vector<vector<vector<vector<T>>>> name((n), vector<vector<vector<T>>>((m), vector<vector<T>>((k), vector<T>((p), (val)))))

using namespace std;
using i128 = __int128;
using u128 = unsigned __int128;
using LL = long long;
using LD = long double;
using ULL = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using PLD = pair<LD, LD>;

const int N = 1e5 + 10, MOD = 998244353;
const int INF = 1e9;
const LL LL_INF = 2e18;
const LD EPS = 1e-8;
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

bool cmp(LD a, LD b) {
    if (fabs(a - b) < EPS) return 1;
    return 0;
}

LL qpow(LL a, LL b) {
    LL ans = 1;
    a %= MOD;
    while (b) {
        if (b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

struct SCC {
    // 原图是0-based并且dag 也是0-based!!!
    int n;
    vector<vector<int>> g;
    vector<int> dfn, low;
    vector<int> stk;
    vector<bool> in_stk;
    int timer;

    int scc_cnt;
    vector<int> scc_id;
    vector<vector<int>> cont;
    vector<vector<int>> dag;

    SCC(int n) : n(n), g(n), dfn(n, -1), low(n, 0),
                 in_stk(n, 0), timer(0), scc_cnt(0), scc_id(n, -1) {
    }

    void add(int u, int v) {
        g[u].push_back(v);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = timer++;
        stk.push_back(u);
        in_stk[u] = true;
        for (int v : g[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            vector<int> comp;
            while (true) {
                int x = stk.back();
                stk.pop_back();
                in_stk[x] = false;
                scc_id[x] = scc_cnt;
                comp.push_back(x);
                if (x == u) break;
            }
            cont.push_back(move(comp));
            scc_cnt++;
        }
    }

    int build() {
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) tarjan(i);
        }
        dag.assign(scc_cnt, {});
        vector<set<int>> tmp(scc_cnt);
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
                int su = scc_id[u], sv = scc_id[v];
                if (su != sv && !tmp[su].count(sv)) {
                    tmp[su].insert(sv);
                    dag[su].push_back(sv);
                }
            }
        }
        return scc_cnt;
    }

    vector<int> top() {
        vector<int> order(scc_cnt);
        for (int i = 0; i < scc_cnt; ++i) order[i] = scc_cnt - 1 - i;
        return order;
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