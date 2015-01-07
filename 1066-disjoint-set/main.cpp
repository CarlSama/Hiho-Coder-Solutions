#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
using namespace std;

int geneSet(map<string,int> &nameToIdx, vector<int> &link, const string name, int &idx){
	map<string,int>::iterator iter = nameToIdx.find(name);
	if(iter == nameToIdx.end()){
		nameToIdx.insert(pair<string,int>(name,++idx));
		link.push_back(idx);
		return idx;
	}else{
		return iter->second;
	}
}

int find_reprsent(vector<int> &link, int pos){
	if(pos == link[pos]){
		return pos;
	}else{
		link[pos] = find_reprsent(link, link[pos]);
		return link[pos];
	}
}

int querySet(map<string,int> &nameToIdx, vector<int> &link, const string name){
	map<string,int>::iterator iter = nameToIdx.find(name);
	if(iter == nameToIdx.end()){
		return -1;
	}else{
		return find_reprsent(link,iter->second);
	}
}

int main(){
#ifdef DEBUG
	freopen("info","r",stdin);
#endif
	int n;
	cin>>n;

	int op,idx = -1, fIdx, sIdx,fRep,sRep;
	string fname,sname;
	map<string,int> nameToIdx;
	vector<int> link;
	while(n--){
		cin>>op>>fname>>sname;
		switch(op){
			case 0:{
				fIdx = geneSet(nameToIdx,link,fname,idx);
				sIdx = geneSet(nameToIdx,link,sname,idx);
				fRep = find_reprsent(link,fIdx);
				sRep = find_reprsent(link,sIdx);
				if(fRep != sRep)
					link[fRep] = sRep;
				break;
			}
			case 1:{
				int fSet = querySet(nameToIdx,link,fname);
				int sSet = querySet(nameToIdx,link,sname);
				if(fSet!=-1 && sSet!=-1 && fSet==sSet)
					printf("yes\n");
				else
					printf("no\n");
				break;
			}
			default:
				break;
		}
	}

	return 0;
}

