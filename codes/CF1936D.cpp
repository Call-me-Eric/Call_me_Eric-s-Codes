#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10,INF = 0x3f3f3f3f3f3f3f3f, maxl = 30;
typedef pair<int,int> pii;
int n, X;int b[maxn];
int st[21][maxn], lg[maxn];
int qry(int l,int r){int k = lg[r - l + 1];return max(st[k][l],st[k][r - (1 << k) + 1]);}
struct Segment_Tree{
    struct node{
		int l[maxl],r[maxl],res;
    }d[maxn << 2];
	node mergenode(node l,node r,int mid){
        node ans;
		ans.res = min(l.res, r.res);
		int rp = 0;
        for(int i = maxl - 1,nw = 0;i + 1;i--){
			int rr = r.l[i] < INF ? qry(mid + 1,r.l[i]) : INF,
				ll = l.r[i] ? qry(l.r[i], mid) : INF;
			nw = max(min(ll,rr),rp);
			if(X & (1 << i)){
				rp = nw;
                if((1 << i) == (X & -X))ans.res = min(ans.res, nw);
			}else ans.res = min(ans.res,nw);
		}
		for(int i = 0;i < maxl;++i)
			ans.l[i] = min(r.l[i],l.l[i]),ans.r[i] = max(l.r[i],r.r[i]);
		return ans;
	}
	void initval(int p,int pos,int val){
		for(int i = 0;i < maxl;++i)
            if(val & (1 << i))d[p].l[i] = d[p].r[i] = pos;
            else d[p].l[i] = INF, d[p].r[i] = 0;
		d[p].res = val >= X ? qry(pos,pos) : INF;
	}
    void build(int l,int r,int p){
        if(l == r){initval(p,l,b[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1],mid);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r){initval(p,l,upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1],mid);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1),mid);
    }
    void update(int pos,int upd){update(1,n,pos,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
int m;
void solve(){
    n = read(); X = read();lg[0] = -1;
    for(int i = 1;i <= n;i++){st[0][i] = read();lg[i] = lg[i >> 1] + 1;}
    for(int j = 1;(1 << j) <= n;j++)for(int i = 1;i + (1 << j) - 1 <= n;i++)
        st[j][i] = max(st[j - 1][i],st[j - 1][i + (1 << j - 1)]);
    for(int i = 1;i <= n;i++)b[i] = read();
    tree.build(1,n,1);m = read();
        // cerr << "11111111\n";
    for(int i = 1;i <= m;i++){
        int opt = read(), u = read(), v = read();
        if(opt == 1){tree.update(u,v);}
        else{int ans = tree.query(u,v).res;printf("%lld ",ans >= INF ? -1ll : ans);}
    }
    puts("");
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    // freopen("tmp.in","r",stdin);
    // freopen("out.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}