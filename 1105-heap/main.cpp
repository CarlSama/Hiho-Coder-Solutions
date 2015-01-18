#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

class MaxHeap{
	private:
		vector<int> heap;//We store weight from heap[1]
		int tail, curr, n;
	public:
		MaxHeap(int n);
		virtual ~MaxHeap();

		void insert(int weight);
		void eatMaxWeight();
		void swap(int fir, int sec);
};

MaxHeap::MaxHeap(int n){
	tail = 0;
	heap.reserve(n);
	heap.push_back(0);
}

MaxHeap::~MaxHeap(){
}

void MaxHeap::swap(int fir, int sec){
	int tmp = heap[fir];
	heap[fir] = heap[sec];
	heap[sec] = tmp;
}

void MaxHeap::insert(int weight){
	heap.push_back(weight);
	curr = ++tail;
	while((curr>>1) > 0){
		if(heap[curr] > heap[curr>>1]){
			swap(curr, curr>>1);
		}else{
			break;
		}
		curr = curr>>1;
	}
}

void MaxHeap::eatMaxWeight(){
	printf("%d\n",heap[1]);

	swap(1, tail);
	tail--;
	heap.pop_back();

	curr = 1;
	int largestIdx;
	while(curr <= tail){
		largestIdx = curr;
		if((curr<<1) <= tail && heap[curr] < heap[curr<<1]){
			largestIdx = curr<<1;
		}
		if((curr<<1)+1 <= tail && heap[largestIdx] < heap[(curr<<1)+1]){
			largestIdx = (curr<<1)+1;
		}

		if(largestIdx != curr){
			swap(largestIdx, curr);
			curr = largestIdx;
		}else{
			break;
		}
	}
}

int main(){
	freopen("info","r",stdin);
	int n;
	cin>>n;
	MaxHeap heap(n);

	while(n--){
		char type;
		cin>>type;
		if(type == 'A'){
			int weight;
			cin>>weight;
			heap.insert(weight);
		}else{
			heap.eatMaxWeight();
		}
	}

	return 0;
}
