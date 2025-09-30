//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR GAPS ENTRE PRIMOS EM UM DADO INTERVALO PARA INTEIROS DE 64 BITS 

/*

A FUNÇÃO DE GAP ENTRE PRIMOS g(n) É UMA FUNÇÃO ARITMÉTICA DEFINIDA PELA RELAÇÃO g(n)=p(n+1)-p(n), ONDE p(n+1) E p(n) DENOTAM RESPECTIVAMENTE OS (n+1) E
n-ÉSIMOS PRIMEIROS NÚMEROS PRIMOS, POR EXEMPLO, TEMOS QUE p(1)=2, p(2)=3, p(3)=5, p(4)=7, p(5)=11, p(6)=13, p(7)=17, p(8)=19, ETC; ASSIM g(1)=1, g(2)=2,
g(3)=2, g(4)=4, g(5)=2, g(6)=4, g(7)=2 E ASSIM SUCESSIVAMENTE. TAL FUNÇÃO ARIMÉTICA NÃO É ADITIVA E NEM MULTIPLICATIVA.

g(n) ESTÁ RELACIONADA A DISTRIBUIÇÃO DE PRIMOS NO CONJUNTO DOS INTEIROS CAPTURANDO APARENTES IRREGULARIDADES NA DISTRIBUIÇÃO DOS MESMO. VÁRIOS RESULTADOS
ELEMENTARES PODEM SER PROVADOS ACERCA DO VALOR MÉDIO DE TAL FUNÇÃO. DE GRANDE INTERESSE TEÓRICO SÃO ESTIMATIVAS QUANTOS AOS VALORES MÁXIMOS E MÍNIMOS
DESTA FUNÇÃO PARA n-> ∞. RESULTADOS DATANDO DE 2013 PARA CÁ (YITANG-ZHANG/MATH PROJECT) ESTABELECEM UNIVOCAMENTE QUE O ÍNFIMO DE g(n) É IGUAL A 246. COM
ALGUMAS CONJECTURAS ADICIONAIS (ELLIOT-HALBERSTAM) ESTE VALOR É REDUZIDO PARA 16 OU 6 (NA VERSÃO GENERALIZADA DESTA CONJECTURA). OS SUPREMOS DA FUNÇÃO
g(n) SÃO TAMBÉM DE GRANDE INTERESSE TEÓRICO E UM TEOREMA DE ËRDOS (CUJA ESTIMATIVA INICIAL FOI APRIMORADA) ESTABELECE QUE NO LIMITE n-> ∞, A SEGUINTE
IDENTIDADE É VALIDA: sup g(n)> c{ln(n).ln(ln(n).ln(ln(ln(ln(n))))}/{ln(ln(ln(n)))}, ONDE c É UMA CONSTANTE QUE PODE SER TOMADA ARBRITARIAMENTE GRANDE
PARA DADOS VALORES DE n.

A FUNÇÃO Δ(n)=g(n)/ln(n) É CHAMADA DE FUNÇÃO MÉRITO DE g(n), SE CONJECTURAS ACERCA DE g(n) COMO A CONJECTURA DA EXISTÊNCIA DE INFINITOS NÚMEROS PRIMOS 
GÊMEOS EXISTIR ENTÃO NO LIMITE n-> ∞ TEM-SE QUE inf Δ(n)=0. 

VÁRIOS MODELOS PROBALÍSTICOS DA OCORRÊNCIA DE NÚMEROS E TÉCNICAS AVANÇADAS DA TEORIA DE CRIVOS SÃO USADAS PARA ESTUDAR O COMPORTAMENTO DA FUNÇÃO g(n) E 
ALGUNS LIMITES ASSINTÓTICOS PODEM SER PROVADOS POR MEIOS DE TAIS TÉCNICAS. AINDA SIM UMA DESCRIÇÃO PRECISA DO COMPORTAMENTO DESTA FUNÇÃO, SEUS VALORES
MÉDIOS PARA UM DADO n, LIMITANTES SUPERIORES E INFERIORES MAIS PRECISOS AINDA PERMANECEM EM ABERTO, MUITOS RESULTADOS AINDA SÃO APENAS CONJECTURAS.
POR ESTA RAZÃO UMA DAS FERRAMENTAS MAIS EFICAZES NA DETERMINAÇÃO DO COMPORTAMENTO DE g(n), CONSISTE NO ESTUDO DE PRIMOS E PROVÁVEIS PRIMOS EM INTERVALOS
SELECIONADOS E NA COMPARAÇÃO DE EXPERIMENTOS NUMÉRICOS COM OS RESULTADOS CONJECTURADOS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Prime_gap#
                          https://en.wikipedia.org/wiki/Cramér%27s_conjecture
                          https://en.wikipedia.org/wiki/Goldston–Pintz–Yıldırım_sieve
                          https://en.wikipedia.org/wiki/Elliott–Halberstam_conjecture
                          https://campus.lakeforest.edu/trevino/SIDIM2014.pdf
                          https://mathworld.wolfram.com/PrimeGaps.html
                          https://annals.math.princeton.edu/wp-content/uploads/annals-v179-n3-p07-p.pdf
                          https://math.mit.edu/~drew/PrimeGaps.pdf
                          http://lolathompson.com/uploads/1/1/0/6/110629329/cologne_talk.pdf
                          https://ford126.web.illinois.edu/wwwpapers/primegaps.pdf
                          https://icmu.ua/f/240358/x/2a4eb35b21/numbers-in-the-universe-tao-course-notes.pdf
                          https://maths-people.anu.edu.au/~hansons/Talks/gaps%20between%20primes.pdf
                          
*/


