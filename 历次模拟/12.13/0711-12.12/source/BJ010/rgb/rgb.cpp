#include <bits/stdc++.h>

using namespace std;

const int maxn=250000; 

int r,g,b,m,n; 
struct edge {
    int u,v,w,o,id; 
} E[maxn+5]; 
int fa[maxn+5],need[3],nwans[maxn+5]; 

int find(int x) {
    return fa[x]==x?x:fa[x]=find(fa[x]); 
}
int main() {
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout); 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>r>>g>>b>>m;
    n=r+g+b+1; 
    need[0]=r;
    need[1]=g;
    need[2]=b; 
    int cnt[3]={}; 
    for (int i=1;i<=m;i++) {
        int u,v;
        char c;
        cin>>u>>v>>c;
        E[i].id=i;
        E[i].u=u,E[i].v=v; 
        if (c=='r') {
            E[i].o=0; 
        } else if (c=='b') {
            E[i].o=1; 
        } else {
            E[i].o=2; 
        }
        cnt[E[i].o]++; 
    }
    if (cnt[0]<need[0] || cnt[1]<need[1] || cnt[2]<need[2]) {
        cout<<"NO\n";
        return 0; 
    } 
    int L=-250,R=250; 
    while (L<=R) {
        int val1=(L+R)>>1;
        int l=-250,r=250,val2=-1e9;
        while (l<=r) {
            int mid=(l+r)>>1;
            for (int i=1;i<=m;i++) {
                if (E[i].o==0) {
                    E[i].w=val1; 
                } else if (E[i].o==1) {
                    E[i].w=mid; 
                } else if (E[i].o==2) {
                    E[i].w=0;
                }
            }
            sort(E+1,E+m+1,[&](edge x,edge y) {
                return x.w==y.w?(x.o==1)>(y.o==1):x.w<y.w; 
            });
            for (int i=1;i<=n;i++) {
                fa[i]=i; 
            }
            int cnt=0; 
            for (int i=1;i<=m;i++) {
                int u=E[i].u,v=E[i].v,o=E[i].o,id=E[i].id; 
                int fu=find(u),fv=find(v);
                if (fu==fv) continue ;
                fa[fu]=fv;
                cnt+=(o==1);                    
            }
            if (cnt>=g) {
                val2=mid;
                l=mid+1;
            } else r=mid-1; 
        } 
        if (val2==-1e9) {
            R=val1-1;
            continue ;  
        }
        for (int i=1;i<=m;i++) {
            if (E[i].o==0) {
                E[i].w=val1; 
            } else if (E[i].o==1) {
                E[i].w=val2; 
            } else if (E[i].o==2) {
                E[i].w=0;
            }
        }
        int id[3]={},mx=0;
        for (int i=0;i<3;i++) id[i]=i;
        do {
            sort(E+1,E+m+1,[&](edge x,edge y) {
                return x.w==y.w?id[x.o]<id[y.o]:x.w<y.w; 
            });
            for (int i=1;i<=m;i++) {
                nwans[i]=0; 
            }
            int cnt=0;
            int num[3]={}; 
            for (int i=1;i<=n;i++) fa[i]=i; 
            for (int i=1;i<=m;i++) {
                int u=E[i].u,v=E[i].v,o=E[i].o,id=E[i].id; 
                int fu=find(u),fv=find(v);
                if (fu==fv) continue ;
                if (num[o]==need[o]) continue ; 
                fa[fu]=fv;
                cnt++;
                num[o]++;   
                nwans[id]=1;                    
            }
            mx=max(mx,num[0]);
            if (cnt==n-1) {
                cout<<"YES\n"; 
                for (int i=1;i<=m;i++) {
                    cout<<nwans[i]; 
                }
                cout<<'\n';
                return 0;
            }
        } while (next_permutation(id,id+3)); 
        if (mx>=r) {
            R=val1-1; 
        } else L=val1+1; 
    } 
    cout<<"NO\n"; 
    return 0; 
}