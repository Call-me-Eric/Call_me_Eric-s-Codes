#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=double;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
    T x=0,f=0;char c=getchar();
    while(!isdigit(c)) f|=(c=='-'),c=getchar();
    while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
    return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int N=110,MX=1e6;
const db pi=acos(-1);

int n;
struct vec{
    db x,y;
    vec operator+ (const vec &rhs) const{
        return {x+rhs.x,y+rhs.y};
    }
};

vec p[N];
map<pii,vi> mp;
i64 res[N];

int to_int(db x){
    return round(x*MX);
}

int main(){
    n=rdi();

    memset(res,-1,sizeof(res));
    for(int i=0;i<n;i++)
        p[i]={cos(2*pi*i/n),sin(2*pi*i/n)};

    int mid=n/2;
    for(int i=0;i<(1<<mid);i++){
        vec sum{0,0};
        for(int j=0;j<mid;j++)
            if(i>>j&1) sum=sum+p[j];
        mp[{to_int(sum.x),to_int(sum.y)}].pb(i);
    }
    for(int i=0;i<(1<<(n-mid));i++){
        vec sum{0,0};
        for(int j=0;j<n-mid;j++)
            if(i>>j&1) sum=sum+p[j+mid];
        auto it=mp.find({-to_int(sum.x),-to_int(sum.y)});
        if(it!=mp.end()){
            for(auto j:it->se){
                i64 stat=(i64)i<<mid|j;
                int c=__builtin_popcountll(stat);
                if(!~res[c]) res[c]=stat;
            }
        }
    }
    for(int i=0;i<=n;i++)
        if(res[i]!=-1){
            printf("%2d: ",i);
            for(int j=0;j<n;j++)
                cout<<(res[i]>>j&1);
            cout<<'\n';
        }
    return 0;
}
