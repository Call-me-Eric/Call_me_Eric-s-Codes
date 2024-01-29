#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int maxn = 1e6 + 100;
int T;
int n;
int a[maxn];
char ans[maxn];
int tot;
int lefta,righta,totb;
bool book = 0;
bool left[maxn], right[maxn];
int b[maxn];
bool check(){
    for(int i = 1;i <= n;i++){
        if(b[i] != b[2 * n + 1 - i])return false;
    }
    return true;
}
void dfs(int now){
    if(book)return;
    if(now > 2 * n){
        if(check()){
            for(int i = 1;i < tot;i++){
                putchar(ans[i]);
            }
            putchar('\n');
            book = 1;
            return;
        }
        return;
    }
    //L
    if((tot <= n && left[a[lefta]] == 0)){
        ans[tot] = 'L';
        b[totb] = a[lefta];
        left[a[lefta]] = 1;
        lefta++;totb++;
        tot++;
        dfs(now + 1);
        tot--;
        ans[tot] = 0;
        b[totb] = 0;
        lefta--;totb--;
        left[a[lefta]] = 0;
    }
    else if(tot > n && a[lefta] == b[2 * n + 1 - totb] && right[a[lefta]] == 0){
        ans[tot] = 'L';
        b[totb] = a[lefta];
        right[a[lefta]] = 1;
        lefta++;totb++;
        tot++;
        dfs(now + 1);
        tot--;
        ans[tot] = 0;
        b[totb] = 0;
        lefta--;totb--;
        right[a[lefta]] = 0;
    }
    //R
    if((tot <= n && left[a[righta]] == 0)){//
        ans[tot] = 'R';
        left[a[righta]] = 1;
        tot++;
        b[totb] = a[righta];
        righta--;totb++;
        dfs(now + 1);
        tot--;
        ans[tot] = 0;
        b[totb] = 0;
        righta++;totb--;
        left[a[righta]] = 0;
    }
    else if(tot > n && a[righta] == b[2 * n + 1 - totb] && right[a[righta]] == 0){
        ans[tot] = 'R';
        right[a[righta]] = 1;
        tot++;
        b[totb] = a[righta];
        righta--;totb++;
        dfs(now + 1);
        tot--;
        ans[tot] = 0;
        b[totb] = 0;
        righta++;totb--;
        right[a[righta]] = 0;
    }
}
void percent_40(){
    while(T--){
        memset(left,0,sizeof(left));
        memset(right,0,sizeof(right));
        book = 0;
        tot = 1;
        scanf("%d",&n);
        righta = n * 2;
        lefta = 1;
        totb = 1;
        for(int i = 1;i <= n * 2;i++){
            scanf("%d",&a[i]);
        }
        dfs(1);
        if(book == false){
            puts("-1");
        }
    }
}
int main(){/*
    freopen("palin.in","r",stdin);
    freopen("palin.out","w",stdout);*/
    scanf("%d",&T);
    percent_40();
    return 0;
}
/*
2
5
4 1 2 4 5 3 1 2 3 5
3
3 2 1 2 1 3

*/