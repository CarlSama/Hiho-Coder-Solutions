#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int weight;
	int lInterval,rInterval;
	struct Node *left,*right;
}SegTNode;

/*
 * i means the start position 
 * left and right means the interval of vector
 */
SegTNode *build(int left,int right,int *weight){
	if(right <  left)
		return 0;
	if(right == left){
		SegTNode *root = (SegTNode *)malloc(sizeof(SegTNode));
		root->weight = weight[left],
		root->lInterval = root->rInterval = left;
		root->left = root->right = 0;
		return root;
	}

	SegTNode *root = (SegTNode *)malloc(sizeof(SegTNode));
	root->lInterval = left;
	root->rInterval = right;
	int mid = (right+left)>>1;
	root->left = build(left,mid,weight);
	root->right = build(mid+1,right,weight);
	root->weight = min(root->left->weight, root->right->weight); 
	return root;
}

inline int min(int l,int r){
	return l<r?l:r;
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
	scanf("%d",&n);
	if(n < 1)
		return 1;

	int* weight = (int*)malloc((n+1)*sizeof(int));
	while(i <= n){
		scanf("%d",&weight[i]);//The interval starts at 1
		i++;
	}

	SegTNode *root = build(1,n,weight);

	scanf("%d",&times);
	while(times--){
		int type;
		scanf("%d",&type);
		if(type==0){
			int left,right;
			scanf("%d %d",&left,&right);
			printf("%d\n",query(left,right,root));
		}else{//type == 1
			int idx,newWeight;
			scanf("%d %d",&idx,&newWeight);
			modify(idx,newWeight,root);
		}
	}
	free(weight);
	return 0;
}
