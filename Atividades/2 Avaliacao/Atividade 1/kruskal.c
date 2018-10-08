#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j, k, a, b, u, v, ne = 1;
int min, parent[10];

int find(int i) {
    while(parent[i])
        i = parent[i];
    return i;
}

int uni(int i, int j) {
    if(i != j) {
        parent[j] = i;
        return 1;
    }

    return 0;
}

void kruskall(int k_inst, void * matrix){
    int (*array)[k_inst] = (int (*)[k_inst]) matrix;
    int custo_min = 0;

    while(ne < k_inst) {
        for(i = 1, min = 99999; i <= k_inst; i++) {
            for(j = 1; j <= k_inst; j++) {
                if(array[i][j] < min) {
                    min = array[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }

        u = find(u);
        v = find(v);

        if(uni(u, v)) {
            printf("\n%d aresta (%d,%d) = %d\n", ne++, a, b, min);
            custo_min += min;
        }

        array[a][b] = array[b][a] = 99999;
    }
    printf("\nCusto Mínimo = %d\n", custo_min);  
}

char dir[] = "../instancias/";
void name_file(char * file){
    strcat(dir, file);
}

void read_instances(){
    FILE *stream;
	char *line = NULL;
	size_t len = 0, read;
    int i = -1;

    stream = fopen (dir , "r");
    read = getline(&line, &len, stream);
    int k_inst = atoi(line);
    int array[k_inst][k_inst];
    char *number_s;
    
    while ((read = getline(&line, &len, stream)) != -1) {
        i++;
        int j = 0;
        
        number_s = strtok (line, " ");
        while (number_s != NULL)
        {
            if(i == j){
                array[i][j] = 99999;
                j++;
                continue;
            }

            if (i > j){
                //array[i][j] = INFINITY;//--
                array[i][j] = array[j][i];
                j++;
                continue;
            }
            else
                array[i][j] = atoi(number_s);

            number_s = strtok (NULL, " ");
            j++;
        }
    } 
    free(line);
    fclose(stream);

    //copia a ultima coluna para a ultima linha (transposicao)
    for(int i = 0; i <= k_inst; i++)
        //array[k_inst-1][i] = INFINITY;//--
        array[k_inst-1][i] = array[i][k_inst-1];
    array[k_inst-1][k_inst-1] = array[0][0];

    kruskall(k_inst, array);

    for(int i=0;i<k_inst;i++)
    { 
        for(int j=0;j<k_inst;j++)
            printf("%d\t",array[i][j]);
        printf("\n");
    }

}

void file_process(char * file){
    name_file(file);
    read_instances();
}

int main( int argc, char **argv ){
    file_process(argv[1]);

    return 0;
}