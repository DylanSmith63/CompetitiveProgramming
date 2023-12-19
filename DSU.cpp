struct DSU {
    vector<int> group, cnt;
    DSU(int N) {
        group = vector<int>(N);
        for (int i = 0; i < N; i++) group[i] = i;
        cnt = vector<int>(N, 1);
    }
    int find(int u) {
        return group[u] == u ? u : group[u] = find(group[u]);
    }
    bool merge(int u, int v) {
        int g1 = find(u), g2 = find(v);
        if (g1 == g2) return 0;
        if (cnt[g1] > cnt[g2]) swap(g1, g2);
        cnt[g2] += cnt[g1];
        group[g1] = g2;
        return 1;
    }
};