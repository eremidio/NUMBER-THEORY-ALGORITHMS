//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A VARIANTE DE MONTGOMERY DO MÉTODO DE FATORAÇÃO VIA CURVAS ELÍPTICAS

/*

  O MÉTODO DE MONTGOMERY É UMA VARIAÇÃO DO MÉTODO ORIGINAL DE FATORAÇÃO VIA CURVAS ELÍPTICAS PROPOSTOPOR H. LENSTRA QUE USA AS CHAMADAS CURVAS DE MONTOGOMERY
  gy²=x³+Cx²+x (mod p). ASSIM COMO NO ALGORITMO ORIGINAL PONTOS SOBRE A CURVA FORMAM UM GRUPO ABELIANO COM AS OPERAÇÕES GEOMÉTRICAS DE ADIÇÃO DE PONTOS E MULTIPLICAÇÃO
  POR UM ESCALAR.

  ESTE ALGORITMO TEM A VANTAGEM DE NÃO REQUERER O CÁLCULO DE INVERSOS MODULARES USANDO-SE O ALGORITMO DE EUCLIDES EXTENDIDO COMO NO ALGORITMO ORIGINAL, ALÉM DE
  POSSIBILITAR A EXECUÇÃO DE UM SEGUNDO ESTÁGIO NO ALGORITMO QUE EMPREGA DOIS NÚMEROS B1 E B2 PARA CONTROLAR O INTERVALO DE BUSCA POR FATORES PRIMOS (FATORES NÃO TRIVIAIS
  SÃO ENCONTRADOS SE A ORDEM DO SUBGRUPO E(p) DE PONTOS EM CURVAS FOR SUAVE EM RELAÇÃO A ESTE PARÂMETROS, O TEOREMA DE HASSE ESTIMA QUE A ORDEM #E(p) ESTÁ NO INTERVALO
  (p+1)-2√p, ..., (p+1)+2√p). A ESCOLHA DE PARAMETRIZAÇÕES ADEQUADAS GARANTE QUE #E(p) É SUAVE EM RELAÇÃO AOS PARÂMETROS B1 E B2.

  PARA MAIORES INFORMAÇÕES: https://dspace.mit.edu/bitstream/handle/1721.1/97521/18-783-spring-2013/contents/lecture-notes/MIT18_783S13_lec12.pdf
                            https://eprint.iacr.org/2017/212.pdf
                            https://members.loria.fr/PZimmermann/papers/40760525.pdf
                            https://members.loria.fr/PZimmermann/records/ecm/params.html
                            https://en.wikipedia.org/wiki/Lenstra_elliptic-curve_factorization
                            https://www.rieselprime.de/ziki/Elliptic_curve_method#Step_2
                            Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_H
#define MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_H

#include"montgomery_elliptic_curve_factorization_auxiliary_functions.hpp"
#include<random>
#include<string>
#include<iostream>
#include<limits>

//CONSTANTES GLOBAIS
#define MAX_CURVES 15000

//Parâmetros otimos para fatores de até 50 dígitos decimais
uint64_t B1_table[8]={2000, 11000, 50000, 250000, 1000000, 3000000, 11000000, 43000000};
int digits_table[8]= {15, 20, 25, 30, 35, 40, 45, 50};


//********************************************************************************************************************************************************************
//CLASSE DO ALGORITMO
class elliptic_curve_method{
    public:

  //Membros da classe
  cpp_int number;//Número a ser fatorado
  std::string number_string;//Número a ser fatorado
  uint64_t B1, B2, B;//Variável usada na escolha de profundidadede busca por um número primo
  cpp_int factor1, factor2, selection;//Fatores primos encontrados
  int64_t sigma_parameter;//Variável de seleção do ponto inicial usado nas curvas
  cpp_int C;//Parâmetro que define a curva usada no algoritmo
  uint64_t curve_number;//Função que determina o número de curva testadas no algoritmo

  std::vector<uint64_t> prime_buffer_B1;//Buffer de números primos usados no algoritmo

  int auto_setup;//Função usada para iniciar o estágio 2 do algoritmo
  cpp_int up, vp, x0, z0, xp, zp;//Coordenadas das curvas usadas no cálculo no estágio 1 do algoritmo
  cpp_int prime_power;//Variável usada para definir o fator multiplicativo no cálculo de pontos sobre a curva elíptica

  cpp_int xq, zq, xc, zc, x7, z7, x11, z11, x13, z13, x30, z30;//Coordenadas das curvas usadas no cálculo no estágio 2 do algoritmo
  cpp_int g, gt, h, ht, multiplier;//Variáveis usadas no cálculo no estágio 2 do algoritmo



    //Construtores e destruidores
    elliptic_curve_method(){ };
    ~elliptic_curve_method(){ };

  //Métodos da classe
  void run();//Função principal do algoritmo
  void setup();//Função que recebe input do usuário e ajusta variáveis usadas no algoritmo
  void set_new_curve();//Função que reajusta a equação da curva para novos testes
  void first_stage();//Função que implementa o estágio 1 do algoritmo
  void second_stage();//Função que implementa o estágio 2 do algoritmo
  void calculate_factors();//Função que calcula fatores primos dos números a ser fatorado
  void print_result();//Função que exibe o resultado da execução do algoritmo
 
};



//********************************************************************************************************************************************************************
//MÉTODOS DA CLASSE

//Função principal da classe
void elliptic_curve_method::run(){

  //Etapa 1: configurando variáveis usadas no algoritmo
  step1:
    setup();

    //Verificando se o número já possui um fator conhecido durante a configuração
    if(selection>1 && selection!=number)
      goto step4;

    if(selection==number){
      std::cout<<"O número informado não é adequado para o algoritmo de fatoração.\n";
      return;
    };

  //Etapa 2: executando o estágio 1 do algoritmo
  step2:
    first_stage();

    if(selection>1 && selection!=number)
      goto step4;


  //Etapa 3: executando o estágio 2 do algoritmo
  step3:
    second_stage();

    if(selection>1 && selection!=number)
      goto step4;


  //Etapa 4: calculando fatores primos
  step4:
    if(selection>1 && selection!=number){
      calculate_factors();
      print_result();
      return;
    };

  //Etapa 5: Encerrando o algortimo caso um fator não tenha sido encontrado no estágio 2 do algoritmo
  step5:
    set_new_curve();

    if(selection>1 && selection!=number)
      goto step4;

    ++curve_number;

    if(curve_number<=MAX_CURVES)
      goto step2;
    else{
      std::cout<<"O algoritmo não encontrou fatores primos do número em questão\n";
      return;
    };

};


//Função que recebe input do usuário
void elliptic_curve_method::setup(){

  //Recebendo input do usuário
  std::cout<<"Número a ser fatorado: ";
  std::cin>>number_string;

  number=cpp_int(number_string);

  //Verificando condições básicas
  if(number<2){
    std::cout<<"O número deve ser maior que 1.\n";
    selection=number;
    return;
  };

  std::cout<<"Fator de profundidade usado na busca por fatores primos: ";
  std::cin>>B1;

  if(B1<2){
    std::cout<<"B1 deve ser maior ou igual a 2.\n";
    selection=number;
    return;
  };
  
  std::cout<<"Fator σ que define a curva e ponto na curva a ser usada no cálculo: ";
  std::cin>>sigma_parameter;


  //Cálculos de outros parâmetros
    //Fator de profundidade usado na busca no estágio 2 do algoritmo

    //Proteção contra overflow de uint64_t
    if(B1>std::numeric_limits<uint64_t>::max()/1000){

      std::cout<<"O valor de B1 é muito grande para o cálculo automático de B2.\n";
      selection=number;
      return;
    };

    B2=B1*1000;

    B=B2;

    while(B>=30 && (B%30)!=0)
      --B;

    //Parâmetros que definem o ponto da inicial curva
    while(std::abs(sigma_parameter)==1 || sigma_parameter==0 || sigma_parameter==5)
      sigma_parameter=generate_random_number();

    up=(sigma_parameter*sigma_parameter)-5;
    vp=4*sigma_parameter;

    x0=((up%number)*(up%number)*(up%number))%number;
    z0=((vp%number)*(vp%number)*(vp%number))%number;

    //Normalização das coordenadas
    if(x0<0)
      x0+=number;
    if(z0<0)
      z0+=number;


    //Parâmetro que define a curva
    /*
        A curva de Montgomery é construída a partir de:
        C = ((v-u)^3 * (3u+v)) / (4u^3v) - 2
    */

    cpp_int numerator=(vp-up)*(vp-up)*(vp-up)*((3*up)+vp);
    cpp_int denominator=4*up*up*up*vp;

    cpp_int denominator_reduced=denominator%number;
    cpp_int denominator_gcd= euclides_algorithm(denominator_reduced, number);

    if(denominator_gcd>1){
      selection=denominator_gcd;
      return;
    };

    cpp_int denominator_inverse;
    if(!modular_inverse(
          denominator_inverse,
          denominator_reduced,
          number)){
      selection=number;
      return;
    };

    C=((numerator%number)*denominator_inverse)%number;
    C-=2;
    C%=number;

    if(C<0) C+=number;


    //Preenchendo o buffer de primos usados no estágio 1 do algoritmo
    fill_prime_buffer(prime_buffer_B1, B1);

    //Outros ajustes de parâmetros
    factor1=0;
    factor2=0;
    selection=0;
    prime_power=0;

    auto_setup=0;
    curve_number=1;

    g=1;
    gt=1;
    h=1;
    ht=1;

    multiplier=1;

    xp=x0;
    zp=z0;

};



