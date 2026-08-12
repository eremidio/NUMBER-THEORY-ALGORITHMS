  //VAMOS CRIAR UM PROGRAMA QUE COMPUTA LOGARITMOS DISCRETOS

  /*

    LOGARITMOS DISCRETOS SÃO SOLUÇÕES DA EQUAÇÃO a^x=b, COM a, x, b INTEIROS, USUALMENTE RESTRITOS A UM CORPO FINITO DO PRIMEIRO TIPO Z/pZ COM
    p PRIMO OU POTÊNCIA DE UM NÚMERO PRIMO. ESSE TIPO DE EQUAÇÃO PODE SER RESOLVIDO USANDO-SE DIFERENTES ALGORITMOS COM DIFERENTES ORDENS DE
    COMPLEXIDADE. A ABORDAGEM MAIS BÁSICA CONSISTE EM TESTAR OS (p-1) VALORES POSSÍVEIS DE x {1, 2, ..., p-2} TEM COMPLEXIDADE O(p).

    EXISTE UMA FORMA ANÁLITICA QUE PERMITE COMPUTAR O RESULTADO EXATO DE x QUE SATIFAZ A RELAÇÃO a^x=b EM Z/pZ x=Σ(1-a^j)b^j (mod p-1) COM
    j=1,..., p-2. ESTA FÓRMULA, PORÉM TEM COMPLEXIDADE PIOR QUE O ALGORITMO DE FORÇA BRUTA, REQURENDO O(p) EXECUÇÕES DO ALGORITMO ESTENDIDO DE
    EUCLIDES PARA SE COMPUTAR INVERSOS MODULARES.

    
    PARA MAIORES INFORMAÇÕES: Number Theoretical Algorithms in Criptography by O. N. Vasilenko


  */



  //********************************************************************************************************************************************
  //CABEÇALHO
  #ifndef DISCRETE_LOGARITHM_H
  #define DISCRETE_LOGARITHM_H
  #include<stdint.h>
  #include<stdlib.h>
  #include<math.h>


  //********************************************************************************************************************************************
  //DECLARAÇÃO DE FUNÇÕES
  int64_t modular_inverse(int64_t, int64_t);
  int64_t discrete_logarithm_brute_force(int64_t, int64_t, int64_t);
  int64_t discrete_logarithm_analytical_formula(int64_t, int64_t, int64_t);


  //********************************************************************************************************************************************
  //FUNÇÕES
  //Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
  int64_t modular_inverse(int64_t a, int64_t n) {


    // Variáveis locais
    int64_t r0, r1, x0, x1, r2, x2;

    // Procedimentos
      // Ajuste de variáveis
      r0 = a;
      r1 = n;
      r2 = 1;
      x0 = 1;
      x1 = 0;

      // Calculando os valores finais dos coeficientes recursivamente
      while (r2 > 0) {
        int64_t quotient = floor(r0 / r1);

        r2 = r0 - quotient * r1;
        x2 = x0 - quotient * x1;

        // Atualizando variáveis para a próxima iteração
        if (r2 > 0) {
          r0 = r1;
          r1 = r2;
          x0 = x1;
          x1 = x2;
        };
      };


    // Resultado
    if (x1 < 0) return (x1 + n);
    else return x1;

  };


  //Função que computa logaritmo discretos usando busca lineares
  int64_t discrete_logarithm_brute_force(int64_t g, int64_t h, int64_t m){

    //Variáveis locais
    __int128_t result=1;


    //Procedimentos
      //Loop principal
      for(int64_t i=1; i<m; ++i){

        result=(result*g)%m;
        if(result==h) return i;

      }

    
    //Resultado em caso de falha
    return (-1);

  };


  //Função que computa logaritmo discretos usando uma fórmula analítica
  int64_t discrete_logarithm_analytical_formula(int64_t g, int64_t h, int64_t m){

    //Variáveis locais
    int64_t result=0, g_power=1, h_power=1, a=0, inv=0;


    //Procedimentos: loop principal
    for(int64_t i=1; i<(m-1); ++i){

      //Ajuste de variáveis
      g_power=(g_power*g)%(m);
      h_power=(h_power*h)%(m);

      a=(1-g_power)%(m); if(a<0) a+=m;
      inv=modular_inverse(a, m);

      result=result+(inv*h_power)%(m);

    }


    //Resultado
    return (result%m);

  };

  //********************************************************************************************************************************************
  //FIM DO HEADER
  #endif
