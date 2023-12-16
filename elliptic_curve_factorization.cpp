//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DEFINIDAS NO ARQUIVO elliptic_curve_factorization.hpp
//COMPILAR ESTE PROGRAMA COM: g++ -o elliptic_curve_factorization elliptic_curve_factorization.cpp -O3 -lboost_system

//CABEÇALHO
#include"elliptic_curve_factorization.hpp"
using namespace std;

//FUNÇÃO PRINCIPAL
int main(){
//Instanciando um objeto da classe e executando um algoritmo
elliptic_curve_method factorizer;
factorizer.run();

//Finalizando a aplicação
return 0;

          }
