#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e3 + 10;
struct node{
    int val, id;
    node(int v = 0,int i = 0):val(v),id(i){}
    friend bool operator < (node a,node b){return a.val < b.val;}
};
priority_queue<node,vector<node>,less<node> > q1,q2,q3;
int n, x, y;
int a[maxn], b[maxn];
int opt[maxn];
signed main(){
    n = read();x = read(); y = read();int ans = 0;
    for(int i = 1;i <= n;i++)q1.push(node(a[i] = read(),i));
    for(int i = 1;i <= n;i++)q2.push(node(b[i] = read(),i));
    for(int i = 1;i <= n;i++)q3.push(node(b[i] - a[i],i));
    for(int i = 1;i <= x;i++){
        int pos = q1.top().id; opt[pos] = 1;
        ans += q1.top().val; q1.pop();
    }
    while(!q1.empty())q1.pop();
    for(int i = 1;i <= n;i++)if(opt[i] != 1)q1.push(node(a[i],i));
    for(int i = 1;i <= y;i++){
        int op = 0, j, k,val = 0;
        while(!q2.empty() && opt[q2.top().id] != 0)q2.pop();
        if(!q2.empty()){
            val = q2.top().val;
            j = q2.top().id; op = 1;
        }
        while(!q1.empty() && opt[q1.top().id] != 0)q1.pop();
        while(!q3.empty() && opt[q3.top().id] != 1)q3.pop();
        if(!q1.empty() && !q3.empty()){
            if(q3.top().val + q1.top().val > val){
                val = q3.top().val + q1.top().val;
                j = q3.top().id; k = q1.top().id; op = 2;
            }
        }
        if(op == 1){ans += val;q2.pop();opt[j] = 2;}
        else{ans += val;opt[k] = 1;opt[j] = 2;q1.pop();q3.pop();}
    }
    printf("%d\n",ans);
    for(int i = 1;i <= n;i++)if(opt[i] == 1)printf("%d ",i);puts("");
    for(int i = 1;i <= n;i++)if(opt[i] == 2)printf("%d ",i);puts("");
    return 0;
}