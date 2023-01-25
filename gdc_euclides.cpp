//VAMOS ESCREVER UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE EUCLIDES PARA SE CALCULAR O MDC DE DOIS NÚMEROS INTEIROS

/*EXPLICAÇÃO DO ALGORITMO DE EUCLIDES:

DADOS DOIS NÚMEROS 'A' E 'B' COM A>B DIVIMOS A POR B E OBTEMOS A SEGUINTE EXPRESSÃO A=P(0)*B+Q(0) COM Q(0)<B, EM SEGUIDA PROSSEGUIMOS COM B=Q(0)*P(1)+Q(1)--> Q(0)=Q(1)*P(2)+Q(2) --> Q(1)=Q(2)*P(3)+Q(3) -->  ...
REPETE-SE ESSE CÁLCULO ATÉ QUE O N-ÉSIMO TERMO DA SEQUÊNCIA SEJA Q(N)=0. O MÁXIMO DIVISOR COMUM DE A E B É O TERMO Q(N-1).

*/

/*CABEÇALHO*/
#include<iostream>
using namespace std;


int main(){
//DEFINIÇÃO DE VARIÁVEIS
long long int numero1, numero2, resto;
long long int valor1, valor2;

//PROCEDIMENTOS EXECUTÁVEIS
//ENTRADAS DE DADOS
cout<<"Digite o primeiro número inteiro:\n";
cin>>numero1;

cout<<"Digite o segundo número inteiro:\n";
cin>>numero2;

valor1=numero1;
valor2=numero2;


//CALCULANDO O MDC E MOSTRANDO OS PASSOS DO CÁLCULO
cout<<"Redução de euclides:\n";
do{
cout<<numero1 << " "<<numero2<<"\n";
resto=(numero1%numero2);
numero1=numero2;
numero2=resto;

  }while(resto>0);

cout<<"\nO máximo divisor comum de "<<valor1<< " e "<<valor2<< " é "<<numero1<<".\n";
return 0;


}
