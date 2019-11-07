#include "grader.cpp"

void pianifica(int R, int* A, int* B, int* T) {
    int kmin = 0;
    int kmax = 1e9;
    while (kmin + 1 < kmax) {
        int k = (kmin + kmax) / 2;
        bool buono = true;
        int libero = 0;
        for (int i = 0; i < R; i++) {
            if (libero < A[i])
                libero = A[i] + k;
            else if (libero <= B[i])
                libero += k;
            else {
                buono = false;
                break;
            }
        }
        if (buono)
            kmin = k;
        else
            kmax = k;
    }
    int k = kmin;
    int libero = 0;
    for (int i = 0; i < R; i++) {
        if (libero < A[i]) {
            T[i] = A[i];
            libero = A[i] + k;
        } else {
            T[i] = libero;
            libero += k;
        }
    }
}