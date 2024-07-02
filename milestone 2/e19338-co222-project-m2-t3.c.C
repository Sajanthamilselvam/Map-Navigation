/*
CO 222 PROJECT MILESTONE 02
TASK 03
E/19/338
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 26

// Global variables for the map
int H, W;
char map[MAX_SIZE][MAX_SIZE];  // 2D array to store the characters

// Prototype functions
int isFibonacciEqual(int n, int equal1, int equal2);
int fib(int n);
void createMap(char *str);
int findMinDistance(int srcRow, int srcCol, int destRow, int destCol);
int isValidMove(char src, char dest);
void findMinDistances(int startRow, int startCol, int endRow, int endCol, int tele1Row, int tele1Col, int tele2Row, int tele2Col);

// Function to create the 2D array from the given string
void createMap(char *str) {
    for (int index = 0; index < H * W; index++) {
        int i = index / W;        // Calculate the row index
        int j = index % W;        // Calculate the column index

        map[i][j] = str[index];   // Assign the current character of the string to the current position in the array
    }
}

// Function to find the minimum distance path
int findMinDistance(int srcRow, int srcCol, int destRow, int destCol) {
    // Array to store visited cells
    int visited[MAX_SIZE][MAX_SIZE] = {0};
    
    // A 2D array (queue) to store information about cells during the algorithm
    int queue[MAX_SIZE * MAX_SIZE][3];
    int front = 0, rear = 0;

    // Enqueue the starting cell
    queue[rear][0] = srcRow;
    queue[rear][1] = srcCol;
    queue[rear++][2] = 0;
    visited[srcRow][srcCol] = 1;

    // Possible moves (up, down, left, right)
    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (front < rear) {
        int row = queue[front][0];
        int col = queue[front][1];
        int distance = queue[front][2];
        front++;

        // Check if the destination is reached
        if (row == destRow && col == destCol) {
            return distance;
        }

        // Explore possible moves (up, down, left, and right)
        for (int i = 0; i < 4; i++) {
            int newRow = row + moves[i][0];
            int newCol = col + moves[i][1];

            // Check if the new position is within bounds and is a valid move
            if (newRow >= 0 && newRow < H && newCol >= 0 && newCol < W && !visited[newRow][newCol] && isValidMove(map[row][col], map[newRow][newCol])) {
                // Enqueue the new cell
                queue[rear][0] = newRow;
                queue[rear][1] = newCol;
                queue[rear++][2] = distance + 1;
                visited[newRow][newCol] = 1;
            }
        }
    }

    // If the destination is not reachable within the given conditions, return INT_MAX to indicate an unreachable condition
    return INT_MAX;
}

// Function to check if the move from the source cell to the destination cell is valid based on the difference in altitude between these two cells
int isValidMove(char src, char dest) {
    int diff = dest - src;  // Calculates the difference between the ASCII values 
    return (diff >= -2 && diff <= 2) || (diff >= -3 && diff <= 3);
}

// Function to find the minimum distances as specified
void findMinDistances(int startRow, int startCol, int endRow, int endCol, int tele1Row, int tele1Col, int tele2Row, int tele2Col) {
    // 1. From the starting point to the endpoint
    int dist1 = findMinDistance(startRow, startCol, endRow, endCol);

    // 2. From the starting point to the teleportation door point 1
    int dist2 = findMinDistance(startRow, startCol, tele1Row, tele1Col);

    // 3. From the starting point to the teleportation door point 2
    int dist3 = findMinDistance(startRow, startCol, tele2Row, tele2Col);

    // 4. From the teleportation door point 1 to the endpoint
    int dist4 = findMinDistance(tele1Row, tele1Col, endRow, endCol);

    // 5. From the teleportation door point 2 to the endpoint
    int dist5 = findMinDistance(tele2Row, tele2Col, endRow, endCol);

    // Output the results
    printf("The minimum distance from %c to %c is ", map[startRow][startCol], map[endRow][endCol]);

    // Check if teleportation is a better option
    if (dist2 != INT_MAX && dist4 != INT_MAX && dist5 != INT_MAX) {
        int teleportationDist1 = dist2 + 0 + dist4;
        int teleportationDist2 = dist3 + 0 + dist5;
        int teleportationDist = (teleportationDist1 < teleportationDist2) ? teleportationDist1 : teleportationDist2;

        if (teleportationDist < dist1) {
            printf("%d (Using teleportation)\n", teleportationDist);
            return;
        }
    }

    // If teleportation is not a better option or not possible, output the minimum distance without teleportation
    if (dist1 != INT_MAX) {
        printf("%d\n", dist1);
    } else {
        printf("There is no possible path from %c to %c\n", map[startRow][startCol], map[endRow][endCol]);
    }
}

int main() {
    int startRow, startCol, endRow, endCol, tele1Row, tele1Col, tele2Row, tele2Col, numDoors;

    // Reading the input
    scanf("%d %d", &H, &W);
    scanf("%d %d", &startRow, &startCol);
    scanf("%d %d", &endRow, &endCol);

    char inputStr[MAX_SIZE * MAX_SIZE];
    scanf("%s", inputStr);
    createMap(inputStr);

    int matchingFib1, matchingFib2;
    scanf("%d", &matchingFib1);
    scanf("%d", &matchingFib2);

    scanf("%d", &numDoors);

    // Array to store door positions
    int doorPositions[MAX_SIZE * MAX_SIZE][2];

    // Reading door positions
    for (int i = 0; i < numDoors; i++) {
        scanf("%d %d", &doorPositions[i][0], &doorPositions[i][1]);
    }

    // Find the minimum distances
    findMinDistances(startRow, startCol, endRow, endCol, doorPositions[0][0], doorPositions[0][1], doorPositions[1][0], doorPositions[1][1]);

    return 0;
}