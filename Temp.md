[TOC]

## 输入输出

### cin读取一整行

先忽略换行

``` cpp
    cin >> n;
    cin.ignore();
```

然后再`getline`, 下面是示例

```cpp
int n;
    cin >> n;
    cin.ignore();
    vector<vector<string>> a(n);
    struct F {
        int id;
        int cnt;
    };
    vector<string> ans(n);
    map<string, vector<F>> mp;

    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        stringstream ss(s);
        string tmp;

        string it;
        while (ss >> tmp) {
            a[i].push_back(tmp);
            it += tmp[0];
        }
        mp[it].push_back({i, 0});
    }

```

**交互题需要输出$endl$**

### $int128$输入输出

```cpp
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
```

### 四连通, 八连通, 马连通

```cpp
const int dx4[] = {-1, 0, 1, 0}, dy4[] = {0, 1, 0, -1};
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int hx[] = {-2, -2, -1, -1, 1, 1, 2, 2}, hy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
```

### 创建多维数组

```cpp
template <class T>
auto make_vec(size_t n) {
    return vector<T>(n);
}

template <class T, class... Args>
auto make_vec(size_t n, Args... args) {
    return vector<decltype(make_vec<T>(args...))>(n, make_vec<T>(args...));
}
```

### 输入输出火车头

```cpp
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
using LL = long long;
using LD = long double;
using ULL = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using PLD = pair<LD, LD>;

const int N = 1e5 + 10, MOD = 998244353;
const int INF = 1e9;
const LL LL_INF = 2e18;
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
```



## 位运算相关

```cpp
#define pop_cnt(x) __builtin_popcountll((unsigned long long)(x))
```

### 计算最低位$1$的位置

```cpp
__builtin_ctz(x)      // count trailing zeros
__builtin_ctzll(x)
```

### 快速求$\log_2 ^ n$

```cpp
int k = 31 - __builtin_clz(x);      // 32位
int k = 63 - __builtin_clzll(x);    // 64位
```

### 子集枚举

```cpp
for (int s = mask; s; s = (s - 1) & mask)
```

### 取最高位$1$

```cpp
int highest = 1 << (31 - __builtin_clz(x));
```

## 数据结构

### $ST$表

```cpp
struct ST {
    const int N = 30;
    int n;
    int flg;
    vector<LL> lg;
    vector<vector<LL>> st;

    ST(int _n, int _flg, const vector<LL>& a) : n(_n), lg(_n + 1), flg(_flg), st(N, vector<LL>(_n + 1)) {
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        if (flg) {
            for (int k = 1; k < N; ++k) {
                int len = 1 << (k - 1);
                for (int i = 0; i + (1 << k) - 1 < n; ++i) {
                    st[k][i] = max(st[k - 1][i], st[k - 1][i + len]);
                }
            }
        }
        else {
            for (int k = 1; k < N; ++k) {
                int len = 1 << (k - 1);
                for (int i = 0; i + (1 << k) - 1 < n; ++i) {
                    st[k][i] = min(st[k - 1][i], st[k - 1][i + len]);
                }
            }
        }
    }

    LL query(int l, int r) {
        if (l > r) return (flg ? -LL_INF : LL_INF);
        int k = lg[r - l + 1];
        if (flg) {
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        }
        else {
            return min(st[k][l], st[k][r - (1 << k) + 1]);
        }
    }
};
```



### 并查集

```cpp
struct EDSU {
    int n;
    vector<int> p;
    vector<int> sz;
    EDSU(int _n) : n(_n), p(_n), sz(_n) {
        for (int i = 0; i < _n; ++i) {
            p[i] = i;
            sz[i] = 1;
        }
    };

    int find(int x) {
        if (p[x] != x) return p[x] = find(p[x]);
        return p[x];
    }

    void merge(int x, int y) {
        int fa1 = find(x), fa2 = find(y);
        if (fa1 == fa2) return;
        p[fa2] = fa1;
        sz[fa1] += sz[fa2];
    }
};
```

### 单调栈建笛卡尔树

```cpp
    int n;
    cin >> n;
    vector<int> ls(n + 1), rs(n + 1);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    stack<int> stk;
    for (int i = 1; i <= n; ++i) {
        int lst = 0;
        while (stk.size() && a[stk.top()] > a[i]) lst = stk.top(), stk.pop();
        if (stk.size()) rs[stk.top()] = i;
        ls[i] = lst;
        stk.push(i);
    }
```

### 常规树状数组

```cpp
struct Fenwick {
    int n;
    vector<LL> tr;

    Fenwick() : n(0) {
    }

    // 带参构造:
    Fenwick(int _n) {
        init(_n);
    }

    // 初始化函数: 支持延迟初始化
    void init(int _n) {
        n = _n + 1;
        tr.assign(n, 0);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int u, LL x) {
        if (u <= 0) return;
        for (int i = u; i < n; i += lowbit(i)) tr[i] += x;
    }

    LL query(int u) {
        u = min(u, n - 1);
        LL ans = 0;
        for (int i = u; i; i -= lowbit(i)) ans += tr[i];
        return ans;
    }

    LL query(int a, int b) {
        if (a > b) return 0;
        return query(b) - query(a - 1);
    }

    // 第k个1在哪
    LL kth(LL k) {
        int lg = 31 - __builtin_clz(n);
        int up = 1 << lg;
        int x = 0;
        for (int p = up; p; p >>= 1) {
            if (x + p < n && tr[x + p] < k) {
                k -= tr[x + p];
                x += p;
            }
        }
        return x + 1;
    }
};
```

### 最小值树状数组

```cpp
struct MinFenwick {
    int n;
    vector<LL> tr;

    MinFenwick(int _n) : n(_n + 1), tr(_n + 1, LL_INF) {
    }

    int lowbit(int x) {
        return x & -x;
    }

    void update(int u, LL x) {
        if (u <= 0) return;
        for (int i = u; i < n; i += lowbit(i))
            tr[i] = min(tr[i], x);
    }

    LL query(int u) {
        u = min(u, n - 1);
        LL ans = LL_INF;
        for (int i = u; i; i -= lowbit(i))
            ans = min(ans, tr[i]);
        return ans;
    }
};
```



### $FHQ-Treap$

```cpp
struct FHQ {
    using LL = long long;

    struct Node {
        int l = 0, r = 0;
        int sz = 0, cnt = 0;
        unsigned pri = 0;
        LL v = 0;

        void init(LL _v, unsigned _pri) {
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

    int new_node(LL v) {
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
    void splitLess(int u, LL v, int& x, int& y) {
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
    void splitLE(int u, LL v, int& x, int& y) {
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
    void insert(LL val) {
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
    void remove(LL val) {
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
    int count(LL val) {
        int a, b, c;
        splitLess(root, val, a, b);
        splitLE(b, val, b, c);

        int res = b ? tr[b].cnt : 0;
        root = merge(a, merge(b, c));
        return res;
    }

    // 是否存在 val
    bool find(LL val) {
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
    int get_rank(LL val) {
        int a, b;
        splitLess(root, val, a, b);
        int res = tr[a].sz + 1;
        root = merge(a, b);
        return res;
    }

    // 1-based 第 k 小
    // 越界返回 -1
    LL get_k(int k) {
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
    LL get_pre(LL val) {
        int a, b;
        splitLess(root, val, a, b); // a < val, b >= val

        if (!a) {
            root = merge(a, b);
            return -1;
        }

        int u = a;
        while (tr[u].r) u = tr[u].r;
        LL res = tr[u].v;

        root = merge(a, b);
        return res;
    }

    // 严格后继：> val 的最小值
    // 不存在返回 -1
    LL get_nxt(LL val) {
        int a, b;
        splitLE(root, val, a, b); // a <= val, b > val

        if (!b) {
            root = merge(a, b);
            return -1;
        }

        int u = b;
        while (tr[u].l) u = tr[u].l;
        LL res = tr[u].v;

        root = merge(a, b);
        return res;
    }
};
```

