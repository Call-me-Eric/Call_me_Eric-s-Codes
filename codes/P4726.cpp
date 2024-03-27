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

namespace polymod{
//NTT
    vector<int> rev;
    int mod, g, gi;
    vector<int> pwwwg, pwwwig;
    vector<int> invvv;
    int qpow(int x,int a){
        if(x == g && a <= 1e6){return pwwwg[a];}
        if(x == gi && a <= 1e6){return pwwwig[a];}
        if(a == mod - 2 && x <= invvv.size()){return invvv[x];}
        int res = 1;
        while(a){
            if(a & 1)res = res * x % mod;
            x = x * x % mod;a >>= 1;
        }
        return res;
    }
    void init(int md){
        mod = md;
		if(mod == 998244353 || mod == 1004535809){g = 3;}
		else {cerr << "No Root !";}
		gi = qpow(g,mod - 2);
        pwwwg.push_back(1);pwwwig.push_back(1);
        for(int i = 1;i <= 1e6;i++){pwwwg.push_back(pwwwg.back() * g % mod);pwwwig.push_back(pwwwig.back() * gi % mod);}
        invvv.push_back(0);invvv.push_back(1);
        for(int i = 2;i <= 1e6;i++){invvv.push_back((mod - mod / i) * invvv[mod % i] % mod);}
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

/*
    input a[0,n], b[0,m],return ans[0,n + m] in O(2^k times k)(2^{k-1}<n+m<=2^k)
    which meet forall i in[0,n + m],ans_i= sum_{j=0}^{i}a_j times b_{i - j}(mod p)
*/
    vector<int> NTTcon(vector<int> a,vector<int> b){
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
//polyinv
    vector<int> invb, inva ,invc;int len, L;
    void getinv(int n){
        if(n == 1){invb[0] = qpow(inva[0],mod - 2);return;}
        getinv((n + 1) >> 1);
        len = 1;L = 0;while(len < (n << 1))len <<= 1,L++;
        for(int i = 0;i < len;i++){rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));}
        for(int i = 0;i < n;i++){invc[i] = inva[i];}for(int i = n;i < len;i++)invc[i] = 0;
        NTT(invc,len,1);NTT(invb,len,1);
        for(int i = 0;i < len;i++){invb[i] = (2 - invb[i] * invc[i] % mod + mod) % mod * invb[i] % mod;}
        NTT(invb,len,-1);int inv = qpow(len,mod - 2);
        for(int i = 0;i < n;i++)invb[i] = (invb[i] * inv) % mod;
        for(int i = n;i < len;i++)invb[i] = 0;
    }
    vector<int> polyinv(vector<int> arr,int n = -1){
        inva.clear();invb.clear();invc.clear();
        inva = arr;if(n == -1)n = inva.size();int mxn = n * 5;
        rev.resize(mxn);inva.resize(mxn);invb.resize(mxn);invc.resize(mxn);
        getinv(n);invb.resize(n);
        return invb;
    }
//polyln
    typedef vector<int> vi;
    vi lna, lnb, A, B;
    void Derive(vi A,vi &B,int len){for(int i = 1;i < len;i++)B[i - 1] = i * A[i] % mod;B[len - 1] = 0;}
    void Integrate(vi A,vi &B,int len){for(int i = 1;i < len;i++)B[i] = A[i - 1] * qpow(i,mod - 2) % mod;B[0] = 0;}
    void getln(vi &f,vi &g,int n){
        Derive(f,A,n);B = polyinv(f,n);

        len = 1;L = 0;while(len < (n << 1))len <<= 1,L++;
        for(int i = 0;i < len;i++){rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));}

        B.resize(len + 10);
        NTT(A,len,1);NTT(B,len,1);
        for(int i = 0;i < len;i++)A[i] = A[i] * B[i] % mod;
        NTT(A,len,-1);int inv = qpow(len,mod - 2);
		for(int i = 0;i < len;i++){A[i] = A[i] * inv % mod;}
        Integrate(A,g,n);
    }
    vi polyln(vi arr,int n = -1){
        lna.clear();lnb.clear();A.clear();B.clear();
        lna = arr;if(n == -1)n = lna.size();
        int mxn = n * 5;rev.resize(mxn);
        lna.resize(mxn);lnb.resize(mxn);A.resize(mxn);B.resize(mxn);
        int m = 1;for(;m <= n;m <<= 1);getln(lna,lnb,m);
        lnb.resize(n);return lnb;
    }
//polyexp
    vi expa, expb, lnnb,a1;
    void getexp(vi a,vi &b,int n){
        if(n == 1){b[0] = 1;return;}
        getexp(a,b,(n + 1) >> 1);
        lnnb = polyln(b, n);

        len = 1;L = 0;while(len < (n << 1))len <<= 1,L++;
        for(int i = 0;i < len;i++){rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));}

        a1.clear();a1.resize(len);
        for(int i = 0;i < n;i++)a1[i] = ((a[i] - lnnb[i]) % mod + mod) % mod;for(int i = n;i < len;i++)a1[i] = 0;
        a1[0]++;NTT(b,len,1);NTT(a1,len,1);
        for(int i = 0;i < len;i++)b[i] = b[i] * a1[i] % mod;
        NTT(b,len,-1);int inv = qpow(len,mod - 2);
        for(int i = 0;i < n;i++)b[i] = b[i] * inv % mod;for(int i = n;i < len;i++)b[i] = 0;
    }
    vi polyexp(vi arr,int n = -1){
        expa.clear();expb.clear();a1.clear();lnnb.clear();
        expa = arr;
        if(n == -1)n = expa.size();
        int mxn = n * 5;expa = arr;
        expa.resize(mxn);expb.resize(mxn);a1.resize(mxn);lnnb.resize(mxn);
        getexp(expa,expb,n);expb.resize(n);
        return expb;
    }
};
int n;vector<int> a;
void main(){
    n = read();for(int i = 1;i <= n;i++)a.push_back(read());
    polymod::init(998244353);
    vector<int> ans = polymod::polyexp(a);
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