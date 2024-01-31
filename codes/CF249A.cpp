#include<bits/stdc++.h>
using namespace std;
double y1, y2, yw, xb, yb, r, xw;
signed main(){
    scanf("%lf%lf%lf%lf%lf%lf",&y1,&y2,&yw,&xb,&yb,&r);
    double a = yw - y1 - 2.0 * r,b = yw - yb - r,x = a * xb / (a + b),l = sqrt(x * x + a * a),ans =x * (y2 - y1 - r) / l;
    if(r > ans)puts("-1");
    else printf("%.10lf\n",x);
    return 0;
}