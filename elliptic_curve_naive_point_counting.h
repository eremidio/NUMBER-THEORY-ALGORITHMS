//VAMOS CRIAR UM PROGRAMA QUE COMPUTA PONTOS EM CURVAS ELÍPTICAS USANDOS OS ALGORITMOS DE FORÇA BRUTA

/*
CURVAS ELÍPTICAS SÃO CURVAS SATISFAZENDO CERTAS EQUAÇÕES CÚBICAS SOBRE CORPOS NÚMERICOS. CURVAS ELÍPTICAS PODEM SER EXPRESSAS POR DISTINTAS
PARAMETRIZAÇÕES, NA CHAMADA FORMA NORMAL REDUZIDA DE WEIERSTRASS ELAS SÃO DESCRITAS PELA EQUAÇÃO: y²=x³+ax+b. DEFININDO-SE UMA OPERAÇÃO DE
ADIÇÃO DE PONTOS NA CURVA (QUE VARIA DE ACORDO COM A PARAMETRIZAÇÃO ADOTADA), PODE-SE PROVAR QUE PONTOS EM UMA CURVA ELÍPTICA FORMAM UM
GRUPO ABELIANO COM RESPEITO A ESTA OPERAÇÃO.

DE GRANDE INTERESSE PARA APLICAÇÕES EM TEORIA DE NÚMEROS, CRIPTOGRAFIA E AFINS É DETERMINAR O NÚMERO DE PONTOS EM UMA CURVA SOBRE UM CORPO
FINITO (POR EXEMPLO, F(p) INTEIROS A MENOS DE UMA CORNGRUÊNCIA MÓDULO p), TAL VALOR É DENOMINADO ORDEM DA CURVA E DENOTADO #E(p) NO CASO DE
UM CORPO NÚMERICO F(p). É IMPORTANTE SALIENTAR QUE OS CASOS p=2,3 SÃO TRATADOS A PARTE, POIS A EXPRESSÃO MATEMÁTICA PARA UMA CURVA ELÍPTICA
SOBRE OS CORPOS NÚMERICOS GF(2), GF(3) É LIGEIRAMENTE MAIS COMPLICADA.


ALGORITMO COMO A FATORAÇÃO VIA CURVAS (NA VERDADE PSEUDOCURVAS) ELÍPTICAS E O TESTE DE PRIMALIDADE USANDO CURVAS ELÍPTICAS DEPENDEM DO VALOR
DO PARÂMETRO #E(p) E DE PROPRIEDADES A ELE RELACIONADAS (COMO O FATO DESTE VALOR SER COMPLETAMENTE DESCOMPOSTO EM RELAÇÃO A UMA PEQUENA BASE
DE NÚMEROS PRIMOS). PORTANTO ESTIMATIVAS DESSE VALOR SÃO DE GRANDE INTERESSE PRÁTICO, OS SEGUINTES TEOREMAS SÃO ÚTEIS EM ANÁLISES 
ESTATÍSTICAS ACERCA DA EXISTÊNCIA DE CURVAS ELÍPTICAS COM CUJA ORDEM #E(p) ESTÁ DENTRO DE UM DETERMINADO VALOR.

TEOREMA DE HASSE: A ORDEM DE UMA CURVA ELPITICA #E(p) ESTÁ SITUADO NO INTERVALO (INTERVALO DE HASSE) [p+1-2√p, p+1+2√p].
TEOREMA DE DEURING: DADO UM INTEIRO m NO INTERVALO DE HASSE [p+1-2√p, p+1+2√p] O NÚMERO DE CURVAS COM ORDEM m A MENOS DE UM ISOMORFISMO É
IGUAL A k(p,m)=(p+1-m)²-4m (NÚMERO DE CLASSE DE KRONECKER).


DADO UMA CURVA ELÍPTICA DE GRANDE INTERESSE É COMPUTAR UM PONTO NA CURVA EM QUESTÃO, UM TEOREMA DEVIDO A LENSTRA (VER REFERÊNCIAS) FORNECE
UMA NOÇÃO  ESTATÍSTICA DA DISTRIBUIÇÃO NÃO SOMENTE DO NÚMERO DE CURVAS (CADA CURVA CORRESPONDE A UM PAR DE PARÂMETROS (a,b)) CUJA ORDEM SE
SITUA EM UM DADO CONJUNTO NÚMÉRICO, MAS TAMBÉM DO NÚMERO DE ESCOLHA DE DISTINTAS PARAMETRIZAÇÕES FIXADO UM PONTO NA CURVA.

NO PRESENTE PROGRAMA VAMOS IMPLEMENTAR O ALGORITMO DE FORÇA BRUTA QUE USA CLASSES RESIDUAIS QUADRÁTICAS PARA ORDENS PEQUENAS (p<10000). O 
ALGORITMO DE CONTAGEM DE FORÇA BRUTA BASEIA-SE NO SEGUINTE PRINCÍPIO: SEJA A EQUAÇÃO DE UMA CURVA ELÍPTICA y²=x³+ax+b (mod p), PARA CADA
VALOR DE x, HAVERÁ DUAS SOLUÇÕES POSSÍVEIS PARA y SE E SOMENTE SE (x³+ax+b) FOR UMA CLASSE RESÍDUAL QUADRÁTICA MÓDULO p, TAL RACIOCÍNIO
NOS CONDUZ A SEGUINTE FÓRMULA: #E(p)=(p+1)+Σ([x³+ax+b]|p), ONDE (|) DENOTA O SÍMBOLO DE LEGENDRE.

ESTA FÓRMULA É EXATA, PORÉM SEU USO SÓ É VANTAJOSO PARA PEQUENOS VALORES DE p. PARA GRANDES VALORES DE p, ESQUEMAS MAIS EFICIENTES COMO
O ALGORITMO DE SHANKS-MESTRE E O ALGORITMO DE SCHOOF DEVEM SER EMPREGADOS.


PARA MAIORES REFERÊNCIAS: Prime Numbers. A Computational Perspective by R.Crandall & Carl B. Pomerance
                          https://www.wstein.org/projects/168/neal_harris/project.pdf
                          https://en.wikipedia.org/wiki/Counting_points_on_elliptic_curves

*/

//*********************************************************************************************************************************************************
//CABEÇALHOS
#ifndef NAIVE_ELLIPTIC_CURVE_POINTING_COUNTING_H
#define NAIVE_ELLIPTIC_CURVE_POINTING_COUNTING_H
#include"mod_bin_exponentiation.h"
#include<assert.h>


//*********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int legendre(int64_t, int64_t);
int64_t elliptic_curve_point_counting(int64_t, int64_t, int64_t);

//*********************************************************************************************************************************************************
//FUNÇÕES
//Função que calcula o símbolo de Legendre usando o critério de Euler
int legendre(int64_t n, int64_t p){

  if((n%p)==0) return 0;
  else if(mod_bin_pow(n, ((p-1)/2), p)==1) return 1;
  else return (-1);

};

//Função que computa o número de pontos em uma curva elíptica módulo um primo pequeno
int64_t elliptic_curve_point_counting(int64_t a, int64_t b, int64_t p){

  //Restrição
  assert(p<1e6 && a<p && b<p);

  //Variáveis locais
  int64_t sum=(p+1);
  int64_t numerator;

    //Procedimentos
      //Loop principal sobre elementos em GF(P) inteiros a menos de uma congruência mod p
      for(int64_t x=0; x<p; ++x){
        numerator=(x*x*x)+(a*x)+b;
        sum+=legendre((numerator%p), p);
        
      }


  //Resultado
  return sum;

};


//*********************************************************************************************************************************************************
//FIM DO HEADER
#endif