//Função que reajusta a equação da curva para novos testes
void elliptic_curve_method::set_new_curve(){

  //Parâmetros que definem o ponto da inicial curva
  sigma_parameter=generate_random_number();

  while(std::abs(sigma_parameter)==1 ||
        sigma_parameter==0 ||
        sigma_parameter==5)
    sigma_parameter=generate_random_number();

  up=(sigma_parameter*sigma_parameter)-5;
  vp=4*sigma_parameter;

  x0=((up%number)*(up%number)*(up%number))%number;
  z0=((vp%number)*(vp%number)*(vp%number))%number;

  //Normalização das coordenadas
  if(x0<0) x0+=number;
  if(z0<0) z0+=number;
  if(auto_setup>0){
    xq=x0;
    zq=z0;
  };


  //Parâmetro que define a curva
  /*
      A curva de Montgomery é construída a partir de:
      C = ((v-u)^3 * (3u+v)) / (4u^3v) - 2
  */

  cpp_int numerator= (vp-up)*(vp-up)*(vp-up)*((3*up)+vp);
  cpp_int denominator= 4*up*up*up*vp;

  cpp_int denominator_reduced=denominator%number;
  cpp_int denominator_gcd= euclides_algorithm(denominator_reduced, number);

  if(denominator_gcd>1){
    selection=denominator_gcd;
    return;
  };

  cpp_int denominator_inverse;
  if(!modular_inverse(
        denominator_inverse,
        denominator_reduced,
        number)){
    selection=number;
    return;
  };

  C=((numerator%number)*denominator_inverse)%number;
  C-=2;
  C%=number;
  if(C<0) C+=number;

};



