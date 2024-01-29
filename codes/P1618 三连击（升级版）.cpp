#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[10],b[10],f[10];
int a1, b1, c1;
bool flag = false;
int judge(int x, int y ,int z) {
	memset(f,0,sizeof(f));
	for(int i = 1; i <= 3; i++){
		f[x%10] ++; f[y%10] ++; f[z%10]++;
		x /= 10; y /= 10; z/= 10;
	}
	for(int i = 1; i <= 9; i++)
		if(f[i] != 1) return 0;
	return 1;
}
void dfs(int step){ //搜每一位放什么 
	if(step == 4){
//		for(int i = 1; i <= 3; i++)	//测试输出正常 
//			cout << a[i] << ' ';
//		cout <<endl;
		int numa = 100*a[1] + 10*a[2] + a[3];
		int numb = numa * b1 / a1, numc = numa * c1 /a1;
		if(numb>987 || numc>987) {
			return;	
		}
		if(judge(numa,numb,numc)){
			cout << numa <<' '<< numb <<' '<< numc<<endl;
			flag = true;
		}
		return;
	}
	for(int i = 1; i <= 9; i++)
	if(!b[i]) {
		b[i] = 1;
		a[step] = i;
		dfs(step+1);
		b[i] = 0;
		
	}
}
int main(){
	cin >> a1 >> b1 >> c1;
	dfs(1) ;
	if(!flag) cout <<"No!!!"<< endl; 
	return 0;
}

