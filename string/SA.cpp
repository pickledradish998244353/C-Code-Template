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