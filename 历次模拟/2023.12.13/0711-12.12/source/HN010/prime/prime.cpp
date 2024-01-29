#include<cstdio>
typedef unsigned long long u64;
const u64 M=998244353;
int d[6]={0,1,4,6,8,9},e[10]={0,1,-1,-1,2,-1,3,-1,4,5};
int a[18][6]={
	{ 0, 1, 0, 0, 0, 5,},
	{ 2,-1,-1,-1, 4,17,},
	{ 3,-1,-1,-1,15,17,},
	{ 3,-1,-1,-1,17,-1,},
	{15,-1,-1,-1,-1,17,},
	{ 6,-1, 7,13,-1, 6,},
	{ 6,-1,-1, 6,-1, 6,},
	{ 8,-1,-1,11,-1,17,},
	{ 9,-1,-1,11,-1,-1,},
	{10,-1,-1,11,-1,-1,},
	{12,-1,-1,12,-1,-1,},
	{17,-1,-1,12,-1,-1,},
	{17,-1,-1,17,-1,-1,},
	{ 6,-1,15,14,-1, 6,},
	{ 6,-1,15,16,-1, 6,},
	{17,-1,-1,-1,-1,17,},
	{ 6,-1,17,16,-1, 6,},
	{17,-1,-1,-1,-1,-1,}
};
u64 T,n,i,j,k,f[18][2],g[18][2],ans;//f:0 <=,1 >
char s[100086];
u64 read(char *s){
	char c;
	while(c=getchar(),c<'0'||c>'9');
	u64 r=0;
	for(;c>='0'&&c<='9';c=getchar())s[r++]=c-'0';
	for(i=0;i<r-i-1;++i)s[i]^=s[r-i-1]^=s[i]^=s[r-i-1];
	return r;
}u64 play(){
	for(i=0;i<18;++i)f[i][0]=f[i][1]=0;
	f[0][0]=1;
	for(i=0;i<n;++i){
		for(j=0;j<18;++j)g[j][0]=g[j][1]=0;
		for(j=0;j<s[i];++j)if(e[j]!=-1)
			for(k=0;k<18;++k)if(a[k][e[j]]!=-1)
				g[a[k][e[j]]][0]+=f[k][0]+f[k][1];
		if(e[s[i]]!=-1)for(k=0;k<18;++k)
			if(a[k][e[s[i]]]!=-1)g[a[k][e[s[i]]]][0]+=f[k][0],g[a[k][e[s[i]]]][1]+=f[k][1];
		for(j=s[i]+1;j<10;++j)if(e[j]!=-1)
			for(k=0;k<18;++k)if(a[k][e[j]]!=-1)
				g[a[k][e[j]]][1]+=f[k][0]+f[k][1];	
		for(j=0;j<18;++j)f[j][0]=g[j][0]%M,f[j][1]=g[j][1]%M;
	}for(i=j=0;i<18;++i)j+=f[i][0];
	return j%M;
}bool check(){
	for(i=j=0;i<n;++i)if(e[s[i]]==-1)return 0;
	else if(a[j][e[s[i]]]==-1)return 0;
	else j=a[j][e[s[i]]];
	return 1;
}int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	scanf("%llu",&T);
	while(T--){
		n=read(s);
		ans=M-play();
		if(check())++ans;
		n=read(s);
		printf("%llu\n",(ans+play())%M);
	}return 0;
}