### 区间加, 区间和, 最大值线段树

```cpp
struct Seg {
    struct Node {
        int l, r;
        LL sm, mx, tag;
        Node() : l(0), r(0), sm(0), mx(0), tag(0) {
        }
    };

    int n;
    vector<Node> tr;

    void pushup(int u) {
        tr[u].sm = tr[u << 1].sm + tr[u << 1 | 1].sm;
        tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
    }
    void apply(int u, LL v) {
        tr[u].sm += (LL)(tr[u].r - tr[u].l + 1) * v;
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
    void build(int u, int l, int r, vector<LL>& a) {
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

    void add(int u, int ql, int qr, LL v) {
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

    LL query(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].sm;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        LL res = 0;
        if (ql <= mid) res += query(u << 1, ql, qr);
        if (qr > mid) res += query(u << 1 | 1, ql, qr);
        return res;
    }
    LL query_mx(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].mx;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        LL res = LLONG_MIN;
        if (ql <= mid) res = max(res, query_mx(u << 1, ql, qr));
        if (qr > mid) res = max(res, query_mx(u << 1 | 1, ql, qr));
        return res;
    }
    int firstGE(int u, LL val) {
        if (tr[u].mx < val) return tr[u].r + 1;
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushdown(u);
        if (tr[u << 1].mx >= val) return firstGE(u << 1, val);
        return firstGE(u << 1 | 1, val);
    }
    int firstGT(int u, LL val) {
        if (tr[u].mx <= val) return tr[u].r + 1;
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushdown(u);
        if (tr[u << 1].mx > val) return firstGT(u << 1, val);
        return firstGT(u << 1 | 1, val);
    }
    void assign(int u, int pos, LL v) {
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
    Seg(int _n, vector<LL>& a) {
        init(_n, a);
    }

    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n); // 只设置 l, r，其余保持 0
    }
    void init(int _n, vector<LL>& a) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n, a);
    }

    void assign(int pos, LL v) {
        assign(1, pos, v);
    }
    void add(int l, int r, LL v) {
        add(1, l, r, v);
    }
    LL query(int l, int r) {
        return query(1, l, r);
    }
    LL query_mx(int l, int r) {
        return query_mx(1, l, r);
    }
    LL query_mx() {
        return tr[1].mx;
    }
    LL query_sum() {
        return tr[1].sm;
    }
    int lower_bound(LL val) {
        return firstGE(1, val);
    }
    int upper_bound(LL val) {
        return firstGT(1, val);
    }
};
```

### 区间乘线段树

```cpp
struct Seg {
    struct Node {
        int l, r;
        LL sm, mx, mn;
        LL mul, add; // 懒标记：x = x * mul + add
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
    void apply(int u, LL mul, LL add) {
        int len = tr[u].r - tr[u].l + 1;

        tr[u].sm = tr[u].sm * mul + (LL)len * add;

        LL old_mx = tr[u].mx;
        LL old_mn = tr[u].mn;
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

    void build(int u, int l, int r, vector<LL>& a) {
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

    void add(int u, int ql, int qr, LL v) {
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

    void mul(int u, int ql, int qr, LL v) {
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

    LL query(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].sm;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        LL res = 0;
        if (ql <= mid) res += query(u << 1, ql, qr);
        if (qr > mid) res += query(u << 1 | 1, ql, qr);
        return res;
    }

    LL query_mx(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].mx;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        LL res = LLONG_MIN;
        if (ql <= mid) res = max(res, query_mx(u << 1, ql, qr));
        if (qr > mid) res = max(res, query_mx(u << 1 | 1, ql, qr));
        return res;
    }

    LL query_mn(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u].mn;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        LL res = LLONG_MAX;
        if (ql <= mid) res = min(res, query_mn(u << 1, ql, qr));
        if (qr > mid) res = min(res, query_mn(u << 1 | 1, ql, qr));
        return res;
    }

    int firstGE(int u, LL val) {
        if (tr[u].mx < val) return tr[u].r + 1;
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushdown(u);
        if (tr[u << 1].mx >= val) return firstGE(u << 1, val);
        return firstGE(u << 1 | 1, val);
    }

    int firstGT(int u, LL val) {
        if (tr[u].mx <= val) return tr[u].r + 1;
        if (tr[u].l == tr[u].r) return tr[u].l;
        pushdown(u);
        if (tr[u << 1].mx > val) return firstGT(u << 1, val);
        return firstGT(u << 1 | 1, val);
    }

    void assign(int u, int pos, LL v) {
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
    Seg(int _n, vector<LL>& a) {
        init(_n, a);
    }

    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n); // 只设置 l, r，其余保持 0；mul=1, add=0
    }

    void init(int _n, vector<LL>& a) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n, a); // a 按 1 下标传入
    }

    void assign(int pos, LL v) {
        assign(1, pos, v);
    }
    void add(int l, int r, LL v) {
        add(1, l, r, v);
    }
    void mul(int l, int r, LL v) {
        mul(1, l, r, v);
    }
    LL query(int l, int r) {
        return query(1, l, r);
    }
    LL query_mx(int l, int r) {
        return query_mx(1, l, r);
    }
    LL query_mn(int l, int r) {
        return query_mn(1, l, r);
    }
    LL query_mx() {
        return tr[1].mx;
    }
    LL query_mn() {
        return tr[1].mn;
    }
    LL query_sum() {
        return tr[1].sm;
    }
    int lower_bound(LL val) {
        return firstGE(1, val);
    }
    int upper_bound(LL val) {
        return firstGT(1, val);
    }
};
```

### 最大子段和

