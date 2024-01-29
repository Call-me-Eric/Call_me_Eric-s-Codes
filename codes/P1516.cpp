#include<bits/stdc++.h>
using namespace std;
long long Extend_GCD(long long a,long long b,long long& x,long long &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    long long d = Extend_GCD(b,a % b,x,y);
    long long t = x;
    x = y;y = t - a / b * y;
    return d;
}
long long xpos,ypos,n,m,L;
int main(){
    cin >> xpos >> ypos >> m >> n >> L;
    long long a = n - m, b = L,c = xpos - ypos, x0 = 0,y0 = 0,d = 0;
    if(a < 0){
        c = -c;
        a = -a;
    }
    d = Extend_GCD(a,b,x0,y0);
    if(c % d != 0){
        cout << "Impossible" << endl;
        return 0;
    }
    long long x = (x0 * (c / d) % (b / d) + (b / d)) % (b / d);
    cout << x << endl;
    return 0;
}