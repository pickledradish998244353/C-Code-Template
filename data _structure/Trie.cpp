#include <bits/stdc++.h>
using namespace std;

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

template <typename T = int, int BITS = 30>
struct BinaryTrie {
    struct Node {
        array<int, 2> ch = {0, 0}; // 子节点索引 0/1
        int cnt = 0;               // 经过/终止于该节点的数值个数 (Pass Count)
    };

    vector<Node> tr;

    BinaryTrie() {
        new_node();
    }

    int new_node() {
        tr.push_back(Node());
        return (int)tr.size() - 1;
    }

    // 插入数值 x，val 为改变的数量 (默认 +1)
    void insert(T x, int val = 1) {
        int p = 0;
        tr[p].cnt += val;
        for (int i = BITS - 1; i >= 0; i--) {
            int v = (x >> i) & 1;
            if (!tr[p].ch[v]) {
                tr[p].ch[v] = new_node();
            }
            p = tr[p].ch[v];
            tr[p].cnt += val;
        }
    }

    // 删除数值 x (逻辑删除，将 count 减 1)
    void erase(T x) {
        insert(x, -1);
    }

    // 查询集合中存在的所有 y 中，(x ^ y) 的最大值
    T max_xor(T x) const {
        if (tr[0].cnt == 0) return 0; // Trie 为空
        int p = 0;
        T res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            int v = (x >> i) & 1;
            int want = v ^ 1; // 贪心：优先走相反的方向
            if (tr[p].ch[want] && tr[tr[p].ch[want]].cnt > 0) {
                res |= ((T)1 << i);
                p = tr[p].ch[want];
            }
            else {
                p = tr[p].ch[v];
            }
        }
        return res;
    }

    // 查询集合中存在的所有 y 中，(x ^ y) 的最小值
    T min_xor(T x) const {
        if (tr[0].cnt == 0) return 0;
        int p = 0;
        T res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            int v = (x >> i) & 1;
            int want = v; // 贪心：优先走相同的方向以抵消
            if (tr[p].ch[want] && tr[tr[p].ch[want]].cnt > 0) {
                p = tr[p].ch[want];
            }
            else {
                res |= ((T)1 << i);
                p = tr[p].ch[v ^ 1];
            }
        }
        return res;
    }

    // 查询与 x 异或结果中，第 k 小的值 (k 从 1 开始)
    T kth_min_xor(T x, int k) const {
        if (k < 1 || k > tr[0].cnt) return -1; // 超出范围
        int p = 0;
        T res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            int v = (x >> i) & 1;
            int left_child = tr[p].ch[v];
            int left_cnt = (left_child ? tr[left_child].cnt : 0);

            if (k <= left_cnt) {
                p = left_child;
            }
            else {
                k -= left_cnt;
                res |= ((T)1 << i);
                p = tr[p].ch[v ^ 1];
            }
        }
        return res;
    }

    void clear() {
        tr.clear();
        new_node();
    }

    int size() const {
        return (int)tr.size();
    }

    int count() const {
        return tr[0].cnt;
    }
};