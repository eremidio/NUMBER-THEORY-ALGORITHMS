//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO totient_valence_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o totient_valence_function totient_valence_function.c -O2


//Cabeçalho
#include"totient_valence_function.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de valência totiente no intervalo {1,2,...,n}
    int32_t* totient_valence_array=compute_totient_valence_function(n);

    for(int32_t i=1; i<=n; ++i) printf("Nφ(%i)=%i, ", i, totient_valence_array[i]);
    printf("...\n");

    //Limpando o cachê de memória
    if(totient_valence_array) free(totient_valence_array);
    totient_valence_array=NULL;


  //Finalizando a aplicação
  return 0;

}
