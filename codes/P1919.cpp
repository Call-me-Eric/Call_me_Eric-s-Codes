#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
namespace FFT{
    const double eps = 0.49,pi = acos(-1.0);
    typedef complex<double> comp;
    vector<int> rev;vector<comp> ans;

    void FFT(int n,int inv){
        for(int i = 0;i < n;i++)if(i < rev[i])swap(ans[i],ans[rev[i]]);
        for(int i = 1;i < n;i <<= 1){
            comp wn(cos(pi / i),inv * sin(pi / i));
            for(int j = 0;j < n;j += (i << 1)){
                comp w0(1, 0);
                for(int k = 0;k < i;k++,w0 *= wn){
                    comp x = ans[j + k], y = w0 * ans[i + j + k];
                    ans[j + k] = x + y;ans[i + j + k] = x - y;
                }
            }
        }
    }

/*
    input a[0,n], b[0,m],return ans[0,n + m] in O(2^k times k)(2^{k-1}<n+m<=2^k)
    which meet forall i in[0,n + m],ans_i= sum_{j=0}^{i}a_j times b_{i - j}
*/
    vector<int> solve(vector<int> a,vector<int> b){
        int n = a.size() - 1, m = b.size() - 1;
        int len = (1 << max((int)ceil(log2(n + m)),1));rev.clear();ans.clear();
        ans.resize(len + 10);rev.resize(len + 10);
        for(int i = 0;i <= n;i++){ans[i].real(a[i]);}
        for(int i = 0;i <= m;i++){ans[i].imag(b[i]);}
        for(int i = 0;i < len;i++){rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (max((int)ceil(log2(n + m)),1) - 1));}
        FFT(len,1);
        for(int i = 0;i < len;i++)ans[i] = ans[i] * ans[i];
        FFT(len,-1);
        for(int i = 0;i <= n + m;i++){rev[i] = round(ans[i].imag() / 2 / len + eps);}
        rev.resize(n + m + 1);
        return rev;
    }
};
vector<int> a, b;
void main(){
    char ch = getchar();while(!isdigit(ch))ch = getchar();
    while(isdigit(ch)){a.push_back(ch - '0');ch = getchar();}
    while(!isdigit(ch))ch = getchar();
    while(isdigit(ch)){b.push_back(ch - '0');ch = getchar();}
    auto c = FFT::solve(a,b);
    for(int i = c.size() - 1;i;i--){if(c[i] >= 10){c[i - 1] += c[i] / 10;c[i] %= 10;}}
    for(int i : c)printf("%d",i);puts("");
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}