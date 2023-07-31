//Programa simples para se calcular raiz quadrada de números inteiros positivos qudrados perfeitos

/*
A IDEIA DO ALGORITMO É EXPLORAR A RELAÇÃO:
(n+1)² = n²+2n+1, DONDE (n+1)² - n² = 2n+1
PORTANTO A RAÍZ QUADRADA DE UM NÚMERO PODE SER OBTIDA SUBTRAINDO-SE OS NÚMEROS IMPÁRES ATÉ QUE O RESULTADO SEJA ZERO.
PARA NÚMEROS QUE NÃO SÃO QUADRADOS PERFEITOS, ESTE ALGORITMO DÁ UM LIMITANTE INFERIOR PARA SUA RÁZ QUADRADA.
*/

/*CABEÇALHO*/
#include<iostream>
using namespace std;

int main(){
//Definição de variáveis	
int valor, valor_inicial, numero_impar, contador;
numero_impar=1;
contador=0;

//Comandos executáveis
cout<<"DIGITE UM NÚMERO INTEIRO:  ";
cin>>valor_inicial;
//Ajustando variável de cálculo
valor=valor_inicial;

while(valor>0){
valor=valor-numero_impar;
numero_impar=numero_impar+2;
contador++;
               };

if(valor==0)
cout<<"A RAÍZ QUADRADA DE "<< valor_inicial << " É "<<contador<<"\n";
if(valor<0)
cout<<"A RAÍZ QUADRADA DE "<< valor_inicial << " É LIMITADA INFERIORMENTE POR "<<(contador-1)<<"\n";

return 0;

}
