//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO gaussian_factorization.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o gaussian_factorization gaussian_factorization.cpp

//Cabeçalho
#include"gaussian_factorization.hpp"
#include"complex_numbers.hpp"
#include<iostream>
using namespace std;

//Função principal
int main(){
//Variáveis locais
complex<int64_t> gaussian;
//Procedimentos
//Recebendo input do usuário
gaussian.set();

//Decompondo o número em questão em fatores primos
gaussian_factorization(gaussian);

//Finalizando a aplicação
return 0;
          }
