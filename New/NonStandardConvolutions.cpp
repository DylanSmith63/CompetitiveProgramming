/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: various sources, Ronit for subset fft
 * Description: OR Convolution, AND Convolution, XOR Convolution, GCD Convolution, LCM Convolution, Subset Convolution
 * Time: All are $O(n\log(n))$ except for subset convolution which is $O(n \log^2(n))$ iirc
 * Status: Tested on Library Checker Convolution section
 */
#pragma once

void orfft(vector<ll> &v) {
    for (int j = bits - 1; j >= 0; j--)
        for (int i = 0; i < 1 << bits; i++, i += i & 1 << j)
            v[i ^ 1 << j] += v[i];
    for (int i = 0; i < 1 << bits; i++) v[i] %= mod;
}
void orifft(vector<ll> &v) {
    for (int j = 0; j < bits; j++)
        for (int i = 0; i < 1 << bits; i++, i += i & 1 << j)
            v[i ^ 1 << j] -= v[i];
    for (int i = 0; i < 1 << bits; i++) v[i] = (v[i] % mod + mod) % mod;
}
vector<ll> orMult(vector<ll> a, vector<ll> b) {
    orfft(a); orfft(b); vector<ll> c(1 << bits);
    for (int i = 0; i < 1 << bits; i++) c[i] = a[i] * b[i] % mod;
    orifft(c); return c;
}
vector<ll> andMult(vector<ll> a, vector<ll> b) {
    reverse(all(a)); reverse(all(b));
    vector<ll> c = orMult(a, b);
    reverse(all(c)); return c;
}

void xorfft(vector<ll> &v, bool inv = 0) {
    for (int k = 0; k < bits; k++) {
        for (int i = 0; i < 1 << bits; i++, i += i & 1 << k) {
            ll a = v[i], b = v[i ^ 1 << k];
            v[i] = a + b, v[i ^ 1 << k] = a - b;
        }
    }
    for (int i = 0; i < 1 << bits; i++) v[i] = (v[i] % mod + mod) % mod;
    if (inv) {
        ll n = 1; for (int i = 0; i < bits; i++) n = n * 2 % mod;
        n = mInv(n);
        for (int i = 0; i < 1 << bits; i++) v[i] = v[i] * n % mod;
    }
}
vector<ll> mult(vector<ll> a, vector<ll> b) {
    xorfft(a); xorfft(b); vector<ll> c(1 << bits);
    for (int i = 0; i < 1 << bits; i++) c[i] = a[i] * b[i] % mod;
    xorfft(c, 1); return c;
}

// 1-indexed
vector<ll> gcdMult(vector<ll> a, vector<ll> b) {
    vector<ll> c(sz(a), 0);
    for (int g = sz(a); g >= 1; g--) {
        ll l = 0, r = 0;
        for (int i = g; i <= sz(a); i += g)
            l += a[i-1], r += b[i-1], c[g-1] -= c[i-1];
        c[g-1] += (l % mod) * (r % mod) % mod;
        c[g-1] = (c[g-1] % mod + mod) % mod;
    }
    return c;
}

// 1-indexed
vector<ll> lcmMult(vector<ll> a, vector<ll> b) {
    vector<ll> l(sz(a), 0), r(sz(a), 0), c(sz(a), 0);
    for (int i = 1; i <= sz(a); i++)
        for (int j = i; j <= sz(a); j += i)
            l[j-1] += a[i-1], r[j-1] += b[i-1];
    for (int g = 1; g <= sz(a); g++) {
        c[g-1] += (l[g-1] % mod) * (r[g-1] % mod) % mod;
        c[g-1] = (c[g-1] % mod + mod) % mod;
        for (int i = g*2; i <= sz(a); i += g) c[i-1] -= c[g-1];
    }
    return c;
}

struct yint {
    int B = 22; ll a[22];
    yint() { for (int i = 0; i < B; i++) a[i] = 0; }
    yint(ll k) { *this = yint(); a[0] = k; }
    yint& operator+=(yint o) {
        for (int i = 0; i < B; i++)
            if ((a[i] += o.a[i]) >= mod) a[i] -= mod;
        return *this; }
    yint& operator-=(yint o) {
        for (int i = 0; i < B; i++)
            if ((a[i] -= o.a[i]) < 0) a[i] += mod;
        return *this; }
    yint& operator*=(int k) {
        for (int i = 0; i < B; i++)
            a[i] = a[i] * k % mod;
        return *this; }
    yint& operator*=(yint o) {
        ll a2[22]; for (int i = 0; i < B; i++) a2[i] = 0;
        for (int i = 0; i < B; i++) for (int j = 0; i + j < B; j++) {
            a2[i + j] += a[i] * o.a[j] % mod;
            if (a2[i + j] >= mod) a2[i + j] -= mod; }
        swap(a, a2); return *this; }
    yint& operator-() {
        for (int i = 0; i < B; i++)
            if ((a[i] = -a[i]) < 0) a[i] += mod;
        return *this; }
    yint& shiftY(int k) {
        if (k > 0) {
            for (int i = B-1; i - k >= 0; i--) a[i] = a[i - k];
            for (int i = 0; i < k; i++) a[i] = 0;
        } else { k = -k;
            for (int i = 0; i + k < B; i++) a[i] = a[i + k];
            for (int i = B - k; i < B; i++) a[i] = 0;
        } return *this; }
    yint& multY() {
        for (int i = B-1; i > 0; i--) a[i] = a[i - 1];
        a[0] = 0; return *this; }
    yint& divY() {
        for (int i = 0; i < B-1; i++) a[i] = a[i + 1];
        a[B-1] = 0; return *this; }
    friend yint operator+(yint a, yint b) { return a += b; }
    friend yint operator-(yint a, yint b) { return a -= b; }
    friend yint operator*(yint a, yint b) { return a *= b; }
};

void subsetfft(vector<yint> &v) {
    for (int i = 0; i < 1 << bits; i++) v[i].shiftY(__builtin_popcount(i));
    for (int j = 0; j < bits; j++) {
        for (int i = 0; i < 1 << bits; i++, i += i & 1 << j) {
            yint a = v[i], by = v[i ^ 1 << j];
            v[i] = a - by; v[i ^ 1 << j] = a + by;
        }
    }
}
void subsetifft(vector<yint> &v) {
    for (int j = 0; j < bits; j++) {
        for (int i = 0; i < 1 << bits; i++, i += i & 1 << j) {
            yint a = v[i], b = v[i ^ 1 << j];
            v[i] = a + b; v[i ^ 1 << j] = (b - a);
        }
    }
    for (int i = 0; i < 1 << bits; i++) v[i].shiftY(-__builtin_popcount(i));
    ll p = 1; for (int j = 0; j < bits; j++) p = p * 2 % mod; p = mInv(p);
    for (int i = 0; i < 1 << bits; i++) v[i] *= p;
}
vector<ll> subsetMult(vector<ll> a, vector<ll> b) {
    vector<yint> aY(1 << bits), bY(1 << bits), cY(1 << bits);
    for (int i = 0; i < 1 << bits; i++) aY[i] = yint(a[i]), bY[i] = yint(b[i]);
    subsetfft(aY); subsetfft(bY);
    for (int i = 0; i < 1 << bits; i++) cY[i] = aY[i] * bY[i];
    subsetifft(cY);
    vector<ll> c(1 << bits);
    for (int i = 0; i < 1 << bits; i++) c[i] = cY[i].a[0];
    return c;
}
