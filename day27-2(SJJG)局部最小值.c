//二分法实现局部最小值问题 罗尔定理
#include<stdio.h>
#include<string.h>
int LocalMini(int *arr,int len)
{
	int right = len - 1, left = 0;
	int mid = 0;
	if (arr[left] < arr[left + 1])
		return left;
	else if (arr[right - 1] > arr[right])
		return right;
	else
	{
		while (left + 1 < right)
		{
			mid = (left + right)/2;
			if (arr[mid] < arr[mid + 1])
				right = mid;
			else
				left = mid;
		}
		if (arr[left] < arr[right])
			return left;
		else
			return right;
	}
	
}
void test()
{
	int arr[] = { 69,61,68,67,66,65,64,40,31,51,52,53,81,91,92,93,94 };
	int arr1[] = { 69,68,67,66,5,68,69,70,71,72,73,81,91,92,93,94 };
	int size = sizeof(arr) / sizeof(arr[0]);
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	int num = LocalMini(arr, size);
	printf("%d\n", arr[num]);
	int num1 = LocalMini(arr1, size1);
	printf("%d\n", arr1[num1]);
}
int main()
{
	test();
	return 0;
}