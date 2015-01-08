#include<cstdio>
#include<iostream>
#include<map>
#include<vector>
#include<list>
#include<queue>

using namespace std;

/*
 * The prim's time complexity is O(n*n), regardless edge num.
 * So it suits the dense graph.
 *
 * The Kruskal's time complexity is O(eloge), suits better for the sparse graph.
 */

struct Path{
	int start;
	int end;
	int cost;
	Path(int s,int e,int c):start(s),end(e),cost(c){}
};
struct Cmp {
	bool operator() (Path *a, Path *b) {
		return (a->cost > b->cost);		
	}
};

int find_represent(vector<int> &link,int pos){
	if(pos == link[pos]){
		return pos;
	}else{
		link[pos] = find_represent(link,link[pos]);
		return link[pos];
	}
}

int GeneKruskal(priority_queue<Path *, vector<Path *>, Cmp> &pqueue, vector<int> &link){
	int cost = 0;
		
	int i=0;
	while(!pqueue.empty()){
		Path * leastPath = pqueue.top();
		pqueue.pop();

		int l = find_represent(link, leastPath->start);
		int r = find_represent(link, leastPath->end);
		if(l != r){
			cost += leastPath->cost;
			link[l] = r;
		}
	}	

	return cost;
}

void init(int &cityNum, int &roadNum, priority_queue<Path *, vector<Path *>, Cmp> &pqueue, vector<int> &link){
	int start,end,cost;
	for(int i=0;i<=roadNum;i++){
		cin>>start>>end>>cost;
		pqueue.push(new Path(start,end,cost));
	}

	for(int i=0;i<=cityNum;i++)
		link[i] = i;
}

int main(){
#ifdef DEBUG
	freopen("info","r",stdin);
#endif
	int cityNum, roadNum;
	cin>>cityNum>>roadNum; //First time, I put this in init(), which leads to link was initialized with wrong parameter.

	priority_queue<Path *, vector<Path *>, Cmp> pqueue;
	vector<int> link(cityNum+1);
	init(cityNum, roadNum, pqueue, link);

	printf("%d\n",GeneKruskal(pqueue, link));

	return 0;
}
