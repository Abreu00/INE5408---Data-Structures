#ifndef DEALLOC_MATRIX_HPP
#define DEALLOC_MATRIX_HPP

void deallocMatrix(int**& matrix, int lines, int cols) {
    for (int i = 0; i < lines; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

#endif