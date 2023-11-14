struct Trie {
    int bits = 30;
    struct Node {
        Node *z = nullptr, *o = nullptr, *p = nullptr;
        int cnt = 0;
        Node (Node *par) : p(par) {}
    };
    Node *root = new Node(nullptr);
    void merge(Node *n) {
        n->cnt = (n->z ? n->z->cnt : 0) + (n->o ? n->o->cnt : 0);
    }
    void add(int n) {
        Node *cur = root;
        for (int j = bits - 1; j >= 0; j--) {
            if (n & 1 << j) {
                if (!cur->o) cur->o = new Node(cur);
                cur = cur->o;
            } else {
                if (!cur->z) cur->z = new Node(cur);
                cur = cur->z;
            }
        }
        cur->cnt++;
        for (int j = 0; j < bits; j++) {
            cur = cur->p;
            merge(cur);
        }
    }
    void remove(int n) {
        Node *cur = root;
        for (int j = bits - 1; j >= 0; j--) {
            if (n & 1 << j) cur = cur->o;
            else cur = cur->z;
        }
        cur->cnt--;
        for (int j = 0; j < bits; j++) {
            cur = cur->p;
            merge(cur);
            if (cur->z && !cur->z->cnt) cur->z = nullptr;
            if (cur->o && !cur->o->cnt) cur->o = nullptr;
        }
    }
    int maxXor(int n) {
        Node *cur = root;
        int res = 0;
        for (int j = bits - 1; j >= 0; j--) {
            if (n & 1 << j) {
                if (cur->z) {
                    cur = cur->z;
                    res ^= 1 << j;
                } else cur = cur->o;
            } else {
                if (cur->o) {
                    cur = cur->o;
                    res ^= 1 << j;
                } else cur = cur->z;
            }
        }
        return res;
    }
};