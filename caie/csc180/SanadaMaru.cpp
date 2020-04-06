#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <string.h>

#define RESET           0
#define BRIGHT          1
#define DIM             2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8
#define BLACK           0
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define WHITE           7
using namespace std;

void setup();
void printboard();
int tempboard[8][7];
string input;

stringstream ss;
string str;

//Extra pieces are made if [7][6]. I do not know why this works
int board[8][7]; 
int maxdepth = 10;
vector <string> validmoves; 
vector <string> vector2;
vector <string> vector3;
vector <string> vector4;

int max(int depth, string input, int side);
int min(int depth, string input, int side);


void textcolor(int attr, int fg, int bg) { 
	char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}
	
void printboard() {
	cout << "\n  ---------------------   Sanada Maru\n" ;
	for (int sizeRow = 7; sizeRow >= 0; sizeRow--) {
		cout << sizeRow + 1 << " ";
		for (int sizeCol = 0; sizeCol <= 6; sizeCol++) {
			if (board[sizeRow][sizeCol] == -1) {
				textcolor(BRIGHT,YELLOW,BLACK);
				cout << " J ";
				textcolor(RESET,WHITE,BLACK);
			}
			else if (board[sizeRow][sizeCol] == -2) {
				textcolor(BRIGHT,YELLOW,BLACK);
				cout << " j ";
				textcolor(RESET,WHITE,BLACK);
			}
			
			else if (board[sizeRow][sizeCol] == -3) {
				textcolor(BRIGHT,YELLOW,BLACK);
				cout << " S ";
				textcolor(RESET,WHITE,BLACK); 
			}
			
			else if (board[sizeRow][sizeCol] == -4) {
				textcolor(BRIGHT,YELLOW,BLACK);
				cout << " s ";
				textcolor(RESET,WHITE,BLACK); 
			}	
			
			else if (board[sizeRow][sizeCol] == -10) {
				textcolor(BRIGHT,YELLOW,BLACK);
				cout << " K ";
				textcolor(RESET,WHITE,BLACK); 
			}
			
			else if (board[sizeRow][sizeCol] == 10) {
				cout << " K ";
			}
			
			else if (board[sizeRow][sizeCol] == 1) {
				cout << " J ";
			}
			
			else if (board[sizeRow][sizeCol] == 2) {
				cout << " j ";
			}
			
			else if (board[sizeRow][sizeCol] == 3) {
				cout << " S ";
			}
			
			else if (board[sizeRow][sizeCol] == 4) {
				cout << " s ";
			}
			
			else {
				cout << "   ";
			}
		}
		cout <<"\n";	
	}
    cout << " ---------------------   Human\n";
    cout << "   A  B  C  D  E  F  G \n" ;
	cout << "   0  1  2  3  4  5  6 \n" ;	
}
//Negative numbers are opponent. Positive are players.
//10 = King 
//1 =  Ninja
//2 = Mini Ninja
//3 = Samurai
//4 = Mini Samurai

void setup() {    
    board[7][3] = -10;
    board[6][0] = -1;
    board[6][1] = -1;
    board[6][2] = -1;
    board[5][0] = -4;
    board[5][1] = -4;
    board[5][2] = -4;
    board[6][4] = -3;
    board[6][5] = -3;
    board[6][6] = -3;
    board[5][4] = -2;
    board[5][5] = -2;
    board[5][6] = -2;
    // Board State for Opponent
	board[0][3] = 10;
	board[1][0] = 3;
	board[1][1] = 3;
	board[1][2] = 3;
	board[1][4] = 1;
	board[1][5] = 1;
	board[1][6] = 1;
	board[2][0] = 2;
	board[2][1] = 2;
	board[2][2] = 2;
	board[2][4] = 4;
	board[2][5] = 4;
	board[2][6] = 4;
	// Board State for Player
}
	
