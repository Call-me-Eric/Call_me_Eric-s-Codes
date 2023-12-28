#include <iostream>
using namespace std;

/* d0j1a_1701 FastIO Lite ver. 5.0 */
#define dIO_USE_BUFFER // 注释以使用键盘读入（交卷时请取消注释）
struct IO{
#ifdef dIO_USE_BUFFER
	const static int BUFSIZE=1<<20;
	char ibuf[BUFSIZE], obuf[BUFSIZE], *p1, *p2, *pp;
	inline int getchar(){return(p1 == p2&&(p2=(p1=ibuf)+fread(ibuf,1,BUFSIZE,stdin),p1==p2)?EOF:*p1++);}
	inline int putchar(char x){return((pp-obuf==BUFSIZE&&(fwrite(obuf,1,BUFSIZE,stdout),pp=obuf)),*pp=x,pp++),x;}
	IO(){p1=p2=ibuf,pp=obuf;}
	~IO(){fwrite(obuf,1,pp-obuf,stdout),pp=obuf,fflush(stdout);}
#else
	int (*getchar)()=&::getchar,(*putchar)(int)=&::putchar;
	inline IO &flush(){return fflush(stdout),*this;}
#endif
	template<typename Tp,typename enable_if<is_integral<Tp>::value>::type * =nullptr>
	inline void read(Tp &s){
		int f=1,ch=getchar();s=0;
		while(!isdigit(ch))f=(ch=='-'?-1:1),ch=getchar();
		while(ch == '0')ch = getchar();
		while(isdigit(ch))s=s*10+(ch^48),ch=getchar();
		s*=f;
	}
	template<typename Tp,typename enable_if<is_integral<Tp>::value>::type * =nullptr>
	inline void write(Tp x){
		if(x<0)putchar('-'),x=-x;
		static char sta[41];
		int top=0;
		do sta[top++]=x%10^48,x/=10;while(x);
		while(top)putchar(sta[--top]);
	}
	template<typename Tp>
	inline void writeln(const Tp &x){write(x);putchar('\n');}
	template<typename Tp>
	inline void writeSp(const Tp &x){write(x);putchar(' ');}
}io;

/* 使用说明 */
// 交卷时请把 #define 的注释去掉，获得更好的性能 
int main(){
	int x;
	io.read(x); // cin >> x;
	long long y;
	io.read(y);
	
	io.write(x); // cout << x;
	io.writeSp(y); // cout << y << '  ';
	io.writeln(x+y); // cout << x+y << endl;
	return 0;
} 
