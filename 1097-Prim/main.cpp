#include<iostream>
#include<map>
#include<cstdio>
#include<vector>
#include<climits>
using namespace std;

inline int getMin(vector<int> &distance,int n){
	int minDis = n;
	for(int i=0;i<n;i++){
		if(distance[i] && distance[i]<distance[minDis])
			minDis = i;
	}
	return minDis;
}

void updateDis(vector<int> &distance, vector<vector<int> >&matrix, int n, int pos){
	distance[pos] = 0;
	for(int i=0;i<n;i++){
		if(distance[i] && matrix[i][pos] < distance[i])
			distance[i] = matrix[i][pos];
	}
}

int GenePrim(int n,vector<vector<int> > &matrix){
	int cost = 0,minDis,i;
	vector<int> distance(n+1,0);		
	distance[0] = 0;
	for(i=0;i<n;i++)
		distance[i] = matrix[0][i];
	
	distance[n] = INT_MAX;
	i=0;
	while((++i) < n){
		minDis = getMin(distance,n);
		cost += distance[minDis];
		updateDis(distance,matrix,n,minDis);
	}
	return cost;
}

int main(){
	freopen("info","r",stdin);
	int n;
	cin>>n;

	vector<vector<int> > matrix(n,vector<int>(n,0));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cin>>matrix[i][j];
	}

	printf("%d\n",GenePrim(n,matrix));
	return 0;
}