```cpp
struct Seg {
    struct Node {
        int l, r;
        LL sm;       // 区间和
        LL mx;       // 最大子段和
        LL lmx;      // 最大前缀和
        LL rmx;      // 最大后缀和
        LL tag;      // 区间加懒标记
        Node() : l(0), r(0), sm(0), mx(0), lmx(0), rmx(0), tag(0) {
        }
    };

    int n;
    vector<Node> tr;

    void pushup(int u) {
        int lc = u << 1, rc = u << 1 | 1;
        tr[u].sm = tr[lc].sm + tr[rc].sm;
        tr[u].lmx = max(tr[lc].lmx, tr[lc].sm + tr[rc].lmx);
        tr[u].rmx = max(tr[rc].rmx, tr[rc].sm + tr[lc].rmx);
        tr[u].mx = max({tr[lc].mx, tr[rc].mx, tr[lc].rmx + tr[rc].lmx});
    }

    void apply(int u, LL v) {
        int len = tr[u].r - tr[u].l + 1;
        tr[u].mx += v;       // 单点时 mx = 该值，加 v 即可
        tr[u].lmx += v;
        tr[u].rmx += v;
        tr[u].sm += (LL)len * v;
        tr[u].tag += v;
    }

    void build(int u, int l, int r) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            tr[u].sm = tr[u].mx = tr[u].lmx = tr[u].rmx = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void build(int u, int l, int r, vector<LL>& a) {
        tr[u].l = l;
        tr[u].r = r;
        if (l == r) {
            tr[u].sm = tr[u].mx = tr[u].lmx = tr[u].rmx = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    // 单点赋值
    void assign(int u, int pos, LL v) {
        if (tr[u].l == tr[u].r) {
            tr[u].sm = tr[u].mx = tr[u].lmx = tr[u].rmx = v;
            return;
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (pos <= mid) assign(u << 1, pos, v);
        else assign(u << 1 | 1, pos, v);
        pushup(u);
    }

    // 单点加
    void add(int u, int pos, LL v) {
        if (tr[u].l == tr[u].r) {
            tr[u].sm += v;
            tr[u].mx = tr[u].lmx = tr[u].rmx = tr[u].sm;
            return;
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (pos <= mid) add(u << 1, pos, v);
        else add(u << 1 | 1, pos, v);
        pushup(u);
    }

    // 区间查询：返回一个 Node，包含 sm / mx / lmx / rmx
    Node query(int u, int ql, int qr) {
        if (tr[u].l >= ql && tr[u].r <= qr) return tr[u];
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (qr <= mid) return query(u << 1, ql, qr);
        if (ql > mid) return query(u << 1 | 1, ql, qr);
        // 两边都有交集，需要合并
        Node L = query(u << 1, ql, qr);
        Node R = query(u << 1 | 1, ql, qr);
        Node res;
        res.sm = L.sm + R.sm;
        res.lmx = max(L.lmx, L.sm + R.lmx);
        res.rmx = max(R.rmx, R.sm + L.rmx);
        res.mx = max({L.mx, R.mx, L.rmx + R.lmx});
        return res;
    }

    Seg() : n(0) {
    }
    Seg(int _n) {
        init(_n);
    }
    Seg(int _n, vector<LL>& a) {
        init(_n, a);
    }

    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n);
    }
    void init(int _n, vector<LL>& a) {
        n = _n;
        tr.assign(4 * n + 10, Node());
        build(1, 1, n, a);
    }

    void assign(int pos, LL v) {
        assign(1, pos, v);
    }
    void add(int pos, LL v) {
        add(1, pos, v);
    }

    // 查询区间最大子段和
    LL query_mx(int l, int r) {
        return query(1, l, r).mx;
    }
    // 查询全局最大子段和
    LL query_mx() {
        return tr[1].mx;
    }
    // 查询区间和
    LL query_sum(int l, int r) {
        return query(1, l, r).sm;
    }
    LL query_sum() {
        return tr[1].sm;
    }
    // 查询区间最大前缀和
    LL query_lmx(int l, int r) {
        return query(1, l, r).lmx;
    }
    // 查询区间最大后缀和
    LL query_rmx(int l, int r) {
        return query(1, l, r).rmx;
    }
};
```



### 主席树

```cpp
struct PST {
    int idx;
    vector<int> rt;
    struct Node {
        int ls, rs;
        LL sm;
        Node() : ls(0), rs(0), sm(0) {};
    };
    vector<Node> tr;

    PST(int n, int m, int q) {
        idx = 0;
        int len = max(n, q);
        rt.assign(len + 1, 0);
        tr.resize(q * 40 + 10);
    }

    int clone(int p) {
        idx++;
        tr[idx] = tr[p];
        return idx;
    }

    LL query(int u, int l, int r, int ql, int qr) {
        if (!u) return 0;
        if (l >= ql && r <= qr) return tr[u].sm;
        int mid = l + r >> 1;

        LL res = 0;
        if (ql <= mid) res += query(tr[u].ls, l, mid, ql, qr);
        if (qr > mid) res += query(tr[u].rs, mid + 1, r, ql, qr);
        return res;
    }

    int modify(int u, int l, int r, int pos, int v) {
        int nw = clone(u);
        if (l == r) {
            tr[nw].sm = v;
            return nw;
        }
        int mid = l + r >> 1;
        if (pos <= mid) tr[nw].ls = modify(tr[u].ls, l, mid, pos, v);
        if (pos > mid) tr[nw].rs = modify(tr[u].rs, mid + 1, r, pos, v);
        tr[nw].sm = tr[tr[nw].ls].sm + tr[tr[nw].rs].sm;
        return nw;
    }
};

struct KPST {
    int idx, m;
    vector<int> rt;

    struct Node {
        int ls, rs, sm;
        Node() : ls(0), rs(0), sm(0) {
        }
    };
    vector<Node> tr;

    KPST(int n, int m) {
        idx = 0;
        this->m = m;
        rt.assign(n + 1, 0);
        tr.resize((n + 5) * 40);
    }

    int clone(int p) {
        tr[++idx] = tr[p];
        return idx;
    }

    int modify(int u, int l, int r, int pos, int v) {
        int nw = clone(u);
        tr[nw].sm += v;
        if (l == r) return nw;

        int mid = (l + r) >> 1;
        if (pos <= mid) tr[nw].ls = modify(tr[u].ls, l, mid, pos, v);
        else tr[nw].rs = modify(tr[u].rs, mid + 1, r, pos, v);

        return nw;
    }

    int kth_small(int u, int v, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int cntLeft = tr[tr[v].ls].sm - tr[tr[u].ls].sm;

        if (k <= cntLeft)
            return kth_small(tr[u].ls, tr[v].ls, l, mid, k);
        else
            return kth_small(tr[u].rs, tr[v].rs, mid + 1, r, k - cntLeft);
    }

    int kth_big(int u, int v, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int cntRight = tr[tr[v].rs].sm - tr[tr[u].rs].sm;

        if (k <= cntRight)
            return kth_big(tr[u].rs, tr[v].rs, mid + 1, r, k);
        else
            return kth_big(tr[u].ls, tr[v].ls, l, mid, k - cntRight);
    }
};
```



### 吉司机线段树

