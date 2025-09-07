#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define fr(i,s,n) for(int i = s; i < (n); i++)
#define fre(x, v) for(auto& x : v)
#define endl "\n"
#define vi vector<int>
#define vll vector<ll>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pair<int, int>>
#define mi map<int,int>
#define ff first
#define ss second

const int INF = 1e9;
const long long LINF = 1e18;
const int MOD = 1e9 + 7;

#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ", dout(__VA_ARGS__)
void dout() { cerr << endl; }
template <typename T, typename... Args>
void dout(T t, Args... args) {
    cerr << t;
    if(sizeof...(args)) cerr << ", ";
    dout(args...);
}

mt19937 rng(steady_clock::now().time_since_epoch().count());
ll getRand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}


void soln() {
    
}



signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    auto start = high_resolution_clock::now(); 
    ll tc = 1;
    cin >> tc;
    for (ll cn = 1; cn <= tc; cn++) {
        soln();
    }

    auto end = high_resolution_clock::now();   
    auto duration = duration_cast<milliseconds>(end - start).count();

    cerr << "Execution Time: " << duration << " ms" << endl;

    return 0;
}
