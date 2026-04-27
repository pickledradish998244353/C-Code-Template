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

template <typename Key, typename Val>
struct Map {
    struct custom_hash {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }
        template <class T>
        size_t operator()(const T& x) const {
            static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64((uint64_t)x + FIXED_RANDOM);
        }
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const {
            static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            uint64_t h1 = splitmix64((uint64_t)p.first + FIXED_RANDOM);
            uint64_t h2 = splitmix64((uint64_t)p.second + FIXED_RANDOM + 0x9e3779b9);
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };

    struct Node {
        Key key;
        Val val;
        int next;
    };

    static const int M = 1000003;
    static const int MAX_N = 5e5 + 10;

    vector<Node> pool;
    vector<int> head;
    int tot;
    custom_hash hash_fn;

    Map(int n = 2e5 + 10) : tot(0) {
        head.assign(M, -1);
        pool.reserve(n + 5);
    }

    void clear() {
        fill(head.begin(), head.end(), -1);
        pool.clear();
        tot = 0;
    }

    Node* end() {
        return nullptr;
    }

    Node* find(const Key& key) {
        int h = hash_fn(key) % M;
        for (int i = head[h]; i != -1; i = pool[i].next) {
            if (pool[i].key == key) return &pool[i];
        }
        return nullptr;
    }

    void insert(const Key& key, const Val& val) {
        int h = hash_fn(key) % M;
        for (int i = head[h]; i != -1; i = pool[i].next) {
            if (pool[i].key == key) {
                pool[i].val = val;
                return;
            }
        }
        pool.push_back({key, val, head[h]});
        head[h] = tot++;
    }

    Val& operator[](const Key& key) {
        int h = hash_fn(key) % M;
        for (int i = head[h]; i != -1; i = pool[i].next) {
            if (pool[i].key == key) return pool[i].val;
        }
        pool.push_back({key, Val(), head[h]});
        head[h] = tot++;
        return pool.back().val;
    }
};
