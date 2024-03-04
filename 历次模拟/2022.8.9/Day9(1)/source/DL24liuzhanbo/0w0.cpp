#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
const int N=50010;
int read(){
	int sum=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return f*sum;
}
int n,m;
char s[N];
int main(){
	freopen("0w0.in","r",stdin);freopen("0w0.out","w",stdout);
	n=read(),m=read();
	scanf("%s",s+1);
	for(re int i=1;i<=m;i++){
		char a,d;int b,c;
		cin>>a;
		if(a=='A'){cin>>b>>d;s[b]=d;}
		if(a=='B'){
			cin>>b>>c>>d;
			for(re int j=b;j<=c;j++){s[j]=d;}
		}
		if(a=='C'){
			ll ans=0;
			b=read(),c=read();
			for(re int u=b;u<=c-2;u++){
				for(re int v=u+1;v<=c-1;v++){
					for(re int w=v+1;w<=c;w++){
						if(s[u]=='0'&&s[v]=='w'&&s[w]=='0') ans++,ans%=4294967296;
					}
				}
			}
			printf("%lld\n",ans);
		}
	}
}
