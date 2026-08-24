//VAMOS IMPLEMENTAR ROTINAS AUXILIARES USADAS NO ALGORITMO DE FATORAÇÃO VIA CURVAS ELÍPTICAS

/*
  NOTA: Usaremos inteiros de 64 bits nas pré-computação de primos usados no algoritmo, a aritmética em curvas elípticas será feita usando-se inteiros de 512 bits para
  evitar overflow.
*/

//********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_AUXILIARY_FUNCTIONS_H
#define MONTGOMERY_ELLPITIC_CURVE_FACTORIZATION_AUXILIARY_FUNCTIONS_H
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
#include<vector>
#include<cstdint>
#include<cmath>
#include<random>
#include<limits>
using namespace boost::multiprecision;


//********************************************************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
bool fast_prime_checking(uint64_t);
void fill_prime_buffer(std::vector<uint64_t>&, uint64_t);
void fill_prime_buffer(std::vector<uint64_t>&, uint64_t, uint64_t);

cpp_int euclides_algorithm(cpp_int, cpp_int);
uint64_t euclides_algorithm(uint64_t, uint64_t);

//Função que calcula o inverso modular de um inteiro de 512 bits
bool modular_inverse(cpp_int&, cpp_int, cpp_int);

int64_t generate_random_number();
void extract_bits(std::vector<int8_t>&, cpp_int);

//Funções que definem a aritmética de em curvas elípticas na parametrização de Montgomery usando coordenadas projetivas
void pointwise_doubling(cpp_int&, cpp_int&, cpp_int, cpp_int);
void pointwise_addition(cpp_int&, cpp_int&, cpp_int, cpp_int, cpp_int, cpp_int, cpp_int, cpp_int);
void pointwise_scalar_multiplication(cpp_int&, cpp_int&, cpp_int, cpp_int, cpp_int, cpp_int, cpp_int);

//********************************************************************************************************************************************************************
//FUNÇÕES

//Função que determina se um inteiro de 64 bits é primo ou não usando uma otimização 30k+1
bool fast_prime_checking(uint64_t n){

  //Casos triviais: primos menores que 30
  if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 || n==23 || n==29)
    return true;

  //Casos triviais: números menores que 2 e múltiplos de 2, 3 ou 5
  if(n<2 || (n%2)==0 || (n%3)==0 || (n%5)==0)
    return false;

  //Variáveis locais
  uint64_t i;
  uint64_t limit=static_cast<uint64_t>(std::sqrt(static_cast<long double>(n)));

  uint64_t divisors[8]={1, 7, 11, 13, 17, 19, 23, 29};//Números coprimos com 30 no intervalo 1,...,30

  //Procedimentos
    //Teste dos divisores coprimos com 30 na primeira iteração
    for(i=1; i<8; ++i){
      if((n%divisors[i])==0)
        return false;
    };


    //Demais interações
    while(divisors[7]<=limit){

      //Testando possíveis divisores
      for(i=0; i<8; ++i){
        if(divisors[i]>limit)
          break;

        if((n%divisors[i])==0)
          return false;
      };

      //Atualizando variáveis
      for(i=0; i<8; ++i)
        divisors[i]=divisors[i]+30;

    };


  //Caso o número passe nos testes acima
  return true;

};



