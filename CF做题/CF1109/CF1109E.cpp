#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, mod, q;
int a[maxn], b[maxn];
int cnt[maxn][11];
int factor[11], tot;

int qpow(int x,int a){
    // printf("x = %lld a = %lld\n",x,a);
    int res = 1;
    while(a){
        if(a & 1)res = ((long long)res * x) % mod;
        x = (long long)x * x % mod;a >>= 1;
    }
    return res;
}

struct Segment_Tree{
    struct node{
        int summ, tag, cnt[11];int leaf;
        node(int summ = 0,int tag = 1,int leaf = false):leaf(leaf)
        ,summ(summ),tag(tag){for(int i = 1;i <= tot;i++)cnt[i] = 0;}
    }d[maxn << 2];
    node mergenode(node l,node r){return node((l.summ + r.summ) % mod);}
    void change(int p,int tag,int * tmp){
        d[p].tag = ((long long)d[p].tag * tag) % mod;
        d[p].summ = ((long long)d[p].summ * tag) % mod;
        if(d[p].leaf){b[d[p].leaf] = (long long)b[d[p].leaf] * tag % mod;}
        for(int i = 1;i <= tot;i++){
            d[p].cnt[i] += tmp[i];
            d[p].summ = ((long long)d[p].summ * qpow(factor[i],tmp[i])) % mod;
        }
    }
    void pushdown(int p){
        if(!d[p].leaf){
            change(p << 1,d[p].tag,d[p].cnt);
            change(p << 1 | 1,d[p].tag,d[p].cnt);
            d[p].tag = 1;memset(d[p].cnt,0,sizeof(d[p].cnt));
        }
    }
    void build(int l,int r,int p){
        if(l == r){
            d[p].summ = a[l] % mod;d[p].leaf = l;
            for(int i = 1;i <= tot;i++)d[p].cnt[i] = cnt[l][i];
            return;
        }
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    int query(int l,int r){return query(1,n,l,r,1).summ;}
    void update(int l,int r,int s,int t,int p,int upd,int *tmp){
        if(s <= l && r <= t){change(p,upd,tmp);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd,tmp);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd,tmp);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int upd,int *tmp){update(1,n,l,r,1,upd,tmp);}
    
    void update(int l,int r,int pos,int p,int upd,int *tmp){
        if(l == r && l == pos){
            b[l] = (long long)b[l] * upd % mod;
            d[p].summ = b[l];
            for(int i = 1;i <= tot;i++){
                // printf("upd2 : pos = %lld,fac[%lld] = %lld, cnt = %lld,tmp = %lld\n",pos,i,factor[i],d[p].cnt[i],tmp[i]);
                d[p].cnt[i] += tmp[i];
                d[p].summ = (long long)d[p].summ * qpow(factor[i],d[p].cnt[i]) % mod;
            }
            return;
        }
        int mid = l + r >> 1;pushdown(p);
        if(pos <= mid)update(l,mid,pos,p << 1,upd,tmp);
        else update(mid + 1,r,pos,p << 1 | 1,upd,tmp);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int pos,int upd,int *tmp){update(1,n,pos,1,upd,tmp);}
    void print(int l,int r,int p){
        printf("l = %lld r = %lld p = %lld sum = %lld tag = %lld\n",l,r,p,d[p].summ,d[p].tag);
        for(int i = 1;i <= tot;i++)
            printf("fac = %lld,cnt = %lld%c",factor[i],d[p].cnt[i]," \n"[i == tot]);
        if(l == r)return;
        int mid = l + r >> 1;pushdown(p);
        print(l,mid,p << 1);print(mid + 1,r,p << 1 | 1);
    }
}tr;
int tmp[11];

signed main(){
    n = read(); mod = read();int x = mod, opt, l , r;
    for(int i = 2;i * i <= x;i++){
        if(x % i == 0){
            factor[++tot] = i;
            while(x % i == 0)x /= i;
        }
    }
    if(x > 1){factor[++tot] = x;}
    for(int i = 1;i <= n;i++){
        a[i] = read();x = a[i];
        for(int j = 1;j <= tot;j++)
            while(x % factor[j] == 0){
                cnt[i][j]++;x /= factor[j];
            }
        b[i] = x;
    }
    tr.build(1,n,1);q = read();
    while(q--){
        opt = read(); l = read(); r = read();
        if(opt == 1){
            memset(tmp,0,sizeof(tmp));x = read();
            // if(a[1] == 976)printf("%lld %lld %lld %lld ",opt,l,r,x);
            for(int i = 1;i <= tot;i++)
                while(x % factor[i] == 0){
                    x /= factor[i];tmp[i]++;
                }
            tr.update(l,r,x,tmp);
        }
        if(opt == 2){
            memset(tmp,0,sizeof(tmp));x = r;
            // if(a[1] == 976)printf("%lld %lld %lld ",opt,l,r);
            for(int i = 1;i <= tot;i++)
                while(x % factor[i] == 0){
                    x /= factor[i];tmp[i]--;
                }
        // tr.print(1,n,1);
            tr.update(l,qpow(x,mod - 2),tmp);
        }
        if(opt == 3){
            // if(a[1] == 976)printf("%lld %lld %lld ",opt,l,r);
            printf("%lld\n",tr.query(l,r));
        }
        // if(q % 60 == 0 && a[1] == 976)puts("");
    }
    return 0;
}
/*
100 1478
976 681 934 854 977 810 894 964 733 889 708 987 889 915 974 961 957 879 681 974 431 846 982 969 451 1000 996 955 661 912 901 521 909 924 977 851 615 888 778 892 944 640 579 870 949 975 840 985 663 990 972 923 640 703 803 798 754 774 723 936 972 970 678 456 893 1000 979 792 951 781 921 835 929 751 619 996 934 731 451 641 662 881 957 777 997 872 833 931 790 977 892 781 1000 941 878 981 863 628 634 970
501
3 37 61
2 71 307
2 23 491
2 89 1
1 22 56 930
1 92 95 950
2 95 1
2 69 1
2 96 1
2 9 733
1 3 91 499
2 7 1
2 2 227
1 19 49 889
2 52 499
2 92 1
2 7 1
3 45 75
2 14 61
2 74 1
2 81 331 
2 51 2 2 70 1 2 4 499 2 44 1 2 27 3 2 8 1 1 40 60 783 2 7 1 2 32 3 2 5 977 3 63 76 2 37 41 3 9 93 1 1 9 982 2 69 1 1 62 82 814 1 42 61 918 3 60 86 2 51 4 1 33 68 836 2 21 431 3 42 52 2 26 1 3 33 76 3 14 33 2 97 1 2 52 1 2 21 1 2 69 1 2 12 47 2 90 977 2 63 1 1 21 37 862 3 2 32 2 77 467 1 49 85 996 2 91 1 3 40 71 2 8 1 2 94 1 2 40 2...

*/