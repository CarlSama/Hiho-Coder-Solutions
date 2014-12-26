#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>

using namespace std;

struct SegTNode{
	int weight;
	int lInterval,rInterval;
};

/*
 * i means the start position 
 * left and right means the interval of vector
 */
void build(int i,int left,int right,vector<SegTNode> &segTree,vector<int> &weight){
	if(right <  left)
		return;
	if(right == left){
		segTree[i].weight = weight[left];
		segTree[i].lInterval = segTree[i].rInterval = left;
		return ;
	}

	int mid = (right+left)>>1;
	build(i<<1,left,mid,segTree,weight);
	build((i<<1)+1,mid+1,right,segTree,weight);
	
	segTree[i].weight = min(segTree[i<<1].weight, segTree[(i<<1)+1].weight); 
	segTree[i].lInterval = left;
	segTree[i].rInterval = right;
}
	
int query(int start, int left ,int right, vector<SegTNode> &segTree){
	if(segTree[start].lInterval==left && segTree[start].rInterval==right)
		return segTree[start].weight;

	int mid = (segTree[start].lInterval+segTree[start].rInterval)>>1;
	//We assume left and right must be in our segment.
	if(right <= mid){
		return query(start<<1,left,right,segTree);
	}else if(left > mid){
		return query((start<<1)+1,left,right,segTree);
	}else{
		int lMin = query(start<<1,left,mid,segTree);
		int rMin = query((start<<1)+1,mid+1,right,segTree);
		return lMin<rMin?lMin:rMin;
	}
}


void modify(int start, int idx, int weight, vector<SegTNode> &segTree){
	if(segTree[start].lInterval==idx && segTree[start].rInterval==idx){
		segTree[start].weight = weight;
		return ;
	}

	int mid = (segTree[start].lInterval+segTree[start].rInterval)>>1;
	if(idx <= mid){
		modify(start<<1, idx, weight,segTree);
	}else {
		modify((start<<1)+1,idx,weight,segTree);
	}

	segTree[start].weight = min(segTree[start<<1].weight,segTree[(start<<1)+1].weight); 
}

int main(){
	freopen("info","r",stdin);
	int n, times, i, sumLen;
	cin>>n;
	if(n < 1)
		return 1;

	sumLen = (n<<1)-1; 
	vector<int> weight(n+1);
	vector<SegTNode> segTree(sumLen+1);//We store the tree from [1] to [2*n+1]
		//The weight are stored to leaf, which range from n to 2n+1
	i = 1;
	while(i <= n){
		cin>>weight[i];//The interval starts at 1
		i++;
	}

	build(1,1,n,segTree,weight);

	cin>>times;
	while(times--){
		int type;
		cin>>type;
		if(type==0){
			int left,right;
			cin>>left>>right;
			if(left>=1 && right <=n)
				cout<<query(1,left,right,segTree)<<endl;
		}else{//type == 1
			int idx,newWeight;
			cin>>idx>>newWeight;
			if(idx>=1 && idx<=n)
				modify(1,idx,newWeight,segTree);
		}
	}
	return 0;
}
