#include<bits/stdc++.h>
using namespace std;
struct plan{int l, r;bool operator < (const plan &that)const{return this->r < that.l;}}tmp;
const int maxn = 2e5 + 10;
int n;
set<plan> st;
signed main(){
    scanf("%d",&n);
    char opt;int cnt = 0;
    for(int i = 1;i <= n;i++){
        scanf(" %c",&opt);
        if(opt == 'A'){
            scanf("%d%d",&tmp.l,&tmp.r);
            set<plan>::iterator it = st.find(tmp);cnt = 0;
            while(it != st.end()){++cnt;st.erase(it);it = st.find(tmp);}
            printf("%d\n",cnt);st.insert(tmp);
        }
        else printf("%d\n",st.size());
    }
    return 0;
}