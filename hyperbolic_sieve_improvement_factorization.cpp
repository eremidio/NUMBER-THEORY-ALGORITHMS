//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO  hyperbolic_sieve_improvement_factorization.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o hyperbolic_sieve_improvement_factorization hyperbolic_sieve_improvement_factorization.cpp -O2

//Cabeçalho
#include"hyperbolic_sieve_improvement_factorization.hpp"

//Função principal
int main(){
//Variáveis locais
__int128_t number, bound;
char number_string[41], number_string2[41];

//Recebendo o input
printf("Número a ser fatorado: ");

if(scanf("%s", number_string)!=1)
return 0;
number=scanf128(number_string);


printf("Intervalo de busca: ");

if(scanf("%s", number_string2)!=1)
return 0;

bound=scanf128(number_string2);


//Aplicando o algoritmo de Fermat
hyperbolic_fermat_factorization(number, bound);

//Finalizando a aplicação
return 0;
          }

