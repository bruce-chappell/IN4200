To compile the programs run the Makefile. This will produce the following executables:

serial.exe
mpi.exe

These may be run with the following commands respectively:

./serial.exe <preset/custom>
mpirun -np <num_threads> ./mpi.exe <preset/custom>

If you choose "preset", the programs will run with a hardcoded 10x10 matrix.
If you choose "custom", you will be prompted to enter a row length (int) and
column length (int). The program will then create a matrix of random integers from 0-9
to populate the [row x column] matrix. These programs require the c11 standard
and MPI. 
