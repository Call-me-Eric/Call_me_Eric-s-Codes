#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, m, q;
int a[maxn], d[maxn];
struct Segment_Tree{
    struct node{
        int sum0, sum1;
        int siz0, siz1;
        int revtag;
        node(int sum0 = 0,int sum1 = 0,int siz0 = 0,int siz1 = 0,int tag = 0)
        :sum0(sum0),sum1(sum1),siz0(siz0),siz1(siz1),revtag(revtag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum0 + r.sum0,l.sum1 + r.sum1,l.siz0 + r.siz0,l.siz1 + r.siz1);}
    void change(int p){
        swap(d[p].siz0,d[p].siz1);
        swap(d[p].sum0,d[p].sum1);
    }
    void pushdown(int p){
        if(d[p].revtag){
            change(p << 1);change(p << 1 | 1);
            d[p << 1].revtag ^= 1;d[p << 1 | 1].revtag ^= 1;
            d[p].revtag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){
            int tmp = ::d[l] > 0;
            d[p] = node(!tmp * a[l],tmp * a[l],!tmp,tmp,0);
            return;
        }
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){d[p].revtag ^= 1;change(p);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int s,int t){update(1,n,s,t,1);}
    node query(int l,int r){
        if(l > r)return node();
        return query(1,n,l,r,1);
    }
    int queryl(int l,int r,int p,int pos){
        if(l == r)return l;
        int mid = l + r >> 1;pushdown(p);
        if(d[p << 1].siz1 >= pos)return queryl(l,mid,p << 1,pos);
        else return queryl(mid + 1,r,p << 1 | 1,pos - d[p << 1].siz1);
    }
    pair<int,int> queryl(int r,int pos){//找两个l_1,l，使siz1[l,r] = pos,siz1[l_1,r] = pos + 1
        int tot = query(1,n,1,r,1).siz1;
        pos = tot - pos + 1;//现在是找[1,l],siz1[1,l_1]=pos-1,siz1[1,l]=pos;
        return make_pair(queryl(1,n,1,pos - 1),queryl(1,n,1,pos));
    }
    int queryr(int l,int r,int p,int pos){
        if(l == r)return l;
        int mid = l + r >> 1;pushdown(p);
        if(d[p << 1 | 1].siz0 >= pos)return queryr(mid + 1,r,p << 1 | 1,pos);
        else return queryr(l,mid,p << 1,pos - d[p << 1 | 1].siz0);
    }
    pair<int,int> queryr(int l,int pos){//找两个r_1,r，使siz0[l,r] = pos,siz0[l,r_1] = pos + 1
        int tot = query(1,n,l,n,1).siz0;
        pos = tot - pos + 1;//现在是找[r,n],siz0[r_1,n]=pos-1,siz0[r,n]=pos;
        return make_pair(queryr(1,n,1,pos - 1),queryr(1,n,1,pos));
    }
}tree;
signed main(){
    freopen("observe.in","r",stdin);
    freopen("observe.out","w",stdout);
    n = read(); m = read(); q = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)d[i] = read();
    if(n >= 3000){
    tree.build(1,n,1);
    while(q--){
        int opt = read(), l = read(), r = read();
        int ll = lower_bound(a + 1,a + 1 + n,l) - a - 1;
        int rr = lower_bound(a + 1,a + 1 + n,r) - a - 1;
        while(a[ll] <= l && ll != n)ll++;
        while(a[rr] >= r && rr != 1)rr--;
        // printf("%lld %lld %lld %lld\n",l,a[ll],a[rr],r);
        if(opt == 1){tree.update(l,r);}
        if(opt == 2){
            int sum = 0;
            if(ll <= rr){
                Segment_Tree::node tmp = tree.query(ll,rr);
                sum = (r * tmp.siz1 - tmp.sum1) + (tmp.sum0 - l * tmp.siz0);
            }
            printf("%lld\n",sum);
        }
        if(opt == 3){
            int x = read();
            if((a[x] <= l) || (a[x] >= r) || ll > rr){puts("0");continue;}
            //0 = left, 1 = right
            Segment_Tree::node tmp = tree.query(ll,rr);
            int siz0 = tree.query(x + 1,rr).siz0, siz1 = tree.query(ll,x - 1).siz1;
            opt = tree.query(x,x).siz1;int len = 0, L = 0, R = 0, sum = 0;
            if(opt){
                if(siz1 >= siz0){
                    len = siz0;L = tree.queryl(x - 1,len).second;
                    sum = r - a[L];
                }
                else{
                    len = siz1;R = tree.queryr(x + 1,len).first;
                    sum = a[R] - l;
                }
            }
            else{
                if(siz0 >= siz1){
                    len = siz1; R = tree.queryr(x + 1,len).second;
                    sum = a[R] - l;
                }
                else{
                    len = siz0; L = tree.queryl(x - 1,len).first;
                    sum = r - a[L];
                }
            }
            printf("%lld\n",sum);
        }
    }
    }
    else{
        
    while(q--){
        int opt = read(), l = read(), r = read();
        if(opt == 1){for(int i = l;i <= r;i++)d[i] = -d[i];}
        if(opt == 2){
            int sum = 0;
            for(int i = 1;i <= n;i++)
                if(a[i] < r && l < a[i]){
                    if(d[i] < 0)sum += a[i] - l;
                    else sum += r - a[i];
                }
            printf("%lld\n",sum);
        }
        if(opt == 3){
            int x = read();vector<int> vec[2];
            // printf("(%lld,%lld), a[%lld] = %lld,%d\n",l,r,x,a[x],(a[x] <= l || a[x] >= r));
            if((a[x] <= l) || (a[x] >= r)){puts("0");continue;}
            //0 = left, 1 = right
            for(int i = x + 1;i <= n;i++){
                if(d[i] < 0 && a[i] < r){vec[0].push_back(a[i]);}
                if(a[i] >= r)break;
            }
            for(int i = x - 1;i;i--){
                if(d[i] > 0 && a[i] > l){vec[1].push_back(a[i]);}
                if(a[i] <= l)break;
            }
            opt = d[x] > 0;int len = 0, L = 0, R = 0, sum = 0;
            if(opt){
                if(vec[1].size() >= vec[0].size()){
                    len = vec[0].size();
                    L = vec[1][len - 1];R = vec[0][len - 1];
                    sum = r - L;
                }
                else{
                    len = vec[1].size();
                    L = vec[1][len - 1];R = vec[0][len];
                    sum = R - l;
                }
            }
            else{
                if(vec[0].size() >= vec[1].size()){
                    len = vec[1].size();
                    R = vec[0][len - 1];L = vec[1][len - 1];
                    sum = R - l;
                }
                else{
                    len = vec[0].size();
                    R = vec[0][len - 1];L = vec[1][len];
                    sum = r - L;
                }
            }
            printf("%lld\n",sum);
        }
    }
    }
    return 0;
}