#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
priority_queue<int,vector<int>,less<int> > que1,que2, que3;
int n;
signed main(){
    n = read();int ans = 0,cnt[3] = {0,0,},tot = 0;
    for(int i = 1;i <= n;i++){
        int opt = read(), x = read();
        if(opt == 00){que3.push(x);}
        if(opt == 11){ans += x;cnt[1]++;cnt[2]++;tot++;}
        if(opt == 10){que1.push(x);}
        if(opt == 01){que2.push(x);}
    }
    while(!que1.empty() && !que2.empty()){ans += que1.top() + que2.top();que1.pop();que2.pop();cnt[1]++;cnt[2]++;tot += 2;}
    int opt = 1;
    if(que1.empty()){que1 = que2;opt = 2;}
    while(!que1.empty() || !que3.empty()){
        int x = 0;
        if(!que1.empty() && cnt[3 - opt] * 2 >= tot + 1){
            x = que1.top();
        }
        int y = 0;
        if(!que3.empty() && cnt[1] * 2 >= tot + 1 && cnt[2] * 2 >= tot + 1){
            y = que3.top();
        }
        if(!x && !y)break;
        else{
            if(x > y){ans += x;que1.pop();cnt[opt]++;tot++;}
            else{ans += y;que3.pop();tot++;}
        }
    }
    printf("%lld\n",ans);
    return 0;
}