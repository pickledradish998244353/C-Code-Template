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

const int N = 2e5 + 10, MOD = 998244353;
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

bool cmp(LD a, LD b) {
    if (fabs(a - b) < EPS) return 1;
    return 0;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<LL>> a(n + 1, vector<LL>(m + 1, 0));
    vec3(LL, f, n + 1, m + 1, 2, -LL_INF);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    f[1][1][0] = f[1][1][1] = a[1][1];
    function<LL(int, int, int)> dfs = [&](int x, int y, int flg) {
        if (x < 1 || x > n || y < 1 || y > m) return -LL_INF;
        if (f[x][y][flg] != -LL_INF) return f[x][y][flg];
        if (flg) {
            f[x][y][flg] = max({dfs(x + 1, y, flg), dfs(x, y - 1, flg), dfs(x, y - 1, flg ^ 1)}) + a[x][y];
        }
        else {
            f[x][y][flg] = max({dfs(x - 1, y, flg), dfs(x, y - 1, flg), dfs(x, y - 1, flg ^ 1)}) + a[x][y];
        }

        return f[x][y][flg];
    };

    cout << dfs(n, m, 0) << '\n';

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