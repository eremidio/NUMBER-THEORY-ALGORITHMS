//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO gaussian_euclidean_division.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o gaussian_euclidean_division gaussian_euclidean_division.cpp

//Cabeçalho
#include"complex_numbers.hpp"
#include"gaussian_euclidean_division.hpp"
#include<iostream>
using namespace std;

//Funções
int main(){
//Variáveis locais
complex<int64_t> z, w, gcd;

//Procedimentos
//Recebendo input do usuário
z.set();
w.set();

//Calculando máximo divisor comum de dois inteiros gaussianos
gcd=gaussian_euclides_algorithm(z, w);
cout<<"mmc de "<<z.algebraic() <<" e "<< w.algebraic()<<" é "<<gcd.algebraic()<<"\n";

//Finalizando a aplicação
return 0;
          }
