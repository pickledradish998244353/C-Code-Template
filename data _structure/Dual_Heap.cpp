template <class T = long long>
struct DualHeap {
    template <class Compare>
    struct ErasablePQ {
        priority_queue<T, vector<T>, Compare> pq, del;
        int sz = 0;
        T sum = 0;

        void push(T x) {
            pq.push(x);
            sz++;
            sum += x;
        }

        // 注意：调用 erase 时必须保证 x 确实在当前堆中存在
        void erase(T x) {
            del.push(x);
            sz--;
            sum -= x;
        }

        void prune() {
            while (!pq.empty() && !del.empty() && pq.top() == del.top()) {
                pq.pop();
                del.pop();
            }
        }

        T top() {
            prune();
            return pq.top();
        }

        void pop() {
            prune();
            T x = pq.top();
            pq.pop();
            sz--;
            sum -= x;
        }

        int size() const {
            return sz;
        }
        bool empty() const {
            return sz == 0;
        }
        T get_sum() const {
            return sum;
        }
    };

    ErasablePQ<less<T>> L;    // 大根堆，维护前 K 小的元素
    ErasablePQ<greater<T>> R; // 小根堆，维护剩余的较大元素
    int k;                    // 目标参数 k

    // 默认 k = -1 为动态下中位数模式；k >= 0 为固定前 k 小模式
    DualHeap(int k_ = -1) : k(k_) {
    }

    // 获取当前左堆 L 应该维持的目标大小
    int get_target_L_size() const {
        if (k == -1) return (size() + 1) / 2; // 下中位数
        return min((int)size(), k);           // 前 K 小
    }

    // 平衡两个堆的大小
    void balance() {
        int target = get_target_L_size();
        while (L.size() > target) {
            T x = L.top();
            L.pop();
            R.push(x);
        }
        while (L.size() < target) {
            T x = R.top();
            R.pop();
            L.push(x);
        }
    }

    // 插入元素
    void insert(T x) {
        if (L.empty() || x <= L.top()) {
            L.push(x);
        }
        else {
            R.push(x);
        }
        balance();
    }

    // 删除元素
    void erase(T x) {
        if (!L.empty() && x <= L.top()) {
            L.erase(x);
        }
        else {
            R.erase(x);
        }
        balance();
    }

    // 动态修改 k 值
    void set_k(int k_) {
        k = k_;
        balance();
    }

    int size() const {
        return L.size() + R.size();
    }
    bool empty() const {
        return size() == 0;
    }

    // 获取第 k 小
    T get_kth() {
        assert(!L.empty());
        return L.top();
    }

    // 获取下中位数（仅当 k == -1 时有意义）
    T get_median() {
        return get_kth();
    }

    // 获取前 k 小的元素之和
    T get_L_sum() const {
        return L.get_sum();
    }

    // 获取剩余元素的和
    T get_R_sum() const {
        return R.get_sum();
    }

    // 计算所有元素到某个指定值 x 的距离绝对值之和
    T get_abs_sum(T x) {
        return (x * L.size() - L.get_sum()) + (R.get_sum() - x * R.size());
    }
};