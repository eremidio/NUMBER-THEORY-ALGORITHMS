//VAMOS CRIAR UM PROGRAMA QUE CALCULA A FUNÇÃO DE MERTENS USANDO UMA VARIANTE DO CRIVO DE ERATÓSTENES

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/mertens_function_recursive.h

*/


//****************************************************************************************************
//CABEÇALHO
#ifndef MERTENS_FUNCTION_SIEVING_H
#define MERTENS_FUNCTION_SIEVING_H
#include"fast_perfect_square_detection.h"
#include<stdlib.h>
#include<stdio.h>



//CONSTANTES GLOBAIS
int32_t prime_buffer[9592];//π(100000)=9592

//****************************************************************************************************
//ESTRTUTURAS USADAS  NO ALGORITMO
struct mertens_pair{
  uint64_t n;//Index
  int mu_n;//μ(n)

};

//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void fill_prime_buffer();
struct mertens_pair* generate_mobius_array(uint64_t);
int64_t mertens_function_sieving(uint64_t, struct mertens_pair[]);


//****************************************************************************************************
//FUNÇÕES
//Função que preenche um buffer de primos até 10^5
void fill_prime_buffer(){

  //Variáveis locais
  FILE* prime_file;
  int32_t prime;
  int counter=0;

  //Procedimentos
    //Abrindo o arquivo para leitura
    prime_file=fopen("prime_list.txt", "r");
   
    //Alocando o buffer de primos
    while(fscanf(prime_file, "%i\n", &prime)!=EOF){
      prime_buffer[counter]=prime;
      counter++; 
      if(counter==9592) break;
    };

    //Fechando o arquivo
    fclose(prime_file);

};



//Função que gera um array de valores (n, μ(n))
struct mertens_pair* generate_mobius_array(uint64_t n){

  //Variáveis locais
  struct mertens_pair* mobius_array=(struct mertens_pair*)calloc((n+1), sizeof(struct mertens_pair));
  uint64_t root;

  //Procedimentos
    //Inicializando os arrays
    mobius_array[0].n=0; mobius_array[0].mu_n=0;   
    mobius_array[1].n=1; mobius_array[1].mu_n=1;   

    for(uint64_t i=2; i<=n; ++i){
      mobius_array[i].n=i;

      if((i&3)==0 || perfect_square_detection_64bits(i, &root)==true || (i%9)==0 || (i%25)==0 || (i%49)==0 || (i%121)==0 || (i%169)==0 || (i%289)==0 || (i%361)==0)
        mobius_array[i].mu_n=0;//Filtrando quadrados perfeitos e números com fatores quadráticos inferiores a 20
      else  mobius_array[i].mu_n=1;   

    };

    //Calculando a função de Möbius no intervalo: loop sobre os primos até 100000
    for(int j=0; j<9592/*π(100000)*/; ++j){

      if(prime_buffer[j]*prime_buffer[j]>n) break;
    
      //Loop sobre os elementos do array
      for(uint64_t k=0; k<=n; ++k){
        if(mobius_array[k].mu_n==0 || mobius_array[k].n<=1) continue;
        if((mobius_array[k].n)%(prime_buffer[j])==0){
          mobius_array[k].n= mobius_array[k].n/prime_buffer[j];
          mobius_array[k].mu_n=(~mobius_array[k].mu_n)+1;
          if((mobius_array[k].n)%(prime_buffer[j])==0){
            mobius_array[k].mu_n=0;
            continue;
          }

        }


      };

    };//Fim do loop principal

    //Ajuste fino da seleção: n contém fatores primos superiores a 100000
    for(uint64_t l=0; l<=n; ++l){
      if(mobius_array[l].n>1) mobius_array[l].mu_n=(~mobius_array[l].mu_n)+1;
    }

  //Resultado
  return mobius_array;

};


//Função que computa a Função de Mertens
int64_t mertens_function_sieving(uint64_t n, struct mertens_pair mobius_array[]){

  // Variáveis locais
  int64_t result = 0;
  int64_t bound=floor(n/3.0);  

  // Procedimento:loop principal
  for (uint64_t i = 1; i <=bound; ++i){
    result += (floor((n-i)/(2.0*i))*mobius_array[i].mu_n);

  }

  // Resultado
  return (-1)*result;
};

//****************************************************************************************************
//FIM DO HEADER
#endif
