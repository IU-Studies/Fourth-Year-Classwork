%%writefile exp13.cu
#include <stdio.h>
#include <cuda_runtime.h>

#define N 4

__global__ void matrixAdd(int *A, int *B, int *C, int width) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < width && col < width) {
        int index = row * width + col;
        C[index] = A[index] + B[index];
    }
}

int main() {
    int size = N * N * sizeof(int);
    int h_A[N * N], h_B[N * N], h_C[N * N];

    for (int i = 0; i < N * N; i++) {
        h_A[i] = i + 1;
        h_B[i] = (i + 1) * 10;
    }

    printf("--- Matrix A (%dx%d) ---\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", h_A[i * N + j]);
        }
        printf("\n");
    }

    printf("\n--- Matrix B (%dx%d) ---\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", h_B[i * N + j]);
        }
        printf("\n");
    }

    int *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(2, 2);
    dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x,
                       (N + threadsPerBlock.y - 1) / threadsPerBlock.y);

    matrixAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\n--- Result Matrix C = A + B (Computed on GPU) ---\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", h_C[i * N + j]);
        }
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    printf("\nCUDA Matrix Addition completed successfully.\n");
    return 0;
}





!nvcc exp13.cu -o exp13
!./exp13