//Função que calcula fatores primos dos números a ser fatorado
void elliptic_curve_method::calculate_factors(){

    factor1=selection;
    factor2=number/factor1;

  };



//Função que exibe o resultado da execução do algoritmo
void elliptic_curve_method::print_result(){

  std::cout<<"\nRelatório de execução do algoritmo:\n";
  std::cout<<"Curva usada para encontrar o fator: gy²=x³+("<<C<<")x²+x (mod "<<number<<")\n";
  std::cout<<"σ: "<<sigma_parameter<<'\n';
  std::cout<<"Número de curvas testadas: "<<curve_number<<'\n';
  std::cout<<"B1: "<<B1<<'\n';
  std::cout<<"B2: "<<B2<<'\n';
  std::cout<<"Número a ser fatorado: "<<number<<'\n';
  std::cout<<"Fator encontrado: "<<factor1<<'\n';
  std::cout<<"Restante: "<<factor2<<'\n';

};




//Função que implementa o estágio 1 do algoritmo
void elliptic_curve_method::first_stage(){

  //Ajuste de variáveis
  auto_setup=0;

  /*
  O estágio 1 calcula: Q=[M]P onde:
      M=produto de p^k para todos os primos p<=B1,
      com p^k<=B1.
  Em vez de calcular [p^k]P independentemente para cada
  primo, começamos com Q=P e aplicamos [p] repetidamente:
      Q=[p]Q
  Isso produz exatamente o mesmo resultado [M]P,
  mas evita recalcular a multiplicação escalar a partir
  do ponto inicial para cada potência de cada primo.
  */

  //Ajuste do ponto inicial
  xp=x0;
  zp=z0;

  //Loop principal
  for(auto x: prime_buffer_B1){

    prime_power=x;

    while(prime_power<=B1){

      /*
      Multiplicação do ponto atualmente acumulado por p.
      Depois da primeira iteração:
          Q=[p]P
      depois:
          Q=[p²]P
      e assim por diante.
      */

      pointwise_scalar_multiplication(
        xp,
        zp,
        xp,
        zp,
        x,
        C,
        number
      );

      selection=euclides_algorithm(zp, number);

      if(selection>1)
        return;

      //Proteção contra overflow do cálculo da próxima potência
      if(prime_power>B1/x)
        break;

      prime_power=prime_power*x;

    };

  };

};

