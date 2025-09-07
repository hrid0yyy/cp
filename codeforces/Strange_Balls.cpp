#include<bits/stdc++.h>
using namespace std;

int trackCheck(stack<int> stk)
{
    int trk = 1;
    int first = stk.top();
    stk.pop();
    
    while(!stk.empty())
    {
        if(first == stk.top()) 
        {
            trk++;
            stk.pop();
        }
        else
        {
            return trk;
        }
    }

    return trk;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    stack <int> stk;
    int track = 1;

    for(int i=1;i<=N;i++)
    {
        int a;
        cin >> a;
        
        if(!stk.empty())
        {
            if(stk.top() == a) 
            {
                track++;

                if(track == a)
                {
                    while(track != 1)
                    {
                        if(!stk.empty()) stk.pop();
                        track--;
                    }
                    
                    if(!stk.empty()) track = trackCheck(stk);

                    cout << stk.size() << endl;
                }
                else
                {
                    stk.push(a);
                    cout << stk.size() << endl;
                }
            }
            else
            {
                track = 1;
                stk.push(a);
                cout << stk.size() << endl;
            }
        }
        else
        {
            track = 1;
            stk.push(a);
            cout << stk.size() << endl;
        }
    }

   

    return 0;
}