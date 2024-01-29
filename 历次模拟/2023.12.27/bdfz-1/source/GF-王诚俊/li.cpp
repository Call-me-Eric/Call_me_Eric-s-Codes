#include <bits/stdc++.h>
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
constexpr int INF=1e9;

#ifndef DADALZY
#define FILEIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
#define LOG(...) [](auto...){}(__VA_ARGS__)
#else
#define FILEIO(file) freopen("li2.in","r",stdin)
#define LOG(...) fprintf(stderr,__VA_ARGS__)
#endif

constexpr int MAXN=2e5;

int n,m;

int fa[MAXN+5],siz[MAXN+5];
inline int findFa(int x)
{ return x!=fa[x]?fa[x]=findFa(fa[x]):x; }
inline void merge(int x,int y)
{ x=findFa(x),y=findFa(y);if(x!=y)fa[y]=x,siz[x]+=siz[y]; }

int deg[MAXN+5],mnd[MAXN+5],mxd[MAXN+5];

int main()
{
	FILEIO("li");
	qin>>n>>m;
	iota(fa+1,fa+n+1,1);
	fill(siz+1,siz+n+1,1);
	for(int i=1,u,v;i<=m;i++)
	{
		qin>>u>>v;
		merge(u,v);
		deg[u]++,deg[v]++;
	}
	fill(mnd+1,mnd+n+1,INF);
	fill(mxd+1,mxd+n+1,-INF);
	for(int i=1;i<=n;i++)
	{
		int x=findFa(i);
		mnd[x]=min(mnd[x],deg[i]);
		mxd[x]=max(mxd[x],deg[i]);
	}
	bool fl1=false,fl2=false;
	LL k=0,b=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=findFa(i)) continue;
		if(mxd[i]==0) b++;
		else if(mxd[i]<=2 && mnd[i]==1)
			b+=siz[i]*LL(siz[i]+1)/2;
		else if(mxd[i]==2 && mnd[i]==2)
			k+=siz[i],b+=siz[i],fl1=true;
		else fl2=true;
	}
	if(fl2) qout<<"-1\n";
	else if(fl1) qout<<"1 "<<k<<'\n';
	else qout<<"0 "<<b<<'\n';
	return 0;
}
