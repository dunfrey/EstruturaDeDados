#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void selection_sort(int * array, int tam_arr){
    
    for(int i = 0; i < tam_arr - 1; i++)
    {
        int min_idx = i;
        for(int j = i+1 ; j < tam_arr; j++)
        {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }

        int temp = array[min_idx];
        array[min_idx] = array[i];
        array[i] = temp;     
    }
}

void insertion_sort(int * array, int tam_arr){

    for(int i = 1; i < tam_arr; i++)
    {
        int min_atual   = array[i];
        int j = i -1;

        while (j >= 0 && min_atual < array[j]) {
            array[j+1] = array[j];
            j--;
        }

        array[j+1] = min_atual;
    }
}

void print_ord_num(int array[], int tam_arr){
    printf("NUMEROS ORDENADOS\n");
    for(int loop = 0; loop < tam_arr; loop++)
        printf("%d ", array[loop]);
    printf("\n\n");
}

char dir[] = "./instancias-num/";
void solve_name_file(char * file){
    strcat(dir, file);
}

int count_inst(){
    FILE *stream;
	char *line = NULL;
	size_t len = 0, read;
    int i = -1;

    stream = fopen (dir , "r");
    if (dir == NULL) perror ("Error opening file");
    else {
        while ((read = getline(&line, &len, stream)) != -1) {
            i++;
        }
    }

	free(line);
	fclose(stream);
    return i;
}

void copy_inst(int * array){
    FILE *stream;
	char *line = NULL;
	size_t len = 0, read;
    int i = -1;

    stream = fopen (dir , "r");
    if (dir == NULL) perror ("Error opening file");
    else {
        while ((read = getline(&line, &len, stream)) != -1) {
            i++;
            array[i] = (int) atoi(line);
        }
    }

	free(line);
	fclose(stream);
}

int * embaralhar(int * array, int vetSize){
	for (int i = 0; i < vetSize; i++)
	{
		int r = rand() % vetSize;

		int temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
    return array;
}

void ordenar(int * array){
    clock_t t1, t2, t3;
    t1 = clock();

    int tam_array = count_inst();
    
    selection_sort(array, tam_array);
    t2 = clock() - t1;

    insertion_sort(embaralhar(array, tam_array),tam_array);
    t3 = clock() - t2;

    printf("\nselection_sort() levou %f segundos para ordenar", ((double)t2)/CLOCKS_PER_SEC);
    printf("\ninsertion_sort() levou %f segundos para ordenar\n\n", ((double)t3)/CLOCKS_PER_SEC);
    //print_ord_num(array, count_inst());
}

void file_process(char * file){
    
    solve_name_file(file);   
    int array[count_inst()];
    copy_inst(array);
    ordenar(array);
    
}

void without_file_process(int argc, char **argv){
    int tam_arr = (int)argc - 1;
    int array[tam_arr];
    for(int pos_arr = 0; pos_arr < tam_arr; pos_arr++)
    {
        array[pos_arr] = atoi(argv[pos_arr+1]);
    }
    
    ordenar(array);
}

int main( int argc, char **argv ){
    if(argc == 2){
        file_process(argv[1]);
    } 
    else if(argc > 2){
        without_file_process(argc, argv);      
    } else {
        puts("ERRO NA ENTRADA");
    }

    return 0;
}