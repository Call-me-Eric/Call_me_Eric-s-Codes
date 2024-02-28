#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) [](auto...){}(__VA_ARGS__)
#define debuga(...) [](auto...){}(__VA_ARGS__)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
using namespace std; typedef long long ll;
namespace FastIO{
    const int BUF_SIZ=1<<16;
    char in_buf[BUF_SIZ],*got_pos=in_buf,*read_pos=in_buf,out_buf[BUF_SIZ],*write_pos=out_buf;
    inline char get_next_char(){if(read_pos==got_pos){got_pos=read_pos=in_buf;got_pos+=fread(got_pos,sizeof(char),BUF_SIZ,stdin);}return*(read_pos++);}
    inline void flush_output(){fwrite(out_buf,sizeof(char),write_pos-out_buf,stdout);write_pos=out_buf;}
    inline void put_char(char ch){*(write_pos++)=ch;if(write_pos==out_buf+BUF_SIZ)flush_output();}
#ifndef FASTIO_READ_NEGATIVE
    template<typename T> inline void read(T& res){char ch;while(!isdigit(ch=get_next_char()));res=ch^'0';while(isdigit(ch=get_next_char()))res=(res<<3)+(res<<1)+(ch^'0');}
#else
    template<typename T> inline void read(T& res){char ch;bool flg=0;while(!isdigit(ch=get_next_char()))flg|=ch=='-';res=ch^'0';while(isdigit(ch=get_next_char()))res=(res<<3)+(res<<1)+(ch^'0');if(flg)res=-res;}
#endif
    template<typename T> inline void write(T x){if(!x){put_char('0');return;}static int lis[25],*lp=lis;while(x){*(++lp)=x%10;x/=10;}while(lp!=lis)put_char((*(lp--))+'0');}
    template<typename T> inline void writeln(const T& x){write(x);put_char('\n');}
    template<typename T> inline void writesp(const T& x){write(x);put_char(' ');}
    class _IO_Flusher{public:~_IO_Flusher(){flush_output();}}__Flusher;
    class IStream{public:
        template<typename T> inline IStream& operator>>(T& x){read(x);return *this;}
        inline IStream& operator>>(char* str){char ch;while(isspace(ch=get_next_char()));(*(str++))=ch;while(!isspace(ch=get_next_char())){if(ch==EOF)break;(*(str++))=ch;}*str=0;return *this;}
    }Cin;
    class OStream{public:
        template<typename T> inline enable_if_t<is_integral<T>::value,OStream&> operator<< (const T& x){write(x);return *this;}
        inline OStream& operator<< (const char& ch){put_char(ch);return *this;}
        inline OStream& operator<< (const char* str){for(const char* p=str;*p;put_char(*(p++)));return *this;}
    }Cout;
}
using namespace FastIO;
#define cin Cin
#define cout Cout
constexpr int N=3e5+5; using pii = pair<int,int>;
int n,m,K,dfn[N],low[N],dfscnt,st[N],tp,ins[N],cp[N],cpcnt; vector<pii> to[N]; vector<int> lis[N]; ll val[N];
void dfs(int u){
    dfn[u]=low[u]=++dfscnt; ins[st[++tp]=u]=1;
    for(auto [v,e]:to[u]){
        if(!dfn[v]) dfs(v),low[u]=min(low[u],low[v]);
        else if(ins[v]) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        cpcnt++; int z; do ins[z=st[tp--]]=0,lis[cp[z]=cpcnt].push_back(z); while(z!=u);
    }
}
signed main(){
    Fin("ship.in"); Fout("ship.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    cin>>n>>m>>K; For(i,1,m) { int x,y,z; cin>>x>>y>>z; to[x].emplace_back(y,z); z=(K-z%K)%K; val[x]+=z; val[y]-=z; }
    For(i,1,n) if(!dfn[i]) dfs(i);
    priority_queue<int> q; ll ans=0,qwq=0;
    Rev(o,cpcnt,1){
        vector<int> vec;
        for(int u:lis[o]){
            int r=(val[u]%K+K)%K; qwq+=(val[u]-r)/K; vec.push_back(r);
        }
        sort(vec.begin(),vec.end(),greater<>());
        while(q.size()&&qwq>0){
            ans+=(K-q.top()); q.pop(); qwq--;
        }
        vector<int> tmp;
        for(int x:vec){
            if(qwq<0) qwq++,tmp.push_back(K-x);
            else if(q.size()&&q.top()+x>=K) ans+=(K-q.top()),q.pop(),tmp.push_back(K-x);
            else ans+=x;
        }
        for(int x:tmp) q.push(x);
        if(qwq>0) ans+=K*qwq,qwq=0;
    }
    while(q.size()) ans+=q.top(),q.pop();
    cout<<(ans+K*abs(qwq))/2<<'\n';
    return 0;
}

// CONTINUE, NON-STOPPING, FOR CHARLIEY
// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING

// Started Coding On: February 22 Thu, 09 : 46 : 17