void getmove(int side) {
	int collisionl = 0;
    int collisionr = 0;
	int secondcount = 1;
	int kingHit = 0;
	if (side == 1) {
		for(int i = 0; i <= 7; i++) {
			for(int j = 0; j <= 6; j++) {
				switch(board[i][j]) {
					//Cases for player pieces
					case 1 : 
						// Left movement Ninja	
						for (int nL = 0; nL <= j; nL++) {
							if (j - secondcount < 0) break;
							if (board[i + secondcount][j - secondcount] != 0) {
								collisionl = 1;
							} 
							if (board[i + secondcount][j - secondcount] == 0 && collisionl == 0) {
								ss << j << i << j - secondcount << i + secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
							//	cout << j << i << j - secondcount << i + secondcount << " ";
							}
							secondcount++;
						}
						secondcount = 1;
						for (int bL = 0; bL < i; bL++) {
							// Checking backwards movement left
							if (board[i - secondcount][j - secondcount] == -1 || board[i - secondcount][j - secondcount] == -2 || board[i - secondcount][j - secondcount] == -3 || board[i - secondcount][j - secondcount] == -4 || board[i - secondcount][j - secondcount] == -10 ) {
								ss << j << i << j - secondcount << i - secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
							//	cout << j << i << j - secondcount << i - secondcount << " ";
							}
							
							secondcount++;
						}
						secondcount = 1;
						// Right movement
						for (int nR = j; nR <= 6; nR++) {
							// Checking forwards movement right
							if (j + secondcount > 6) break;
							if (board[i + secondcount][j + secondcount] != 0) {
								collisionr = 1;
							}
							if (board[i + secondcount][j + secondcount] == 0 && collisionr == 0) {
								ss << j << i << j + secondcount << i + secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
							//	cout << j << i << j + secondcount << i + secondcount << " ";
							}
							secondcount++;
						}
						secondcount = 1;
						for (int bR = 0; bR < i; bR++) { 
							//Checking backwards movement right
							if (board[i - secondcount][bR + 1] == -1 || board[i - secondcount][bR + 1] == -2 || board[i - secondcount][bR + 1] == -3 ||board[i - secondcount][bR + 1] == -4) {
								ss << j << i << bR + 1 << i - secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
							//	cout << j << i << nR + 1 << i - secondcount << " ";
							}
							secondcount++;
						}
						secondcount = 1;
						collisionl = 0;
						collisionr = 0;
						break;	
				
					case 2 :
						//Forward movement left and right Mini Ninja
						if (board[i+1][j-1] == 0 && ((j - 1) >= 0)) {
							ss << j << i << j - 1 << i + 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j - 1 << i + 1 << " ";
						}
				
						if (board[i+1][j+1] == 0 && ((j + 1) < 7)) {
							ss << j << i << j + 1 << i + 1;
							validmoves.push_back(ss.str());
							ss.str("");
						//	cout << j << i << j + 1 << i + 1 << " ";

						}
				
						//Backward movement left and right
						if (board[i - 1][j - 1] == -10 || board[i - 1][j - 1] == -1 || board[i - 1][j - 1] == -2 || board[i - 1][j - 1]  == -3 || board[i - 1][j - 1]  == -4) {
							ss << j << i << j - 1 << i - 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j - 1 << i - 1 << " ";
						}
				
						if (board[i - 1][j + 1] == -10 || board[i - 1][j + 1] == -1 || board[i - 1][j + 1] == -2 || board[i - 1][j + 1] == -3 || board[i - 1][j + 1] == -4) {
							ss << j << i << j + 1 << i - 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j + 1 << i - 1 << " ";
						}
						break;
				
					case 3:
						//Forward movement Samurai
						for (int sU = i; sU <= 7; sU++) {
							if (board[sU + 1][j] == -1 || board[sU + 1][j] == -2 || board[sU + 1][j] == -3 || board[sU + 1][j] == -4 || board[sU + 1][j] == 1 || board[sU + 1][j] == 2 ||board[sU + 1][j] == 3 || board[sU + 1][j] == 4 || board[sU + 1][j] == 10 || board[sU + 1][j] == -10) {
								break;
							}
						
							else if (board[sU + 1][j] == 0) {
								ss << j << i << j << sU + 1;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << j << nU + 1 << " ";
							}	
						}
				
						//Sideway movement Left
						for (int iL = j; iL <= 0; iL--) {
							if (board[i + 1][iL - 1] == 0) {
								break;
							}
							if (board[i + 1][iL - 1] == -1 || board[i + 1][iL - 1] == -2 || board[i + 1][iL - 1] == -3 || board[i + 1][iL - 1] == -4) {
								ss << j << i << iL - 1 << i ;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << iL - 1  << i << " ";
							}
						}
						
						//Sideway movement Right
						for(int iR = j; iR <= 6; iR++) {
							if (board[i + 1][iR + 1] == 0) {
								break;
							}
							if (board[i + 1][iR + 1] == -1 || board[i + 1][iR + 1] == -2 || board[i + 1][iR + 1] == -3 || board[i + 1][iR + 1] == -4) {
								ss << j << i << iR + 1 << i ;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << iR + 1 << i << " ";
							}
						}
						break;
					case 4:
						//Forward movement Mini Samurai
						if (board[i + 1][j] == 0) {
							ss << j << i << j << i + 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j << i + 1 << " ";
						}
				
						//Sideway movement
				
						if ((board[i + 1][j + 1] == -1 || board[i + 1][j + 1] == -2 || board[i + 1][j + 1] == -3 || board[i + 1][j + 1] == -4 || board[i + 1][j + 1] == -10) && (j + 1) < 7) {
							ss << j << i << j + 1 << i + 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << i << j + 1 << " ";
						}	
				
						if ((board[i + 1][j - 1] == -1 || board[i + 1][j - 1] == -2 || board[i + 1][j - 1] == -3 || board[i + 1][j - 1] == -4 || board[i + 1][j - 1]== -10) && (j - 1) >= 0) {
							ss << j << i << j - 1 << i;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j - 1 << i << " ";
						}
						break;
				}
			}
		}
	}
	else {
		for(int i = 0; i <= 7; i++) {
			for(int j = 0; j <= 6; j++) {
				switch(board[i][j]) {
					//Cases for AI pieces
					case -1:
						// Left movement Ninja	
						for (int nL = 0; nL < j; nL++) {
							if (j - secondcount < 0) break;
							if (board[i - secondcount][j - secondcount] != 0) {
								collisionl = 1;
							} 
							
							if (board[i - secondcount][j - secondcount] == 0 && collisionl == 0) {
								ss << j << i << j - secondcount << i - secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << j - secondcount << i - secondcount << " ";
							}
							secondcount++;

						}
						secondcount = 1;	
						for (int bN = 0; bN < j; bN++) {
							// Checking backwards movement left
							if (board[i + secondcount][j - secondcount] == 1 || board[i + secondcount][j - secondcount] == 2 || board[i + secondcount][j - secondcount] == 3 || board[i + secondcount][j - secondcount] == 4 || board[i + secondcount][j - secondcount] == 10) {
								ss << j << i << j - secondcount << i + secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << j - secondcount << i + secondcount << " ";
								secondcount++;
							}
						}
						secondcount = 1;	
						// Right movement
						for (int nR = j; nR <= 6; nR++) {
							// Checking forwards movement right
							if (j + secondcount > 6) break;
							if (board[i - secondcount][j + secondcount] != 0) {
								collisionr = 1;
							}
							if (board[i - secondcount][j + secondcount] == 0 && collisionr == 0) {
								ss << j << i << j + secondcount << i - secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << j + secondcount << i - secondcount << " ";
							}
						}
						for (int bR = 0; bR <= j; bR++) {
							//Checking backwards movement right
							if (board[i + secondcount][j + secondcount] == 1 || board[i + secondcount][j + secondcount] == 2 || board[i + secondcount][j + secondcount] == 3 || board[i + secondcount][j + secondcount] == 4 || board[i + secondcount][j + secondcount] == 10) {
								ss << j << i << j + secondcount << i + secondcount;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << j + secondcount << i + secondcount << " ";
							}
							secondcount++; 
						}
						secondcount = 1;
						collisionl = 0;
						collisionr = 0;
						break;	
				
					case -2 :
						//Forward movement left and right Mini Ninja
						if (board[i - 1][j - 1] == 0 && ((j - 1) >= 0)) {
							ss << j << i << j - 1 << i - 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j - 1 << i - 1 << " ";
						}
				
						if (board[i - 1][j + 1] == 0 && ((j + 1) < 7)) {
							ss << j << i << j + 1 << i - 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j + 1 << i - 1 << " ";

						}
				
						//Backward movement left and right
						if (board[i + 1][j - 1] == 10 || board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == 2 || board[i + 1][j - 1]  == 3 || board[i + 1][j - 1]  == 4) {
							ss << j << i << j - 1 << i + 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j - 1 << i + 1 << " ";
						}
				
						if (board[i + 1][j + 1] == 10 || board[i + 1][j + 1] == 1 || board[i + 1][j + 1] == 2 || board[i + 1][j + 1] == 3 || board[i + 1][j + 1] == 4) {
							ss << j << i << j + 1 << i + 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j + 1 << i + 1 << " ";
						}
						break;
				
					case -3:
						//Forward movement Samurai
						for (int nU = i; nU > 0; nU--) {
							if (board[nU - 1][j] == 1 || board[nU - 1][j] == 2 || board[nU - 1][j] == 3 || board[nU - 1][j] == 4 || board[nU - 1][j] == 10 || board[nU - 1][j] == -1 || board[nU - 1][j] == -2 || board[nU - 1][j] == -3 || board[nU - 1][j] == -4 || board[nU - 1][j] == -10) {
								break;
							}
						
							if (board[nU - 1][j] == 0) {
								ss << j << i << j << nU - 1;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << j << nU - 1 << " ";
							}	
						}
				
						//Sideway movement Left
						for (int nL = j; nL <= 0; nL--) {
							if (board[i - 1][nL - 1] == 0) {
								break;
							}
							if (board[i - 1][nL - 1] == 1 || board[i - 1][nL - 1] == 2 || board[i - 1][nL - 1] == 3 || board[i - 1][nL - 1] == 4 ||  board[i - 1][nL - 1] == 10) {
								ss << j << i << j << nL - 1;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << nL - 1  << i << " ";
							}
						}
						
						//Sideway movement Right
						for(int iR = j; iR <= 6; iR++) {
							if (board[i - 1][iR + 1] == 0) {
								break;
							}
							if (board[i - 1][iR + 1] == 1 || board[i - 1][iR + 1] == 2 || board[i - 1][iR + 1] == 3 || board[i - 1][iR + 1] == 4 && (iR + 1) < 7) {
								ss << j << i << iR + 1 << i;
								validmoves.push_back(ss.str());
								ss.str("");
								//cout << j << i << iR + 1 << i << " ";
							}
						}
						break;
					case -4:
						//Forward movement Mini Samurai
						if (board[i - 1][j] == 0) {
							ss << j << i << j << i - 1;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j << i + 1 << " ";
						}
				
						//Sideway movement
				
						if (board[i - 1][j + 1] == 1 || board[i - 1][j + 1] == 2 || board[i - 1][j + 1] == 3 || board[i - 1][j + 1] == 4 || board[i - 1][j + 1] == 10) {
							ss << j << i << j + 1 << i;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j + 1 << i << " ";
						}	
				
						if ((board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == 2 || board[i - 1][j - 1] == 3 || board[i - 1][j - 1] == 4 || board[i - 1][j - 1]== 10)) {
							ss << j << i << j - 1 << i;
							validmoves.push_back(ss.str());
							ss.str("");
							//cout << j << i << j - 1 << i << " ";
						}
						break;
				}
			}
		}			
	}

	for (int vi = 0; vi < validmoves.size(); vi++) {
			for (int index = 0; index < 4; index++) {
				if (validmoves.at(vi).at(index) == '0' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'A';
					//cout << "A";
				}
				else if (validmoves.at(vi).at(index) == '1' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'B';
					//cout << "B";
				}
				else if (validmoves.at(vi).at(index) == '2' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'C';
					//cout << "C";
				}
				else if (validmoves.at(vi).at(index) == '3' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'D';
					//cout << "D";
				}
				else if (validmoves.at(vi).at(index) == '4' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'E';
					//cout << "E";
				}
				else if (validmoves.at(vi).at(index) == '5' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'F';
					//cout << "F";
				}
				else if (validmoves.at(vi).at(index) == '6' && (index == 0 || index == 2)) {
					validmoves.at(vi).at(index) = 'G';
					//cout << "G";
				}	
				else {
					//cout << (validmoves.at(vi).at(index));
				}				
			}
			
				//cout << " ";
	}
}

