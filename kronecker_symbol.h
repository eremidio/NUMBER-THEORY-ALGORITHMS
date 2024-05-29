// VAMOS CRIAR UM PROGRAMA QUE COMPUTA OS CHAMADOS SÍMBOLOS DE KRONECKER PARA INTEIROS

/*
OS SÍMBOLOS DE KRONECKER SÃO GENERALIZAÇÕES (EXTENSÕES) DOS SÍMBOLOS DE LEGENDRE
E DE JACOBI VÁLIDOS PARA TODOS OS NÚMEROS INTEIROS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Kronecker_symbol
                          Elementary Number Theory by Edmund Landau
                          A Course In Computational Algebraic Number Theory by Henri Cohen

*/

//*****************************************************************************************************************************************************************
// CABEÇALHO
#ifndef KRONECKER_SYMBOL_H
#define KRONECKER_SYMBOL_H
#include<stdbool.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdio.h>
#include<assert.h>

//*****************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES

int kronecker(int64_t, int64_t);

//*****************************************************************************************************************************************************************
// FUNÇÕES

// Função que calcula o símbolo de Kronecker (a|n)
int kronecker(int64_t a, int64_t n){

  //Restrição
  assert(n*(-1)==1 || n>=0);

  //Variável global:resultado
  int k=1;

  //Caso base: n= 2
  if(n==2){
    if((a%8)==1 || (a%8)==7)
      return k;
    if((a%8)==3 || (a%8)==5)
      return (-1)*k;
    else
      return 0;
           };

  //Caso base: n=0
  if(n==0){
    if((a*a)==1)
      return k;
    else
      return 0;

          };

  //Caso base: n=1
  if(n==1)
    return k;

  //Caso base: n= -1
  if((-1)*n==1){
    if(a>=0)
      return k;
    else
      return (-1)*k;
             };


  //Caso trivial: a, n são ambos pares 
  if(!(a&1) && !(n&1))
    return 0;

  //Caso geral: usando a lei da reciprocidade quadrática para computar o símbolo de Kronecker de forma eficiente
    //Variáveis locais
    int residue_table[8]={0,1,0, (-1), 0, (-1), 0, 1};
    int64_t b=n;
    int64_t r=0, v=0;


    //Procedimentos

     //TESTE USE /**/ APÓS O MESMO
     /*printf("a:%lu b:%lu\n", a, b);
     for(int x=0; x<8; x++)
      printf("table_entry:%i ", residue_table[x]);
     printf("\n");*/


      step2:
      //Removendo fatores 2 do segundo argumento
      v=0;
      while(!(b&1)){
        v++;
        b>>=1;
                   };

      //Ajuste de variáveis
      if(!(v&1))
        k=1;
      else
        k=residue_table[a&7];

    
      if(a<0) k=(-1)*k;


     //TESTE USE /**/ APÓS O MESMO
     /*printf("a:%lu b:%lu v:%lu k:%d\n", a, b, v, k);*/


       step3:
       //Reduzindo o valor de a (mod b)
       a%=b;

       step4:
      //Condição que determina o fim do algoritmo
      if(a==0 && b>1)
        return 0;
      if(a==0 && b==1)
        return k;

 
      step5:
      //Ajuste de variáveis
      v=0;
      while(!(a&1)){
        v++;
        a>>=1;
                   };

      if((v&1))
       k=residue_table[b&7];

     
      step6:
      r=b-a;
      if(r>=0){

       //Aplicando a lei da reciprocidade quadrática
       if(a&b&2)
        k=(-1)*k;

       //Ajuste de variáveis
       b=a;
       a=r;
               };
     
       if(r<0) a=(-1)*r;



     //TESTE USE /**/ APÓS O MESMO
     /*printf("a:%lu b:%lu v:%lu r:%lu\n", a, b, v, r);*/

     goto step4;


    //Em caso de erro 
    return 2;
                                   };

//*****************************************************************************************************************************************************************
// FIM DO HEADER
#endif
