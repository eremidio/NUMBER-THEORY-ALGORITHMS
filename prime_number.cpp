//VAMOS CRIAR UM PROGRAMA PARA CALCULAR SE UM NÚMERO É PRIMO OU NÃO USANDO UM MÉTODO DE DIVISÃO
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o prime_number prime_number.cpp

//*****************************************************************************************************
//CABEÇALHO
#include <iostream>
#include<cmath>
#include<stdint.h>
using namespace std;


//*****************************************************************************************************
//FUNÇÕES
//Função que calcula se um número é primo ou não
bool is_prime(uint64_t n){
//Casos triviais
//0,1
if(n<=1)
return false;

//Primos menores que 100
if(n==2 || n==3 || n==5 || n==7 || n==11 ||  n==13|| n==17 || n==19 || n==23 || n==29|| n==31 || n==37 || n==41)
return true;
if(n==43 || n==47 || n==53 || n==59 || n==61 || n==67 || n==71|| n==73 || n==79 || n==83 || n==89|| n==97)
return true;

//Testando divisibilidade por primos menores do que 100
if(n%2==0 || n%3==0 || n%5==0 || n%7==0 || n%11==0|| n%13==0|| n%17==0 || n%19==0 || n%23==0 || n%29==0|| n%31==0 || n%37==0 || n%41==0)
return false;
else if(n%43==0|| n%47==0 || n%53==0 || n%59==0|| n%61==0 || n%67==0 || n%71==0 || n%73==0|| n%79==0 || n%83==0 || n%89==0)
return false;
else if(n%97==0)
return false;

//Variáveis locais
uint64_t sqrt_n =std::sqrt(n);

//Procedimento usando uma otimização 30k+1
for(uint64_t i=31; i<sqrt_n+1; i+=30){
if((n%i)==0 || (n%(i+2))==0 ||(n%(i+6))==0 || (n%(i+10))==0 || (n%(i+12))==0 || (n%(i+16))==0 || (n%(i+18))==0 || (n%(i+22))==0 || (n%(i+28))==0)
return false;
                                     };
return true;
                         };

//*****************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t number, i;
//Procedimentos
//Recebendo input do usuário
cout<<"Digite um limitante para sua sequência de números primos: ";
cin>>number;
   
//Printando a sequência de números primos
for(i=0; i<=number; ++i){
if(is_prime(i))
cout<<i<<" ";
                        };
cout<<"\n";
   
//Finalizando a aplicação
return 0;
           }
