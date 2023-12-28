#include<iostream>
#include<algorithm>
#include<cstdio>

#define maxn 1000005

using namespace std;

int arr[maxn], countArr[maxn];
int prefixSum[maxn];

bool flag[maxn];

int stack1[maxn], stack2[maxn];
int top1, top2;

int binarySearch1(int x)
{
    int left = 1, right = top1, mid, result = 0;

    while (left <= right)
    {
        mid = (left + right) >> 1;
        if (stack1[mid] < x)
        {
            right = mid - 1;
            result = top1 - mid + 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return result;
}

int binarySearch2(int x)
{
    int left = 1, right = top2, mid, result = 0;

    while (left <= right)
    {
        mid = (left + right) >> 1;
        if (stack2[mid] < x)
        {
            right = mid - 1;
            result = top2 - mid + 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return result;
}

int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int i = 1;
    while (i <= n)
    {
        cin >> arr[i];

        i++;
    }

    int tmp = arr[1];

    i=2;
    while (i <= n)
    {
        if (arr[i] < tmp)
        {
            tmp = arr[i];
            flag[i] = 1;
            countArr[i] = countArr[i - 1] + 1;
        }
        else
        {
            countArr[i] = countArr[i - 1];
        }

        i++;
    }

    int ans = 0;

    cout << 1 << " ";
    stack1[0] = 11451419;
    int last = 1;

    i=2;
    while (i <= n)
    {
        if (!flag[i])
        {
            tmp = binarySearch1(arr[i]) + (arr[i] != arr[last]);
            ans += tmp;

            if (stack1[top1] > arr[i] && arr[i] != arr[last])
            {
                stack1[++top1] = arr[i];
            }

            prefixSum[i] = prefixSum[i - 1] + binarySearch2(arr[i]) + 1;

            if (i == 2)
            {
                stack2[++top2] = arr[2];
            }
            if (i > 2)
            {
                if (stack2[top2] > arr[i])
                    stack2[++top2] = arr[i];
            }
        }
        else
        {
            ans = countArr[i] + prefixSum[i - 1] + binarySearch2(arr[1]) + 1;
            prefixSum[i] = prefixSum[i - 1] + 1;

            top1 = top2;
            stack1[top1] = stack2[top2];
            stack2[++top2] = arr[i];

            if (stack1[top1] > arr[1] || top1 == 0)
            {
                stack1[++top1] = arr[1];
            }

            last = i;
        }

        cout << ans + i << " ";

        i++;
    }

    return 0;
}
