#include<iostream>
#include<cstdio>
#include<vector>
#include<climits>

using namespace std;

class ShortestPath{
	public:
		//vector<vector<int> > AdjMatrix;
		int AdjMatrix[1001][1001];
		int link[1005];
		int vertex;
	public:
		ShortestPath(int vertex);
		virtual ~ShortestPath();

		void build(int from, int to, int weight);
		void findAns(int from, int to);
};

ShortestPath::ShortestPath(int v){
	for(int i=0;i<=v;i++){
		for(int j=0;j<=v;j++){
			AdjMatrix[i][j] = INT_MAX;
		}
	}

	vertex = v;
}

ShortestPath::~ShortestPath(){
}

void ShortestPath::build(int from, int to, int weight){
	if(AdjMatrix[from][to] > weight){ // Smart choice !~
		AdjMatrix[from][to] = weight;
		AdjMatrix[to][from] = weight;
	}
}

void ShortestPath::findAns(int from, int to){
	for(int i=0;i<=vertex;i++)
		link[i] = AdjMatrix[from][i];
	link[from] = 0;
	cout<<endl;
	for(int i=0;i<=vertex;i++)
		cout<<link[i]<<" ";
	cout<<endl;

	int res = 0;
	while(link[to]){
		int minIdx = 0;
		for(int i=1;i<=vertex;i++){
			if(link[i] && link[i] < link[minIdx])
				minIdx = i;
		}

		for(int i=1;i<=vertex;i++){
			if(link[i] && AdjMatrix[minIdx][i] != INT_MAX &&  link[i] > link[minIdx] + AdjMatrix[minIdx][i]){
				link[i] = link[minIdx] + AdjMatrix[minIdx][i];
			}
		}

		res = link[minIdx];
		link[minIdx] = 0;
	for(int i=0;i<=vertex;i++)
		cout<<link[i]<<" ";
	cout<<endl;
	}

	printf("%d\n",res);
	
}

int main(){
	freopen("info","r",stdin);
	int n,m,s,t;
	cin>>n>>m>>s>>t;

	ShortestPath sp(n);
	int from,to,weight;
	while(m--){
		cin>>from>>to>>weight;
		sp.build(from, to, weight);
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			cout<<sp.AdjMatrix[i][j]<<"  ";
		}
		cout<<endl;
	}

	sp.findAns(s, t);

	return 0;
}
