#include<bits/stdc++.h>
#define mid (l+r)/2
#define N 1000001
using namespace std;
int n,r,g,b,rr,gg,bb,m,u[N],v[N],fa[N],cnt;
pair<int,int> ji[N];
int ans[N];
char op[N],z[2];
queue<int> dl,dl2;
int getf(int u){
    ++cnt;
    if(fa[u]==u)return u;
    return getf(fa[u]);
}
int merge(int u,int v){
    int fa1=getf(u);
    int fa2=getf(v);
    if(fa1==fa2)return 0;
    return 1;
}
pair<int,int> merge2(int u,int v){
    int fa1=getf(u);
    int fa2=getf(v);
    fa[fa1]=fa2;
    return make_pair(fa1,fa2);
}
int dfs(char a,int w){
    for(int i=1;i<=m;i++){
        ++cnt;
        if(ans[i]==1||op[i]==a||!merge(u[i],v[i]))continue;
        if(op[i]=='b'){
            if(bb+1<=b+w&&b!=0){
                ans[i]=1;
                ji[i]=merge2(u[i],v[i]);
                bb++;
                return 1;
            }
        }else if(op[i]=='g'){
            if(gg+1<=g+w){
                ans[i]=1;
                ji[i]=merge2(u[i],v[i]);
                gg++;
                return 1;
            }
        }else if(op[i]=='r'){
            if(rr+1<=r+w){
                ans[i]=1;
                ji[i]=merge2(u[i],v[i]);
                rr++;
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    cin>>r>>g>>b>>m;
    n=r+g+b+1;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%s",&u[i],&v[i],&z);
        op[i]=z[0];
        dl.push(i);
    }
    while(!dl.empty()){
        int x=dl.front();
        dl.pop();
        if(!merge(u[x],v[x]))continue;
        if(op[x]=='r'&&rr<r){
            ji[x]=merge2(u[x],v[x]);
            rr++;
            ans[x]=1;
        }else if(op[x]=='b'&&bb<b){
            ji[x]=merge2(u[x],v[x]);
            bb++;
            ans[x]=1;
        }else if(op[x]=='g'&&gg<g){
            ji[x]=merge2(u[x],v[x]);
            gg++;
            ans[x]=1;
        }else{
            dl2.push(x);
        }
    }
    while(!dl2.empty()){
        int x=dl2.front();
        dl2.pop();
        if(!merge(u[x],v[x]))continue;
        if(op[x]=='b'&&b==0)continue;
        ji[x]=merge2(u[x],v[x]);
        if(op[x]=='b')bb++;
        if(op[x]=='g')gg++;
        if(op[x]=='r')rr++;
    }
    for(int t=4;t>=0;t--){
        for(int i=1;i<=m;i++){
            if(rr==r&&gg==g&&bb==b)break;
            if(cnt>3e8)break;
            if(ans[i]==0)continue;
            int x=i;
            if(op[i]=='g'&&gg>g){
                fa[ji[i].first]=ji[i].first;
                if(dfs(op[i],t)){
                    ans[i]=0;
                    gg--;
                }else{
                    fa[ji[i].first]=ji[i].second;
                }
            }else if(op[i]=='b'&&bb>b){
                fa[ji[i].first]=ji[i].first;
                if(dfs(op[i],t)){
                    ans[i]=0;
                    bb--;
                }else{
                    fa[ji[i].first]=ji[i].second;
                }
            }else if(op[i]=='r'&&rr>r){
                fa[ji[i].first]=ji[i].first;
                if(dfs(op[x],t)){
                    ans[i]=0;
                    rr--;
                }else{
                    fa[ji[i].first]=ji[i].second;
                }
            }
        }
    }
    if(rr==r&&gg==g&&bb==b){
        cout<<"YES"<<endl;
        for(int i=1;i<=m;i++){
            printf("%d",ans[i]);
        }
    }else{
        printf("NO\n");
    }
    return 0;
}
