//VAMOS CRIAR UM PROGRAMA QUE GENERALIZA O ALGORITMO DE TONELLI SHANKS PARA POTÊNCIAS DE NÚMEROS PRIMOS

/*
O ALGORITMO DE TONELLI SHANKS ORIGINALMENTE SÓ SE APLICA A EQUAÇÕES DO TIPO x²=a (mod p) COM p PRIMO. É POSSÍVEL
GENERALIZAR ESTE ALGORITMO PARA INTEIROS DO TIPO p^k, COM p PRIMO E k INTEIRO VALENDO-SE DA SEGUINTE PROPOSIÇÃO:
SEJA x UMA SOLUÇÃO DA EQUAÇÃO x²=a (mod p); UMA SOLUÇÃO DA EQUAÇÃO y²= a (mod p^k) TEM A FORMA
y=x^(p^(k-1))*a^([(p^k)-2p^(k-1)+1]/2) (mod p^k).

USANDO ESTE RESULTADO E O TEOREMA DO RESÍDUO CHINÊS PODE-SE ESTENDER O ALGORITMO EM QUESTÃO PARA EQUAÇÕES 
x²=a (mod n), COM n COMPOSTO. 


PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Tonelli–Shanks_algorithm#Generalizations
                          https://exploringnumbertheory.wordpress.com/2022/12/26/finding-square-roots-modulo-a-power-of-an-odd-prime/
                          https://exploringnumbertheory.wordpress.com/2022/12/26/finding-square-roots-modulo-an-odd-composite-number/

*/


//*********************************************************************************************************************
//CABEÇALHO
#ifndef TONELLI_SHANKS_EXTENSION_H
#define TONELLI_SHANKS_EXTENSION_H
#include"tonelli_shanks.h"

//*********************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t tonelli_shanks_extension(int64_t, int64_t, int64_t);

//*********************************************************************************************************************
//FUNÇÕES
//Função que calcula raízes quadradas a menos de uma congruência de uma potência de número primo
int64_t tonelli_shanks_extension(int64_t n, int64_t prime, int64_t power){

  //Caso base: expooente 1
  if(power==1)
    return tonelli_shanks(n, prime);

  //Caso geral:
    //Variáveis locais
    int64_t prime_power=bin_pow(prime, power);
    int64_t exponent = (prime_power-(2*(prime_power/prime))+1)/2;
    __int128_t result1=mod_bin_pow(n, exponent, prime_power);
    __int128_t partial_result=tonelli_shanks(n, prime);
    __int128_t partial_result2=prime-partial_result;
    __int128_t result2=mod_bin_pow(partial_result, (prime_power/prime), prime_power);
    __int128_t result3=mod_bin_pow(partial_result2, (prime_power/prime), prime_power);
    __int128_t final_result=((result1*result2)%prime_power);
    __int128_t final_result2=((result1*result3)%prime_power);



  //Resultado
  if((final_result*final_result)%prime_power==n)
    return final_result;
  else
    return final_result2;


  
                                                                         };

//*********************************************************************************************************************
//FIM DO HEADER
#endif