//Função que preenche um buffer de primos até um determinado valor
void fill_prime_buffer(std::vector<uint64_t>& prime_vector, uint64_t upper_bound, uint64_t lower_bound){

  //Variáveis locais
  uint64_t i;

  //Procedimentos
    //Ajuste de variáveis
    prime_vector.clear();

    //Ajuste do limite inferior
    if(lower_bound<2)
      lower_bound=2;

    //Verificando se o intervalo é válido
    if(lower_bound>upper_bound)
      return;

    /*
    Usaremos o Crivo de Eratóstenes para gerar os primos.
    Isso é significativamente mais eficiente que chamar
    fast_prime_checking() para cada inteiro do intervalo.
    */

    //Para evitar overflow no cálculo do tamanho do vetor
    uint64_t range_size=upper_bound-lower_bound;
    if(range_size==std::numeric_limits<uint64_t>::max())
      return;

    ++range_size;
    std::vector<bool> prime_flags(static_cast<std::size_t>(range_size), true);

    //Tratamento do caso 2
    if(lower_bound<=2 && 2<=upper_bound)
      prime_vector.push_back(2);

    //Primeiro múltiplo de 2 dentro do intervalo
    uint64_t first_even;

    if(lower_bound<=2)
      first_even=4;
    else{
      first_even=lower_bound;
      if((first_even%2)!=0)
        ++first_even;
    }

    //Marcando os múltiplos de 2
    if(first_even<=upper_bound){
      for(uint64_t j=first_even; j<=upper_bound; ){

        prime_flags[static_cast<std::size_t>(j-lower_bound)]=false;

        if(j>upper_bound-2)
          break;

        j+=2;
      };
    };


    //Limite necessário para o crivo
    uint64_t limit=static_cast<uint64_t>(
      std::sqrt(static_cast<long double>(upper_bound))
    );

    //Crivo principal
    for(uint64_t p=3; p<=limit; p+=2){

      if(!fast_prime_checking(p))
        continue;

      //Primeiro múltiplo de p no intervalo
      uint64_t first_multiple;

      if(p>upper_bound/p)
        break;

      uint64_t p_squared=p*p;

      if(lower_bound<=p_squared)
        first_multiple=p_squared;
      else{
        uint64_t quotient=lower_bound/p;

        if((lower_bound%p)!=0)
          ++quotient;

        //Proteção contra overflow
        if(quotient>upper_bound/p)
          continue;

        first_multiple=quotient*p;
      }

      //Marcando os múltiplos de p
      for(uint64_t j=first_multiple; j<=upper_bound; ){

        if(j>=lower_bound)
          prime_flags[static_cast<std::size_t>(j-lower_bound)]=false;

        if(j>upper_bound-p)
          break;

        j+=p;
      };
    };


    //Construindo o buffer de primos
    for(i=lower_bound; i<=upper_bound; ++i){

      if(prime_flags[static_cast<std::size_t>(i-lower_bound)]){

        //O número 2 já foi inserido anteriormente.
        if(i!=2)
          prime_vector.push_back(i);
      }

      //Proteção contra overflow do contador
      if(i==std::numeric_limits<uint64_t>::max())
        break;
    };

};

void fill_prime_buffer(std::vector<uint64_t>& prime_vector, uint64_t upper_bound){

  //Procedimentos
    //Usa a versão geral do Crivo de Eratóstenes
    if(upper_bound<2){
      prime_vector.clear();
      return;
    }

    fill_prime_buffer(prime_vector, upper_bound, 2);

};




//Função que implementa o algoritmo de euclides para inteiro de precisão múltipla e para inteiros de 64 bits
cpp_int euclides_algorithm(cpp_int a, cpp_int b){

  //Ajuste de variáveis
  if(a<0)
    a=-a;

  if(b<0)
    b=-b;

  //Procedimentos
  while(b!=0){

    cpp_int temp=a%b;
    a=b;
    b=temp;

  };

  return a;

};


uint64_t euclides_algorithm(uint64_t a, uint64_t b){

  //Procedimentos
  while(b!=0){

    uint64_t temp=a%b;
    a=b;
    b=temp;

  };

  return a;

};



//Função que calcula o inverso modular de um inteiro de 512 bits
bool modular_inverse(cpp_int& inverse, cpp_int a, cpp_int n){

  //Variáveis locais
  cpp_int old_r;
  cpp_int r;
  cpp_int old_s;
  cpp_int s;

  //Ajuste de variáveis
  a%=n;

  if(a<0)
    a+=n;

  if(n<=1)
    return false;

  old_r=a;
  r=n;

  old_s=1;
  s=0;

  //Procedimentos
  while(r!=0){

    cpp_int quotient=old_r/r;

    cpp_int temp=old_r-(quotient*r);
    old_r=r;
    r=temp;

    temp=old_s-(quotient*s);
    old_s=s;
    s=temp;

  };


  //O inverso existe somente quando gcd(a,n)=1
  if(old_r!=1)
    return false;

  inverse=old_s%n;

  if(inverse<0)
    inverse+=n;

  return true;

};



//Função usada para se gerar um número inteiro aleatório da ordem 64 bits
int64_t generate_random_number(){

  //Variáveis locais
  const int64_t limit=10000000000000000LL;

  //Procedimentos
    //Ajuste da distribuição de números aleatórios
    static std::random_device generator_x;
    static std::mt19937_64 gen(generator_x());
    static std::uniform_int_distribution<int64_t> elliptic_distribution(10000, limit);


  //Resultado
  return elliptic_distribution(gen);

};



