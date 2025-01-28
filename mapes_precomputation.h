//VAMOS CRIAR UM PROGRAMA QUE ENLISTA VALORES DA FUNÇÃO φ(m, n) COMPUTADOS USANDO-SE O ALGORITMO DE MAPES


//**********************************************************************************************************************
//CABEÇALHO
#ifndef MAPES_PRECOMPUTATION_H
#define MAPES_PRECOMPUTATION_H
#include<stdio.h>
#include<stdint.h>


//**********************************************************************************************************************
//VARIÁVEIS GLOBAIS
int64_t mapes2[100000];
int64_t mapes3[100000];
int64_t mapes4[100000];
int64_t mapes5[100000];
int64_t mapes6[100000];
int64_t mapes7[100000];
int64_t mapes8[100000];
int64_t mapes9[100000];
int64_t mapes10[100000];
int64_t mapes15[100000];
int64_t mapes20[100000];


//**********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void mapes_precomputation();

//**********************************************************************************************************************
//FUNÇÕES
//Função para alocar valores da função φ(m, n) computados via algoritmo de Mapes
void mapes_precomputation(){

  //Variáveis locais
  FILE* mapes_file2, *mapes_file3, *mapes_file4, *mapes_file5, *mapes_file6, *mapes_file7, *mapes_file8, *mapes_file9, *mapes_file10, *mapes_file15, *mapes_file20;
  int64_t mapes_value, i;

  //Procedimenstos
    //Abrindo arquivos para leitura
    mapes_file2=fopen("mapes2.txt", "r"); mapes_file3=fopen("mapes3.txt", "r"); mapes_file4=fopen("mapes4.txt", "r");
    mapes_file5=fopen("mapes5.txt", "r"); mapes_file6=fopen("mapes6.txt", "r"); mapes_file7=fopen("mapes7.txt", "r");
    mapes_file8=fopen("mapes8.txt", "r"); mapes_file9=fopen("mapes9.txt", "r"); mapes_file10=fopen("mapes10.txt", "r");
    mapes_file15=fopen("mapes15.txt", "r"); mapes_file20=fopen("mapes20.txt", "r");

    //Carregando os dados nos arrays (variáveis globais)
    i=0;
    while(fscanf(mapes_file2, "%li\n", &mapes_value)!=EOF){
      mapes2[i]=mapes_value;
      ++i;
    }

    i=0;
    while(fscanf(mapes_file3, "%li\n", &mapes_value)!=EOF){
      mapes3[i]=mapes_value;
      ++i;
    }

    i=0;
    while(fscanf(mapes_file4, "%li\n", &mapes_value)!=EOF){
      mapes4[i]=mapes_value;
      ++i;
    }

    i=0;
    while(fscanf(mapes_file5, "%li\n", &mapes_value)!=EOF){
      mapes5[i]=mapes_value;
      ++i;
    }


    i=0;
    while(fscanf(mapes_file6, "%li\n", &mapes_value)!=EOF){
      mapes6[i]=mapes_value;
      ++i;
    }


    i=0;
    while(fscanf(mapes_file7, "%li\n", &mapes_value)!=EOF){
      mapes7[i]=mapes_value;
      ++i;
    }

    i=0;
    while(fscanf(mapes_file8, "%li\n", &mapes_value)!=EOF){
      mapes8[i]=mapes_value;
      ++i;
    }


    i=0;
    while(fscanf(mapes_file9, "%li\n", &mapes_value)!=EOF){
      mapes9[i]=mapes_value;
      ++i;
    }


    i=0;
    while(fscanf(mapes_file10, "%li\n", &mapes_value)!=EOF){
      mapes10[i]=mapes_value;
      ++i;
    }

    i=0;
    while(fscanf(mapes_file15, "%li\n", &mapes_value)!=EOF){
      mapes15[i]=mapes_value;
      ++i;
    }

    i=0;
    while(fscanf(mapes_file20, "%li\n", &mapes_value)!=EOF){
      mapes20[i]=mapes_value;
      ++i;
    }
   

    //Fechandos os arquivos
    fclose(mapes_file2); fclose(mapes_file3); fclose(mapes_file4);
    fclose(mapes_file5); fclose(mapes_file6); fclose(mapes_file7);
    fclose(mapes_file8); fclose(mapes_file9); fclose(mapes_file10);
    fclose(mapes_file15); fclose(mapes_file20);

};


//**********************************************************************************************************************
//FIM DO HEADER
#endif
