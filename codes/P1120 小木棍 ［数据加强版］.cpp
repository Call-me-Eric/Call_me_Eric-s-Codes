#include <bits/stdc++.h>
using namespace std;
int n, m, a[65], next[65], len, sum = 0, cnt = 0;
bool used[65], ok;
bool cmp(int x , int y){
	return x > y ;
}
void dfs(int k, int last, int rest){
	//kΪ����ƴ��ľ���ı�ţ�lastΪ����ƴ��ľ����ǰһ�ڱ��
	//restΪ��ľ����δƴ�ĳ��� 
	int i ;
	if(rest == 0){
		if(k == m){   //�Ż�6���Ҵ�𰸾��Ƴ� 
			ok = 1;
			return;
		}
		for(i = 1; i <= cnt; i++)
			if(!used[i])
				break;
		used[i] = 1;
		dfs(k + 1 , i , len - a[i]);
		used[i] = 0;
		if(ok) return ;
	}
	//�Ż�4�������ҵ�һ��ľ�����Ȳ�����δƴ����rest��λ�� 
	int l = last + 1 , r = cnt, mid;
	while(l < r){
		mid = (l + r) >> 1;
		if(a[mid] <= rest) r = mid;
		else	l = mid + 1;
	}
	for (i = l; i <= cnt; i++){
		if(!used[i]){ //�Ż�5���ж��Ƿ��ù� 
			used[i] = 1;
			dfs(k, i , rest - a[i]);
			used[i] = 0;
			if(ok) return ;	//�Ż�6 
			if(rest ==a[i] || rest == len) return ;//�Ż�7 
			i = next[i];
			if(i == cnt) return ;
		}
	} 
} 
int main(){
	scanf("%d", &n);
	for (int i = 1;i <= n; i++){
		int t;
		scanf("%d", &t);
		if(t > 50) continue;
		a[++cnt] = t;
		sum += t;
	}
	sort(a+1, a+n+1, cmp);	//�Ż�1���Ӵ�С���� 
	next[cnt] = cnt;
	for (int i = cnt - 1; i > 0; i--){//�Ż�3��Ԥ����next���� 
		if(a[i] == a[i + 1])
			next[i] = next[i+1];
		else
			next[i] = i; 
	}
	for(len = a[1]; len <= sum /2; len++){
		if(sum % len == 0){
			m = sum / len;
			ok = 0;
			used[1] = 1;
			dfs(1, 1, len -a[1]);
			used[1] = 0;
			if(ok){			//�Ż�6���ҵ���С�ľͲ����� 
				printf("%d\n", len);
				return 0;
			}
		}		
	}
	printf("%d\n", sum);	//���һ���� 
	return 0;
}
