#include <bits/stdc++.h>
using namespace std;

string intToRoman(int n)
{
    vector<pair<int, string>> val = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
    string roman = "";
    for (auto &p : val)
    {
        while (n >= p.first)
        {
            roman += p.second;
            n -= p.first;
        }
    }
    return roman;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << intToRoman(n) << endl;
    }
    return 0;
}