#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int sum, length;
};

struct Line
{
    int sign, l, r, h;
};

vector<char> matrix[200001];
vector<int> edges[200001];
Node tree[800001];
Line lines[200001];
char c;
bool not_root[200001];
int n, m, counter, answer, pointer, dfn[200001], sizes[200001];

int hash_(int x, int y);
void dfs(int index, int father);
bool compare(Line a, Line b);
void push_up(int from, int to, int current);
void modify(int left, int right, int from, int to, int current, int modifier);
void DEBUG(int,int,int);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        matrix[i].emplace_back(0);
        for (int j = 1; j <= m; j++)
        {
            cin >> c;
            matrix[i].emplace_back(c);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i - 2 >= 1 && matrix[i - 2].at(j) == 'U' && matrix[i - 1].at(j) == 'D')
            {
                edges[hash_(i, j)].emplace_back(hash_(i - 2, j));
                not_root[hash_(i - 2, j)] = true;
            }
            if (i + 2 <= n && matrix[i + 1].at(j) == 'U' && matrix[i + 2].at(j) == 'D')
            {
                edges[hash_(i, j)].emplace_back(hash_(i + 2, j));
                not_root[hash_(i + 2, j)] = true;
            }
            if (j - 2 >= 1 && matrix[i].at(j - 2) == 'L' && matrix[i].at(j - 1) == 'R')
            {
                edges[hash_(i, j)].emplace_back(hash_(i, j - 2));
                not_root[hash_(i, j - 2)] = true;
            }
            if (j + 2 <= m && matrix[i].at(j + 1) == 'L' && matrix[i].at(j + 2) == 'R')
            {
                edges[hash_(i, j)].emplace_back(hash_(i, j + 2));
                not_root[hash_(i, j + 2)] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!not_root[hash_(i, j)] && !dfn[hash_(i,j)])  { dfs(hash_(i, j), 0); }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (matrix[i].at(j) == 'L' || matrix[i].at(j) == 'U')  { continue; }

            int u = hash_(i, j), v, x1, x2, y1, y2;

            if (matrix[i].at(j) == 'D')  { v = hash_(i - 1, j); }
            else  { v = hash_(i, j - 1); }
            x1 = dfn[u];
            x2 = dfn[u] + sizes[u] - 1;
            y1 = dfn[v];
            y2 = dfn[v] + sizes[v] - 1;
            if ((i + j) % 2)
            {
                swap(x1, y1);
                swap(x2, y2);
            }
            printf("%d(%d,%d),(%d,%d)\n",(i+j)%2,x1,x2,y1,y2);
            lines[++pointer] = { 1, x1, x2, y1 };
            lines[++pointer] = { -1, x1, x2, y2 +1};
        }
    }
    sort(lines + 1, lines + pointer + 1, compare);
    
    printf("counter = %d\n",counter);
    for (int i = 1; i <= pointer; i++)
    {printf("[%d,%d],%d,upd = %d\n",lines[i].l,lines[i].r,lines[i].h,lines[i].sign);
        modify(lines[i].l, lines[i].r, 1, counter, 1, lines[i].sign);
        if(lines[i].h != lines[i + 1].h) answer += tree[1].length;
        printf("i = %d : %d %d %d %d\n",i,answer,tree[1].length,lines[i].h,lines[i - 1].h);
        // DEBUG(1,counter,1);
    }
    cout << answer << endl;

    return 0;
}
void DEBUG(int l = 1,int r = counter,int p = 1){
    printf("(%d,%d),p = %d,length = %d,sum = %d\n",l,r,p,tree[p].length,tree[p].sum);
    if(l == r)return; int mid = l + r >> 1;
    DEBUG(l,mid,p << 1);DEBUG(mid + 1,r,p << 1 | 1);
}

int hash_(int x, int y)
{
    return (x - 1) * m + y;
}

void dfs(int index, int father)
{
    dfn[index] = ++counter;
    sizes[index] = 1;
    for (auto son : edges[index])
    {
        if (son == father)  { continue; }
        dfs(son, index);
        sizes[index] += sizes[son];
    }
}

bool compare(Line a, Line b)
{
    if (a.h == b.h)  { return a.sign > b.sign; }
    return a.h < b.h;
}

void push_up(int from, int to, int current)
{
    if (tree[current].sum)  { tree[current].length = to - from + 1; }
    else  { tree[current].length = tree[current << 1].length + tree[current << 1 | 1].length; }
}

void modify(int left, int right, int from, int to, int current, int modifier)
{
    // printf("(%d %d) (%d %d)\n",from,to,left,right);
    if (left > to || right < from)  { return ; }
    if (left <= from && right >= to)
    {
        tree[current].sum += modifier;
        push_up(from, to, current);

        return ;
    }

    int middle = (from + to) >> 1;

    modify(left, right, from, middle, current << 1, modifier);
    modify(left, right, middle + 1, to, current << 1 | 1, modifier);
    push_up(from, to, current);
}
