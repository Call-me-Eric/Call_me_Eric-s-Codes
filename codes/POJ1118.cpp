#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
struct point{
    double x, y;
};
int main(){
    while(1){
        scanf("%d",&n);
        point* p = new point[n + 1];
        if(n == 0)break;
        for(int i = 1;i <= n;i++){
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
        int maxn = 2;
        for(int i = 1;i <= n;i++){
            for(int j = i + 1;j <= n;j++){
                int cnt = 2;
                for(int k = j + 1;k <= n;k++){
                    if((p[i].x - p[j].x) * (p[i].y - p[k].y) == 
                    (p[i].x - p[k].x) * (p[i].y - p[j].y))cnt++;
                }
                maxn = max(maxn,cnt);
            }
        }
        printf("%d\n",maxn);
        delete[] p;
    }
    return 0;
}