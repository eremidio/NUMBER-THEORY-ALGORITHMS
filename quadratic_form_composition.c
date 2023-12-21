//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO quadratic_form_composition.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o quadratic_form_composition quadratic_form_composition.c -lm

//Cabeçalho
#include"quadratic_form_composition.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t binary_quadratic_form1[3], binary_quadratic_form2[3], binary_quadratic_form3[3];

//Procedimentos
//Recebendo input do usuário
printf("Digite o valor do 1º coeficiente da forma quadrática 1: ");
scanf("%li", &binary_quadratic_form1[0]);
printf("Digite o valor do 2º coeficiente da forma quadrática 1: ");
scanf("%li", &binary_quadratic_form1[1]);
printf("Digite o valor do 3º coeficiente da forma quadrática 1: ");
scanf("%li", &binary_quadratic_form1[2]);

printf("\nForma quadrática 1: (%lix²)+(%lixy)+(%liy²)\n", binary_quadratic_form1[0], binary_quadratic_form1[1], binary_quadratic_form1[2]);

//Recebendo input do usuário
printf("Digite o valor do 1º coeficiente da forma quadrática 2: ");
scanf("%li", &binary_quadratic_form2[0]);
printf("Digite o valor do 2º coeficiente da forma quadrática 2: ");
scanf("%li", &binary_quadratic_form2[1]);
printf("Digite o valor do 3º coeficiente da forma quadrática 2: ");
scanf("%li", &binary_quadratic_form2[2]);

printf("\nForma quadrática 1: (%lix²)+(%lixy)+(%liy²)\n", binary_quadratic_form2[0], binary_quadratic_form2[1], binary_quadratic_form2[2]);


//Aplicando o algoritmo de composição de formas quadráticas 
quadratic_form_composition(binary_quadratic_form1, binary_quadratic_form2, binary_quadratic_form3);
printf("\nForma quadrática composta: (%lix²)+(%lixy)+(%liy²)\n", binary_quadratic_form3[0], binary_quadratic_form3[1], binary_quadratic_form3[2]);

//Finalizando a aplicação
return 0;
          }
