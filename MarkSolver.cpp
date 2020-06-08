#ifndef WUMPUSMARKSOLVER
#define WUMPUSMARKSOLVER
#include <iostream>
#include <vector>
#include <string>
#include "node.cpp"

using namespace std;
typedef vector< vector<Node> > game;
bool testing=false;
/*  checkgold will check if the game is end or not.
	@param gamestate  It is the game board of the current state
	@param mapsize  It is n for an n*n board, we assume that all the boards are in shape of n*n.
	@return the function returns true if the board is solved;  false if it is not sovled.
*/
bool checkgold(game gamestate, int mapsize){
	for(int i=0;i<mapsize;i++){
		for(int j =0;j<mapsize;j++){
			if (gamestate[i][j].visited==false&&gamestate[i][j].is_gold()==true) return false;
		}
	}
	return true;
}

/* 	countposwnum counts the number of possible spots of wumpus that the robot think it can be.
	@param gamestate  It is the game board of the current state
	@param mapsize  It is n for an n*n board, we assume that all the boards are in shape of n*n.
	@return the the number of possible spots of wumpus that the robot think it can be.
*/
int countposwnum(game gamestate, int mapsize){
	int count=0;
	for(int i=0;i<mapsize;i++){
		for(int j =0;j<mapsize;j++){
			if (gamestate[i][j].nw==false) count++;
		}
	}
	return count;
}
/* 	expandbyrule will put all the nodes that can be visited into visited nodes by the rule of the marking algorithm.
	@param gamestate  It is the game board of the current state
	@param mapsize  It is n for an n*n board, we assume that all the boards are in shape of n*n.
	@return the gameboard after the expanding.
*/
game expandbyrule(game gamestate, int mapsize){
	bool expanding=true;
	
	while(expanding){
		expanding=false;
		for(int i=0;i<mapsize;i++){
			for(int j =0;j<mapsize;j++){
				if(gamestate[i][j].visited==false&&gamestate[i][j].nw==true&&gamestate[i][j].np==true){
					gamestate[i][j].visited=true;
					expanding=true;
					if (gamestate[i][j].is_breeze() && gamestate[i][j].is_stench()){
						for(int x=0;x<mapsize;x++){
							for(int y =0;y<mapsize;y++){
								if(!((x==i+1&&y==j)||(x==i-1&&y==j)||(x==i&&y==j+1)||(x==i&&y==j-1)) ) {
									gamestate[x][y].nw=true;
								}
							}
						}
						
					}				
	
					else if(gamestate[i][j].is_stench()){
						for(int x=0;x<mapsize;x++){
							for(int y =0;y<mapsize;y++){
								if(!((x==i+1&&y==j)||(x==i-1&&y==j)||(x==i&&y==j+1)||(x==i&&y==j-1)) ) {
									gamestate[x][y].nw=true;
								}
							}
						}
						if(i+1<mapsize) gamestate[i+1][j].np=true;
						if(j+1<mapsize) gamestate[i][j+1].np=true;
						if(i-1>=0) gamestate[i-1][j].np=true;
						if(j-1>=0) gamestate[i][j-1].np=true;
					}
	
					else if(gamestate[i][j].is_breeze()){
						if(i+1<mapsize) gamestate[i+1][j].nw=true;
						if(j+1<mapsize) gamestate[i][j+1].nw=true;
						if(i-1>=0) gamestate[i-1][j].nw=true;
						if(j-1>=0) gamestate[i][j-1].nw=true;
						
					}
					else{
						if(i+1<mapsize) gamestate[i+1][j].np=true;
						if(j+1<mapsize) gamestate[i][j+1].np=true;
						if(i-1>=0) gamestate[i-1][j].np=true;
						if(j-1>=0) gamestate[i][j-1].np=true;
						if(i+1<mapsize) gamestate[i+1][j].nw=true;
						if(j+1<mapsize) gamestate[i][j+1].nw=true;
						if(i-1>=0) gamestate[i-1][j].nw=true;
						if(j-1>=0) gamestate[i][j-1].nw=true;
						
					}
				}
				if(testing){
					cout<<endl;
					for(int i=0;i<mapsize;i++){
					for(int j =0;j<mapsize;j++){
						if (gamestate[i][j].nw==false){
				
						cout<<0;
						}
						else cout<<1;
							}
					cout<<endl;
					}
				}
			}
		}
	}
	
	return gamestate;
}


