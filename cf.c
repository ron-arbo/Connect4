#include <stdio.h>
#include <stdbool.h>

//Will print the board for the user
void printBoard(char input[7][8]){
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 8; j++){
      printf("%c ", input[i][j]);
    }
    printf("\n");
  }
}

//This method will determine if the input place on the board is the start of a vertical 
//winning connection, returning true or false
bool vertWinner(char board[7][8], int i, int j){
  if(i > 3){
    return false;
  }
  char current;
  current = board[i][j];
  if(current == 'X' || current == 'O'){
     if(board[i+1][j] == current && 
        board[i+2][j] == current && 
        board[i+3][j] == current){
        return true;
      }
  }
  return false;
}

//This method will determine if the input place on the board is the start of a horizontal 
//winning connection, returning true or false
bool horizontalWinner(char board[7][8], int i, int j){
  if(j > 4){
    return false;
  }
  char current;
  current = board[i][j];
  if(current == 'X' || current == 'O'){
     if(board[i][j+1] == current && 
        board[i][j+2] == current && 
        board[i][j+3] == current){
        return true;
      }
  }
  return false;
}

//This method will determine if the input place on the board is the start of a diagonal 
//winning connection, returning true or false
bool diagonalWinner(char board[7][8], int i, int j){
  if(i > 3){
    return false;
  }
  char current;
  current = board[i][j];
  if(current == 'X' || current == 'O'){
     if(board[i+1][j+1] == current && 
        board[i+2][j+2] == current && 
        board[i+3][j+3] == current){
        return true;
      }
      if(board[i+1][j-1] == current && 
         board[i+2][j-2] == current && 
         board[i+3][j-3] == current){
        return true;
      }

  }
  return false;
}

//This method will return the char of the player who has won the game, or if there is 
//no winner yet, 'N'
char winningState(char board[7][8], char humanChar, char aiChar){
  char current;
  for(int i = 1; i < 7; i++){
    for(int j = 1; j < 8; j++){
      current = board[i][j];
      if(current == humanChar || current == aiChar){
       if(vertWinner(board, i, j) || 
          horizontalWinner(board, i, j) ||
          diagonalWinner(board, i, j)){
          return current;
       }
      }
    }
  }
  return 'N';
}

//This method will tell whether or not the user should keep playing 
//(i.e. whether someone has won or the board is filled)
bool keepPlaying(char board[7][8], char humanChar, char aiChar){
  //Check to see if there is a winner already
  if(winningState(board, humanChar, aiChar) == 'N'){
    return true;
  }
  else{
    return false;
  }
  
  //Checks if there are any empty spaces left
  for(int i = 1; i < 7; i++){
    for(int j = 1; j < 8; j++){
      if(board[i][j] == '.'){
        return true;
      }
    }
  }
  return false;
}

//This method will enter a char into a column, based on if its the ai or the human. It will also populate the moves array for whoever uses the method
void insertToColumn(char board[7][8], char column, char insert, char movesArray[21]){
  for(int j = 0; j < 8; j++){
    if(board[0][j] == column){
      //Checks if column is already full
      if(board[1][j] != '.'){
        printf("Sorry that column is full, please try another\n");
      }
      //Inserts the char into the column
      for(int i = 0; i < 7; i++){
        if(board[i+1][j] != '.'){
          board[i][j] = insert;
          break;
        }
      }
    }
  }
  
  //Adds the move to the moves array
 for(int i = 0; i < 21; i++){
 	if(movesArray[i] == '\0'){
 	   movesArray[i] = column;
 	   movesArray[i+1] = '\0';
 	   break;
 	}
 }
}

//This method will find a vertical pattern of the char lookingFor, and depending on the
//number in-a-row that the AI is looking for (this is the parameter inRow) it will return 
//which column the piece should be entered in. If it cannot find a column it will return 
//'N' instead.
char findVertical3(char board[7][8], char lookingFor, int inRow){
  //Iterates through board to find possible place to play, taking into account how many 
  //in-a-row it is looking for
  for(int i = 1; i <= 3; i++){
    for(int j = 1; j < 8; j++){
      if(board[i][j] == '.'){
      	if(board[i+1][j] == lookingFor){
        	if(inRow == 1){
      	     return board[0][j];
		  	}
      		if(board[i+2][j] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
      			if(board[i+3][j] == lookingFor){
      				if(inRow == 3){
                		return board[0][j];
             		}
      			}
			}
   		 }
 	   }
	}
  }
 return 'N';
}

