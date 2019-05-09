/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"


CellContent op_field[10][10];
CellContent my_field[10][10];
CellContent my_guess[10][10];
/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
  FILE* fd_op = fopen("battleship.op", "r");
  FILE* fd_my = fopen("battleship.my", "r");

  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 10; ++j)
    {
        my_guess[i][j] = Unknown;

        fread(&my_field[i][j], sizeof(CellContent), 1, fd_my);
        fread(&op_field[i][j], sizeof(CellContent), 1, fd_op);
    }
  }
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
  if (row < 0 || col < 0 || row >= 10 || col >= 10)
  {
    return OutOfRange;
  }
  return my_field[row][col];

}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if (row < 0 || col < 0 || row >= 10 || col >= 10)
  {
    return false;
  }

  if (op_field[row][col] == Boat)
  {
    my_guess[row][col] = Boat;

    SetWater(row-1,col);
    SetWater(row-1,col-1);
    SetWater(row-1,col+1);

    SetWater(row+1,col);
    SetWater(row+1,col-1);
    SetWater(row+1,col+1);

    SetWater(row,col+1);
    SetWater(row,col-1);
  }
  else
  {
    my_guess[row][col] = Water;
  }
  return true;

}

void SetWater(int row, int col)
{
  if (row < 0 || col < 0 || row >= 10 || col >= 10)
  {
    return;
  }
  my_guess[row][col] = Water;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if (row < 0 || col < 0 || row > 10 || col > 10)
  {
    return OutOfRange;
  }
  return my_guess[row][col];

}
