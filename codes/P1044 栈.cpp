#include <iostream>
#include <cstdio>
using namespace std;
int n,ans = 0;
int f[19][19]; 
void dfs(int top,int k) {
	if(k == n + 1){
		ans++;	return ;
	}
	if(top!=0) dfs(top-1,k);
	dfs(top+1,k+1);
}
int dfs1(int x,int y){ //���仯 x�Ƕ������滹�е�����y��ջ��������� 
	if(f[x][y] != 0) return f[x][y];
	if(x == 0) return 1;
	if(y > 0) f[x][y] += dfs1(x,y-1);
	f[x][y] += dfs1(x-1,y+1);
	return f[x][y];
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	//dfs(0,1);	//����dfs 80�� 
	//cout << ans << endl;
	cout <<dfs1(n,0) <<endl; //���仯 100 
	return 0;
}

