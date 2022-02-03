#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<malloc.h>
#include<assert.h>
#include<time.h>
/*
                         	ʱ		��		�ȶ���

ѡ������ 	N2		1		���ȶ��� 3 3 3 3 1 3 3 4 5
ð��       		N2		1		����ʵ���ȶ��� ���ʱ���û�����        
�������� 	N2		1		����ʵ���ȶ��� ���ʱ���ò������
���ţ�		NlgN		N		��˫ָ�룬partation���̻ᷢ������
						���ָ�����С�ڵ��������ұ�����������
�鲢��		NlgN		lgN		�ȿ�����ߵľͿ��ԣ���С��-�ȿ����ұߵģ�
�ѣ�   		NlgN		1		��heapinsert���̣�û��ʵ���ȶ�
*/
______________________________________________________________________________________________________________
/*
1.  �鲢�ռ临�Ӷȿ�����o1�������ѣ�û��Ҫ����ɥʧ�ȶ��ԣ�����ֱ���ö�����
2.  ԭ�ع鲢������������ʱ�����oN^2, �����ò�������ʵ��
3.  ���ſ��������ȶ��ԣ���̫�ѣ����ÿ��ŵĿռ临�Ӷȱ�ΪN������ֱ���ù鲢��
 ________________________________________________�����Ķ�����bullshit��unimportant
4. ��������ߣ�ż�����ұߣ����򱣳ֲ��䣬����ռ临�Ӷ�1��ʱ�临�Ӷ�N���ܷ�������
     ���ű�������(0-1)��׼����żҲ������partationʵ�֣������ѡ�0-1-stablesort��
*/
_______________________________________________________________________________________________________________
/*
1.�ۺ�����
quicksort���������ܴ�ʱ�����ÿ��ŵĵ���˼�룬
                  С�������µ�����ʱ��ֱ�ӽ��в�������oN^2,����ʱ��͡�
2.ϵͳ�Դ����򣺣�
���������ÿ��ţ���Ϊ������Ϊ�ȶ���û���壬��ʱ�����ó���ʱ��͵Ŀ��š�
�Զ������ͣ���ṹ�壬����ѡ���ù鲢
*/
________________________________________________________________________________________________________________
void swaparr(int* arr, int x, int y)
{
	int tmp = 0;
	tmp = *(arr + x);
	*(arr + x) = *(arr + y);
	*(arr + y) = tmp;
}
// �����ʵ�ֽ���
void swaparr1(int* arr, int x, int y)
{
	arr[x] = arr[x] ^ arr[y];
	arr[y] = arr[x] ^ arr[y];
	arr[x] = arr[x] ^ arr[y];
}
//_ N^2 ������\_____________________________________________________________              

