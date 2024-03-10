#include<iostream>
#include<stdio.h>
#include<string.h>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1)+ ch - '0';ch = getchar();}
	return x * f;
}
int T, n, m;
char ch[100][100];
bool changed[100][100];
bool dfs(int i,int j,int to){
	if(i < 1 || i > n || j < 1 || j > m)return false;
	if(ch[i][j] == '-' || ch[i][j] == '|')return true;
	if(ch[i][j] == '#')return false;
	if(ch[i][j] == '/'){
		if(to == 0){
			return dfs(i,j - 1,1);
		}
		if(to == 1){
			return dfs(i + 1,j,0);
		}
		if(to == 2){
			return dfs(i,j + 1,3);
		}
		if(to == 3){
			return dfs(i - 1,j,2);
		}
	}
	if(ch[i][j] == '\\'){
		if(to == 2){
			return dfs(i,j - 1,1);
		}
		if(to == 3){
			return dfs(i + 1,j,0);
		}
		if(to == 0){
			return dfs(i,j + 1,3);
		}
		if(to == 1){
			return dfs(i - 1,j,2);
		}
	}
	if(ch[i][j] == '.' || ch[i][j] == ','){
		ch[i][j] = ',';
		if(to == 0){
			return dfs(i + 1,j,to);
		}
		if(to == 1){
			return dfs(i,j - 1,to);
		}
		if(to == 2){
			return dfs(i - 1,j,to);
		}
		if(to == 3){
			return dfs(i,j + 1,to);
		}
	}
}
signed main(){
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	T = read();
	while(T--){
		bool flag = 0;
		n = read();m = read();
		for(int i = 1;i <= n;i++){
			scanf("%s",ch[i] + 1);
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(ch[i][j] == '-'){
					if(dfs(i,j,3) || dfs(i,j,1)){
						changed[i][j] = 1;
						ch[i][j] = '|';
					}
				}
				if(ch[i][j] == '|'){
					if(dfs(i,j,0) || dfs(i,j,2)){
						if(changed[i][j]){
							puts("IMPOSSIBLE");
							flag = 1;
							break;
						}
						else {
							changed[i][j] = 1;
							ch[i][j] = '-';
						}
					}
				}
				if(ch[i][j] == '-' && changed[i][j]){
					if(dfs(i,j,3) || dfs(i,j,1)){
							puts("IMPOSSIBLE");
							flag = 1;
							break;
					}
				}
			}
			if(flag)break;
		}
		if(flag)continue;
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(ch[i][j] == '.'){
					puts("IMPOSSIBLE");
					flag = 1;
					break;
				}
			}
			if(flag)break;
		}
		if(flag)continue;
		puts("POSSIBLE");
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(ch[i][j] == ',')putchar('.');
				else putchar(ch[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;
}

