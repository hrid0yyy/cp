#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;

    int len = s.size();

    int i = 0;
    int j = len - 1;

    int signal = 0;
    int cnt = 0;

    while (i < j)
    {
        if (s[i] != s[j])
        {
            signal = 1;
            break;
        }
        else
        {
            cnt++;
        }

        i++;
        j--;
    }

    if (signal)
    {
        cout << "1" << endl;
        return 0;
    }

    cout << cnt * 2 << endl;

    return 0;
}
