//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CURVAS ELIPTICAS PARA FATORAR NÚMEROS INTEIROS  

/*

O MÉTODO DE FATORAÇÃO USANDO CURVAS ELÍPTICAS USA O FATO QUE EM CERTOS TIPOS DE CURVAS UMA OPERAÇÃO GEOMÉTRICA DE ADIÇÃO DE PONTOS E MULTIPLICAÇÃO
DE UM PONTO POR UM ESCALAR DEFINE UMA ESTRUTURA QUE É UM GRUPO (ESTRUTURA ALGÉBRICA).

A IDEIA FUNDAMENTAL É CONSIDERAR CURVAS DEFINIDAS PELA EQUAÇÃO y²=x³+ax+b (NA FORMA NORMAL REDUZIDA DE WEIERSTRASS) COM a E b REAIS SOBRE Z/nZ
(INTEIROS COM AS OPERAÇÕES USUAIS A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA). NESTE CONTEXTO A CURVA EM QUESTÃO PASSA A TER UM  NÚMERO FINITO DE
ELEMENTOS, INCLUINDO UM PONTO NO INFINITO - DENOTADO POR o. A EQUAÇÃO PARA CURVAS ELÍPTICAS NA FORMA NORMA DE WEIERSTRASS É PARTICULAMENTE POR
ESTABELECER UMA RELAÇÃO DIRETA ENTRE A TEORIA DE CURVAS ELÍPTICAS E A TEORIA DE FORMAS MODULARES.

PARAMETRIZAÇÕES DIFERENTES PODEM SER ADOTADAS PARA CURVAS ELÍPTICAS, PARA CADA PARAMETRIZAÇÃO É POSSÍVEL DEFINIR UMA REGRA DE ADIÇÃO DE PONTOS NA
CURVA QUE DEFINE A ESTRUTURA DO GRUPO ASSOCIADO. É POSSÍVEL MOSTRAR A EQUIVALÊNCIA ENTRE AS DIVERSAS REPRESENTAÇÕES DIFERENTES.

DE PARTICULAR INTERESSE PARA O MÉTODO DE FATORAÇÃO DE CURVAS ELÍPTICAS É A PARAMETRIZAÇÃO DE EDWARDS QUE DEFINE CURVAS ELÍPTICAS POR MEIO DA
EQUAÇÃO x²+y²=1+dx²y², PONTOS NA CURVA SÃO REPRESENTADOS POR UM PAR ORDERNADO P=(x, y). A REGRA DE ADIÇÃO DE PONTO É DEFINIDA POR
(x1, y1)+(x2, y2) -> ({x1y2+x2y1}/{1+dx1y1x2y2}, {y1y2-ax1x2}/{1-dx1y1x2y2}), UM PONTO É INVERTIDO EM RELAÇÃO AO EIXO POR MEIO DA RELAÇÃO
(x,y) -> (-x, y), O ELEMENTO NEUTRO DO GRUPO É O PONTO (0,1). CURVAS DE EDWARDS SÃO ADEQUADAS NESSE CASSO DEVIDO AO FATO DE SER POSSÍVEL ESCOLHER
PARAMETRIZAÇÕES TAIS QUE O GRUPO DE TORSÃO (SUBGRUPO DE PONTOS EM QUE TODOS OS ELEMENTOS TEM ORDEM FINITA) DA CURVA ELÍPTICA SEJA 'SUFICIENTEMENTE
GRANDE', O QUE FAVORECE A BUSCA POR FATORES PRIMOS QUANDO A ORDEM DO GRUPO #GF(n) É COMPOSTO (NESTE CASO A REGRA DE ADIÇÃO DE PONTOS NÃO DEFINE UM
GRUPO NO SENTIDO ESTRITO DO TERMO - INVERSÕES MODULARES PODEM REVELAR FATORES PRIMOS DO NÚMERO n).


O ALGORITMO DE FATORAÇÃO USANDO CURVAS ELÍPTICAS É UMA GENERALIZAÇÃO DO MÉTODO DE POLLARD RHO (p-1), SENDO O MAIS SOIMPLES DOS MÉTODOS DE FATORAÇÃO
DE NÚMEROS QUE EXPLORA A ORDEM DE GRUPOS ABELIANOS ALGÉBRICOS.


PARA MAIORES INFORMAÇÕES: https://medium.com/@gaelfoppolo/elliptic-curve-cryptography-ecc-6af6142b0dd1
                          https://en.wikipedia.org/wiki/Lenstra_elliptic-curve_factorization
                          https://zafirr31.github.io/posts/lenstra-elliptic-curve-method-of-factorization/
                          https://members.loria.fr/PZimmermann/records/ecm/params.html
                          https://www.ams.org/journals/mcom/2013-82-282/S0025-5718-2012-02633-0/S0025-5718-2012-02633-0.pdf
                          https://en.wikipedia.org/wiki/Torsion_group

*/ 


//***************************************************************************************************************************
//CABEÇALHO
#ifndef ELLIPTIC_CURVE_FACTORIZATION_H
#define ELLIPTIC_CURVE_FACTORIZATION_H
#include"edwards_elliptic_curve_arithmetic.h"


