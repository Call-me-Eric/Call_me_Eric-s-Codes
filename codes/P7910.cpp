#include<bits/stdc++.h>
using namespace std;
int n,Q;
struct note{
    int a, id;
}a[10000];
    bool cmp(note a,note b){
        if(a.a != b.a) return a.a < b.a;
        else return a.id < b.id;
    }

int id[10000];
int main(){
    scanf("%d%d",&n,&Q);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i].a);
        a[i].id = i;
    }
    int temp,x,y;
    sort(a + 1,a + 1 + n,cmp);
    for(int i = 1;i <= n;i++){
        id[a[i].id] = i;
    }
    while(Q--){
        scanf("%d",&temp);
        if(temp == 1){
            scanf("%d%d",&x,&y);
            a[id[x]].a = y;
            for(int i = n;i > 1;i--){
                if(cmp(a[i],a[i - 1])){
                    note tmp = a[i];
                    a[i] = a[i- 1];
                    a[i- 1] = tmp;
                }
            }
            for(int i = 2;i <= n;i++){
                if(cmp(a[i],a[i - 1])){
                    note tmp = a[i];
                    a[i] = a[i- 1];
                    a[i- 1] = tmp;
                }
            }
            for(int i = 1;i <= n;i++){
                id[a[i].id] = i;
            }
        }
        else{
            scanf("%d",&x);
            printf("%d\n",id[x]);
        }
    }
    
    return 0;
}