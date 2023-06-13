//VAMOS ESCREVER UM ALGORITMO QUE CALCULA TRIPLAS PITAGÓRICAS USANDO NÚMEROS COMPĹEXOS
//USAREMOS A CLASSE DE NPÚMEROS COMṔLEXOS DEFINIDOS NO ARQUIVO complex_numbers.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o pythagorean_triples2 pythagorean_triples2.cpp

/*
DADO UM NÚMERO COMPLEXO z=a+bi, TEMOS QUE z.z=(a²-b²)+(2ab)i  E |z|²=z*z=a²+b².
ESTAS SÃO EXATAMENTE AS FÓRMULASDE EUCLIDES PARA AS TRIPLAS PITAGÓRICAS.
DESTA FORMA COMPLEXOS DA FORMA z=a+bi, COM a, b INTEIROS E DE PARIDADES DIFERENTES NOS DÃO OUTRA FORMA DE CALCULA TRIPLAS PITAGÓRICAS.

*/

//*************************************************************************************************************************
//CABEÇALHO
#include<iostream>
#include"complex_numbers.hpp"
using namespace std;

//*************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
long long int limit, m, n;
long long int a, b, c;
bool end;
complex<long long int> z1, z2; //Instanciando objetos da classe

//Procedimento
//Recebendo input do usuário
cout<<"Usuário digite um limitante superior para sua tripla pitagórica: ";
cin>>limit;

//Exibindo as triplas pitagóricas
cout<<"Eis a sua lista de triplas pitagóricas:\n";
//Loop principal
for(m=2; m<limit; ++m){
//Caso 1: m é par
if(m%2==0){
for(n=1; n<m; n+=2){
z1.real=m;
z1.imag=n;
z2=z1*z1;

a=z2.real;
b=z2.imag;
c=z1.norm();

//Finalizando o loop
if(c>limit){
end=true;
break;
           } 

cout<<"("<<a<<", "<<b<<", "<<c<<")\n";
                  };
          };

//Caso 2: m é impar
if(m%2==1){
for(n=2; n<m; n+=2){
z1.real=m;
z1.imag=n;
z2=z1*z1;

a=z2.real;
b=z2.imag;
c=z1.norm();

//Finalizando o loop
if(c>limit){
end=true;
break;
           } 

cout<<"("<<a<<", "<<b<<", "<<c<<")\n";
                  };
          };

if(end==true)
break;
                      }; 


//Finalizando a aplicação
return 0;
          }

