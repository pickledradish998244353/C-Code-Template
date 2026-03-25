#include <bits/stdc++.h>

#define x first
#define y second
#define all(x) x.begin(), x.end()

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

struct Hash {
    vector<int> h, p;
    int B = 131;
    Hash (const string &s) {
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

struct Fenwick {
    int n;
    vector<LL> tr;

    void init(int _n) {
        n = _n;
        tr.assign(_n, 0);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int u, LL x) {
        for (int i = u; i <= n; i += lowbit(i)) tr[i] += x;
    }

    LL query(int u) {
        LL ans = 0;
        for (int i = u; i; i -= lowbit(i)) ans += tr[i];
        return ans;
    }

    LL query(int a, int b) {
        if (a > b) return 0;
        return query(b) - query(a - 1);
    }

    LL kth(LL k) {
        int x = 0;
        for (int p = 1 << 19; p; p >>= 1) {
            if (x + p <= n && tr[x + p] < k) {
                k -= tr[x + p];
                x += p;
            }
        }
        return x + 1;
    }
};

void solve() {
#ifdef LOCAL
    cout << flush;
#endif
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T--) solve();
    cout << fixed << setprecision(15);

    return 0;
}