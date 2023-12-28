#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10,n=4;
int m;
vector<pii>ans,path[10][4];
inline bool inside(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
inline void pushin_A1(pii cod)
{
    int x=1,y=cod.second;
    vector<pii>tmp=(vector<pii>){{x+2,y+1},{x+0,y+2},{x+1,y+0},{x+3,y+1},{x+1,y+2},{x+3,y+3}};
    ans.insert(ans.end(),tmp.begin(),tmp.end());
}
inline void pushin_A2(pii cod)
{
    int x=1,y=cod.second;
    vector<pii>tmp=(vector<pii>){{x+1,y+1},{x+3,y+2},{x+2,y+0},{x+0,y+1},{x+2,y+2},{x+0,y+3}};
    ans.insert(ans.end(),tmp.begin(),tmp.end());
}
inline void pushin_B1(pii cod)
{
    int x=1,y=cod.second-2;
    vector<pii>tmp=(vector<pii>){{x+3,y+1},{x+1,y+0},{x+0,y+2},{x+2,y+1},{x+0,y+0},{x+2,y-1}};
    ans.insert(ans.end(),tmp.begin(),tmp.end());
}
inline void pushin_B2(pii cod)
{
    int x=1,y=cod.second-2;
    vector<pii>tmp=(vector<pii>){{x+0,y+1},{x+2,y+0},{x+3,y+2},{x+1,y+1},{x+3,y+0},{x+1,y-1}};
    ans.insert(ans.end(),tmp.begin(),tmp.end());
}
inline void constr(int k,int opt,int Dx,int Dy,pii cod){for(auto [x,y]:path[k][opt]) if(pii(x+Dx,y+Dy)!=cod) ans.push_back(pii(x+Dx,y+Dy));}
inline void solve()
{
    cin>>m;
    if(m<3 || m==4) return cout<<"No\n",void(); else cout<<"Yes\n";
    pii cod(1,1);ans.push_back(cod); int cnt=0,k=m;
    while(k>7){ cnt++,k-=3; if(cod.first==1) pushin_A1(cod),cod=ans.back(); else pushin_A2(cod),cod=ans.back(); }
    int tx=cod.first,ty=cod.second;
    if(tx==1) constr(k,1,0,ty-1,cod),cod=pii(2,ty-1); else constr(k,4,0,ty-1,cod),cod=pii(3,ty-1);
    if(inside(cod.first,cod.second)) ans.push_back(cod);
    while(cnt--){ if(cod.first==2) pushin_B1(cod),cod=ans.back(); else pushin_B2(cod),cod=ans.back(); }
    for(auto [x,y]:ans) if(inside(x,y)) cout<<x<<" "<<y<<'\n'; ans.clear();
}
signed main()
{
    freopen("horse.in","r",stdin),freopen("horse.out","w",stdout); 
    path[3][1]=(vector<pii>){{1,1},{3,2},{1,3},{2,1},{4,2},{2,3},{3,1},{1,2},{3,3},{4,1},{2,2},{4,3}};
    path[5][1]=(vector<pii>){{1,1},{2,3},{1,5},{3,4},{4,2},{2,1},{1,3},{2,5},{4,4},{3,2},{2,4},{4,5},{3,3},{1,2},{3,1},{4,3},{3,5},{1,4},{2,2},{4,1}};
    path[6][1]=(vector<pii>){{1,1},{2,3},{1,5},{3,6},{4,4},{3,2},{1,3},{2,5},{4,6},{3,4},{4,2},{2,1},{3,3},{4,5},{2,6},{1,4},{3,5},{1,6},{2,4},{1,2},{3,1},{4,3},{2,2},{4,1}};
    path[7][1]=(vector<pii>){{1,1},{2,3},{1,5},{2,7},{4,6},{3,4},{4,2},{2,1},{1,3},{2,5},{1,7},{3,6},{4,4},{3,2},{2,4},{1,6},{3,7},{4,5},{3,3},{1,2},{3,1},{4,3},{3,5},{4,7},{2,6},{1,4},{2,2},{4,1}};
    path[5][4]=(vector<pii>){{4,1},{3,3},{4,5},{2,4},{1,2},{3,1},{4,3},{3,5},{1,4},{2,2},{3,4},{1,5},{2,3},{4,2},{2,1},{1,3},{2,5},{4,4},{3,2},{1,1}};
    path[6][4]=(vector<pii>){{4,1},{3,3},{4,5},{2,6},{1,4},{2,2},{4,3},{3,5},{1,6},{2,4},{1,2},{3,1},{2,3},{1,5},{3,6},{4,4},{2,5},{4,6},{3,4},{4,2},{2,1},{1,3},{3,2},{1,1}};
    path[7][4]=(vector<pii>){{4,1},{2,2},{4,3},{2,4},{4,5},{3,7},{1,6},{3,5},{4,7},{2,6},{1,4},{3,3},{1,2},{3,1},{2,3},{4,4},{2,5},{1,7},{3,6},{1,5},{2,7},{4,6},{3,4},{4,2},{2,1},{1,3},{3,2},{1,1}};
    ios::sync_with_stdio(false);cin.tie(NULL);int T;cin>>T;while(T--)solve();
}
