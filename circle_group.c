//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADASNO ARQUIVO circle_group.h
//COMPILAR ESTE PROGRAMA COM COMANDO: gcc -o circle_group circle_group.c


//Cabeçalho
#include"circle_group.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  struct circle_point p1, p2, p3;
  int64_t characteristic, order, n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Característica do grupo] Inteiro primo ímpar: ");
    scanf("%li", &characteristic);

    //Gerando um ponto no círculo unitário
    p1=set_unitary_circle_point(characteristic);
    printf("[Ponto gerado no círculo unitário]: P(%li, %li)\n", p1.x,  p1.y);

    //Duplicando um ponto
    p2=circle_pointwise_doubling(p1);  
    printf("[Ponto duplicado]: 2P(%li, %li)\n", p2.x,  p2.y);

    //Múltiplo escalar de um  ponto
    printf("[Escalar] n: ");
    scanf("%li", &n);    
  
    p3=circle_pointwise_scalar_multiplication(p1, n);
    printf("[Múltiplo escalar de um ponto]: %liP(%li, %li)\n", n, p3.x,  p3.y);


    //Ordem do grupo
    order=unitary_circle_group_order(characteristic);
    printf("[Ordem do grupo] #C(%li)=%li\n", characteristic, order);


  //Finalizando a aplicação
  return 0;

}



