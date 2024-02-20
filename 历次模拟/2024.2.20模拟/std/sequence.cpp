#include <bits/stdc++.h>
#include "convolution.h"
using namespace std;
// #define OPENIOBUF

namespace FastIO
{

class FastIOBase
{
 protected:
#ifdef OPENIOBUF
	static const int BUFSIZE=1<<16;
	char buf[BUFSIZE+1];
	int buf_p=0;
#endif
	FILE *target;
	FastIOBase(FILE *f): target(f){}
	~FastIOBase()=default;
 public:
#ifdef OPENIOBUF
	virtual void flush()=0;
#endif
};

class FastOutput final: public FastIOBase
{
 public:
	FastOutput(FILE *f=stdout): FastIOBase(f) {}
#ifdef OPENIOBUF
	~FastOutput() { flush(); }
	void flush() { fwrite(buf,1,buf_p,target),buf_p=0; }
#endif
	void put(char x)
	{
#ifdef OPENIOBUF
		if(buf[buf_p++]=x,buf_p==BUFSIZE) flush();
#else
		putc(x,target);
#endif
	}
	FastOutput &operator <<(char x)
	{ return put(x),*this; }
	FastOutput &operator <<(const char *s)
	{ for(;*s;put(*(s++)));return *this; }
	FastOutput &operator <<(const std::string &s)
	{ return (*this)<<s.c_str(); }
	template<typename T>
	std::enable_if_t<std::is_integral<T>::value,FastOutput&> operator <<(T x)
	{
		if(x<0) return put('-'),(*this)<<(-x);
		char stk[std::numeric_limits<T>::digits10+1],*top=stk;
		do *(top++)=x%10+'0',x/=10; while(x);
		while(top!=stk) put(*(--top));
		return *this;
	}
	template<typename ...T>
	void writesp(T &&...x)
	{ std::initializer_list<int>{((*this)<<(x),put(' '),0)...}; }
	template<typename ...T>
	void writeln(T &&...x)
	{ std::initializer_list<int>{((*this)<<(x),put('\n'),0)...}; }
	template<typename Iter>
	std::enable_if_t<std::is_base_of<
		std::forward_iterator_tag,
		typename std::iterator_traits<Iter>::iterator_category>
	::value> writesp(Iter begin,Iter end)
	{ while(begin!=end) (*this)<<*(begin++)<<' '; }
	template<typename Iter>
	std::enable_if_t<std::is_base_of<
		std::forward_iterator_tag,
		typename std::iterator_traits<Iter>::iterator_category>
	::value> writeln(Iter begin,Iter end)
	{ while(begin!=end) (*this)<<*(begin++)<<'\n'; }
}qout;

class FastInput final: public FastIOBase
{
 private:
	bool __eof;
 public:
	FastInput(FILE *f=stdin): FastIOBase(f),__eof(false)
#ifdef OPENIOBUF
	{ buf_p=BUFSIZE; }
	void flush() { buf[fread(buf,1,BUFSIZE,target)]=EOF,buf_p=0; }
	bool eof()const { return buf[buf_p]==EOF; }
#else
	{}
	bool eof()const { return feof(target); }
#endif
	char get()
	{
		if(__eof) return EOF;
#ifdef OPENIOBUF
		if(buf_p==BUFSIZE) flush();
		char ch=buf[buf_p++];
#else
		char ch=getc(target);
#endif
		return ~ch?ch:(__eof=true,EOF);
	}
	void unget(char c)
	{
		__eof=false;
#ifdef OPENIOBUF
		buf[--buf_p]=c;
#else
		ungetc(c,target);
#endif
	}
	explicit operator bool()const { return !__eof; }
	FastInput &operator >>(char &x)
	{ while(isspace(x=get()));return *this; }
	template<typename T>
	std::enable_if_t<std::is_integral<T>::value,FastInput&> operator >>(T &x)
	{
		char ch,sym=0;x=0;
		while(isspace(ch=get()));
		if(__eof) return *this;
		if(ch=='-') sym=1,ch=get();
		for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=get());
		return unget(ch),sym?x=-x:x,*this;
	}
	FastInput &operator >>(char *s)
	{
		while(isspace(*s=get()));
		if(__eof) return *this;
		for(;!isspace(*s) && !__eof;*(++s)=get());
		return unget(*s),*s='\0',*this;
	}
	FastInput &operator >>(std::string &s)
	{
		char str_buf[(1<<8)+1]={0},*p=str_buf;
		char *const buf_end=str_buf+(1<<8);
		while(isspace(*p=get()));
		if(__eof) return *this;
		for(s.clear(),p++;;p=str_buf)
		{
			for(;p!=buf_end && !isspace(*p=get()) && !__eof;p++);
			if(p!=buf_end) break;
			s.append(str_buf);
		}
		unget(*p),*p='\0',s.append(str_buf);
		return *this;
	}
	template<typename ...T>
	void read(T &&...x)
	{ std::initializer_list<int>{((*this)>>(x),0)...}; }
	template<typename Iter>
	std::enable_if_t<std::is_base_of<
		std::forward_iterator_tag,
		typename std::iterator_traits<Iter>::iterator_category>
	::value> read(Iter begin,Iter end)
	{ while(begin!=end) (*this)>>*(begin++); }
}qin;

} // namespace FastIO
using FastIO::qin,FastIO::qout;

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

