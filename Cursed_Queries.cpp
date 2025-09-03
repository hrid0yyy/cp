#include <bits/stdc++.h>
using namespace std;

struct BIT
{
    vector<int> tree;
    int n;
    BIT() : n(0) {} // Default constructor
    BIT(int sz) : n(sz), tree(sz + 2, 0) {}
    void add(int idx, int val)
    {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] += val;
    }
    int sum(int idx)
    {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res += tree[idx];
        return res;
    }
    int range(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        int q;
        cin >> q;
        map<int, BIT> bits; // g -> BIT
        vector<int> gs;     // order of g's seen
        while (q--)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int i, x;
                cin >> i >> x;
                --i;
                for (auto &[g, bit] : bits)
                {
                    int old = (a[i] % g == 0);
                    int nw = (x % g == 0);
                    if (old != nw)
                        bit.add(i, nw - old);
                }
                a[i] = x;
            }
            else if (type == 2)
            {
                int l, r, k;
                cin >> l >> r >> k;
                int g = gcd(k, m);
                if (!bits.count(g))
                {
                    bits[g] = BIT(n);
                    for (int i = 0; i < n; ++i)
                        if (a[i] % g == 0)
                            bits[g].add(i, 1);
                }
                int total = r - l + 1;
                int bad = bits[g].range(l - 1, r - 1);
                cout << total - bad << '\n';
            }
        }
    }
    return 0;
}
