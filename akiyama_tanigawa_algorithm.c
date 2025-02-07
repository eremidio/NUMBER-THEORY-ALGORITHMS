//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO akiyama_tanigawa_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o akiyama_tanigawa_algorithm akiyama_tanigawa_algorithm.c 
//Cabeçalho
#include"akiyama_tanigawa_algorithm.h"



//Função principal
int main(){

  //Variáveis locais
  int n;


  //Procedimento
    //Recebendo input do usuário
    printf("[Inteiro] n(<=100): ");
    scanf("%d", &n);

    //Computando os números de Bernoulli via o algoritmo de Akiyama-Tanigawa
    akiyama_tanigawa_algorithm(n);

    for(int i=0; i<n; ++i)
      printf("%li/%li, ", bernoulli_fractions_array[i].num, bernoulli_fractions_array[i].den);
    printf("...\n");


  //Finalizando a aplicação
  return 0;


}
