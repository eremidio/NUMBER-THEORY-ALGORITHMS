//VAMOS CRIAR UM PROGRAMA EM C++ QUE IMPLMENTA A CLASSE DOS NÚMEROS PERPLEXOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o perplex perplex.cpp

/* TEORIA:

A classe dos números perplexos compreende a classe de números da forma: z=(x, y) ou em notação algébrica z= x+yj, onde j é a unidade hiperbólica imaginária que satifaxz a relação: j²=1.

As regras de adição e multiplicação de números perplexos são definidas respectivamente por:
(x, y) +(u, v) =(x+u, y+v) ou (x+yj)+(u+vj)=(x+u)+(y+v)j
(x, y) × (u, v) =(xu+yv, xv+yu) ou (x+yj)×(u+vj)=(xu+yv)+(xv+yu)j 

O complexo do número z=x+yj é z*=x-yj. Esta operação satisfaz as propriedades: (z+w)*=z*+w*,(zw)*=z*w*, (z*)*=z.  
Isto define um automorfismo de ordem 2 em relação a operação de conjugação.

O módulo quadrado deste número é: z²=|zz*|= x²-y².

Inversos multiplicativos são definidos por (1/z)=(z*)/z².

A exponencial de um número perplexo é definida pela relação: exp(ja)=cosh(a)+jsenh(a). Números perplexos com parte real nula coprrepondem a pontos em uma hipérbole unitária.

Ver maiores informações em: https://en.wikipedia.org/wiki/Split-complex_number

*/

//***************************************************************************************************************************
/*CABEÇALHO*/
#include<iostream>
#include<cmath>
#include<string>
using namespace std;



//***************************************************************************************************************************
//CLASSE DOS NÚMEROS PERPELEXOS
template<typename T>
class perplex{
public:
//MEMBROS DA CLASSE
T x;
T y;
//CONSTRUTORES E DESTRUIDORES
perplex(){ };
perplex (T , T);
~perplex();
//MÉTODOS DA CLASSE
perplex<T> operator+(perplex<T>);
perplex<T> operator-(perplex<T>);
perplex<T> operator*(perplex<T>);
perplex<T> operator/(perplex<T>);
perplex<T> exp();
perplex<T> conjugate();
perplex<T> inverse();
T absolute();
T angle();
string show();
             };

//MÉTODOS DA CLASSE
//CONSTRUTOR E DESTRUIDOR
template<typename T>
perplex<T>::perplex(T a, T b){
x=a;
y=b;
                             };

template<typename T>
perplex<T>::~perplex(){
                      };

//OPERADORES ARITMÉTICOS BÁSICOS
template<typename T>
perplex<T> perplex<T>::operator +(perplex<T> z1){
perplex z2;
z2.x=x+z1.x;
z2.y=y+z1.y;
return z2;
                                                };

template<typename T>
perplex<T> perplex<T>::operator -(perplex<T> z1){
perplex z2;
z2.x=x-z1.x;
z2.y=y-z1.y;
return z2;
                                                };

template<typename T>
perplex<T> perplex<T>::operator *(perplex<T> z1){
perplex z2;
z2.x=x*z1.x+y*z1.y;
z2.y=x*z1.y+y*z1.x;
return z2;
                                                };

template<typename T>
perplex<T> perplex<T>::operator/(perplex<T> z1){
perplex z2;
perplex z3;
T modulus;
//CALCULANDO O INVERSO
modulus = pow(z1.x, 2) - pow(z1.y, 2);
z2.x= z1.x/modulus;
z2.y= (-1)*z1.y/modulus;

//EFETUANDO A DIVISÃO
z3.x=x*z1.x+z2.y*y;
z3.y=x*z1.y+z2.y*x;

return z3;
                                               };

//FUNÇÕES QUE DEFINEM OPERAÇÕES ESPECIAIS RELACIONADAS AOS NÚMEROS PERPLEXOS
//FUNÇÃO QUE RETORNA O CONJUNGADO DE UM NÚMERO PERPLEXO
template<typename T>
perplex<T> perplex<T>::conjugate(){
perplex z2;
z2.x=x;
z2.y=(-1)*y;
return z2;
                                  };

//FUNÇÃO QUE RETORNA O MÓDULO QUADRADO DE UM NÚMERO PERPLEXO
template<typename T>
T perplex<T>::absolute(){
T result;
result= pow(x, 2) - pow(y, 2);
return result;
                        };

//FUNÇÃO QUE RETORNA O MÓDULO QUADRADO DE UM NÚMERO PERPLEXO
template<typename T>
T perplex<T>::angle(){
T result;
result= atanh(y/x);
return result;
                        };

//FUNÇÃO QUE RETORNA O CONJUNGADO DE UM NÚMERO PERPLEXO
template<typename T>
perplex<T> perplex<T>::inverse(){
perplex z2;
T modulus;

modulus = pow(x, 2) - pow(y, 2);
z2.x= x/modulus;
z2.y= (-1)*y/modulus;

return z2;
                                     };

//FUNÇÃO QUE RETORNA A EXPONENCIAL DE UM NÚMERO PERPLEXO
template<typename T>
perplex<T> perplex<T>::exp(){
perplex z2;

z2.x= std::exp(x)*cosh(y);
z2.y= std::exp(x)*sinh(y);

return z2;
                           };

//FUNÇÃO QUE EXIBE UM NÚMERO PERPLEXO EM NOTAÇÃO ALGÉBRICA
template<typename T>
string perplex<T>::show(){
string result;

result="";
result+=to_string(x);

if(y>0)
result+="+";

result+=to_string(y);
result+="j";

return result;
                         };

//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//INICIALIZANDO OBJETOS DA CLASSE
float absolute_value, hyperbolic_angle;
perplex<float> z1(1.0, 2.0);
perplex<float> z2(1.4, 2.5);
perplex<float> z3, z4, z5, z6, z7, z8, z9;
perplex<float> z10(2.5, 1.4);

//OPERAÇÕES
cout<<"z1: "<<z1.show()<<"\n";
cout<<"z2: "<<z2.show()<<"\n";

z3=z1+z2;
z4=z2-z1;
z5=z1*z2;
z6=z1/z2;

cout<<"z1+z2: "<<z3.show()<<"\n";
cout<<"z2-z1: "<<z4.show()<<"\n";
cout<<"z1*z2: "<<z5.show()<<"\n";
cout<<"z1/z2: "<<z6.show()<<"\n";

z7=z1.conjugate();
z8=z1.inverse();
z9=z1.exp();
absolute_value=z1.absolute();
hyperbolic_angle = z10.angle();

cout<<"z1*: "<<z7.show()<<"\n";
cout<<"1/z1: "<<z8.show()<<"\n";
cout<<"exp(z1): "<<z9.show()<<"\n";
cout<<"|z1|²: "<<absolute_value<<"\n";
cout<<"Ângulo hiperbólico associado a (2.5+1.4j): "<<hyperbolic_angle<<"\n";




//FINALIZANDO A APLICAÇÃO
return 0;
          }
