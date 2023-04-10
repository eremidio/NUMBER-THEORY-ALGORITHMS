//VAMOS CRIAR UM PROGRAMA EM C++ QUE IMPLMENTA A CLASSE DOS NÚMEROS DUAIS
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o dual dual.cpp

/* TEORIA:

A classe dos números duais compreende a classe de números da forma: z=(x, y) ou em notação algébrica z= x+yε, onde ε satifaz a relação: ε²=0.

As regras de adição, subtração, multiplicação, divisão de números duais são definidas respectivamente por:
(x, y) +(u, v) =(x+u, y+v) ou (x+yε)+(u+vε)=(x+u)+(y+v)ε
(x, y) -(u, v) =(x-u, y-v) ou (x+yε)-(u+vε)=(x-u)+(y-v)ε
(x, y) × (u, v) =(xu+yv, xv+yu) ou (x+yε)×(u+vε)=xu+(xv+yu)ε
(x, y)/(u, v) =(x/u, (yu-xv)/u²) ou (x+yε)/(u+vε)=(x/u)+{(yu-xv)/u²}ε

Funções analíticas pode ser definidas usando a seguinte regra: f(a+bε)=f(a)+bf'(a)ε.
Esta regra é obtida por meio da expansão em série de Taylor de uma função analítica, e usando-se o fato de que potências de ε superiores a 2 se anulam. Para polinômios obtemos uma regra exata para diferenciação.

Para maiores informações: https://en.wikipedia.org/wiki/Dual_number
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
class dual{
public:
//MEMBROS DA CLASSE
T x;
T y;
//CONSTRUTORES E DESTRUIDORES
dual(){ };
dual(T , T);
~dual();
//MÉTODOS DA CLASSE
dual<T> operator+(dual<T>);
dual<T> operator-(dual<T>);
dual<T> operator*(dual<T>);
dual<T> operator/(dual<T>);
string show();
          };

//MÉTODOS DA CLASSE
//CONSTRUTOR E DESTRUIDOR
template<typename T>
dual<T>::dual(T a, T b){
x=a;
y=b;
                       };

template<typename T>
dual<T>::~dual(){
                      };

//OPERADORES ARITMÉTICOS BÁSICOS
template<typename T>
dual<T> dual<T>::operator+(dual<T> z1){
dual z2;
z2.x=x+z1.x;
z2.y=y+z1.y;
return z2;
                                      };

template<typename T>
dual<T> dual<T>::operator-(dual<T> z1){
dual z2;
z2.x=x-z1.x;
z2.y=y-z1.y;
return z2;
                                      };

template<typename T>
dual<T> dual<T>::operator*(dual<T> z1){
dual z2;
z2.x=x*z1.x;
z2.y=(x*z1.y+y*z1.x);
return z2;
                                      };


template<typename T>
dual<T> dual<T>::operator/(dual<T> z1){
dual z2;
z2.x=x/z1.x;
z2.y=(y*z1.x-x*z1.y)/(pow(z1.x, 2));
return z2;
                                      };

//FUNÇÃO QUE EXIBE UM NÚMERO DUAL EM NOTAÇÃO ALGÉBRICA
template<typename T>
string dual<T>::show(){
string result;

result="";
result+=to_string(x);

if(y>0)
result+="+";

result+=to_string(y);
result+="ε";

return result;
                     };

//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//INICIALIZANDO OBJETOS DA CLASSE
dual<float> z1(1.2, 2.67);
dual<float> z2(2.001, 2.323);
dual<float> z3, z4, z5, z6;
 
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

//FINALIZANDO A APLICAÇÃO
return 0;
          }
