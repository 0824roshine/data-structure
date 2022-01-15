//�������Ч�ʺ�������֯��ʽ�йء�
//��η��ࣿ   ȷ�����ͣ���β����µģ����Ѱ�ң�
#include<math.h>
#include<stdio.h>
int maxSubArray(int* nums, int numsSize) {
    int tmp = nums[0]; int i = 1; int tgt = nums[0];
    for (; i < numsSize; i++)
    {
        if (tmp < 0)
            tmp = 0;
        tmp += nums[i];
        if (tmp > tgt)
            tgt = tmp;
    }
    return tgt;
}
int maxSubArray_Official(int* nums, int numsSize) {
    int pre = 0, maxAns = nums[0];
    for (int i = 0; i < numsSize; i++) {
        pre = fmax(pre + nums[i], nums[i]);
        maxAns = fmax(maxAns, pre);
    }
    return maxAns;
}

int main()
{
	int i; int n = 9;
	return 0;
}