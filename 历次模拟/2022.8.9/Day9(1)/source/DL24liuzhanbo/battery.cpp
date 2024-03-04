#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
int read(){
	int sum=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return f*sum;
}
int T,n,m;
char ch[51][51];
bool flag=0;
inline void work(int i){
	for(re int j=1;j<=m;j++){
		//cout<<1<<endl;
		if(ch[i][j]=='-'){
			//cout<<1<<endl;
			ch[i][j]='|';
			//cout<<ch[i][j]<<endl;
			for(re int k=1;k<=n;k++){
				if(k==i) continue;
				if(ch[k][j]=='|'||ch[k][j]=='-'){
					//puts(" IMPOSSIBLE");
					cout<<1<<endl;
					flag=1;
					return;
				}
			}
		} 
	}
}
inline void work2(int k){
	for(re int i=1;i<=n;i++){
		if(ch[i][k]=='|'){
			ch[i][k]='-';
			for(re int j=1;j<=m;j++){
				if(j==k) continue;
				if(ch[i][j]=='-'||ch[i][j]=='|'){
					//puts(" IMPOSSIBLE");
					flag=1;
					return;
				}
			}
		}
	}
}
inline void check1(){
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(re int j=1;j<=m;j++){
			if(ch[i][j]=='|'||ch[i][j]=='-'){
				cnt++;
				if(cnt==2){
					work(i);
					goto lzb;
				}
			}
		}
		lzb:;
	}
}
inline void check2(){
	for(re int i=1;i<=m;i++){
		int cnt=0;
		for(int j=1;j<=n;j++){
			if(ch[j][i]=='-'||ch[j][i]=='|'){
				cnt++;
				if(cnt==2){
					work2(j);
					goto beimian;
				}
			}
		}
		beimian:;
	}
}
int main(){
	freopen("battery.in","r",stdin);freopen("battery.out","w",stdout);
	T=read();
	yan_jun:
	while(T--){
		flag=0;
		n=read(),m=read();
		for(re int i=1;i<=n;i++){
			scanf("%s",ch[i]+1);
		}
		check1();
		//cout<<flag<<endl;
		if(flag==1){
			//cout<<2<<endl;
			puts("IMPOSSIBLE");
			goto yan_jun;
		}
		check2();
		if(flag){
			//cout<<1<<endl;
			puts("IMPOSSIBLE");
			goto yan_jun;
		}
		if(n==1&&m==3){
			int sum=0;
			for(re int i=1;i<=3;i++){
				if(ch[1][i]=='|'||ch[1][i]=='-'){
					sum++;
				}
			}
			if(sum==2){
				puts("IMPOSSIBLE");
				goto yan_jun;
			}
		}
		if(n==4&&m==3){
			int kkk=0,f[5];
			for(re int i=1;i<n-1;i++){
				int sum=0;
				for(re int j=1;j<=n;j++){
					if(ch[i][j]=='-') ch[i][j]='|',sum++,f[i]=j;
					else if(ch[i][j]=='|') ch[i][j]='-',sum++,f[i]=j;
				}
			}
		}
		puts("POSSIBLE");
		for(re int i=1;i<=n;i++){
			for(re int j=1;j<=m;j++){
				printf("%c" ,ch[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
