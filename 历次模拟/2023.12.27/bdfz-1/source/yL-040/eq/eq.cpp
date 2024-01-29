#include <bits/stdc++.h>
using namespace std;

namespace FastIO {
	#define iL (1 << 20)
	char ibuf[iL],*iS = ibuf + iL,*iT = ibuf + iL;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf,1,iL,stdin),iS == iT ? EOF : *iS++) : *iS++)
	template<typename T>
	inline void read(T &a)
	{
		char ch;int sign = 0;
		for(ch = gc();!isdigit(ch);ch = gc())
			if(ch == '-') sign = 1;
		a = ch & 15;
		for(ch = gc();isdigit(ch);ch = gc())
			a = (a << 3) + (a << 1) + (ch & 15);
		if(sign) a = -a;
	}
	char Out[iL],*iter = Out;
	#define flush() fwrite(Out,1,iter - Out,stdout),iter = Out
	template<typename T>
	inline void write(T x,char end = '\n')
	{
		int c[40],l = 0;if(x < 0) *iter++ = '-',x = -x;
		do c[++l] = x % 10,x /= 10; while(x);
		while(l) *iter++ = c[l--] + '0';
		*iter++ = end;flush();
	}
	#undef iL
	#undef gc
	#undef flush
}
using namespace FastIO;

const int N = 7e2 + 5,P = 998244353;
inline int qpow(int a,int b) { int res = 1;while(b) {if(b&1) res = 1ll * res * a % P;a = 1ll * a * a % P;b >>= 1;} return res;}
int n,q;
namespace Subtask1 {
	int a[N][N]; 
	int c[N][N];
	int X[N];
	int Gauss()
	{
		for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n + 1;j++)
			a[i][j] = c[i][j];
		memset(X,0,sizeof X);
		for(int i = 1;i <= n;i++)
		{
			if(!a[i][i])
			for(int j = i + 1;j <= n;j++)
			if(a[j][i]) {swap(a[j],a[i]);break;}
			if(!a[i][i] && !a[i][n + 1]) return 2;
			if(!a[i][i] && a[i][n + 1]) return -1;
			for(int j = 1;j <= n;j++)
			if(j != i)
			{
				int div = 1ll * a[j][i] * qpow(a[i][i],P - 2) % P;
				for(int k = i;k <= n + 1;k++)
					a[j][k] = (a[j][k] + P - 1ll * a[i][k] * div % P) % P;
			}
		}
		for(int i = 1;i <= n;i++)
			X[i] = 1ll * a[i][n + 1] * qpow(a[i][i],P - 2) % P;
		return 1; 
	}
	void output()
	{
		int flg = Gauss();
		if(flg == 2) puts("Many");
		if(flg == -1) puts("No");
		if(flg == 1)
		{
			for(int i = 1;i <= n;i++)
				write(X[i],i == n ? '\n' : ' ');
		}
	}
	void work()
	{
		for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n + 1;j++)
			read(c[i][j]);
		output();
		for(int _ = 1;_ <= q;_++)
		{
			int z;
			read(z);
			for(int i = 1;i <= n + 1;i++)
				read(c[z][i]);
			output();
		}
	}
}
namespace Subtask2 {
	int a[N][N],c[N][N];
	int inva[N][N];
	int b[N];
	int X[N],dta[N],D[N];
	long long t[N][N];
	inline void NxtInv(int z) // (A + D)^-1
	{
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++) 
				t[i][j] = 0;
		int div = qpow(D[z] + 1,P - 2);
		for(int j = 1;j <= n;j++)
		for(int i = 1;i <= n;i++)
			if(i != z)
				t[j][i] += inva[j][i];
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				if(t[i][j] >= P) t[i][j] %= P;
		for(int i = 1;i <= n;i++) D[i] = 1ll * ((i == z) ? 1 : P - D[i]) * div % P;// T[z][i]
		for(int j = 1;j <= n;j++)
		for(int i = 1;i <= n;i++) 
				(t[j][i] += 1ll * inva[j][z] * D[i] % P);			
		
		for(int i = 1;i <= n;i++)
		{
				for(int j = 1;j <= n;j++)
				inva[i][j] = t[i][j] % P;
		}
		
	}
	inline void Inv0()
	{
		memset(inva,0,sizeof inva);
		memcpy(c,a,sizeof a);
		for(int i = 1;i <= n;i++) inva[i][i] = 1;
		for(int i = 1;i <= n;i++)
		{
			if(!c[i][i])
			for(int j = i + 1;j <= n;j++)
			if(c[j][i]) { swap(c[i],c[j]);swap(inva[i],inva[j]);break;}
			for(int j = 1;j <= n;j++)
				if(j != i)
				{
					int div = 1ll * c[j][i] * qpow(c[i][i],P - 2) % P;
					for(int k = 1;k <= n;k++)
						c[j][k] = (c[j][k] + P - 1ll * c[i][k] * div % P) % P,
						inva[j][k] = (inva[j][k] + P - 1ll * inva[i][k] * div % P) % P;
				}
		}
		for(int i = 1;i <= n;i++)
		{
			int div = qpow(c[i][i],P - 2);
			for(int j = 1;j <= n;j++)
				inva[i][j] = 1ll * inva[i][j] * div % P;
//			for(int j = 1;j <= n;j++)
//				cout << inva[i][j] << ' ';
//			cout << endl;
		}
//		printf("tim:%.4lf\n",1.0 * clock() / CLOCKS_PER_SEC);
	}
	void GetEq()
	{
		memset(X,0,sizeof X);
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				(X[i] += 1ll * inva[i][j] * b[j] % P) %= P;
		for(int i = 1;i <= n;i++)
			write(X[i],i == n ? '\n' : ' ');
	}
	inline void work()
	{
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++) read(a[i][j]);
			read(b[i]);
		}
		Inv0();
		GetEq();
		for(int _ = 1;_ <= q;_++)
		{
			int z;
			read(z);
			for(int i = 1,x;i <= n;i++)
				read(x),dta[i] = (x - a[z][i] + P) % P;
			read(b[z]);
			memset(D,0,sizeof D);
			for(int i = 1;i <= n;i++)
				for(int j = 1;j <= n;j++)
					(D[j] += 1ll * dta[i] * inva[i][j] % P) %= P;
			NxtInv(z);
			GetEq();
			for(int i = 1;i <= n;i++) (a[z][i] += dta[i]) %= P;
		}
	}
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	read(n);read(q);
//	Subtask2::work();
	if(n <= 2 || q <= 2) Subtask1::work();
	else Subtask2::work();
	return 0;
}

/*
3 1
1 1 0 2
1 0 1 2
0 1 1 2
1 1 0 0 1

*/

