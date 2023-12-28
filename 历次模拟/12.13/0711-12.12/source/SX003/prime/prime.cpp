#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,M=1e7+5;
int d[6]={0,1,4,6,8,9},tot=0,prime[M],sum[6];
bool v[M];
vector<int>vm[11];
void pre()
{
    for(int i=2;i<=1e7;i++)
    {
        if(!v[i]) tot++,prime[tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<=1e7;j++)
        {
            v[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
int pan(int x)
{
    int t=0;
    while(x) t++,x/=10;
    return t;
}
bool push(int x,int pre)
{
    vm[pre+1].clear(),vm[pre+1].push_back(x);
    for(int i=1;i<=pre;i++)
        for(int j:vm[i])
        {
            int y=j*10+x;
            if(prime[lower_bound(prime+1,prime+tot+1,y)-prime]==y)
            {
                vm[pre+1].clear();
                return 0;
            }
            vm[pre+1].push_back(y);
        }
    return 1;
}
int f(int x,int dep,int flag,int s,int top)
{
    int now,ans=0;
    if(x>dep) return 1;
    for(int i=0;i<=5;i++)
    {
        now=d[i];
        if((now==1&&(flag||sum[2]||sum[3]||sum[4]>1||sum[5]>1))||s*10+now>top) continue;
        if(push(now,x-1))
        {
            sum[i]++;
            if(now==1) ans+=f(x+1,dep,1,s*10+now,top);
            else ans+=f(x+1,dep,flag,s*10+now,top);
            sum[i]--;
        }
    }
    return ans;
}
int main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    int t,l,r;
    pre(),scanf("%d",&t);
    for(int w=1;w<=t;w++)
    {
        scanf("%d%d",&l,&r);
        printf("%d",(f(1,pan(r),0,0,r)-f(1,pan(l-1),0,0,l-1))%mod);
    }
    return 0;
}