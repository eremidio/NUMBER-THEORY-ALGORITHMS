//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DEFINIDAS NO ALGORITMO DA PENEIRA GENERALIZADA DE CORPOS NUMÉRICOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o  general_number_field_sieve general_number_field_sieve.cpp -O2


//Cabeçalho
#include"general_number_field_sieve_main.h"


//Função principal
int main(){
//Instanciando um objeto da classe
general_number_field_sieve factorizer;

//Executando o algoritmo
factorizer.run();
factorizer.print_result();

//Finalizando a aplicação
return 0; 
          }
