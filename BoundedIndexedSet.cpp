struct BoundedIndexedSet {
    int M; int *tree;
    BoundedIndexedSet(int N) {
        M = 1; while (M < N) M <<= 1;
        tree = new int[M << 1];
        fill(tree, tree + (M << 1), 0);
    }
    void set(int k, int v) {
        int n = M + k;
        tree[n] = v; n >>= 1;
        while (n > 0) tree[n] = tree[n * 2] + tree[n * 2 + 1], n >>= 1;
    }
    void add(int k) { set(k, 1); }
    void remove(int k) { set(k, 0); }
    bool contains(int k) { return tree[M + k]; }
    int higher(int k) {
        int n = M + k;
        while (!tree[n]) {
            if (__builtin_popcount(n + 1) == 1) return -1;
            if (n % 2 == 1) n = n / 2 + 1;
            else n /= 2; }
        while (n < M) {
            if (tree[n * 2]) n *= 2;
            else n = n * 2 + 1; }
        return n - M;
    }
    int lower(int k) {
        int n = M + k;
        while (!tree[n]) {
            if (__builtin_popcount(n) == 1) return -1;
            if (n % 2 == 0) n = n / 2 - 1;
            else n /= 2; }
        while (n < M) {
            if (tree[n * 2 + 1]) n = n * 2 + 1;
            else n *= 2; }
        return n - M;
    }
};