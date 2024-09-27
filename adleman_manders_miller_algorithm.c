//VAMOS CRIAR ROTINAS PARA TESTARAS ROTINAS CRIADAS NO ARQUIVO adleman_manders_miller_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o adleman_manders_miller_algorithm adleman_manders_miller_algorithm.c -lm


//Cabeçalho
#include"adleman_manders_miller_algorithm.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t a, r, prime, root;


  //Procedimentos
    //Recebendo input do usuário  
    printf("Radicando: ");
    scanf("%li", &a);
    printf("Ordem da raíz: ");
    scanf("%li", &r);
    printf("Módulo: ");
    scanf("%li", &prime);


    //Calculando a raíz de ordem superior em F(p)
    root=modular_nth_root(a, r, prime);

    if(root!=0)
      printf("Raíz de ordem %li de %li em F(%li)=%li\n", r, a, prime, root);
    else
      printf("Não foram encontradas raízes de ordem %li de %li em F(%li)\n", r, a, prime);          
    


  //Finalizando a aplicação
  return 0;
  
} 