void undoMove(int oboard[8][7]){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			board[i][j] = tempboard[i][j];
		}
	}
}

int checkEnd() {
	int movesleft = validmoves.size();
    if (board[0][3] == 0) return -5000;
	else if (board[7][3] == 0) return 5000;
	else return 0;
}

int checkValid(string input) {
	for (int vi = 0; vi < validmoves.size(); vi++) {
		if ((input.compare(validmoves[vi])) == 0) {
			return 1;
			break;
		}
	}
	return 0;
	
}

void makeMove(string input, int side) {
	if (side == 1) {
		cout << "You moved " << input.at(0) << input.at(1) << " to " << input.at(2) << input.at(3) << "\n";
		for (int index = 0; index < 4; index++) {
			if (input.at(index) == 'A' && (index == 0 || index == 2)) {
				input.at(index) = '0';
			}
			else if (input.at(index) == 'B' && (index == 0 || index == 2)) {
				input.at(index) = '1';
			}
			else if (input.at(index) == 'C' && (index == 0 || index == 2)) {
				input.at(index) = '2';
			}
			else if (input.at(index) == 'D' && (index == 0 || index == 2)) {
				input.at(index) = '3';
			}
			else if (input.at(index) == 'E' && (index == 0 || index == 2)) {
				input.at(index) = '4';
			}
			else if (input.at(index) == 'F' && (index == 0 || index == 2)) {
				input.at(index) = '5';
			}
			else if (input.at(index) == 'G' && (index == 0 || index == 2)) {
				input.at(index) = '6';
			}
		}
		int tempboard = board[input.at(1) - '0'][input.at(0) - '0'];
		board[input.at(3) - '0'][input.at(2) - '0'] = tempboard;
		board[input.at(1) - '0'][input.at(0) - '0'] = 0;
		tempboard = 0;
		if (board[(input.at(3) - '0' + 1)][input.at(2) - '0'] == -1 ) {
			board[(input.at(3) - '0' + 1)][input.at(2) - '0'] = -2;
			cout << "Hi-Ya!\n";
		}
		
		else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0'] == -2) {
			board[(input.at(3) - '0' + 1)][input.at(2) - '0'] = 0;
			cout << "Hi-Ya!\n";
		}
		
		else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0'] == -3) {
			board[(input.at(3) - '0' + 1)][input.at(2) - '0'] = -4;
			cout << "Hi-Ya!\n";
		}
		
		else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0'] == -4) {
			board[(input.at(3) - '0' + 1)][input.at(2) - '0'] = 0;
			cout << "Hi-Ya!\n";
		}
		
		else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0'] == -10) {
			board[(input.at(3) - '0' + 1)][input.at(2) - '0'] = 0;
			cout << "Hi-Ya!\n";
		}
	}
	else {
		string translate;
		if (input.at(0) == 'G') translate = translate + 'A';
		else if (input.at(0) == 'F') translate = translate + 'B';
		else if (input.at(0) == 'E') translate = translate + 'C';
		else if (input.at(0) == 'D') translate = translate + 'D';
		else if (input.at(0) == 'C') translate = translate + 'E';
		else if (input.at(0) == 'B') translate = translate + 'F';
		else if (input.at(0) == 'A') translate = translate + 'G';
		if (input.at(1) == '1') translate = translate + '8';
		else if (input.at(1) == '2') translate = translate + '7';
		else if (input.at(1) == '3') translate = translate + '6';
		else if (input.at(1) == '4') translate = translate + '5';
		else if (input.at(1) == '5') translate = translate + '4';
		else if (input.at(1) == '6') translate = translate + '3';
		else if (input.at(1) == '7') translate = translate + '2';
		else if (input.at(1) == '8') translate = translate + '1';
		if (input.at(2) == 'G') translate = translate + 'A';
		else if (input.at(2) == 'F') translate = translate + 'B';
		else if (input.at(2) == 'E') translate = translate + 'C';
		else if (input.at(2) == 'D') translate = translate + 'D';		
		else if (input.at(2) == 'C') translate = translate + 'E';
		else if (input.at(2) == 'B') translate = translate + 'F';
		else if (input.at(2) == 'A') translate = translate + 'G';
		if (input.at(3) == '1') translate = translate + '8';
		else if (input.at(3) == '2') translate = translate + '7';
		else if (input.at(3) == '3') translate = translate + '6';
		else if (input.at(3) == '4') translate = translate + '5';
		else if (input.at(3) == '5') translate = translate + '4';
		else if (input.at(3) == '6') translate = translate + '3';
		else if (input.at(3) == '7') translate = translate + '2';
		else if (input.at(3) == '8') translate = translate + '1';
		
		cout << "AI moved " << input.at(0) << input.at(1) << " to " << input.at(2) << input.at(3) << " (" << translate << ") \n";
		for (int index = 0; index < 4; index++) {
			if (input.at(index) == 'A' && (index == 0 || index == 2)) {
				input.at(index) = '0';
			}
			else if (input.at(index) == 'B' && (index == 0 || index == 2)) {
				input.at(index) = '1';
			}
			else if (input.at(index) == 'C' && (index == 0 || index == 2)) {
				input.at(index) = '2';
			}
			else if (input.at(index) == 'D' && (index == 0 || index == 2)) {
				input.at(index) = '3';
			}
			else if (input.at(index) == 'E' && (index == 0 || index == 2)) {
				input.at(index) = '4';
			}
			else if (input.at(index) == 'F' && (index == 0 || index == 2)) {
				input.at(index) = '5';
			}
			else if (input.at(index) == 'G' && (index == 0 || index == 2)) {
				input.at(index) = '6';
			}
		}
		int tempboard = board[input.at(1) - '0'][input.at(0) - '0'];
		board[input.at(3) - '0'][input.at(2) - '0'] = tempboard;
		board[input.at(1) - '0'][input.at(0) - '0'] = 0;
		tempboard = 0;
		if (board[(input.at(3) - '0' - 1)][input.at(2) - '0'] == 1 ) {
			board[(input.at(3) - '0' - 1)][input.at(2) - '0'] = 2;
			cout << "Hi-YA!\n";	
		}
		
		else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0'] == 2) {
			board[(input.at(3) - '0' - 1)][input.at(2) - '0'] = 0;
			cout << "Hi-YA!\n";
		}
		
		else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0'] == 3) {
			board[(input.at(3) - '0' - 1)][input.at(2) - '0'] = 4;
			cout << "Hi-YA!\n";
		}
		
		else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0'] == 4) {
			board[(input.at(3) - '0' - 1)][input.at(2) - '0'] = 0;
			cout << "Hi-YA!\n";
		}
		
		else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0'] == 10) {
			board[(input.at(3) - '0' - 1)][input.at(2) - '0'] = 0;
			cout << "Hi-YA!\n";
		}
	}
	validmoves.clear();
}

