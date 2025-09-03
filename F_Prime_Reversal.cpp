#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  

    int T;
    cin >> T; 

    for(int i=1;i<=T;i++)
    {
        int N;
        cin >> N;

        string A, B;
        cin >> A >> B;
        map <char,int> mp1;
        map <char,int> mp2;

        for(int j=0;j<N;j++)
        {
            mp1[A[j]]++;
        }

        for(int j=0;j<N;j++)
        {
            mp2[B[j]]++;
        }
    
        if(mp1['0'] != mp2['0']) cout << "NO" << endl;
        else if(mp1['1'] != mp2['1']) cout << "NO" << endl;
        else cout << "YES" << endl;
    }


    return 0;
}