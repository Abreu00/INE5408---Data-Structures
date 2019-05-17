#ifndef DEALOC_MATRIX_HPP
#define DEALOC_MATRIX_HPP

void dealocMatrix(int**& matrix, int lines, int cols) {
    for (int i = 0; i < lines; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

#endif