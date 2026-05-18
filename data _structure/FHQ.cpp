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

struct T {
    struct Node {
        int l, r;
        int sz, cnt;
        unsigned pri;
        LL v;
        void init(LL _v, unsigned _pri) {
            l = r = 0;
            sz = cnt = 1;
            pri = _pri;
            v = _v;
        }
    };

    int root, idx;
    vector<Node> tr;
    vector<int> q;
    mt19937 rng;

    T(int _n) : root(0), idx(0), tr(_n + 10), rng(chrono::steady_clock::now().time_since_epoch().count()) {
    }

    int get_node(LL v) {
        int u;
        if (!q.empty()) {
            u = q.back();
            q.pop_back();
        }
        else {
            u = ++idx;
        }
        tr[u].init(v, rng());
        return u;
    }

    void del(int u) {
        tr[u].l = tr[u].r = tr[u].sz = tr[u].cnt = 0;
        tr[u].pri = 0;
        tr[u].v = 0;
        q.push_back(u);
    }

    void pushup(int u) {
        if (!u) return;
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;
    }

    void split(int u, LL v, int& x, int& y) {
        if (!u) {
            x = y = 0;
            return;
        }
        if (tr[u].v <= v) {
            x = u;
            split(tr[u].r, v, tr[u].r, y);
            pushup(u);
        }
        else {
            y = u;
            split(tr[u].l, v, x, tr[u].l);
            pushup(u);
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (tr[x].pri < tr[y].pri) {
            tr[x].r = merge(tr[x].r, y);
            pushup(x);
            return x;
        }
        else {
            tr[y].l = merge(x, tr[y].l);
            pushup(y);
            return y;
        }
    }

    void insert(LL val) {
        int a, b, c;
        split(root, val, a, c);
        split(a, val - 1, a, b);
        if (b) {
            tr[b].cnt++;
            pushup(b);
        }
        else {
            b = get_node(val);
        }
        root = merge(merge(a, b), c);
    }

    void remove(LL val) {
        int a, b, c;
        split(root, val, a, c);
        split(a, val - 1, a, b);
        if (b) {
            if (tr[b].cnt > 1) {
                tr[b].cnt--;
                pushup(b);
            }
            else {
                del(b);
                b = 0;
            }
        }
        root = merge(merge(a, b), c);
    }

    int get_rank(LL val) {
        int a, b;
        split(root, val - 1, a, b);
        int res = tr[a].sz;
        root = merge(a, b);
        return res;
    }

    LL get_k(int k) {
        k++;
        int u = root;
        while (u) {
            int lsz = tr[tr[u].l].sz;
            if (k <= lsz) {
                u = tr[u].l;
            }
            else if (k <= lsz + tr[u].cnt) {
                return tr[u].v;
            }
            else {
                k -= lsz + tr[u].cnt;
                u = tr[u].r;
            }
        }
        return -1;
    }

    int get_k_ptr(int k) {
        k++;
        int u = root;
        while (u) {
            int lsz = tr[tr[u].l].sz;
            if (k <= lsz) {
                u = tr[u].l;
            }
            else if (k <= lsz + tr[u].cnt) {
                return u;
            }
            else {
                k -= lsz + tr[u].cnt;
                u = tr[u].r;
            }
        }
        return -1;
    }

    LL get_pre(LL val) {
        int a, b;
        split(root, val - 1, a, b);
        int u = a;
        if (!u) {
            root = merge(a, b);
            return -1;
        }
        while (tr[u].r) u = tr[u].r;
        LL res = tr[u].v;
        root = merge(a, b);
        return res;
    }

    LL get_nxt(LL val) {
        int a, b;
        split(root, val, a, b);
        int u = b;
        if (!u) {
            root = merge(a, b);
            return -1;
        }
        while (tr[u].l) u = tr[u].l;
        LL res = tr[u].v;
        root = merge(a, b);
        return res;
    }

    void find(LL val) {
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