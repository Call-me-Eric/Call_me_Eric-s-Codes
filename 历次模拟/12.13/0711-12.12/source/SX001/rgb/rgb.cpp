#include<bits/stdc++.h>
#define int long long 
using namespace std;
int num;
int n,m;
int r,g,b;
int fa[255];
bool bb[550005];
bool a[25];
int hd[255];
bool qw[255];
char c;
int u,v;
bool bl;
vector<int>xl;
struct P{
    int nxt,to;
    char tp;
}line[600005];
inline void add(int x,int y,char ch){
    ++num;
    line[num].nxt=hd[x];
    line[num].to=y;
    line[num].tp=ch;
    hd[x]=num;
    return ;
}
int find(int x){
    return (fa[x]==x?x:fa[x]=find(fa[x]));
}
void dfs(int t){
    if(bl)return ;
    if(t==m+1){
        int bll=0;
        int rn=0,gn=0,bn=0;
        for(int i=1;i<=m;++i)bll+=a[i];
        if(bll!=n-1)return ;
        for(int i=1;i<=n;++i)fa[i]=i;
        for(int i=1;i<=m;++i){
            if(!a[i])continue;
            int fx=find(line[i*2].to),fy=find(line[i*2+1].to);
            if(fx==fy)return ;
            if(line[i*2].tp=='r')++rn;
            else if(line[i*2].tp=='g')++gn;
            else ++bn;
            fa[fx]=fy;
        }
        if(rn!=r or gn!=g or bn!=b)return;
        bl=1;
        for(int i=1;i<=m;++i)bb[i]=a[i];
        return ;
    }
    a[t]=1;
    dfs(t+1);
    a[t]=0;
    dfs(t+1);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    cin>>r>>g>>b>>m;
    num=1;
    n=r+g+b+1;
    for(int i=1;i<=m;++i){
        cin>>u>>v>>c;
        add(u,v,c);
        add(v,u,c);
    }
    if(n<=5){
        dfs(1);
        if(!bl){cout<<"NO"<<'\n';return 0;}
        cout<<"YES"<<'\n';
        for(int i=1;i<=m;++i)cout<<bb[i];
        cout<<'\n';
        return 0;
    }
    if(m<n*(n-1)/20 or (g<=10 and g<(n-1)/3)){cout<<"NO"<<'\n';return 0;}
    xl.push_back(1);
    qw[1]=1;
    for(int i=1;i<=r;++i){
        for(auto x:xl){
            bool bl=0;
            for(int i=hd[x];i;i=line[i].nxt){
                int to=line[i].to;
                if(qw[to])continue;
                if(line[i].tp=='r'){xl.push_back(to);bl=1;qw[to]=1;bb[i/2]=1;break;}
            }
            if(bl)break;
        }
    }
    for(int i=1;i<=b;++i){
        for(auto x:xl){
            bool bl=0;
            for(int i=hd[x];i;i=line[i].nxt){
                int to=line[i].to;
                if(qw[to])continue;
                if(line[i].tp=='b'){xl.push_back(to);bl=1;qw[to]=1;bb[i/2]=1;break;}
            }
            if(bl)break;
        }
    }
    for(int i=1;i<=g;++i){
        for(int x=1;x<=n;++x){
            if(qw[x])continue;
            bool bl=0;
            for(int i=hd[x];i;i=line[i].nxt){
                int to=line[i].to;
                if(!qw[to])continue;
                if(line[i].tp=='g'){xl.push_back(to);bl=1;qw[x]=1;bb[i/2]=1;break;}
            }
            if(bl)break;
        }
    }
    int qwe=0;
    cout<<"YES"<<'\n';
    for(int i=1;i<=m;++i)cout<<bb[i],qwe+=bb[i];
    if(qwe!=n-1)cerr<<"WA!!"<<'\n';
    else{
        for(int i=1;i<=n;++i)fa[i]=i;
        int rn=0,gn=0,bn=0;
        for(int i=1;i<=m;++i){
            if(bb[i]){
                int fx=find(line[i*2].to),fy=find(line[i*2+1].to);
                if(fx==fy){cerr<<"WA!!!"<<' '<<i<<'\n';return 0;}
                fa[fx]=fy;
                if(line[i*2].tp=='r')++rn;else if(line[i*2].tp=='g')++gn;else ++bn;
            }
        }
        if(rn!=r or gn!=g or bn!=b)cerr<<"WA!!!!"<<'\n';
        else cerr<<"AC!!"<<"\n";
    }
    cout<<'\n';
    return 0;
}
