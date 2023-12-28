#include<bits/stdc++.h>
using namespace std;
const int maxn = 20;
char ch[maxn][maxn];
int n = 10, m = 9;
//					 0        3          7            11          15          19
const int dx[20] = { 0,-1, 1, 0, 1, 1,-1,-1, 2, 2,-2,-2, 1, 1,-1,-1, 2, 2,-2,-2};
const int dy[20] = {-1, 0, 0, 1, 1,-1, 1,-1, 2,-2, 2,-2,-2, 2,-2, 2,-1, 1,-1, 1};
bool is_lower(char c){return c <= 'z' && c >= 'a';}
bool is_upper(char c){return c <= 'Z' && c >= 'A';}
void solve(){
	for(int i = 1;i <= n;i++)
		scanf("%s",ch[i] + 1);
	int cnt = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			switch(ch[i][j]){
				case 'j':{//TODO j
					for(int k = 0;k < 4;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(nx < 1 || nx > 3 || ny < 4 || ny > 6)continue;
						if(is_lower(ch[nx][ny]))continue;
						cnt++;
					}
					bool flag = false;
					for(int k = i + 1;k <= n;k++){
						if(ch[k][j] != '*'){
							flag = (ch[k][j] == 'J');
							break;
						}
					}
					cnt += flag;
					break;
				}
				case 'J':{
					for(int k = 0;k < 4;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(nx < 8 || nx > 10 || ny < 4 || ny > 6)continue;
						if(is_upper(ch[nx][ny]))continue;
						cnt++;
					}
					bool flag = false;
					for(int k = i - 1;k;k--){
						if(ch[k][j] != '*'){
							flag = (ch[k][j] == 'j');
							break;
						}
					}
					cnt += flag;
					break;
				}
				case 's':{//TODO s
					for(int k = 4;k < 8;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(nx < 1 || nx > 3 || ny < 4 || ny > 6)continue;
						if(is_lower(ch[nx][ny]))continue;
						cnt++;
					}
					break;
				}
				case 'S':{
					for(int k = 4;k < 8;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(nx < 8 || nx > 10 || ny < 4 || ny > 6)continue;
						if(is_upper(ch[nx][ny]))continue;
						cnt++;
					}
					break;
				}
				case 'x':{//TODO x
					for(int k = 8;k < 12;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(nx < 1 || nx > 5 || ny < 1 || ny > 9)continue;
						if(ch[(i + nx) / 2][(j + ny) / 2] != '*')continue;
						if(is_lower(ch[nx][ny]))continue;
//						printf("nx = %d,ny = %d, i = %d, j = %d,dx = %d,dy = %d\n",nx,ny,i,j,dx[k],dy[k]);
						cnt++;
					}
					break;
				}
				case 'X':{
					for(int k = 8;k < 12;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(nx < 6 || nx > 10 || ny < 1 || ny > 9)continue;
						if(ch[(i + nx) / 2][(j + ny) / 2] != '*')continue;
						if(is_upper(ch[nx][ny]))continue;
						cnt++;
					}
					break;
				}
				case 'c':{
					for(int k = i + 1;k <= n;k++){
						if(ch[k][j] != '*'){
							if(ch[k][j] <= 'Z' && ch[k][j] >= 'A')cnt++;
							break;
						}
						cnt++;
					}
					for(int k = i - 1;k;k--){
						if(ch[k][j] != '*'){
							if(ch[k][j] <= 'Z' && ch[k][j] >= 'A')cnt++;
							break;
						}
						cnt++;
					}
					
					for(int k = j + 1;k <= m;k++){
						if(ch[i][k] != '*'){
							if(ch[i][k] <= 'Z' && ch[i][k] >= 'A')cnt++;
							break;
						}
						cnt++;
					}
					for(int k = j - 1;k;k--){
						if(ch[i][k] != '*'){
							if(ch[i][k] <= 'Z' && ch[i][k] >= 'A')cnt++;
							break;
						}
						cnt++;
					}
					break;
				}
				case 'C':{
					for(int k = i + 1;k <= n;k++){
						if(ch[k][j] != '*'){
							if(ch[k][j] <= 'z' && ch[k][j] >= 'a')cnt++;
							break;
						}
						cnt++;
					}
					for(int k = i - 1;k;k--){
						if(ch[k][j] != '*'){
							if(ch[k][j] <= 'z' && ch[k][j] >= 'a')cnt++;
							break;
						}
						cnt++;
					}
					
					for(int k = j + 1;k <= m;k++){
						if(ch[i][k] != '*'){
							if(ch[i][k] <= 'z' && ch[i][k] >= 'a')cnt++;
							break;
						}
						cnt++;
					}
					for(int k = j - 1;k;k--){
						if(ch[i][k] != '*'){
							if(ch[i][k] <= 'z' && ch[i][k] >= 'a')cnt++;
							break;
						}
						cnt++;
					}
					break;
				}
				case 'm':{
					for(int k = 12;k < 16;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(ch[i][(j + ny) / 2] != '*')continue;
						if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
						if(is_lower(ch[nx][ny]))continue;
						cnt++;
					}
					for(int k = 16;k < 20;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(ch[(i + nx) / 2][j] != '*')continue;
						if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
						if(is_lower(ch[nx][ny]))continue;
						cnt++;
					}
					break;
				}
				case 'M':{
					for(int k = 12;k < 16;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(ch[i][(j + ny) / 2] != '*')continue;
						if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
						if(is_upper(ch[nx][ny]))continue;
						cnt++;
					}
					for(int k = 16;k < 20;k++){
						int nx = dx[k] + i, ny = dy[k] + j;
						if(ch[(i + nx) / 2][j] != '*')continue;
						if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
						if(is_upper(ch[nx][ny]))continue;
						cnt++;
					}
					break;
				}
				case 'p':{
					for(int k = i + 1;k <= n;k++){
						if(ch[k][j] != '*')break;
						cnt++;
					}
					for(int k = i - 1;k;k--){
						if(ch[k][j] != '*')break;
						cnt++;
					}
					
					for(int k = j + 1;k <= m;k++){
						if(ch[i][k] != '*')break;
						cnt++;
					}
					for(int k = j - 1;k;k--){
						if(ch[i][k] != '*')break;
						cnt++;
					}
					
					for(int k = 1;k <= i - 1;k++){
						int flag = 0;if(!is_upper(ch[k][j]))continue;
						for(int u = k + 1;u < i;u++)flag += (ch[u][j] != '*');
						if(flag == 1)cnt++;
					}
					for(int k = i + 1;k <= n;k++){
						int flag = 0;if(!is_upper(ch[k][j]))continue;
						for(int u = i + 1;u < k;u++)flag += (ch[u][j] != '*');
						if(flag == 1)cnt++;
					}
					for(int k = 1;k <= j - 1;k++){
						int flag = 0;if(!is_upper(ch[i][k]))continue;
						for(int u = k + 1;u < j;u++)flag += (ch[i][u] != '*');
						if(flag == 1)cnt++;
					}
					for(int k = j + 1;k <= m;k++){
						int flag = 0;if(!is_upper(ch[i][k]))continue;
						for(int u = j + 1;u < k;u++)flag += (ch[i][u] != '*');
						if(flag == 1)cnt++;
					}
					break;
				}
				case 'P':{
					for(int k = i + 1;k <= n;k++){
						if(ch[k][j] != '*')break;
						cnt++;
					}
					for(int k = i - 1;k;k--){
						if(ch[k][j] != '*')break;
						cnt++;
					}
					
					for(int k = j + 1;k <= m;k++){
						if(ch[i][k] != '*')break;
						cnt++;
					}
					for(int k = j - 1;k;k--){
						if(ch[i][k] != '*')break;
						cnt++;
					}
//					printf("i = %d, j = %d, cnt = %d\n",i,j,cnt);
					for(int k = 1;k <= i - 1;k++){
						int flag = 0;if(!is_lower(ch[k][j]))continue;
						for(int u = k + 1;u < i;u++)flag += (ch[u][j] != '*');
						if(flag == 1){cnt++;}
					}
					for(int k = i + 1;k <= n;k++){
						int flag = 0;if(!is_lower(ch[k][j]))continue;
						for(int u = i + 1;u < k;u++)flag += (ch[u][j] != '*');
						if(flag == 1){cnt++;}
					}
					for(int k = 1;k <= j - 1;k++){
						int flag = 0;if(!is_lower(ch[i][k]))continue;
						for(int u = k + 1;u < j;u++)flag += (ch[i][u] != '*');
						if(flag == 1){cnt++;}
					}
					for(int k = j + 1;k <= m;k++){
						int flag = 0;if(!is_lower(ch[i][k]))continue;
						for(int u = j + 1;u < k;u++)flag += (ch[i][u] != '*');
						if(flag == 1){cnt++;}
					}
					break;
				}
				case 'b':{
					if(i < 10 && !is_lower(ch[i + 1][j]))cnt++;
					if(i >= 6 && i <= 10 && j >= 1 && j <= 9){
						if(j != 1){if(!is_lower(ch[i][j - 1]))cnt++;}
						if(j != 9){if(!is_lower(ch[i][j + 1]))cnt++;}
					}
					break;
				}
				case 'B':{
					if(i > 1 && !is_upper(ch[i - 1][j]))cnt++;
					if(i >= 1 && i <= 5 && j >= 1 && j <= 9){
						if(j != 1){if(!is_upper(ch[i][j - 1]))cnt++;}
						if(j != 9){if(!is_upper(ch[i][j + 1]))cnt++;}
					}
					break;
				}
				default:break;
			}
//			printf("%d ",cnt);
		}
//		puts("");
	}
	printf("%d\n",cnt);
	return;
}
signed main(){
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--){solve();}
	return 0;
}
/*
1
BB**j**C*
*xcsP****
pC**c****
**M**P***
b*m****x*
**bb****M
X**X**B**
*m*******
***SSB***
*****J*p*

*/
