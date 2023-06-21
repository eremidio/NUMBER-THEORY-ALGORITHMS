//VAMOS CRIAR UM PROGRAMA QUE EXIBE NA TELA UMA LISTA DE NÚMEROS PRIMOS ATÉ UM LIMITE DETERMINADO PELO USUÁRIO

/*CABEÇAHO*/
#include<iostream>
#include<cmath>
using namespace std;

//FUNÇÃO QUE CHECA SE UM NÚMERO É PRIMO
bool eprimo(uint64_t n){
//Variáveis
uint64_t i;

//Procedimentos

if (n == 2 || n == 3)
return true;

if (n <= 1 || n % 2 == 0 || n % 3 == 0)
return false;

for(i = 5; i * i <= n; i += 6){
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
cout<<"2, ";
for(i=3; i<=limite; i++){
if(eprimo(i))
cout<<i<<", ";
else if(!eprimo(i))
               continue;};
cout<<" ...\n";
return 0;
}

