//VAMOS CRIAR UM PROGRAMA QUE COMPUTA UM LIMITANTE SUPERIOR PARA O NÚMERO DE PRIMOS GÊMEOS EM UM INTERVALO

/*

NÚMEROS PRIMOS GÊMEOS SÃO NÚMEROS PRIMOS DIFERINDO POR DUAS UNIDADES, POR EXEMPLO, OS PARES (71,73) E (101,103) SE ENQUADRAM
NESSA CATEGORIA.

USANDO A CHAMADA PENEIRA DE SELBERG, QUE PERMITE ESTIMATIVAS RAZOÁVEIS DE CONJUNTOS DE INTEIROS FILTRADOS DE ACORDO COM ALGUM 
CRITÉRIO ESPECIFÍCO POR MEIO DE FUNÇÕES ARTIMÉTICAS MULTIPLICATIVAS RAZOAVEMENTE BEM COMPORTADAS, PODE-SE DEMONSTRAR O
SEGUINTE TEOREMA:

TEOREMA (DE BRUN): O NÚMERO DE PRIMOS GÊMEOS EM UM CERTO INTERVALO [x, x+y] COM x, y INTEIROS É LIMITADO SUPERIORMENTE PELA
QUANTIDADE Q={(8y)/log²(y)C}+ O({ylog(log(y))}/{log³(y)}), ONDE C=(1/2)Π{p(p-2)}/{(p-1)²}, ONDE O PRODUTO É FEITO SOBRE O 
CONJUNTOS DOS NÚMEROS PRIMOS.

COMO UMA CONSEQUÊNCIA DESTE TEOREMA TEMOS:
COROLÁRIO: A SOMA DOS RECÍPROCOS DOS NÚMEROS PRIMOS GÊMEOS CONVERGE.

A DEMONSTRAÇÃO DO TEOREMA E DO COROLÁRIO ESTÃO DISPONÍVEIS NO ARTIGO: https://web.math.princeton.edu/~gyujino/Selbergsieve.pdf

A CONSTANTE C QUE APARECE NO TEOREMA ACIMA É DENOMINADA CONSTANTE DE PRIMOS GÊMEOS. SEU VALOR POR SER ESTIMADO CALCULANDO-SE
PRIMEIRO log(C) NO LUGAR DE C DIRETAMENTE, DESTA FORMA O PRODUTÓRIO SE CONVERTE EM UM SOMATÓRIO. TAL FÓRMULA PODE SER MANIPULADA
ALGEBRICAMENTE DE MODO A SE OBTER: log(C/2)=Σ [{(2^j)-2}/j]Σ(p^j), ONDE j=1,2,3,... E p INCLUI TODOS OS NÚMEROS PRIMOS MAIORES
QUE 2. A SEGUNDA SOMA PODE SER APROXIMADA PELA RELAÇÃO Σ(p^j)= P(s)-(2^s), ONDE P(s) É A FUNÇÃO ZETA PRIMO. ESTAS RELAÇÕES
PODEM SER USADAS PARA SE ESTIMAR O NÚMERO DE PRIMOS GÊMEOS EM UM INTERVALO COM ALTO GRAU DE PRTECESÃO A MEDIDA QUE INTEVALOS 
MAIORES SÃO CONSIDERADOS.

CONSIDERAÇÕES COMO AS DISCUTIDAS ACIMA REMONTAM AO TRABALHO DE HARDY-LITLEWOOD E PODEM SER ESTENDIDOS A CONSTELAÇÕES VÁLIDAS
DE NÚMEROS PRIMOS COMO: (p, p+2, p+6), (p, p+4, p+6), (p, p+2, p+6, p+8), ENTRE OUTROS. RESULTADOS EXPERIMENTAIS COMPROVAM A 
VALIDADE DA ESTIMATIVAS COM TÉCNICAS DE CRIVOS COMO AS PENEIRAS DE BRUN, SELBERG, ENTRE OUTRAS.


PARA MAIORES INFORMAÇÕES: https://web.math.princeton.edu/~gyujino/Selbergsieve.pdf
                          Prime Numbers And Computer Methods For Factorization, by Hans Riesel


*/


//*******************************************************************************************************************************
//CABEÇALHO
#ifndef TWIN_PRIME_CONJECTURE_H
#define TWIN_PRIME_CONJECTURE_H
#include"prime_zeta_function.h"


//*******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
long double compute_prime_twin_constant();
long double compute_twin_prime_pair_limit(long double);
long double compute_error_term(long double);


//*******************************************************************************************************************************
//FUNÇÕES
//Função que computa a constante dos primos gêmeos
long double compute_prime_twin_constant(){

  //Variáveis
  long double log_twin_prime_constant=0.0;
  long double power2=0.0, prime_sum=0.0, partial=0.0, prime_zeta=0.0;
  int64_t i;

  
  //Procedimentos
    //Loop principal
    for(i=2; ; ++i){
      
      prime_zeta=prime_zeta_function(i);
      if(prime_zeta<PRIME_ZETA_EPSILON) break;

      power2= pow(2, i);
      prime_sum=prime_zeta-(1.0/power2);

      log_twin_prime_constant=log_twin_prime_constant-((power2-2)/i)*prime_sum;

    };//Fim do loop principal

    //Cálculo do resultado
    long double C=2*exp(log_twin_prime_constant);


  //Resultado
  return C;

};


//Função que estima o número de constelações de primos gêmeos (p, p+2) em um intervalo
long double compute_twin_prime_pair_limit(long double L){

  //Variáveis locais
  long double twin_prime_constant=compute_prime_twin_constant();
  long double logL=log(L); 

  //Resultado
  return ((2.0*L)/(twin_prime_constant*logL*logL));

};


//Função que estima o erro da contagem de contelação de primos gêmeos
long double compute_error_term(long double L){

  //Variáveis locais
  long double logL=log(L), loglogL=log(logL);

  //Resultado
  return (L*loglogL)/(logL*logL*logL); 

};


//*******************************************************************************************************************************
//FIM DO HEADER
#endif
