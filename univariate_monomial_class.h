//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA CLASSE DE MONÔMIOS EM UMA VARIÁVEL

/*
ESTA CLASSE DE MONÔMIOS SERÁ USADO PARA CRIAR UMA CLASSE DE POLINÔMIOS ESPARSOS. ISTO É, UMA
CLASSE QUE MANIPULA POLINÔMIOS COM MUITOS COEFICIENTS ZERO.


*/

//*****************************************************************************************************************
//CABEÇALHO
#ifndef UNIVARIATE_MONOMIAL_CLASS_H
#define UNIVARIATE_MONOMIAL_CLASS_H
#include<stdint.h>
#include<inttypes.h>
#include<assert.h>
#include<string>
#include<iostream>
#include<type_traits>


//*****************************************************************************************************************
//CLASSE DE MONÔMIOS
template<typename T>
class univariate_monomial{
  public:

  //Membros da classe
  T coefficient;
  int64_t power;

  //Construtores e destruidores
  univariate_monomial(){ };
  univariate_monomial(T a, int64_t b){
    coefficient=a;
    power=b;
  };

  virtual ~univariate_monomial(){ };


  //Métodos da classe
    //Funções básicas: input e output
    void set_degree(int64_t);
    void set_coefficient(T);
    void set();
    std::string algebraic();

    //Operações aritméticas
    univariate_monomial<T> operator+(univariate_monomial<T>&);
    univariate_monomial<T> operator-(univariate_monomial<T>&);
    univariate_monomial<T> operator*(univariate_monomial<T>&);
    univariate_monomial<T> operator/(univariate_monomial<T>&);
    univariate_monomial<T> operator=(const univariate_monomial<T>&);

    //Operadores de comparação: útil em operações com polinômios
    bool operator==(univariate_monomial<T>&);
    bool operator<(univariate_monomial<T>&);


};


//*****************************************************************************************************************
//MÉTODOS DA CLASSE
  //Funções básicas: input e output

//Função que define a potência associada a um monômio
template<typename T>
void univariate_monomial<T>::set_degree(int64_t n){
  power=n;
};

//Função que define o coeficiente de um monômio
template<typename T>
void univariate_monomial<T>::set_coefficient(T n){
  coefficient=n;
};

//Função que define manualmente um monômio
template<typename T>
void univariate_monomial<T>::set(){

  //Variáveis locais
  T c;
  int64_t p;

  //Procedimentos
    //Recebendo input do usuário
    std::cout<<"Potência do monômio: ";
    std::cin>> p;
    std::cout<<"Coeficiente do monômio: ";
    std::cin>> c;

    //Definindo os parâmetros do monômio
    coefficient=c;
    power=p;

};


//Função que expressa o monômio como uma string do tipo a(n)x^n
template<typename T>
std::string univariate_monomial<T>::algebraic(){

  //Variáveis locais
  std::string monomial_string="";

  //Procedimentos 
    //Caso base: a(n)=0
    if(coefficient==0){
      monomial_string=" ";
      return monomial_string;
    }

    //Caso geral
    monomial_string+=std::to_string(coefficient);
    monomial_string+="x^";
    monomial_string+=std::to_string(power);

  //Resultado
  return monomial_string;

};


  //Operações aritméticas com monômios

//Adição
template <typename T>
univariate_monomial<T> univariate_monomial<T>::operator+(univariate_monomial<T>& m1){

  //Restrição: grau dos monômios devem ser iguais
  assert(power==m1.power);

  //Variáveis locais
  univariate_monomial<T> result;

  //Procedimentos
    //Ajuste do resultado
    result.power=power;
    result.coefficient=coefficient+m1.coefficient;

  //Resultado
  return result;

}

//Subtração
template <typename T>
univariate_monomial<T> univariate_monomial<T>::operator-(univariate_monomial<T>& m1){

  //Restrição: grau dos monômios devem ser iguais
  assert(power==m1.power);

  //Variáveis locais
  univariate_monomial<T> result;

  //Procedimentos
    //Ajuste do resultado
    result.power=power;
    result.coefficient=coefficient-m1.coefficient;

  //Resultado
  return result;

}

//Multiplicação
template <typename T>
univariate_monomial<T> univariate_monomial<T>::operator*(univariate_monomial<T>& m1){

  //Variáveis locais
  univariate_monomial<T> result;

  //Procedimentos
    //Ajuste do resultado
    result.power=power+m1.power;
    result.coefficient=coefficient*m1.coefficient;

  //Resultado
  return result;

}

//Divisão
template <typename T>
univariate_monomial<T> univariate_monomial<T>::operator/(univariate_monomial<T>& m1){

  //Variáveis locais
  univariate_monomial<T> result;

  //Procedimentos
    //Ajuste do resultado
    result.power=power-m1.power;
    result.coefficient=coefficient/m1.coefficient;

  //Resultado
  return result;

}

