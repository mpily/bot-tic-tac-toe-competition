#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<unordered_map>
#include<utility>
#include<algorithm>
/*

*/
class scoreCounter{
public:
	char toput;
	int towin;
	std::string toCheck;
	char getOpp(char curr);
	scoreCounter(char,int,std::string&);
	std::pair<int,int> check();
};
scoreCounter :: scoreCounter(char a, int b, std::string& c){
	toput = a;
	towin = b;
	toCheck = c;
}
char scoreCounter::getOpp(char curr){
	if(curr == 'x')return 'o';
	else return 'x';
}
/*
	the algorithm to use works as follows

	for each row maintain a stack that holds the number of continuous cells
	als maintain the number of non-0 elements in the stack
	also maintain the type of element in the stack if there are only 0's maintain 0 else maintain the other type
	while reading the elements in the row :
		if the element is a 0 push it into the stack regardless
		if the element is the same as the main element in the stack add it to the stack and increment the count of the non-0 element
		if the element is different and the main element in the stack is 0  add it to the stack change the main element of the stack to be the current  element of the stack increment no-0 element
		otherwise :
		  increment the count of the current element.
			remove all but the last continuous set of  zero elements
			change the main element of the stack
			add the new element to the counter increment non zero element count by 1
	after all the cells are done check if there is anything to be updated before moving on
	it is affordable to also check if there is already a winner within the row first

*/

std::pair<int,int> scoreCounter :: check(){
	int p1 = 0;
	int p2 = 0;
	std::vector<char> stack;
	char mainelem = '0';
	int nonzero = 0;
	if(this->toCheck.size() < towin){
		return std:: make_pair(0,0);
	}
	for(int i = 0; i < this->toCheck.size(); i++){
		if(toCheck[i] == '0'){
			stack.push_back('0');
		}
		else if(toCheck[i] == mainelem){
			stack.push_back(toCheck[i]);
			nonzero+=1;
		}
		else if(mainelem == '0'){
			mainelem = toCheck[i];
			stack.push_back(toCheck[i]);
			nonzero = 1;
		}
		else{
			//incrementing count
			if(mainelem == this->toput && stack.size()>=this->towin){
				p1+=nonzero;
			}
			else if(mainelem == this->getOpp(this->toput) && stack.size() >= this->towin){
				p2+=nonzero;
			}
			//removing all but last continuous set of zeros
			std::vector<char> temp;
			for(int i = stack.size()-1 ; i >= 0; i--){
				if(stack[i] == '0')temp.push_back('0');
				else if(stack[i] != '0')break;
			}
			stack = temp;
			//adding new element to stack
			stack.push_back(toCheck[i]);
			mainelem = toCheck[i];
			nonzero = 1;
		}

	}
	if(mainelem == this->toput && stack.size()>=this->towin){
		p1+=nonzero;
	}
	else if(mainelem == this->getOpp(this->toput) && stack.size() >= this->towin){
		p2+=nonzero;
	}
	//checking if someone has won
	std::vector<char> temp;
	for(int j = 0; j < toCheck.size(); j++){
		if(toCheck[j] == '0')temp.clear();
		else if(temp.size()== 0)temp.push_back(toCheck[j]);
		else if(toCheck[j] == temp[0])temp.push_back(toCheck[j]);
		else{
			temp.clear();
			temp.push_back(toCheck[j]);
		}
		if(temp.size() == this->towin){
			if(temp[0] == this->toput)return std::make_pair(450,0);
			else return std::make_pair(0,450);
		}
	}
	return std::make_pair(p1,p2);
}
/*
Using min max algorithm to solve tic tac toe
A board is ranked as follows
	 if there is already a winner return 1 if it is the player who has won otherwise return 0
	 we count the number of continuous situations that can result in a win and weight them based off the number of continuous squares
	 note the above weighting is not the best as the difference between one with 2 and one which has only 1 is not that big but will have to do
	 std::get the difference between those for x and those for o
	 if the opponent is winning set the difference to -ve
	 return the fraction of the difference to the total wins


the code takes too long to run

*/

