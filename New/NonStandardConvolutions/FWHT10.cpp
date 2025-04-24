// a + br + cr^2 + dr^3 where r^10=1
template <typename T>
struct r10 {
	T a = 0, b = 0, c = 0, d = 0;
	r10() : r10(0) {}
	r10(int n) : r10(T(n)) {}
	r10(T n) { a = n; }
	r10 operator+(const r10 &o) const {
		r10 res;
		res.a = a + o.a;
		res.b = b + o.b;
		res.c = c + o.c;
		res.d = d + o.d;
		return res;
	}
	r10 operator-(const r10 &o) const {
		r10 res;
		res.a = a - o.a;
		res.b = b - o.b;
		res.c = c - o.c;
		res.d = d - o.d;
		return res;
	}
	r10 operator*(const r10 &o) const {
		r10 res;
		res.a = a*o.a - b*o.d - c*o.c - c*o.d - d*o.b - d*o.c;
		res.b = a*o.b + b*o.a + b*o.d + c*o.c + d*o.b - d*o.d;
		res.c = a*o.c + b*o.b - b*o.d + c*o.a - c*o.c - d*o.b;
		res.d = a*o.d + b*o.c + b*o.d + c*o.b + c*o.c + d*o.a + d*o.b;
		return res;
	}
	r10 operator/(const r10 &o) const { return *this * o.inv(); }
	r10 &operator+=(const r10 &o) { return *this = *this + o; }
	r10 &operator-=(const r10 &o) { return *this = *this - o; }
	r10 &operator*=(const r10 &o) { return *this = *this * o; }
	r10 &operator/=(const r10 &o) { return *this = *this / o; }
	r10 pow(ll e) const {
		r10 res = 1;
		for (r10 n = *this; e; e >>= 1, n *= n) if (e & 1) res *= n;
		return res;
	}
	T real() {
		return a;
	}
};

// need to divide by sz(v) after calling with inv=1
template <typename T>
void fwht10(vector<r10<T>> &v, bool inv = 0) {
	r10<T> rt = 0; rt.b += 1;
	vector<r10<T>> pw(10, 1);
	for (int i = 1; i < 10; i++) pw[i] = pw[i - 1] * rt;
	if (inv) reverse(1+all(pw));
	auto op = [&](vector<int> &p) {
		vector<r10<T>> x(10);
		for (int i = 0; i < 10; i++) x[i] = v[p[i]], v[p[i]] = 0;
		rep(i, 0, 10) rep(j, 0, 10) v[p[i]] += x[j] * pw[i * j % 10];
	};
	for (int k = 1; k * 10 <= sz(v); k *= 10)
		for (int i = 0; i < sz(v); i += k * 10)
			for (int j = 0; j < k; j++) {
				vector<int> p;
				for (int x = 0; x < 10; x++) p.pb(i + j + k * x);
				op(p);
			}
}