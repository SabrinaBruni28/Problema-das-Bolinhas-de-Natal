#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Número de cores
#define K 2
//arquivo de texto
#define TEXT "Arquivos/Sem solução/testeS10.txt"
//Número de espaços
#define N 10
//Número máximo de adjacências por bolinha
#define A 4

//Função que constrói a matriz de adjacência
int matriz(FILE *file, int m[N][N])
{
    char c;
    int i, j;
    file = fopen(TEXT, "r");
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            m[i][j] = 0;

    if(file == NULL)
    {
        printf("Erro ao abrir arquivo!");
        return 0;
    }
    fflush(file);
    
    while(1)
    {
        fscanf(file, "%d", &i);
        if( feof(file) )
            break;
        m[i][i] = -1;
        
        while(1)
        {
            c = fgetc(file);
            if( c != ' ' )
                break;
            fscanf(file, "%d", &j);
            m[i][j] = 1;
        }
    }
    fclose(file);

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }

    return 1;
}

//Função que verifica, com base na matriz de adjacência, se o arranjo de cores é válido
int Verifica(char *str,int matriz[N][N]){
    int i, j, k, guarda[A];
    for(i = 0; i < N; i++){
        for(k = 0; k < A; k++){
            guarda[k] = -1;
        }
        k=0;
        for(j = 0; j < N; j++){
            if(matriz[i][j] == 1){
                guarda[k] = j;
                k++;
            }
        }
        for(k = 0; (guarda[k] != -1) && (k < A); k++){
            if(str[i] == str[guarda[k]]){
                return 0;
            }
        }
    }
    return 1;
}

int main() {

    // Criação da matriz de adjacência
    FILE* file = NULL;
    int m[N][N];
    matriz(file, m);
    
    // Conjunto de caracteres a ser permutado
    char input[K] = {'A', 'B'};
    
    // Vetor onde serão permutados os caracteres
    char str[N];
    
    // Variáveis para percorrer vetores
    int i, j, k;
    // Contador de soluções encontradas
    int cont=0;
    
    //"Número" que representará a permutação atual
    int *num;
    
    printf("\nConjunto de solucoes para %d bolinhas: cor A e cor B\n\n", N);
    
    /*
     * Cria o nosso "número". Ele é um vetor
     * de N+1 posições, sendo que a última é 
     * reservada para indicar quando todos as
     * permutações de tamanho N foram gerados,
     * que inicializa com todas as posições
     * valendo 0. A idéia é que o código "conte",
     * variando os caracteres no vetor do mesmo
     * modo que se variam os algarismos ao se contar.
     */
    num = (int *) calloc( (N+1), sizeof(int) );
    if ( num == NULL ) {
        perror("calloc");
        return -1;
    }

    /* 
     * Laço que termina quando a última posição
     * do vetor for 1.
     */
    while ( num[N] == 0 ) {
        // Laço que varia a primeira posição da primeira à K-ésima cor
        for ( i = 0; i < K; i++ ) {
            // "Coloração" do str
            for ( j = 0, k = N-1; j < N; j++ ) {
                str[k] = input[num[j]];
                k-- ;
            }
            str[N] = 0;
            
            // Valida a coloração aplicada a str
            if(Verifica(str, m)){
                cont++;
                printf("Solucao %d: %s\n", cont, str);
            }
            
            // Incrementa o algarismo menos significativo do "número
            num[0]++;
        }
        
        // Muda de casa na contagem do "número" e lança os "vai uns" 
        for ( i = 0; i < N; i++ ) {
            if ( num[i] == K ) {
                num[i] = 0;
                num[i+1]++;
            }
        }
    }
    if(cont==0)
        printf("Nao ha solucao\n");
    return 0 ;
}
