struct Trie {
    int bits = 30;
    struct Node {
        int z = -1, o = -1, p = -1, cnt = 0;
        Node (int par) : p(par) {};
    };
    vector<Node> tree;
    int newNode(int par = -1) {
        tree.pb({par});
        return sz(tree) - 1;
    }
    Trie() { newNode(); }
    void merge(int n) {
        tree[n].cnt = (tree[n].z >= 0 ? tree[tree[n].z].cnt : 0);
        tree[n].cnt += (tree[n].o >= 0 ? tree[tree[n].z].cnt : 0);
    }
    void add(int n) {
        int cur = 0;
        for (int j = bits - 1; j >= 0; j--) {
            if (n & 1 << j) {
                if (tree[cur].o == -1) tree[cur].o = newNode(cur);
                cur = tree[cur].o;
            } else {
                if (tree[cur].z == -1) tree[cur].z = newNode(cur);
                cur = tree[cur].z;
            }
        }
        tree[cur].cnt++;
        for (int j = 0; j < bits; j++) {
            cur = tree[cur].p;
            merge(cur);
        }
    }
    void remove(int n) {
        int cur = 0;
        for (int j = bits - 1; j >= 0; j--) {
            if (n & 1 << j) cur = tree[cur].o;
            else cur = tree[cur].z;
        }
        tree[cur].cnt--;
        for (int j = 0; j < bits; j++) {
            cur = tree[cur].p;
            merge(cur);
            if (tree[cur].z >= 0 && !tree[tree[cur].z].cnt) tree[cur].z = -1;
            if (tree[cur].o >= 0 && !tree[tree[cur].o].cnt) tree[cur].o = -1;
        }
    }
    int maxXor(int n) {
        int cur = 0, res = 0;
        for (int j = bits - 1; j >= 0; j--) {
            if (n & 1 << j) {
                if (tree[cur].z >= 0) {
                    cur = tree[cur].z;
                    res ^= 1 << j;
                } else cur = tree[cur].o;
            } else {
                if (tree[cur].o >= 0) {
                    cur = tree[cur].o;
                    res ^= 1 << j;
                } else cur = tree[cur].z;
            }
        }
        return res;
    }
};