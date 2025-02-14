#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

map<ll, double> mem;
double search(int deck_bad, vector<int> deck_good, int hand_bad, vector<int> hand_good, bool drawing) {
    ll key = deck_bad;
    for (int i : deck_good) key = key * 6 + i;
    key = key * 6 + hand_bad;
    for (int i : hand_good) key = key * 6 + i;
    key = key * 2 + drawing;
    if (mem.count(key)) return mem[key];
    if (drawing) {
        int num_hand = hand_bad;
        for (int i : hand_good) {
            if (i == 5) return mem[key] = 0;
            num_hand += i;
        }
        if (num_hand == 5) return mem[key] = search(deck_bad, deck_good, hand_bad, hand_good, 0);
        int num_deck = deck_bad;
        for (int i : deck_good) num_deck += i;
        if (num_deck == 0) return mem[key] = 1000000.0;
        double res = 0.0;
        if (deck_bad > 0) {
            double d = search(deck_bad - 1, deck_good, hand_bad + 1, hand_good, drawing);
            if (d > 500000) return mem[key] = 1000000.0;
            res += (double)deck_bad / num_deck * d;
        }
        for (int i = 0; i < sz(deck_good); i++) {
            if (deck_good[i] > 0) {
                deck_good[i]--;
                hand_good[i]++;
                double d = search(deck_bad, deck_good, hand_bad, hand_good, drawing);
                deck_good[i]++;
                hand_good[i]--;
                if (d > 500000) return mem[key] = 1000000.0;
                res += (double)deck_good[i] / num_deck * d;
            }
        }
        return mem[key] = res;
    }
    int num_hand = hand_bad;
    for (int i : hand_good) num_hand += i;
    double res = 1000000.0;
    if (num_hand < 5) res = min(res, search(deck_bad, deck_good, hand_bad, hand_good, 1));
    if (hand_bad > 0) res = min(res, search(deck_bad, deck_good, hand_bad - 1, hand_good, drawing));
    for (int i = 0; i < sz(hand_good); i++) {
        if (hand_good[i] > 0) {
            hand_good[i]--;
            res = min(res, search(deck_bad, deck_good, hand_bad, hand_good, drawing));
            hand_good[i]++;
        }
    }
    if (res < 500000 && num_hand == 5) res++;
    return mem[key] = res;
}

vector<double> res = {3.598290598, 8.067171309, 12.423075934638051265, 16.636642360808391317};

void solve() {
    int N; cin >> N;
    cout << setprecision(20) << res[N - 1] << "\n";
    // takes ~5s for n=4
    // cout << setprecision(20) << search(8 * N, vector<int>(N, 5), 0, vector<int>(N, 0), 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    solve();

    return 0;
}