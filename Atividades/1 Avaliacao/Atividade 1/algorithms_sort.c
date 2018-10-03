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

    for(int j = 1; j < tam_arr; j++)
    {
        int chave = array[j];
        int i = j-1;

        while (i >= 0 && array[i] > chave) {
            array[i+1] = array[i];
            i--;
        }

        array[i+1] = chave;
    }
}

void print_ord_num(int array[], int tam_arr){
    printf("NUMEROS ORDENADOS\n");
    for(int loop = 0; loop < tam_arr; loop++)
        printf("%d ", array[loop]);
    printf("\n\n");
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

void ordenar(int * array, int tam_array){
    clock_t t1, t2, t3;
    t1 = clock();
    
    insertion_sort(array,tam_array);
    print_ord_num(array, tam_array);
    t2 = clock() - t1;
    printf("\ninsertion_sort() levou %f segundos para ordenar\n", ((double)t2)/CLOCKS_PER_SEC);

    printf("\n\n\n-----------------------------------------------\n\n\n");

    selection_sort(embaralhar(array, tam_array), tam_array);
    print_ord_num(array, tam_array);
    t3 = clock() - t2;
    printf("\nselection_sort() levou %f segundos para ordenar\n", ((double)t3)/CLOCKS_PER_SEC);

}

char dir[] = "./instancias-num/";
void name_file(char * file){
    strcat(dir, file);
}

void instances(){
    FILE *stream;
	char *line = NULL;
	size_t len = 0, read;
    int i = 0;

    stream = fopen (dir , "r");
    
    if (dir == NULL){
        int array[1];
    }
    else {
        read = getline(&line, &len, stream);
        int k_inst = atoi(line);
        int array[k_inst];
        while ((read = getline(&line, &len, stream)) != -1) {
            array[i] = atoi(line);
            i++;
        }
        //printf("%d",i);
        ordenar(array, i);
    }

    free(line);
    fclose(stream);

}

void file_process(char * file){
    name_file(file);
    instances();
}

int main( int argc, char **argv ){
    if(argc == 2){
        file_process(argv[1]);
    } else {
        puts("ERRO NA ENTRADA");
    }

    return 0;
}