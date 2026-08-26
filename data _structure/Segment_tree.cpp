#include <bits/stdc++.h>

#define x first
#define y second
#define all(x) x.begin(), x.end()
#define vec1(T, name, n, val) vector<T> name(n, val)
#define vec2(T, name, n, m, val) vector<vector<T>> name(n, vector<T>(m, val))
#define vec3(T, name, n, m, k, val) vector<vector<vector<T>>> name(n, vector<vector<T>>(m, vector<T>(k, val)))
#define vec4(T, name, n, m, k, p, val) vector<vector<vector<vector<T>>>> name((n), vector<vector<vector<T>>>((m), vector<vector<T>>((k), vector<T>((p), (val)))))
#define pop_cnt(x) __builtin_popcountll((unsigned long long)(x))

using namespace std;
using i128 = __int128;
using u128 = unsigned __int128;
using ll = long long;
using LD = long double;
using ULL = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using PLD = pair<LD, LD>;

const int N = 1e5 + 10, MOD = 998244353;
const int INF = 1e9;
const ll LL_INF = 2e18;
const LD EPS = 1e-11;
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
auto make_vec(size_t n) {
    return vector<T>(n);
}

template <class T, class... Args>
auto make_vec(size_t n, Args... args) {
    return vector<decltype(make_vec<T>(args...))>(n, make_vec<T>(args...));
}

bool cmp(LD a, LD b) {
    if (fabs(a - b) < EPS) return 1;
    return 0;
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
        ll sm, mx, tag;
        Node() : l(0), r(0), sm(0), mx(0), tag(0) {
        }
    };

    int n;
    vector<Node> tr;

    void pushup(int u) {
        tr[u].sm = tr[u << 1].sm + tr[u << 1 | 1].sm;
        tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
    }
    void apply(int u, ll v) {
        tr[u].sm += (ll)(tr[u].r - tr[u].l + 1) * v;
        tr[u].mx += v;
        tr[u].tag += v;
    }
    void pushdown(int u) {
        if (!tr[u].tag) return;
        apply(u << 1, tr[u].tag);
        apply(u << 1 | 1, tr[u].tag);
        tr[u].tag = 0;
    }

    void build(int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    void build(int u, int l, int r, vector<ll>& a) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            tr[u].sm = tr[u].mx = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    void add(int u, int ql, int qr, ll v) {
        if (tr[u].l >= ql && tr[u].r <= qr) {
            apply(u, v);
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (ql <= mid) add(u << 1, ql, qr, v);
        if (qr > mid) add(u << 1 | 1, ql, qr, v);
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
            tr[u].sm = v;
            tr[u].mx = v;
            tr[u].tag = 0;
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
        build(1, 1, n); // 只设置 l, r，其余保持 0
    }
    void init(int _n, vector<ll>& a) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n, a);
    }

    void assign(int pos, ll v) {
        assign(1, pos, v);
    }
    void add(int l, int r, ll v) {
        add(1, l, r, v);
    }
    ll query(int l, int r) {
        return query(1, l, r);
    }
    ll query_mx(int l, int r) {
        return query_mx(1, l, r);
    }
    ll query_mx() {
        return tr[1].mx;
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

struct T {
    int n;
    vector<int> tr;

    T() : n(0) {
    }

    T(int n_) {
        init(n_);
    }

    void init(int n_) {
        this->n = n_;
        tr.assign(4 * n_ + 1, 0); // 使用 assign 重置大小并清零
    }

    void update(int p, int val) {
        if (n == 0) return;
        update(1, 1, n, p, val);
    }

    void update(int u, int l, int r, int p, int val) {
        if (l == r) {
            tr[u] = max(tr[u], val);
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) update(u << 1, l, mid, p, val);
        else update(u << 1 | 1, mid + 1, r, p, val);
        tr[u] = max(tr[u << 1], tr[u << 1 | 1]);
    }

    int query(int ql, int qr) {
        if (n == 0 || ql > qr) return 0;
        return query(1, 1, n, ql, qr);
    }

    int query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u];
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid) res = max(res, query(u << 1, l, mid, ql, qr));
        if (qr > mid) res = max(res, query(u << 1 | 1, mid + 1, r, ql, qr));
        return res;
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