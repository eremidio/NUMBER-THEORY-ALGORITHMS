//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO abc_conjecture.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o abc_conjecture abc_conjecture.c -lm -O2

//Cabeçalho
#include"abc_conjecture.h"


//Função principal
int main(){

  //Variáveis locais
  FILE* abc_file;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n (n²≲ limite de teste): ");
    if(scanf("%i", &ABC_SIZE)!=1)  return 0;

    //Computando um array de menores fatores primos de números inteiros e abrindo um arquivo para alocação de resultados da simulação
    abc_file=fopen("ABC_TEST.txt", "a+");
    int32_t* ABC_PRIME_ARRAY=fill_prime_factor_array();//Pré computação de fatorações parciais
    for(int32_t i=0; i<=ABC_RAD_MAX; ++i) ABC_RADICALS[i]=0;//Pré computação de radicais

    struct abc_set* abc_array=test_abc_conjecture(ABC_PRIME_ARRAY);


    //Registrando os dados da simulação em um arquivo
    fprintf(abc_file, "Simulação da conjectura abc\nLimitante superior para os parâmetros a,b: %li\na   b   c   q(a, b, c)\n\n", (int64_t)(ABC_SIZE*ABC_SIZE));
    for(size_t c=0; c<ABC_COUNTER; c++)
      fprintf(abc_file, "%li    %li    %li    %lf\n", abc_array[c].a,  abc_array[c].b,  abc_array[c].c,  abc_array[c].q);


    //Limpando o cachê de memória
    fclose(abc_file);
    if(ABC_PRIME_ARRAY){
      free(ABC_PRIME_ARRAY); ABC_PRIME_ARRAY=NULL;  
    }  
    if(abc_array){
      free(abc_array); abc_array=NULL;  
    }  

  //Finalizando a aplicação
  return 0;

}
