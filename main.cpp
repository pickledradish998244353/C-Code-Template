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
const LL LL_INF = 1e18;
const LD EPS = 1e-8;
const int dx4[] = {-1, 0, 1, 0}, dy4[] = {0, 1, 0, -1};
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

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

struct Hash {
    vector<int> h, p;
    int B = 131;
    Hash(const string& s) {
        int n = s.size();
        h.resize(n + 1, 0);
        p.resize(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            p[i + 1] = p[i] * B % MOD;
            h[i + 1] = (h[i] * B + s[i]) % MOD;
        }
    }

    LL get(int l, int r) {
        LL v = h[r] - h[l - 1] * p[r - l + 1] % MOD;
        v = (v % MOD + MOD) % MOD;
        return v;
    }
};

void solve() {
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<int> d1(n + 1, -1), d2(n + 1, -1);
    auto bfs = [&](int st, vector<int>& d) -> void {
        d[st] = 0;
        queue<int> q;
        q.push(st);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    };

    bfs(a, d1), bfs(b, d2);

    bool ok = 0;
    for (int i = 1; i <= n; ++i) {
        if (g[i].size() == 1) {
            // 因为小红先手可以等于
            if (2 * d1[i] <= d2[i]) ok |= 1;
        }
    }

    if (ok) cout << "red" << '\n';
    else cout << "purple" << '\n';

/**/ #ifdef LOCAL
    cout << flush;
/**/ #endif
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
    cout << fixed << setprecision(15);

    return 0;
}