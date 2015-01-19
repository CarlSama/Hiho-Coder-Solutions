#include<iostream>
#include<algorithm>
#include<cstdio>
#include<climits>

using namespace std;

class Floyd{
	private:
		int matrix[101][101];
		int vertex;
	public:
		Floyd(int v);
		virtual ~Floyd();

		void build(int from, int to, int weight);
		void findAns();
};

Floyd::Floyd(int v){
	vertex = v;
	for(int i = 1;i<=vertex;i++){
		for(int j = 1;j<=vertex;j++){
			matrix[i][j] = INT_MAX;
		}
		matrix[i][i] = 0;
	}
}

Floyd::~Floyd(){
}

void Floyd::build(int from, int to, int weight){
	if(matrix[from][to] > weight){
		matrix[from][to] = weight;
		matrix[to][from] = weight;
	}
}

void Floyd::findAns(){
	for(int k=1;k<=vertex;k++){
		for(int i=1;i<=vertex;i++){
			for(int j=1;j<=vertex;j++){
				if(i!=j && j!=k && matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX){
					matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
				}
			}
		}
	}

	for(int i=1;i<=vertex;i++){
		for(int j=1;j<=vertex;j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}

int main(){
	freopen("info","r",stdin);
	int n,m;
	cin>>n>>m;

	Floyd fd(n);
	int from,to,weight;
	while(m--){
		cin>>from>>to>>weight;
		fd.build(from, to, weight);
	}

	fd.findAns();

	return 0;
}

