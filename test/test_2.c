#include <stdio.h>

void swap(int **a, int **b);

int main() {
    int x = 1;
    int y = 2;
    int *px = &x;
    int *py = &y;

    printf("Before swap: x = %i, y = %i\n", x, y);

    swap(&px, &py);

    printf("After swap: x = %i, y = %i\n", x, y);
}

void swap(int **a, int **b) {
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}