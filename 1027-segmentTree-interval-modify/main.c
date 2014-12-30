#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int lazy,sum;
	int lInterval,rInterval;
	struct Node *left,*right;
}SegTNode;

int min(int l, int r){
	return l<r?l:r;
}

SegTNode *build(int left,int right,int *weight){
	if(right < left)
		return 0;
	if(left == right){
		SegTNode *root = (SegTNode *)malloc(sizeof(SegTNode));
		root->lazy = -1;
		root->sum = weight[left];
		root->lInterval = root->rInterval = left;
		root->left = root->right = 0;
		return root;
	}

	SegTNode *root = (SegTNode *)malloc(sizeof(SegTNode));
	root->left = build(left,(right+left)>>1,weight);
	root->right = build(((right+left)>>1)+1,right,weight);
	root->lInterval = left;
	root->rInterval = right;
	root->lazy = -1;
	root->sum = root->left->sum + root->right->sum;
	return root;
}

void modify(int left,int right,int w, SegTNode *root){
	if(root->lInterval==left && root->rInterval==right){
		root->lazy = w;
		root->sum = w * (right-left+1);
		return ;
	}

	if(root->lazy != -1){//the modification made before still haunt.Just push down to its children.
		root->left->lazy = root->right->lazy = root->lazy;
		root->left->sum	 = root->lazy * (root->left->rInterval - root->left->lInterval + 1);
		root->right->sum = root->lazy * (root->right->rInterval - root->right->lInterval + 1);
		root->lazy = -1;
	}

	if(right <= root->left->rInterval){
		modify(left,right,w,root->left);
	}else if(left >= root->right->lInterval){
		modify(left,right,w,root->right);
	}else{
		modify(left,root->left->rInterval,w,root->left);
		modify(root->right->lInterval,right,w,root->right);
	}
	root->sum = root->left->sum + root->right->sum;
}


int query(int left,int right,SegTNode *root){
	if(root->lInterval==left && root->rInterval==right){
		return root->sum;
	}

	if(root->lazy != -1){
		root->left->lazy = root->right->lazy = root->lazy;
		root->left->sum  = root->lazy * (root->left->rInterval - root->left->lInterval + 1);
		root->right->sum = root->lazy * (root->right->rInterval - root->right->lInterval + 1);
		root->lazy = -1;
	}

	if(right <= root->left->rInterval){
		return query(left,right,root->left);
	}else if(left >= root->right->lInterval){
		return query(left,right,root->right);
	}else{
		return query(left,root->left->rInterval,root->left) + query(root->right->lInterval,right,root->right);
	}
}

int main(){
	freopen("info","r",stdin);
	int n,times,i=1,left,right,w;
	scanf("%d",&n);
	int *weight = (int *)malloc((n+1) * sizeof(int));
	while(i <= n){
		scanf("%d",&weight[i]);
		i++;
	}
	
	SegTNode *root = build(1,n,weight);
	scanf("%d",&times);
	while(times--){
		scanf("%d",&i);
		if(i==0){
			scanf("%d %d",&left,&right);
			printf("%d\n",query(left,right,root));
		}else{
			scanf("%d %d %d",&left,&right,&w);
			modify(left,right,w,root);
		}
	}

	return 0;
}
