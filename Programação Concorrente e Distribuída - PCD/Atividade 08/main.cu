#include <stdio.h>

#define TAM 1.0
#define DX 0.00001
#define DT 0.000001
#define T  0.01
#define KAPPA 0.000045
#define N (long int)(TAM/DX)
#define CONSTANT KAPPA * DT / (DX*DX)

#define THREADS_PER_BLOCK 512
#define BLOCK_SIZE 2

__global__ void calculator(double *a, double *b);

void change_context(double **a, double **b);

int main() {
  long int i, maxloc, size = (N + 1) * sizeof(double);;
  double *d_a, *d_b, x = 0, t = 0.;
  cudaMalloc((void **) &d_a, size);
  cudaMalloc((void **) &d_b, size);
  double *a = (double *) malloc(size);
  double *b = (double *) malloc(size);

  printf("Início: qtde = %ld, dt = %g, dx = %g, dx² = %g, kappa = %f, const = %f\n", (N + 1), DT, DX, DX * DX, KAPPA, KAPPA * DT / (DX * DX));
  printf("Iterações previstas: %g\n", T / DT);

  for (i = 0; i < N + 1; i++) {
    if (x <= 0.5) {
      a[i] = 200 * x;
    } else {
      a[i] = 200 * (1. - x);
    }
    x += DX;
  }

  printf("dx = %g, x = %g, (x-dx) = %g\n", DX, x, x - DX);
  printf("prev[0,1] = %g, %g\n", a[0], a[1]);
  printf("prev[n-1,n] = %g, %g\n", a[N - 1], a[N]);

  while (t < T) {
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    calculator<<< ((N - 1) + (THREADS_PER_BLOCK - 1)) / THREADS_PER_BLOCK, THREADS_PER_BLOCK >>>(d_a, d_b);
    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    b[0] = b[N] = 0.;
    change_context(&a, &b);
    t += DT;
  }

  maxloc = 0;
  for (i = 1; i < N + 1; i++) if (b[i] > b[maxloc]) maxloc = i;
  printf("Maior valor u[%ld] = %g\n", maxloc, b[maxloc]);
  cudaFree(d_a);
  cudaFree(d_b);
  return 0;
}

__global__ void calculator(double *a, double *b) {
  int i = (blockIdx.x * blockDim.x + threadIdx.x) + 1;
  b[i] = a[i] + CONSTANT * (a[i - 1] - 2 * a[i] + a[i + 1]);
}

void change_context(double **a, double **b) {
  double *temp;
  temp = *b;
  *b = *a;
  *a = temp;
}
