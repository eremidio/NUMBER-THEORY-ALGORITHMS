//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DEFINIDAS NO ARQUIVO modular_forms.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o modular_forms modular_forms.cpp -O3

//Cabeçalho
#include<iostream>
#include"modular_forms.hpp"
using namespace std;

//Função principal
int main(){
//Variáveis locais
complex<double> z1, z2, z3;
int k;
//Procedimentos
//Recebendo input do usuário
z1.set();
z2.set();
cout<<"Digite um número inteiro: ";
cin>> k;

//Computando as formas modulares
//Séries de Eisentein
cout<<"G("<<k<<", "<<z1.algebraic()<<", "<<z2.algebraic()<<")= "<< eisenstein_series(z1, z2, k).algebraic()<<"\n";
cout<<"G("<<k<<", "<<z1.algebraic()<<")= "<< eisenstein_series(z1, k).algebraic()<<"\n";
cout<<"E("<<k<<", "<<z1.algebraic()<<")= "<< normalized_eisenstein_series(z1, k).algebraic()<<"\n";

//Discrimante modular, Dedekind eta  e invariante j
cout<<"Δ("<<z1.algebraic()<<")= "<< modular_discriminant(z1).algebraic()<<"\n";
cout<<"η("<<z1.algebraic()<<")= "<< dedekind_eta_function(z1).algebraic()<<"\n";
cout<<"j("<<z1.algebraic()<<")= "<< j_invariant(z1).algebraic()<<"\n";

//Função rho de Weierstrass
//Recebendo input do usuário
z3.set();
cout<<"ρ("<<z3.algebraic()<<", "<<z1.algebraic()<<", "<<z2.algebraic()<<")= "<< weierstrass_rho_function(z3, z1, z2).algebraic()<<"\n";

//Jacobi theta function
cout<<"Θ("<<z1.algebraic()<<", "<<z2.algebraic()<<")= "<< jacobi_theta_function(z1, z2).algebraic()<<"\n";

//Finalizando a aplicação
return 0;
          }