```cpp
struct SegTreeBeats {
    static const LL INF = 4e18; // 保证不溢出的足够大的数

    struct Node {
        LL sum;
        LL mx1, mx2; int mxc; // 最大值，严格次大值，最大值个数
        LL mn1, mn2; int mnc; // 最小值，严格次小值，最小值个数
        LL add_tag;           // 区间加法的 lazy tag
    };

    int n;
    vector<Node> t;

    SegTreeBeats(const vector<LL>& a) {
        n = a.size() - 1; // 假设 a 的有效下标为 1~n
        t.resize(4 * n + 1);
        build(1, 1, n, a);
    }

    void push_up(int p) {
        int lc = p << 1, rc = p << 1 | 1;
        t[p].sum = t[lc].sum + t[rc].sum;

        // 维护最大值及次大值
        if (t[lc].mx1 == t[rc].mx1) {
            t[p].mx1 = t[lc].mx1;
            t[p].mxc = t[lc].mxc + t[rc].mxc;
            t[p].mx2 = max(t[lc].mx2, t[rc].mx2);
        } else if (t[lc].mx1 > t[rc].mx1) {
            t[p].mx1 = t[lc].mx1;
            t[p].mxc = t[lc].mxc;
            t[p].mx2 = max(t[lc].mx2, t[rc].mx1);
        } else {
            t[p].mx1 = t[rc].mx1;
            t[p].mxc = t[rc].mxc;
            t[p].mx2 = max(t[lc].mx1, t[rc].mx2);
        }

        // 维护最小值及次小值
        if (t[lc].mn1 == t[rc].mn1) {
            t[p].mn1 = t[lc].mn1;
            t[p].mnc = t[lc].mnc + t[rc].mnc;
            t[p].mn2 = min(t[lc].mn2, t[rc].mn2);
        } else if (t[lc].mn1 < t[rc].mn1) {
            t[p].mn1 = t[lc].mn1;
            t[p].mnc = t[lc].mnc;
            t[p].mn2 = min(t[lc].mn2, t[rc].mn1);
        } else {
            t[p].mn1 = t[rc].mn1;
            t[p].mnc = t[rc].mnc;
            t[p].mn2 = min(t[lc].mn1, t[rc].mn2);
        }
    }

    void build(int p, int l, int r, const vector<LL>& a) {
        t[p].add_tag = 0;
        if (l == r) {
            t[p].sum = t[p].mx1 = t[p].mn1 = a[l];
            t[p].mx2 = -INF; t[p].mn2 = INF;
            t[p].mxc = t[p].mnc = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        push_up(p);
    }

    // 处理区间加法
    void update_add(int p, int l, int r, LL v) {
        t[p].sum += (r - l + 1) * v;
        t[p].mx1 += v; if (t[p].mx2 != -INF) t[p].mx2 += v;
        t[p].mn1 += v; if (t[p].mn2 != INF) t[p].mn2 += v;
        t[p].add_tag += v;
    }

    // 处理区间对 v 取 min（即限制最大值）
    void update_chmin(int p, LL v) {
        if (v >= t[p].mx1) return;
        t[p].sum -= (t[p].mx1 - v) * t[p].mxc;
        if (t[p].mn1 == t[p].mx1) t[p].mn1 = v; // 如果区间只有一种值，最小值也要变
        if (t[p].mn2 == t[p].mx1) t[p].mn2 = v; // 如果次小值等于最大值，次小值也要变
        t[p].mx1 = v;
    }

    // 处理区间对 v 取 max（即提升最小值）
    void update_chmax(int p, LL v) {
        if (v <= t[p].mn1) return;
        t[p].sum += (v - t[p].mn1) * t[p].mnc;
        if (t[p].mx1 == t[p].mn1) t[p].mx1 = v; 
        if (t[p].mx2 == t[p].mn1) t[p].mx2 = v;
        t[p].mn1 = v;
    }

    void push_down(int p, int l, int r) {
        int lc = p << 1, rc = p << 1 | 1;
        int mid = (l + r) >> 1;
        
        // 1. 下传加法标记
        if (t[p].add_tag != 0) {
            update_add(lc, l, mid, t[p].add_tag);
            update_add(rc, mid + 1, r, t[p].add_tag);
            t[p].add_tag = 0;
        }
        // 2. 下传 max/min 限制 (chmin 和 chmax 标记隐式包含在父节点的 mx1 和 mn1 中)
        update_chmin(lc, t[p].mx1); update_chmax(lc, t[p].mn1);
        update_chmin(rc, t[p].mx1); update_chmax(rc, t[p].mn1);
    }

    void add(int p, int l, int r, int ql, int qr, LL v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            update_add(p, l, r, v);
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        add(p << 1, l, mid, ql, qr, v);
        add(p << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(p);
    }

    void chmin(int p, int l, int r, int ql, int qr, LL v) {
        if (qr < l || r < ql || v >= t[p].mx1) return;
        if (ql <= l && r <= qr && v > t[p].mx2) { // 剪枝条件：严格处于次大和最大之间
            update_chmin(p, v);
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        chmin(p << 1, l, mid, ql, qr, v);
        chmin(p << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(p);
    }

    void chmax(int p, int l, int r, int ql, int qr, LL v) {
        if (qr < l || r < ql || v <= t[p].mn1) return;
        if (ql <= l && r <= qr && v < t[p].mn2) { // 剪枝条件：严格处于最小和次小之间
            update_chmax(p, v);
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        chmax(p << 1, l, mid, ql, qr, v);
        chmax(p << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(p);
    }

    LL qsum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[p].sum;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        return qsum(p << 1, l, mid, ql, qr) + qsum(p << 1 | 1, mid + 1, r, ql, qr);
    }

    LL qmax(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return -INF;
        if (ql <= l && r <= qr) return t[p].mx1;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        return max(qmax(p << 1, l, mid, ql, qr), qmax(p << 1 | 1, mid + 1, r, ql, qr));
    }

    LL qmin(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return INF;
        if (ql <= l && r <= qr) return t[p].mn1;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        return min(qmin(p << 1, l, mid, ql, qr), qmin(p << 1 | 1, mid + 1, r, ql, qr));
    }

    // --------- 供外部调用的简洁接口 ---------
    void add(int l, int r, LL v)   { add(1, 1, n, l, r, v); }
    void chmin(int l, int r, LL v) { chmin(1, 1, n, l, r, v); }
    void chmax(int l, int r, LL v) { chmax(1, 1, n, l, r, v); }
    LL qsum(int l, int r)          { return qsum(1, 1, n, l, r); }
    LL qmax(int l, int r)          { return qmax(1, 1, n, l, r); }
    LL qmin(int l, int r)          { return qmin(1, 1, n, l, r); }
};
```

## 图论

### 匈牙利算法求二分图最大匹配

**搞个时间戳**, 每次需要清空$vis$

```cpp
struct Hungarian {
    int n, m;
    vector<vector<int>> g;
    vector<int> match, vis;
    int tim;

    Hungarian(const vector<vector<int>>& graph, int right_size)
        : g(graph), n((int)graph.size()), m(right_size),
          match(m, -1), vis(m, 0), tim(0) {
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            if (vis[v] == tim) continue;
            vis[v] = tim;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_match() {
        int ans = 0;
        for (int u = 0; u < n; ++u) {
            ++tim;
            if (dfs(u)) ++ans;
        }
        return ans;
    }
};
```



### $LCA$

```cpp
struct LCA {
    int n, LOG;
    vector<vector<int>> g;
    vector<vector<int>> fa;
    vector<int> depth;

    LCA(int _n) : n(_n), g(_n + 1) {
        LOG = 32 - __builtin_clz(max(1, n));
        fa.assign(n + 1, vector<int>(LOG, 0));
        depth.assign(n + 1, 0);
    }

    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int p) {
        fa[u][0] = p;
        depth[u] = depth[p] + 1;
        for (int i = 1; i < LOG; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int v : g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
    }

    void build(int root = 1) {
        depth[0] = 0;
        dfs(root, 0);
    }

    int query(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        for (int i = LOG - 1; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = fa[u][i];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }

        return fa[u][0];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }
};
```



