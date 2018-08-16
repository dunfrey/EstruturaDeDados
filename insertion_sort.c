#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int array[], int tam_arr){
    
    if(sizeof(array) > 1){

        for(int i = 0; i < tam_arr; i++)
        {
            int min_atual   = array[i];
            
            for(int j = i+1; j < tam_arr; j++)
            {
                if(min_atual > array[j]){
                    min_atual = array[j];
                    array[j]  = array[i];
                    array[i]  = min_atual;
                }
            }
        }

    }
}

void print_ord_num(int array[], int tam_arr){
    printf("NUMEROS ORDENADOS\n");
    for(int loop = 0; loop < tam_arr; loop++)
        printf("%d ", array[loop]);
    printf("\n\n");
}

int main( int argc, char **argv ){
    if(argc > 1){
        int tam_arr = (int)argc - 1;
        int array[tam_arr];
        for(int pos_arr = 0; pos_arr < tam_arr; pos_arr++)
        {
            array[pos_arr] = atoi(argv[pos_arr+1]);
        }
        
        clock_t t;
        t = clock();
        //--------------------
        insertion_sort(array, tam_arr);
        //--------------------
        t = clock() - t;
        printf("\ninsertion_sort() levou %f segundos para ordenar \n\n", ((double)t)/CLOCKS_PER_SEC);
        
        print_ord_num(array, tam_arr);
        
    } else {
        printf("entre com no minimo um numero a ser ordenado\n");
    }

    return 0;
}