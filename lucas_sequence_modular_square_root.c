//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO lucas_sequence_modular_square_root.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lucas_sequence_modular_square_root lucas_sequence_modular_square_root.c -lm -O2


//Cabeçalho
#include"lucas_sequence_modular_square_root.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t n, p, root;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número primo ímpar: ");
    if(scanf("%li", &p)!=1) return 0;
    printf("Digite um número inteiro: ");
    if(scanf("%li", &n)!=1) return 0;

    //Calculando raíz quadrada a menos de uma relação de congruência
    root = ls_modular_square_root(n, p);

    if(root==0)
      printf("Não foram em contradas raízes quadradas de %li (mod %li)\n", n, p);
    else
      printf("Raíz quadrada de %li (mod %li)=%li.\n", n, p, root);

  //Finalizando a aplicação
  return 0;

}