### $SCC$强连通分量

```cpp
struct SCC {
    // 原图是0-based并且dag 也是0-based!!!
    int n;
    vector<vector<int>> g;
    vector<int> dfn, low;
    vector<int> stk;
    vector<bool> in_stk;
    int timer;

    int scc_cnt;
    vector<int> scc_id;
    vector<vector<int>> cont;
    vector<vector<int>> dag;

    SCC(int n) : n(n), g(n), dfn(n, -1), low(n, 0),
                 in_stk(n, 0), timer(0), scc_cnt(0), scc_id(n, -1) {
    }

    void add(int u, int v) {
        g[u].push_back(v);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = timer++;
        stk.push_back(u);
        in_stk[u] = true;
        for (int v : g[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            vector<int> comp;
            while (true) {
                int x = stk.back();
                stk.pop_back();
                in_stk[x] = false;
                scc_id[x] = scc_cnt;
                comp.push_back(x);
                if (x == u) break;
            }
            cont.push_back(move(comp));
            scc_cnt++;
        }
    }

    int build() {
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) tarjan(i);
        }
        dag.assign(scc_cnt, {});
        vector<set<int>> tmp(scc_cnt);
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
                int su = scc_id[u], sv = scc_id[v];
                if (su != sv && !tmp[su].count(sv)) {
                    tmp[su].insert(sv);
                    dag[su].push_back(sv);
                }
            }
        }
        return scc_cnt;
    }

    vector<int> top() {
        vector<int> order(scc_cnt);
        for (int i = 0; i < scc_cnt; ++i) order[i] = scc_cnt - 1 - i;
        return order;
    }
};
```

### 最大流最小割

```cpp
struct Dinic {
    struct Edge {
        int to;
        LL cap;
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> cur;

    Dinic(int _n) : n(_n), adj(_n + 1), level(_n + 1), cur(_n + 1) {
    }

    void add(int u, int v, LL w) {
        adj[u].push_back({v, w, (int)adj[v].size()});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    LL dfs(int u, int t, LL flow) {
        if (u == t || flow == 0) return flow;
        for (int& i = cur[u]; i < adj[u].size(); ++i) {
            Edge& e = adj[u][i];
            if (level[e.to] == level[u] + 1 && e.cap > 0) {
                LL d = dfs(e.to, t, min(flow, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    adj[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    LL max_flow(int s, int t) {
        LL flow = 0;
        while (bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while (LL pushed = dfs(s, t, LL_INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};
```

## 数学

### 欧几里得和扩展欧几里得

```cpp
LL gcd(LL x, LL y) {
    return y ? gcd(y, x % y) : x;
}
```

- 扩展欧几里得求解线性同余方程$ax \equiv  b(\mod m)$, 等价于$ax + my \equiv b$
- 求逆元, $ax \equiv q(\mod m)$, 等价于$ax + m \equiv 1$, **需要保证$gcd(a, m) = 1$, 否则无解**

```cpp
auto exgcd = [&](auto exgcd, LL a, LL b, LL& x, LL& y) -> LL {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    LL _x, _y;
    LL d = exgcd(exgcd, b, a % b, _x, _y);
    x = _y;
    y = _x - (a / b) * _y;
    return d;
};
```

### 求组合数

$a, b$非常大用$lucas$定理

```cpp
struct Comb {
    int n;
    vector<LL> fact, infact;
    Comb(int _n) : n(_n + 1), fact(_n + 1), infact(_n + 1) {
        fact[0] = 1;
        for (int i = 1; i < n; ++i) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        infact[n - 1] = qpow(fact[n - 1], MOD - 2);
        for (int i = n - 2; i >= 0; --i) {
            infact[i] = infact[i + 1] * (i + 1) % MOD;
        }
    };

    LL C(LL a, LL b) {
        if (a < b || b < 0) return 0;
        return fact[a] * infact[b] % MOD * infact[a - b] % MOD;
    }

    LL lucas(LL a, LL b) {
        if (b == 0) return 1;
        return lucas(a / MOD, b / MOD) * C(a % MOD, b % MOD) % MOD;
    }
};
```

### 线性基

```cpp
struct LB { // Linear Basis
    using i64 = long long;
    const int BASE = 63;
    vector<i64> d, p;
    int cnt, flag;

    LB() {
        d.resize(BASE + 1);
        p.resize(BASE + 1);
        cnt = flag = 0;
    }
    bool insert(i64 val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    return true;
                }
                val ^= d[i];
            }
        }
        flag = 1; // 可以异或出0
        return false;
    }
    bool check(i64 val) { // 判断 val 是否能被异或得到
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    return false;
                }
                val ^= d[i];
            }
        }
        return true;
    }
    i64 ask_max() {
        i64 res = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ d[i]) > res) res ^= d[i];
        }
        return res;
    }
    i64 ask_min() {
        if (flag) return 0; // 特判 0
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i]) return d[i];
        }
    }
    void rebuild() { // 第k小值独立预处理
        for (int i = BASE - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (d[i] & (1ll << j)) d[i] ^= d[j];
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i]) p[cnt++] = d[i];
        }
    }
    i64 kthquery(i64 k) { // 查询能被异或得到的第 k 小值, 如不存在则返回 -1
        if (flag) k--;    // 特判 0, 如果不需要 0, 直接删去
        if (!k) return 0;
        i64 res = 0;
        if (k >= (1ll << cnt)) return -1;
        for (int i = BASE - 1; i >= 0; i--) {
            if (k & (1LL << i)) res ^= p[i];
        }
        return res;
    }
    void Merge(const LB& b) { // 合并两个线性基
        for (int i = BASE - 1; i >= 0; i--) {
            if (b.d[i]) {
                insert(b.d[i]);
            }
        }
    }
};
```

### 矩阵乘法

```cpp
template <int MOD>
struct Mat {
    int n, m;
    vector<vector<i64>> a;

    Mat(int n, int m) : n(n), m(m), a(n, vector<i64>(m, 0)) {
    }
    Mat(int n) : Mat(n, n) {
    }
    Mat(const vector<vector<i64>>& v)
        : n(v.size()), m(v.empty() ? 0 : v[0].size()), a(v) {
    }

    vector<i64>& operator[](int i) {
        return a[i];
    }
    const vector<i64>& operator[](int i) const {
        return a[i];
    }

    static Matrix identity(int n) {
        Matrix I(n, n);
        for (int i = 0; i < n; i++) I.a[i][i] = 1;
        return I;
    }

    Mat operator*(const Mat& o) const {
        assert(m == o.n);
        Mat c(n, o.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (!a[i][k]) continue;
                i64 aik = a[i][k];
                for (int j = 0; j < o.m; j++) {
                    c.a[i][j] = (c.a[i][j] + aik * o.a[k][j]) % MOD;
                }
            }
        }
        return c;
    }

    Mat& operator*=(const Matrix& o) {
        return *this = *this * o;
    }

    Mat operator+(const Mat& o) const {
        assert(n == o.n && m == o.m);
        Mat c(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                c.a[i][j] = (a[i][j] + o.a[i][j]) % MOD;
        return c;
    }
};
```