//CONSTANTES GLOBAIS
const int EDWARDS_CURVE_MAX=100;//Número máximo de curvas a ser testada
const int EDWARDS_CURVE_MASK=255;//2^9-1
const uint64_t PHI2310=480;
uint64_t coprime2310[480]={1, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 169, 173, 179, 181, 191, 193, 197, 199, 211, 221, 223, 227, 229, 233, 239, 241, 247, 251, 257, 263, 269, 271, 277, 281, 283, 289, 293, 299, 307, 311, 313, 317, 323, 331, 337, 347, 349, 353, 359, 361, 367, 373, 377, 379, 383, 389, 391, 397, 401, 403, 409, 419, 421, 431, 433, 437, 439, 443, 449, 457, 461, 463, 467, 479, 481, 487, 491, 493, 499, 503, 509, 521, 523, 527, 529, 533, 541, 547, 551, 557, 559, 563, 569, 571, 577, 587, 589, 593, 599, 601, 607, 611, 613, 617, 619, 629, 631, 641, 643, 647, 653, 659, 661, 667, 673, 677, 683, 689, 691, 697, 701, 703, 709, 713, 719, 727, 731, 733, 739, 743, 751, 757, 761, 767, 769, 773, 779, 787, 793, 797, 799, 809, 811, 817, 821, 823, 827, 829, 839, 841, 851, 853, 857, 859, 863, 871, 877, 881, 883, 887, 893, 899, 901, 907, 911, 919, 923, 929, 937, 941, 943, 947, 949, 953, 961, 967, 971, 977, 983, 989, 991, 997, 1003, 1007, 1009, 1013, 1019, 1021, 1027, 1031, 1033, 1037, 1039, 1049, 1051, 1061, 1063, 1069, 1073, 1079, 1081, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1121, 1123, 1129, 1139, 1147, 1151, 1153, 1157, 1159, 1163, 1171, 1181, 1187, 1189, 1193, 1201, 1207, 1213, 1217, 1219, 1223, 1229, 1231, 1237, 1241, 1247, 1249, 1259, 1261, 1271, 1273, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1313, 1319, 1321, 1327, 1333, 1339, 1343, 1349, 1357, 1361, 1363, 1367, 1369, 1373, 1381, 1387, 1391, 1399, 1403, 1409, 1411, 1417, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1457, 1459, 1469, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1501, 1511, 1513, 1517, 1523, 1531, 1537, 1541, 1543, 1549, 1553, 1559, 1567, 1571, 1577, 1579, 1583, 1591, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1633, 1637, 1643, 1649, 1651, 1657, 1663, 1667, 1669, 1679, 1681, 1691, 1693, 1697, 1699, 1703, 1709, 1711, 1717, 1721, 1723, 1733, 1739, 1741, 1747, 1751, 1753, 1759, 1763, 1769, 1777, 1781, 1783, 1787, 1789, 1801, 1807, 1811, 1817, 1819, 1823, 1829, 1831, 1843, 1847, 1849, 1853, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1891, 1901, 1907, 1909, 1913, 1919, 1921, 1927, 1931, 1933, 1937, 1943, 1949, 1951, 1957, 1961, 1963, 1973, 1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2021, 2027, 2029, 2033, 2039, 2041, 2047, 2053, 2059, 2063, 2069, 2071, 2077, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2117, 2119, 2129, 2131, 2137, 2141, 2143, 2147, 2153, 2159, 2161, 2171, 2173, 2179, 2183, 2197, 2201, 2203, 2207, 2209, 2213, 2221, 2227, 2231, 2237, 2239, 2243, 2249, 2251, 2257, 2263, 2267, 2269, 2273, 2279, 2281, 2287, 2291, 2293, 2297, 2309};


//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool* generate_prime_array(uint64_t);
void elliptic_curve_factorization_second_stage(mpz_t, mpz_t, mpz_t, mpz_t, mpz_t,uint64_t);
void elliptic_curve_factorization(mpz_t, mpz_t, uint64_t, uint64_t, int);


//***************************************************************************************************************************
//FUNÇÕES
//Função que calcula um array de números primos usando a peneira de Eratóstenes
bool* generate_prime_array(uint64_t B1){

  //Variáveis locais
  bool* number_array=(bool*)malloc((B1+1)*sizeof(bool));
  

  //Procedimentos
    //Inicializando o array de booleanos
    number_array[0]=false; number_array[1]=false;
    for(int64_t i=2; i<=B1; ++i) number_array[i]=true;

    //Loop principal
    for(int64_t i=2; (i*i)<=B1; ++i){

      if(number_array[i]==false) continue;
      for(int64_t j=(i*i); j<=B1; j+=i) number_array[j]=false;

    }


  //Resultado
  return number_array;  

};

