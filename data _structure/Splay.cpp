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
        int s[2], p;
        LL v;
        int cnt, sz;
        void init(LL _v, int _p) {
            v = _v;
            p = _p;
            cnt = sz = 1;
            s[0] = s[1] = 0;
        }
    };

    int root, idx;
    vector<Node> tr;
    vector<int> q;

    int get_node(LL v, int p) {
        int u;
        if (!q.empty()) {
            u = q.back();
            q.pop_back();
        }
        else {
            u = ++idx;
        }
        tr[u].init(v, p);
        return u;
    }

    void del(int u) {
        tr[u].s[0] = tr[u].s[1] = tr[u].p = 0;
        tr[u].v = tr[u].cnt = tr[u].sz = 0;
        q.push_back(u);
    }

    void pushup(int u) {
        if (!u) return;
        tr[u].sz = tr[tr[u].s[0]].sz + tr[tr[u].s[1]].sz + tr[u].cnt;
    }

    void rotate(int x) {
        int y = tr[x].p, z = tr[y].p;
        int k = (tr[y].s[1] == x);
        tr[z].s[tr[z].s[1] == y] = x;
        tr[x].p = z;
        tr[y].s[k] = tr[x].s[k ^ 1];
        if (tr[x].s[k ^ 1]) tr[tr[x].s[k ^ 1]].p = y;
        tr[x].s[k ^ 1] = y;
        tr[y].p = x;
        pushup(y), pushup(x);
    }

    void splay(int x, int k) {
        while (tr[x].p != k) {
            int y = tr[x].p, z = tr[y].p;
            if (z != k)
                (tr[y].s[1] == x) ^ (tr[z].s[1] == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
        if (!k) root = x;
    }

    void find(LL val) {
        int u = root;
        if (!u) return;
        while (tr[u].s[val > tr[u].v] && val != tr[u].v)
            u = tr[u].s[val > tr[u].v];
        splay(u, 0);
    }

    void insert(LL val) {
        int u = root, p = 0;
        while (u && tr[u].v != val) {
            p = u;
            u = tr[u].s[val > tr[u].v];
        }
        if (u) {
            tr[u].cnt++;
        }
        else {
            u = get_node(val, p);
            if (p) tr[p].s[val > tr[p].v] = u;
        }
        splay(u, 0);
    }

    void remove(LL val) {
        find(val);
        int u = root;
        if (tr[u].v != val) return;

        if (tr[u].cnt > 1) {
            tr[u].cnt--;
            pushup(u);
            return;
        }

        int dnode = u;
        if (!tr[u].s[0] && !tr[u].s[1]) {
            root = 0;
        }
        else if (!tr[u].s[0]) {
            root = tr[u].s[1];
            tr[root].p = 0;
        }
        else if (!tr[u].s[1]) {
            root = tr[u].s[0];
            tr[root].p = 0;
        }
        else {
            int cur = tr[u].s[0];
            while (tr[cur].s[1]) cur = tr[cur].s[1];
            splay(cur, u);
            tr[cur].s[1] = tr[u].s[1];
            tr[tr[u].s[1]].p = cur;
            root = cur;
            tr[root].p = 0;
            pushup(root);
        }
        del(dnode);
    }

    LL get_k(int k) {
        k++;
        int u = root;
        while (u) {
            int lsz = tr[tr[u].s[0]].sz;
            if (k <= lsz) u = tr[u].s[0];
            else if (k <= lsz + tr[u].cnt) return tr[u].v;
            else {
                k -= (lsz + tr[u].cnt);
                u = tr[u].s[1];
            }
        }
        return -1;
    }

    int get_rank(LL val) {
        find(val);
        return tr[tr[root].s[0]].sz;
    }

    LL get_k_ptr(int k) {
        k++;
        int u = root;
        while (u) {
            int lsz = tr[tr[u].s[0]].sz;
            if (k <= lsz) u = tr[u].s[0];
            else if (k <= lsz + tr[u].cnt) return u;
            else {
                k -= (lsz + tr[u].cnt);
                u = tr[u].s[1];
            }
        }
        return -1;
    }

    LL get_pre(LL val) {
        find(val);
        int u = root;
        if (tr[u].v < val) return tr[u].v;
        u = tr[u].s[0];
        while (tr[u].s[1]) u = tr[u].s[1];
        return tr[u].v;
    }

    LL get_nxt(LL val) {
        find(val);
        int u = root;
        if (tr[u].v > val) return tr[u].v;
        u = tr[u].s[1];
        while (tr[u].s[0]) u = tr[u].s[0];
        return tr[u].v;
    }

    T(int _n) : root(0), idx(0), tr(_n + 10) {
        insert(-4e18);
        insert(4e18);
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