//This method will find a horizontal pattern of pieces of the char lookingFor, and 
//depending on the number in-a-row that the AI is looking for (parameter lookingFor) it 
//will return the column of where the piece should be played. If it cannot find a column, 
//it will return 'N'
char findHorizontal3(char board[7][8], char lookingFor, int inRow){
  //Iterates through board to find possible place to play, taking into account how many 
  //in-a-row it is looking for
  for(int i = 1; i < 7; i++){
    for(int j = 1; j < 8; j++){
      if(board[i][j] == '.'){
        //Fills free spot to the left of 3
        if(board[i][j+1] == lookingFor){
      		if(inRow == 1){
      			return board[0][j];
      		}
      		if(board[i][j+2] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
      			if(board[i][j+3] == lookingFor){
                	//This second condition is to make sure the spot below the desired 
              		//play is not empty,otherwise the piece would fall through and the AI 
              		//would make the wrong play
      				if(inRow == 3 && board[i+1][j] != '.'){
                		return board[0][j];
              		}
      			}
          	}
        }
        //Fills free spot to the right of 3   
        if(board[i][j-1] == lookingFor){
      		if(inRow == 1){
      			return board[0][j];
      		}
      		if(board[i][j-2] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
           		//This second condition is to make sure the spot below the desired 
              		//play is not empty,otherwise the piece would fall through and the AI 
              		//would make the wrong play
      			if(board[i][j-3] == lookingFor && board[i+1][j] != '.'){
              		if(inRow == 3){
      				  return board[0][j];
             		}
      			}
    		} 
    	}
      }
    }
  } 
  return 'N';
}

//This method will find a diagonal 3 in-a-row of the parameter lookingFor to either block 
//or win the game. Otherwise it will return 'N'
char findDiagonal3(char board[7][8], char lookingFor, int inRow){
  //Iterates through board to find possible place to play, taking into account how many 
  //in-a-row it is looking for
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 8; j++){
      if(board[i][j] == '.'){
        //Check top left
        if(board[i+1][j+1] == lookingFor){
      		if(inRow == 1){
      			return board[0][j];
      		}
      		if(board[i+2][j+2] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
      			if(board[i+3][j+3] == lookingFor){
              		//This second condition is to make sure the spot below the desired 
              		//play is not empty,otherwise the piece would fall through and the AI 
              		//would make the wrong play
              		if(inRow == 3 && board[i+1][j] != '.'){
      				  return board[0][j];
             		 }
      			}
          	}
        }
        //Check top right
        if(board[i+1][j-1] == lookingFor){
      		if(inRow == 1){
      			return board[0][j];
      		}
      		if(board[i+2][j-2] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
      			if(board[i+3][j-3] == lookingFor){
             		//This second condition is to make sure the spot below the desired 
              		//play is not empty,otherwise the piece would fall through and the AI 
              		//would make the wrong play
              		if(inRow == 3 && board[i+1][j] != '.'){
      					return board[0][j];
              		}
      			}
         	 }
        }
        //Check bottom left
        if(board[i-1][j+1] == lookingFor){
      		if(inRow == 1){
      			return board[0][j];
      		}
      		if(board[i-2][j+2] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
      			if(board[i-3][j+3] == lookingFor){
              		if(inRow == 3){
      					return board[0][j];
             		 }
      			}
          	}
        }
        //Check bottom right
        if(board[i-1][j-1] == lookingFor){
      		if(inRow == 1){
      			return board[0][j];
      		}
      		if(board[i-2][j-2] == lookingFor){
      			if(inRow == 2){
      				return board[0][j];
      			}
      			if(board[i-3][j-3] == lookingFor){
              		if(inRow == 3){
      			  		return board[0][j];
             		 }
      			}
        	}
        }
      }
    }
  }
    return 'N';
}

//This method will have the AI play a piece
void aiPlay(char board[7][8], char humanChar, char aiChar, char aiMoves[21]){
  //This loop changes the threshold of how many pieces should be in a row before the 
  //AI decides it wants to move there. It starts at 3 for obvious reasons as it can win a
  //game or block a winning move, and then it moves down in order to build up or stop
  //opponents from building up. And, like your average 5-year-old,it prioritizes offense
  char columnInsert;
  for(int inRow = 3; inRow >= 1; inRow--){
  
    //Takes vertical win/move if there
    columnInsert = findVertical3(board, aiChar, inRow);
    if(columnInsert != 'N'){
  	  insertToColumn(board, columnInsert, aiChar, aiMoves);
  	  return;
    }
  
    //Takes horizontal win/move if there
    columnInsert = findHorizontal3(board, aiChar, inRow);
    if(columnInsert != 'N'){
  	  insertToColumn(board, columnInsert, aiChar, aiMoves);
  	  return;
    }
  
    //Takes diagonal win/move if there
    columnInsert = findDiagonal3(board, aiChar, inRow);
    if(columnInsert != 'N'){
  	  insertToColumn(board, columnInsert, aiChar, aiMoves);
  	  return;
    }
  
    //Takes vertical block if there
    columnInsert = findVertical3(board, humanChar, inRow);
    if(columnInsert != 'N'){
      insertToColumn(board, columnInsert, aiChar, aiMoves);
      return;
    }

    //Takes horizontal block if there
    columnInsert = findHorizontal3(board, humanChar, inRow);
    if(columnInsert != 'N'){
      insertToColumn(board, columnInsert, aiChar, aiMoves);
      return;
    }

    //Takes diagonal block if there
    columnInsert = findDiagonal3(board, humanChar, inRow);
    if(columnInsert != 'N'){
      insertToColumn(board, columnInsert, aiChar, aiMoves);
      return;
    }
  }

  
  //If there are no offensive/defensive moves that the computer recognizes,
  //it will drop a piece in the column with the least amount of pieces in it already
  char column = 'A';
  for(int i = 6; i > 0; i--){
  	for(int j = 1; j < 8; j++){
  		if(board[i][j] == '.'){
  		   column = board[0][j];
  		   break;
  		}
  	}
  	break;
  }
  insertToColumn(board, column, aiChar, aiMoves);
}

