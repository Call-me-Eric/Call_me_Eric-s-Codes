#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
class Splay{
//#define DEBUG 114514
    private:
    int root, tot;
    struct node{
        int fa, child[2], val, cnt, size;
     }d[maxn];
    
    void maintain(int x){d[x].size = d[d[x].child[0]].size + d[d[x].child[1]].size + d[x].cnt;}
    bool get(int x){return x == d[d[x].fa].child[1];}
    void clear(int x){d[x].child[0] = d[x].child[1] = d[x].cnt = d[x].fa = d[x].size = d[x].val = 0;}
    
    void rotate(int x){//旋转(双层)
        int y = d[x].fa, z = d[y].fa;int pos = get(x);
        d[y].child[pos] = d[x].child[pos ^ 1];
        if(d[x].child[pos ^ 1])d[d[x].child[pos ^ 1]].fa = y;
        d[x].child[pos ^ 1] = y;
        d[y].fa = x;
        d[x].fa = z;
        if(z) d[z].child[y == d[z].child[1]] = x;
        maintain(y); maintain(x);
    }
    void splay(int x){//将x转到根上
        for(int f = d[x].fa;f = d[x].fa,f;rotate(x))
            if(d[f].fa) rotate(get(x) == get(f) ? f : x);
        root = x;
    }
    void ins(int k){
        if(!root){//如果当前是一棵空树
            d[++tot].val = k;//直接加进来就好
            d[tot].cnt++;
            root = tot;
            maintain(root);
            return;
        }
        int u = root, f = 0;//如果不是
        while(1){
            if(d[u].val == k){//如果之前插入过相等的元素
                d[u].cnt++;//原来的cnt++就行
                maintain(u);
                maintain(f);//别忘了更新
                splay(u);
                break;
            }
            f = u;
            u = d[u].child[d[u].val < k];
            if(!u){//如果走到了绝路(即夹在fa[u]和pre(fa[u])(或nxt(fa[u])(当val[u]>=k))之间,且之间再没有元素了)
                d[++tot].val = k;//那就新加一个元素,在fa[u]的左儿子(或右儿子)上
                d[tot].cnt++;
                d[tot].fa = f;
                d[f].child[d[f].val < k] = tot;
                maintain(tot);
                maintain(f);//更新
                splay(tot);//转到根上
                break;
            }
        }
    }
    int rk(int k){
        int res = 0, u = root;
        while(1){
            if(k < d[u].val){//如果k在u的左子树上
                u = d[u].child[0];
            }
            else{//否则
                //k一定比左子树所有元素大
                res += d[d[u].child[0]].size;//排名要加上size[lchild]
                if(k == d[u].val){//如果k刚好在u节点上
                    splay(u);
                    return res + 1;//注意题中的定义(比k小的数的个数+1),所以要res+1
                }
                res += d[u].cnt;//否则k比u的元素都大,加上cnt[u]
                u = d[u].child[1];//跳到u的右子树
            }
        }
    }
    int kth(int k){//基本与rk(int)同理
        int u = root;
        while(1){
            if(d[u].child[0] && k <= d[d[u].child[0]].size) u = d[u].child[0];
            else {
                k -= d[u].cnt + d[d[u].child[0]].size;
                if(k <= 0){splay(u); return d[u].val;}
                u = d[u].child[1];
            }
        }
    }
    int pre(){
        int u = d[root].child[0];//根据平衡树的性质,root的前驱一定在root的左子树上
        if(!u)return u;//当然如果没有左子树自然就没有前驱(此时root是整棵树上最小的)
        while(d[u].child[1])u = d[u].child[1];//又因为要找比root大的数中最小的,那就一直往右子树上跳
        splay(u); return u;//不要忘了把前驱提到root上
    }
    int suf(){
        int u = d[root].child[1];
        if(!u)return u;
        while(d[u].child[0])u = d[u].child[0];
        splay(u); return u;
    }
    void del(int k){
        rk(k);//把要删的元素提到根上
        if(d[root].cnt > 1){//如果节点数大于1
            d[root].cnt--; maintain(root);//那最好办,减去一个点就好了
            return;
        }
        if(!d[root].child[0] && !d[root].child[1]){//或者整个树只有一个节点
            clear(root);root = 0;//那就让整棵树变成空树
            return;
        }
        if(!d[root].child[0]){//如果只有右子树
            int u = root;
            root = d[root].child[1];//让原右子树的根作为新根
            d[root].fa = 0;//新根没有父亲[怎么听着怪怪的:(]
            clear(u);//然后删掉新根的左子树
            return;
        }
        if(!d[root].child[1]){//如果只有左子树
            int u = root;//那就和上面反过来
            root = d[root].child[0];
            d[root].fa = 0;
            clear(u);
            return;
        }
        //如果以上几种情况都不是
        int u = root;//先记录一下原根
        int x = pre();//然后把原根的前驱转到根上
        d[d[u].child[1]].fa = x;//接下来把原根的右子树接到新根上
        d[x].child[1] = d[u].child[1];//新根的右儿子变成原根的右儿子,架空原根
        clear(u);//删除原根
        maintain(root);//更新新根状态
    }
    public:
    void insert(int x){ins(x);}
    void delet(int x){del(x);}
    int prenum(){return d[pre()].val;}
    int sufnum(){return d[suf()].val;}
    int rank(int x){return rk(x);}
    int ranknum(int x){return kth(x);}
}tree;
int n;
signed main(){
    n = read(); int op, x;
    for(int i = 1;i <= n;i++){
        op = read(); x = read();
        switch(op){
            case 1:tree.insert(x);break;
            case 2:tree.delet(x);break;
            case 3:printf("%d\n",tree.rank(x));break;
            case 4:printf("%d\n",tree.ranknum(x));break;
            case 5:tree.insert(x);printf("%d\n",tree.prenum());tree.delet(x);break;
            case 6:tree.insert(x);printf("%d\n",tree.sufnum());tree.delet(x);break;
            default:break;
        }
    }
    return 0;
}