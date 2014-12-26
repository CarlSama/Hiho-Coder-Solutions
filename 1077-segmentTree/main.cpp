#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;

struct SegTNode{
	int weight;
	int lInterval,rInterval;
	struct SegTNode *left,*right;
	SegTNode(int w, int lIt,int rIt,SegTNode *l,SegTNode *r):weight(w),lInterval(lIt),rInterval(rIt),left(l),right(r){}
};

/*
 * i means the start position 
 * left and right means the interval of vector
 */
SegTNode *build(int left,int right,int *weight){
	if(right <  left)
		return 0;
	if(right == left){
		SegTNode *root = new SegTNode(weight[left],left,left,0,0);
		return root;
	}

	SegTNode *root = new SegTNode(0,left,right,0,0);
	int mid = (right+left)>>1;
	root->left = build(left,mid,weight);
	root->right = build(mid+1,right,weight);
	root->weight = min(root->left->weight, root->right->weight); 
	return root;
}

int query(int left ,int right, SegTNode *root){
	if(NULL==root)
		return 0;

	if(root->lInterval==left && root->rInterval==right)
		return root->weight;

	if(right <= root->left->rInterval){
		return query(left,right,root->left);
	}else if(left >= root->right->lInterval){
		return query(left,right,root->right);
	}else{
		return min(query(left,root->left->rInterval,root->left),query(root->right->lInterval,right,root->right));
	}
}


void modify(int idx, int weight, SegTNode *root){
	if(NULL==root)
		return;

	if(root->lInterval==idx && root->rInterval==idx){
		root->weight = weight;
		return;
	}

	if(idx <= root->left->rInterval){
		modify(idx, weight,root->left);
	}else {
		modify(idx,weight,root->right);
	}

	root->weight = min(root->left->weight,root->right->weight); 
}

int main(){
	freopen("info","r",stdin);
	int n, times, i=1;
	cin>>n;
	if(n < 1)
		return 1;

	int* weight = new int[n+1];
	while(i <= n){
		cin>>weight[i];//The interval starts at 1
		i++;
	}

	SegTNode *root = build(1,n,weight);

	cin>>times;
	while(times--){
		int type;
		cin>>type;
		if(type==0){
			int left,right;
			cin>>left>>right;
			cout<<query(left,right,root)<<endl;
		}else{//type == 1
			int idx,newWeight;
			cin>>idx>>newWeight;
			modify(idx,newWeight,root);
		}
	}
	return 0;
}
