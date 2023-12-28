#include <cstdio>
#include <functional>
using namespace std;

int main() {
    static const int maxn=300;
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    int n,m,C[3];
    scanf("%d %d %d %d",C,C+1,C+2,&m),n=C[0]+C[1]+C[2]+1;
    struct dsu {
        int fa[maxn];
        inline void init(const int n) {
            for(int i=1;i<=n;i++) fa[i]=i;
            return;
        }
        int find(const int u) { return u==fa[u]?u:fa[u]=find(fa[u]); }
        inline void merge(int u,int v) {
            u=find(u),v=find(v);
            if(u!=v)fa[u]=v;
            return;
        }
    };
    static dsu t[1<<3];
    static int u[maxn*maxn],v[maxn*maxn],c[maxn*maxn];
    for(int i=1;i<=m;i++) {
        scanf("%d %d",u+i,v+i);
        char ch=getchar();
        while(ch!='r'&&ch!='g'&&ch!='b')ch=getchar();
        c[i]=ch=='r'?0:ch=='g'?1:2;
        for(int s=0;s<7;s++)
            if((s>>c[i])&1)
                t[s].merge(u[i],v[i]);
    }
    for (int i=1;i<=n;i++)
        if(t[7].find(i)!=t[7].find(1)) {
            printf("NO\n");
            return 0;
        }
    static char Ans[maxn*maxn];
    for(int i=1;i<=m;i++) Ans[i]='0';
    static int bel[maxn];
    for(int i=1;i<=n;i++) bel[i]=i;
    function<int(int)> find=[&find](int u) { return u==bel[u]?u:bel[u]=find(bel[u]); };
    while (C[0]>=0&&C[1]>=0&&C[2]>=0) {
        int tot=0;
        for(int i=1;i<=m;i++) tot+=Ans[i]=='1';
        if(tot==n-1)
            break;
        bool flag=false;
        static int siz[maxn][3];
        for(auto& T:t) T.init(n);
        for(int i=1;i<=n;i++) find(i);
        for(int i=1;i<=m;i++)
            if(bel[u[i]]&&bel[v[i]])
                for(int s=0;s<7;s++)
                    if((s>>c[i])&1)
                        t[s].merge(bel[u[i]],bel[v[i]]);
        for(int i=1;i<=n;i++) siz[i][0]=siz[i][1]=siz[i][2]=0;
        for(int i=1;i<=n;i++)
            if(bel[i]==i)
                for(int j=0;j<3;j++)
                    siz[t[1<<j].find(i)][j]++;
        for(int i=1;i<=n;i++) {
            if(bel[i]!=i) continue;
            int pl=-2;
            for(int j=0;j<3;j++)
                if(siz[t[1<<j].find(i)][j]!=1) {
                    if(pl==-2) pl=j;
                    else {
                        pl=-1;
                        break;
                    }
                }
            if (pl>=0) {
                int Pl=-1;
                for(int P=1;P<=m;P++)
                    if(bel[u[P]]!=bel[v[P]]&&(bel[u[P]]==i||bel[v[P]]==i)&&c[P]==pl) {
                        Pl=P;
                        break;
                    }
                Ans[Pl]='1',C[pl]--;
                bel[bel[u[Pl]]]=bel[v[Pl]],flag=true;
                break;
            }
        }
        if(flag) continue;
        for(int x=1;x<=n&&!flag;x++)
            for(int y=x+1;y<=n&&!flag;y++)
                if(bel[x]==x&&bel[y]==y)
                    for(int i=0;i<3;i++)
                        if(t[7-(1<<i)].find(x)!=t[7-(1<<i)].find(y)&&t[1<<i].find(x)==t[1<<i].find(y)) {
                            int pl=-1;
                            for(int P=1;P<=m;P++)
                                if(((bel[u[P]]==x&&bel[v[P]]==y)||(bel[u[P]]==y&&bel[v[P]]==x))&&c[P]==i) {
                                    pl=P;
                                    break;
                                }
                            if(pl==-1) continue;
                            Ans[pl]='1',C[i]--;
                            bel[x]=y,flag=true;
                            break;
                        }
        if(flag) continue;
        static int Cnt[3];
        Cnt[0]=Cnt[1]=Cnt[2]=0;
        for(int i=1;i<=m;i++)
            if(bel[u[i]]&&bel[v[i]]&&bel[u[i]]!=bel[v[i]])
                Cnt[c[i]]++;
        for(int i=0;i<3;i++) if(!C[i]) Cnt[i]=m+10;
        int mx=max(max(C[0]-Cnt[0],C[1]-Cnt[1]),C[2]-Cnt[2]);
        for(int i=1;i<=m;i++)
            if(bel[u[i]]&&bel[v[i]]&&bel[u[i]]!=bel[v[i]]&&C[c[i]]-Cnt[c[i]]==mx) {
                Ans[i]='1',C[c[i]]--;
                bel[bel[u[i]]]=bel[v[i]],flag=true;
                break;
            }
        if(!flag) {
            printf("NO\n");
            return 0;
        }
    }
    if(C[0]<0||C[1]<0||C[2]<0) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n%s\n",Ans+1);
    return 0;
}
