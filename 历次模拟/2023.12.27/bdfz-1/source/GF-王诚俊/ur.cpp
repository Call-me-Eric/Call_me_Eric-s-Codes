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

#ifndef DADALZY
#define FILEIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
#define LOG(...) [](auto...){}(__VA_ARGS__)
#else
#define FILEIO(file) //freopen("ur2.in","r",stdin)
#define LOG(...) fprintf(stderr,__VA_ARGS__)
#endif

int n,K;

namespace Subtask1
{

#define ppc(x) __builtin_popcount(x)

int m,P[40];
map<vector<int>,string> mp[40];

void getPhi()
{
	constexpr double PI=acos(-1);
	static complex<double> tmp[40];

	fill(tmp,tmp+n,0);
	tmp[0]=1;
	for(int i=1;i<n;i++)
	{
		if(__gcd(i,n)!=1) continue;
		complex<double> w=exp(2*PI/n*i*1i);
		m++;
		for(int j=m;j>=1;j--)
			tmp[j]=tmp[j-1]+tmp[j]*(-w);
		tmp[0]*=(-w);
	}
	for(int i=0;i<=m;i++) P[i]=round(tmp[i].real());
}

void main()
{
	getPhi();
	int n1=n/2,n2=n-n/2;
	for(int S=0;S<(1<<n1);S++)
	{
		vector<int> a(n1);
		string s(n1,'0');
		for(int i=0;i<n1;i++)
			if(S>>i&1) a[i]=1,s[i]='1';
		for(int i=n1-1;i>=m;i--)
			for(int j=0;j<m;j++)
				a[i-(m-j)]+=a[i]*(-P[j]);
		a.resize(m);
		mp[ppc(S)][a]=s;
	}
	int ans1=0;
	string ans2(n,'0');
	for(int S=0;S<(1<<n2);S++)
	{
		vector<int> a(n);
		string s(n2,'0');
		for(int i=n1;i<n;i++)
			if(S>>(i-n1)&1) a[i]=1,s[i-n1]='1';
		for(int i=n-1;i>=m;i--)
			for(int j=0;j<m;j++)
				a[i-(m-j)]+=a[i]*(-P[j]);
		a.resize(m);
		for(int i=0;i<m;i++) a[i]=-a[i];
		int c=ppc(S);
		for(int i=K-c;i+c>ans1;i--)
		{
			if(!mp[i].count(a)) continue;
			ans1=i+c;
			ans2=mp[i][a]+s;
		}
	}
	qout<<ans2<<'\n';
}

} // namespace Subtask1

namespace Subtask2
{

void main()
{
	string ans(n,'0');
	if(K==n) ans=string(n,'1');
	else
	{
		int mx=0,d=0;
		for(int i=2;i<n;i++)
		{
			if(n%i!=0) continue;
			int c=i*(K/i);
			if(c>mx) mx=c,d=i;
		}
		if(d) for(int j=0;j<n;j++)
			ans[j]="01"[j%(n/d)<K/d];
	}
	qout<<ans<<'\n';
}

} // namespace Subtask2

int main()
{
	FILEIO("ur");
	qin>>n>>K;
	if(n<=36) Subtask1::main();
	else Subtask2::main();
	return 0;
}
