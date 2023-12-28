#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
int n,m,q;
const int p=998244353;
vector<int>a,b;
unordered_map<ll,int>mem;
int ans=0;
inline ll gethasa(){
    ll re=0;
    for(int i=0;i<a.size();++i){
        re=re*7+a[i];
    }
    re=re*11771+a.size();
    return re;
}
inline ll gethasb(){
    ll re=0;
    for(int i=0;i<b.size();++i){
        re=re*7+b[i];
    }
    re=re*11771+b.size();
    return re;
}
inline void dfsa(int k){
    if(k==0){
        ll sum=gethasa();
        mem[sum]++;
        // for(int i:a) printf("%d ",i);
        // printf("\n");
        return;
    }
    for(int i=0;i<a.size();++i){
        if(i==0||a[i]+1/<=a[i-1]){
            a[i]++;
            dfsa(k-1);
            a[i]--;
        }
        if(a[i]>1&&(i==a.size()-1||a[i]-1>=a[i+1])){
            a[i]--;
            dfsa(k-1);
            a[i]++;
        }
    }
    if(a[a.size()-1]==1){
        a.pop_back();
        dfsa(k-1);
        a.push_back(1);
    }
    a.push_back(1);
    dfsa(k-1);
    a.pop_back();
    return;
}
inline void dfsb(int k){
    if(k==0){
        ll sum=gethasb();
        if(mem.count(sum)) (ans+=mem[sum])%=p;
        return;
    }
    for(int i=0;i<b.size();++i){
        if(i==0||b[i]+1<=b[i-1]){
            b[i]++;
            dfsb(k-1);
            b[i]--;
        }
        if(b[i]>1&&(i==b.size()-1||b[i]-1>=b[i+1])){
            b[i]--;
            dfsb(k-1);
            b[i]++;
        }
    }
    if(b[b.size()-1]==1){
        b.pop_back();
        dfsb(k-1);
        b.push_back(1);
    }
    b.push_back(1);
    dfsb(k-1);
    b.pop_back();
    return;
}
int main(){
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    scanf("%d",&n);
    int x;
    for(int i=1;i<=n;++i){
        scanf("%d",&x);
        a.push_back(x);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i){
        scanf("%d",&x);
        b.push_back(x);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
        mem.clear();
        ans=0;
        scanf("%d",&x);
        // dfsa(x);
        // dfsb(0);
        dfsa(x/2);
        dfsb((x+1)/2);
        printf("%d\n",ans);
    }
    return 0;
}

