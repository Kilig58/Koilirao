#include <bits/stdc++.h>
#include <time.h>
#include <Windows.h>
using namespace std;
int n[6] = {1000, 10000, 100000, 1000000, 10000000, 100000000}; //表示各档数据范围
int num1[100000000];
int num2[100000000];
int num3[100000000];

void QuickSort(int a[], int left, int right)
{
    if (left > right)
        return;
    int tmp = a[(left+right)/2];
    int i = left;
    int j = right;
    while (i != j)
    {
        while (a[j] >= tmp && j > i)
            j--;
        while (a[i] <= tmp && j > i)
            i++;
        if (j > i)
        {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[left] = a[i];
    a[i] = tmp;
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
} //快速排序

void HeapAdjust(int a[], int left, int right)
{
    int tmp = a[left];
    for (int i = 2 * left + 1; i <= right; i = i * 2 + 1)
    {
        if (i < right && a[i] < a[i + 1])
            i++;
        if (a[i] > tmp)
        {
            a[left] = a[i];
            left = i;
        }
        else
            break;
    }
    a[left] = tmp;
}
void HeapSort(int a[], int len)
{
    for (int i = (len - 1 - 1) / 2; i >= 0; i--)
    {
        HeapAdjust(a, i, len - 1);
    }
    int tmp;
    for (int i = 0; i < len - 1; i++)
    {
        tmp = a[0];
        a[0] = a[len - 1 - i];
        a[len - 1 - i] = tmp;
        HeapAdjust(a, 0, len - 1 - i - 1);
    }
} //堆排序

void MergeArray(int a[],int left,int mid,int right,int temp[])	
{
	int i=left,j=mid+1;
	int m=mid,n=right;
	int k=0;
	while(i<=m&&j<=n)
	{
		if(a[i]<a[j])
			temp[k++]=a[i++];
		else
			temp[k++]=a[j++];
	}
	while(i<=m)
		temp[k++]=a[i++];
	while(j<=n)
		temp[k++]=a[j++];
	for(i=0;i<k;i++)
		a[left+i]=temp[i];
}
void mergesort(int a[],int left,int right,int temp[])	
{
	if(left<right)
	{
		int mid=(left+right)/2;
		mergesort(a,left,mid,temp);	
		mergesort(a,mid+1,right,temp);	
		MergeArray(a,left,mid,right,temp);	
	}
}
bool MergeSort(int a[], int n)  
{  
    int *p = new int[n];
    if (p == NULL)  
        return false;  
    mergesort(a, 0, n - 1, p);  
    delete[] p;  
    return true;  
} 

int main()
{
    srand((unsigned)time(NULL));
    double run_time1, run_time2, run_time3;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    for (int j = 0; j < 6; j++)
    {
        run_time1 = run_time2 = run_time3 = 0.0;//记录调用函数所需要的时间
        // 生成升序整数数组
        for (int i = 0; i < n[j]; i++){
            num1[i] = i; 
            num2[i] = i; 
            num3[i] = i; 
        }
        // 生成降序整数数组
        int m1=0,m2=0,m3=0;
        for (int i = n[j]-1; i >= 0; i--){
            num1[m1++] = i; 
            num2[m2++] = i; 
            num3[m3++] = i; 
        }
        //生成一定区间内随机整数数组
        for (int i = 0; i < n[j]; i++){
            num1[i] = i;
        }
        for (int i = n[j]-1; i >= 1; i--)
            swap(num1[i], num1[rand() % i]); //随机一个下标进行数值交换达到随机数目的
        for(int i=0;i<n[j];i++)
            num2[i]=num3[i]=num1[i];

        //以上三种数据生成方式，每次只调用一种
        QueryPerformanceCounter(&time_start); //计时开始
        MergeSort(num1,n[j]);//合并排序
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time1 = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        QueryPerformanceCounter(&time_start); //计时开始
        QuickSort(num2, 0, n[j] - 1);//快速排序
        QueryPerformanceCounter(&time_over); //计时结束
        run_time2 = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        QueryPerformanceCounter(&time_start); //计时开始
        HeapSort(num3, n[j]);//堆排序
        QueryPerformanceCounter(&time_over); //计时结束
        run_time3 = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        printf("the range(%d)\n", n[j]);
        printf("MergeSort run_time: %fms\n", run_time1 ); //合并排序所需时间
        printf("QuickSort run_time: %fms\n", run_time2 ); //快速排序所需时间
        printf("HeapSort  run_time: %fms\n", run_time3 ); //堆排序所需时间
        
    }

    //以下为检测三个函数是否可用的操作
    /*
    int n1;
    cin >> n1;
    for (int i = 0; i < n1; i++){
        num1[i] = i;
    }
    for (int i = n1-1; i > 0; i--)
        swap(num1[i], num1[rand() % i]);
    for (int i = 0; i < n1; i++)
        cout << num1[i] << " ";
    cout<<endl;
    HeapSort(num1, n1);
    MergeSort(num1, n1);
    QuickSort(num1, 0, n1 - 1);
    for (int i = 0; i < n1; i++)
        cout << num1[i] << " ";
    */
    
    return 0;
}
