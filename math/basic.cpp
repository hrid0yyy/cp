#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ------------------- GCD & LCM -------------------
ll gcd(ll a, ll b) {
    while (b != 0) { ll t = b; b = a % b; a = t; }
    return a;
}

ll lcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return a / gcd(a, b) * b;
}

// ------------------- Modular Arithmetic -------------------
ll mod_add(ll a, ll b, ll mod) { return (a + b) % mod; }
ll mod_sub(ll a, ll b, ll mod) { return (a - b + mod) % mod; }
ll mod_mul(ll a, ll b, ll mod) { return (__int128)a * b % mod; }

// Modular exponentiation
ll mod_pow(ll a, ll b, ll mod) {
    ll result = 1;
    a %= mod;
    while (b) {
        if (b & 1) result = (__int128)result * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return result;
}

// Modular inverse (mod must be prime)
ll mod_inv(ll a, ll mod) { return mod_pow(a, mod - 2, mod); }

// ------------------- Factorial & Combinations -------------------
const int MAXN = 1e6 + 5;
ll fact[MAXN];
ll inv_fact[MAXN];

void precompute_factorials(ll mod) {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) fact[i] = fact[i-1] * i % mod;
    inv_fact[MAXN-1] = mod_inv(fact[MAXN-1], mod);
    for (int i = MAXN-2; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % mod;
}

ll nCr(ll n, ll r, ll mod) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % mod * inv_fact[n-r] % mod;
}

// ------------------- Power & Integer Root -------------------
ll power(ll a, ll b) { // normal power
    ll result = 1;
    while (b) { if (b&1) result *= a; a *= a; b >>= 1; }
    return result;
}

// Integer square root
ll isqrt(ll x) {
    ll r = sqrtl(x);
    while (r*r > x) r--;
    while ((r+1)*(r+1) <= x) r++;
    return r;
}
