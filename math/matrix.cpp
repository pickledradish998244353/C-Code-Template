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

template <int MOD>
struct Matrix {
    int n, m;
    vector<vector<i64>> a;

    Matrix(int n, int m) : n(n), m(m), a(n, vector<i64>(m, 0)) {
    }
    Matrix(int n) : Matrix(n, n) {
    }
    Matrix(const vector<vector<i64>>& v)
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

    Matrix operator*(const Matrix& o) const {
        assert(m == o.n);
        Matrix c(n, o.m);
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

    Matrix& operator*=(const Matrix& o) {
        return *this = *this * o;
    }

    Matrix operator+(const Matrix& o) const {
        assert(n == o.n && m == o.m);
        Matrix c(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                c.a[i][j] = (a[i][j] + o.a[i][j]) % MOD;
        return c;
    }

    // 快速幂（仅方阵）
    Matrix power(i64 p) const {
        assert(n == m);
        Matrix res = identity(n), base = *this;
        while (p) {
            if (p & 1) res *= base;
            base *= base;
            p >>= 1;
        }
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

