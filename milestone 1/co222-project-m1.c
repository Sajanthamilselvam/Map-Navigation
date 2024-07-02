/*CO222 Project - Milestone 01
E/19/338
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 26

// Global variables for the map
int H, W;
char map[MAX_SIZE][MAX_SIZE];   // 2D array to store the characters

//function prototype declaration
char inputStr[MAX_SIZE * MAX_SIZE]; 
int findMinDistance(int srcRow, int srcCol, int destRow, int destCol);


// Function to check  The function checks whether the move from the source cell to the destination cell is valid based on the difference in altitude between these two cells
int isValidMove(char src, char dest) 
{
    int diff = dest - src;  // Calculates the difference between the ASCII values 
    return (diff >= -2 && diff <= 2) || (diff >= -3 && diff <= 3);  // check if the move is valid based on the given conditions(ASCII(C2) -                                                                     ASCII(C1) <= 2 (Climbing) orASCII(C1) - ASCII(C2) <= 3 (Going down))
}

// Function to create the 2D array from the given string
void Array(char *str) {
    for (int index = 0; index < H * W; index++) {
        int i = index / W;        // Calculate the row index
        int j = index % W;        // Calculate the column index

        map[i][j] = str[index];   // Assign the current character of the string to the current position in the Array
    }
}


int main() {
    int startRow, startCol, endRow, endCol;
    // Reading the 4 inputs
    //printf("Enter the height and width of the array:");
    scanf("%d %d", &H, &W); // Store the Height and Width of the 2D array.

    // Finding the minimum value between two cells
    //printf("Enter the 1st line:");
    scanf("%d %d", &startRow, &startCol);   // Store the two integers for starting position
    
    //printf("Enter the 2nd line:");
    scanf("%d %d", &endRow, &endCol);   // Store the two integers for ending position

    //printf("Enter the map string:");
    scanf("%s", inputStr);      // For the map creation (Using the string)

    // Create the map
    Array(inputStr);

    // Find the minimum distance
    int minDistance = findMinDistance(startRow, startCol, endRow, endCol);

    // Output the result
    if (minDistance == INT_MAX) {
        printf("There is no possible path from %c to %c\n", map[startRow][startCol], map[endRow][endCol]);
    } else {
        printf("The minimum distance from %c to %c is %d\n", map[startRow][startCol], map[endRow][endCol], minDistance);
    }

    return 0;
}


// Function to find the minimum distance path

int findMinDistance(srcRow,srcCol,destRow,destCol) 
{
    // Array to store visited cells (To ensure that it is not processed again during the algorithm.)
    int visited[MAX_SIZE][MAX_SIZE] = {0};  //Initially, all cells are marked as not visited (0).
    
    // A 2D array (queue) will be store information about cell during the algorithm.
    int queue[MAX_SIZE * MAX_SIZE][3]; // it store information about row, col, distance cells
    int front = 0, rear = 0;    //front and rear pointer variables to keep track of the front and rear of the queue

    // Enqueue the starting cell
    queue[rear][0] = srcRow;    // the row of the starting cell which stores the row information of the starting cell in the queue
    queue[rear][1] = srcCol;    //the column of the starting cell which stores the column information of the starting cell in the queue.    
    queue[rear++][2] = 0;   // Distance of the cell from the starting point and increments the value by 1 after the assignment is done (move the pointer to the next position)
    visited[srcRow][srcCol] = 1;    // marking cells as visited in order to avoid revisiting the same cell multiple times, preventing an infinite loop

    // Possible moves (up, down, left, right)
    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};   // In a single move, you can go to the next cell, up, down, left or right. (No diagonal moves)


    while (front < rear) {  //main loop, checking whether cells in queue.
        int row = queue[front][0];  //getting the row index of the cell from the queue
        int col = queue[front][1];  //getting the column index of the cell from the queue
        int distance = queue[front][2]; // this distance represents how far we're traveled to reach the cell
        front++; // the loops continues until the queue is empty

        // Check if the destination is reached
        if (row == destRow && col == destCol) {
            return distance;
        }

        // Explore possible moves (up, down, left, and right)
        for (int i = 0; i < 4; i++) {
            int newRow = row + moves[i][0]; // new position represent nowRow and newCol
            int newCol = col + moves[i][1];

            // Check if the new position is within bounds and is a valid move
            if (newRow >= 0 && newRow < H && newCol >= 0 && newCol < W && !visited[newRow][newCol] && isValidMove(map[row][col], 
            map[newRow][newCol])) {

                // enqueue the new cell
                queue[rear][0] = newRow;
                queue[rear][1] = newCol;
                queue[rear++][2] = distance + 1;
                visited[newRow][newCol] = 1;
            }
        }
    }

    //    If the destination is not reachable within the given conditions, (return INT_MAX) to indicate an unreachable condition
    return INT_MAX;
}