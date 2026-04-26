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

istream &operator>>(istream &is, i128 &val) {
    string str;
    is >> str;
    val = 0;
    bool flag = false;
    if (str[0] == '-') flag = true, str = str.substr(1);
    for (char &c: str) val = val * 10 + c - '0';
    if (flag) val = -val;
    return is;
}

ostream &operator<<(ostream &os, i128 val) {
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

struct Comb {
    int n;
    vector<LL> fact, infact;
    Comb(int _n) : n(_n + 1), fact(_n + 1), infact(_n + 1) {
        fact[0] = 1, infact[0] = 1;
        for (LL i = 1; i < _n; ++i) {
            fact[i] = fact[i - 1] * i % MOD;
            infact[i] = qpow(fact[i], MOD - 2) % MOD;
        }
    };

    LL C(LL a, LL b) {
        if (a < b || b < 0) return 0;
        return fact[a] % MOD * infact[b] % MOD * infact[a - b] % MOD;
    }

    LL lucas(LL a, LL b) {
        if (a < MOD && b < MOD) return C(a, b);
        return lucas(a / MOD, b / MOD) * lucas(a % MOD, b % MOD) % MOD;
    }
};

LL gcd(LL x, LL y) {
    return y ? gcd(y, x % y) : x;
}

void solve() {
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