%%writefile exp14.cu
#include <stdio.h>
#include <cuda_runtime.h>

#define N 4  // 4x4 Matrices for clear output demonstration

// CUDA Kernel for Matrix Multiplication: C = A * B
__global__ void matrixMul(int *A, int *B, int *C, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < width && col < width) {
        int sum = 0;
        for (int k = 0; k < width; k++) {
            sum += A[row * width + k] * B[k * width + col];
        }
        C[row * width + col] = sum;
    }
}

int main() {
    int size = N * N * sizeof(int);

    // Host matrices
    int h_A[N * N], h_B[N * N], h_C[N * N];

    // Initialize matrix A and B with simple values
    for (int i = 0; i < N * N; i++) {
        h_A[i] = (i % N) + 1;       // e.g. 1, 2, 3, 4 per row
        h_B[i] = (i / N == i % N) ? 2 : 1; // 2 on diagonal, 1 elsewhere
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

    // Device pointers
    int *d_A, *d_B, *d_C;

    // 1. Allocate device memory
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // 2. Copy host data to GPU device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 3. Define 2D thread block and grid
    dim3 threadsPerBlock(2, 2);
    dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x,
                       (N + threadsPerBlock.y - 1) / threadsPerBlock.y);

    // 4. Launch CUDA matrix multiplication kernel
    matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // Wait for GPU execution to complete
    cudaDeviceSynchronize();

    // 5. Copy result from GPU to Host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // 6. Display Result Matrix C
    printf("\n--- Result Matrix C = A * B (Computed on GPU) ---\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", h_C[i * N + j]);
        }
        printf("\n");
    }

    // 7. Free GPU memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    printf("\nCUDA Matrix Multiplication completed successfully.\n");
    return 0;
}



!nvcc exp14.cu -o exp14
!./exp14