#ifndef DADALZY
#define FILEIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
#define LOG(...) [](auto...){}(__VA_ARGS__)
#else
#define FILEIO(file) freopen("input.in","r",stdin),freopen("output.out","w",stdout)
#define LOG(...) fprintf(stderr,__VA_ARGS__)
#endif

namespace Math
{

template<typename Derived>
class ModintBase
{
#define DEF_OP1(op,expr) \
	friend constexpr Derived operator op(const Derived &lhs,const Derived &rhs) \
	{ return Derived(lhs)op##=rhs; } \
	constexpr Derived &operator op##=(const Derived &rhs) \
	{ return (expr),*static_cast<Derived*>(this); }
#define DEF_OP2(op,expr) \
	constexpr Derived operator op(int) \
	{ Derived res(*static_cast<Derived*>(this)); return op(*this),res; } \
	constexpr Derived &operator op() \
	{ return (expr),*static_cast<Derived*>(this); }
#define DEF_OP3(op,expr) \
	constexpr Derived operator op()const \
	{ return (expr); }
#define DEF_OP4(op) \
	friend constexpr bool operator op(const Derived &lhs,const Derived &rhs) \
	{ return lhs.val op rhs.val; }
#define MOD Derived::getMod()
 protected:
	int val;
 private:
	template<typename T>
	static constexpr std::enable_if_t<std::is_integral<T>::value,T> __inv(T a,T b)
	{ T x=0,y=1,t=0;for(;a;t=b/a,std::swap(a,b-=t*a),std::swap(y,x-=t*y));return x; }
	template<typename T>
	static constexpr std::enable_if_t<std::is_integral<T>::value,T> __fix(T x)
	{ return Derived::fix(x); }
	static constexpr void __qmo(int &x)
	{ x+=(x>>31&MOD); }
 public:
	constexpr ModintBase(): val(0) {}
	constexpr ModintBase(const Derived &x): val(x.val) {}
	template<typename T>
	constexpr ModintBase(T x): val(__fix(x)) {}
	constexpr static Derived unfixed(int x)
	{ return reinterpret_cast<Derived&>(x); }
	constexpr Derived inv()const
	{ return Derived(__inv(val,MOD)); }
	constexpr int operator ()()const
	{ return val; }
	DEF_OP1(+,__qmo(val+=rhs.val-MOD))
	DEF_OP1(-,__qmo(val-=rhs.val))
	DEF_OP1(*,(val=__fix(1ll*val*rhs.val)))
	DEF_OP1(/,(val=__fix(1ll*val*__inv(rhs.val,MOD))))
	DEF_OP2(++,__qmo(val+=1-MOD))
	DEF_OP2(--,__qmo(--val))
	DEF_OP3(+,*this)
	DEF_OP3(-,unfixed(val?MOD-val:0))
	DEF_OP4(==) DEF_OP4(!=) DEF_OP4(<) DEF_OP4(>) DEF_OP4(<=) DEF_OP4(>=)
#undef DEF_OP1
#undef DEF_OP2
#undef DEF_OP3
#undef DEF_OP4
#undef MOD
};
template<typename T,typename U>
constexpr std::enable_if_t<std::is_integral<T>::value,U> qpow(U x,T y)
{ U res(1);for(;y;x*=x,y>>=1)if(y&1)res*=x;return res; }

class FastMod
{
 private:
	using ULL=uint64_t;
	using U128=__uint128_t;
	ULL p,m;
 public:
	constexpr FastMod(): p(0),m(0) {}
	constexpr FastMod(ULL p): p(p),m((U128(1)<<64)/p) {}
	constexpr ULL getp()const { return p; }
	constexpr ULL operator()(ULL a)const
	{ ULL q=(U128(m)*a)>>64,r=a-q*p;return r>=p?r-p:r; }
};

// Modint for dynamic MOD
class DModint: public ModintBase<DModint>
{
 private:
	using BaseT=ModintBase<DModint>;
	static FastMod R;
	friend BaseT;
	template<typename T> static constexpr T fix(T x)
	{ return x<0?R.getp()-R(-x):R(x); }
 public:
	using BaseT::BaseT;
	static constexpr void setMod(int mod) { R=FastMod(mod); }
	static constexpr int getMod() { return R.getp(); }
};
FastMod DModint::R{};

// Modint for static MOD
template<int MOD>
class SModint: public ModintBase<SModint<MOD>>
{
 private:
	using BaseT=ModintBase<SModint<MOD>>;
	friend BaseT;
	template<typename T> static constexpr T fix(T x)
	{ return (x%=MOD)<0?x+MOD:x; }
 public:
	using BaseT::BaseT;
	static constexpr int getMod() { return MOD; }
};

} // namespace Math

constexpr int MOD=998244353;
using Mint=Math::SModint<MOD>;

constexpr int MAXN=5e5;

Mint fac[2*MAXN+5],inv[2*MAXN+5];
inline Mint binom(int r,int c)
{ return r<c?0:fac[r]*inv[c]*inv[r-c]; }
void prepare()
{
	fac[0]=1;
	for(int i=1;i<=2*MAXN;i++) fac[i]=fac[i-1]*i;
	inv[2*MAXN]=fac[2*MAXN].inv();
	for(int i=2*MAXN;i>=1;i--) inv[i-1]=inv[i]*i;
}

int n,a[MAXN+5],c[MAXN+5],bk[MAXN+5];
vector<int> S;
Mint f[2*MAXN+5],A[MAXN+5],B[MAXN+5],ans[MAXN+5];
void conv(const Mint *bg1,const Mint *ed1,const Mint *bg2,const Mint *ed2,Mint *out)
{
	vector<int> F((const int*)bg1,(const int*)ed1),
				G((const int*)bg2,(const int*)ed2);
	auto res=convolution(F,G);
	for(int i=0;i<(int)res.size();i++)
		out[i]=Mint::unfixed(res[i]);
}

int main()
{
	FILEIO("sequence");
	qin>>n;
	qin.read(a+1,a+n+1);
	for(int i=1;i<=n;i++) c[a[i]]++;
	prepare();
	int has=0;
	Mint mul=1;
	for(int i=1;i<=n;i++)
	{
		if(!c[i]) continue;
		has++,mul*=inv[c[i]];
		if(!bk[c[i]]) S.push_back(c[i]);
		bk[c[i]]++;
	}
	// part 1
	A[0]=1;
	for(int i=1;i<=n;i++)
	{
		A[i]=((i&1)?-inv[i]:inv[i]);
		B[i]=inv[i]*qpow(inv[i-1],has)*mul;
		for(auto &j: S) B[i]*=qpow(fac[j+i-1],bk[j]);
	}
	conv(A,A+n+1,B,B+n+1,f);
	// part 2
	for(int i=0;i<=n;i++)
	{
		A[n-i]=((i&1)?-inv[i]:inv[i]);
		B[i]=fac[i]*fac[n-i]*f[n-i];
	}
	conv(A,A+n+1,B,B+n+1,f);
	// get the answer
	for(int i=0;i<n;i++) ans[n-1-i]=inv[i]*f[i+n];
	for(int i=0;i<n;i++) qout<<ans[i]()<<' ';
	qout<<'\n';
	return 0;
}
