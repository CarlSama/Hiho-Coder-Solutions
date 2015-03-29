#include<iostream>
#include<cstdio>
using namespace std;

/*
 * 在**非有序数组**中查找特定值，
 * 并获得其排名
 *
 * 非常简单，使用quick sort解决第k小问题的思路，
 * 遍历一次数组即可解决
 */
int binarySearch(int* sum,int len,int destV){
	int leftNum = 0;
	bool isFound = false;

	for(int i=0;i<len;i++){
		if(sum[i] < destV){
			leftNum++;
		}else if(sum[i] == destV){
			isFound = true;
		}else{
			;
		}
	}
	if(isFound)
		return leftNum + 1;
	else
		return -1;
}

int main(){
	int len,destV;
	freopen("info","r",stdin);
	cin>>len>>destV;

	int *sum = new int[len+1];
	for(int i=0;i<len;i++){
		cin>>sum[i];
	}

	printf("%d\n",binarySearch(sum,len,destV));
}
