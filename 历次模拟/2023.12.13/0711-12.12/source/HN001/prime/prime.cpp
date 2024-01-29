#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>

#define maxn 101101

const int mod=998244353;

bool Mbg;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r*10)+(c^48),c=getchar();
	return f?-r:r;
}

/*

const int num[]={0,1,4,6,8,9};

char L[maxn],R[maxn];

int len,lim[maxn];

int f[maxn][2][3][5][3][3][3][2][2];

long long dfs(int d,bool flg,int a,int b,int c,int d,int e,int f,int g,int h){
	int Lim=flg?lim[d]:9;
	if(!Lim)
}

inline long long calc(char *str){
	len=strlen(str+1);
	for(int i=1;i<=len;i++)
		lim[i]=str[i]-'0';
	return dfs(len,1,0,0,0,0,0,0,0,0);
}

inline void work(){
	scanf("%s",L+1);
	scanf("%s",R+1);
	int lenl=strlen(L+1);
	std::reverse(L+1,L+lenl+1);
	int lenr=strlen(R+1);
	std::reverse(R+1,R+lenr+1);
	for(int i=1;i<=lenr;i++){
		if(str[i]<'9'){
			str[i]++;
			break;
		}
		str[i]='0';
	}
	printf("%lld\n",((calc(R)-calc(L))%mod+mod)%mod);
}

*/

int s_p,p[maxn],ans[maxn];

bool n_p[maxn];

inline bool check(int x){
	int len=0,X=x;
	static int num[11];
	while(X)num[len++]=X%10,X/=10;
	int N=1<<len;
	for(int S=1;S<N;S++){
		int val=0,pw=1;
		for(int i=0;i<len;i++)
			if((S>>i)&1)val+=num[i]*pw,pw*=10;
		if(!n_p[val])return false;
	}
	return true;
}

inline void init(int n=1e5){
	n_p[0]=n_p[1]=true;
	for(int i=2;i<=n;i++){
		if(!n_p[i])p[++s_p]=i;
		for(int j=1;j<=s_p&&p[j]<=n/i;j++){
			n_p[i*p[j]]=1;
			if(!(i%p[j]))break;
		}
	}
	for(int i=1;i<=n;i++)
		ans[i]=ans[i-1]+check(i);
}

inline void work(){
	int l=read<int>();
	int r=read<int>();
	printf("%d\n",ans[r]-ans[l-1]);
}

bool Med;

int main(){
	double Mb=((&Mbg)-(&Med))/1e6;
	fprintf(stderr,"%.2lfMB\n",Mb=Mb<0?-Mb:Mb);
	if(Mb>1000)fprintf(stderr,"MLE!!!\n");
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	init();
	int t=read<int>();
	while(t--)work();
	return 0;
}
