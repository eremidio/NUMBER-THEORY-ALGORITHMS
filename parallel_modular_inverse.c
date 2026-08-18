//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO parallel_modular_inverse.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o parallel_modular_inverse parallel_modular_inverse.c -O2


//Cabeçalho
#include"parallel_modular_inverse.h"


//Função principal
int main(){

  //Variáveis locais
  size_t set_size;
  int64_t N, factor;

  //Propcedimentos
    //Recebendo input do usuário e alocando espaço de memória
    printf("[Inteiro congruente] N: ");
    if(scanf("%li", &N)!=1) return 0;
    printf("[Número de classes residuais - inteiro] k: ");
    if(scanf("%zu", &set_size)!=1) return 0;

    int64_t* a = (int64_t*)calloc(set_size, sizeof(int64_t));//Array de classes residuais
    int64_t* b = (int64_t*)calloc(set_size, sizeof(int64_t));//Array de inversos modulares
    int64_t* c = (int64_t*)calloc(set_size, sizeof(int64_t));//Array de classes residuais acumuladas


    for(size_t i=0; i<set_size; ++i){
      printf("[Classe residual] a(%zu): ", i);
      if(scanf("%li", &a[i])!=1) goto clean_memory;
    }


    //Computando inversos modulares ou um fator não trivial de N
    bool test=parallel_modular_inverse(a, b, c, set_size, &factor, N);
    if(!test){
      printf("Fator de %li encontrado: %li\n", N, factor);
    }
    else{
      for(size_t j=0; j<set_size; ++j){
        printf("%li ⁻¹ mod %li = %li, ", a[j], N, b[j]);
      }
      printf("...\n");
    }


    //Limpando o cachê de memória
    clean_memory:
    if(a) free(a); a=NULL;
    if(b) free(b); b=NULL;
    if(c) free(c); c=NULL;


  //Finalizando a aplicação 
  return 0;

}
