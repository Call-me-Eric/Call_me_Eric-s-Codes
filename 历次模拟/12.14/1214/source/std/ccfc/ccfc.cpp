#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<random>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<set>

#define int long long
#define fi first
#define se second
#define max Max
#define min Min
#define abs Abs
#define lc (x<<1)
#define rc (x<<1|1)
#define mid ((l+r)>>1)
#define pb(x) push_back(x)
#define lowbit(x) ((x)&(-(x)))
#define fan(x) ((((x)-1)^1)+1)
#define mp(x,y) make_pair(x,y)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define SZ(x) ((int)(x.size()))
#define INF 0x3f3f3f3f

using namespace std;

inline int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=(ans<<1)+(ans<<3)+c-'0';c=getchar();}
	return ans*f;
}

inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x/10) write(x/10);
	putchar((char)(x%10)+'0');
}

template<typename T>inline T Abs(T a){return a>0?a:-a;};
template<typename T,typename TT>inline T Min(T a,TT b){return a<b?a:b;}
template<typename T,typename TT> inline T Max(T a,TT b){return a<b?b:a;}

const int N=2e5+5,B=1,base=131;
const int mod[B]={1000000007};
int n,ans[N],id[N],rk[N];
char s[N];

inline int q_pow(int a,int b,int p)
{
	int c=1;
	while(b)
	{
		if(b&1) c=a*c%p;
		a=a*a%p;b>>=1;
	}
	return c;
}

struct Hash
{
	int w[B];
	Hash(){memset(w,0,sizeof(w));}
	Hash(int x){for(int i=0;i<B;++i) w[i]=x;}
	Hash operator + (const Hash &p)const
	{
		Hash res;
		for(int i=0;i<B;++i)
			res=(w[i]+p.w[i])%mod[i];
		return res;
	}
	Hash operator - (const Hash &p)const
	{
		Hash res;
		for(int i=0;i<B;++i)
			res=(w[i]-p.w[i]+mod[i])%mod[i];
		return res;
	}
	Hash operator * (const Hash &p)const
	{
		Hash res;
		for(int i=0;i<B;++i)
			res=w[i]*p.w[i]%mod[i];
		return res;
	}
	bool operator == (const Hash &p)const
	{
		for(int i=0;i<B;++i)
			if(w[i]!=p.w[i])
				return 0;
		return 1;
	}
	bool operator < (const Hash &p)const
	{
		for(int i=0;i<B;++i)
			if(w[i]!=p.w[i])
				return w[i]<p.w[i];
		return 0;
	}
	inline void inv()
	{
		for(int i=0;i<B;++i)
			w[i]=q_pow(w[i],mod[i]-2,mod[i]);
	}
}pw[N],iv[N],h[N];

Hash query(int l,int r)
{
	Hash tmp=h[r];
	if(l) tmp=tmp-h[l-1];
	return tmp*iv[l];
}

int LCP(int x,int y)
{
	int res=0,l=0,r=min(n-x,n-y);
	while(l<=r)
	{
		if(query(x,x+mid-1)==query(y,y+mid-1))
			res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}

bool cmp(int x,int y)
{
	int lcp=LCP(x,y);
	if(x+lcp>=n||y+lcp>=n)
		return x>y;
	return s[x+lcp]<s[y+lcp];
}

struct BIT
{
	int c[N];
	inline void add(int x,int v)
	{
		for(;x<=n;x+=lowbit(x))
			c[x]+=v;
	}
	inline int query(int x)
	{
		int res=0;
		for(;x;x-=lowbit(x))
			res+=c[x];
		return res;
	}
	inline int query(int l,int r)
	{
		return query(r)-query(l-1);
	}
	inline void clear()
	{
		for(int i=1;i<=n;++i)
			c[i]=0;
	}
}sm;
 
signed main()
{
	freopen("ccfc.in","r",stdin);
	freopen("ccfc.out","w",stdout);
    scanf("%s",s);
    n=strlen(s);
    pw[0]=iv[0]=Hash(1);
	for(int i=1;i<=n;++i)
	{
		pw[i]=pw[i-1]*Hash(base);
		iv[i]=pw[i];iv[i].inv();
	}
	for(int i=0;i<n;++i)
	{
		if(i) h[i]=h[i-1];
		h[i]=h[i]+pw[i]*s[i];
	}
	for(int i=0;i<n;++i)
		id[i]=i;
	sort(id,id+n,cmp);
	for(int i=0;i<n;++i)
		rk[id[i]]=i;
    auto CMP=[&](int i,int j,bool equal)
	{
        int lcp=LCP(i, j);
        if(lcp==n-j)
            i+=n-j,lcp=LCP(i,j);
        if(lcp==n-j) return equal;
        if(i+lcp==n) return true;
        if(j+lcp==n) return false;
        return s[i+lcp]<s[j+lcp];
    };
    int j=0;
    for(int i=0;i<n;++i)
	{
		if((n-i)*3+1>n) continue;
        int L,R,l,r;l=0,r=n;
        while(r-l>1)
        {
        	if(CMP(id[mid],i,0))
        		l=mid;
        	else r=mid;
		}
        L=r;l=0,r=n;
        while(r-l>1)
        {
        	if(CMP(id[mid],i,1))
        		l=mid;
        	else r=mid;
		}
        R=r;
        if(L>=R) continue;
        while(j<3*i-n*2)
            ans[j]=-sm.query(rk[j]),++j;
        sm.add(L,1),sm.add(R,-1);
    }
    while(j<n)
        ans[j]=-sm.query(rk[j]),++j;
    for (int i=0;i<n;++i) 
        ans[i]+=sm.query(rk[i]);
    for(int i=0;i<n;++i)
	{
        write(ans[i]);
		if(i!=n-1) putchar(' ');
    }
}
