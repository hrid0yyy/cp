#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Modular arithmetic constants
const ll MOD = 1e9 + 7;
const ll MAXN = 1e6 + 5;

// Arrays to store factorials and their modular inverses
vector<ll> fact(MAXN), inv_fact(MAXN);

// Modular exponentiation for calculating (base^exp) % MOD
ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Precompute factorials and inverse factorials
void init_factorials() {
    fact[0] = inv_fact[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        inv_fact[i] = mod_pow(fact[i], MOD - 2, MOD); // Fermat's little theorem
    }
}

// Calculate combination nCr % MOD
ll nCr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[r] % MOD * inv_fact[n - r]) % MOD;
}

// Calculate permutation nPr % MOD
ll nPr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[n - r]) % MOD;
}

int main() {
    init_factorials(); // Precompute factorials and inverses
    
    // Example usage
    ll n = 5, r = 2;
    cout << "nCr(" << n << ", " << r << ") = " << nCr(n, r) << endl;
    cout << "nPr(" << n << ", " << r << ") = " << nPr(n, r) << endl;
    
    return 0;
}
