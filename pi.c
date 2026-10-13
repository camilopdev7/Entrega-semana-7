#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	long long n = 9000000000LL;
	double suma = 0.0, total = 0.0;
	double inicio, tiempo, tiempo_max;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (argc> 1)
		n = atoll(argv[1]);
	if (n <= 0) {
		if (rank == 0)
			printf("Las iteraciones deben ser positivas.\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	inicio = MPI_Wtime();

	for (long long i = rank; i < n; i += size) {
		double signo = (i % 2 == 0) ? 1.0 : -1.0;
		suma += signo / (2.0 * i + 1.0);
	}

	MPI_Reduce(&suma, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	tiempo = MPI_Wtime() - inicio;

	MPI_Reduce(&tiempo, &tiempo_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Procesos: %d\n", size);
		printf("Iteraciones totales: %lld\n", n);
		printf("PI: %.15f\n", 4.0 * total);
		printf("Tiempo: %.6f segundos\n", tiempo_max);
	}
	MPI_Finalize();
	return 0;
}














