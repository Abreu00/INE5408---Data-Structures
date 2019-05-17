#include "Image.h"
#include "linked_queue.hpp"
#include "dealloc_matrix.hpp"

using namespace structures;

int** create_null_matrix(int height, int width);
void neighbors(int x, int y, LinkedQueue<int> &queue, Image &img, int** &aux, int label);

int count_related(Image img) {
    int** data_matrix = img.data;
    int height = img.height; 
    int width = img.width;
    int** aux_matrix = create_null_matrix(height, width);
    LinkedQueue<int> queue;

    int label = 0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (data_matrix[i][j] == 1 && aux_matrix[i][j] == 0) {
                ++label;
                queue.enqueue(j);
                queue.enqueue(i);
                aux_matrix[i][j] = label;
            }
            while (!queue.empty()) {
                int x = queue.dequeue(); // Matrix col cord
                int y = queue.dequeue(); // Matrix line cord
                neighbors(x, y, queue, img, aux_matrix, label);
            }
        }  
    }
    deallocMatrix(aux_matrix, height, width);
    return label;
    
}


int** create_null_matrix(int height, int width) {
    int** matrix = new int*[height];
    for (int i = 0; i < height; ++i) {
        matrix[i] = new int[width];
        for (int j = 0; j < width; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void neighbors(int x, int y, LinkedQueue<int> &queue, Image &img, int** &aux, int label) {
    //! Labels the four neighbors of (x, y) on the auxiliary matrix
    //! Inserts neighbors on the queue
    int** data = img.data;
    int height = img.height;
    int width = img.width;

    if (x - 1 >= 0 && data[y][x - 1] == 1 && aux[y][x - 1] == 0) {
        queue.enqueue(x - 1);
        queue.enqueue(y);
        aux[y][x - 1] = label;
    }
    if (x + 1 < width && data[y][x + 1] == 1 && aux[y][x + 1] == 0) {
        queue.enqueue(x + 1);
        queue.enqueue(y);
        aux[y][x + 1] = label;
    }
    if (y - 1 >= 0 && data[y - 1][x] == 1 && aux[y - 1][x] == 0) {
        queue.enqueue(x);
        queue.enqueue(y - 1);
        aux[y - 1][x] = label;
    }
    if (y + 1 < height && data[y + 1][x] == 1 && aux[y + 1][x] == 0) {
        queue.enqueue(x);
        queue.enqueue(y + 1);
        aux[y + 1][x] = label;
    }
}