// src/matrix.h
#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура, представляющая матрицу чисел double.
 *
 * Структура содержит данные матрицы и её размерности.
 * Все операции библиотеки работают с этой структурой.
 */
typedef struct {
    double** data;  ///< Указатель на двумерный массив данных матрицы
    int rows;       ///< Количество строк в матрице
    int cols;       ///< Количество столбцов в матрице
} Matrix;

/**
 * @brief Создает новую матрицу с заданными размерами.
 *
 * @param rows Количество строк (должно быть > 0)
 * @param cols Количество столбцов (должно быть > 0)
 * @return Matrix Созданная матрица с нулевыми элементами
 * @throws std::invalid_argument Если rows или cols <= 0
 * @throws std::bad_alloc Если не удалось выделить память
 *
 * @note Память должна быть освобождена с помощью free_matrix()
 * @warning Не забывайте освобождать память после использования!
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, занятую матрицей.
 *
 * @param m Матрица, память которой нужно освободить
 *
 * @note Безопасна для вызова с уже освобожденной матрицей
 * @warning После вызова этой функции матрица становится невалидной
 */
void free_matrix(Matrix m);

/**
 * @brief Выполняет сложение двух матриц.
 *
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return Matrix Результат сложения a + b
 * @throws std::invalid_argument Если размеры матриц не совпадают
 *
 * @note Сложность: O(rows * cols)
 * @example
 * Matrix A = create_matrix(2, 2);
 * Matrix B = create_matrix(2, 2);
 * Matrix C = matrix_add(A, B);
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Выполняет умножение двух матриц.
 *
 * @param a Первая матрица (размер M×N)
 * @param b Вторая матрица (размер N×K)
 * @return Matrix Результат умножения a × b (размер M×K)
 * @throws std::invalid_argument Если количество столбцов a не равно количеству строк b
 *
 * @note Сложность: O(M * N * K)
 * @warning Умножение матриц не коммутативно!
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Транспонирует матрицу.
 *
 * @param m Исходная матрица
 * @return Matrix Транспонированная матрица
 *
 * @note Размер результата: cols × rows
 * @example
 * Исходная: 3×2, Результат: 2×3
 */
Matrix matrix_transpose(Matrix m);

/**
 * @brief Выводит матрицу в консоль в форматированном виде.
 *
 * @param m Матрица для вывода
 *
 * @note Для больших матриц показывает только первые 10 строк и 8 столбцов
 * @warning Вывод использует std::cout
 */
void print_matrix(Matrix m);

/**
 * @brief Создает матрицу из одномерного массива.
 *
 * @param data Указатель на массив данных
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Matrix Созданная матрица
 * @throws std::invalid_argument Если data == nullptr или размеры некорректны
 *
 * @note Данные копируются из массива в матрицу
 * @example
 * double arr[] = {1, 2, 3, 4, 5, 6};
 * Matrix m = matrix_from_array(arr, 2, 3);
 * // Результат: [[1, 2, 3], [4, 5, 6]]
 */
Matrix matrix_from_array(double* data, int rows, int cols);

void matrix_to_csv(Matrix m, const char* filename);
Matrix matrix_from_csv(const char* filename);

#endif // MATRIX_H