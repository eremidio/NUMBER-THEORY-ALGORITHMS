//VAMOS CRIAR UM PROGRAMA QUE CALCULAS AS CHAMADAS SEQUÊNCIAS DE FAREY

/*
AS CHAMADAS SEQUÊNCIAS DE FAREY SÃO SEQUÊNCIAS DE FRAÇÕES COMPLETAMENTE REDUZIDAS.
ESTAS SEQUÊNCIAS NORMALMENTE SÃO RESTRITAS ENTRE 0 E 1.

AS SEQUÊNCIAS DE FAREY SÃO MUITO IMPORTANTES EM DIVERSAS ÁREAS DA MATEMÁTICA TENDO UMA RELAÇÃO DIRETA COM A CONJECTURA DE 
COLLATZ, A HIPÓTESE DE RIEMANN, APROXIMAÇÃO DE IRRACIONAIS, CICLOS DE FORD EM GEOMETRIA, TEORIA DOS FRACTAIS, ALÉM DE APARECER
EM UMA SÉRIE DE RELAÇÕES EXTREMAMENTE ÚTEIS ENVOLVENDO FUNÇÕES ESPECIAIS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Farey_sequence

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef FAREY_SEQUENCE_H
#define FAREY_SEQUENCE_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>


//CONSTANTES GLOBAIS
enum ordering{Up, Down};

//*************************************************************************************************************************
//CLASSE DE FRAÇÕES 
struct fraction{
int x;
int y;
//Construtores
fraction(){ };
fraction(int a, int b){
x=a; y=b;
                      };
               };

//*************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
void generate_farey_sequence(int);
bool compare_fractions(fraction, fraction);
int euclides_algorithm(int, int);

//*************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para cálculo do mmc  de dois números
int euclides_algorithm(int a, int b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                    };

//Função que compara duas frações
bool compare_fractions(fraction a, fraction b){
return ((a.x)*(b.y))>((a.y)*(b.x));
                                              };


//Função que gera uma sequência de Farey
void generate_farey_sequence(int n, enum ordering x){
//Variáveis locais
fraction element;
std::vector<fraction> fraction_vector;
int d, n1;//Denominador, numerador de frações


//Procedimentos
//Ajuste de variáveis 
fraction_vector.resize(0);

//Gerando o primeiro e o último elemento da sequência de Farey
element.x=0;
element.y=1;
fraction_vector.push_back(element);
element.x=1;
element.y=1;
fraction_vector.push_back(element);

//Gerando a frações redutíveis que compõe a sequência de Farey
for(d=2; d<=n; ++d){
for(n1=1; n1<d; ++n1){
if(euclides_algorithm(n1, d)==1){
element.x=n1;
element.y=d;
fraction_vector.push_back(element);
                               };
                     };
                   };

//Ordenando as frações em ordem crescente
if(x==Up)
std::sort(fraction_vector.begin(), fraction_vector.end(), compare_fractions);
if(x==Down){
std::sort(fraction_vector.begin(), fraction_vector.end(), compare_fractions);
std::reverse(fraction_vector.begin(), fraction_vector.end());
           };

//Printando a sequência de Farey na Tela
std::cout<<"F("<<(n-1)<<") = {";
for(int i = 0; i<fraction_vector.size(); ++i){
if(i==0)
std::cout<<fraction_vector[i].x<<"/"<<fraction_vector[i].y;
if(i>0)
std::cout<<", "<<fraction_vector[i].x<<"/"<<fraction_vector[i].y;
                                             };
std::cout<<"}\n";

                                                    };

//*************************************************************************************************************************
//FIM DO HEADER
#endif
