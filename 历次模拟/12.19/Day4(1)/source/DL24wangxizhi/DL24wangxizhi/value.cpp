#include <bits/stdc++.h>
#define int long long
using namespace std;


const int maxn=1.5e5+10,inf=0x3f3f3f3f;

int n,ans;
struct node{int a,b;}t[maxn];

namespace subtask1
{
    vector<int>lsh;
    int rg;
    inline void solve()
    {
        for(int i=1;i<=n;i++) lsh.push_back(t[i].a),lsh.push_back(t[i].b);
        sort(lsh.begin(),lsh.end());
        lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
        rg=lsh.size();
        set<int>s;
        int pos=1,num=0;
        for(auto v:lsh)
        {
            ++num;
            int len=0,res=0,idx=0;
            for(auto x:s) res=max(res,(pos-1-idx)*x),idx++;
            while(pos<=n && t[pos].a==v) s.insert(t[pos].b),pos++,len++;
            if(!len) continue;
            int suma=(n-pos+1+len)*v;
            ans=max(ans,res+suma);
        }
        cout<<ans<<endl;
    }
}
namespace subtask2
{
    vector<int>lsh;
    inline int check(int x)
    {
        int cnt=0;
        vector<int>vec;
        for(int i=1;i<=n;i++)
            if(t[i].a>=lsh[x]) cnt++;
            else vec.push_back(t[i].b);
        sort(vec.begin(),vec.end(),greater<int>());
        int idx=0,res=0;
        for(auto v:vec) idx++,res=max(res,idx*v);
        res+=cnt*lsh[x];
        ans=max(ans,res);
        return res;
    }
    inline void solve()
    {
        cin>>n;
        lsh.push_back(-1);
        for(int i=1;i<=n;i++) lsh.push_back(t[i].a);
        sort(lsh.begin(),lsh.end());
        lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
        int l=1,r=(int)lsh.size()-1;
        while(l+5<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid)<=check(mid+1)) l=mid;
            else r=mid+1; 
        }
        for(int i=l;i<=r;i++) check(i);
        cout<<ans<<endl;
    }
}
inline void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i].a>>t[i].b;
    sort(t+1,t+n+1,[](const node&A,const node&B){return A.a<B.a;});
    if(n<=3000) subtask1::solve();
    else subtask2::solve();
}
signed main()
{
    freopen("value.in","r",stdin);
    freopen("value.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}