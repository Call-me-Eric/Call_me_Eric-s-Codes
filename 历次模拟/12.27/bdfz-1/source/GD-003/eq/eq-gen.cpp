#include<bits/stdc++.h>
using namespace std;

mt19937 mt(114514);
const int p=998244353;

inline
int randNum(int l,int r)
{
    return l+mt()%(r-l+1);
}

int main()
{
    const int n=700,q=700;
    cout<<n<<" "<<q<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n+1;j++) cout<<randNum(0,p-1)<<" ";
        cout<<endl;
    }
    for(int i=1;i<=q;i++)
    {
        cout<<randNum(1,n)<<" ";
        for(int j=1;j<=n+1;j++) cout<<randNum(0,p-1)<<" ";
        cout<<endl;
    }
}