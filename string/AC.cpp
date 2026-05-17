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

template <int M, char Base>
struct AC_automata {
    struct Node {
        int next[M];
        int fail;
        bool out; // 是否包含模式串（自身是终止 或 fail 链上有终止）
        Node() : fail(0), out(false) {
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

    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - Base;
            if (!tr[u].next[c]) {
                tr.emplace_back();
                tr[u].next[c] = tr.size() - 1;
            }
            u = tr[u].next[c];
        }
        tr[u].out = true;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < M; c++) {
            if (tr[0].next[c]) q.push(tr[0].next[c]);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            tr[u].out = tr[u].out || tr[tr[u].fail].out;
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