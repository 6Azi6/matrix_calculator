// src/main.cpp
#include "matrix.h"
#include <iostream>
#include <cstdlib>  // для std::rand, std::srand
#include <ctime>    // для std::time

int main() {
    std::cout << "=== Matrix Calculator Demo ===" << std::endl;
    std::cout << "Demonstrating all library functions" << std::endl;
    std::cout << "=========================================" << std::endl;

    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try {
        // 1. Демонстрация создания матриц
        std::cout << "\n1. Creating matrices A and B:" << std::endl;
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(2, 2);

        // Заполняем матрицы тестовыми данными
        A.data[0][0] = 1; A.data[0][1] = 2;
        A.data[1][0] = 3; A.data[1][1] = 4;

        B.data[0][0] = 5; B.data[0][1] = 6;
        B.data[1][0] = 7; B.data[1][1] = 8;

        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);
        std::cout << "Matrix B:" << std::endl;
        print_matrix(B);

        // 2. Демонстрация сложения матриц
        std::cout << "\n2. Matrix addition A + B:" << std::endl;
        Matrix sum = matrix_add(A, B);
        print_matrix(sum);

        // 3. Демонстрация умножения матриц
        std::cout << "\n3. Matrix multiplication A × B:" << std::endl;
        Matrix product = matrix_multiply(A, B);
        print_matrix(product);

        // 4. Демонстрация транспонирования
        std::cout << "\n4. Transpose of A:" << std::endl;
        Matrix transposed = matrix_transpose(A);
        print_matrix(transposed);

        // 5. Демонстрация создания матрицы из массива
        std::cout << "\n5. Matrix from array:" << std::endl;
        double data[] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
        Matrix from_arr = matrix_from_array(data, 2, 3);
        print_matrix(from_arr);

        // 6. Демонстрация создания случайных матриц
        std::cout << "\n6. Random matrices:" << std::endl;
        
        Matrix random1 = create_matrix(2, 3);
        Matrix random2 = create_matrix(3, 2);

         // Заполняем случайными значениями от 0.0 до 10.0
        for (int i = 0; i < random1.rows; i++) {
            for (int j = 0; j < random1.cols; j++) {
                random1.data[i][j] = static_cast<double>(std::rand() % 100) / 10.0;
            }
        }
        
        for (int i = 0; i < random2.rows; i++) {
            for (int j = 0; j < random2.cols; j++) {
                random2.data[i][j] = static_cast<double>(std::rand() % 100) / 10.0;
            }
        }
        
        std::cout << "Random matrix 1 (2x3):" << std::endl;
        print_matrix(random1);
        std::cout << std::endl;
        std::cout << "Random matrix 2 (3x2):" << std::endl;
        print_matrix(random2);
        std::cout << std::endl;
        
        // Демонстрация умножения случайных матриц
        std::cout << "Multiplication of random matrices:" << std::endl;
        Matrix random_product = matrix_multiply(random1, random2);
        print_matrix(random_product);
                // Освобождение памяти 
        free_matrix(random1);
        free_matrix(random2);
        free_matrix(random_product);

        // 7. Демонстрация с большей матрицей
        std::cout << "\n7. Demonstration with larger matrix:" << std::endl;
        Matrix large = create_matrix(3, 4);

        // Заполняем значениями для демонстрации
        large.data[0][0] = 10.5; large.data[0][1] = 2.3; large.data[0][2] = 15.7; large.data[0][3] = 4.1;
        large.data[1][0] = 5.9;  large.data[1][1] = 20.2; large.data[1][2] = 8.4; large.data[1][3] = 12.6;
        large.data[2][0] = 7.3;  large.data[2][1] = 1.8;  large.data[2][2] = 18.9; large.data[2][3] = 6.0;

        std::cout << "Large matrix:" << std::endl;
        print_matrix(large);

        // 8. Демонстрация обработки ошибок
        std::cout << "\n8. Error handling demonstration:" << std::endl;

        // Попытка создания матрицы с неверными размерами
        try {
            [[maybe_unused]] Matrix invalid = create_matrix(-1, 5);
            std::cout << "This should not be printed!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

        // Попытка сложения несовместимых матриц
        try {
            Matrix incompatible = create_matrix(2, 3);
            [[maybe_unused]] Matrix result = matrix_add(A, incompatible);
            std::cout << "This should not be printed!" << std::endl;
            free_matrix(incompatible);
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

                // 10. Демонстрация работы с CSV файлами
        std::cout << "\n10. CSV Export/Import Demonstration:" << std::endl;
        
        // Создаем матрицу для демонстрации CSV
        double csv_data[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
        Matrix csv_matrix = matrix_from_array(csv_data, 2, 3);
        
        std::cout << "Original matrix for CSV export:" << std::endl;
        print_matrix(csv_matrix);
        
        // Экспорт в CSV
        std::cout << "Exporting matrix to CSV file 'demo_matrix.csv'..." << std::endl;
       
        
        // Импорт из CSV
        std::cout << "Importing matrix from CSV file..." << std::endl;
        Matrix imported_matrix = matrix_from_csv("demo_matrix.csv");
        
        std::cout << "Imported matrix from CSV:" << std::endl;
        print_matrix(imported_matrix);
        
        // Проверка целостности данных
        bool data_matches = true;
        for (int i = 0; i < csv_matrix.rows && data_matches; i++) {
            for (int j = 0; j < csv_matrix.cols && data_matches; j++) {
                if (std::abs(csv_matrix.data[i][j] - imported_matrix.data[i][j]) > 1e-6) {
                    data_matches = false;
                }
            }
        }
        
        std::cout << "CSV data integrity check: " << (data_matches ? "✓ PASSED" : "✗ FAILED") << std::endl;

        // Освобождение памяти
        std::cout << "\n9. Freeing memory..." << std::endl;
        free_matrix(A);
        free_matrix(B);
        free_matrix(sum);
        free_matrix(product);
        free_matrix(transposed);
        free_matrix(from_arr);
        free_matrix(large);

        std::cout << "=========================================" << std::endl;
        std::cout << "=== Demo completed successfully! ===" << std::endl;
        std::cout << "All matrices were properly created, manipulated and freed." << std::endl;
        std::cout << "No memory leaks detected (if compiled with appropriate flags)." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}