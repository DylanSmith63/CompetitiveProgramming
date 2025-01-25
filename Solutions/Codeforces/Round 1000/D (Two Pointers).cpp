#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x),end(x)
#define lb(x,y) lower_bound(all(x),y)-begin(x)

mt19937 rng;

int getK(int N, int M) {
	return min(min(N, M), (N + M) / 3);
}

void solve() {
    int N, M; cin >> N >> M;
    int K = getK(N, M);
    vector<int> a(N), b(M);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    for (int i = 0; i < b.size(); i++) cin >> b[i];
    sort(all(a));
	sort(all(b));
	vector<pair<int, int>> srt;
	vector<int> srtA, srtB;
	for (int i = 0; i < N - 1 - i; i++) {
		srt.pb({a[N - 1 - i] - a[i], 0});
		srtA.pb(a[N - 1 - i] - a[i]);
	}
	for (int i = 0; i < M - 1 - i; i++) {
		srt.pb({b[M - 1 - i] - b[i], 1});
		srtB.pb(b[M - 1 - i] - b[i]);
	}
	vector<ll> preSrtA(sz(srtA) + 1, 0), preSrtB(sz(srtB) + 1, 0);
	for (int i = 0; i < sz(srtA); i++) preSrtA[i+1] += preSrtA[i] + srtA[i];
	for (int i = 0; i < sz(srtB); i++) preSrtB[i+1] += preSrtB[i] + srtB[i];
	sort(all(srt));
	reverse(all(srt));
	int cnt = 0, cntA = 0, cntB = 0, kP = K, kP2 = 1;
	ll sum = 0;
	vector<ll> res(K + 1);
	for (auto &p : srt) {
		while (kP >= cnt + 1) {
			bool stop = 1;
			if (p.second == 0) {
				if (cnt + 1 + getK(N - cntA * 2 - cntB - 2, M - cntB * 2 - cntA - 1) < kP) {
					int k = kP - cnt;
					res[kP] = sum + preSrtB[cntB + k] - preSrtB[cntB];
					stop = 0;
					kP--;
				}
			} else {
				if (cnt + 1 + getK(N - cntA * 2 - cntB - 1, M - cntB * 2 - cntA - 2) < kP) {
					int k = kP - cnt;
					res[kP] = sum + preSrtA[cntA + k] - preSrtA[cntA];
					stop = 0;
					kP--;
				}
			}
			if (stop) break;
		}
		cnt++;
		if (p.second == 0) cntA++;
		else cntB++;
		sum += p.first;
		if (cnt > kP) break;
		res[cnt] = sum;
	}

	cout << K << "\n";
	for (int i = 1; i <= K; i++) {
		cout << res[i] << (i == K ? "\n" : " ");
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }

    return 0;
}