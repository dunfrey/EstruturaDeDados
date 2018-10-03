#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>

using namespace std;

void max_heapify(int array[], int n, int i)
{
    int maior = i;
    int fi_esq = i*2 + 1;
    int fi_dir = i*2 + 2;

    if(fi_esq < n && array[fi_esq] > array[maior])
        maior = fi_esq;
    if(fi_dir < n && array[fi_dir] > array[maior])
        maior = fi_dir;

    if (maior != i){
        swap(array[i], array[maior]);
        max_heapify(array, n, maior);
    } 
}

void heapSort(int array[], int tam_arr)
{
    for(int i = tam_arr/2 ; i >= 0 ; i--)
        max_heapify(array, tam_arr, i);

    for(int i = tam_arr ; i >= 0 ; i--)
    {
        swap(array[0], array[i]);
        max_heapify(array, i, 0);
    }   
}

//----------------------------------------

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
    
    heapSort(array,tam_array-1);
    print_ord_num(array, tam_array);
    t2 = clock() - t1;
    //printf("\ncounting_sort() levou %f segundos para ordenar\n", ((double)t2)/CLOCKS_PER_SEC);

    //printf("\n\n\n-----------------------------------------------\n\n\n");

    //radix_sort(embaralhar(array, tam_array), tam_array);
    //print_ord_num(array, tam_array);
    t3 = clock() - t2;
    //printf("\nradix_sort() levou %f segundos para ordenar\n", ((double)t3)/CLOCKS_PER_SEC);

}

char dir[] = "../instancias-num/";
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

void without_file_process(int argc, char **argv){
    int tam_arr = (int)argc - 1;
    int array[tam_arr];
    for(int pos_arr = 0; pos_arr < tam_arr; pos_arr++)
    {
        array[pos_arr] = atoi(argv[pos_arr+1]);
    }
    
    ordenar(array, tam_arr);
}

int main( int argc, char **argv ){
    if(argc == 2){
        file_process(argv[1]);
    }
    else if(argc > 2){
        without_file_process(argc, argv); 
    }
    else {
        puts("ERRO NA ENTRADA");
    }

    return 0;
}
