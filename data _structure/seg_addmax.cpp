using ll = long long;

template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;

    LazySegmentTree() : n(0) {
    }

    LazySegmentTree(int n_, const Info& v = Info()) {
        init(n_, v);
    }

    template <class T>
    LazySegmentTree(const vector<T>& a) {
        init(a);
    }

    // 用 n 个相同的初始值建树
    void init(int n_, const Info& v = Info()) {
        vector<Info> a(n_, v);
        init(a);
    }

    // 用数组建树
    template <class T>
    void init(const vector<T>& a) {
        n = (int)a.size();

        if (n == 0) {
            info.clear();
            tag.clear();
            return;
        }

        info.assign(4 * n + 5, Info());
        tag.assign(4 * n + 5, Tag());

        build(1, 0, n, a);
    }

    template <class T>
    void build(int p, int l, int r, const vector<T>& a) {
        if (r - l == 1) {
            info[p] = a[l];
            return;
        }

        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m, r, a);
        pull(p);
    }

    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void apply(int p, const Tag& v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p) {
        apply(p << 1, tag[p]);
        apply(p << 1 | 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            tag[p] = Tag();
            return;
        }

        push(p);

        int m = (l + r) >> 1;
        if (x < m) {
            modify(p << 1, l, m, x, v);
        }
        else {
            modify(p << 1 | 1, m, r, x, v);
        }

        pull(p);
    }

    void modify(int x, const Info& v) {
        assert(0 <= x && x < n);
        modify(1, 0, n, x, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (r <= x || y <= l) {
            return Info();
        }

        if (x <= l && r <= y) {
            return info[p];
        }

        push(p);

        int m = (l + r) >> 1;
        return rangeQuery(p << 1, l, m, x, y) + rangeQuery(p << 1 | 1, m, r, x, y);
    }

    Info rangeQuery(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return Info();
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag& v) {
        if (r <= x || y <= l) {
            return;
        }

        if (x <= l && r <= y) {
            apply(p, v);
            return;
        }

        push(p);

        int m = (l + r) >> 1;
        rangeApply(p << 1, l, m, x, y, v);
        rangeApply(p << 1 | 1, m, r, x, y, v);

        pull(p);
    }

    void rangeApply(int l, int r, const Tag& v) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        rangeApply(1, 0, n, l, r, v);
    }

    /*
        找 [x, y) 内第一个满足条件的位置。

        pred(info[p]) == false:
            表示这个节点对应的整个区间一定不可能有答案。

        pred(info[p]) == true:
            表示这个区间“可能”包含答案，需要继续往下找。

        返回下标；不存在返回 -1。
    */
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F&& pred) {
        if (r <= x || y <= l) {
            return -1;
        }

        if (x <= l && r <= y && !pred(info[p])) {
            return -1;
        }

        if (r - l == 1) {
            return l;
        }

        push(p);

        int m = (l + r) >> 1;
        int res = findFirst(p << 1, l, m, x, y, pred);

        if (res == -1) {
            res = findFirst(p << 1 | 1, m, r, x, y, pred);
        }

        return res;
    }

    template <class F>
    int findFirst(int l, int r, F&& pred) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return -1;
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F&& pred) {
        if (r <= x || y <= l) {
            return -1;
        }

        if (x <= l && r <= y && !pred(info[p])) {
            return -1;
        }

        if (r - l == 1) {
            return l;
        }

        push(p);

        int m = (l + r) >> 1;
        int res = findLast(p << 1 | 1, m, r, x, y, pred);

        if (res == -1) {
            res = findLast(p << 1, l, m, x, y, pred);
        }

        return res;
    }

    template <class F>
    int findLast(int l, int r, F&& pred) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return -1;
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Tag {
    ll add = 0;
    void apply(const Tag& t) & {
        add += t.add;
    }
};

struct Info {
    ll mx = -2e18;
    void apply(const Tag& t) & {
        mx += t.add;
    }
};

Info operator+(const Info& a, const Info& b) {
    return max(a.mx, b.mx);
}