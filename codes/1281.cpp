#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int a[5005];
long long dp[5005];
int main() {
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
    	dp[i] = 1;//ÿ������1����Ϊ��
		//��ʼ������Լ������ʧ����
	}
	for(int i = 2;i <= n;i++){
		for(int j = 1;j < i;j++){//Ӧ����a[i]֮ǰ�����������j<i 
			if(a[j] < a[i]){
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	cout << *max_element(dp + 1, dp + 1 + n) << endl;
	return 0;
}
