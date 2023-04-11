//VAMOS ESCREVER UM PROGRAMA EM FORTRAN QUE IMPLEMENTA A CLASSE DOS QUANTERNIÕES EM C++
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o quaternion quaternion.cpp 

/*QUANTERNIÕES SÃO UMA GENERALIZAÇÃO DOS NÚMEROS COMPLEXOS. EM GERAL SÃO EXPRESSOS COMO UMA ÉNUPLA: q=(a.1+b.i+c.j+d.k).
NO QUAL AS OPERAÇÕE DE ADIÇÃO E MULTIPLICAÇÃO SÃO DEFINIDAS, RESPECTIVAMENTE, PELAS RELAÇÕES:
(a1.1+b1.i+c1.j+d1.k)+(a2.1+b2.i+c2.j+d2.k)=(a1+a2)1+(b1+b2)i+(c1+c2)j+(d1+d2)k

ii=jj=kk=(ij)k=-1, ij=-ji=k, jk=-kj=i, ki=-ik=j ------>
(a1.1+b1.i+c1.j+d1.k)×(a2.1+b2.i+c2.j+d2.k)=(a1a2-b1b2-c1c2-d1d2) + (c1d2-d1c2+a1b2+b1a2)i + (d1b2-b1d2+a1c2+c1a2)j +
(b1c2-c1b2+a1d2+d1a2)k

O CONJUGADO DE UM QUATERNIÃO q=(a1.1+b1.i+c1.j+d1.k) É q*=(a1.1-b1.i-c1.j-d1.k)
O MÓDULO QUADRADO DE q=(a.1+b.i+c.j+d.k) É |q|²=qq*=a²+b²+c²+d².
O INVERSO MULTIPLICATIVO DE q=(a.1+b.i+c.j+d.k) É DADO POR: 1/q=(q*)/|q|²=(a.1-b.i-c.j-d.k)/(a²+b²+c²+d²).

A DIVISÃO POR SUA VEZ É DADA POR:
(a1.1+b1.i+c1.j+d1.k)/(a2.1+b2.i+c2.j+d2.k)={(a1a2+b1b2+c1c2+d1d2)+ (-c1d2+d1c2-a1b2+b1a2)i + (-d1b2+b1d2-a1c2+a2c1)j +
(-b1c2+c1b2-a1d2+d1a2)k }/{(a2)²+(b2)²+(c2)²+(d2)²}.

A ÁLGEBRA DOS QUATERNIÕES DETERMINA SIMULTANEAMENTE A REGRA ENVOVENDO O PRODUTO ESCALAR E VETORIAL NO ESPAÇO EUCLIDIANO EM
TRÊS DIMENSÕES. NA MULTIPLICAÇÃO DE DOIS QUATERNIÕES COM O PRIMEIRO COEFICIENTE NULO, O PRIMEIRO TERMO CORRESPONDE AO PRODUTO
ESCALAR, AO PASSO QUE OS DEMAIS TERMOS CORRESPONDE AO PRODUTO VETORIAL DE DOIS VETORES (USANDO A BASE i, j, k PARA O ESPAÇO 3D
EUCLIDIANO).


UMA OPERAÇÃO DO TIPO qVq-¹, ONDE q É UMA QUATERNIÃO DE MÓDULO 1 E V É UM VETOR NO ESPAÇO EUCLIDIANO É USADA PARA REPRESENTAR ROTAÇÕES NO ESPAÇO TRIDIMENSIONAL. QUATERNIÕES UNITÁRIOS FORMAM O GRUPO ESTRUTURAL DA ESFERA S³ Spin(3) QUE É ISOMÓRFICO A SU(2), QUE POR SUA VEZ É UMA COBERTURA UNIVERSAL DO GRUPO SO(3) DE ROTAÇÕES EM 3D.
MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Quaternion
*/



//***************************************************************************************************************************
/*CABEÇALHO*/
#include<iostream>
#include<cmath>
#include<string>
using namespace std;


//***************************************************************************************************************************
//CLASSE DO QUATERNIÕES
template<typename T>
class quaternion{
public:
//MEMBROS DA CLASSE
T a;
T b;
T c;
T d;
//CONSTRTUTORES E DESTRUIDORES
quaternion(){ };
quaternion (T , T, T, T);
~quaternion();
//MÉTODOS DA CLASSE
quaternion<T> operator+(quaternion<T>);
quaternion<T> operator-(quaternion<T>);
quaternion<T> operator*(quaternion<T>);
quaternion<T> operator/(quaternion<T>);
T absolute();
quaternion<T> conjugate();
quaternion<T> inverse();
string show();
                };

//MÉTODOS DA CLASSE
//CONSTRUTORES E DESTRUIDORES
template<typename T>
quaternion<T>::quaternion(T x1, T x2, T x3, T x4){
a=x1;
b=x2;
c=x3;
d=x4;
                                                 };

