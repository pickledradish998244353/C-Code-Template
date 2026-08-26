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
const int INF = 1e9;
const ll LL_INF = 2e18;
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

struct Seg {
    struct Node {
        int l, r;
        ll sm, mx, mn;
        ll mul, add; // 懒标记：x = x * mul + add
        Node() : l(0), r(0), sm(0), mx(0), mn(0), mul(1), add(0) {
        }
    };

    int n;
    vector<Node> tr;

    void pushup(int u) {
        tr[u].sm = tr[u << 1].sm + tr[u << 1 | 1].sm;
        tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
        tr[u].mn = min(tr[u << 1].mn, tr[u << 1 | 1].mn);
    }

    // 对节点 u 整体施加变换：x = x * mul + add
    void apply(int u, ll mul, ll add) {
        int len = tr[u].r - tr[u].l + 1;

        tr[u].sm = tr[u].sm * mul + (ll)len * add;

        ll old_mx = tr[u].mx;
        ll old_mn = tr[u].mn;
        if (mul >= 0) {
            tr[u].mx = old_mx * mul + add;
            tr[u].mn = old_mn * mul + add;
        }
        else {
            tr[u].mx = old_mn * mul + add;
            tr[u].mn = old_mx * mul + add;
        }

        tr[u].mul = tr[u].mul * mul;
        tr[u].add = tr[u].add * mul + add;
    }

    void pushdown(int u) {
        if (tr[u].mul == 1 && tr[u].add == 0) return;
        apply(u << 1, tr[u].mul, tr[u].add);
        apply(u << 1 | 1, tr[u].mul, tr[u].add);
        tr[u].mul = 1;
        tr[u].add = 0;
    }

    void build(int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        tr[u].mul = 1;
        tr[u].add = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    void build(int u, int l, int r, vector<ll>& a) {
        tr[u].l = l;
        tr[u].r = r;
        tr[u].mul = 1;
        tr[u].add = 0;
        if (l == r) {
            tr[u].sm = tr[u].mx = tr[u].mn = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    void add(int u, int ql, int qr, ll v) {
        if (tr[u].l >= ql && tr[u].r <= qr) {
            apply(u, 1, v);
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (ql <= mid) add(u << 1, ql, qr, v);
        if (qr > mid) add(u << 1 | 1, ql, qr, v);
        pushup(u);
    }

    void mul(int u, int ql, int qr, ll v) {
        if (tr[u].l >= ql && tr[u].r <= qr) {
            apply(u, v, 0);
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (ql <= mid) mul(u << 1, ql, qr, v);
        if (qr > mid) mul(u << 1 | 1, ql, qr, v);
        pushup(u);
    }

    ll query(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].sm;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        ll res = 0;
        if (ql <= mid) res += query(u << 1, ql, qr);
        if (qr > mid) res += query(u << 1 | 1, ql, qr);
        return res;
    }

    ll query_mx(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].mx;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        ll res = LLONG_MIN;
        if (ql <= mid) res = max(res, query_mx(u << 1, ql, qr));
        if (qr > mid) res = max(res, query_mx(u << 1 | 1, ql, qr));
        return res;
    }

    ll query_mn(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].mn;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        ll res = LLONG_MAX;
        if (ql <= mid) res = min(res, query_mn(u << 1, ql, qr));
        if (qr > mid) res = min(res, query_mn(u << 1 | 1, ql, qr));
        return res;
    }

    int firstGE(int u, ll val) {
        if (tr[u].mx < val) return tr[u].r + 1;
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushdown(u);
        if (tr[u << 1].mx >= val) return firstGE(u << 1, val);
        return firstGE(u << 1 | 1, val);
    }

    int firstGT(int u, ll val) {
        if (tr[u].mx <= val) return tr[u].r + 1;
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushdown(u);
        if (tr[u << 1].mx > val) return firstGT(u << 1, val);
        return firstGT(u << 1 | 1, val);
    }

    void assign(int u, int pos, ll v) {
        if (tr[u].l == tr[u].r) {
            tr[u].sm = tr[u].mx = tr[u].mn = v;
            tr[u].mul = 1;
            tr[u].add = 0;
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (pos <= mid) assign(u << 1, pos, v);
        else assign(u << 1 | 1, pos, v);
        pushup(u);
    }

    Seg() : n(0) {
    }
    Seg(int _n) {
        init(_n);
    }
    Seg(int _n, vector<ll>& a) {
        init(_n, a);
    }

    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n); // 只设置 l, r，其余保持 0；mul=1, add=0
    }

    void init(int _n, vector<ll>& a) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n, a); // a 按 1 下标传入
    }

    void assign(int pos, ll v) {
        assign(1, pos, v);
    }
    void add(int l, int r, ll v) {
        add(1, l, r, v);
    }
    void mul(int l, int r, ll v) {
        mul(1, l, r, v);
    }
    ll query(int l, int r) {
        return query(1, l, r);
    }
    ll query_mx(int l, int r) {
        return query_mx(1, l, r);
    }
    ll query_mn(int l, int r) {
        return query_mn(1, l, r);
    }
    ll query_mx() {
        return tr[1].mx;
    }
    ll query_mn() {
        return tr[1].mn;
    }
    ll query_sum() {
        return tr[1].sm;
    }
    int lower_bound(ll val) {
        return firstGE(1, val);
    }
    int upper_bound(ll val) {
        return firstGT(1, val);
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