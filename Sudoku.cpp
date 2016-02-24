#include<vector>
#include<set>
#include<string>
#include<iostream>
#include<map>

using namespace std;
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
	bool rowMap[9][9]={0},colMap[9][9]={0},gridMap[9][9]={0};
	for(int r = 0; r < 9; ++r){
		for(int c = 0; c < 9; ++c){
			int grid = (r/3)*3 + c/3;
			int charId =board[r][c] - '1';
			if(board[r][c] != '.'){
				rowMap[r][charId] = true;
				colMap[c][charId] = true;
				gridMap[grid][charId]= true;
			}
		}
	}
        solveSudoku(board, 0, rowMap, colMap, gridMap);
    }
    bool solveSudoku(vector<vector<char>>& board, int start, bool rowMap[][9], bool colMap[][9], bool gridMap[][9]) {
        while(start < 81 && board[start/9][start%9] != '.') start++;
        if(start == 81) return true;

	int row = start/9;
	int col = start%9;
	int grid = (row/3)*3 + col/3 ;
	for(int i = 0 ; i < 9; i++){
	    if(!rowMap[row][i] && !colMap[col][i] && !gridMap[grid][i]){
		rowMap[row][i] = true;
		colMap[col][i] = true;
		gridMap[grid][i]= true;
            	board[row][col] = i+'1';
            	if(solveSudoku(board, start+1, rowMap, colMap, gridMap)) return true;
            	board[row][col] = '.';
		rowMap[row][i] = false;
		colMap[col][i] = false;
		gridMap[grid][i]= false;
	   }
        }
        return false;
    }
};

int main(){
	string v[] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."}; 
	vector<vector<char>> board(9);
	for(int i = 0 ; i < 9; ++i){
		std::copy(v[i].begin(), v[i].end(), std::back_inserter(board[i]));
	}
	Solution s;
	for(int i = 0 ; i < 9; ++i){
		string str(board[i].begin(),board[i].end());
		cout << str << endl;
	}
	s.solveSudoku(board);
	cout << "===================" <<endl;
	for(int i = 0 ; i < 9; ++i){
		string str(board[i].begin(),board[i].end());
		cout << str << endl;
	}
	return 0;
}
