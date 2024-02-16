//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO special_purpose_factorization_algorithm1.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o special_purpose_factorization_algorithm1 special_purpose_factorization_algorithm1.c -lm

//NOTA: O algoritmo as vezes produz resultados incorretos ou fica num loop infinito.



//Cabeçalho
#include"special_purpose_factorization_algorithm1.h"

//Função principal
int main(){
//Variáveis locais
int64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro a ser fatorado: ");
scanf("%li", &number);

//Fatorando o número em questão
special_purpose_factorization_algorithm(number);

//Finalizando a aplicação
return 0;
          }
