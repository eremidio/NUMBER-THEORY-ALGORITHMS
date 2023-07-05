//VAMOS CRIAR UM PROGRAMA QUE EXIBE NA TELA UMA LISTA DE NÚMEROS PRIMOS ATÉ UM LIMITE DETERMINADO PELO USUÁRIO

/*CABEÇALHO*/
#include<iostream>
#include<cmath>
using namespace std;

//FUNÇÃO QUE CHECA SE UM NÚMERO É PRIMO
bool eprimo(uint64_t n){
//Variáveis
uint64_t i;

//Procedimentos
//Casos triviais
if(n==2 || n==3 || n==5 || n==7 || n==11 ||  n==13|| n==17 || n==19 || n==23 || n==29|| n==31 || n==37 || n==41 || n==43)
return true;
if(n==47 || n==53 || n==59 || n==61 || n==67 || n==71|| n==73 || n==79 || n==83 || n==89|| n==97)
return true;

//Teste de fatores primos menores que 100
if(n%2==0 || n%3==0 || n%5==0 || n%7==0 || n%11==0|| n%13==0|| n%17==0 || n%19==0 || n%23==0 || n%29==0|| n%31==0 || n%37==0 || n%41==0)
return false;
else if(n%43==0|| n%47==0 || n%53==0 || n%59==0|| n%61==0 || n%67==0 || n%71==0 || n%73==0|| n%79==0 || n%83==0 || n%89==0)
return false;
else if(n%97==0)
return false;

//Tentativa de divisão e erro com uma otimização 6k+1
if (n <= 1)
return false;

for(i = 101; i * i <= n; i += 6){
if (n % i == 0 || n % (i + 2) == 0)
return false;
                             };
return true;
                       }

//FUNÇÃO PRINCIPAL
int main(){
//DEFINIÇÃO DE VARIÁVEIS
uint64_t limite, i;
cout<<"Digite um limitante superior para sua sequência de números primos:\n";
cin>>limite;
//CRIANDO A LISTA DE NÚMEROS PRIMOS
cout<<"Eis a sua lista de números primos.\n";
for(i=2; i<=limite; i++){
if(eprimo(i))
cout<<i<<", ";
else if(!eprimo(i))
               continue;};
cout<<" ...\n";
return 0;
}

