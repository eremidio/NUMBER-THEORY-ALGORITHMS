/*Vamos escrever um programa que calcula o valor de pi usando o método de Monte Carlo*/

/*Cabeçalho inncluindo os arquivos mestres e os namespaces usados*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;


int main(){
//Semente para a geração de números aleatórios
srand(time(NULL));
//Definindo as variáveis
int n_quadrado, n_circulo;
float lado, x, y, n, pi, distancia;
//Entrada manual de dados
cout<<"Quantos pontos você deseja usar para calcular o valor de pi?\n";
cin>>n_quadrado;
//Atualizando as variáveis usadas no programa
n_circulo=0;
n=0;
lado=1.0;
//Computando o valor de pi
for(n=0;n<=n_quadrado; n++)
{x=float(rand()%100001)/100000;
y=float(rand()%100001)/100000;
distancia=sqrt(pow(x,2)+pow(y,2));
if(distancia<=1)
n_circulo++;
else if(distancia>1)
continue;
};
pi=float(4.0*n_circulo)/n_quadrado;
cout<<"O valor calculado de pi pelo método de Monte carlo é "<< pi<< ".\n";
return 0;

}
