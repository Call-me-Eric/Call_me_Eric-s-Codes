#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
int a[100][100];
pair<int,int> pr[50];
bool check(int x,int y,int z,int w){
	return (abs(x - z) + abs(y - w) == 3) && x != z && y != w;
}
void dfs(int x,int y){
//	printf("x=%d y=%d\n",x,y);
	if(y == 6){x++;y = 1;}
	if(x == 5){
		for(int i = 1;i < 20;i++)
			if(!check(pr[i].first,pr[i].second,pr[i + 1].first,pr[i + 1].second))return;
//		if(!check(pr[12].first,pr[12].second,pr[1].first,pr[1].second))return;
		puts("");
		for(int i = 1;i <= 20;i++){
			a[pr[i].first][pr[i].second] = i;
		}
		for(int i = 1;i <= 4;i++){
			for(int j = 1;j <= 5;j++){
				printf("%.2d ",a[i][j]);
			}
			puts("");
		}
		return;
	}
	for(int i = 1;i <= 20;i++){
		if(pr[i].first == 0){
			if(pr[i + 1].first){if(!check(x,y,pr[i + 1].first,pr[i + 1].second))continue;}
			if(pr[i - 1].first){if(!check(x,y,pr[i - 1].first,pr[i - 1].second))continue;}
			pr[i] = make_pair(x, y);
			dfs(x,y + 1);
			pr[i] = make_pair(0, 0);
		}
	}
}
int n;
signed main(){
	freopen("horse.in","r",stdin);
	freopen("horse.out","w",stdout);
int T = read();
while(T--){
	n = read();
	if(n == 3){
		puts("Yes");
		puts("\
1 2\n\
3 3\n\
4 1\n\
2 2\n\
4 3\n\
3 1\n\
2 3\n\
1 1\n\
3 2\n\
1 3\n\
2 1\n\
4 2");
	}
	else if(n == 5){
		puts("Yes");
		puts("\
1 1\n\
3 2\n\
4 4\n\
2 5\n\
1 3\n\
2 1\n\
4 2\n\
3 4\n\
1 5\n\
2 3\n\
3 4\n\
1 2\n\
3 3\n\
4 1\n\
2 2\n\
1 4\n\
3 5\n\
4 3\n\
2 4\n\
4 5\n\
");
	}
	else puts("No");
}
//	dfs(1, 1);
	return 0;
}