class board{
	public:
	  char toput;
	  char opponent;
	  std::vector<std::string>currstate;
	  int towin;
	  board(std::vector<std::string>board,char toPut,int toWin);
	  void play();
	  void display();
		char getOpp(char curr);
		bool checkNeighbours(int  ,int , std::vector<std::string>&);
		double minimax(int &, int &,std::vector<std::string>& board,int depth,bool isMax,double,double);
	  std::pair<int,int> horTrouble(std::vector<std::string>&);
	  std::pair<int,int> verTrouble(std::vector<std::string>&);
	  std::pair<int,int> leadDiagTrouble(std::vector<std::string>&);
	  std::pair<int,int> revDiagTrouble(std::vector<std::string>&);
};
board:: board(std::vector<std::string>board,char toPut,int toWin){
	this->currstate = board;
	this->toput = toPut;
	this->towin = toWin;


}
//function to check whether a move is valid and also whether if it is around one of  the other played moves
//will be better if you didnt add the need to be next to other moves
bool board:: checkNeighbours(int i, int j,std::vector<std::string>&piece){
	if(piece[i][j] != '0')return 0;
	else{
		if(i && j && piece[i-1][j-1] != '0')return 1;
		if(i && piece[i-1][j] != '0')return 1;
		if(i && j < piece.size()-1 && piece[i-1][j+1]!= '0')return 1;
		if(j && piece[i][j-1]!= '0')return 1;
		if(j && i <piece.size()-1 && piece[i+1][j-1]!='0')return 1;
		if(i < piece.size()-1 && piece[i+1][j] != '0')return 1;
		if(i < piece.size()-1 && j < piece.size()-1 && piece[i+1][j+1]!='0')return 1;
		if(j < piece.size()-1 && piece[i][j+1]!= '0')return 1;

	}
	return 0;
}
//function to std::get the opponent character
char board::getOpp(char curr){
	if(curr == 'x')return 'o';
	else return 'x';
}
//these are the main functions they count the number of continuous sections that might result in a win
//we do it horizontally first then vertically then diagonally
//In order to catch all continuous segments you need to do it twice once forward the other time in reverse


std::pair<int,int> board :: horTrouble(std::vector<std::string>&toCheck){
	//debugging purposes
	int p1 = 0;
	int p2 = 0;
	for (int i = 0; i < toCheck.size(); i++) {
		scoreCounter checking(this->toput,this->towin,toCheck[i]);
		std::pair<int,int> forrow = checking.check();
		if(forrow.first == 450)return forrow;
		else if(forrow.second == 450)return forrow;
		else{
			p1+=forrow.first;
			p2+=forrow.second;
		}
	}
	return std::make_pair(p1,p2);
}
std::pair<int,int> board :: verTrouble(std::vector<std::string> &toCheck){
	//debugging purposes
	int p1 = 0;
	int p2 = 0;
	for (int i = 0; i < toCheck.size(); i++){
		std::string temp;
		for(int j = 0; j < toCheck.size();j++){
			temp.push_back(toCheck[j][i]);
		}
		scoreCounter checking(this->toput,this->towin,temp);
		std::pair<int,int> forrow = checking.check();
		if(forrow.first == 450)return forrow;
		else if(forrow.second == 450)return forrow;
		else{
			p1+=forrow.first;
			p2+=forrow.second;
	}
}
	return std::make_pair(p1,p2);
}
std::pair<int,int> board :: leadDiagTrouble(std::vector<std::string>& toCheck){
	int p1 = 0;
	int p2 = 0;
	for(int k = 0; k < toCheck.size();k++){
		std::string temp ;
		for(int i = k, j =0; i < toCheck.size(); i++,j++){
			temp.push_back(toCheck[i][j]);
		}
		scoreCounter checking(this->toput,this->towin,temp);
		std::pair<int,int> forrow = checking.check();
		if(forrow.first == 450)return forrow;
		else if(forrow.second == 450)return forrow;
		else{
			p1+=forrow.first;
			p2+=forrow.second;
		}
	}
	return std:: make_pair(p1,p2);
}
std::pair<int,int> board :: revDiagTrouble(std::vector<std::string>& toCheck){
	int p1 = 0;
	int p2 = 0;
	for(int k = toCheck.size()-1; k >=0 ;k--){
		std::string temp ;
		for(int i = k, j =0; i >= 0; i--,j++){
			temp.push_back(toCheck[i][j]);
		}
		scoreCounter checking(this->toput,this->towin,temp);
		std::pair<int,int> forrow = checking.check();
		if(forrow.first == 450)return forrow;
		else if(forrow.second == 450)return forrow;
		else{
			p1+=forrow.first;
			p2+=forrow.second;
		}
	}
	return std:: make_pair(p1,p2);
}

