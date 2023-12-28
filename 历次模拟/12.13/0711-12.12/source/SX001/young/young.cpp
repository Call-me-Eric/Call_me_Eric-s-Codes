#include<bits/stdc++.h>
#define int long long
#define abs(x) (x>0?x:-(x))
using namespace std;
int n,m;
int a[559];
int b[448];
int q,k;
map<vector<int>,int>mp[55];
vector<int>tp1,tp2;
int size;
enum :int{MOd=998244353};
stack<vector<int> >st;
int dfs(vector<int>xl,int y){
    if(mp[y].count(xl))return mp[y][xl]%MOd;
    int pr=0;
    for(int i=0;i<xl.size();++i)pr+=abs(xl[i]-tp2[i]);
    int ans=0;
    for(int i=0;i<xl.size();++i){
        vector<int>tp={};
        int q=pr-abs(xl[i]-tp2[i])+abs(xl[i]+1-tp2[i]);
        if(q<y and (i==0 or xl[i]+1<=xl[i-1])){tp=xl;++tp[i];ans+=dfs(tp,y-1);}
        q=pr-abs(xl[i]-tp2[i])+abs(xl[i]-1-tp2[i]);
        if(q<y and (i==xl.size()-1 and xl[i]-1>=0 or xl[i]-1>=xl[i+1])){tp=xl;--tp[i];ans+=dfs(tp,y-1);}
    }
    return mp[y][xl]=ans%MOd;
}
signed main(){
    ios::sync_with_stdio(0);
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    cin>>m;
    for(int j=1;j<=m;++j)cin>>b[j];
    cin>>q>>k;
    size=max(n,m)+k/2;
    tp1.clear();tp2.clear();
    for(int i=1;i<=size;++i)tp1.push_back(a[i]);
    for(int i=1;i<=size;++i)tp2.push_back(b[i]);
    mp[0][tp2]=1;
    cout<<dfs(tp1,k)<<'\n';
    return 0;
}
