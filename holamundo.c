#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size, longitud;
	char equipo[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(equipo, &longitud);

	printf("Soy el core nro. %d de %d en %s\n", rank, size, equipo);

	MPI_Finalize();
	return 0;
}
