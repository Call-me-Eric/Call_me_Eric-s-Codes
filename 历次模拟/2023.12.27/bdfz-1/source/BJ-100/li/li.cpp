#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
vector<int> g[210000];
int d[210000];
bool v[210000];
ll a,b,k;
void dfs(int u,int f){
    if(v[u])return;
    v[u]=1;
    k++;
    for(int v:g[u])
        if(v!=f)dfs(v,u);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        d[u]++;
        d[v]++;
    }
    for(int i=1;i<=n;i++){
        if(d[i]>3){
            cout<<"-1";
            return 0;
        }
        if(d[i]==3){
            v[i]=1;
            for(int j:g[i]){
                if(d[j]>1){
                    cout<<"-1";
                    return 0;
                }
                v[j]=1;
            }
            b+=3;
        }
    }
    for(int i=1;i<=n;i++){
        if(d[i]<=1){
            k=0;
            dfs(i,0);
            a+=k*(k+1)/2;
        }
    }
    for(int i=1;i<=n;i++)
        if(!v[i])b++;
    if(!b)cout<<"0 "<<a;
    else cout<<"1 "<<b;
    return 0;
}