### 快速幂

```cpp
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
```

### 三分求单峰函数极值

```cpp
    auto calc = [&](LL m) -> LL {

    };

    LL l = 0, r = n * n / 4;
    while (r - l >= 3) {
        LL d = (r - l) / 3;
        LL m1 = l + d;
        LL m2 = r - d;
        if (calc(m1) <= calc(m2)) {
            l = m1;
        }
        else r = m2;
    }
```



## 字符串

### Trie树

```cpp
template <int M, char Base>
struct Trie {
    vector<array<int, M>> tr; // 子节点
    vector<int> cnt;          // 以该节点结尾的单词数
    vector<int> pass;         // 经过该节点的单词数

    Trie() {
        new_node();
    }

    int new_node() {
        tr.push_back({});
        cnt.push_back(0);
        pass.push_back(0);
        return (int)tr.size() - 1;
    }

    void insert(const string& s) {
        int p = 0;
        pass[p]++;
        for (char c : s) {
            int u = c - Base;
            if (!tr[p][u])
                tr[p][u] = new_node();
            p = tr[p][u];
            pass[p]++;
        }
        cnt[p]++;
    }

    void erase(const string& s) {
        int p = 0;
        pass[p]--;
        for (char c : s) {
            int u = c - Base;
            int nxt = tr[p][u];
            pass[nxt]--;
            if (pass[nxt] == 0) {
                tr[p][u] = 0;
                return;
            }
            p = nxt;
        }
        cnt[p]--;
    }

    int count_word(const string& s) {
        int p = 0;
        for (char c : s) {
            int u = c - Base;
            if (!tr[p][u]) return 0;
            p = tr[p][u];
        }
        return cnt[p];
    }

    int count_prefix(const string& s) {
        int p = 0;
        for (char c : s) {
            int u = c - Base;
            if (!tr[p][u]) return 0;
            p = tr[p][u];
        }
        return pass[p];
    }

    bool search(const string& s) {
        return count_word(s) > 0;
    }

    bool starts_with(const string& s) {
        return count_prefix(s) > 0;
    }

    void clear() {
        tr.clear();
        cnt.clear();
        pass.clear();
        new_node();
    }

    int size() {
        return (int)tr.size();
    } // 节点数量
};
```



### 字符串哈希

```cpp
struct Hash {
    vector<ULL> h, p;
    int B = 131;
    Hash(const string& s) {
        int n = s.size();
        h.resize(n + 1, 0);
        p.resize(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            p[i + 1] = p[i] * B;
            h[i + 1] = (h[i] * B + s[i]);
        }
    }
    // 给定字符串是0-base, get 是1-base
    LL get(int l, int r) {
        LL v = h[r] - h[l - 1] * p[r - l + 1];
        return v;
    }
};
```

### $AC$自动机

```cpp
template <int M, char Base>
struct AC_automata {
    struct Node {
        int next[M];
        int fail;
        int mask; // 该节点对应的模式串集合（包括 fail 链上的）
        Node() : fail(0), mask(0) {
            fill(next, next + M, 0);
        }
    };
    vector<Node> tr;
    AC_automata() {
        tr.emplace_back();
    }

    int size() const {
        return tr.size();
    }
    Node& operator[](int i) {
        return tr[i];
    }

    void insert(const string& s, int idx) {
        int u = 0;
        for (char ch : s) {
            int c = ch - Base;
            if (!tr[u].next[c]) {
                tr.emplace_back();
                tr[u].next[c] = tr.size() - 1;
            }
            u = tr[u].next[c];
        }
        tr[u].mask |= (1 << idx);
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < M; c++) {
            if (tr[0].next[c]) q.push(tr[0].next[c]);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            tr[u].mask |= tr[tr[u].fail].mask;
            for (int c = 0; c < M; c++) {
                int& v = tr[u].next[c];
                if (v) {
                    tr[v].fail = tr[tr[u].fail].next[c];
                    q.push(v);
                }
                else {
                    v = tr[tr[u].fail].next[c];
                }
            }
        }
    }
};
```

### 后缀数组

