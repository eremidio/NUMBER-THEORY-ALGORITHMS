//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO divisor_residue_class_algorithm.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o divisor_residue_class_algorithm divisor_residue_class_algorithm.c -lm


//Cabeçalho
#include"divisor_residue_class_algorithm.h"

//Função principal
int main(){
//Variáveis locais
int64_t r, s, n;

//Procedimentos
//Recebendo input do usuário
printf("Digite um inteiro n:");
scanf("%li", &n);
printf("Digite um inteiro s<n:");
scanf("%li", &s);
printf("Digite um inteiro r<s:");
scanf("%li", &r);

//Teste das funções auxiliares
printf("73-¹ mod 75: %li\n", modular_inverse(73,75));

//Executando o algoritmo
divisors_residue_class_algorithm(r, s, n);

//Finalizando a aplicação
return 0;
          }
