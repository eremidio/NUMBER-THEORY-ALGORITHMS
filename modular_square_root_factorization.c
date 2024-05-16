//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO modular_square_root_factorization.h
//COMPILAR ESTE PROGRAMA COM COMANDO: gcc -o modular_square_root_factorization modular_square_root_factorization.c


//Cabeçalho
#include"modular_square_root_factorization.h"


//Função principal
int main(){

 //Variáveis locais
 int64_t n, trials;

 //Procedimentos
  //Recebendo input do usuário
  printf("Número a ser fatorado: ");
  scanf("%li", &n);
  printf("Número de tentativas: ");
  scanf("%li", &trials);


  //Fatorando o número em questão usando o algoritmo probabilístico usando raízes quadradas modulares
  modular_square_root_factorization(n, trials);


 //Finalizando a aplicação
 return 0;

          }
