#include "testlib.h"
#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
#define assume(expr) ((!!(expr))||(exit((fprintf(stderr,"Assumption Failed: %s on Line %d\n",#expr,__LINE__),-1)),false))
#define range basic_string_view
using namespace std; typedef long long ll;
signed main(int argc,char** argv){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(1,500),m=inf.readInt(1,500),k=inf.readInt(1,1e9);
    auto test=[&](int fir){
        vector<vector<int>> a(n+1); For(i,1,n) a[i].resize(m+1);
        int o=1;
        For(_,1,n*m){
            int x,y; if(_==1) x=fir,y=ouf.readInt(); else x=ouf.readInt(),y=ouf.readInt();
            if(a[x][y]) quitf(_wa,"Duplicated pairs in S: (%d,%d)",x,y);
            a[x][y]=o; o=3-o;
        }
        For(i,1,n){
            For(j,1,m){
                For(dx,-1,1) For(dy,-1,1) if(dx||dy){
                    int x=i,y=j,ok=0;
                    For(_,1,k-1){
                        x+=dx; y+=dy; if(x<1||x>n||y<1||y>m||a[x][y]!=a[i][j]) { ok=1; break; }
                    }
                    if(!ok) quitf(_wa,"k consecutive pairs starting from (%d,%d) ending on (%d,%d)",i,j,i+(k-1)*dx,j+(k-1)*dy);
                }
            }
        }
        return true;
    };
    int ww=ans.readInt(),hh=ouf.readInt();
    if(ww==-1){
        if(hh==-1) quitf(_ok,"Correct! S is empty.");
        else ensuref(!test(hh),"How did you come up with an answer?");
    }
    test(hh);
    quitf(_ok,"Correct! Gracontulations!");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: September 26 Tue, 09 : 04 : 56