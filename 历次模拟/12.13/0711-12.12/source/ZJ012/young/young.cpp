#include<bits/stdc++.h>
using namespace std;typedef long long ll;
const int maxn=15,mod=998244353;
int n,m,a[maxn],b[maxn],q,k;map<vector<int>,int>mp1,mp2;
int main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)scanf("%d",b+i);
    vector<int>v1(maxn,0),v2(maxn,0);
    for(int i=0;i<n;i++)v1[i]=a[i+1];
    for(int i=0;i<m;i++)v2[i]=b[i+1];
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&k);mp1[v1]=1;
        while(k--)
        {
            for(auto t:mp1)
            {
                vector<int>zt=t.first;int v=t.second;
                for(int j=0;j<zt.size();j++)
                {
                    if((!j)||zt[j-1]>zt[j])
                    {
                        zt[j]++;
                        mp2[zt]=(mp2[zt]+v)%mod;
                        zt[j]--;
                    }
                    if(zt[j]>0&&(j==zt.size()-1||zt[j+1]<zt[j]))
                    {
                        zt[j]--;
                        mp2[zt]=(mp2[zt]+v)%mod;
                        zt[j]++;
                    }
                }
            }
            mp1=mp2,mp2.clear();
        }
        printf("%d\n",mp1[v2]);
    }
    return 0;
}
/*
10
10 9 8 7 6 5 4 3 2 1
10
10 9 8 7 6 5 4 3 2 1
1
10
*/