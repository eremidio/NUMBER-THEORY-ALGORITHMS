//VAMOS CRIAR UM PROGRAMA QUE TESTAS AS ROTINAS CRIADAS NO ARQUIVO modular_cubic_root.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o modular_cubic_root modular_cubic_root.c



//Cabeçalho
#include"modular_cubic_root.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t a, prime, root;


  //Procedimentos
    //Recebendo input do usuário  
    printf("Radicando: ");
    scanf("%li", &a);
    printf("Módulo: ");
    scanf("%li", &prime);


    //Calculando a raíz de ordem superior em F(p)
    root=modular_cubic_root(a, prime);

    if(root!=0)
      printf("Raíz de cúbica de %li em F(%li)=%li\n", a, prime, root);
    else
      printf("Não foram encontradas raízes cúbicas de %li em F(%li)\n", a, prime);          
    


  //Finalizando a aplicação
  return 0;
  
} 
