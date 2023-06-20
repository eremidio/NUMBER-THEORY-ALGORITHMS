//VAMOS CRIAR UM PROGRAMA PARA TESTAR A FUNÇÃO ZETA DE RIEMANN DEFINIDA NO ARQUIVO riemann_zeta.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o riemann_zeta riemann_zeta.cpp

//**************************************************************************************************************************
//Cabeçalho
#include<iostream>
#include<iomanip>
#include<cmath>
#include"complex_numbers.hpp"
#include"riemann_zeta.hpp"
using namespace std;

//**************************************************************************************************************************
//Função principal

int main(){
//Variáveis locais
int argument1;
double argument2;
complex<double> argument3;
complex<double> argument4(0.56, 3.2), argument5(-0.56, 3.2);

//Procedimentos
//Argumento inteiro
cout<<"Usuário digite um número inteiro: \n->";
cin>>argument1;
cout<<"ζ("<<argument1<<")= "<<riemann_zeta_function(argument1)<<".\n";

//Argumento real
cout<<"Usuário digite um número real: \n->";
cin>>argument2;
cout<<"ζ("<<argument2<<")= "<<setprecision(10)<<riemann_zeta_function(argument2)<<".\n";
cout<<"O valor de π é cerca de "<<setprecision(10)<<sqrt(riemann_zeta_function(2)*6)<<"\n";

//Argumento complexo
argument3.set();
cout<<"ζ("<<argument3.algebraic()<<")= "<<riemann_zeta_function(argument3).algebraic()<<".\n";

//Função eta de Dirichlet
cout<<"η("<<argument2<<")= "<<setprecision(10)<<dirichlet_eta_function(argument2)<<".\n";
cout<<"η("<<argument3.algebraic()<<")= "<<dirichlet_eta_function(argument3).algebraic()<<".\n";

//Função xi de Riemann
cout<<"χ("<<argument2<<")= "<<setprecision(10)<<riemann_xi_function(argument2)<<".\n";
cout<<"χ("<<argument3.algebraic()<<")= "<<riemann_xi_function(argument3).algebraic()<<".\n";

//Continuação analítica da função zeta de Riemann
cout<<"ζ(0.5)= "<<setprecision(10)<<riemann_zeta_function_analytical_continuation(0.5)<<".\n";
cout<<"ζ(-0.5)= "<<setprecision(10)<<riemann_zeta_function_analytical_continuation(-0.5)<<".\n";
cout<<"ζ(0.56+3.2i)= "<<riemann_zeta_function_analytical_continuation(argument4).algebraic()<<".\n";
cout<<"ζ(-0.56+3.2i)= "<<riemann_zeta_function_analytical_continuation(argument5).algebraic()<<".\n";

//Finalizando a aplicação
return 0;
          }
