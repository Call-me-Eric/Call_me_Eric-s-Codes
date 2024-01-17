#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=2e3+5;
const int M=1e5+5;
const int inf=0x3f3f3f3f;
const int mod=998244353;
const int base=13131;
inl int read(){
    int x=0,f=1;char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();}
    return x*f;
}
inl void write(int x){
    if(x<0){pc('-');x=-x;}
    if(x>9)write(x/10);
    pc(x%10+'0');
}
inl void writei(int x){write(x);pc(' ');}
inl void writel(int x){write(x);pc('\n');}
int n(1e2),m,lst,tp;
struct segment_tree{
    int s[N<<2],tag[N];
    #define ls k<<1
    #define rs k<<1|1
    #define mid (l+r>>1)
    inl void pushup(int k){s[k]=s[ls]+s[rs];}
    inl void adt(int k,int l,int r,int v){
        s[k]=(s[k]+(r-l+1)*v%mod)%mod;tag[k]=(tag[k]+v)%mod;
    }
    inl void pushdown(int k,int l,int r){
        if(!tag[k])return;
        adt(ls,l,mid,tag[k]);adt(rs,mid+1,r,tag[k]);
        tag[k]=0;
    }
    inl void modify(int k,int l,int r,int x,int y,int v){
        if(x<=l&&r<=y)return adt(k,l,r,v);
        pushdown(k,l,r);
        if(x<=mid)modify(ls,l,mid,x,y,v);
        if(y>mid)modify(rs,mid+1,r,x,y,v);
        pushup(k);
    }
    inl int query(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y)return s[k];
        pushdown(k,l,r);int ans=0;
        if(x<=mid)ans=(ans+query(ls,l,mid,x,y))%mod;
        if(y>mid)ans=(ans+query(rs,mid+1,r,x,y))%mod;
        return ans;
    }
}SGT;
signed main(){
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    m=read();tp=read();
    while(m--){
        int op=read();
        if(op==1){
            int l=read()^lst,r=read()^lst,v=read()^lst;
            SGT.modify(1,1,n,l,r,v);
        }else if(op==2){            
            int a,b,x=read()^lst,v=read()^lst;
            for(int i=1;i*i<=n;i++){
                if(x%i)continue;
                if(x/i-i<=2){
                    a=i,b=x/i;
                    break;
                }
            }
            if(a==b){
                if(a&1){
                    SGT.modify(1,1,n,1,x,v);
                    for(int ping=a,add=a+2,lst=2*a;ping*ping+add<=n;ping+=2,add+=3,lst+=2){
                        int st=ping*ping+add,ed=min(st+lst,n);
                        SGT.modify(1,1,n,st,ed,v);
                    }
                }else{
                    SGT.modify(1,1,n,x,x+1,v);
                    for(int ping=a+1,add=a+3,lst=3;ping*ping+add<=n;ping+=2,add+=3,lst+=2){
                        int st=ping*ping+add,ed=min(st+lst,n);
                        SGT.modify(1,1,n,st,ed,v);
                    }
                }
            }
            if(b-a==1){
                if(a&1){
                    if(a^1)SGT.modify(1,1,n,(a-2)*(a-2)+a-1,(a-2)*(a-2)+2*a-2,v);
                    else SGT.modify(1,1,n,1,1,v);
                    SGT.modify(1,1,n,x,x,v);
                    for(int ping=a,add=a+1,lst=a+2;ping*ping+add<=n;ping+=2,add+=3,lst+=2){
                        int st=ping*ping+add,ed=min(st+lst,n);
                        SGT.modify(1,1,n,st,ed,v);
                    }
                }else{
                    SGT.modify(1,1,n,x-1,x,v);
                    for(int ping=b,add=b*2+1,lst=3;ping*ping+add<=n;ping+=2,add+=3,lst+=2){
                        int st=ping*ping+add,ed=min(st+lst,n);
                        SGT.modify(1,1,n,st,ed,v);
                    }
                }
            }
            if(b-a==2){
                if(a&1){
                    SGT.modify(1,1,n,x,x+2,v);
                    for(int ping=b,add=2*b-1,lst=4;ping*ping+add<=n;ping+=2,add+=3,lst+=2){
                        int st=ping*ping+add,ed=min(st+lst,n);
                        SGT.modify(1,1,n,st,ed,v);
                    }
                }else{
                    SGT.modify(1,1,n,1,(a-1)*(a-1),v);
                    SGT.modify(1,1,n,x-a+2,x,v);
                    for(int ping=a-1,add=a+1,lst=2*a-1;ping*ping+add<=n;ping+=2,add+=3,lst+=2){
                        int st=ping*ping+add,ed=min(st+lst,n);
                        SGT.modify(1,1,n,st,ed,v);
                    }
                }
            }
        }else{
            int l=read()^lst,r=read()^lst;
            int x=SGT.query(1,1,n,l,r);
            if(tp)lst=x;
            cout<<x<<endl;
        }
    }
    return 0;
}