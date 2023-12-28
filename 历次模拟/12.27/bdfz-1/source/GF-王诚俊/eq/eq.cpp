#include <bits/stdc++.h>
using namespace std;
#define OPENIOBUF

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
using I128=__int128_t;
using U128=__uint128_t;

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

constexpr int MAXN=700;
using FVec=valarray<Mint>;

int n,m;

vector<tuple<int,FVec,int>> add[MAXN+5];
int tim[MAXN+5];
FVec a[MAXN+5],b[MAXN+5];

inline void insert(FVec x,int t)
{
	for(int i=0;i<n;i++)
	{
		if(!x[i]()) continue;
		if(tim[i]==-1)
			return b[i]=x,tim[i]=t,void();
		else
		{
			if(tim[i]<t) x.swap(b[i]),swap(t,tim[i]);
			Mint coe=x[i]/b[i][i];
			x-=coe*b[i];
		}
	}
}
inline pair<bool,FVec> solve(int t)
{
	bool fl=false;
	FVec res(n);
	for(int i=n-1;i>=0;i--)
	{
		if(tim[i]<t || !b[i][i]())
			{ fl=true;continue; }
		U128 sum=MOD-b[i][n]();
		for(int j=i+1;j<n;j++)
			sum+=(U128)b[i][j]()*res[j]();
		sum=MOD-sum%MOD;
		res[i]=int(sum)/b[i][i];
	}
	return make_pair(fl,res);
}

int main()
{
	FILEIO("eq");
	qin>>n>>m;
	for(int i=0;i<n;i++)
	{
		a[i]=FVec(n+1);
		for(int j=0;j<=n;j++) qin>>(int&)a[i][j];
	}
	for(int i=1,x;i<=m;i++)
	{
		qin>>x,x--;
		add[tim[x]].emplace_back(x,a[x],i-1);
		tim[x]=i;
		for(int j=0;j<=n;j++) qin>>(int&)a[x][j];
	}
	for(int i=0;i<n;i++)
	{
		add[tim[i]].emplace_back(i,a[i],m);
		tim[i]=-1;
	}
	for(int o=0;o<=m;o++)
	{
		for(auto &[p,x,t]: add[o]) insert(x,t),a[p]=x;
		auto [is_many,res]=solve(o);
		bool is_no=false;
		for(int i=0;i<n;i++)
		{
			U128 sum=0;
			for(int j=0;j<n;j++)
				sum+=(U128)a[i][j]()*res[j]();
			sum%=MOD;
			if(int(sum)!=a[i][n]) { is_no=true;break; }
		}
		if(is_no) qout<<"No\n";
		else if(is_many) qout<<"Many\n";
		else for(int i=0;i<n;i++) qout<<res[i]()<<" \n"[i==n-1];
	}
	return 0;
}
/*
1 1 0 2
1 0 1 2
0 1 1 2

*/