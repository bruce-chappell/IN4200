CC = gcc-9
CFLAGS = -Wall -fopenmp -g
OBJS = tools.o test_functions.o top_n_webpages.o count_mutual_links2.o count_mutual_links1.o $\
read_graph_from_file2.o read_graph_from_file1.o main.o
PROG = final_out.exe

all:$(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

tools.o: helper_functions.h
read_graph_from_file1.o: helper_functions.h webgraph_functions.h
read_graph_from_file2.o: helper_functions.h webgraph_functions.h
count_mutual_links1.o: helper_functions.h webgraph_functions.h
count_mutual_links2.o: helper_functions.h webgraph_functions.h
top_n_webpages.o: helper_functions.h webgraph_functions.h
test_functions.o: helper_functions.h webgraph_functions.h test_functions.h
main.o: helper_functions.h webgraph_functions.h test_functions.h

clean:
	rm -f *~ *.o $(PROG)