//This will allow the user to play a piece
void userPlay(char board[7][8], char humanChar, char humanMoves[21]){
  //Column to be played
  char column;
  
  do{
    printf("Your turn! In which column would you like to play a piece? (Please enter a capital letter A-G)\n");
    scanf(" %c", &column);

    if(column < 65 || column > 71){
       printf("Unreognized input! Please make sure to input a captial letter between A and G!\n");
    }
  }
 while(column < 65 || column > 71);
  
 //Inserting piece to specified column 
 insertToColumn(board, column, humanChar, humanMoves);
}

int main(void) {
//Defining the gameBoard
  char gameBoard[7][8];
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 8; j++){
      gameBoard[i][j] = '.';
    }
  }
  gameBoard[0][0] = ' ';
  gameBoard[1][0] = '6';
  gameBoard[2][0] = '5';
  gameBoard[3][0] = '4';
  gameBoard[4][0] = '3';
  gameBoard[5][0] = '2';
  gameBoard[6][0] = '1';
  gameBoard[0][1] = 'A';
  gameBoard[0][2] = 'B';
  gameBoard[0][3] = 'C';
  gameBoard[0][4] = 'D';
  gameBoard[0][5] = 'E';
  gameBoard[0][6] = 'F';
  gameBoard[0][7] = 'G';

  //Player choosing order
  char choice;
  do{
    printf("Would you like to play first? Enter 'Y' or 'N'\n");
    scanf(" %c", &choice);

    if(choice != 'Y' && choice != 'N'){
      printf("Unrecognized input! Remember, enter a capital Y or a captial N to answer!\n");
    }
  }while(choice != 89 && choice != 78);

 //Arrays to keep track of moves
 char humanMoves[21];
 char aiMoves[21];
 
 //Null chars that will be used to check where to add the next item/stop printing
 humanMoves[0] = '\0';
 aiMoves[0] = '\0';

 //These variables are to keep track of who is playing which pieces (X or O)
 char humanChar;
 char aiChar;
  
  if(choice == 'Y'){
  //Player goes first
  printf("Alright! You are Xs, good luck!\n");
  humanChar = 'X';
  aiChar = 'O';
    //Board will print, user can play, AI will play, then repeats until game is over
    while(keepPlaying(gameBoard, humanChar, aiChar)){
      printBoard(gameBoard);
      userPlay(gameBoard, humanChar, humanMoves);
      if(keepPlaying(gameBoard, humanChar, aiChar)){
        aiPlay(gameBoard, humanChar, aiChar, aiMoves);
        printf("AI has moved\n");
      }
    }
  }
  //AI goes first
  else{
    printf("Alright! You are Os, good luck!\n");
    humanChar = 'O';
    aiChar = 'X';
    //AI plays first, board is printed, user can play, then repeats until game is over
    while(keepPlaying(gameBoard, humanChar, aiChar)){
      aiPlay(gameBoard, humanChar, aiChar, aiMoves);
      printBoard(gameBoard);
      printf("AI has moved\n");
      if(keepPlaying(gameBoard, humanChar, aiChar)){
        userPlay(gameBoard, humanChar, humanMoves);
      }
    }
  }

  //Shows final result
  printBoard(gameBoard);
  
  //Determines char of winner, then prints results accordingly
  char c = winningState(gameBoard, humanChar, aiChar);
  if(c == humanChar){
    printf("It looks like you, the player, have won! Congratulations!\n");
    printf("Here are the moves that won you the game:\n");
    for(int i = 0; i < 21; i++){
    	if(humanMoves[i] == '\0'){
    		break;
    	}
    	printf("%c ", humanMoves[i]);
    }
  }
  if(c == aiChar){
    printf("Yikes, tough loss. You lost to a 5-year old\n");
    printf("Here are the moves it used to beat you:\n");
    for(int i = 0; i < 21; i++){
    	if(aiMoves[i] == '\0'){
    		break;
    	}
    	printf("%c ", aiMoves[i]);
    }
  }
  if(c == 'N'){
  	printf("Looks like this one was a draw. Better luck next time!\n");
  }
  return 0;
}