int evaluate(int score, string input, int depth) {
	if ((input.at(3) - '0') == 1 && (input.at(2) - '0') == 3) return 5000 - depth;
	else if ((input.at(3) - '0') == 6 && (input.at(2) - '0') == 3) return -5000 - depth;
	else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0' == 1]) return -100 - depth;
	else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0' == 2]) return -150 - depth;
	else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0' == 3]) return -100 - depth;
	else if (board[(input.at(3) - '0' - 1)][input.at(2) - '0' == 4]) return -150 - depth;
	else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0' == 1]) return 100 - depth;
	else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0' == 2]) return 150 - depth;
	else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0' == 3]) return 100 - depth;
	else if (board[(input.at(3) - '0' + 1)][input.at(2) - '0' == 4]) return 150 - depth;
	else if ((input.at(3) - '0' == 6) && input.at(2) - '0' == 3) return -50 - depth;
	else if ((input.at(3) - '0' == 3) && input.at(2) - '0' == 2) return -50 - depth;
	else if ((input.at(3) - '0' == 3) && input.at(2) - '0' == 4) return -50 - depth;
	else return 0 - depth;
}

int max(int depth, string input, int side) { 
	int best = -20000,score;
	if (checkEnd() != 0) return (checkEnd());
	if (depth == maxdepth) return (evaluate(score, input, depth));
	getmove(side);
	for (int v = 0; v < validmoves.size(); v++) {
		makeMove(validmoves[v], side);
		score = min(depth+1, input, side);
		if (score > best) {
			best=score;
			input = validmoves[v];
		}
		getmove(side);
		undoMove(board);
	}
	return(best);
}

