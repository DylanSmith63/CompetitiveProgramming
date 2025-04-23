/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: jiangly/tfg
 * Description: Fast Walsh Hadamard Transform, Extended to Base 3 (x_i^3-1)
 * Time: $O(n \log(n))$
 * Status: Tested on https://www.codechef.com/problems/MDSWIN?tab=statement
 */
#pragma once

// a + br where r^3=1
struct tmi {
	mi a, b;
	tmi operator+(const tmi &o) const { return tmi{a+o.a, b+o.b}; }
	tmi operator-(const tmi &o) const { return tmi{a-o.a, b-o.b}; }
	tmi operator*(const tmi &o) const { return tmi{a*o.a - b*o.b, b*o.a + a*o.b - b*o.b}; }
	tmi operator/(const tmi &o) const { return *this * o.inv(); }
	tmi &operator+=(const tmi &o) { return *this = *this + o; }
	tmi &operator-=(const tmi &o) { return *this = *this - o; }
	tmi &operator*=(const tmi &o) { return *this = *this * o; }
	tmi &operator/=(const tmi &o) { return *this = *this / o; }
	tmi pow(ll e) const {
		tmi res = tmi{1, 0};
		for (tmi n = *this; e; e >>= 1, n *= n) if (e & 1) res *= n;
		return res;
	}
	tmi inv() const { return pow(MOD - 2); }
};

void fwht3(vector<tmi> &v, bool inv = 0) {
	auto op = [&](int i, int j, int k) {
		tmi a = v[i], b = v[j], c = v[k];
		v[i] = a + b + c;
		v[j] = a + b * tmi{0, 1} + c * tmi{mod-1, mod-1};
		v[k] = a + b * tmi{mod-1, mod-1} + c * tmi{0, 1};
	};
	tmi div = tmi{1, 0}, inv3 = tmi{3, 0}.inv();
	for (int k = 1; k * 3 <= sz(v); k *= 3, div = div * inv3)
		for (int i = 0; i < sz(v); i += k * 3)
			for (int j = 0; j < k; j++)
				if (!inv) op(i + j, i + j + k, i + j + k * 2);
				else op(i + j, i + j + k * 2, i + j + k);
	if (inv) for (auto &i : v) i = i * div;
}