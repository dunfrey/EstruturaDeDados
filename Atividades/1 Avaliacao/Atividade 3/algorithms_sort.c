#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int getMaior (int * array, int tam_array){
    int maior_numero = array[0];

    for(int i = 1; i < tam_array; i++)
    {
        if (maior_numero < array[i])
            maior_numero = array[i];
    }

    return maior_numero;
}

int getMenor (int * array, int tam_array){
    int menor_numero = array[0];

    for(int i = 1; i < tam_array; i++)
    {
        if (menor_numero > array[i])
            menor_numero = array[i];
    }

    return menor_numero;
}

void counting_sort(int * array, int tam_array){
    
    //busca o maior numero para ser criado o vetor de contagem
    int vetor_organizado[tam_array];
    int maior_numero = getMaior(array, tam_array);
    int menor_numero = getMenor(array, tam_array);
    if(menor_numero > 0)
        menor_numero = 0;

    //cria o vetor de contagem e seta os valores para 0
    int contador[1 + maior_numero + (-1*menor_numero)];
    memset(contador,0,sizeof(contador));
    int tam_contador = sizeof(contador)/sizeof(int);    

    // FOR 1: faz contagem dos elementos do array
    for(int i = 0; i < tam_array; i++){
        //suponha: array[-3,4,0,4,-1] - contador[0,1,2,3,4,-1,-2,-3]
        if(array[i] >= 0)
            ++contador [ array[i] ];
        if(array[i] < 0) 
            ++contador [ (-1*array[i]) + maior_numero ];
            //++contador[ -(-3) + 4 ] = contador[ 7 ]
    }

    // reposiciona valores de contador -----
    if(menor_numero < 0){
        //      -3 -2 -1  0  1  2  3  4
        // aux:  1  0  1  1  0  0  0  2
        int aux[tam_contador];
        memset(aux,0,sizeof(aux));

        for(int i = 0; i < tam_contador; i++)
        {
            aux[i] = contador[(tam_contador-1)-i];
            if(i >= (-1*menor_numero)){
                aux[i] = contador[i + menor_numero];
            }
        }
        for(int i = 0; i < tam_contador; i++) {
            contador[i] = aux[i];
        }
    }
    //--------------------------------------
    
    // FOR 2: regulariza o contador no vetor de contagem: "i = i + [i-1]"
    for(int i = 1; i < tam_contador ; i++){
        contador[i] += contador[i-1];
    }
    
    // decrementa a posicao de localizacao do valor e insere na posicao no novo vetor organizado
    for(int i = 0; i < tam_array; i++){
        printf("i: %d-", i-1);
        printf("%d\n", contador[i-1]);
        --contador[array[i]];
    /*
        if(menor_numero >= 0)
            vetor_organizado[contador[array[i]]] = array[i + (-1*menor_numero)];
        if(menor_numero < 0)
            vetor_organizado[contador[array[i]]] = array[tam_array - i];
    */
    }
/*
    //copia de um array pro outro
    for(int i = 0; i < tam_array; i++) {
      array[i] = vetor_organizado[i];
    }
    */
}

//-------------- RADIX SORT --------------
void radix_sort(int * array, int size){
  
  // Base 10 is used
  int i;
  int semiSorted[size];
  int significantDigit = 1;
  int largestNum = getMaior(array, size);
  
  // Loop until we reach the largest significant digit
  while (largestNum / significantDigit > 0){
       
    int bucket[10] = { 0 };
    
    // Counts the number of "keys" or digits that will go into each bucket
    for (i = 0; i < size; i++)
      bucket[(array[i] / significantDigit) % 10]++;
    
    /**
     * Add the count of the previous buckets,
     * Acquires the indexes after the end of each bucket location in the array
		 * Works similar to the count sort algorithm
     **/
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];
    
    // Use the bucket to fill a "semiSorted" array
    for (i = size - 1; i >= 0; i--)
      semiSorted[--bucket[(array[i] / significantDigit) % 10]] = array[i];
    
    
    for (i = 0; i < size; i++)
      array[i] = semiSorted[i];
    
    // Move to next significant digit
    significantDigit *= 10;
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
    
    counting_sort(array,tam_array);
    //print_ord_num(array, tam_array);
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