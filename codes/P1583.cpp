/*
��w��i���Ӵ�С���򣬻���µ����d��i��
��d��i��ȡģ+1�����c��i��
��ci���ei��
���ei+wi �Ӵ�С�������ǰk�� ��������
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
struct STR{
	int w;
	int d0,d;	//d0��ʾԭʼ��� ��d��ʾ��wi�����ı�� 
	int c;
}str[20005];
int n, k, e[15];
bool cmp(STR s1, STR s2){
	if(s1.w == s2.w)
		return s1.d0 < s2.d0;
	return s1.w > s2.w;
}
int main(){
	//freopen("a.in","r",stdin);
	//freopen()
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= 10; i++)
		scanf("%d", &e[i]);
	for(int i = 1; i <= n; i++){
		scanf("%d", &str[i].w);
		str[i].d0 = i;	//ԭʼ��� 
	}
	sort(str+1, str+n+1,cmp);
//	for(int i = 1; i <= n; i++)
//		printf("%d ",str[i].w);
//	printf("\n\n");
	for(int i = 1; i <= n; i++){
		str[i].d = i;	//�����µı�� 
		str[i].c = (str[i].d -1)%10+1;
		str[i].w += e[str[i].c];
	}
	sort(str+1, str+n+1, cmp);
	for(int i = 1; i <= k; i++){
		printf("%d ",str[i].d0);
	}	
	printf("\n");	
	return 0;
}

