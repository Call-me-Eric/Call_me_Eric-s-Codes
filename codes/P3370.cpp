#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10, base = 131;
const int mod[2] = {(int)(1e7 + 7),(int)(1e7 + 9)};
class Hash_Table{
    private:
    bool hash[2][int(1e7 + 8)];
    int hash_mod(char *s,int op){
        int val = 0,len = strlen(s);
        for(int i = 0;i < len;i++){val = (val * base + s[i]) % mod[op];}
        return val;
    }
    void insert(char *s){
        int p0 = hash_mod(s,0) ,p1 = hash_mod(s,1);
        hash[0][p0] = hash[1][p1] = 1;
    }
    bool findd(char *s){
        int p0 = hash_mod(s,0), p1 = hash_mod(s,1);
        if(hash[0][p0] && hash[1][p1])return true;
        else return false;
    }
    public:
    void ins(char *s){insert(s);}
    bool find(char *s){return findd(s);}
}HT;
int n, ans;
char ch[maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch);
        if(!HT.find(ch)){HT.ins(ch);ans++;}
    }
    printf("%d\n",ans);
    return 0;
}