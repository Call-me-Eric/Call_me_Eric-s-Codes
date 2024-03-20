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
const int maxn = 2e5 + 10,maxsqrt = 500 + 10;
int sid, n, m;
int a[maxn], maxver[maxn];
int blocklen;
int id[maxn], lid[maxsqrt], rid[maxsqrt];
int kmaxver[maxsqrt][maxsqrt];
int val[maxsqrt][maxsqrt];
pair<int,int> tmp[maxsqrt];
int maxtag[maxsqrt], sumtag[maxsqrt];
bool operator < (pair<int,int> a,pair<int,int> b){
    return a.first == b.first ? a.second < b.second : a.first < b.first;
}
void pushdown(int block){
    for(int i = lid[block];i <= rid[block];i++){
        maxver[i] = max(maxver[i],a[i] + maxtag[block]);
        a[i] += sumtag[block];
    }
    maxtag[block] = sumtag[block] = 0;
}
void rebuild(int block){
    for(int i = 1;i <= rid[block] - lid[block] + 1;i++){
        tmp[i] = make_pair(a[i + lid[block] - 1],maxver[i + lid[block] - 1]);
    }
    sort(tmp + 1,tmp + 1 + (rid[block] - lid[block] + 1));
    val[block][0] = kmaxver[block][0] = -0x3f3f3f3f3f3f3f3f;
    for(int i = 1;i <= rid[block] - lid[block] + 1;i++){
        kmaxver[block][i] = max(kmaxver[block][i - 1],tmp[i].second);
        val[block][i] = tmp[i].first;
    }
}
void main(){
    sid = read(); n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = maxver[i] = read();
    blocklen = sqrt(n);int cntblock = 1;
    for(int i = 1;i <= n;i += blocklen){
        lid[cntblock] = i;maxtag[cntblock] = sumtag[cntblock] = 0;
        for(int j = 0;j < blocklen && i + j <= n;j++){
            id[i + j] = cntblock;
            rid[cntblock] = i + j;
        }
        cntblock++;
    }
    // cerr << "blocklen = " << blocklen << " cntblock = " << cntblock << endl;
    cntblock--;
    for(int i = 1;i <= cntblock;i++)rebuild(i);
    int opt, l, r, x;
    while(m--){
        opt = read(), l = read(), r = read(), x = read();
        if(opt == 1){
            int tmpl = 0, tmpr = 0;
            if(id[l] == id[r]){
                pushdown(id[l]);
                for(int i = l;i <= r;i++){
                    a[i] += x;maxver[i] = max(maxver[i],a[i]);
                }
                rebuild(id[l]);continue;
            }
            if(lid[id[l]] != l){
                pushdown(id[l]);
                for(int i = l;i <= rid[id[l]];i++){
                    a[i] += x;maxver[i] = max(maxver[i],a[i]);
                }
                rebuild(id[l]);tmpl++;
            }
            if(rid[id[r]] != r){
                pushdown(id[r]);
                for(int i = lid[id[r]];i <= r;i++){
                    a[i] += x;maxver[i] = max(maxver[i],a[i]);
                }
                rebuild(id[r]);tmpr++;
            }
            for(int i = id[l] + tmpl;i <= id[r] - tmpr;i++){
                sumtag[i] += x;
                maxtag[i] = max(maxtag[i],sumtag[i]);
            }
        }
        else{
            int ans = -0x3f3f3f3f3f3f3f3f;
            int tmpl = 0, tmpr = 0;
            if(id[l] == id[r]){
                for(int i = l;i <= r;i++){
                    if(a[i] + sumtag[id[l]] < x)ans = max(ans,max(a[i] + maxtag[id[l]],maxver[i]));
                }
                if(ans == -0x3f3f3f3f3f3f3f3f){puts("-inf");}
                else printf("%lld\n",ans);
                continue;
            }
            if(lid[id[l]] != l){
                for(int i = l;i <= rid[id[l]];i++){
                    if(a[i] + sumtag[id[l]] < x)ans = max(ans,max(a[i] + maxtag[id[l]],maxver[i]));
                }
                tmpl++;
            }
            if(rid[id[r]] != r){
                for(int i = lid[id[r]];i <= r;i++){
                    if(a[i] + sumtag[id[r]] < x)ans = max(ans,max(a[i] + maxtag[id[r]],maxver[i]));
                }
                tmpr++;
            }
            for(int i = id[l] + tmpl;i <= id[r] - tmpr;i++){
                int pos = lower_bound(val[i] + 1,val[i] + 1 + (rid[i] - lid[i] + 1),x - sumtag[i]) - val[i] - 1;
                if(pos){ans = max(ans,max(kmaxver[i][pos],val[i][pos] + maxtag[i]));}
            }
            if(ans == -0x3f3f3f3f3f3f3f3f){puts("-inf");}
            else printf("%lld\n",ans);
        }
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("recall.in","r",stdin);
    freopen("recall.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}