#include<bits/stdc++.h>
#define LL long long
using namespace std;
int k, n;
const LL mod = 1e9 + 7;
const int maxn = 5e5 + 100;
LL c[maxn],d[maxn],e[maxn];//e[i]Ϊ��ǰ��ƫ����
LL l[20], r[20];//l,r����һ�ֵ�iά������˲�����(����)�ĺ����Ҷ˲����ϵĵ�(����)
LL w[20];
LL ans = 1;
int main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= k;i++){
        scanf("%lld",&w[i]);
        ans = ans * w[i] % mod;
    }
    //��ʱans = ���е�(ÿһ�������߳���ʱҲ��һ��)
    for(int i = 1;i <= n;i++){
        scanf("%lld%lld",&c[i],&d[i]);
    }
    while(1){//ö��ÿһ��
        for(int i = 1;i <= n;i++){
            //��¼ƫ����
            e[c[i]] += d[i];
            //���±߽�
            l[c[i]] = min(l[c[i]],e[c[i]]);
            r[c[i]] = max(r[c[i]],e[c[i]]);
            LL s = 1;
            for(int j = 1;j <= k;j++){
                if(r[j] - l[j] >= w[j]){
                    printf("%lld",ans);
                    return 0;//���е��Ѿ�ȫ������
                }
                s = s * (w[j] - r[j] + l[j]) % mod;//���Ϻϸ�ĵ�
            }
            ans = (ans + s) % mod;
            //���´�
        }
        bool book = 1;
        for(int i = 1;i <= k;i++){
            if(e[i] != 0){//����߲���ȥ
                book = 0;
                break;
            }
        }
        if(book){
            puts("-1");
            return 0;
        }
    }
    return 0;
}