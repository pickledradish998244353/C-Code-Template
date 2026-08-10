#include <bits/stdc++.h>
using namespace std;

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