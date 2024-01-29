//http://class.51nod.com/Classes/Problem.html#courseProblemId=1720&classId=129
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm> 
using namespace std;
int n,m,col[151];
int u[121],v[124];
int f[141];
int getf(int x){
	if(f[x] == x)return x;
	else return f[x] = getf(f[x]);
}
struct edge{
	int u,v;
	int w;
}e[234];
struct cmp{
	bool operator()(edge a,edge b){
		return a.w < b.w;
	}
};
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&col[i]);
		f[i] = i;
	}
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&u[i],&v[i]);
		e[i].u = u[i];
		e[i].v = v[i];
		e[i].w = (col[u[i]] == col[v[i]]);
	}
	int f1 = 0,f2 = 0,ans = 0,flag = 0;
	sort(e + 1,e + 1 + m,cmp());
	for(int i = 1;i <= m;i++){
		f1 = getf(f[e[i].u]);
		f2 = getf(f[e[i].v]);
		if(f1 != f2){
			f[f1] = f2;
			ans += e[i].w;
		}
	}
	printf("%d",ans);
	return 0;
}

