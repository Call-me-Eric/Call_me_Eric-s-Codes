/*
对w【i】从大到小排序，获得新的序号d【i】
对d【i】取模+1，获得c【i】
由ci获得ei，
最后按ei+wi 从大到小排序，输出前k个 最初的序号
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
struct STR{
	int w;
	int d0,d;	//d0表示原始编号 ，d表示按wi排序后的编号 
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
		str[i].d0 = i;	//原始编号 
	}
	sort(str+1, str+n+1,cmp);
//	for(int i = 1; i <= n; i++)
//		printf("%d ",str[i].w);
//	printf("\n\n");
	for(int i = 1; i <= n; i++){
		str[i].d = i;	//产生新的编号 
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

