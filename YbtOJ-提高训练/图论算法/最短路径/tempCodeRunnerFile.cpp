#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;

int n,k;
int scc[MAXN],sum,low[MAXN],dfn[MAXN],cnt,tot[MAXN];
//以上是强连通图的必备变量，唯一tot是记录每个强连通分量里面有多少个点 
int dp[MAXN];
//这个用于DP记录答案 
int in[MAXN];
//这个记录入度，用于Topo 
long long ans;
//最终答案 
struct Node{
	int next;//记录每个点的下一个点 
	int v;//记录边权 
};
vector<Node>nei[MAXN];//旧图 
vector<Node>nnei[MAXN];//新图 
bool Stack[MAXN];//用于Tarjan 
stack<int> s;//用于Tarjan

inline int read(){//快速读入 
    int f = 1, x = 0;
    char c = getchar();

    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }

    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }

    return f * x;
}


void Tarjan(int u){//Tarjan模板 
	low[u] = dfn[u] = ++cnt;
	Stack[u] = true;
	s.push(u);
	
	int len = nei[u].size();
	for(int i = 0;i < len; i++){
		int next = nei[u][i].next;
		
		if(dfn[next] == 0){
			Tarjan(next);
			low[u] = min(low[u],low[next]);
		}else
		if(Stack[next]){
			low[u] = min(low[u],dfn[next]);
		}
	}
	
	if(dfn[u] == low[u]){
		sum++;
		scc[u] = sum;
		Stack[u] = false;
		tot[sum]++;
		
		while(s.top() != u){
			Stack[s.top()] = false;
			scc[s.top()] = sum;
			s.pop();
			tot[sum]++;
		}
		s.pop();
	}
}

int main()
{
	n = read(),k = read();//读入 
	
	for(int i = 1;i <= k; i++){
		int z = read(),x = read(),y = read();
		switch(z){//使用开关函数 
			case 1:{//一号情况 
				nei[x].push_back((Node){y,0});
				nei[y].push_back((Node){x,0});
				//这里一定要建两条边！ 
				break;
			}
			case 2:{//二号情况 
				nei[x].push_back((Node){y,1});
				break;
			}
			case 3:{//三号情况 
				nei[y].push_back((Node){x,0});
				break;
			}
			case 4:{//四号情况 
				nei[y].push_back((Node){x,1});
				break;
			}
			case 5:{//五号情况 
				nei[x].push_back((Node){y,0});
				break;
			}
		}
	}

	for(int i = 1;i <= n; i++){
    	if(dfn[i] == 0)Tarjan(i);//Tajan 
    }

    for(int i = 1;i <= n; i++){//建新图 
    	int len = nei[i].size();
		
		for(int j = 0;j < len; j++){
			int next = nei[i][j].next;
			int xx = scc[i];
        	int yy = scc[next];
        
        	if(xx == yy && nei[i][j].v == 1){//判断无解  
        		cout<<-1<<"\n";
        		return 0;
			}
        
        	if(xx != yy){//建新图 
        	    nnei[xx].push_back((Node){yy,nei[i][j].v});
        	    in[yy]++;
        	}
		}
    }
    
    queue<int>q;//Topo模板 
    
    for(int i = 1;i <= sum; i++){//将入读为0的压入队列 
    	if(!in[i]){
    		q.push(i);
    		dp[i] = 1;//初始化 
		}
	}
	
	while(!q.empty()){//拓扑模板 
		int cur = q.front();
		q.pop();
		int len = nnei[cur].size();
		
		for(int i = 0;i < len; i++){
			int next = nnei[cur][i].next;
			in[next]--;
			dp[next] = max(dp[next],dp[cur] + nnei[cur][i].v);//Dp方程 
			
			if(!in[next])q.push(next);
		}
	}
    for(int i = 1;i <= n;i++){
        printf("%d belongs to %d\n",i,scc[i]);
    }
	for(int i = 1;i <= sum;i++){
        printf("%d %d\n",dp[i],tot[i]);
    }
	for(int i = 1;i <= sum; i++){//累加答案 
		ans += (long long) dp[i] * tot[i];
	}
	cout<<ans;//输出 
	return 0;
}