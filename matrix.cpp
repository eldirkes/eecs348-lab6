/*
    Ethan Dirkes
    KU ID 3064954
    EECS 348
    Lab 6
*/

#include <iostream>
#include <fstream>
#include <string>

/*
	Get the size of the square matrix.
	
	Reads the first line of the file and returns that as an int.
*/
int getMatrixSize(std::ifstream& infile);

/*
	Takes in a file and the desired size of the matrix and returns a matrix of said size.
	
	Reads the first matrixSize lines of the file and organizes that into a 2D array.
*/
int** toMatrix(std::ifstream& infile, const int matrixSize);

/*
	Calculate the sum between two matrices, and return as a new matrix.
*/
int** sumMatrix(int** matrix1, int** matrix2, const int mSize);

/*
	Calculate the difference between two matrices, and return as a new matrix.
*/
int** diffMatrix(int** matrix1, int** matrix2, const int mSize);

/*
	Calculate the product of two matrices, and return as a new matrix
*/
int** multMatrix(int** matrix1, int** matrix2, const int mSize);

/*
	Print the contents of a matrix.
	
	Done by iterating through the matrix and printing the number at each position, with a space inbetween
	and a new line at the end of each row.
*/
void printMatrix(int** matrix, const int mSize);

int main() {
	/*
		Store the contents of the matrix_input.txt file into userFile.
		Run the getMatrixSize function to get the size of the matrices (first line of file) and
		store it in matrixSize variable.
		If the matrix size is large than 100, then the size is invalid and the program exits.
	*/
    std::ifstream userFile ("matrix_input.txt");
    static const int matrixSize = getMatrixSize(userFile);
	if (matrixSize > 100) {
		std::cout << "Matrix size must be less than or equal to 100" << std::endl;
		exit(0);
	}
	
	/*
		Create each matrix, where
		matrices A and B are read from the file,
		matrix C is the sum of A and B,
		matrix D is the product of A and B, and
		matrix E is the difference of A and B.
	*/
    int** matrixA = toMatrix(userFile, matrixSize);
	int** matrixB = toMatrix(userFile, matrixSize);
	int** matrixC = sumMatrix(matrixA, matrixB, matrixSize);
	int** matrixD = multMatrix(matrixA, matrixB, matrixSize);
	int** matrixE = diffMatrix(matrixA, matrixB, matrixSize);
	
	// print the "header" of the output
	std::cout << std::endl;
	std::cout << "Ethan Dirkes" << std::endl << "Lab#6: Matrix Manipulation" << std::endl;
	std::cout << std::endl;
	
	// print the contents of matrixA
	std::cout << "Matrix A:" << std::endl;
    printMatrix(matrixA, matrixSize);
	std::cout << std::endl;
	
	// print the contents of matrix B
	std::cout << "Matrix B:" << std::endl;
	printMatrix(matrixB, matrixSize);
	std::cout << std::endl;
	
	// print the contents of matrix C
	std::cout << "Matrix Sum (A + B):" << std::endl;
	printMatrix(matrixC, matrixSize);
	std::cout << std::endl;

	// print the contents of matrix D
	std::cout << "Matrix Product (A * B):" << std::endl;
	printMatrix(matrixD, matrixSize);
	std::cout << std::endl;
	
	// print the contents of matrix E
	std::cout << "Matrix Difference (A - B):" << std::endl;
	printMatrix(matrixE, matrixSize);
	std::cout << std::endl;
    
	return 0;
}

/*
	Get the size of the square matrix.
	
	Reads the first line of the file and returns that as an int.
*/
int getMatrixSize(std::ifstream& infile) {
    std::string fileText;
    while (std::getline(infile, fileText)) {
        return std::stoi(fileText);
    }
}