template<typename T>
quaternion<T>::~quaternion(){
                            };

//OPERADORES ARITMÉTICOS BASICOS
template<typename T>
quaternion<T> quaternion<T>::operator +(quaternion<T> q1){
quaternion q2;
q2.a=a+q1.a;
q2.b=b+q1.b;
q2.c=c+q1.c;
q2.d=d+q1.d;
return q2;
                                                         };

template<typename T>
quaternion<T> quaternion<T>::operator -(quaternion<T> q1){
quaternion q2;
q2.a=a-q1.a;
q2.b=b-q1.b;
q2.c=c-q1.c;
q2.d=d-q1.d;
return q2;
                                                         };

template<typename T>
quaternion<T> quaternion<T>::operator *(quaternion<T> q1){
quaternion q2;
q2.a=a*q1.a-b*q1.b-c*q1.c-d*q1.d;
q2.b=c*q1.d-d*q1.c+a*q1.b+b*q1.a;
q2.c=d*q1.b-b*q1.d+a*q1.c+c*q1.a;
q2.d=b*q1.c-c*q1.b+a*q1.d+d*q1.a;
return q2;
                                                         };

template<typename T>
quaternion<T> quaternion<T>::operator /(quaternion<T> q1){
quaternion q2, q3;
T modulus;

modulus=sqrt(pow(q1.a, 2)+pow(q1.b, 2)+pow(q1.c, 2)+pow(q1.d, 2));
q2.a=q1.a;
q2.b=(-1.0)*q1.b;
q2.c=(-1.0)*q1.c;
q2.d=(-1.0)*q1.d;

q3.a=(a*q2.a-b*q2.b-c*q2.c-d*q2.d)/modulus;
q3.b=(c*q2.d-d*q2.c+a*q2.b+b*q2.a)/modulus;
q3.c=(d*q2.b-b*q2.d+a*q2.c+c*q2.a)/modulus;
q3.d=(b*q2.c-c*q2.b+a*q2.d+d*q2.a)/modulus;

return q3;
                                                         };

//OUTRAS FUNÇÕES
//FUNÇÃO QUE CALCULA O MÓDULO QUADRADO DE UM QUATERNIÃO
template<typename T>
T quaternion<T>::absolute(){
T modulus;
modulus=sqrt(pow(a, 2)+pow(b, 2)+pow(c, 2)+pow(d, 2));
return modulus;
                           };

//FUNÇÃO QUE CALCULA O INVERSO DE UM QUATERNIÃO
template<typename T>
quaternion<T> quaternion<T>::inverse(){
quaternion q2;
T modulus;

modulus=sqrt(pow(a, 2)+pow(b, 2)+pow(c, 2)+pow(d, 2));

q2.a=a/modulus;
q2.b=((-1.0)*b)/modulus;
q2.c=((-1.0)*c)/modulus;
q2.d=((-1.0)*d)/modulus;

return q2;
                                      };

//FUNÇÃO QUE CALCULA O CONJUGADO DE UM QUATERNIÃO
template<typename T>
quaternion<T> quaternion<T>::conjugate(){
quaternion q2;

q2.a=a;
q2.b=(-1.0)*b;
q2.c=(-1.0)*c;
q2.d=(-1.0)*d;

return q2;
                                        };

//FUNÇÃO QUE EXIBE UM NÚMERO PERPLEXO EM NOTAÇÃO ALGÉBRICA
template<typename T>
string quaternion<T>::show(){
string result;

result="";
result+=to_string(a);

if(b>0)
result+="+";
result+=to_string(b);
result+="i";

if(c>0)
result+="+";
result+=to_string(c);
result+="j";

if(d>0)
result+="+";
result+=to_string(d);
result+="k";

return result;
                         };


//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//INICIALIZANDO OBJETOS DA CLASSE
float q1_modulus;
quaternion<float> q1(2.56, -3.66, 1.54, 0.98);
quaternion<float> q2(9.56, 9.76, -8.54, 7.77);
quaternion<float> q3, q4, q5, q6, q7, q8;

//OPERAÇÕES
q3=q1+q2;
q4=q2-q1;
q5=q1*q2;
q6=q1/q2;

cout<<"q1: "<<q1.show()<<"\n";
cout<<"q2: "<<q2.show()<<"\n";
cout<<"q1+q2: "<<q3.show()<<"\n";
cout<<"q2-q1: "<<q4.show()<<"\n";
cout<<"q1*q2: "<<q5.show()<<"\n";
cout<<"q1/q2: "<<q6.show()<<"\n";

q7=q1.inverse();
q8=q1.conjugate();

cout<<"q1-¹: "<<q7.show()<<"\n";
cout<<"q1*: "<<q8.show()<<"\n";

//FINALIZANDO A APLICAÇÃO
return 0;



          }
