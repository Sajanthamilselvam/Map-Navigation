/*
CO 222 PROJECT MILESTONE 02
TASK 01
E/19/338
*/

#include <stdio.h>

// Prototype functions

int isFibonacciEqual(int n, int equal1, int equal2);    // Function to check if a number is Fibonacci
int fib(int n); // Function to calculate Fibonacci number iteratively

int main() {
    // Declare variables to store user input
    int n, equal1, equal2;

    //printf("Enter three integers : ");
    scanf("%d %d %d", &n, &equal1, &equal2);    //store user input

    // Check if the Fibonacci value equal either equal1 or equal2
    int result = isFibonacciEqual(n, equal1, equal2);   //function calling

    // Output the result
    if (result) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }

    return 0;
}

// Function to check if a number is Fibonacci and equal to either of two given numbers
int isFibonacciEqual(int n, int equal1, int equal2) {
    // Calculate Fibonacci number for the given term
    int fibN = fib(n);  // calling the fib(n) function

    // Check if the calculated Fibonacci number equal to either equal1 or equal2
    return (fibN == equal1 || fibN == equal2);
}

// Function to calculate Fibonacci number iteratively
int fib(int n) {
    if (n == 0) {
        return 0;   //(Taking the 0th Fibonacci number as 0 and 1st as 1
    } else if (n == 1) {
        return 1;
    } else {
        int fibN_2 = 0;  // Initialize Fibonacci term n-2
        int fibN_1 = 1;  // Initialize Fibonacci term n-1
        int fibN = 0;    // Initialize Fibonacci term n

        for (int i = 2; i <= n; ++i) {
            fibN = fibN_1 + fibN_2;

            // Update Fibonacci terms for the next iteration
            fibN_2 = fibN_1;
            fibN_1 = fibN;
        }

        return fibN;
    }
}