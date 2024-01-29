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
constexpr int N=705,mod=998244353;
int n,Q,va[N][N],bad[N],a[N][N],bs[N][N],co[N][N];
inline void qmo(int& x) { x+=(x>>31)&mod; }
inline int qpow(int x,int y){int res=1;while(y){if(y&1)res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
bool insert(const int* const _A,const int* const _C,int id){
    static int A[N],C[N]; For(i,1,n+1) A[i]=_A[i],C[i]=_C[i];
    For(i,1,n) if(A[i]){
        if(!bs[i][i]){
            int t=qpow(A[i],mod-2);
            For(j,i,n+1) bs[i][j]=1ll*A[j]*t%mod;
            For(j,1,n) co[i][j]=1ll*C[j]*t%mod;
            return true;
        }
        else{
            int t=A[i]; assert(bs[i][i]==1);
            For(j,i,n+1) qmo(A[j]-=1ll*t*bs[i][j]%mod);
            For(j,1,n) qmo(C[j]-=1ll*t*co[i][j]%mod);
        }
    }
    assert(id!=-1);
    For(i,1,n) va[id][i]=C[i];
    return false;
}
void Answer(){
    static int ans[N]; int ok=1;
    Rev(i,n,1){
        if(bs[i][i]==0) ok=0,ans[i]=1;
        else{
            int t=bs[i][n+1]; For(j,i+1,n) qmo(t-=1ll*bs[i][j]*ans[j]%mod);
            ans[i]=t; 
        }
    }
    if(ok) { For(i,1,n) cout<<ans[i]<<' ';; cout<<'\n'; }
    else{
        ok=1;
        For(o,1,n){
            int t=0; For(i,1,n) t=(t+1ll*ans[i]*a[o][i])%mod;
            if(t!=a[o][n+1]) { ok=0; break; }
        }
        if(ok) cout<<"Many\n"; else cout<<"No\n";
    }
}
signed main(){
    Fin("eq.in"); Fout("eq.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    cin>>n>>Q;
    For(o,1,n){
        For(i,1,n+1) cin>>a[o][i];
        static int qwq[N]; For(i,1,n) qwq[i]=(i==o);
        bad[o]=!insert(a[o],qwq,o);
    }
    Answer();
    while(Q--){
        int o; cin>>o;
        if(!bad[o]){
            int p=0;
            For(i,1,n) if(co[i][o]){
                if(p){
                    int t=1ll*co[p][o]*qpow(co[i][o],mod-2)%mod;
                    For(j,i,n+1) qmo(bs[p][j]-=1ll*bs[i][j]*t%mod);
                    For(j,1,n) qmo(co[p][j]-=1ll*co[i][j]*t%mod);
                }
                p=i;
            }
            if(p){
                For(j,1,n+1) bs[p][j]=co[p][j]=0;
            }
            p=0;
            For(i,1,n) if(va[i][o]){
                if(p==0) p=i;
                else{
                    int t=1ll*va[i][o]*qpow(va[p][o],mod-2)%mod;
                    For(j,1,n) qmo(va[i][j]-=1ll*va[p][j]*t%mod);
                }
            }
            if(p){
                static int qwq[N]; For(i,1,n) qwq[i]=(i==p);
                bool _=insert(a[p],qwq,p); assert(_); bad[p]=0; For(i,1,n) va[p][i]=0;
            }
        }
        For(i,1,n+1) cin>>a[o][i];
        static int qwq[N]; For(i,1,n) qwq[i]=(i==o),va[o][i]=0;
        bad[o]=!insert(a[o],qwq,o);
        Answer();
    }
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: December 25 Mon, 15 : 32 : 08