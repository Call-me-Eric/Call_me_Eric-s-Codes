#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define ll long long
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
	void write(ll x,char c='\0'){
		if (x<0)putc('-'),x=-x;
		while (x)num[++num[0]]=x%10,x/=10;
		if (!num[0])putc('0');
		while (num[0])putc(num[num[0]--]+'0');
		putc(c);
	}
};using IO::read;using IO::write;
int n,m,q,head[N],nex[N],st[N],num[20];
ll f[N],ans[N];
set<int>s;
set<int>::iterator it;
struct Data{
	int p,x,y,z;
	bool operator < (const Data &k)const{
		return x>k.x;
	}
}a[N],Q[N];
int lowbit(int k){
	return k-(k&(k-1));
}
void update(int x,int y){
	while (x<=m){
		f[x]+=y;
		x+=lowbit(x);
	}
}
ll query(int x){
	ll ans=0;
	while (x){
		ans+=f[x];
		x-=lowbit(x);
	} 
	return ans;
}
int main(){
	freopen("operate.in","r",stdin);
	freopen("operate.out","w",stdout);
	n=read(),m=read(),q=read();
	bool flag=0;
	for(int i=1;i<=m;i++){
		a[i].p=read(),a[i].x=read();
		if (a[i].p==1)a[i].y=read();
		if (a[i].p==2)a[i].y=read(),a[i].z=read(),flag=1;
	}
	if (!flag){
		for(int i=1;i<=q;i++)putchar('0'),putchar('\n');
		return 0;
	}
	for(int i=1;i<=q;i++){
		Q[i].x=read(),Q[i].y=read();
		Q[i].p=i;
	}
	sort(Q+1,Q+q+1);
	memset(head,-1,sizeof(head));
	for(int i=m,j=1;i;i--){
		if (a[i].p==1){
			if ((head[a[i].x]==-1)&&(head[a[i].y]!=-1)){
				s.erase(a[i].y);
				s.insert(a[i].x);
			}
			if ((head[a[i].x]!=-1)&&(head[a[i].y]==-1)){
				s.erase(a[i].x);
				s.insert(a[i].y);
			}
			swap(head[a[i].x],head[a[i].y]);
		}
		if (a[i].p==2){
			for(it=s.lower_bound(a[i].x);(it!=s.end())&&((*it)<=a[i].y);it++){
				int k=st[++st[0]]=(*it);
				while (head[k]!=-1){
					update(head[k],a[i].z);
					head[k]=nex[head[k]];
				}
			}
			while (st[0])s.erase(st[st[0]--]);
		}
		if (a[i].p==3){
			if (head[a[i].x]==-1)s.insert(a[i].x);
			nex[i]=head[a[i].x];
			head[a[i].x]=i;
		}
		while ((j<=q)&&(Q[j].x==i)){
			ans[Q[j].p]=query(Q[j].y);
			j++;
		}
	}
	for(int i=1;i<=q;i++)write(ans[i],'\n');
	IO::flush();
	return 0;
} 
