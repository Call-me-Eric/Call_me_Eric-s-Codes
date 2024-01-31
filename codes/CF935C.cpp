#include<bits/stdc++.h>
using namespace std;
double R, x_1,x_2,y_1,y_2;
signed main(){
    scanf("%lf%lf%lf%lf%lf",&R,&x_1,&y_1,&x_2,&y_2);
    double len = sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
    if(len > R){printf("%.7lf %.7lf %.7lf\n",x_1,y_1,R);}
    else if(x_1 == x_2 && y_1 == y_2){printf("%.7lf %.7lf %.7lf\n",x_1 + R / 2.0,y_1,R / 2.0);}
    else printf("%.7lf %.7lf %.7lf\n"
    ,x_1 + ((len - R) * (x_2 - x_1) / len / 2.0)
    ,y_1 + ((len - R) * (y_2 - y_1) / len / 2.0)
    ,(R + len) / 2.0);
    return 0;
}