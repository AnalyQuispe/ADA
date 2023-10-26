#include <iostream>
using namespace std;

// Definir estructura para representar la matriz 4x4
struct Matrix {
    int m[4][4];
};

Matrix add(Matrix A, Matrix B) {
    Matrix C;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            C.m[i][j] = A.m[i][j] + B.m[i][j];
    return C;
}

Matrix subtract(Matrix A, Matrix B) {
    Matrix C;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            C.m[i][j] = A.m[i][j] - B.m[i][j];
    return C;
}

Matrix strassen(Matrix A, Matrix B) {
    // Base case: 2x2 matrix
    if (sizeof(A.m)/sizeof(A.m[0]) == 2) {
        // Código simplificado para matrices 2x2, similar al que proporcionaste originalmente
        Matrix C;
        int m1 = (A.m[0][0] + A.m[1][1]) * (B.m[0][0] + B.m[1][1]);
        int m2 = (A.m[1][0] + A.m[1][1]) * B.m[0][0];
        int m3 = A.m[0][0] * (B.m[0][1] - B.m[1][1]);
        int m4 = A.m[1][1] * (B.m[1][0] - B.m[0][0]);
        int m5 = (A.m[0][0] + A.m[0][1]) * B.m[1][1];
        int m6 = (A.m[1][0] - A.m[0][0]) * (B.m[0][0] + B.m[0][1]);
        int m7 = (A.m[0][1] - A.m[1][1]) * (B.m[1][0] + B.m[1][1]);

        C.m[0][0] = m1 + m4 - m5 + m7;
        C.m[0][1] = m3 + m5;
        C.m[1][0] = m2 + m4;
        C.m[1][1] = m1 - m2 + m3 + m6;

        return C;
    }

    // Descomponer cada matriz 4x4 en 4 submatrices 2x2
    // (Esto se puede hacer de manera más eficiente, pero por simplicidad lo haré manualmente)

    Matrix A11 = {{ {A.m[0][0], A.m[0][1]}, {A.m[1][0], A.m[1][1]} }};
    Matrix A12 = {{ {A.m[0][2], A.m[0][3]}, {A.m[1][2], A.m[1][3]} }};
    Matrix A21 = {{ {A.m[2][0], A.m[2][1]}, {A.m[3][0], A.m[3][1]} }};
    Matrix A22 = {{ {A.m[2][2], A.m[2][3]}, {A.m[3][2], A.m[3][3]} }};

    Matrix B11 = {{ {B.m[0][0], B.m[0][1]}, {B.m[1][0], B.m[1][1]} }};
    Matrix B12 = {{ {B.m[0][2], B.m[0][3]}, {B.m[1][2], B.m[1][3]} }};
    Matrix B21 = {{ {B.m[2][0], B.m[2][1]}, {B.m[3][0], B.m[3][1]} }};
    Matrix B22 = {{ {B.m[2][2], B.m[2][3]}, {B.m[3][2], B.m[3][3]} }};

    // Recursivamente multiplicar submatrices 2x2
    Matrix C11 = add(strassen(A11, B11), strassen(A12, B21));
    Matrix C12 = add(strassen(A11, B12), strassen(A12, B22));
    Matrix C21 = add(strassen(A21, B11), strassen(A22, B21));
    Matrix C22 = add(strassen(A21, B12), strassen(A22, B22));

    // Construir matriz resultante 4x4 a partir de los resultados 2x2
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C.m[i][j] = C11.m[i][j];
            C.m[i][j+2] = C12.m[i][j];
            C.m[i+2][j] = C21.m[i][j];
            C.m[i+2][j+2] = C22.m[i][j];
        }
    }
    return C;
}

void printMatrix(Matrix M) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << M.m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix A = {{{1, 3, 2, 4}, {5, 7, 6, 8}, {1, 3, 2, 4}, {5, 7, 6, 8}}};
    Matrix B = {{{8, 4, 7, 3}, {6, 2, 5, 1}, {8, 4, 7, 3}, {6, 2, 5, 1}}};
    Matrix C = strassen(A, B);
    cout << "Resultado de la multiplicación:" << endl;
    printMatrix(C);
    return 0;
}
