#include <bits/stdc++.h>
#include <time.h>
#include <Windows.h>
using namespace std;
int N[6] = {150,1500,15000,150000,1500000, 6000000};//随机数略大于数据范围
int n[6] = {100, 1000, 10000, 100000, 1000000, 5000000};//表示各档数据范围
int num[6000000];
int check1(int a[], int value, int n)
{
    int low, high, mid, flag = 1;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (a[mid] == value)
            return mid;
        if (a[mid] > value)
            high = mid - 1;
        if (a[mid] < value)
            low = mid + 1;
    }
    return -1;
}//二分查找
int check2(int a[], int value, int n)
{
    for (int i = 0; i < n; i++)
        if (a[i] == value)
            return i;
    return -1;
}//顺序查找
int main()
{
    srand((unsigned)time(NULL));
    double run_time1, run_time2;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    for(int j=0;j<6;j++){
        double sum1 = 0.0;
        double sum2 = 0.0;
        for (int i = 0; i < 1000; i++)
        {
            for (int i = 0; i <= N[j]; ++i)
                num[i] = i; //生成0到N[j]的顺序int形数字
            for (int i = N[j]; i >= 1; --i)
                swap(num[i], num[rand() % i]); //随机一个下标进行数值交换达到随机数目的
            sort(num, num + n[j]);
            // sort函数进行排序
            //其中N表示生成随机数的范围，n表示测试数据范围为num[0] - num[n-1]
            //每次循环都生成不同的随机数
            int num1 = (rand() << 10) + rand();
            num1 %= n[j];//生成随机数
            QueryPerformanceCounter(&time_start); //计时开始
            check1(num, num1, n[j]); //为了准确计算算法的运行时间，没有输出结果，但经过验证算法能够正确输出答案
            QueryPerformanceCounter(&time_over);  //计时结束
            run_time1 = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
            sum1 += run_time1;
            // printf("%d+run_time1:%fus\n",check1(num,num1,n),run_time);
            QueryPerformanceCounter(&time_start); //计时开始
            check2(num, num1, n[j]);
            QueryPerformanceCounter(&time_over); //计时结束
            run_time2 = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
            sum2 += run_time2;
        }
        printf("the range(%d) :run_time1:%fus\n", n[j], sum1 / 1000.0);//二分查找所需时间
        printf("the range(%d) :run_time2:%fus\n", n[j], sum2 / 1000.0);//顺序查找所需时间
    }
    return 0;
}