//1   ѡ������
void selection_sort(int* arr, int len)
{
	int tmp;
	int i = 0, j = 0;
	for (i = 0; i < len; i++)
	{
		for (j = i + 1, tmp = i; j < len; j++)
			tmp = (arr[j] < arr[tmp] ? j : tmp);
		swaparr(arr, i, tmp);
	}
}
//2   ð������
void bubble_sort(int* arr, int len)
{
	int i = 0, j = 0;
	for (i = len - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
				swaparr1(arr, j, j + 1);
		}
	}
}
//3   ��������
void insert_sort(int* arr, int len)
{
	int i = 0,j = 0;
	for (i = 1; i < len; i++)
	{
		for (j = i; j >=0 && (arr[j] < arr[j - 1]); j--)
			swaparr(arr, j, j - 1);
	}	
}
//4-1 �鲢���� -> ��С��  _______�Ƚϵ���Ϣ�����´��ݣ��������˷ѱȽ���Ϊ nlgn  n
void merge(int* arr2, int L, int M, int R)
{
	int length =R-L+1;
	int* p = (int*)malloc(sizeof(int) * length);
	int i = 0, p1 = L, p2 = M + 1;      //˫ָ����ʼλ��
	while (p1 <= M && p2 <= R)          //С�ڵ��ڣ��Ͼ��������ֶ�Ҫ����
	{
		if (arr2[p1] <= arr2[p2])
			p[i++] = arr2[p1++];
		else
			p[i++] = arr2[p2++];
	}
	while (p1 <= M)
		p[i++] = arr2[p1++];
	while (p2 <= R)
		p[i++] = arr2[p2++];
	for (i = 0; i < length; i++)
		arr2[L+i] = p[i];
	free(p);
	p = NULL;
}
void half(int* arr1, int L, int R)
{
	if (L == R)
		return;
	int M = L + ((R - L) >> 1);
	half(arr1, L, M);
	half(arr1, M + 1, R);
	merge(arr1, L, M, R);
}
void merge_sort(int* arr,int len)
{
	if (arr == NULL && len < 2)
		return ;
	else
		half(arr, 0, len - 1);
}
//4-2 ��С��
int sum_while_merge(int* arr2, int L, int M, int R)
{
	int length = R - L + 1;
	int res = 0;
	int* p = (int*)malloc(sizeof(int) * length);
	int i = 0, p1 = L, p2 = M + 1;      //˫ָ����ʼλ��
	while (p1 <= M && p2 <= R)          //С�ڵ��ڣ��Ͼ��������ֶ�Ҫ����
	{
		res += arr2[p1] < arr2[p2] ? (R-p2+1)*arr2[p1] : 0;
		p[i++] = arr2[p1] < arr2[p2] ? arr2[p1++] : arr2[p2++];
	}
	while (p1 <= M)
		p[i++] = arr2[p1++];
	while (p2 <= R)
		p[i++] = arr2[p2++];
	for (i = 0; i < length; i++)
		arr2[L + i] = p[i];
	free(p);
	p = NULL;
	return res;
}
int sum_by_half(int* arr1, int L, int R)
{
	if (L == R)
		return 0;
	int M = L + ((R - L) >> 1);
	return sum_by_half(arr1, L, M)+ 
		sum_by_half(arr1, M + 1, R)+
		sum_while_merge(arr1, L, M, R);
}
int small_sum(int* arr, int len)
{
	if (arr == NULL && len < 2)
		return 0;
	else
		return sum_by_half(arr, 0, len - 1);
}
//5   �������� ������ֵ�й�    from������������-> 
void Netherlandflag(int* arr, int len)
{
	int num = 10;
	int L = 0,R=len-1;
	int smaller = L - 1, larger = R;
	while (L < larger)              //ע����С���ұ߽�
	{
		if (arr[L] < num)
			swaparr(arr, L++, (++smaller));
		else if (arr[L] > num)
			swaparr(arr, L, (--larger));
		else
			L++;
	}
}
int* partation(int*arr,int L,int R)
{
	int smaller = L - 1, larger = R;
	while (L < larger)
	{
		if (arr[L] < arr[R])
			swaparr(arr, L++, ++smaller);
		else if (arr[L] > arr[R])
			swaparr(arr, L, --larger);
		else
			L++;
	}
	swaparr(arr, larger, R);
	int *res =(int*)malloc(2 * sizeof(int));
	res[0] = smaller+1;
	res[1] = larger;
	return res;
}
void quick_sort(int*arr,int L,int R)
{
	if (L < R)
	{
		srand(time(NULL));
		int pos = rand() % (R - L) + L;
		swaparr(arr, pos, R);
		int* p = partation(arr, L, R);
		quick_sort(arr, L, p[0] - 1);
		quick_sort(arr, p[1] + 1, R);
	}
}
//6   ������    ��ȫ������ ����heapinsert�������ɴ���� �������Ƴ�������logN
// ���ȼ����нṹ�����Ƕѽṹ
// �ӹ��ܣ�heapinsert heapify��������heapifyʵ��heapinsert      �������������
void heapinsert(int* arr,int index)
{
	while (arr[index]>arr[(index-1)/2])
	{
		swaparr(arr, index, (index - 1) / 2);
		index = (index - 1)/2;
	}
}
void heapify(int* arr, int index,int heapsize)
{
	int left =2*index+1;
	while (left < heapsize)
	{
		int largest = left + 1 < heapsize && arr[left + 1] > arr[left]
			? left + 1 : left;
		largest = arr[largest] > arr[index]
			? largest : index;
		if (largest == index)
			break;
		swaparr(arr, largest, index);
		index = largest;
		left = index * 2 + 1;
	}
}
void heap_sort(int* arr,int len)
{
	if (arr == NULL || len < 2)
		return;
	/*for (int i = 0; i < len; i++)    //o(logN)  
	    heapinsert(arr, i);*/
	for (int i = len - 1; i >= 0; i--)  // ��ײ�ڵ�N/2����
		heapify(arr, i, len);
	int heapsize = len;
	swaparr(arr, 0, --heapsize);
	while (heapsize)
	{
		heapify(arr,0, heapsize);
		swaparr(arr,0, --heapsize);
	}
}
//7   Ͱ����
/*
   arr = {  013,   021,  011,  052,  062  }
  count��Ƶ�� [10]= { 0 2 2 1 0 0 0 0 0 0 }  -->   { 0 2 4 5 5 5 5 5 5 5 }
   ĳһλ�ϣ���λ�� count[i],����i�����м���              <= 2�����м���
   ��arr, �������󣬸���count��ֵ����arr�����ֵ����help���൱�ڡ���Ͱ��
   ��λ<=2 ������4����help={   ,   ,   ,062,   ,}   count[2]-1 { 0 2 3 5 ....
   ��λ<=2 ������3����help={   ,   ,052,062,   ,}   count[2]-1 { 0 2 2 5 ....
   ��λ<=1 ������2����help={   ,011,052,062,   ,}   count[2]-1 { 0 1 2 5 ....
   ��λ<=1 ������1����help={021,011,052,062,   ,}   count[2]-1 { 0 0 2 5 ....

*/
int get_digit(int* arr, int len)
{
	int max = arr[0],i=0;
	for ( i = 0; i < len; i++)
		max = max > arr[i] ? max : arr[i];
	i = 0;
	while (max)
	{
		max /= 10;
		i++;
	}
	return i;
}
int get_the_numofdigit(int a, int b)
{
	for (int i = 1; i < b; i++)
		a /= 10;
	return a%10;
}
void bucket(int* arr, int L, int R, int digit)
{
	int* help = (int*)malloc(sizeof(int) * (R - L + 1));
	const int count = 10;
	int i = 1, j = 0,tmp=0;
	for (i=1;i <= digit;i++)
	{
		int frqcy[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (j = L; j <=R; j++)
		{
			tmp = get_the_numofdigit(arr[j], i);
			frqcy[tmp] = frqcy[tmp]+ 1;
		}
		for (j = 1; j < 10; j++)
			frqcy[j] = frqcy[j] + frqcy[j - 1];
		for (j = R; j >= L; j--)
		{
			tmp= get_the_numofdigit(arr[j], i);
			help[frqcy[tmp]-1] = arr[j];
			frqcy[tmp] = frqcy[tmp] - 1;
		}
		for (j = L; j <= R; j++)
			arr[j] = help[j];
	}
}
void Bucket_sort(int* arr, int len)
{
	if (arr == NULL || len < 2)
		return;
	bucket(arr, 0, len - 1, get_digit(arr, len));
}
//_____________________________________________________________
void test1()
{
	{
		int arr[] = { 11,4,2,18,54,22,0,3 };
		int size = sizeof(arr) / sizeof(arr[0]);
		selection_sort(arr, size);
		for (int k = 0; k < size; k++)
			printf("%d  ", arr[k]);
		printf("\n");

		int arr2[] = { 11,4,2,18,54,22,0,3 };
		size = sizeof(arr2) / sizeof(arr2[0]);
		bubble_sort(arr2, size);
		for (int k2 = 0; k2 < size; k2++)
			printf("%d  ", arr2[k2]);

		int arr3[] = { 11,4,2,18,54,22,0,3 };
		size = sizeof(arr3) / sizeof(arr3[0]);
		insert_sort(arr3, size);
		for (int k3 = 0; k3 < size; k3++)
			printf("%d  ", arr2[k3]);
	}

	
}
void test2_mergesort()
{
	int arr5[] = { 11,4,2,18,54,22,1};
	int size0 = sizeof(arr5) / sizeof(arr5[0]);
	merge_sort(arr5,size0);
	for (int k5 = 0; k5 < size0; k5++)
		printf("%d  ", arr5[k5]);
	printf("\n");
}
void test_smallsum()
{
	int arr7[] = {1,3,4,2,5};
	int size7 = sizeof(arr7) / sizeof(arr7[0]);
	printf("%d\n", small_sum(arr7, size7));
	return 0;
}
void test_Netherland_flag()
{
	int arr6[] = { 3,14,15,9,26,5,3,5,7,21,10,15 };
	int size6 = sizeof(arr6) / sizeof(arr6[0]);
	Netherlandflag(arr6, size6);
	for (int k6 = 0; k6 < size6; k6++)
		printf("%d  ", arr6[k6]);
	printf("\n");
}
void test_qsort()
{
	int arr[] = { 3,14,15,92,65,35,8,9,79,32,38,46,26,43,3,83,27,9,5,0,28,8,41,97,16,11 };
	int size = sizeof(arr) / sizeof(arr[0]);
	quick_sort(arr, 0,size-1);
	for (int k = 0; k < size; k++)
		printf("%d  ", arr[k]);
	printf("\n");
}
void test_heapsort()
{
	int arr[] = { 3,14,15,92,65,35,8,9,79,32,38,46,26,43,3,83,27,9,5,0,28,8,41,97,16,11 };
	int size = sizeof(arr) / sizeof(arr[0]);
	heap_sort(arr, size);
	for (int k = 0; k < size; k++)
		printf("%d  ", arr[k]);
	printf("\n");
}
void test_bucketsort()
{
	int arr[] = { 114,514,114514,4,3,14,15,92,65,35,8,9,79,32,38,46,26,43,3,83,27,9,5,0,28,8,41,97,16,11 };
	int size = sizeof(arr) / sizeof(arr[0]);
	Bucket_sort(arr, size);
	for (int k = 0; k < size; k++)
		printf("%d  ", arr[k]);
	printf("\n");
}
int main()
{
	/*test2_mergesort();
	test_smallsum();
	test_Netherland_flag();*/
	//test_qsort();
	/*test_heapsort();*/
	test_bucketsort();
	return 0;	
}