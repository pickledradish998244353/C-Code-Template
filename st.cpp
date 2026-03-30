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

struct ST {
    const int N = 30;
    int n;
    int flg;
    vector<LL> lg;
    vector<vector<LL>> st;

    ST(int _n, int _flg, vector<LL>& a) : n(_n), lg(_n + 1), flg(_flg), st(_n + 1, vector<LL>(N)) {
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < n; ++i) {
            flg ? fill(all(st[i]), -LL_INF) : fill(all(st[i]), LL_INF);
        }
        for (int i = 0; i < n; ++i) st[i][0] = a[i];
        for (int k = 1; k < N; ++k) {
            for (int i = 0; i + (1 << k) - 1 < n; ++i) {
                if (flg) {
                    st[i][k] = max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
                }
                else {
                    st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
                }
            }
        }
    }

    LL query(int l, int r) {
        if (l > r) return (flg ? -LL_INF : LL_INF);
        int k = r - l + 1;
        k = lg[k];
        if (flg) {
            return max(st[l][k], st[r - (1 << k) + 1][k]);
        }
        else {
            return min(st[l][k], st[r - (1 << k) + 1][k]);
        }
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