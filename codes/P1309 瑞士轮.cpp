#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct stru {					//�ṹ��洢id��s��w��ֵ 
	int id, s, w;
}a[200005],win[100005],lose[100005];
int n,r,q; 
int cmp(stru s1, stru s2) {		//cmp�ȽϺ��� 
	if(s1.s == s2.s) return s1.id < s2.id;
	return s1.s > s2.s;
}
int qread(){			//������򣬶Ա���ûɶ�ô� 
	int x = 0, f= 1;
	char ch =getchar();
	while(ch <  '0' || ch >  '9') { if(ch== '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') { x=x*10+ch-'0'; ch = getchar();}
	return x*f;
} 
void merage(){
	int i = 1, j = 1, s = 1;
	while(s <= 2*n){
		if(i >n) {	//i >n ˵��win��i��������ɣ�lose��j��û������� 
			while(j <=n)
				a[s++] = lose[j++];
		}
		if(j >n) {
			while(i<=n)
				a[s++] = win[i++];
		}
		//�ϲ������֣���������� 
		if(win[i].s > lose[j].s ||(win[i].s == lose[j].s && win[i].id < lose[j].id))
			a[s++] = win[i++];
		else
			a[s++] = lose[j++];
	}
}

int main(){
//	freopen("1.in","r",stdin);
//	freopen("11.out","w",stdout);

	n = qread(); r= qread() ;q = qread();   //scanf("%d%d%d",&n,&r,&q);
	int n1= 2*n;
	for(int i = 1; i <= n1; i++){
		a[i].id = i;
		a[i].s = qread(); 	//scanf("%d",&man[i].s);
	}
	for(int j = 1; j <= n1; j++)	
		a[j].w = qread();   //scanf("%d",&man[j].w);
	stable_sort(a+1, a+n1+1,cmp);
	for(int k = 1; k <= r; k++){
		int k1=1, k2=1;	
		for(int i = 1; i <= n1; i+=2){
			if(a[i].w > a[i+1].w) {
				a[i].s++;
				win[k1++] = a[i];
				lose[k2++] =a[i+1];
				
			}
			else {
				a[i+1].s++;
				win[k1++] = a[i+1];
				lose[k2++] =a[i];
			}
		}
		merage();
		//merge(lose+1,lose+n+1,win+1,win+n+1,a+1,cmp);  //STL��merge���� 
		//stable_sort(a+1, a+n1+1,cmp);		//ÿ�ο��Żᳬʱ80�֣�sort 60�� �����鿪100000���ָ��� 
	}

	printf("%d\n",a[q].id);
	return 0;
}

