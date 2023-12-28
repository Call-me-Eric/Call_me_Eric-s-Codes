// #include<iostream>
// #include<stack>
// #include<queue>
// #include<vector>
// #include<algorithm>
// #include<map>
// #include<set>
// #include<ctime>
// #include<cstdio>
// #include<cmath>
// #include<cstdlib>
// #include<cstring>
#define ll long long
#define inf 0x3f3f3f3f
#define fi first
#define se second
#define Max 120
#include<bits/stdc++.h>
// #define local
#define eps 4e-13
#define fo(x,y,z) for(int x = (y);x < (z);++x)
#define rfo(x,z,y) for(int x = (y) - 1; x >= (z);--x)
using namespace std;
typedef pair<int,int> P;
int dx[] = {0,0,1,-1},dy[] = {1,-1,0,0};


ll mod = 1e9+7;
inline ll poww(ll x,ll y,ll z = mod) {
    ll ans = 1;
    while(y){
        if(y&1) ans = ans*x%z;
        y>>=1,x = x*x%z;
    }
    return ans;
}

int a[Max],b[Max];
int dp[1<<22],ma[1<<22];
int main(){
	freopen("bag.in","r",stdin);
	freopen("bag.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    fo(i,0,n)scanf("%d",&a[i]);
    fo(i,0,m)scanf("%d",&b[i]);
    sort(b,b+m,greater<int>());
    memset(dp,-1,sizeof(int) * (1<<n));
    dp[0] = b[0];
    fo(i,0,n) ma[1<<i] = i;
    int s = (1<<n) - 1;
    fo(i,0,m){
        fo(j,0,1<<n) if(dp[j] >= 0)dp[j] = b[i];
        fo(j,0,1<<n)
            if(dp[j]>0){
                int S = s&(~j);
                while(S){
                    int ne = S&(-S),z = ma[ne];
                    if(dp[j] >= a[z]) dp[j|ne] = max(dp[j|ne],dp[j] - a[z]);
                    S -= ne;
                }
            }
        if(dp[s]>=0){
            printf("%d\n",i+1);
            return 0;
        }
    }
    printf("%d\n",-1);
    return 0;
}