/*
	Takes in a file and the desired size of the matrix and returns a matrix of said size.
	
	Reads the first matrixSize lines of the file and organizes that into a 2D array.
*/
int** toMatrix(std::ifstream& infile, const int matrixSize) {
	static const int maxSize = 100;	// the max possible size of the array, given by assignment description
	
	/*
		Create the 2D array and the string to read each line of the file to, and initialize counters
		to track the current row and column of the matrix.
	*/
	int** fileMatrix = new int*[maxSize];
	std::string fileText;
	int row = 0;
	int col = 0;
	
	/*
		Read each line from the file to store in the matrix, and write the current
		line to the fileText string.
	*/
	while (std::getline(infile, fileText)) {
		
		/*
			Initialize each row of the matrix and initialize
			the first index of each row to be 0.
		*/
		fileMatrix[row] = new int[maxSize];
		fileMatrix[row][col] = 0;
		
		/*
			Read through each character of the current line add it to the matrix at the current (row, col).
			
			If the current character is not a digit then increment to the next column (new entry in the matrix)
			and initialize the new entry to 0.
			Otherwise multiply the current entry in the matrix by 10 and add the current digit to the entry.
				This is because the each number gets read one character at a time from left to right, so
				the number 123 gets processed as 0*10 + 1 = 1 -> 1*10 + 2 = 12 -> 12*10 + 3 = 123
		*/
		for (int i = 0; i < fileText.length(); i++) {
			if (fileText[i] < '0' || fileText[i] > '9') {
				col++;
				fileMatrix[row][col] = 0;
			} else {
				fileMatrix[row][col] *= 10;
				fileMatrix[row][col] += (fileText[i] - '0');	// subtract the 0 character's ascii number from the
																// current character's ascii number to get the digit
			}
		}
		
		/*
			Increment to the next row and reset to the first column after a line is done being read.
			If the row after the increment is larger than the size of the matrix, then the matrix
			has been filled and the file must not be read anymore, so break.
		*/
		row++;
		col = 0;
		if (row >= matrixSize) break;
	}
	
	return fileMatrix;	// return the matrix
}

/*
	Calculate the sum between two matrices, and return as a new matrix.
*/
int** sumMatrix(int** matrix1, int** matrix2, const int mSize) {	// mSize = matrixSize
	static const int maxSize = 100;	// the max possible size of the array, given by assignment description
	
	int** newMatrix = new int*[maxSize];	// initialize the new matrix
	
	/*
		Iterate through the rows and columns of the two matrices and sum the numbers between
		the matrices at each position.
	*/
	for (int row = 0; row < mSize; row++) {
		newMatrix[row] = new int[maxSize];	// initialize each row of the new matrix
		for (int col = 0; col < mSize; col++) {
			newMatrix[row][col] = matrix1[row][col] + matrix2[row][col];	// assign the current position of the new
																			// matrix to be the sum of the two other matrices
		}
	}
	
	return newMatrix;	// return the new matrix
}

/*
	Calculate the difference between two matrices, and return as a new matrix.
*/
int** diffMatrix(int** matrix1, int** matrix2, const int mSize) {	// mSize = matrixSize
	static const int maxSize = 100;	// the max possible size of the array, given by assignment description
	
	int** newMatrix = new int*[maxSize];	// initialize the new matrix
	
	/*
		Iterate through the rows and columns of the two matrices and calculate the difference
		of the numbers between the matrices at each position.
	*/
	for (int row = 0; row < mSize; row++) {
		newMatrix[row] = new int[maxSize];	// initialize each row of the new matrix
		for (int col = 0; col < mSize; col++) {
			newMatrix[row][col] = matrix1[row][col] - matrix2[row][col];	// assign current position of the new matrix
																			// to be the difference of the other two matrices
		}
	}
	
	return newMatrix;	// return the new matrix
}

/*
	Calculate the product of two matrices, and return as a new matrix
*/
int** multMatrix(int** matrix1, int** matrix2, const int mSize) {	// mSize = matrixSize
	static const int maxSize = 100;	// the max possible size of the array, given by assignment description
	
	int** newMatrix = new int*[maxSize];	// initialize the new matrix
	
	/*
		Perform the dot product between the two matrices and store it in the new matrix. This is done by
		iterating through the rows and columns (first two for loops) of the matrix and performing the dot
		product at that position, using another for loop to iterate through the other matrices and sum together
		the appropriate products.
	*/
	for (int i = 0; i < mSize; i++) {
		newMatrix[i] = new int[maxSize];	// initialize each row of the new matrix
		for (int j = 0; j < mSize; j++) {
			newMatrix[i][j] = 0;			// initialize the current position of the new matrix to 0
			for (int k = 0; k < mSize; k++) {
				newMatrix[i][j] += matrix1[i][k] * matrix2[k][j];	// dot product
			}
		}
	}
	
	return newMatrix;	// return the new matrix
}

/*
	Print the contents of a matrix.
	
	Done by iterating through the matrix and printing the number at each position, with a space inbetween
	and a new line at the end of each row.
*/
void printMatrix(int** matrix, const int mSize) {	// mSize = matrixSize
    for (int row = 0; row < mSize; row++) {
		for (int col = 0; col < mSize; col++) {
			std::cout << matrix[row][col] << " ";
		}
		std::cout << std::endl;
	}
}