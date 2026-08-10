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