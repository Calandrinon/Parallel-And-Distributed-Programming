#include <iostream>
#include <tuple>
#include <vector>
#include <mpi.h>
#define MPI_MATRIX_AS_INTEGER_POINTER 0
#define MPI_MATRIX_ROWS 1
#define MPI_MATRIX_COLUMNS 2
#define MPI_MATRIX_RESULT 3

std::pair<std::pair<int, int>, int*> convertMatrixIntoIntegerPointer(std::vector<std::vector<int>>& matrix) {
    int* matrixAsVector = new int[matrix.size()*matrix[0].size()];
    int rows = matrix.size(), columns = matrix[0].size();
    int position = 0;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            matrixAsVector[position] = matrix[i][j];
            position++;
        }
    }

    return std::make_pair(std::make_pair(rows, columns), matrixAsVector);
}

std::vector<std::vector<int>> convertIntegerPointerIntoMatrix(int* sequenceOfNumbers, int rows, int columns) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns));

    int index = 0;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            matrix[row][column] = sequenceOfNumbers[index];
            index++;
        }
    }

    return matrix;
}


void runMasterProcess() {
    std::vector<std::vector<int>> matrix;
    int number = 0;
    for (int i = 0; i < 3; i++) {
        matrix.emplace_back();
        for (int j = 0; j < 3; j++) {
            number++;
            matrix[i].push_back(number);
        }
    }

    std::pair<std::pair<int, int>, int*> matrixAsIntegerPointer = convertMatrixIntoIntegerPointer(matrix);

    MPI_Send(&matrixAsIntegerPointer.first.first, 1, MPI_INT, 1, MPI_MATRIX_ROWS, MPI_COMM_WORLD);
    MPI_Send(&matrixAsIntegerPointer.first.second, 1, MPI_INT, 1, MPI_MATRIX_COLUMNS, MPI_COMM_WORLD);
    MPI_Send(matrixAsIntegerPointer.second, matrixAsIntegerPointer.first.first * matrixAsIntegerPointer.first.second, MPI_INT, 1, MPI_MATRIX_AS_INTEGER_POINTER, MPI_COMM_WORLD);

    //std::vector<std::vector<int>> convertedMatrix = convertIntegerPointerIntoMatrix(matrixAsIntegerPointer.second, matrixAsIntegerPointer.first.first, matrixAsIntegerPointer.first.second);

    int result;
    MPI_Recv(&result, 1, MPI_INT, 1, MPI_MATRIX_RESULT, MPI_COMM_WORLD, NULL);

    std::cout << "Sum of the matrix: " << result << "\n";

    delete[] matrixAsIntegerPointer.second;
}


void runWorkerProcess() {
    int rows, columns, *matrixAsIntegerPointer;
    MPI_Recv(&rows, 1, MPI_INT, 0, MPI_MATRIX_ROWS, MPI_COMM_WORLD, NULL);
    MPI_Recv(&columns, 1, MPI_INT, 0, MPI_MATRIX_COLUMNS, MPI_COMM_WORLD, NULL);
    matrixAsIntegerPointer = new int[rows*columns];
    MPI_Recv(&matrixAsIntegerPointer[0], rows*columns, MPI_INT, 0, MPI_MATRIX_AS_INTEGER_POINTER, MPI_COMM_WORLD, NULL);

    int sum = 0;
    for (int i = 0; i < rows * columns; i++)
        sum += matrixAsIntegerPointer[i];

    MPI_Send(&sum, 1, MPI_INT, 0, MPI_MATRIX_RESULT, MPI_COMM_WORLD);
}


int main(int argc, char* argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
       runMasterProcess();
    } else {
       runWorkerProcess();
    }

    MPI_Finalize();
    return 0;
}
