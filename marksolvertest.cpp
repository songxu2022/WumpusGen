#include <iostream>
#include <vector>
#include <string>
#include "node.cpp"
#include "MarkSolver.cpp"
using namespace std;
typedef vector< vector<Node> > game;
// 0==empty 1==pit 2==wumups 3==gold
game maptrans(vector<vector<int> > numap){
	game themap;
	int wallsize=numap.size();
	for(int i =0; i<wallsize;i++){
		vector<Node> line;
		for(int j=0;j<wallsize;j++){
			if(numap[i][j]==0) line.push_back(Node(i,j,"e",wallsize));
			else if(numap[i][j]==1) line.push_back(Node(i,j,"p",wallsize));
			else if(numap[i][j]==2) line.push_back(Node(i,j,"w",wallsize));
			else if(numap[i][j]==3) line.push_back(Node(i,j,"g",wallsize));
			else line.push_back(Node(i,j,"e",wallsize));
		}
		themap.push_back(line);
	}
	
	for(int i =0; i<wallsize;i++){		
		for(int j=0;j<wallsize;j++){
		
			if(numap[i][j]==1) {
				if(i+1<wallsize) themap[i+1][j].breeze=true;
				if(j+1<wallsize) themap[i][j+1].breeze=true;
				if(i-1>=0) themap[i-1][j].breeze=true;
				if(j-1>=0) themap[i][j-1].breeze=true;
			}
			if(numap[i][j]==2) {
				if(i+1<wallsize) themap[i+1][j].stench=true;
				if(j+1<wallsize) themap[i][j+1].stench=true;
				if(i-1>=0) themap[i-1][j].stench=true;
				if(j-1>=0) themap[i][j-1].stench=true;
			}
			if(numap[i][j]==3) {
				if(i+1<wallsize) themap[i+1][j].glitter=true;
				if(j+1<wallsize) themap[i][j+1].glitter=true;
				if(i-1>=0) themap[i-1][j].glitter=true;
				if(j-1>=0) themap[i][j-1].glitter=true;
			}

		}
		
	}
	
	return themap;
}
int main(){
	vector<vector<int> > map1 {{0,0,0,0},{0,0,0,0},{0,0,0,3},{0,0,0,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map1),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map2 {{0,1,0,0},{1,1,1,1},{0,0,0,3},{0,0,1,0}};
	cout<<"Should be false:";
	if(marksolver(maptrans(map2),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map3 {{0,0,2,0},{0,0,0,3},{1,0,0,0},{0,0,0,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map3),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map4 {{0,0,1,0},{0,0,0,3},{1,0,0,0},{0,0,0,0}};
	cout<<"Should be false:";
	if(marksolver(maptrans(map4),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map5 {{0,0,0,1},{0,0,2,3},{1,1,0,0},{0,0,0,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map5),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map6 {{0,0,0,0},{0,0,0,0},{1,1,0,1},{3,0,2,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map6),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map7 {{0,0,0,0},{0,0,0,2},{1,0,0,3},{0,0,0,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map7),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map8 {{0,0,2,3},{0,0,0,0},{0,0,0,1},{1,1,0,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map8),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map9 {{0,0,0,1},{0,0,1,0},{0,1,0,0},{3,0,2,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map9),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map10 {{0,0,1,0},{0,0,0,1},{2,0,3,0},{1,1,0,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map10),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map11 {{0,0,0,1},{0,0,1,0},{0,1,0,0},{2,0,3,0}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map11),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	vector<vector<int> > map12 {{0,0,1,0},{0,0,0,3},{0,2,0,0},{0,0,0,1}};
	cout<<"Should be true:";
	if(marksolver(maptrans(map12),4)) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	
	return 0;
}
