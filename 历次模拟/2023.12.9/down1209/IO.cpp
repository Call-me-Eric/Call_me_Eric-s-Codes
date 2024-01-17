#include<bits/stdc++.h>
using namespace std;
namespace IO{
	const int S=(1<<20);
	int x,flag,num[50];char c;
	char ibuf[S],*iS=ibuf,*iT=ibuf;
	char obuf[S],*oS=obuf,*oT=obuf+S;
	char getc(){
//		return getchar();
		if (iS==iT)iS=ibuf,iT=ibuf+fread(ibuf,1,S,stdin);
		return (iS==iT ? EOF : *iS++);
	}
	void flush(){
		fwrite(obuf,1,oS-obuf,stdout),oS=obuf;
	}
	void putc(char c){
		*oS++=c;
		if (oS==oT)flush();
	}
	int read(){
		x=flag=0,c=getc();
		while ((c<'0')||(c>'9'))flag|=(c=='-'),c=getc();
		while ((c>='0')&&(c<='9'))x=x*10+c-'0',c=getc();
		return (flag ? -x : x);
	}
	char read_char(){
		c=getc();
		while (1)c=getc();
		return c;
	}
	void write(int x,char c='\0'){
		if (x<0)putc('-'),x=-x;
		while (x)num[++num[0]]=x%10,x/=10;
		if (!num[0])putc('0');
		while (num[0])putc(num[num[0]--]+'0');
		putc(c);
	}
};
int main(){
	//使用时需使用文件操作
	//用IO::函数名调用其中的函数
	//在程序结束前需加上IO::flush()
	return 0;
}
