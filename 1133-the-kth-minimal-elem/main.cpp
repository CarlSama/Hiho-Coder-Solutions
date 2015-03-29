#include<iostream>
#include<ctime> 
#include<cstdlib>
#include<cstdio>

using namespace std;

void swap(int &l,int &r){
	int tmp = l;
	l = r;
	r = l;
}

//we manage num[left] ~ num[right]
//At last, we get the (minIdx+1-left+1)th elem num[midIdx+1]
int partition(unsigned int *num,int left, int right, int &pivotVal){
	int pivotIdx = rand() % (right - left + 1) + left;
	swap(num[pivotIdx], num[right]);//place the pivot to most-rigth
	pivotVal = num[right];

	int minIdx=left-1;
	for(int currIdx=left; currIdx<right; currIdx++){
		if(num[currIdx] < num[right]){
			swap(num[currIdx], num[minIdx+1]);
			minIdx++;
		}
	}

	swap(num[right], num[minIdx+1]);
	return minIdx + 1;
}

int kthMinElem(unsigned int *num,int len,int k){
	int val = 0, left = 0, right = len - 1;
	while(left <= right){
		int pos = partition(num,left,right,val);

		int rank = pos - left + 1;
		if(rank == k){
			return val;
		}else if(rank > k){
			right = pos - 1;
		}else{
			left = pos + 1;
			k -= rank;
		}
	}
	return -1;
}

int main(){
	freopen("info","r",stdin);
	int len,k;
	cin>>len>>k;

	if(k <= 0 || k > len)
		cout<<-1<<endl;
	else{
		unsigned int * num = new unsigned int[len+1];

		srand(time(NULL));

		for(int i=0;i<len;i++){
			cin>>num[i];
		}

		printf("%d\n",kthMinElem(num,len,k));
	}
}

