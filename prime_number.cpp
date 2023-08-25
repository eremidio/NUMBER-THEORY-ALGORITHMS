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
if(n<2)
return false;
//Testes em primos menores que 1000
int low_primes[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

for(auto x:low_primes){
if(n==x)
return true;
if(n%x==0)
return false;
                      };
//Loop principal
if(n>1000){
for(uint64_t i = 1001; i<std::sqrt(n); ++i){
if((n%i)==0 || (n%(i+2))==0)
return false;
                                           };
          };

//Caso passe nos testes acima
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
