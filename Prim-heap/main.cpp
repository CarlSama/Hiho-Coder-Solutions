#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>

using namespace std;

struct Elem{
	int to,weight;
	Elem *next;
	Elem(int t,int w,Elem *n):to(t),weight(w),next(n){}
};

struct Head{
	Elem *next;
	Head():next(0){}
};

Head *AdjList[100001];
int visited[100001];

void init(const int vertex){
	for(int i=0;i<=vertex;i++){
		AdjList[i] = new Head();
	}
	for(int i=0;i<=vertex;i++){
		visited[i] = false;
	}
}

void build(int from,int to,int weight){
	AdjList[from]->next = new Elem(to,weight,AdjList[from]->next);		
	AdjList[to]->next = new Elem(from,weight,AdjList[to]->next);
}

bool cmp(Elem *fir, Elem *sec){
	return fir->weight > sec->weight;
}

void findAns(const int vertex){
	//We build a heap first
	vector<Elem *> adjEdges;
	Elem *next = AdjList[1]->next;
	while(next){
		adjEdges.push_back(next);
		next = next->next;
	}

	make_heap(adjEdges.begin(),adjEdges.end(),cmp);

	visited[1] = true;

	int res = 0;
	int currEdge = 1;
	while(currEdge !=  vertex){
		Elem *minEdge = adjEdges.front();
		pop_heap(adjEdges.begin(),adjEdges.end(),cmp);
		adjEdges.pop_back();
		
		if(!visited[minEdge->to]){
			currEdge++;
			res += minEdge->weight;

			next = AdjList[minEdge->to]->next;
			while(next){
				if(!visited[next->to]){
					adjEdges.push_back(next);
					push_heap(adjEdges.begin(),adjEdges.end(),cmp);
				}
				next = next->next;
			}

			visited[minEdge->to] = true;
		}
	}

	printf("%d\n",res);
}

int main(){
	freopen("info","r",stdin);
	int n,m;
	cin>>n>>m;
	
	init(n);
	int from,to,weight;
	while(m--){
		cin>>from>>to>>weight;
		build(from,to,weight);
	}

	findAns(n);

	return 0;
}