//Função extrai os bits de um inteiro de precisão múltipla e os aloca em um vetor
void extract_bits(std::vector<int8_t>& bit_vector, cpp_int n){

  //Procedimentos
    //Ajuste de variáveis
    bit_vector.clear();

    //Tratamento de números negativos
    if(n<0)
      n=-n;

    //Extraindo os bits
    while(n>0){

      if((n&1)!=0)
        bit_vector.push_back(1);
      else
        bit_vector.push_back(0);

      n>>=1;

    };

};



//****************************************************************************************************************************************************************
//ARITMÉTICA DE CURVAS ELÍPITICAS: 'a' é o parâmetro que define a curva e 'n' é o número a ser fatorado

//Função que a partir de um ponto P=(x:y:z) computa [2]P=P+P
void pointwise_doubling(cpp_int& x_point, cpp_int& z_point, cpp_int a, cpp_int n){

  //Variáveis locais
  cpp_int x_temp=x_point;
  cpp_int z_temp=z_point;

  cpp_int xx=x_temp*x_temp;
  cpp_int zz=z_temp*z_temp;

  cpp_int difference=xx-zz;

  //Procedimentos
  x_point=difference*difference;

  /*
  Forma equivalente da fórmula original:

  z_point = 4*z_temp*
            (x_temp*x_temp*x_temp
            +a*x_temp*x_temp*z_temp
            +x_temp*z_temp*z_temp)

  Colocando x_temp*z_temp em evidência:

  z_point = 4*x_temp*z_temp*
            (x_temp*x_temp
            +a*x_temp*z_temp
            +z_temp*z_temp)
  */

  cpp_int xz=x_temp*z_temp;

  z_point=4*xz*(xx+(a*xz)+zz);

  x_point%=n;
  z_point%=n;

  //Normalização dos restos
  if(x_point<0)
    x_point+=n;

  if(z_point<0)
    z_point+=n;

};



//Função que adiciona dois pontos na curva P=(xp:yp:zp) e Q=(xq:yq:zq) --> R=(xr:yr:zr)
void pointwise_addition(cpp_int& x_result, cpp_int& z_result, cpp_int x1, cpp_int z1, cpp_int x2, cpp_int z2, cpp_int x3, cpp_int z3, cpp_int n){

  //Variáveis locais
  cpp_int difference_1=(x1*x2)-(z1*z2);
  cpp_int difference_2=(x1*z2)-(x2*z1);

  //Procedimentos
  x_result=z3*difference_1*difference_1;
  z_result=x3*difference_2*difference_2;

  x_result%=n;
  z_result%=n;

  //Normalização dos restos
  if(x_result<0)
    x_result+=n;

  if(z_result<0)
    z_result+=n;

};



//Função que multiplica dois pontos na curva por um escalar[k]P=P+...+P (k vezes)
void pointwise_scalar_multiplication(cpp_int& x_result, cpp_int& z_result, cpp_int x_point, cpp_int z_point, cpp_int scalar_factor, cpp_int a, cpp_int n){

  //Variáveis locais
  std::vector<int8_t> bit_vector;
  cpp_int u, v, u1, v1, t, w, t1, w1;



  //Procedimentos
  if(scalar_factor==1){

    z_result=z_point;
    x_result=x_point;

    return;

  }
  else if(scalar_factor==2){

    z_result=z_point;
    x_result=x_point;

    pointwise_doubling(x_result, z_result, a, n);

    return;

  }
  else if(scalar_factor>2){

    //Ajuste de variáveis
    extract_bits(bit_vector, scalar_factor);

    u=x_point;
    v=z_point;

    t=x_point;
    w=z_point;

    pointwise_doubling(t, w, a, n);

    //Loop principal
    for(int i=static_cast<int>(bit_vector.size())-2; i>=0; --i){

      if(bit_vector[static_cast<std::size_t>(i)]==1){

        u1=u;
        v1=v;

        pointwise_addition(
          u,
          v,
          t,
          w,
          u1,
          v1,
          x_point,
          z_point,
          n
        );

        pointwise_doubling(t, w, a, n);

      };

      if(bit_vector[static_cast<std::size_t>(i)]==0){

        t1=t;
        w1=w;

        pointwise_addition(
          t,
          w,
          u,
          v,
          t1,
          w1,
          x_point,
          z_point,
          n
        );

        pointwise_doubling(u, v, a, n);

      };

    };


    x_result=u%n;
    z_result=v%n;

    //Normalização dos restos
    if(x_result<0)
      x_result+=n;

    if(z_result<0)
      z_result+=n;

  };

};

//********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
