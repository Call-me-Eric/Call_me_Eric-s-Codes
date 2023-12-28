#include<bits/stdc++.h>
using namespace std;typedef long long ll;
int re[26]={2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049},T,l,r;
int a[10],len[26],tmp[26][10],jd[26],d,ret;
void dfs(int dep,bool sy)
{
    if(dep>=d)return ret++,void();
    int lim=sy?9:a[dep];
    for(int i=0;i<=lim;i++)
    {
        vector<int>t(26);for(int j=0;j<26;j++)t[j]=jd[j];
        bool js=0;
        for(int j=0;j<26;j++){if(i==tmp[j][jd[j]])jd[j]++;if(jd[j]==len[j]){js=1;break;}}
        if(!js)dfs(dep+1,sy||i!=lim);
        for(int j=0;j<26;j++)jd[j]=t[j];
    }
}
int main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    for(int i=0;i<26;i++)
    {
        int t=re[i];
        while(t)
        {
            tmp[i][len[i]++]=t%10;
            t/=10;
        }
        reverse(tmp[i],tmp[i]+len[i]);
    }
    scanf("%d",&T);
    while(T--)
    {
        int l,r,ans=0;scanf("%d%d",&l,&r);l--;
        d=0;while(r)a[d++]=r%10,r/=10;
        reverse(a,a+d);
        dfs(0,0);ans+=ret;ret=0;
        d=0;while(l)a[d++]=l%10,l/=10;
        reverse(a,a+d);dfs(0,0);ans-=ret;ret=0;
        printf("%d\n",ans);
    }
    return 0;
}
//1 1 4242