/* The assembled main function which takes in a board and return true if the board is solvable, false otherwise.
	@param theboard  It is the game board the generator generated
	@param mapsize  It is n for an n*n board, we assume that all the boards are in shape of n*n.
	@return the function returns true if the board is solvable;  false if it cannot be sovled.
*/
bool marksolver( game theboard, int mapsize ){
	// initialize the game
	
	game gamestate( theboard);
	int i=0;
	int j=0;
	gamestate[i][j].visited=true;
	
	gamestate[i][j].nw=true;
	gamestate[i][j].np=true;
	
	if (gamestate[i][j].is_breeze() && gamestate[i][j].is_stench()){
		for(int x=0;x<mapsize;x++){
			for(int y =0;y<mapsize;y++){
				if(!((x==i+1&&y==j)||(x==i-1&&y==j)||(x==i&&y==j+1)||(x==i&&y==j-1)) ) {
					gamestate[x][y].nw=true;
				}
			}
		}
	}
	
	else if(gamestate[i][j].is_stench()){
		for(int x=0;x<mapsize;x++){
			for(int y =0;y<mapsize;y++){
				if(!((x==i+1&&y==j)||(x==i-1&&y==j)||(x==i&&y==j+1)||(x==i&&y==j-1)) ) {
					gamestate[x][y].nw=true;
				}
			}
		}
		if(i+1<mapsize) gamestate[i+1][j].np=true;
		if(j+1<mapsize) gamestate[i][j+1].np=true;
		if(i-1>=0) gamestate[i-1][j].np=true;
		if(j-1>=0) gamestate[i][j-1].np=true;
	}
	
	else if(gamestate[i][j].is_breeze()){
		if(i+1<mapsize) gamestate[i+1][j].nw=true;
		if(j+1<mapsize) gamestate[i][j+1].nw=true;
		if(i-1>=0) gamestate[i-1][j].nw=true;
		if(j-1>=0) gamestate[i][j-1].nw=true;
	}
	else{
		if(i+1<mapsize) gamestate[i+1][j].np=true;
		if(j+1<mapsize) gamestate[i][j+1].np=true;
		if(i-1>=0) gamestate[i-1][j].np=true;
		if(j-1>=0) gamestate[i][j-1].np=true;
		if(i+1<mapsize) gamestate[i+1][j].nw=true;
		if(j+1<mapsize) gamestate[i][j+1].nw=true;
		if(i-1>=0) gamestate[i-1][j].nw=true;
		if(j-1>=0) gamestate[i][j-1].nw=true;
	}
	
	// first round of expanding, before try to shoot the wumpus.
	game beforeshooting=expandbyrule(gamestate,mapsize);
	// if gold already reached, just return true
	if(checkgold(beforeshooting,mapsize)) return true;
	//shoot the wumpus down if it is possible
	int wnumber=countposwnum( beforeshooting, mapsize);
		//only one possible place for wumpus
	if(wnumber==1){
		
		int x=0;
		int y=0;
		
		for(int i=0;i<mapsize;i++){
			for(int j =0;j<mapsize;j++){
				if (beforeshooting[i][j].nw==false){
				x=i;
				y=j;
				
				}
				
			}
			
		}
		
		
		if(beforeshooting[x][y].is_wumpus()){
			beforeshooting[x][y].nw=true;
			beforeshooting[x][y].np=true;
			for(int a=0;a<mapsize;a++){
				for(int b=0;b<mapsize;b++){
					beforeshooting[a][b].stench=false;
				}
			}
		}
		else{
			beforeshooting[x][y].nw=true;
		}
		beforeshooting[x][y].killw();
		
		game aftershooting=expandbyrule(beforeshooting,mapsize);
		
		if(checkgold(aftershooting,mapsize)) return true;
	}
	
		//if there are two possible places for wumpus
	else if(wnumber==2){
		int x=0;
		int y=0;
		int c,d=0;
		for(int i=0;i<mapsize;i++){
			for(int j =0;j<mapsize;j++){
				if (beforeshooting[i][j].nw==false){
				x=i;
				y=j;
				goto here;
				}
			}
		}
		here:
		
		
		for(int i=0;i<mapsize;i++){
			for(int j =0;j<mapsize;j++){
				if (beforeshooting[i][j].nw==false){
				c=i;
				d=j;
				
				}
			}
		}
		game beforeshooting1(beforeshooting);
		if(beforeshooting1[x][y].is_wumpus()){
			beforeshooting1[x][y].nw=true;
			beforeshooting1[c][d].nw=true;
			beforeshooting1[x][y].np=true;
			for(int a=0;a<mapsize;a++){
				for(int b=0;b<mapsize;b++){
					beforeshooting1[a][b].stench=false;
				}
			}
		}
		else{
			beforeshooting1[x][y].nw=true;
		}
		beforeshooting1[x][y].killw();
		game aftershooting1=expandbyrule(beforeshooting1,mapsize);
		game beforeshooting2(beforeshooting);
		if(beforeshooting2[c][d].is_wumpus()){
			beforeshooting2[x][y].nw=true;
			beforeshooting2[c][d].nw=true;
			beforeshooting2[c][d].np=true;
			for(int a=0;a<mapsize;a++){
				for(int b=0;b<mapsize;b++){
					beforeshooting2[a][b].stench=false;
				}
			}
		}
		else{
			beforeshooting2[c][d].nw=true;
		}
		beforeshooting2[c][d].killw();
		game aftershooting2=expandbyrule(beforeshooting2,mapsize);
		if(checkgold(aftershooting1,mapsize)&&checkgold(aftershooting2,mapsize)) return true;
	}
	
	return false;
}

#endif
