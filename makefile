############################# Makefile ##########################
compile: 
	gcc -o selection_sort selection_sort.c
	gcc -o insertion_sort insertion_sort.c
clean: 
	rm -rf selection_sort
	rm -rf insertion_sort
exec:
	./selection_sort 3 6 4 8 0 1 10 22 13 45 23 21
	./insertion_sort 2 4 3 61 9 5 1 22 13 45 23 21