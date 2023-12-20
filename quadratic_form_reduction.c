//VAMOS CRIARUM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO quadratic_form_reduction.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o quadratic_form_reduction quadratic_form_reduction.c

//Cabeçalho
#include"quadratic_form_reduction.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t binary_quadratic_form[3];

//Procedimentos
//Recebendo input do usuário
printf("Digite o valor do 1º coeficiente da forma quadrática: ");
scanf("%li", &binary_quadratic_form[0]);
printf("Digite o valor do 2º coeficiente da forma quadrática: ");
scanf("%li", &binary_quadratic_form[1]);
printf("Digite o valor do 3º coeficiente da forma quadrática: ");
scanf("%li", &binary_quadratic_form[2]);

printf("\nForma quadrática original: (%lix²)+(%lixy)+(%liy²)\n", binary_quadratic_form[0], binary_quadratic_form[1], binary_quadratic_form[2]);

//Aplicando o algoritmo que reduz uma forma quadrada a sua forma original
reduce_quadratic_form(binary_quadratic_form);
printf("Forma quadrática reduzida: (%lix²)+(%lixy)+(%liy²)\n", binary_quadratic_form[0], binary_quadratic_form[1], binary_quadratic_form[2]);

//Finalizando a aplicação
return 0;

          }
