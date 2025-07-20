//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTI8NAS CRIADAS NO ARQUIVO polygonal_partitions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o polygonal_partitions polygonal_partitions.c -O2


//Cabeçalho
#include"polygonal_partitions.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t n;
  int s;

  //Procedimentos
    //Recebendo input dos usuários
    printf("[Inteiro] n: ");
    if(scanf("%li", &n)!=1) return 0;
    printf("[Inteiro-dimensão do polígono] s: ");
    if(scanf("%i", &s)!=1) return 0;


    //Computando partições poligonais de um inteiro
    generate_polygonal_partitions(n, 1/*fixo*/, 0/*fixo*/, s);


  //Finalizando a aplicação
  return 0;

} 
