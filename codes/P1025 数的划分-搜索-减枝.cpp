#include <cstdio>
#include <iostream>
using namespace std;
int n, k, ans = 0;
void dfs(int step, int last, int rest) {
	//stepΪ�ŵ��ڼ�����lastΪ�ϴ��õ�����rest Ϊʣ�µ��� 
	if(step == k){
		ans++;
		return;
	}
	for(int i = last; i <= rest/(k-step+1); i++) 	//i <= n ��ʱ60��
	//�����ļ�֦ �����ⳬʱ 
		dfs(step+1,i,rest-i);

}
int main() {
	cin >> n >> k;
	dfs(1,1,n); 
	cout <<ans<<endl;
	return 0;
}

