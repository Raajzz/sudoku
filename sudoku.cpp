#include <iostream>
#include <vector>

// since I'm just doing a demo project, I'm using std namespace throughout the project to provide some productivity, this will be re-written later without using namespace std.
using namespace std;

bool is_good_num(vector<vector<int>> &board, int row, int col, int check_element){

  for(int i=0; i<9; i++){
    if(board[row][i] == check_element){
      return false;
    }
  }

  for(int i=0; i<9; i++){
    if(board[i][col] == check_element){
      return false;
    }
  }

  int start_row = row - row%3;
  int start_col = col - col%3;

  for(int i=0; i<start_row+3; i++){
    for(int j=0; j<start_col+3; j++){
      if(board[i][j] == check_element){
        return false;
      }
    }
  }

  return true;
}

bool sudoku_solver(vector<vector<int>> &board, int row, int col){

  // sudoku is solved
  if(row == 9){
    return true;
  } 
  // end of a row in the board
  if (col == 9){
    return sudoku_solver(board, row+1, 0);
  }
  // block is already filled
  if(board[row][col] != 0){
    return sudoku_solver(board, row, col+1);
  }

  for(int i=1; i<=9; i++){
    if(is_good_num(board, row, col, i)){
      board[row][col] = i;
      bool status = sudoku_solver(board, row, col+1);
      if(status){
        return true;
      }
      board[row][col] = 0;
    }
  }
  return false;
}

int main(){

  vector<vector<int>> board;
  board.reserve(9);

  // input
  cout << "Welcome to 9x9 sudoku solver!\n\nEnter your pattern with spaces or new-line between numbers, enter non-filled blocks with zeros!\n";

  int temp;
  for(int i=0; i<9; i++){
    vector<int> board_rows;
    board_rows.reserve(9);
    for(int j=0; j<9; j++){
      cin>>temp;
      board_rows.push_back(temp);
    }
    board.push_back(board_rows);
  }

  bool sudoku = sudoku_solver(board, 0, 0);

  if(sudoku){
    cout << "\nHere's your solved solutions!\n\n";
    for(int i=0; i<9; i++){
      for(int j=0; j<9; j++){
        cout << board[i][j] << " ";
      }
      cout << "\n";
    }
    cout << "\nThank you for stopping by <3 \nCome back soon!";
  } else {
    cout << "\nOh Vey! Some Error had occurred! \nPlease Try Again :'(";
  }

  return 0;
}