
#include <bits/stdc++.h>

#define x first
#define y second
#define all(x) x.begin(), x.end()
#define pop_cnt(x) __builtin_popcountll((unsigned long long)(x))
#define b32(x) ((x) == 0 ? 0 : 32 - __builtin_clz((unsigned int)(x)))
#define b64(x) ((x) == 0 ? 0 : 64 - __builtin_clzll((unsigned long long)(x)))

using namespace std;
using i128 = __int128;
using u128 = unsigned __int128;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;

const int N = 2e5 + 10, MOD = 998244353;
const int inf = 1e9;
const ll ll_inf = 2e18;
const ld eps = 1e-11;
const int dx4[] = {-1, 0, 1, 0}, dy4[] = {0, 1, 0, -1};
// const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};
// const int hx[] = {-2, -2, -1, -1, 1, 1, 2, 2}, hy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

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

template <class T, class... Args>
auto vec(size_t n, Args... args) {
    if constexpr (sizeof...(args) == 0) return vector<T>(n);
    else return vector(n, vec<T>(args...));
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

struct Hash {
    vector<ll> h1, h2, p1, p2;
    static const int B1 = 131, B2 = 13331;
    static const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;

    Hash(const string& s) {
        int n = s.size();
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            p1[i + 1] = p1[i] * B1 % MOD1;
            p2[i + 1] = p2[i] * B2 % MOD2;
            h1[i + 1] = (h1[i] * B1 + s[i]) % MOD1;
            h2[i + 1] = (h2[i] * B2 + s[i]) % MOD2;
        }
    }

    // 给定字符串是 0-base，get 传入 1-base 的闭区间 [l, r]
    pll get(int l, int r) {
        ll v1 = (h1[r] - h1[l - 1] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
        ll v2 = (h2[r] - h2[l - 1] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {v1, v2};
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