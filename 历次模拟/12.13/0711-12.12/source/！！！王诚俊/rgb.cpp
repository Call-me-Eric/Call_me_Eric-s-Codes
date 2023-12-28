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
		char stk[std::numeric_limits<T>::digits10],*top=stk;
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
#define FILEIO(file) freopen("input.in","r",stdin)
#define LOG(...) fprintf(stderr,__VA_ARGS__)
#endif

constexpr int MAXN=250,MAXM=MAXN*(MAXN-1)/2;
mt19937 mt_rnd(random_device{}());

int n,m,c[3];
char ans[MAXM+5];
bool vis[MAXM+5];
struct Edge{ int u,v,w; }e[MAXM+5];

class DisjointSetUnion
{
 private:
	vector<int> fa;
 public:
	DisjointSetUnion()=default;
	void build(int n)
	{ fa.resize(n+1),iota(fa.begin(),fa.end(),0); }
	int findFa(int x)
	{ return x!=fa[x]?fa[x]=findFa(fa[x]):x; }
	void merge(int x,int y)
	{ fa[findFa(y)]=findFa(x); }
}t1,t2;

bool check()
{
	t2=t1;
	for(int i=1;i<=m;i++)
		if(!vis[i]) t2.merge(e[i].u,e[i].v);
	int x=t2.findFa(1);
	for(int i=2;i<=n;i++)
		if(t2.findFa(i)!=x) return false;
	for(int S=1;S<7;S++)
	{
		t2=t1;
		for(int i=1;i<=m;i++)
		{
			if(vis[i] || !(S>>e[i].w&1)) continue;
			int u=t1.findFa(e[i].u),v=t1.findFa(e[i].v);
			t2.merge(u,v);
		}
		int nn=0,k=0,s0=0,s1=0;
		for(int i=1;i<=n;i++)
		{
			if(t1.findFa(i)!=i) continue;
			nn++;
			if(t2.findFa(i)==i) k++;
		}
		for(int i=0;i<3;i++)
			((S>>i&1)?s1:s0)+=c[i];
		if(s1>nn-k || s0<k-1)
			return false;
	}
	return true;
}
void chkans()
{
	assert(c[0]==0 && c[1]==0 && c[2]==0);
	int x=t1.findFa(1);
	for(int i=1;i<=n;i++)
		assert(t1.findFa(i)==x);
}

int main()
{
	FILEIO("rgb");
	qin>>c[0]>>c[1]>>c[2]>>m,n=c[0]+c[1]+c[2]+1;
	for(int i=1;i<=m;i++)
	{
		char ch;
		qin>>e[i].u>>e[i].v>>ch;
		e[i].w=(ch=='r'?0:ch=='g'?1:2);
	}
	t1.build(n);
	if(!check()) assert(0),qout<<"NO\n";
	else
	{
		fill(ans+1,ans+m+1,'0');
		for(int i=1;i<=m;i++)
		{
			vis[i]=true;
			if(!c[e[i].w] || t1.findFa(e[i].u)==t1.findFa(e[i].v))
				continue;
			if(!check())
			{
				ans[i]='1',c[e[i].w]--;
				t1.merge(e[i].u,e[i].v);
			}
		}
		chkans();
		qout<<"YES\n"<<(ans+1)<<'\n';
	}
	return 0;
}
