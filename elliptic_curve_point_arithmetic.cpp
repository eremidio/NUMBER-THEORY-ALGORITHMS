//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO elliptic_curve_point_arithmetic.h
//VAMOS COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o elliptic_curve_point_arithmetic elliptic_curve_point_arithmetic.cpp


//Cabeçalho
#include"elliptic_curve_point_arithmetic.h"
#include"tonelli_shanks.h"
#include<iostream>
using namespace std;


//Função principal
int main(){

  //Teste do algoritmo de euclides
  int64_t gcd, inv=modular_inverse<int64_t>(34, 109, gcd);
  cout<<inv<<'\n';
  cout<<gcd<<'\n';
  if(gcd==1)
    cout<<"Algoritmo extendido de Euclides testado com sucesso.\n";
  else return 0;


  //Variáveis locais
  elliptic_curve<int64_t> e_curve;
  elliptic_curve_point<int64_t> ec_point1, ec_point2={22,860,1}, ec_neg, ec_sum, ec_double, ec_sub, ec_mul;
  int64_t n, temp;

  //Procedimentos
    //Recebendo input do usuário
    //Curva:
    cout<<"Parâmetro 'a' da curva: ";
    cin>>e_curve.a;
    cout<<"Parâmetro 'b' da curva: ";
    cin>>e_curve.b;
    cout<<"Parâmetro 'p' (primo que define a ordem de GF(p)): ";
    cin>>e_curve.p;

    //Ponto na curva:
    ec_point1.z=1;
    cout<<"Coordenada x: ";
    cin>>ec_point1.x;
    temp=((ec_point1.x*ec_point1.x*ec_point1.x)%e_curve.p+(ec_point1.x*e_curve.a)%e_curve.p+e_curve.b)%e_curve.p;
    ec_point1.y=tonelli_shanks(temp, e_curve.p);


    cout<<"Curva elíptica: y²=x³+"<<e_curve.a<<"x+"<<e_curve.b<<'\n';
    cout<<"P: ("<<ec_point1.x<<","<<ec_point1.y<<","<<ec_point1.z<<")\n";
    cout<<"Q: ("<<ec_point2.x<<","<<ec_point2.y<<","<<ec_point2.z<<")\n";

    //Teste de inversão de ponto na curva
    ec_neg=point_negation<int64_t>(ec_point1);
    cout<<"[-1]P: ("<<ec_neg.x<<","<<ec_neg.y<<","<<ec_neg.z<<")\n";

    //Soma, subtração e duplicação de pontos na curva
    ec_sum=point_addition<int64_t>(ec_point1, ec_point2, e_curve);
    ec_double=point_doubling<int64_t>(ec_point1, e_curve);
    ec_sub=point_subtraction<int64_t>(ec_point1, ec_point2, e_curve);

    cout<<"P+Q: ("<<ec_sum.x<<","<<ec_sum.y<<","<<ec_sum.z<<")\n";
    cout<<"2P: ("<<ec_double.x<<","<<ec_double.y<<","<<ec_double.z<<")\n";
    cout<<"P-Q: ("<<ec_sub.x<<","<<ec_sub.y<<","<<ec_sub.z<<")\n";
    

    //Multiplicação por escalar
    cout<<"[Inteiro] n: ";
    cin>>n;

    ec_mul=point_scalar_multiplication<int64_t>(ec_point1, e_curve, n);
    cout<<"["<<n<<"]P: ("<<ec_mul.x<<","<<ec_mul.y<<","<<ec_mul.z<<")\n";  

  //Finalizando a aplicação
  return 0;

}