double board :: minimax(int & row,int & col ,std::vector<std::string> &toPlay,int depth,bool isMax,double alpha, double beta){
	std::pair<int,int>score1 = this->horTrouble(toPlay);
	std::pair<int,int>score2 = this->verTrouble(toPlay);
	std::pair<int,int>score3 = this->leadDiagTrouble(toPlay);
	std::pair<int,int>score4 = this->revDiagTrouble(toPlay);
	double marks = double(score1.first-score2.second + score2.first - score2.second + score3.first - score3.second + score4.first-score4.second);
	if(score1.first == 450 || score1.second == 450 ||score2.first == 450 || score2.second == 450 ||score3.first == 450 || score3.second == 450 ||score4.first == 450 || score4.second == 450 ){
	/*	//std::cout<<"when we got to having placed at"<< " \n";
		for(auto a : toPlay){
			for(auto b: a){
				std::cout<<b<<" ";
			}
			std::cout<<"\n";
		}
		std::cout<<"it has marks"<<marks<<"\n";*/
		if(score1.first == 450 || score2.first == 450 || score3.first == 450 || score4.first == 450 )
		return 10000;
		else if(score1.second == 450 || score2.second == 450 || score3.second == 450 || score4.second == 450 )
		return -10000;
	}
	if(depth == 0){
	/*	//std::cout<<"when we got to having placed at"<< " \n";
		for(auto a : toPlay){
			for(auto b : a){
				std::cout<<b<<" ";
			}
			std::cout<<"\n";
		}
		std::cout<<"\n";
		std::cout<<"it has marks"<<marks<<"\n";*/
		return marks;
	}
	else{
		if(isMax){
			double bestOut = -50000.0;
			bool played = 0;
			for(int i = 0; i < toPlay.size(); i++){
				bool cont = 1;
				for (int j = 0; j < toPlay.size(); j++){
					if( toPlay[i][j] == '0' ){
						played = 1;
						toPlay[i][j] = this->toput;
						double res = minimax(row,col,toPlay,depth-1,0,alpha,beta);
						bestOut = std::max(bestOut,res);
						alpha = std::max(alpha,bestOut);
						/*for debugging purposes*/
						///////////
						/*
						if(res == bestOut){
							std::cout<<"the candidate to win is \n";
							for (auto a : toPlay){
								for (auto b : a){
									std::cout << b<<" ";
								}
								std::cout << '\n';
							}
							std::cout << "which has a score of "<<res << '\n';
					  }
						*/
						//////////////
						toPlay[i][j] = '0';
						if(res == bestOut && depth == 6){
							row = i; col = j;
						}
						if(beta <= alpha){cont = 0;break;}
					}
				}
				if(cont == 0)break;
			}

			if (played) return bestOut;
			else return 0;
		}
		else{
			bool played = 0;
			double bestOut = 50000.0;
			for(int i = 0; i < toPlay.size(); i++){
				for(int j = 0; j < toPlay.size(); j++){
					if(toPlay[i][j] == '0'){
						played = 1;
						toPlay[i][j] = this ->getOpp(this->toput);
						double res = minimax(i,j,toPlay,depth-1,1,alpha,beta);
						bestOut = std::min(bestOut,res);
						beta = std::min(bestOut,beta);
						/*for debugging purposes*/
						///////////
						/*
						if(res == bestOut){
							std::cout<<"the candidate to lose is \n";
							for (auto a : toPlay){
								for (auto b : a){
									std::cout << b<<" ";
								}
								std::cout << '\n';
							}
							std::cout << "which has a score of "<<res << '\n';
					  }
						*/
						//////////////
						toPlay[i][j] = '0';
						if(beta <= alpha)break;
					}
				}
			}
			if (played) return bestOut;
			else return 0;
		}
	}
}
void board :: display(){
	for(auto a : this ->currstate){
		for(auto b : a){
			std::cout<<b;
		}
		std::cout<<"\n";
	}
}
void board :: play(){
	int row,col;
	double high = -50000.0;
	double result = minimax(row,col,this->currstate,6,1,-50000,50000);

	this->currstate[row][col] = toput;
	this->display();
}

//driver code
int main(int argc, char *argv[]) {
	if(argc < 5){
		std::cout<<"have been given insufficient arguments \n";
		return 0;
	}
	std::string temp = argv[1];
	int towin = 0;
	int boardsize = 0;
	for (auto a : temp){
	boardsize*=10;
	boardsize+= (a-'0');
	}
	temp = argv[2];

	for (auto a : temp){
		towin*=10;
		towin+=a-'0';
	}
	std::vector<std::string>boardrep(boardsize);
	temp = argv[3];
	for(int i = 0; i < boardsize; i++){
		for(int j = 0; j < boardsize; j++){
			boardrep[i].push_back(temp[i*boardsize + j]);
		}
	}
	char toput = argv[4][0];
	std::vector<std::string> trial1 = {"000000","000000","000000","000000","000000","000000"};
	board newBoard(boardrep,toput,towin);
	newBoard.play();
	//std::pair<int,int>testing = newBoard.verTrouble(trial1);
	// /std::cout<<"have obtained "<<testing.first<<" "<<testing.second<<"\n";
  return 0;
}
