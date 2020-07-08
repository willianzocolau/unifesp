#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <sys/time.h>

#define tam 100000000
#define u 2.0

int main(int argc, char **argv) {

    int numProc, esteProc, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &esteProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    double local_sum = 0, global_sum, passo = (u - 1) / (double) tam, x;
    double qtde = floor((float) tam / numProc);

    struct timeval inicio, final;
    int tmili;

    gettimeofday(&inicio, NULL);

    for (i = qtde * esteProc; i < qtde * (esteProc + 1); i++) {
        x = 1 + i * passo;
        local_sum = local_sum + 0.5 * (1 / x + 1 / (x + passo));
    }

    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

    if (esteProc == 0) {
        printf("ln %f = %20.15f em %d ms\n", u, passo * global_sum, tmili);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}
