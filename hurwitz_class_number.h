//CVAMOS CRIAR UM PROGRAMA QUE COMPUTA O NÚMERO DE CLASSE DE HURWITZ PARA CORPOS QUADRÁTICOS IMAGINÁRIOS

/*

O NÚMERO DE CLASSE DE HURWITZ DENOTADO POR H(N) É UM INVARIANTE ALGÉBRICO RELACIONADO AO NÚMERO DE CLASSE USUAL
h(d) DE UM CORPO ALGÉBRICO NÚMERICO. ESTE INVARIANTE É DEFINIDO DA SEGUINTE FORMA: PARA N=1,2 (mod 4) H(N)=0;
H(0)=(-1/12); PARA N=2,3 (mod 4), H(N) É IGUAL AO NÚMERO DE CLASSE h(-N) DE FORMAS NÃO NECESSARIAMENTE 
PRIMITIVAS DE FORMAS QUADRÁTICAS COM A RESTRIÇÃO QUE FORMAS QUADRÁTICAS EQUIVALENTES A a(x²+y²) TEM PESO 1/2 E 
FORMAS QUADRÁTICAS EQUIVALENTES A a(x²+xy+y²) TEM PESO 1/3.

DEFININDO h(D) O NÚMERO DE CLASSE ASSOCIADO A FORMAS QUADRÁTICAS POSITIVA DEFINIDAS COM A RESTRIÇÃO h(D)=0 SE
D = 0,1 (mod 4). INTRODUZINDO A DEFINIÇÃO w(-3)=6, w(-4)=4 E w(D)=2 SE D<(-4), h'(D)=h(D)/(w(D)/2) TEMOS
Η(D) = Σ h'(N/d²), ONDE O SOMATÓRIO É FEITO SOBRE TODOS OS VALORES DE d² DIVIDINDO N, SE -N FOR UM DISCRIMANTE
FUDAMENTAL h'(-N) = H(N). USANDO A FÓRMULA DE INVERSÃO DE MÖBIUS TEMOS QUE h'(D) = Σ μ(d)H(N/d²).

DAS CONSIDERAÇÕES ANTERIORES É EVIDENTE QUE COMPUTAR UMA TABELA DE h(D) OU DE H(D) SÃO DOIS PROBLEMAS
EQUIVALENTES. O PROCESSO DE CONTAGEM DE FORMAS QUADRÁTICAS REDUZIDAS PODE SER ADAPTADO PARA COMPUTAR H(D) E O 
NÚMERO DE CLASSE DO GRUPO DE FORMAS QUADRÁTICAS DE DISCRIMINANTES FUDAMENTAIS h(D) PODE SER RECUPERADO POR MEIO
DAS FÓRMULAS ACIMA.


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen


*/ 


//***************************************************************************************************************
//CABEÇALHO
#ifndef HURWITZ_CLASS_NUMBER_H
#define HURWITZ_CLASS_NUMBER_H
#include<stdint.h>
#include<stdbool.h>
#include<math.h>


//***************************************************************************************************************
//ESTRUTURAS E FUNÇÕES USADAS NO ALGORITMO
//Função que computa o mdc de dois inteiros de 64 bits
int64_t gcd_hurwitz(int64_t a, int64_t b){
  if(b<0) b=(-b);   if(a<0) a=(-a);
  if(b==0) return a;
  else return gcd_hurwitz(b, (a%b));

};

//Estrutura usada para computar o número de classe de Hurwitz
struct hurwitz_fraction{
  int64_t num;
  int64_t den;

};

//Constantes
struct hurwitz_fraction hurwitz_one={1,1};
struct hurwitz_fraction hurwitz_zero={0,1};

//Função que soma duas frações
struct hurwitz_fraction hurwitz_fraction_add(struct hurwitz_fraction h1, struct hurwitz_fraction h2){

  //Variáveis locais
  struct hurwitz_fraction h3;

  
  //Procedimentos
    //Cálculo do denominador e numerador
    h3.den=h1.den*h2.den;
    h3.num=(h1.num*h2.den)+(h1.den*h2.num);

    int64_t ratio=gcd_hurwitz(h3.den, h3.num);
    if(ratio>1){
      h3.den/=ratio; h3.num/=ratio;
    };

  //Resultado
  return h3;

};  

//Função que subtrai duas frações
struct hurwitz_fraction hurwitz_fraction_sub(struct hurwitz_fraction h1, struct hurwitz_fraction h2){

  //Variáveis locais
  struct hurwitz_fraction h3;

  
  //Procedimentos
    //Alterando o sinal da 2ª parcela
    h2.num*=(-1);

  //Resultado
  return hurwitz_fraction_add(h1, h2);

};  


//***************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
struct hurwitz_fraction hurwitz_class_number_reduced_forms(int64_t);


//***************************************************************************************************************
//FUNÇÕES
//Função que computa o número de classe de Hurwitz usando contangem de formas quadráticas primitivas
struct hurwitz_fraction hurwitz_class_number_reduced_forms(int64_t N){

  //Casos bases 
  if(N==0){
    struct hurwitz_fraction H={-1, 12};
    return H;
  };

  if(N==3){
    struct hurwitz_fraction H={1,3};
    return H;
  };

  if(N==4){
    struct hurwitz_fraction H={1,2};
    return H;
  };

  if(N&3==1 || N&3==2) return hurwitz_zero;

  //CASO GERAL:
  //Variáveis locais
  struct hurwitz_fraction H=hurwitz_zero, adder;
  int64_t D=(-N);
  int64_t B=floor(sqrt((N/3.0)));
  int64_t a, b, c;


  //Procedimentos
    //Loop principal:contagem de formas reduzidas
    for(b=(N&1); b<=B; b+=2){

      //Inicializando variáveis
      a=b;
      if(a<=1) a=1;

     //Loop secundário sobre possiveis valores de a
     for(; a<=B; a++){
       c=round(((b*b)-D)/4.0);

       if((a*a)<c){
         if((c%a)==0){

           //Caso 1: a=b
           if(a==b){
              if(c==a*b){
                adder.num=1; adder.den=3;
                H=hurwitz_fraction_add(H, adder);
              }
              else H=hurwitz_fraction_add(H,hurwitz_one);
           }        

           //Caso 2: a²=q
           else if((a*a)==c){
             if(b==0){
               adder.num=1; adder.den=2;
               H=hurwitz_fraction_add(H, adder);
             }
             else H=hurwitz_fraction_add(H,hurwitz_one);
           }
          
           //Caso 3:
           else{
             adder.num=2; adder.den=1;
             H=hurwitz_fraction_add(H, adder);
             
           };

         };
       };
  
     };
  


    };//Fim do loop principal


  //Resultado
  return H;

};

//***************************************************************************************************************
//FIM DO HEADER
#endif
