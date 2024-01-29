//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO shanks_class_group_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o shanks_class_group_factorization shanks_class_group_factorization.c -lm


//Cabeçalho
#include"shanks_class_group_factorization.h"

//Função principal
int main(){
//Variáveis locais
int64_t n, d, h;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro: ");
scanf("%li", &n);

//Computando o discrimante fundamental e o número de classe associado a este discriminante fundamental
d=generate_fundamental_discriminant(n);
printf("Discriminante fundamental associado a %li: %li\n", n, d);
h=class_number(n);
printf("h(%li)=%li\n", d, h);

//Fatorando números inteiros
shanks_class_group_factorization(n);

//Finalizando a aplicação
return 0;
          }
