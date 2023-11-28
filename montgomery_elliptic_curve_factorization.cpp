//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO montgomery_elliptic_curve_factorization.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o montgomery_elliptic_curve_factorization montgomery_elliptic_curve_factorization.cpp -O3 -lboost_system

//Cabeçalho
#include"montgomery_elliptic_curve_factorization.hpp"

//Função principal
int main(){
//Criando um objeto da classe
elliptic_curve_method factorizer;

//Executando o algoritmo
factorizer.run();

//Finalizando a aplicação
return 0;
          }