//----------------------------------------------------------------
//Função que implementa o estágio 2 do algoritmo de fatoração usando curvas elípticas
void elliptic_curve_factorization_second_stage(mpz_t X, mpz_t Y, mpz_t d, mpz_t n, mpz_t factor, uint64_t B1){

  //Variáveis locais
  uint64_t B2=10000*B1;
  mpz_t x2310, y2310, xB, yB, xr, yr, stock;
  mpz_t xq_array[480], yq_array[480];

  //Inicializando variáveis
  mpz_init(x2310); mpz_init(y2310); mpz_init(xB); mpz_init(yB); mpz_init(xr); mpz_init(yr); mpz_init(stock);
  for(int i=0; i<480; ++i){
    mpz_init(xq_array[i]); mpz_init(yq_array[i]);
  }


  //Procedimento
    //Ajuste de variáveis
    while((B1%2310)>0) B1--;

    //Pré-computando pontos usados no cálculo
    point_scalar_multiplication(xB, yB, X, Y, d, n, factor, B1);
    if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
      goto memory_cache_cleaning;
    mpz_mul(xr, xB, yB); mpz_gcd(factor, xr, n);
    if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
      goto memory_cache_cleaning;

    point_scalar_multiplication(x2310, y2310, X, Y, d, n, factor, 2310);
    mpz_set_ui(stock, 1);

    for(int i=0; i<480; ++i){
      point_scalar_multiplication(xq_array[i], yq_array[i], X, Y, d, n, factor, coprime2310[i]);
    }

    //Loop principal: iterando sobre os pontos na curva com dordem
    while(B1<B2){

      //Loop sobre pontos de ordem 2310k+r com mdc(r, 2310)=1
      for(int i=0; i<480; ++i){
        pointwise_addition(xr, yr, xB, yB, xq_array[i], yq_array[i], d, n, factor);
        if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0){
          printf("Fator encontrado no estágio 2\n");
          goto memory_cache_cleaning;
        }
        else{
          mpz_mul(stock, stock, xr); mpz_mul(stock, stock, yr);
        }

      };

      //Testando se um fator primo foi encontrado
      mpz_gcd(factor, stock, n);
      if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0){
        printf("Fator encontrado no estágio 2\n");
        break;
      }

      //Atualizando variáveis para a próxima iteração
      B1+=2310;
      mpz_set_ui(stock, 1);
      pointwise_addition(xB, yB, xB, yB, x2310, y2310, d, n, factor);
      if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0){
        printf("Fator encontrado no estágio 2\n");
        break;
      }

    };


    //Limpando o cachê de memória
    memory_cache_cleaning:

    mpz_clear(x2310); mpz_clear(y2310); mpz_clear(xB); mpz_clear(yB); mpz_clear(xr); mpz_clear(yr); mpz_clear(stock);
    for(int i=0; i<480; ++i){
      mpz_init(xq_array[i]); mpz_clear(yq_array[i]);
    }

};
//----------------------------------------------------------------

//Função que implementa o algoritmo de fatoração usando curvas elípticas
void elliptic_curve_factorization(mpz_t n, mpz_t factor, uint64_t B1, uint64_t u, int stage2){

  //Semente para geração de números aleátorios
  srand(time(NULL));

  //Variáveis locais
  bool* prime_array=generate_prime_array(B1);
  int trials=0;
  mpz_t xp, yp, xr, yr, d, stock;


  //Inicializando variáveis
  mpz_init(xr); mpz_init(yr); mpz_init(xp); mpz_init(yp); mpz_init(d); mpz_init(stock);
  mpz_set_ui(factor, 1); mpz_set_ui(stock, 1);

  //Procedimentos
    //Loop principal
    while(trials<EDWARDS_CURVE_MAX){
     
      //Definindo parâmetros da curva elíptica
      setup_edwards_curve_parameters(xp, yp, d, n, factor, u);
      if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
        break; 

      //Estágio 1: Testando se pontos da ordem #p (primoriais) produzem um fator não trivial
      for(uint64_t i=2; i<=B1; ++i){
        if((i&EDWARDS_CURVE_MASK)==0) mpz_mod(stock, stock, n);
        if(prime_array[i]==false) continue;

        point_scalar_multiplication(xr, yr, xp, yp, d, n, factor, i);

        if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
          break;
        else{
          mpz_set(xp, xr); mpz_set(yp, yr);
        } 
        
        mpz_mul(stock, stock, xr); mpz_mul(stock, stock, yr);
      }
      if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
        break; //Fator primo encontrado no cálculo de pontos da curva

      mpz_gcd(factor, stock, n);
      if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
        break; 

      //Estágio 2: Testando pontos de ordem mais elevada (≳B1)
      if(stage2>0){
        elliptic_curve_factorization_second_stage(xp, yp, d, n, factor, B1);
        if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
          break;  
      }
      if(mpz_cmp_ui(factor, 1)>0 && mpz_cmp(factor, n)<0)
        break;  

      //Ajuste de variáveis
      trials++;
      u=1;//Escolha de u alétória para a próxima curva

    }; //Fim do loop principal

    //Limpeza de cachê de memória
    memory_cache_cleaning:
    
    if(prime_array){
      free(prime_array); prime_array=NULL;
    }
    mpz_clear(xr); mpz_clear(yr); mpz_clear(xp); mpz_clear(yp); mpz_clear(d); mpz_clear(stock);

};

//***************************************************************************************************************************
//FIM DO HEADER
#endif