//Função que implementa o estágio 2 do algoritmo
/*
  NOTA: A abordagem mais eficiente que emprega o algoritmo baby step-giant step é mais complesxa de ser implementada. Usaremos uma abordagem simples
        recalculando os pontos na curva partir do último ponto gerado no estágio 1 do algoritmo.
*/
void elliptic_curve_method::second_stage(){

  //Variáveis locais
  cpp_int P=1;
  cpp_int zp30, xp30;
  cpp_int x_next, z_next;


  //Ajuste de variáveis
  xq=xp;
  zq=zp;
  auto_setup=1;
  g=1;
  gt=1;
  h=1;
  ht=1;
  multiplier=B;


  //Calculando o valor das coordenadas dos pontos [B]Q, [7]Q, [11]Q, [13]Q
  pointwise_scalar_multiplication(
    xc,
    zc,
    xq,
    zq,
    B,
    C,
    number
  );


  /*
  Calculando [30]Q.
  Este ponto será usado como diferença fixa entre dois pontos
  consecutivos do estágio 2:

      [B+30k]Q - [B+30(k-1)]Q = [30]Q
  O ponto é calculado uma única vez e reutilizado durante todo
  o estágio 2.
  */
  pointwise_scalar_multiplication(
    x30,
    z30,
    xq,
    zq,
    30,
    C,
    number
  );


  /*
  Calculando os pontos usados nos baby steps:

      [7]Q
      [11]Q
      [13]Q
  */

  pointwise_scalar_multiplication(
    x7,
    z7,
    xq,
    zq,
    7,
    C,
    number
  );

  P=(P*z7)%number;


  pointwise_scalar_multiplication(
    x11,
    z11,
    xq,
    zq,
    11,
    C,
    number
  );

  P=(P*z11)%number;


  pointwise_scalar_multiplication(
    x13,
    z13,
    xq,
    zq,
    13,
    C,
    number
  );

  P=(P*z13)%number;


  /*
  Precisamos manter o ponto gigante anterior para realizar a
  adição diferencial.
  Neste momento:
      xp30,zp30 = [B]Q
  e:
      x30,z30 = [30]Q
  O primeiro ponto seguinte será calculado como:
      [B+30]Q = [B]Q + [30]Q
  usando como diferença:
      [B]Q - [30]Q = [B-30]Q
  Para obter esse ponto de diferença calculamos [B-30]Q uma
  única vez.
  */

  pointwise_scalar_multiplication(
    xp30,
    zp30,
    xq,
    zq,
    B-30,
    C,
    number
  );


  /*
  Inicialização do produto acumulado.
  O primeiro ponto gigante é [B]Q.
  */

  gt=(xc*z7)-(x7*zc);
  gt%=number;

  if(gt<0)
    gt+=number;

  g=(g*gt)%number;


  gt=(xc*z11)-(x11*zc);
  gt%=number;

  if(gt<0)
    gt+=number;

  g=(g*gt)%number;


  gt=(xc*z13)-(x13*zc);
  gt%=number;

  if(gt<0)
    gt+=number;

  g=(g*gt)%number;


  /*
  Acumulando o valor de z do primeiro ponto gigante.
  */
  P=(P*zc)%number;


  //Loop principal sobre o intervalo {B, B+30, ..., B2}
  while(multiplier<B2){

    /*
    Proteção contra overflow do contador.
    */
    if(multiplier>B2-30)
      break;

    multiplier+=30;


    /*
    Calculando o próximo ponto gigante por adição diferencial.
    Antes da operação:
        xc,zc = [B+30(k-1)]Q
        x30,z30 = [30]Q
        xp30,zp30 = [B+30(k-2)]Q
    Portanto:
        [B+30k]Q =
        [B+30(k-1)]Q + [30]Q
    e a diferença entre os dois pontos utilizados na adição é:
        [B+30(k-1)]Q - [30]Q= [B+30(k-2)]Q
    que é exatamente xp30,zp30.
    */

    pointwise_addition(
      x_next,
      z_next,
      xc,
      zc,
      x30,
      z30,
      xp30,
      zp30,
      number
    );


    /*
    Atualizando os pontos usados na próxima adição diferencial.
        xp30,zp30 <- ponto gigante anterior
        xc,zc     <- ponto gigante atual
    */

    xp30=xc;
    zp30=zc;

    xc=x_next;
    zc=z_next;


    /*
      Acumulando os valores z das coordenadas dos pontos.
    */
    P=(P*zc)%number;


    /*
    Acumulando os produtos das diferenças entre as coordenadas x.
    O cálculo é feito em coordenadas projetivas:
        X1/Z1 - X2/Z2
    sem realizar inversões modulares.
    */

    gt=(xc*z7)-(x7*zc);
    gt%=number;

    if(gt<0)
      gt+=number;

    g=(g*gt)%number;


    gt=(xc*z11)-(x11*zc);
    gt%=number;

    if(gt<0)
      gt+=number;

    g=(g*gt)%number;


    gt=(xc*z13)-(x13*zc);
    gt%=number;

    if(gt<0)
      gt+=number;

    g=(g*gt)%number;


    /*
      Acumulando os produtos x*z para uma segunda tentativa
      de encontrar um fator.
    */
    ht=(xc*zc)%number;
    h=(h*ht)%number;


    /*
      Testando periodicamente o produto acumulado.
      Isso evita continuar calculando caso um fator já tenha
      sido encontrado.
    */
    selection=euclides_algorithm(g,number);

    if(selection>1 && selection!=number){
      std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
      return;
    }

    /*
      Se gcd(g,N)=N, o produto contém mais de um termo que pode
      ter produzido o fator. Interrompemos o loop para tentar
      recuperá-lo individualmente.
    */
    if(selection==number)
      break;

  };


  //Testando se um fator primo foi encontrado no segundo estágio
  selection=euclides_algorithm(g,number);

  if(selection>1 && selection!=number){
    std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
    return;
  };


  /*
    Caso o produto acumulado seja exatamente múltiplo de number,
    o MDC retorna number. Nesse caso não podemos concluir qual
    dos fatores individuais produziu o fator encontrado.

    O produto P é testado separadamente.
  */
  selection=euclides_algorithm(P,number);

  if(selection>1 && selection!=number){
    std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
    return;
  };


  /*
    Testando o segundo produto acumulado.
  */
  selection=euclides_algorithm(h,number);

  if(selection>1 && selection!=number){
    std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
    return;
  };


  /*
   Caso o MDC do produto acumulado seja igual ao próprio número,
    tentamos recuperar o fator através dos produtos acumulados
    individualmente.
  */
  if(selection==number || euclides_algorithm(g,number)==number){

    selection=euclides_algorithm(P,number);

    if(selection>1 && selection!=number){
      std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
      return;
    };

  };


  /*
    Testando a diferença entre os dois produtos acumulados.
  */
  if(g>h){

    selection=euclides_algorithm((g-h),number);

    if(selection>1 && selection!=number){
      std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
      return;
    };

  }else{

    selection=euclides_algorithm((h-g),number);

    if(selection>1 && selection!=number){
      std::cout<<"Fator encontrado no estágio 2 do algoritmo.\n";
      return;
    };

  };


};


//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
