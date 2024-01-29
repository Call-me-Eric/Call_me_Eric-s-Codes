#include<bits/stdc++.h>
#define ld long double
using namespace std;
const int maxn = 1e5+5;
const int maxm = 5e5+5;
int d[maxn];
int head[maxn],Next[maxm],e[maxm],tot;
int deg[maxn];//入度
int degg[maxn];//出度
int n, m; 
queue<int> q;
void add(int x, int y){
	e[++tot] = y;
	Next[tot] = head[x];
	head[x] = tot;
}
struct fraction{
    int factor2,factor3,factor5;//分母由2,3,5的乘积得来
    ld molecule;//分子
    fraction operator +(fraction a){
        fraction tmp = (fraction){
            max(factor2,a.factor2),
            max(factor3,a.factor3),
            max(factor5,a.factor5),
            0
        };
        ld t1 = molecule * pow(2,tmp.factor2 - factor2)
                         * pow(3,tmp.factor3 - factor3)
                         * pow(5,tmp.factor5 - factor5);
        ld t2 = a.molecule * pow(2,tmp.factor2 - a.factor2)
                           * pow(3,tmp.factor3 - a.factor3)
                           * pow(5,tmp.factor5 - a.factor5);
        t1 += t2;
        while(round(t1 / 2) * 2 == t1 && tmp.factor2 > 0){
            tmp.factor2--;
            t1 /= 2;
        }
        while(round(t1 / 3) * 3 == t1 && tmp.factor3 > 0){
            tmp.factor3--;
            t1 /= 3;
        }
        while(round(t1 / 5) * 5 == t1 && tmp.factor5 > 0){
            tmp.factor5--;
            t1 /= 5;
        }
        tmp.molecule = t1;
        return tmp;
    }
    ld denominator(){
        return (ld)(pow(2,factor2) * pow(3,factor3) * pow(5,factor5));
    }
}ans[maxn];
fraction operator / (fraction tmp,ld a){
    while(round(a / 2) * 2 == a && a != 0){
        tmp.factor2++;
        a /= 2;
    }
    while(round(a / 3) * 3 == a && a != 0){
        tmp.factor3++;
        a /= 3;
    }
    while(round(a / 5) * 5 == a && a != 0){
        tmp.factor5++;
        a /= 5;
    }
    return tmp;
}
int topsort(int n){
	int cnt = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		cnt++;
        fraction div = ans[x] / (ld)degg[x];
		for(int i = head[x]; i; i = Next[i]){
			int y = e[i];
			deg[y]--;
            ans[y] = ans[y] + div;
			if(deg[y] == 0) q.push(y);
		}
	}
}
int main(){
    scanf("%d%d",&n,&m);
    int v = 0;
	for (int i = 1;i <= n;i++){
        scanf("%d",&d[i]);
        for(int j = 1;j <= d[i];j++){
            scanf("%d",&v);
            add(i,v);
            deg[v]++;
            degg[i]++;
        }
	}
	for(int i = 1; i <= n; i++)
		if(deg[i] == 0){
            q.push(i);
            ans[i].factor2 = ans[i].factor3 = ans[i].factor5 = 0;
            ans[i].molecule = 1;
        }
	topsort(n);
    for(int i = 1;i <= n;i++){
        if(degg[i] == 0){
            printf("%.0Lf %.0Lf\n",ans[i].molecule,ans[i].denominator());
        }
    }
	return 0;
}