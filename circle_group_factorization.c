//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO circle_group_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o circle_group_factorization circle_group_factorization.c -lm


//Cabeçalho
#include"circle_group_factorization.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t number, ord;
 

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    if(scanf("%li", &number)!=1) return 0;
    printf("Fator de profundidade de busca: ");
    if(scanf("%li", &ord)!=1) return 0;

    //Fatorando o número em questão
    circle_group_factorization(number, ord);//Profundidade de busca 1000, parâmetro ajustável

  //Finalizando a aplicação
  return 0;

}
