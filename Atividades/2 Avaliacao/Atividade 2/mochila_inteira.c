#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <iostream>

using namespace std;

typedef struct{
    int valor;
    bool presenca;
} g_i;

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
    int arr_pesos[n], arr_valor[n], j = 0;

    while ((read = getline(&line, &len, stream)) != -1) {
        arr_pesos[j] = atoi(strtok (line, " "));
        arr_valor[j]   = atoi(strtok (NULL, " "));
        j++;
    }    

    free(line);
    fclose(stream);
}

void file_process(char * file){
    name_file(file);
    readInstances();
}

int main( int argc, char **argv ){
    file_process(argv[1]);
    return 0;
}