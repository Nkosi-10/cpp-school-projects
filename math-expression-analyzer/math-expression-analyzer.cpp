#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

// This function calculates the value of the expression f(x) = Ax² + Bsin(Cx) + D.
// It takes coefficients A, B, C, D, and a value for x, then spits out the result.
double calculateExpression(int A, int B, int C, int D, int x) {
    return A * x * x + B * sin(C * x) + D;
}

// This function determines  the average of  numbers in an array.
// It sums up all the numbers and then divides by how many there are.
double calculateMean(double* data, int size) {
    double total = 0;
    double* ptr = data;
    for (int i = 0; i < size; i++, ptr++) {
        total += *ptr;
    }
    return total / size;
}

// This function calculates the standard deviation, showing how spread out the numbers are from their average.
double calculateStdDev(double* data, int size, double mean) {
    double sum = 0;
    double* ptr = data;
    for (int i = 0; i < size; i++, ptr++) {
        sum += pow(*ptr - mean, 2);
    }
    return sqrt(sum / size);
}

// This function goes through an array and separates the sum of positive numbers from the sum of negative numbers.
void findPosNegSums(double* data, int size, double& posSum, double& negSum) {
    posSum = 0;
    negSum = 0;
    // The pointer helps us check each value.
    double* ptr = data;
    for (int i = 0; i < size; i++, ptr++) {
        if (*ptr > 0) posSum += *ptr;
        else negSum += *ptr;
    }
}

// This transformation function calculates the square root of a number, but only if it's positive.
double squareRoot(double x) { return x > 0 ? sqrt(x) : x; }
// This transformation function calculates the natural logarithm of a number, but only if it's positive.
double logarithm(double x) { return x > 0 ? log(x) : x; }
// This transformation function calculates the inverse (1/x) of a number, making sure we don't divide by zero.
double inverse(double x) { return x != 0 ? 1.0 / x : x; }

// This function applies any given transformation (like square root or inverse) to every number in an array.
void applyTransformation(double* data, int size, double(*func)(double)) {
    // We're using a pointer to modify each element directly.
    double* ptr = data;
    for (int i = 0; i < size; i++, ptr++) {
        *ptr = func(*ptr);
    }
}

// This function calculates the sum of numbers in an array using recursion.
// It basically adds the first number to the sum of the rest of the numbers, calling itself for the rest.
double recursiveSum(double* data, int size) {
    if (size == 0) return 0;
    return *data + recursiveSum(data + 1, size - 1);
}

// This function swaps two arrays by simply swapping the pointers that point to their starting memory locations.
void swapArrays(double** a, double** b) {
    double* temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    // This line initializes the random number generator, so you get different random numbers each time you run the program.
    srand(time(0));

    int n;
    cout << "Enter how many expressions to generate: ";
    cin >> n;

    int totalValues = n + 11;

    // Dynamically allocates memory for an array to store the calculated expression values.
    double* expressions = new double[totalValues];
    double* ptr = expressions;

    for (int x = -10; x <= n; x++, ptr++) {
        // Generates random coefficients A, B, C, and D for each expression.
        int A = rand() % 101 - 50;
        int B = rand() % 101 - 50;
        int C = rand() % 101 - 50;
        int D = rand() % 101 - 50;

        // Calculates the expression using the random coefficients and current x, then stores it.
        *ptr = calculateExpression(A, B, C, D, x);
    }

    // Calculates the average of all the generated expression values.
    double mean = calculateMean(expressions, totalValues);
    // Calculates the standard deviation of the expression values, showing their spread.
    double stddev = calculateStdDev(expressions, totalValues, mean);
    // Declares variables to hold the sums of positive and negative numbers.
    double posSum, negSum;
    // Finds and stores the sums of positive and negative values from the expressions array.
    findPosNegSums(expressions, totalValues, posSum, negSum);
    // Calculates the total sum of all expression values using a recursive function.
    double total = recursiveSum(expressions, totalValues);

    // Prints a header for the statistics output.
    cout << "\n Statistics \n";
    // Displays the calculated mean.
    cout << "Mean: " << mean << endl;
    // Shows the standard deviation.
    cout << "Standard Deviation: " << stddev << endl;
    // Prints the sum of all positive numbers.
    cout << "Sum of Positives: " << posSum << endl;
    // Prints the sum of all negative numbers.
    cout << "Sum of Negatives: " << negSum << endl;
    // Displays the total sum, calculated recursively.
    cout << "Total Sum : " << total << endl;

    applyTransformation(expressions, totalValues, inverse);

    cout << "\n--- Inverse ---\n";
    // Resets the pointer to the beginning of the array to print the transformed values.
    ptr = expressions;
    for (int i = 0; i < totalValues; i++, ptr++) {
        cout << *ptr << " ";
    }
    cout << endl;

    // Allocates memory for a second array of the same size.
    double* secondArray = new double[totalValues];
    for (int i = 0; i < totalValues; i++) {
        *(secondArray + i) = rand() % 101 - 50;
    }

    // Swaps the 'expressions' array with the 'secondArray' by exchanging their pointers.
    swapArrays(&expressions, &secondArray);

    // Prints a header indicating that the arrays have been swapped.
    cout << "\n--- After Swapping Arrays ---\n";
    ptr = expressions;
    for (int i = 0; i < totalValues; i++, ptr++) {
        cout << *ptr << " ";
    }
    cout << endl;

    delete[] expressions;
    delete[] secondArray;

    return 0;
}