//Cópia (copy constructor)
template<typename T>
univariate_monomial<T> univariate_monomial<T>::operator=(const univariate_monomial<T>& m1){

  //Condição que implica a não igualdade de monômios
  if(this!= &m1){
    this->coefficient=m1.coefficient;
    this->power=m1.power;
  }


  //Resultado
  return *this;

};


  //Opereadores de comparação

//Igualdade
template<typename T>
bool univariate_monomial<T>::operator==(univariate_monomial<T>& m1){

  //Resultado
  return(power==m1.power && coefficient==m1.coefficient);

};

//Menor que <  
template<typename T>
bool univariate_monomial<T>::operator<(univariate_monomial<T>& m1){

  //Resultado
  return  power<m1.power;

};

//*****************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES AUXILIARES
template<typename T, typename U>
univariate_monomial<T> univariate_monomial_bin_pow(univariate_monomial<T>&, U);

template<typename T, typename U>
univariate_monomial<T> univariate_monomial_mod_bin_pow(univariate_monomial<T>&, U, U);

template<typename T, typename U>
univariate_monomial<T> univariate_monomial_mod(univariate_monomial<T>&, U);

template<typename T, typename U>
U univariate_monomial_valuation(univariate_monomial<T>&, U);

template<typename T, typename U>
U modular_univariate_monomial_valuation(univariate_monomial<T>&, U, U); 

//*****************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que implementa a exponenciação de monômios
template<typename T, typename U>
univariate_monomial<T> univariate_monomial_bin_pow(univariate_monomial<T>& m1, U exponent){
  
  //Restrição
  static_assert(std::is_integral<U>::value, "Expoentes devem ser inteiros");

  //Variáveis locais
  univariate_monomial<T> result(1,0);
  univariate_monomial<T> a=m1;

  //Procedimentos
    //Loop principal
    while(exponent>0){
     if(exponent&1) result=result*a;
  
       //Atualizando variáveius para a próxima iteração
       univariate_monomial<T> temp=a*a;
       a=temp;
       exponent>>=1;  
    }

  //Resultado
  return result;
    
};

//Função que implementa a exponenciação modular de monômios
template<typename T, typename U>
univariate_monomial<T> univariate_monomial_mod_bin_pow(univariate_monomial<T>& m1, U exponent, U modulus){
  
  //Restrição
  static_assert(std::is_integral<T>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<U>::value, "Coeficientes devem ser inteiros");

  //Variáveis locais
  univariate_monomial<T> result(1,0);
  univariate_monomial<T> a=m1;

  //Procedimentos
    //Loop principal
    while(exponent>0){
      if(exponent&1){
        result=result*a;
        result.coefficient%=modulus;
      }

     //Atualizando variáveius para a próxima iteração
     univariate_monomial<T> temp=a*a;
     a=temp;
     a.coefficient%=modulus;
     exponent>>=1;  
   }

    //Ajuste final do resultado
    result.coefficient%=modulus;

  //Resultado
  return result;
    
};


//Redução modular dos coeficientes de um monômio
template<typename T, typename U>
univariate_monomial<T> univariate_monomial_mod(univariate_monomial<T>& m1, U modulus){

  //Restrição
  static_assert(std::is_integral<T>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<U>::value, "Coeficientes devem ser inteiros");

  //Variáveis locais
  univariate_monomial<T> result=m1;

  //Procedimentos
    //Ajuste do resultado
    result.coefficient%=modulus;

  //Resultado
  return result;

};


//Função que estima o valor de um monômio
template<typename T, typename U>
U univariate_monomial_valuation(univariate_monomial<T>& m1, U arg){

  //Variáveis locais
  U result=1, a=arg;
  int64_t e=m1.power;
  
  //Procedimentos
    //Exponenciação binária
    while(e>0){
      if(e&1) result=result*a;
      
      //Atualizando variáveis para a próxima iteração
      U temp=a*a;
      a=temp;
      e>>=1;

    }

  //Resultado
  return (static_cast<U>(m1.coefficient)*result);

};



//Função que estima o valor de um monômio a menos de uma relação de congruência
template<typename T, typename U>
U modular_univariate_monomial_valuation(univariate_monomial<T>& m1, U arg, U modulus){

  //Variáveis locais
  U result=1, a=arg;
  int64_t e=m1.power;
  
  //Procedimentos
    //Exponenciação binária
    while(e>0){
      if(e&1){
        result=result*a;
        result=result%modulus;
      }
      
      //Atualizando variáveis para a próxima iteração
      U temp=a*a;
      a=temp%modulus;
      e>>=1;

    }

  //Resultado
  return (static_cast<U>(m1.coefficient)*result)%modulus;

};



//*****************************************************************************************************************
//FIM DO HEADER
#endif
