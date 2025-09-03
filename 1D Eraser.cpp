#include <bits/stdc++.h>
using namespace std;
int main()
{

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;

        int count = 0;
        for (int j = 0; j < n; j++)
        {
            int temp = 1;
            if (s[j] == 'B')
            {
                count++;
                j += k - 1;
            }
        }
        cout << count << endl;
    }
    return 0;
}