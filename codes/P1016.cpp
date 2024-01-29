#include<bits/stdc++.h>
using namespace std;
int n;
double d[101] , d0, d1, d2, pi[101], c, l, mile,p;
double x,ans;
//pi[p
int main(){
    cin >> d1 >> c >> d2 >> p >> n;
    for(int i = 1;i <= n;i++){
        cin >> d[i] >> pi[i];
    }
    x = c * d2;
    d[0] = 0;
    pi[0] = p;
    for(int i = 1;i <= n;i++){
        if(d[i] - d[i - 1] > x){
            printf("No Solution\n");
            return 0;
        }
    }
    int j = 0;
    double pmin = 10000.0;
    while(d1 - d0){
        for(int i = j + 1;x >= d[i] - d0 && i <= n;i++){
            if(pi[i] < pmin){pmin = pi[i];j = i;}
        }
        if(pmin <= p){//如果有比自己便宜的
            ans += ((d[j] - d0)/d2 - l) * p;
            l = (d[j] - d0) / d2;
        }
        else if(d1 - d0 > x){//如果自己最便宜且到不了终点
            ans += (c - l) * p;
            l = c;
        }
        else{//可以到终点
            ans += ((d1 - d0) / d2 - l) * p;
            break;
        }
        l = l - (d[j] - d0) / d2;
        d0 = d[j];
        p = pmin;
        pmin = 10000.0;
    }
    printf("%.2lf",ans);
    return 0;
}