//VAMOS CRIAR UM PROGRAMAN QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO prime_constellations.h
//COMPILAR ESTE PROGRAMA COM O PROGRAMA: gcc -o prime_constellations prime_constellations.c -lm -O2


//Cabeçalho
#include"prime_constellations.h"


//Função principal
int main(){

  //Variáveis locais
  long double x;


  //Procedimentos  
    //Recebendo input do usuário
    int* prime_constellation =  setup_ktuple();

    printf("\nConstelação de primos da forma: (");
    for(size_t k=0; k<K_TUPLE_SIZE; k++){
      printf("p+%d", prime_constellation[k]);
      if(k==(K_TUPLE_SIZE-1)) break; else printf(", ");
    }
    printf(")\n");


    //Testando se uma enupla define uma constelação de primos admissível
    if(is_admissible_constellation(prime_constellation))
      printf("Constelação de primos admissível!\n");
    else printf("Constelação de primos não admissível!\n");


    //Limpando o cachê de memória
    if(prime_constellation) free(prime_constellation);
    prime_constellation=NULL;


  //Finalizando a aplicação
  return 0;

}
