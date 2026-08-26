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
using ll = long long;
using LD = long double;
using ULL = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using PLD = pair<LD, LD>;

const int N = 1e5 + 10, MOD = 998244353;
const int INF = 1e9;
const ll LL_INF = 2e18;
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

struct FHQ {
    using ll = long long;

    struct Node {
        int l = 0, r = 0;
        int sz = 0, cnt = 0;
        unsigned pri = 0;
        ll v = 0;

        void init(ll _v, unsigned _pri) {
            l = r = 0;
            sz = cnt = 1;
            pri = _pri;
            v = _v;
        }
    };

    int root = 0, idx = 0;
    vector<Node> tr;
    vector<int> gc;
    mt19937 rng;

    FHQ(int max_node = 0)
        : tr(max_node + 5),
          rng((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {
    }

    void expand_if_needed() {
        if (idx + 1 >= (int)tr.size()) {
            tr.resize((int)tr.size() * 2 + 5);
        }
    }

    int new_node(ll v) {
        int u;
        if (!gc.empty()) {
            u = gc.back();
            gc.pop_back();
        }
        else {
            expand_if_needed();
            u = ++idx;
        }
        tr[u].init(v, rng());
        return u;
    }

    void recycle(int u) {
        if (!u) return;
        tr[u] = Node();
        gc.push_back(u);
    }

    void pushup(int u) {
        if (!u) return;
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;
    }

    // 分裂成:
    // x: 所有 key < v
    // y: 所有 key >= v
    void splitLess(int u, ll v, int& x, int& y) {
        if (!u) {
            x = y = 0;
            return;
        }
        if (tr[u].v < v) {
            x = u;
            splitLess(tr[u].r, v, tr[u].r, y);
            pushup(u);
        }
        else {
            y = u;
            splitLess(tr[u].l, v, x, tr[u].l);
            pushup(u);
        }
    }

    // 分裂成:
    // x: 所有 key <= v
    // y: 所有 key > v
    void splitLE(int u, ll v, int& x, int& y) {
        if (!u) {
            x = y = 0;
            return;
        }
        if (tr[u].v <= v) {
            x = u;
            splitLE(tr[u].r, v, tr[u].r, y);
            pushup(u);
        }
        else {
            y = u;
            splitLE(tr[u].l, v, x, tr[u].l);
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

    // 插入一个 val
    void insert(ll val) {
        int a, b, c;
        splitLess(root, val, a, b); // a < val, b >= val
        splitLE(b, val, b, c);      // b == val, c > val

        if (b) {
            tr[b].cnt++;
            pushup(b);
        }
        else {
            b = new_node(val);
        }

        root = merge(a, merge(b, c));
    }

    // 删除一个 val（如果存在）
    void remove(ll val) {
        int a, b, c;
        splitLess(root, val, a, b); // a < val, b >= val
        splitLE(b, val, b, c);      // b == val, c > val

        if (b) {
            if (tr[b].cnt > 1) {
                tr[b].cnt--;
                pushup(b);
            }
            else {
                int t = merge(tr[b].l, tr[b].r);
                recycle(b);
                b = t;
            }
        }

        root = merge(a, merge(b, c));
    }

    // 返回 val 的出现次数
    int count(ll val) {
        int a, b, c;
        splitLess(root, val, a, b);
        splitLE(b, val, b, c);

        int res = b ? tr[b].cnt : 0;
        root = merge(a, merge(b, c));
        return res;
    }

    // 是否存在 val
    bool find(ll val) {
        int a, b, c;
        splitLess(root, val, a, b);
        splitLE(b, val, b, c);

        bool res = (b != 0);
        root = merge(a, merge(b, c));
        return res;
    }

    // 总元素个数（包含重复）
    int size() const {
        return tr[root].sz;
    }

    bool empty() const {
        return root == 0;
    }

    // 1-based 排名：
    // 返回 1 + #(元素 < val)
    // 也就是 val 如果插进去，会在第几个位置
    int get_rank(ll val) {
        int a, b;
        splitLess(root, val, a, b);
        int res = tr[a].sz + 1;
        root = merge(a, b);
        return res;
    }

    // 1-based 第 k 小
    // 越界返回 -1
    ll get_k(int k) {
        if (k < 1 || k > size()) return -1;

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

    // 1-based 第 k 小所在节点编号
    // 越界返回 0
    int get_k_ptr(int k) {
        if (k < 1 || k > size()) return 0;

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
        return 0;
    }

    // 严格前驱：< val 的最大值
    // 不存在返回 -1
    ll get_pre(ll val) {
        int a, b;
        splitLess(root, val, a, b); // a < val, b >= val

        if (!a) {
            root = merge(a, b);
            return -1;
        }

        int u = a;
        while (tr[u].r) u = tr[u].r;
        ll res = tr[u].v;

        root = merge(a, b);
        return res;
    }

    // 严格后继：> val 的最小值
    // 不存在返回 -1
    ll get_nxt(ll val) {
        int a, b;
        splitLE(root, val, a, b); // a <= val, b > val

        if (!b) {
            root = merge(a, b);
            return -1;
        }

        int u = b;
        while (tr[u].l) u = tr[u].l;
        ll res = tr[u].v;

        root = merge(a, b);
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