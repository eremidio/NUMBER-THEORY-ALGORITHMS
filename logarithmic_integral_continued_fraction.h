//VAMOS CRIAR UM PROGRAMA QUE CALCULA APROXIMAÇÕES PARA A FUNÇÃO INTEGRAL LOGARÍTMICA li(x) USANDO EXPANSÃOEM FRAÇÕES CONTINUADAS

/*
PARA MAIORES INFORMAÇÕES: https://mathoverflow.net/questions/391747/continued-fraction-for-logarithmic-integral
                          https://link.springer.com/content/pdf/bbm:978-94-91216-37-4/1
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/continuedfractions.f90

*/



//***********************************************************************************************************************************
//CABEÇALHO
#ifndef LOGARITHMIC_INTEGRAL_CONTINUED_FRACTION_H
#define LOGARITHMIC_INTEGRAL_CONTINUED_FRACTION_H
#include<stdlib.h>
#include<math.h>



//***********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
long double logarithmic_integral_continued_fraction(long double);

//***********************************************************************************************************************************
//FUNÇÕES
//Função que calcula a função integral logarítmica li(x) usando frações continuadas
long double logarithmic_integral_continued_fraction(long double x){

  //Variáveis locais
  long double num[11]={x,1,4,9,16,25,36,49,64,81,100};
  long double den[11]={1,3,5,7,9,11,13,15,17,19,21};
  long double logx=log(x);
  long double partial=(num[10]/(logx-den[10]));
  

  //Procedimentos
    //Calculando a aproximação da fração continuada de da função li(x)
    for(int i=9; i>=0; --i) partial=num[i]/(logx-den[i]-partial);

    //Resultado
    return partial;
  

};

//***********************************************************************************************************************************
//FIM DO HEADER
#endif
