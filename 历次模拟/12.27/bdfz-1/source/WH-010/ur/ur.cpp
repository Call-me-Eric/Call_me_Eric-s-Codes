#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int maxn=1e6+5;
int k,n,cur;
bitset<maxn> ans;
vector<pii> vec;
inline void print()
{
    for(int i=0;i<n;i++) putchar(ans[i]+'0');
    putchar('\n'),exit(0);
}
inline bool push(int i,int j)
{
    if(cur+i>k) return 0;
    int d=n/i;
    for(int k=j;k<n;k+=d) if(ans[k]) return 0;
    cur+=i;
    for(int k=j;k<n;k+=d) ans[k]=1;
    return 1;
}
int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&k);
    if(k==1||k==n)
    {
        if(k==n) ans.set();
        print();
    }
    for(int i=2,x=n;i<=x;i++)
    {
        if(x%i) continue;
        int cnt=0;
        while(x%i==0) x/=i,cnt++;
        vec.push_back(mp(i,cnt));
    }
    int p=vec[0].fi;
    for(int i=0;i<k/p;i++) push(p,i);
    print();
    return 0;
}