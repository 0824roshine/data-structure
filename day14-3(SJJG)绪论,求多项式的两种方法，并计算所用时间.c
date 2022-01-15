//解决问题效率和数据组织方式有关。
//如何分类？   确定类型，如何插入新的，如何寻找？
#include<math.h>
#include<stdio.h>
#include<time.h>
clock_t start, stop;
double duration1;
double duration2;
double fpow(int n, double a[], double x)
{
	double result = a[0];
	int i = 0;
	for (i = 0; i < n; i++)
	{
		result += a[i] * pow(x, i);
	}
	return result;
}
double feasy(int n, double a[], double x)
{
	double result = a[n];
	int i = 0;
	for (i = n; i > 0; i--)
	{
		result = a[i-1] + x * result;
	}
	return result;
}
int main()
{
	int i; int n = 9;
	double a[10];
	for (i = 0; i < 10; i++)
		a[i] = (double)i;
	start = clock();
	for(i=0;i<10000000;i++)
	    fpow(n, a, 1.1);
	stop = clock();
	duration1 = ((double)(stop - start))/ CLK_TCK;
	start = clock();
	for (i = 0; i < 10000000; i++)
	    feasy(n, a, 1.1);
	stop = clock();
	duration2 = ((double)(stop - start))/ CLK_TCK;
	printf("DurationFpow = %10f\n", duration1);
	printf("DurationFeasy = %10f\n", duration2);
	return 0;
}