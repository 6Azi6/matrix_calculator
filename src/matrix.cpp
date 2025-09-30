// src/matrix.cpp
#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>  // для std::rand, std::srand
#include <ctime>    // для std::time
#include <vector>
#include <cstdio>
#include <cstring>

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        if (mat.data[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }

        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }

    return mat;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }

    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
        }
    }

    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must be equal for addition");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Number of columns in A must equal number of rows in B for multiplication");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }

    return result;
}

Matrix matrix_transpose(Matrix m) {
    Matrix result = create_matrix(m.cols, m.rows);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }

    return result;
}

void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < m.rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(6) << m.data[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr) {
        throw std::invalid_argument("Data array cannot be null");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    Matrix result = create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i * cols + j];
        }
    }

    return result;
}

void matrix_to_csv(Matrix m, const char* filename) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        throw std::invalid_argument("Cannot export empty matrix to CSV");
    }
    
    FILE* file = fopen(filename, "w");
    if (file == nullptr) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            fprintf(file, "%.6f", m.data[i][j]);
            if (j < m.cols - 1) fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

Matrix matrix_from_csv(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == nullptr) {
        throw std::runtime_error("Cannot open file for reading");
    }
    
    std::vector<std::vector<double>> temp_data;
    char line[1024];
    int cols = -1;
    
    while (fgets(line, sizeof(line), file)) {
        std::vector<double> row;
        char* token = strtok(line, ",\n");
        
        while (token != nullptr) {
            row.push_back(std::atof(token));
            token = strtok(nullptr, ",\n");
        }
        
        if (cols == -1) cols = row.size();
        if (!row.empty()) temp_data.push_back(row);
    }
    
    fclose(file);
    
    Matrix mat = create_matrix(temp_data.size(), cols);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            mat.data[i][j] = temp_data[i][j];
        }
    }
    
    return mat;
}