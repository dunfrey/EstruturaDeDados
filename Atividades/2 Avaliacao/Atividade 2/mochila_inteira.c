#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <iostream>

typedef struct{
    int valor = 0;
    bool presenca = false;
} value_v_p;

void mochila(int n, int M, int * arr_peso, int * arr_custo){
    value_v_p g_[M+1][n+1];
    
    for(int j = n-1; j >= 0; j--)
        for(int i = 1; i <= M; i++){
            int valor_esq = g_[i][j+1].valor;
            int valor_dir = 0;

            if (arr_peso[j] <= i) 
                valor_dir = g_[(i - arr_peso[j])][i].valor + arr_custo[j];

            if(valor_esq > valor_dir || valor_dir == 0){
                g_[i][j].valor = valor_esq;
                g_[i][j].presenca = false;
            } 
            if(valor_dir > valor_esq) {
                g_[i][j].valor = valor_dir;
                g_[i][j].presenca = true;
            }         
        }
    
    /* PRINTING --
    */
    for(int i = 0; i <= M; i++){
        for(int j = 0; j <= n; j++)
            printf("%d - %d\t",g_[i][j].valor, g_[i][j].presenca);
        printf("\n");
    }

    printf("\n");
    int peso_total = 0, valor_total = 0, count = 0, lin = M, col = 0;
    while(count < n ) {
        printf("g_[lin:%d][col:%d ]: %d \n", lin, col, g_[lin][col].presenca);

        if(g_[lin][col].presenca == 1){
            lin -= arr_peso[count];
            peso_total += arr_peso[count];
            valor_total += arr_custo[count];
        }

        col++;
        count++;
    }
    printf("\n - Peso Total de itens dentro da mochila:  %d kg", peso_total);
    printf("\n - Valor Total de itens dentro da mochila: %d R$\n\n", valor_total);

}

char dir[] = "../instancias_mochila/";
void name_file(char * file){
    strcat(dir, file);
}

void readInstances(){
    
    FILE *stream;
	char *line = NULL;
	size_t len = 0, read;
    char *number_s;

    stream = fopen ( dir , "r");
    read = getline(&line, &len, stream);
    
    int n = atoi(strtok (line, " "));
    int M = atoi(strtok (NULL, " "));
    int arr_peso[n], arr_custo[n], k = 0;

    while ((read = getline(&line, &len, stream)) != -1) {
        arr_peso[k]  = atoi(strtok (line, " "));
        arr_custo[k] = atoi(strtok (NULL, " "));
        k++;
    }

    free(line);
    fclose(stream);

    mochila(n, M, arr_peso, arr_custo);

}

void file_process(char * file){
    name_file(file);
    readInstances();
}

int main( int argc, char **argv ){
    file_process(argv[1]);
    return 0;
}