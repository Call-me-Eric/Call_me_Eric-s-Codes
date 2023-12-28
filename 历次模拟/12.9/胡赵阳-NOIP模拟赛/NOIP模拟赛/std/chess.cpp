#include<bits/stdc++.h>
using namespace std;
int t,ans;
char s[15][15];
int countx(int x,int y0,int y1){
	int cnt=0;
	for(int z=1;z<=9;z++)
		if ((z-y0)*(z-y1)<0)cnt+=(s[x][z]!='*');
	return cnt;
}
int county(int y,int x0,int x1){
	int cnt=0;
	for(int z=1;z<=10;z++)
		if ((z-x0)*(z-x1)<0)cnt+=(s[z][y]!='*');
	return cnt;
}
bool check(int x,int y,int u,int v){
	char c=s[x][y];
	if ((s[u][v]!='*')&&((c>='a')==(s[u][v]>='a')))return 0;
	if (c=='j'){
		if ((abs(x-u)+abs(y-v)==1)&&(1<=u)&&(u<=3)&&(4<=v)&&(v<=6))return 1;
		if ((y==v)&&(s[u][v]=='J')&&(!county(y,x,u)))return 1;
		return 0;
	}
	if (c=='J'){
		if ((abs(x-u)+abs(y-v)==1)&&(8<=u)&&(u<=10)&&(4<=v)&&(v<=6))return 1;
		if ((y==v)&&(s[u][v]=='j')&&(!county(y,x,u)))return 1;
		return 0;
	}
	if (c=='s'){
		if ((abs(x-u)==1)&&(abs(y-v)==1)&&(1<=u)&&(u<=3)&&(4<=v)&&(v<=6))return 1;
		return 0;
	}
	if (c=='S'){
		if ((abs(x-u)==1)&&(abs(y-v)==1)&&(8<=u)&&(u<=10)&&(4<=v)&&(v<=6))return 1;
		return 0;
	}
	if (c=='x'){
		if ((abs(x-u)==2)&&(abs(y-v)==2)&&(s[x+u>>1][y+v>>1]=='*')&&(1<=u)&&(u<=5))return 1;
		return 0;
	}
	if (c=='X'){
		if ((abs(x-u)==2)&&(abs(y-v)==2)&&(s[x+u>>1][y+v>>1]=='*')&&(6<=u)&&(u<=10))return 1;
		return 0;
	}
	if ((c=='c')||(c=='C')){
		if ((x==u)&&(y!=v)&&(!countx(x,y,v)))return 1;
		if ((y==v)&&(x!=u)&&(!county(y,x,u)))return 1;
		return 0;
	}
	if ((c=='m')||(c=='M')){
		if ((abs(x-u)==1)&&(abs(y-v)==2)&&(s[x][y+v>>1]=='*'))return 1;
		if ((abs(x-u)==2)&&(abs(y-v)==1)&&(s[x+u>>1][y]=='*'))return 1;
		return 0;
	}
	if ((c=='p')||(c=='P')){
		if (s[u][v]=='*'){
			if ((x==u)&&(y!=v)&&(!countx(x,y,v)))return 1;
			if ((y==v)&&(x!=u)&&(!county(y,x,u)))return 1;
		}
		else{
			if ((x==u)&&(y!=v)&&(countx(x,y,v)==1))return 1;
			if ((y==v)&&(x!=u)&&(county(y,x,u)==1))return 1;
		}
		return 0;
	}
	if (c=='b'){
		if ((x==u-1)&&(y==v))return 1;
		if ((x==u)&&(abs(y-v)==1)&&(6<=x)&&(x<=10))return 1;
		return 0;
	} 
	if (c=='B'){
		if ((x==u+1)&&(y==v))return 1;
		if ((x==u)&&(abs(y-v)==1)&&(1<=x)&&(x<=5))return 1;
		return 0;
	}
	return 0;
}
int main(){
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	scanf("%d",&t);
	while (t--){
		for(int i=1;i<=10;i++)scanf("%s",s[i]+1);
		ans=0;
		for(int x=1;x<=10;x++)
			for(int y=1;y<=9;y++)
				if (s[x][y]!='*'){
					for(int u=1;u<=10;u++)
						for(int v=1;v<=9;v++)ans+=check(x,y,u,v);
				}
		printf("%d\n",ans);
	}
	return 0;
}
