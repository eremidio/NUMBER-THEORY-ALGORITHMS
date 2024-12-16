//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO least_primitive_root.h
//COMPILAR ESTE PROGRAMA COMOCOMANDO: gcc -o least_primitive_root least_primitive_root.c -lm


//Cabeçalho
#include"least_primitive_root.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  uint64_t n, g;


  //Procedmentos
    //Recebendo input do usuário
    printf("Inteiro a ser testado: ");
    scanf("%lu", &n);


    //Calculasndo raízes primitivas módulo n
    g=find_primitive_root(n);

    if(g==0) printf("Não existem raízes primitivas em F(%lu).\n", n);
    else printf("Raíz primitiva em F(%lu)=%lu.\n", n, g);


  //Finalizando a aplicação
  return 0;

}
