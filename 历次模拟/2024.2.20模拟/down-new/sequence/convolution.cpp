#include "convolution.h"
#include <stdexcept>
#include <algorithm>

namespace
{

constexpr int MOD=998244353,G=114514,MAXN=1<<23;
using LL=long long;

inline int qpow(LL x,LL y)
{
	LL res=1;
	for(;y;x=x*x%MOD,y>>=1)
		if(y&1) res=res*x%MOD;
	return res;
}
inline int qmo(int x) { return x+=(x>>31)&MOD; }
inline int madd(int x,int y) { return qmo(x-MOD+y); }
inline int msub(int x,int y) { return qmo(x-y); }
inline int mmul(int x,int y) { return (LL)x*y%MOD; }

struct Precalc
{
	int g[MAXN],tmp[MAXN];
	Precalc()
	{
		for(int i=1;i<MAXN;i<<=1)
		{
			g[i]=1;
			int gn=qpow(G,(MOD-1)/(i<<1));
			for(int j=i+1;j<(i<<1);j++)
				g[j]=mmul(g[j-1],gn);
		}
	}
}precalc;
void DFT(int *a,int len)
{
	for(int i=len>>1;i;i>>=1)
		for(int j=0;j<len;j+=i<<1)
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				a[j+k]=madd(x,y);
				a[i+j+k]=mmul(precalc.g[i+k],msub(x,y));
			}
}
void IDFT(int *a,int len)
{
	for(int i=1;i<len;i<<=1)
		for(int j=0;j<len;j+=i<<1)
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=mmul(precalc.g[i+k],a[i+j+k]);
				a[j+k]=madd(x,y);
				a[i+j+k]=msub(x,y);
			}
	int x=qpow(len,MOD-2);
	for(int i=0;i<len;i++)
		a[i]=mmul(a[i],x);
	std::reverse(a+1,a+len);
}

} // anonymous namespace

std::vector<int> convolution(const std::vector<int> &a,const std::vector<int> &b)
{
	if(a.empty() || b.empty()) return std::vector<int>{};
	std::size_t n1=a.size(),n2=b.size(),m=1;
	while(m<n1+n2-1) m<<=1;
	if(m>MAXN) throw std::length_error("n1+n2 is greater than 8,388,608");
	std::vector<int> res(m);
	std::copy(a.begin(),a.end(),res.begin());
	std::copy(b.begin(),b.end(),precalc.tmp);
	DFT(res.data(),m);
	DFT(precalc.tmp,m);
	for(std::size_t i=0;i<m;i++)
		res[i]=mmul(res[i],precalc.tmp[i]);
	IDFT(res.data(),m);
	std::fill(precalc.tmp,precalc.tmp+m,0);
	res.resize(n1+n2-1);
	return res;
}
