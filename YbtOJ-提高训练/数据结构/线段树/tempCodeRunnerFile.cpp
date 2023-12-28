#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 100100;
char ch[maxn];
int book[30];
class Segment_tree{
    #define L(x) (x << 1)
    #define R(x) ((x << 1) | 1)
    private:
    int tr[maxn * 4];
    void pushup(int p){if(tr[L(p)] == tr[R(p)]) tr[p] = tr[L(p)];}
    void pushdown1(int p){if(tr[p])tr[L(p)] = tr[R(p)] = tr[p];}
    void pushdown2(int p){if(tr[p])tr[L(p)] = tr[R(p)] = tr[p];tr[p] = 0;}
    void build(int l,int r,int p){
        if(l == r){tr[p] = ch[l] - 'a' + 1;return;}
        int mid = (l + r) >> 1;
        build(l,mid,L(p)); build(mid + 1,r,R(p));
        pushup(p);
    }
    void print(int l,int r,int p){
        if(tr[p]){for(int i = l;i <= r;i++)putchar(tr[p] + 'a' - 1);return;}
        int mid = (l + r) >> 1;
        print(l,mid,L(p));print(mid + 1,r,R(p));
    }
    void query(int s,int t,int l,int r,int p){
        if(t < l || r < s)return;
        if(l <= s && t <= r && tr[p]){book[tr[p]] += t - s + 1;return;}
        int mid = (s + t) >> 1; pushdown1(p);
        query(s,mid,l,r,L(p)); query(mid + 1,t,l,r,R(p));
    }
    void update(int s,int t,int l,int r,int p,int v){
        if(t < l || r < s)return;
        if((l <= s && t <= r) || tr[p] == v){tr[p] = v;return;}
        int mid = (s + t) >> 1; pushdown2(p);
        update(s,mid,l,r,L(p),v); update(mid + 1,t,l,r,R(p),v);pushup(p);
    }
    public:
    void build(int n){build(1,n,1);}
    void update(int l,int r,int i){update(1,n,l,r,1,i);}
    void query(int l,int r){query(1,n,l,r,1);}
    void print(int n){print(1,n,1);puts("");}
}tree;
signed main(){
    int l, r, x;
    scanf("%d%d",&n,&m);
    scanf("%s",ch + 1);
    tree.build(n);
    tree.print(n);
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&l,&r,&x);
        memset(book,0,sizeof(book)); tree.query(l,r);
        if(x)for(int i = 1;i <= 26;i++){tree.update(l,l + book[i] - 1,i);l += book[i];}
        else for(int i = 26;i;i--){tree.update(l,l + book[i] - 1,i);l += book[i];}
        tree.print(n);
    }
    tree.print(n);
    return 0;
}