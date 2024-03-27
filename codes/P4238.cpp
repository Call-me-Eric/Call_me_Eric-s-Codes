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
#define int long long
namespace NTT{
    vector<int> rev;
    int mod, g, gi;
    int qpow(int x,int a){
        int res = 1;
        while(a){
            if(a & 1)res = res * x % mod;
            x = x * x % mod;a >>= 1;
        }
        return res;
    }
    void NTT(vector<int> &ans,int n,int inv){
        for(int i = 0;i < n;i++)if(i < rev[i])swap(ans[i],ans[rev[i]]);
        for(int i = 1;i < n;i <<= 1){
            int wn = qpow((inv == 1 ? g : gi),(mod - 1) / (i << 1));
            for(int j = 0;j < n;j += (i << 1)){
                int w0 = 1;
                for(int k = 0;k < i;k++,w0 = w0 * wn % mod){
                    int x = ans[j + k], y = w0 * ans[i + j + k] % mod;
                    ans[j + k] = (x + y) % mod;ans[i + j + k] = (x - y + mod) % mod;
                }
            }
        }
    }
	int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

/*
    input a[0,n], b[0,m],return ans[0,n + m] in O(2^k times k)(2^{k-1}<n+m<=2^k)
    which meet forall i in[0,n + m],ans_i= sum_{j=0}^{i}a_j times b_{i - j}(mod p)
*/
    vector<int> solve(vector<int> a,vector<int> b,int md){
        mod = md;
		if(mod == 998244353 || mod == 1004535809){g = 3;}
		else {cerr << "No Root !";}
		gi = qpow(g,mod - 2);
        int n = a.size() - 1, m = b.size() - 1;
        int len = (1 << max((int)ceil(log2(n + m)),1ll));rev.clear();
        rev.resize(len + 10);a.resize(len + 10);b.resize(len + 10);
        for(int i = 0;i < len;i++){rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (max((int)ceil(log2(n + m)),1ll) - 1));}
        NTT(a,len,1);NTT(b,len,1);
        for(int i = 0;i < len;i++)a[i] = a[i] * b[i] % mod;
        NTT(a,len,-1);
		int inv = qpow(len,mod - 2);
		for(int i = 0;i <= n + m;i++){rev[i] = a[i] * inv % mod;}
        rev.resize(n + m + 1);
        return rev;
    }
    void init(int md){
        mod = md;
		if(mod == 998244353 || mod == 1004535809){g = 3;}
		else {cerr << "No Root !";}
		gi = qpow(g,mod - 2);
    }
};
namespace polyinv{
    using namespace Call_me_Eric::NTT;
    vector<int> b, a ,c;int len, L;
    void getinv(int n,int mod){
        if(n == 1){b[0] = qpow(a[0],mod - 2);return;}
        getinv((n + 1) >> 1,mod);
        len = 1;L = 0;
        while(len < (n << 1))len <<= 1,L++;
        for(int i = 0;i < len;i++){rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));}
        for(int i = 0;i < n;i++){c[i] = a[i];}for(int i = n;i < len;i++)c[i] = 0;
        NTT::NTT(c,len,1);NTT::NTT(b,len,1);
        for(int i = 0;i < len;i++){b[i] = (2 - b[i] * c[i] % mod + mod) % mod * b[i] % mod;}
        NTT::NTT(b,len,-1);int inv = qpow(len,mod - 2);
        for(int i = 0;i < n;i++)b[i] = (b[i] * inv) % mod;
        for(int i = n;i < len;i++)b[i] = 0;
    }
    vector<int> solve(vector<int> arr,int mod){
        NTT::init(mod);
        a = arr;int n = a.size(), mxn = n * 5;
        rev.resize(mxn);a.resize(mxn);b.resize(mxn);c.resize(mxn);
        getinv(n,mod);b.resize(n);
        return b;
    }
};
int n;
vector<int> a;
void main(){
    n = read();
    for(int i = 1;i <= n;i++)a.push_back(read());
    auto ans = polyinv::solve(a,998244353);
    for(int i : ans)printf("%lld ",i);puts("");
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