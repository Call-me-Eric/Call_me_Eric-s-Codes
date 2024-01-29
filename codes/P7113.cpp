#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
int gcd(int a,int b){
	if(a == 0 || b == 0)return 1;
	int c;
	while(a % b != 0){
		c = a % b;
		a = b;
		b = c;
	}
	return b;
}
int lcd(int a,int b){
	int c = gcd(a, b);
	return a * b / c;
}
struct fenshu{
	int fenzi, fenmu;
	void print(){
		printf("%d %d\n",fenzi,fenmu);
		return;
	}
};
fenshu yuefen(int a,int b){
	int c = gcd(a,b);
	a /= c;
	b /= c;
	fenshu d;
	d.fenzi = a;
	d.fenmu = b;
	return d;
}
fenshu operator/(fenshu a,fenshu b){
	return yuefen(a.fenzi * b.fenmu,a.fenmu * b.fenzi);
}
fenshu operator+(fenshu a,fenshu b){
	int c = lcd(a.fenmu, b.fenmu);
	int d = c / a.fenmu;
	int e = c / b.fenmu;
	fenshu k;
	k.fenmu = c;
	k.fenzi = a.fenzi * d + b.fenzi * e;
	return k;
}
//jshou[i] == 0则i节点为接收口;pchu[i] == 1则i节点为排出口 
bool jshou[10050], pchu[10050], book[10050];
int n, m;
int edge[10050][7];
fenshu num[10050];
int point[10050];
int k = 1;
int que[10050];
int head = 1, tail = 1;
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&edge[i][0]);
		if(edge[i][0] == 0)pchu[i] = 1;
		else
			for(int j = 1;j <= edge[i][0];j++){
				scanf("%d",&edge[i][j]);
				jshou[edge[i][j]] = 1;
			}
	}
	for(int i = 1;i <= n;i++){//处理排水口\接收口
		if(jshou[i] == 0){
			num[i].fenzi = num[i].fenmu = 1;
			que[head] = i;
			head++;
		}
		if(pchu[i] == 1){
			point[k++] = i;
		}
	}
	k--;
	int tmp = 0;
	while(tail < head){
		tmp = que[tail];
		if(edge[tmp][0] != 0){
			fenshu a;
			a.fenzi = edge[tmp][0];
			a.fenmu = 1;
			a = num[tmp] / a;
			for(int i = 1;i <= tmp;i++){
			//	num[edge[tmp][i]] = num[edge[tmp][i]] + a;//此处有问题 
				que[head++] = edge[tmp][i];
			}
			tail++;
		}
		else tail++;
	}
	for(int i = 1;i <= k;i++){
		num[point[i]].print();
	}
	return 0;
}