//*************************************************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_GAPS_64BITS_H
#define PRIME_GAPS_64BITS_H
#include"pseudosquare_number.h"
#include<stdlib.h>


//CONSTANTES GLOBAIS
const int mod30[30]={0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1};


//*************************************************************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO
//Estrutura que aloca o gap entre dois números primos
struct prime_gap_register{

  int64_t lower_prime;
  int64_t upper_prime;
  int prime_gap;

};

//*************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t* prime_sieving(int64_t, int64_t, int64_t*);
struct prime_gap_register* compute_prime_gaps(int64_t[], int64_t, int64_t*);


//*************************************************************************************************************************************************************
//FUNÇÕES
//Função que computa um array contendo números primos em um dado intervalo
int64_t* prime_sieving(int64_t lower_bound, int64_t upper_bound, int64_t* interval_size){
  
  //Restrição
  assert(lower_bound>=30 && upper_bound<pss_pairs[1].least_solution);


  //Ajuste de variáveis
  (*interval_size)=upper_bound-lower_bound+1;
  int64_t N=(*interval_size);

  //Variáveis locais
  int64_t* interval=(int64_t*)calloc(N*2, sizeof(int64_t));
  int64_t n=0, index;

  //Procedimentos
    //Loop principal
    for(int i=0, j=lower_bound; i<30; ++i, ++j){
      //Ajuste de variáveis
      n=j;
      index=i;
      
      //Teste de classe residual módulo 30
      if(mod30[n%30]==0) continue;

      //Preenchendo um buffer de primos em um intervalo
      while(n<upper_bound){

        //Teste de primalidade: teste de Fermat na base2 e teste de classes residuais pseudoquadráticas
        if(mod_bin_pow(2, (n-1), n)==1 && pseudosquare_primality_testing(n))
          interval[index]=n;
        
        //Ajuste de variáveis
        n+=30;
        index+=30;
        if(index>(*interval_size)) break;

      };//Fim do loop de preenchimento de buffers para uma única classe residual
      

    };//Fim do loop principal

  
  //Resultado
  return interval;

};


//Função que computa gaps de primos em um intervalo
/*
    NOTA: Estritamente falando não estamos computando g(n) definido acima, mas sim o valor de g(n+π(n)), onde π(n) é 
          o número de primos de 2 até o início do intervalo de busca selecionado.
*/
struct prime_gap_register* compute_prime_gaps(int64_t sifted_interval[], int64_t interval_size, int64_t* register_size){

  //Variáveis locais
  struct prime_gap_register* primes_gap_array=NULL;
  int64_t lower_index=0, upper_index=0, first_index=0;
  int64_t prime_gap_size=0;


  //Procedimentos
    //Determinando o primeiro primo no intervalo
    for(int64_t i=0; i<interval_size; ++i){
      if(sifted_interval[i]>0){
        first_index=i; lower_index=first_index;
        break;
      }
    };

    //Loop principal
    for(int64_t i=first_index; i<interval_size; ++i){

       if(sifted_interval[i]>0){
         upper_index=i;
         prime_gap_size++;
         primes_gap_array=(struct prime_gap_register*)realloc(primes_gap_array, prime_gap_size*sizeof(struct prime_gap_register));

         primes_gap_array[prime_gap_size-1].lower_prime=sifted_interval[lower_index];
         primes_gap_array[prime_gap_size-1].upper_prime=sifted_interval[upper_index];
         primes_gap_array[prime_gap_size-1].prime_gap=primes_gap_array[prime_gap_size-1].upper_prime-primes_gap_array[prime_gap_size-1].lower_prime;

         //Atualizando variáveis para o próxima iteração
         lower_index=upper_index;
       }

    };//Fim do loop principal

  
  //Resultado
  (*register_size)=prime_gap_size;
  return primes_gap_array;

};

//*************************************************************************************************************************************************************
//FIM DO HEADER
#endif