```cpp
#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    string s;
    int n = 0;

    vector<int> sa;  // sa[i] = 排名第 i 的后缀的起始位置
    vector<int> rk;  // rk[i] = 后缀 i 的排名
    vector<int> lcp; // lcp[i] = sa[i] 与 sa[i-1] 的 LCP，lcp[0]=0

    vector<vector<int>> st; // RMQ for lcp
    vector<int> lg;

    SuffixArray() {
    }
    SuffixArray(const string& str) {
        build(str);
    }

    void build(const string& str) {
        s = str;
        n = (int)s.size();
        sa.assign(n, 0);
        rk.assign(n, 0);
        lcp.assign(n, 0);
        st.clear();
        lg.clear();

        if (n == 0) return;

        vector<int> x(n), y(n), c(max(256, n) + 1, 0);

        int m = 256;
        for (int i = 0; i < n; ++i) ++c[x[i] = (unsigned char)s[i]];
        for (int i = 1; i < m; ++i) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;

        for (int k = 1; k < n; k <<= 1) {
            int p = 0;

            for (int i = n - k; i < n; ++i) y[p++] = i;
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= k) y[p++] = sa[i] - k;
            }

            fill(c.begin(), c.begin() + m, 0);
            for (int i = 0; i < n; ++i) ++c[x[y[i]]];
            for (int i = 1; i < m; ++i) c[i] += c[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];

            swap(x, y);
            x[sa[0]] = 0;
            p = 1;

            for (int i = 1; i < n; ++i) {
                int a = sa[i], b = sa[i - 1];
                bool same_first = (y[a] == y[b]);
                bool same_second =
                    ((a + k < n ? y[a + k] : -1) == (b + k < n ? y[b + k] : -1));
                x[a] = (same_first && same_second) ? (p - 1) : p++;
            }

            if (p >= n) break;
            m = p;
        }

        for (int i = 0; i < n; ++i) rk[sa[i]] = i;

        build_lcp();
        build_rmq();
    }

    // =========================
    // 问题：模式串是否存在
    // =========================
    bool contains(const string& p) const {
        if (n == 0) return p.empty();
        int pos = lower_bound_pattern(p);
        return pos < n && starts_with(sa[pos], p);
    }

    // =========================
    // 问题：模式串出现次数
    // =========================
    int count_occurrences(const string& p) const {
        auto [L, R] = equal_range_pattern(p);
        return R - L;
    }

    // =========================
    // 问题：模式串出现位置
    // sort_by_pos = true  -> 按原串位置升序返回
    // sort_by_pos = false -> 按后缀字典序区间返回
    // =========================
    vector<int> occurrence_positions(const string& p, bool sort_by_pos = true) const {
        auto [L, R] = equal_range_pattern(p);
        vector<int> res;
        for (int i = L; i < R; ++i) res.push_back(sa[i]);
        if (sort_by_pos) sort(res.begin(), res.end());
        return res;
    }

    // =========================
    // 问题：本质不同子串个数
    // =========================
    long long count_distinct_substrings() const {
        long long total = 1LL * n * (n + 1) / 2;
        long long repeated = 0;
        for (int x : lcp) repeated += x;
        return total - repeated;
    }

    // =========================
    // 问题：最长重复子串长度
    // =========================
    int longest_repeated_substring_len() const {
        int ans = 0;
        for (int x : lcp) ans = max(ans, x);
        return ans;
    }

    // =========================
    // 问题：最长重复子串
    // 若不存在，返回空串
    // =========================
    string longest_repeated_substring() const {
        int best_len = 0, best_idx = -1;
        for (int i = 1; i < n; ++i) {
            if (lcp[i] > best_len) {
                best_len = lcp[i];
                best_idx = i;
            }
        }
        if (best_len == 0) return "";
        return s.substr(sa[best_idx], best_len);
    }

    // =========================
    // 问题：任意两个后缀的 LCP
    // 即 s[i..] 和 s[j..] 的最长公共前缀长度
    // =========================
    int lcp_suffix(int i, int j) const {
        if (i < 0 || j < 0 || i >= n || j >= n) return 0;
        if (i == j) return n - i;
        int ri = rk[i], rj = rk[j];
        if (ri > rj) swap(ri, rj);
        return rmq(ri + 1, rj);
    }

    // =========================
    // 问题：按字典序第 k 小的不同子串
    // k 从 1 开始，若不存在返回 ""
    // =========================
    string kth_distinct_substring(long long k) const {
        if (k <= 0) return "";
        for (int i = 0; i < n; ++i) {
            long long add = (n - sa[i]) - lcp[i];
            if (k > add) {
                k -= add;
            }
            else {
                int len = lcp[i] + (int)k;
                return s.substr(sa[i], len);
            }
        }
        return "";
    }

    // 返回模式串对应的后缀数组区间 [L, R)
    pair<int, int> equal_range_pattern(const string& p) const {
        int L = lower_bound_pattern(p);
        if (L == n || !starts_with(sa[L], p)) return {L, L};

        int l = L, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (starts_with(sa[mid], p)) l = mid + 1;
            else r = mid;
        }
        return {L, l};
    }

private:
    void build_lcp() {
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rk[i] == 0) {
                lcp[0] = 0;
                continue;
            }
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            lcp[rk[i]] = k;
            if (k) --k;
        }
    }

    void build_rmq() {
        if (n == 0) return;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        int K = lg[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = lcp;
        for (int k = 1; k < K; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int rmq(int l, int r) const {
        if (l > r) return 0;
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }

    // 比较 suffix(s[pos..]) 和 pattern p
    // 返回：
    // -1 -> suffix < p
    //  0 -> p 是 suffix 的前缀（即匹配到 p 结束）
    //  1 -> suffix > p
    int compare_suffix_pattern(int pos, const string& p) const {
        int m = (int)p.size();
        int i = 0;
        while (pos + i < n && i < m) {
            unsigned char a = (unsigned char)s[pos + i];
            unsigned char b = (unsigned char)p[i];
            if (a != b) return a < b ? -1 : 1;
            ++i;
        }
        if (i == m) return 0; // pattern 匹配完了
        return -1;            // suffix 先结束，说明 suffix < pattern
    }

    bool starts_with(int pos, const string& p) const {
        return compare_suffix_pattern(pos, p) == 0;
    }

    int lower_bound_pattern(const string& p) const {
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (compare_suffix_pattern(sa[mid], p) < 0) l = mid + 1;
            else r = mid;
        }
        return l;
    }
};
```



### 后缀自动机

```cpp
struct SuffixAutomaton {
    struct State {
        int len = 0;             // 这个状态表示的最长串长度
        int link = -1;           // 后缀链接
        int first_pos = -1;      // 某个出现位置的结尾下标
        long long end_count = 0; // 作为某次插入终点的次数
        long long occ = 0;       // 子串出现次数（需要 prepare_occ 后可用）
        map<char, int> next;     // 转移
    };

    vector<State> st;
    int last = 0;
    string s;

    vector<long long> dp; // dp[v] = 从状态 v 出发能产生多少个不同子串
    bool occ_ready = false;
    bool dp_ready = false;

    SuffixAutomaton() {
        init();
    }
    SuffixAutomaton(const string& str) {
        init();
        build(str);
    }

    void init() {
        st.clear();
        st.push_back(State()); // root = 0
        st[0].link = -1;
        last = 0;
        s.clear();
        dp.clear();
        occ_ready = false;
        dp_ready = false;
    }

    // =========================
    // 问题：在线在末尾追加字符
    // =========================
    void extend(char c) {
        s.push_back(c);

        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].first_pos = st[cur].len - 1;
        st[cur].end_count = 1;

        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        }
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            }
            else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].end_count = 0;
                st[clone].occ = 0;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
        occ_ready = false;
        dp_ready = false;
    }

    void build(const string& str) {
        init();
        for (char c : str) extend(c);
        prepare_occ();
    }

    // =========================
    // 问题：子串是否存在
    // =========================
    bool contains(const string& t) const {
        int v = 0;
        for (char c : t) {
            auto it = st[v].next.find(c);
            if (it == st[v].next.end()) return false;
            v = it->second;
        }
        return true;
    }

    // =========================
    // 问题：子串出现次数
    // 注意：会自动准备 occ
    // =========================
    long long count_occurrences(const string& t) {
        prepare_occ();
        int v = 0;
        for (char c : t) {
            auto it = st[v].next.find(c);
            if (it == st[v].next.end()) return 0;
            v = it->second;
        }
        return st[v].occ;
    }

    // =========================
    // 问题：本质不同子串个数
    // =========================
    long long count_distinct_substrings() const {
        long long ans = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }

    // =========================
    // 问题：最长重复子串长度
    // =========================
    int longest_repeated_substring_len() {
        prepare_occ();
        int ans = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            if (st[v].occ >= 2) ans = max(ans, st[v].len);
        }
        return ans;
    }

    // =========================
    // 问题：最长重复子串
    // 若不存在，返回空串
    // =========================
    string longest_repeated_substring() {
        prepare_occ();
        int best_state = -1;
        int best_len = 0;

        for (int v = 1; v < (int)st.size(); ++v) {
            if (st[v].occ >= 2 && st[v].len > best_len) {
                best_len = st[v].len;
                best_state = v;
            }
        }

        if (best_state == -1) return "";
        int end_pos = st[best_state].first_pos;
        return s.substr(end_pos - best_len + 1, best_len);
    }

    // =========================
    // 问题：两串最长公共子串
    // 用法：先对主串 build，再传另一个串 t
    // 返回 {长度, 子串}
    // =========================
    pair<int, string> longest_common_substring(const string& t) const {
        int v = 0, l = 0;
        int best = 0, best_pos = -1;

        for (int i = 0; i < (int)t.size(); ++i) {
            char c = t[i];

            while (v && !st[v].next.count(c)) {
                v = st[v].link;
                l = st[v].len;
            }

            if (st[v].next.count(c)) {
                v = st[v].next.at(c);
                ++l;
            }
            else {
                v = 0;
                l = 0;
            }

            if (l > best) {
                best = l;
                best_pos = i;
            }
        }

        if (best == 0) return {0, ""};
        return {best, t.substr(best_pos - best + 1, best)};
    }

    // =========================
    // 问题：按字典序第 k 小的不同子串
    // k 从 1 开始，若不存在返回 ""
    // =========================
    string kth_distinct_substring(long long k) {
        prepare_dp();
        if (k <= 0 || k > dp[0]) return "";

        string ans;
        int v = 0;

        while (k > 0) {
            for (auto& [c, to] : st[v].next) {
                long long cnt = 1 + dp[to]; // 以 c 开头的所有不同子串数量
                if (k > cnt) {
                    k -= cnt;
                }
                else {
                    ans.push_back(c);
                    if (k == 1) return ans;
                    --k;
                    v = to;
                    break;
                }
            }
        }

        return ans;
    }

    // 准备每个状态的出现次数 occ
    void prepare_occ() {
        if (occ_ready) return;

        for (auto& node : st) node.occ = node.end_count;

        vector<int> ord(st.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            return st[a].len < st[b].len;
        });

        for (int i = (int)ord.size() - 1; i > 0; --i) {
            int v = ord[i];
            int p = st[v].link;
            if (p >= 0) st[p].occ += st[v].occ;
        }

        occ_ready = true;
    }

private:
    void prepare_dp() {
        if (dp_ready) return;

        dp.assign(st.size(), 0);
        vector<int> ord(st.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            return st[a].len < st[b].len;
        });

        const long long INF = (1LL << 62);

        for (int i = (int)ord.size() - 1; i >= 0; --i) {
            int v = ord[i];
            long long sum = 0;
            for (auto& [c, to] : st[v].next) {
                if (sum > INF - (1 + dp[to])) {
                    sum = INF;
                    break;
                }
                sum += 1 + dp[to];
            }
            dp[v] = sum;
        }

        dp_ready = true;
    }
};
```



