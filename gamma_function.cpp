//PROGRAMA PARA TESTAR A IMPLEMENTAÇÃO DA FUNÇÃO GAMA DEFINIDA NO ARQUIVO gamma_function.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o gamma_function gamma_function.cpp

//**************************************************************************************************************************
//Cabeçalho
#include<iostream>
#include<iomanip>
#include"complex_numbers.hpp"
#include"gamma_function.hpp"
using namespace std;

//**************************************************************************************************************************
//Função principal

int main(){
//Variáveis locais 
int argument1;
double argument2;
complex<double> argument3, argument6(2.5, 2), argument7(1.2, 2.1);
double argument4, argument5;
//Procedimentos
//Argumento inteiro
cout<<"Usuário digite um número inteiro: \n->";
cin>>argument1;
cout<<"Γ("<<argument1<<")= "<<gamma(argument1)<<".\n";

//Argumento real
cout<<"Usuário digite um número real: \n->";
cin>>argument2;
cout<<"Γ("<<argument2<<")= "<<setprecision(8)<<gamma(argument2)<<".\n";
cout<<"O valor de π é cerca de "<<setprecision(8)<<gamma(0.5)*gamma(0.5)<<"\n";

//Número complexo
argument3.set();//Definindo um número complexo usando a notação algébrica
std::cout<<"Γ("<<argument3.algebraic()<<")= "<<setprecision(8)<<gamma(argument3).algebraic()<<".\n";

//Função beta
//Números reais
cout<<"Usuário digite dois números reais: \n->";
cin>>argument4;
cout<<" &\n";

cin>>argument5;
cout<<"β("<<argument4<<","<<argument5<<")= "<<setprecision(8)<<beta(argument4, argument5)<<".\n";

//Números complexos
cout<<"β("<<argument6.algebraic()<<","<<argument7.algebraic()<<")= "<<setprecision(8)<<beta(argument6, argument7).algebraic()<<".\n";
//Finalizando a aplicação
return 0;
          }