int min(int depth, string input, int side) { 
	int best = 20000, score;
	if (checkEnd() != 0) return (checkEnd());
	if (depth == maxdepth) return (evaluate(score, input, depth));
	getmove(side);
	for (int v = 0; v < validmoves.size(); v++) {
		makeMove(validmoves[v], side);	
		score = max(depth+1, input, side);
		if (score < best) {
			best=score;
			input = validmoves[v];
		}
		getmove(side);
		undoMove(board);
	return(best);
	}
}

void AIMove(string AIinput,int 	side) {
	int best = -20000, score;
	int depth = 0;
	getmove(side);	
	for (int v = 0; v < validmoves.size(); v++) {
		AIinput = validmoves[v];
		makeMove(AIinput, side);
		score = max(depth+1, validmoves[v], side);
		if (score < best){
			best=score;
			AIinput = validmoves[v];
		}
		undoMove(board);
		getmove(side);
	}
	makeMove(AIinput,0);
}	

void validMoves(int side) {
	cout << "Your valid moves are:\n ";
	for (int vi = 0; vi < validmoves.size(); vi++) {
			cout << validmoves[vi] << " ";
		}
}		

int main() { 
    string input;
	string AImove;
	int side = 0;
    setup();
    cout << "Would you like to go First or Second?\n";
	while (true) {
		getline(cin, input);
		if (input.compare("F") == 0 || input.compare("FIRST") == 0 || input.compare("First") == 0 || input.compare("first") == 0) {
			cout << "You are going first.\n";
			side = 1;
			for (;;) {
				getmove(side);
				validMoves(side);
				printboard();
				cout << "Enter a move: ";
				getline(cin, input);
				while (checkValid(input) == 0) {
					cout << "Invalid move \n";
					getline(cin, input);
				}
				input.clear();
				makeMove(input, side);
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 7; j++) {
						tempboard[i][j] = board[i][j];
					}
				}
				if (checkEnd() == 5000) {
					cout << "You win.";
					printboard();
					break;
				}
				else if (checkEnd() == -5000) {
					cout << "You lose.";
					printboard();
					break;
				}
				side = 0;
				getmove(side);
				AIMove(AImove, side);
				AImove.clear();
				printboard();
				side = 1;
			}
		}
		
		else if (input.compare("S") == 0 || input.compare("SECOND")  == 0 || input.compare("Second")  == 0 || input.compare("s") == 0 || input.compare("second") == 0) {
			cout << "You are going second. \n";
			side = 0;
			for (;;) {
				getmove(side);
				AIMove(AImove, side);
				AImove.clear();
				printboard();
				side = 1;
				getmove(side);
				validMoves(side);
				printboard();
				cout << "Enter a move: ";
				getline(cin, input);
				while (checkValid(input) == 0) {
					cout << "Invalid move \n";
					getline(cin, input);
				}
				input.clear();
				makeMove(input, side);
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 7; j++) {
						tempboard[i][j] = board[i][j];
					}
				}
				printboard();
				if (checkEnd() == 5000) {
					cout << "You win.";
					break;
				}
				else if (checkEnd() == -5000) {
					cout << "You lose.";
					break;
				}
				side = 0;
			}
		}
		
		else {
			cout << "Invalid output. Type again.\n";
		}
	}
}