## 计算几何

```cpp
#include <bits/stdc++.h>
using namespace std;

using ld = long double;
const ld EPS = 1e-12L;
const ld PI = acosl(-1.0L);

int sgn(ld x) {
    if (fabsl(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}

    // 向量加减、数乘数除
    Point operator + (const Point& o) const { return {x + o.x, y + o.y}; }
    Point operator - (const Point& o) const { return {x - o.x, y - o.y}; }
    Point operator * (ld k) const { return {x * k, y * k}; }
    Point operator / (ld k) const { return {x / k, y / k}; }

    // 比较
    bool operator == (const Point& o) const {
        return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;
    }
    bool operator < (const Point& o) const {
        if (sgn(x - o.x) != 0) return x < o.x;
        return y < o.y;
    }

    // 长度平方、长度
    ld norm2() const { return x * x + y * y; }
    ld norm()  const { return sqrtl(norm2()); }

    // 单位向量（要求不是零向量）
    Point unit() const {
        ld len = norm();
        return *this / len;
    }

    // 逆时针旋转 90°
    Point rot90() const { return {-y, x}; }

    // 逆时针旋转 ang 弧度
    Point rotate(ld ang) const {
        return {
            x * cosl(ang) - y * sinl(ang),
            x * sinl(ang) + y * cosl(ang)
        };
    }

    // 极角 [-pi, pi]
    ld angle() const {
        return atan2l(y, x);
    }
};

using Vec = Point;

// 点积
ld dot(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y;
}

// 叉积
ld cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}

// 三点叉积：AB x AC
ld cross(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

// 两点距离
ld dist2(Point a, Point b) {
    return (a - b).norm2();
}
ld dist(Point a, Point b) {
    return (a - b).norm();
}

// 转向判断：
// 1  -> 左转（逆时针）
// -1 -> 右转（顺时针）
// 0  -> 共线
int orient(Point a, Point b, Point c) {
    return sgn(cross(a, b, c));
}

// 平行 / 垂直
bool parallel(Vec a, Vec b) {
    return sgn(cross(a, b)) == 0;
}
bool perpendicular(Vec a, Vec b) {
    return sgn(dot(a, b)) == 0;
}

// 点 p 在直线 ab 上的投影点
Point projection(Point p, Point a, Point b) {
    if (a == b) return a;
    Vec ab = b - a;
    return a + ab * (dot(p - a, ab) / ab.norm2());
}

// 点 p 关于直线 ab 的对称点
Point reflection(Point p, Point a, Point b) {
    Point q = projection(p, a, b);
    return q * 2 - p;
}

// 点到直线 ab 的距离
ld distPointLine(Point p, Point a, Point b) {
    if (a == b) return dist(p, a); // 退化
    return fabsl(cross(b - a, p - a)) / (b - a).norm();
}

// 点到线段 ab 的距离
ld distPointSegment(Point p, Point a, Point b) {
    if (a == b) return dist(p, a);
    Vec ab = b - a;
    if (sgn(dot(p - a, ab)) < 0) return dist(p, a);
    if (sgn(dot(p - b, a - b)) < 0) return dist(p, b);
    return fabsl(cross(ab, p - a)) / ab.norm();
}

// 判断点 p 是否在线段 ab 上
bool onSegment(Point p, Point a, Point b) {
    return sgn(cross(b - a, p - a)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

// 判断两线段是否相交（包含端点、重合）
bool segIntersect(Point a1, Point a2, Point b1, Point b2) {
    int c1 = orient(a1, a2, b1);
    int c2 = orient(a1, a2, b2);
    int c3 = orient(b1, b2, a1);
    int c4 = orient(b1, b2, a2);

    if (c1 == 0 && c2 == 0) {
        auto overlap = [](ld l1, ld r1, ld l2, ld r2) {
            if (l1 > r1) swap(l1, r1);
            if (l2 > r2) swap(l2, r2);
            return max(l1, l2) <= min(r1, r2) + EPS;
        };
        return overlap(a1.x, a2.x, b1.x, b2.x) &&
               overlap(a1.y, a2.y, b1.y, b2.y);
    }

    return c1 * c2 <= 0 && c3 * c4 <= 0;
}

// 两向量夹角 [0, pi]，要求 a,b 都不是零向量
ld angleBetween(Vec a, Vec b) {
    ld c = dot(a, b) / a.norm() / b.norm();
    c = max((ld)-1.0, min((ld)1.0, c));
    return acosl(c);
}

// 三角形面积
ld triangleArea(Point a, Point b, Point c) {
    return fabsl(cross(a, b, c)) / 2.0L;
}

// ==================== 极角排序 ====================
// 从 x 正半轴开始，逆时针排序
int half(Vec a) {
    return (sgn(a.y) > 0 || (sgn(a.y) == 0 && sgn(a.x) >= 0)) ? 0 : 1;
}

// 按点 o 为中心进行极角排序
void polarSort(vector<Point>& p, Point o = {0, 0}) {
    sort(p.begin(), p.end(), [&](const Point& A, const Point& B) {
        Vec a = A - o;
        Vec b = B - o;

        int ha = half(a), hb = half(b);
        if (ha != hb) return ha < hb;

        int cr = sgn(cross(a, b));
        if (cr != 0) return cr > 0;   // 逆时针在前

        return a.norm2() < b.norm2(); // 同方向时，离中心近的在前
    });
}
```

