#include <bits/stdc++.h>
using namespace std;
int n, m, ans = 0;  
int t[505];		//t��i��Ϊ��i���˵ĵ���ʱ�� 
int min[505];  //min��i��Ϊ��i���˵����ٵȴ�ʱ�� 
void dfs(int i, int st){ //�ѵ�i����,����ʱ��Ϊst����ȴ�������ʱ�� 
	if(i == n + 1)	//���������� 
		return;
	//��������˻�û���ˣ����ó��ȵ�t��i��ʱ���ٷ��� 
	if(st < t[i])  
		dfs(i, t[i]);
	//��������������˵ȳ��ͳ����ˣ�ȡ�ȴ�ʱ�����Сֵ�� 
	//������˵ȳ�
	
	//����ó����ˣ����ϵ��˶��õ�
	int wait_time ; 
}
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i<= n; i++)
		scanf("%d", &t[t]);
	dfs(1,0);
	sort(t + 1, t + n + 1);
	for(int i = 1; i <= n; i++)
		ans += min[i];
	printf("%d\n", ans);
	return 0;
}
