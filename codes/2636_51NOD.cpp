//�˳���ʱ�临�Ӷ�ΪO(n * log n)(nΪ����վ��Ŀ) 
#include<cstdio>
#include<queue>
#include<algorithm>
#define LL long long
using namespace std;
priority_queue<LL> que;
LL n, l, p;
LL k, ans;
LL t1, t2, a[10000001], b[100001];
//������i��ļ���վ,a[i] = ������ b[���] = i 
int main(){
	k = 0;
	scanf("%lld%lld%lld",&l,&p,&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld%lld",&t1,&t2);
		a[t1] = t2;
		b[i] = t1;
	}
	sort(b + 1,b + 1 + n);
	for(int i = 1;i <= n;i++){
		if(p < b[i] - k){
			//����Ͳ�������һ������վ
			if(que.empty()){
				printf("-1");
				return 0;
				//�����ɼ��;ͽ������� 
			}
			else {
				while(p < b[i] - k){//�ɼ��;ͼӵ��㹻Ϊֹ 
					p += que.top();
					que.pop();
					ans++;
				}
				p = p - b[i] + k;
				k = b[i];
				que.push(a[b[i]]);
			}
		}
		else{//�͹��Ļ� 
			p = p - b[i] + k;
			k = b[i];
			que.push(a[b[i]]);
		}
	}
	if(k < l){
		k += p;
		p = 0;
		while(k < l && (!que.empty())){
			k += que.top();
			que.pop();
			ans++;
		}
		if(k < l && que.empty()){
			printf("-1");
			return 0;
		}
	}
	printf("%lld",ans);
	return 0;
}
