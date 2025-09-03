vector<int> primes;
bool sieved = false;

void sieve(int limit) {
    if (sieved) return;

    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    primes.clear();
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    sieved = true;
}

void precompute() {
    sieve(15000000);
}



// fast modular multiplication using __int128
ll mulmod(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

// fast modular exponentiation
ll power(ll a, ll b, ll mod) {
    ll result = 1;
    a %= mod;
    while (b) {
        if (b & 1) result = mulmod(result, a, mod);
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return result;
}

// Miller-Rabin test for a single base
bool millerTest(ll d, ll n, ll a) {
    ll x = power(a, d, n);
    if (x == 1 || x == n - 1) return true;

    while (d != n - 1) {
        x = mulmod(x, x, n);
        d *= 2;
        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    return false;
}

// fully optimized isPrime for numbers up to 10^16
bool isPrime(ll n) {
    if (n <= 3) return n > 1;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // small numbers: trial division
    if (n < 1e9) {
        for (ll i = 5; i * i <= n; i += 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        return true;
    }

    // large numbers: Miller-Rabin with __int128
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;

    // deterministic bases for n < 10^16
    ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll a : bases) {
        if (a >= n) break;
        if (!millerTest(d, n, a)) return false;
    }
    return true;
}


// Largest Prime factor
ll largestPrimeFactor(ll n) {
    long long maxPrime = -1;

    while (n % 2 == 0) {
        maxPrime = 2;
        n /= 2;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            maxPrime = i;
            n /= i;
        }
    }
    if (n > 2) {
        maxPrime = n;
    }
    return maxPrime;
}

