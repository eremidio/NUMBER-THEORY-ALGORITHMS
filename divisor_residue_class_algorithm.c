//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO divisor_residue_class_algorithm.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o divisor_residue_class_algorithm divisor_residue_class_algorithm.c -lm -O3


//Cabeçalho
#include"divisor_residue_class_algorithm.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t r, s, n;
  int counter;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n:");
    if(scanf("%li", &n)!=1) return 0;

    printf("[Inteiro] c:");
    if(scanf("%i", &counter)!=1) return 0;

    //Executando o algoritmo
    lenstra_divisors_residue_class_algorithm(n, counter);


  //Finalizando a aplicação
  return 0;

}
