//VAMOS CRIAR UM PROGRAMA PARA TESTAR O ALGORITMO DA PENEIRA QUADRÁTICA PARA FATORAR GRANDES NÚMEROS INTEIROS (>10²¹)
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o quadratic_sieve quadratic_sieve.cpp

//Cabeçalho
#include"quadratic_sieve_main.h"


//Função principal
int main(){
//Instanciando um objeto da classe
quadratic_sieve factorizer;

//Executando o algoritmo
factorizer.run();
factorizer.print_result();

//Finalizando a aplicação
return 0;
          };
