#include "stdio.h"

#define infinity 999

void dij(int n,int v,int cost[10][10],int dist[])
{
    int i,u,count,w,flag[10],min;

    for(i=1;i<=n;i++)
        flag[i]=0,dist[i]=cost[v][i];

    count=2;

    while(count<=n)
    {
        min=99;
        for(w=1;w<=n;w++)
            if(dist[w]<min && !flag[w])
                min=dist[w],u=w;

        flag[u]=1;
        count++;

        for(w=1;w<=n;w++)
            if((dist[u]+cost[u][w]<dist[w]) && !flag[w])
                dist[w]=dist[u]+cost[u][w];
    }
}

void dij_main(int k_inst, void * matrix){
    int (*array)[k_inst] = (int (*)[k_inst]) matrix;

    int n,v,i,dist[k_inst];
    
    printf("n Enter the source matrix:");

    dij(n,0,array,dist);
    printf("n Shortest path:n");
    
    for(i=1;i<=n;i++)
        if(i!=v)
            printf("%d->%d,array=%dn",v,i,dist[i]);
    getch();
}


char dir[] = "../instancias/";
void name_file(char * file){
    strcat(dir, file);
}

void readInstances_createMatrix(){
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
        array[k_inst-1][i] = array[i][k_inst-1];
    array[k_inst-1][k_inst-1] = array[0][0];

    //memset(pai, 0, sizeof(pai));
    dij_main(k_inst, array);

}

void file_process(char * file){
    name_file(file);
    readInstances_createMatrix();
}

int main( int argc, char **argv ){
    file_process(argv[1]);
    return 0;
}