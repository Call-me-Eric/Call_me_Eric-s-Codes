#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5;
const int mod=4294967296;
int n,m;
int f[N][7];
char s[N];
char get()
{
	char cr=getchar();
	while(!(cr>='A'&&cr<='Z'||cr>='a'&&cr<='z'||cr>='0'&&cr<='9')) cr=getchar();
	return cr;
}
void dp(int l,int r)
{
	for(int i=0;i<5;i++) f[l-1][i]=0;
	for(int i=l;i<=r;i++)
	{
		for(int j=0;j<5;j++) f[i][j]=f[i-1][j]%mod;
		if(s[i]=='(') f[i][0]++;
		if(s[i]=='0') 
		{
			f[i][1]=(f[i][1]+f[i-1][0])%mod;
			f[i][3]=(f[i][3]+f[i-1][2])%mod;
		}
		if(s[i]=='w') f[i][2]=(f[i][2]+f[i-1][1])%mod;
		if(s[i]==')') f[i][4]=(f[i][4]+f[i-1][3])%mod;
	}
}
		
signed main()
{
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=m;i++)
	{
		//cout<<i<<endl;
		char op=get(),c;
		//cout<<op<<endl;
		if(op=='A')
		{
			int x;
			scanf("%lld",&x);c=get();
			//cout<<"c="<<c<<endl;
			s[x]=c;
		}
		else if(op=='B')
		{
			int l,r;
			scanf("%lld%lld",&l,&r);c=get();
			for(int j=l;j<=r;j++) s[j]=c;
		}
		else
		{
			int l,r;
			scanf("%lld%lld",&l,&r);
			dp(l,r);
			cout<<f[r][4]%mod<<endl;
		}
	}
	return 0;
}
/*
28 1
^Q>o_(0-oq/_wAr^<-|wQq0_|z)\
C 1 28
*/
