#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
char S[maxn], T[maxn];

struct node{
    int pos, col;
    node(int p = 0,int col = 0):pos(p),col(col){}
};
stack<node> stk1, stk2;
vector<pair<int,int> > ans;

signed main(){
    scanf("%s",S + 1);scanf("%s",T + 1);
    for(int i = 1, len = strlen(S + 1);i <= len;i++){
        if(stk1.empty()){stk1.push(node(i,S[i] == 'a'));}
        else{
            node tmp = stk1.top();stk1.pop();
            if(tmp.col == (S[i] == 'a')){tmp.pos = i;stk1.push(tmp);}
            else{stk1.push(tmp);stk1.push(node(i,S[i] == 'a'));}
        }
    }
    for(int i = 1, len = strlen(T + 1);i <= len;i++){
        if(stk2.empty()){stk2.push(node(i,T[i] == 'a'));}
        else{
            node tmp = stk2.top();stk2.pop();
            if(tmp.col == (T[i] == 'a')){tmp.pos = i;stk2.push(tmp);}
            else{stk2.push(tmp);stk2.push(node(i,T[i] == 'a'));}
        }
    }

    if(stk1.top().col != stk2.top().col){stk1.pop();stk2.pop();}
    else {if(stk1.size() > stk2.size()){stk1.pop();}else stk2.pop();}
    int rev = 1;
    while(!stk1.empty() || !stk2.empty()){
        rev ^= 1;int u, v;
        
        if(stk1.empty()){u = 0;}
        else {u = stk1.top().pos;stk1.pop();}
        
        if(stk2.empty()){v = 0;}
        else {v = stk2.top().pos;stk2.pop();}
        
        if(rev)swap(u, v);
        ans.push_back(make_pair(u, v));
    }
    freopen("CF1012D.out","w",stdout);
    printf("%d\n",ans.size());
    freopen("CF1012D1.out","w",stdout);
    for(auto i : ans){printf("%d %d\n",i.first,i.second);}
    return 0;
}