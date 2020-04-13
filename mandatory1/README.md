# IN4200 Mandatory Assignment 1 #
## File Structure ##
* src - source files
  * tools.c - usefull matrix operations
  * helper_functions.h - header for tools functions
  -----------------------
  * read_graph_from_file1.c - Full matrix reading function
  * read_graph_from-file2.c - CRS reading function
  * count_mutual_links1.c - Full matrix link counting functions
  * count_mutual_links2.c - CRS link counting functions
  * top_n_webpages.c - Top web page counting functions
  * webgraph_functions.h - Header for the above functions
  ----------------------
  * test_functions.c - Unit test functions
  * test_functions.h - Header for unit test functions
  ---------------------
  * main.c - Main file that runs counting and timing operations
  * Makefile - Make file that produces final_out.exe
  * plot.py - Hard coded plotting function to illustrate results
  ---------------------
  * data - folder containing data files
## Compiling and Running ##
* COMPILING- run the command 'make'. This will generate the executable final_out.exe
  * The Makefile specifies gcc-9 and OpenMP is needed for the parallel functions
* RUNNING- ./final_out.exe 'parallel or serial' 'full_matrix or CRS' 'number of threads'
  * In the quote statements above you pick either parallel or serial, full_matrix or CRS, and an int (num threads) for arguements. I couldn't figure out command line syntax for markdown
* you can change the data file and the desired N for top_n_webpages in the main file

  
  
