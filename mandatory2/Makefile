serial_flags = gcc -std=c11 -O3 -Wall
mpi_flags = mpicc -std=c11 -O3 -Wall

serial = serial.exe
mpi = mpi.exe

all: ${serial} ${mpi}

${mpi}: mpi_main.c
	${mpi_flags} mpi_main.c -o ${mpi}

${serial}: serial_main.c
	${serial_flags} serial_main.c -o ${serial}	
