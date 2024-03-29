//VAMOS IMPLEMENTAR O ALGORITMO DA PENEIRA RACIONAL

/*
O ALGORITMO DA PENEIRA RACIONAL É UM ALGORITMO PARA FATORAR NÚMEROS INTEIROS BASEADO NA SEGUINTE PROPOSIÇÃO:
SEJA n UM NÚMERO A SER FATORADO SE EXISTIREM a E b, TAIS QUE a²=b² mod(n), POSSÍVEIS FATORES DE n TEM A FORMA mdc(a-b, n) OU
mdc(a-b, n).
A IDEIA É USAR UMA PEQUENA BASE DE NÚMEROS PRIMOS PARA TENTAR ENCONTRAR a E b SATISFAZENDO ESTA PROPOSIÇÃO.

ESTE ALGORITMO NÃO FUNCIONA PARA NÚMEROS CONTENDO POTÊNCIAS UM ÚNICO FATOR PRIMO p^k, COM p PRIMO E k INTEIRO.
TAIS NÚMEROS PORÉM SÃO ESTATISTICAMENTE RAROS.

ESTE ALGORITMO PODE SER GENERALIZADO, USANDO-SE ÁLGEBRA E TEORIA ALGÉBRICA DE NÚMEROS PARA SE ENCONTRAR a E b MAIS RAPIDAMENTE.
GENERALIZAÇÕES COMO A PENEIRA DE CORPOS NÚMERICOS ESPECIAIS, A PENEIRA DE CORPOS NÚMERICOS GENERALIZADA E A PENEIRA QUADRÁTICA
ESTÃO ENTRE OS ALGORITMOS MAIS EFICIENTES PARA SE FATORAR NÚMEROS INTEIROS.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/General_number_field_sieve
https://en.wikipedia.org/wiki/Special_number_field_sieve,,
https://en.wikipedia.org/wiki/Quadratic_sieve
https://en.wikipedia.org/wiki/Rational_sieve

*/

//**************************************************************************************************************************
//CABEÇALHO
#if !defined RATIONAL_SIEVE_H
#define RATIONAL_SIEVE_H
#include<vector>
#include<cmath>
#include<stdint.h>

//VARIÁVEIS GLOBAIS
const uint64_t prime_seed[] ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

//**************************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que implementa o algoritmo de Euclides
uint64_t euclides_algorithm(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return euclides_algorithm(b, a%b);
                                                   };

//Função que printa um vetor de inteiros na tela (função de teste)
void print_vector(std::vector<uint64_t> vector_int){
std::cout<<"{";
for(auto y:vector_int){
std::cout<<y<<" ";
                      };
std::cout<<"}\n";
                                                   };


//Função que calcula de um número é um quadrado perfeito
bool is_square(uint64_t n){
//Procedimentos
for(uint64_t i=2; ; ++i){
if(i*i==n)
return true;
if(i*i>n)
return false;
                        };
                          };

//**************************************************************************************************************************
//CLASSE DO ALGORITMO
class rational_sieve{
public:
//Membros da classe
uint64_t number;//Número a ser fatorado
int smoothness;//Tamanho da base de primos
std::vector<uint64_t> factor_base_vector;//Base de primos
std::vector<uint64_t> number_vector1, number_vector2;//Array depossíveis candidatos para as relações constitutivas
uint64_t factor1, factor2;//Fatores
uint64_t selection1, selection2;//Candidatos que satisfazem as relações constitutivas
bool selection_check;//Variável para checar se o número de  candidatos as relações consititutivas falhou

//Métodos
void run();//Função principal
void setup();//Função que recebe input do usuário
void small_prime_test();//Função de busca por fatores primos na base escolhida
void number_selection();//Função que seleciona um conjunto de candidatos para as relações constitutivas
void fast_constitutive_relation();//Busca por fatores quadráticos encontrados na etapa anterior do algoritmo
void slow_constitutive_relation();// "     "      "        "           "       "    "     "      "     "
void generate_factors();//Função que calcula fatores do número a ser fatorado
                    };

//**************************************************************************************************************************
//MÉTODOS DA CLASSE
//Função principal - algoritmo da peneira racional
void rational_sieve::run(){
setup();
small_prime_test();
//Fatores primos encontrados
if(factor1!=0 && factor2!=0)
return;


//Número de candidatos para relações insuficientes
number_selection();

if(selection_check==false){ 
std::cout<<"Número de seleções insuficiente para as relações constitutivas!\nTeste inconclusivo!\n";
return;
                          };

//Busca rápida por números satisfazendo a relação constitutiva encotrados na etapa anterior
fast_constitutive_relation();
if(selection1>1 && selection1!=number && selection2>1 && selection2!=number){
generate_factors();
return;
                                                                            };

//Busca por números compostos satisfazendo a relação constitutiva encotrados na etapa anterior
slow_constitutive_relation();
if(selection1>1 && selection1!=number && selection2>1 && selection2!=number){
generate_factors();
return;
                                                                            };
                          };


//Função que recebe input do usuário
void rational_sieve::setup(){
std::cout<<"Digite um número inteiro para ser fatorado:\n->";
std::cin>> number;
std::cout<<"Digite um número de 1 a 168 para selecionar a profundidade da busca por fatores primos:\n->";
std::cin>> smoothness;

//Preenchendo o vetor de base de primos
factor_base_vector.resize(0);
for(int i=0; i<smoothness; ++i)
factor_base_vector.push_back(prime_seed[i]);

//TESTE 1, use um //após o teste
//std::cout<<"TESTE 1.\n";
//print_vector(factor_base_vector);

                            };

//Função de busca por fatores primos na base escolhida
void rational_sieve::small_prime_test(){
//Ajuste de variáveis
factor1=0;
factor2=0;
//Testando a base de primos selecionadas
for(int i=0; i<smoothness; i++){
if((number%(factor_base_vector[i]))==0){
factor1=factor_base_vector[i];
factor2=number/factor1;
std::cout<<"Fatores primos encontrados: "<<factor1<<" e "<<factor2<<"\n";
return;
                                       };
                               };

                                       };

//Função que seleciona um conjunto de candidatos para as relações constitutivas
void rational_sieve::number_selection(){
//Variáveis locais
int counter=0;
uint64_t candidate1, candidate2;
uint64_t i, j;

//Procedimentos
//Ajuste de variáveis
number_vector1.resize(0);
number_vector2.resize(0);
selection_check=true;

//Loop principal
for(i=2; i<number; ++i){
candidate1=i;
candidate2=candidate1+number;

//Testando a decomposição de possíveis candidatos na base escolhida
for(int j=0; j<smoothness; j++){
while((candidate1%(factor_base_vector[j]))==0)
candidate1/=factor_base_vector[j];
while((candidate2%(factor_base_vector[j]))==0)
candidate2/=factor_base_vector[j];
                               };

//Em caso de sucesso na busca os candidatos são registrados
if(candidate1==1 && candidate2==1){
counter++;
number_vector1.push_back(i);
number_vector2.push_back(i+number);
                                  };

//Fim da busca por candidatos para as relações constitutivas
if(counter==(smoothness+5))
break;
                       };

//Ajuste de variáveis
if(counter<smoothness)
selection_check=false;


//TESTE 2, use um //após o teste
//std::cout<<"TESTE 2.\n";
//print_vector(number_vector1);
//print_vector(number_vector2);

                                       };

//Busca por fatores quadráticos encontrados na etapa anterior do algoritmo
void rational_sieve::fast_constitutive_relation(){
//Variáveis locais
int i;
//Procedimentos
//Ajuste de variáveis
selection1=0;
selection2=0;

//Busca por fatores quadráticos
for(i=0; i<smoothness; ++i){
if(is_square(number_vector1[i])==true){
selection1=number_vector1[i];
selection2=number_vector2[i];
break;
                                      };
                           };


//TESTE 3, use um //após o teste
//std::cout<<"TESTE 3.\n";
//std::cout<<"Selection1: "<<selection1 <<"\n";
//std::cout<<"Selection2: "<<selection2 <<"\n";

                                                 };

//Busca por fatores quadráticos compostos encontrados na etapa anterior do algoritmo
void rational_sieve::slow_constitutive_relation(){

//Variáveis locais
uint64_t temp1, temp2;
int i, j, k;

//Procedimentos
//Ajuste de variáveis
selection1=0;
selection2=0;

//Esquadrinhando os vetores de possíveis candidatos para as relações constitutivas
for(int i=0; i<smoothness; i++){
for(int j=0; j<smoothness; j++){
//Restrição a índices repetidos
if(i==j)
continue;

temp1=number_vector1[i]*number_vector1[j];
temp2=number_vector2[i]*number_vector2[j];

//TESTE 5, use um //após o teste
//std::cout<<"TESTE 5.\n";
//std::cout<<"temp1: "<<temp1 <<"\n";
//std::cout<<"temp2: "<<temp2 <<"\n";


//Reduzindo fatores primos não quadráticos 
for(int k=0; k<smoothness; k++){
while((temp1%factor_base_vector[k])==0 && (temp2%factor_base_vector[k])==0){
temp1/=(factor_base_vector[k]);
temp2/=(factor_base_vector[k]);

                                                                           };
                               };


//TESTE 6, use um //após o teste
//std::cout<<"TESTE 6.\n";
//std::cout<<"temp1: "<<temp1 <<"\n";
//std::cout<<"temp2: "<<temp2 <<"\n";

//Caso fatores quadráticos tenham sido encontrados esta parte do algoritmo dse encerra
if(is_square(temp1)==true && is_square(temp2)==true){
selection1=temp1;
selection2=temp2;

//TESTE 7, use um //após o teste
//std::cout<<"TESTE 7.\n";
//std::cout<<"Selection1: "<<selection1 <<"\n";
//std::cout<<"Selection2: "<<selection2 <<"\n";
return;
                                                    }
                               };
                               };
                                                 };

//Função que calcula fatores do número a ser fatorado
void rational_sieve::generate_factors(){
//Variáveis locais e ajuste de variáveis
uint64_t tester1=std::sqrt(selection1)+std::sqrt(selection2);
uint64_t tester2;

if(selection1>selection2)
tester2=std::sqrt(selection1)-std::sqrt(selection2);
if(selection1<selection2)
tester2=std::sqrt(selection2)-std::sqrt(selection1);

//Calculando os fatores primos
factor1=euclides_algorithm(tester1, number);
factor2=euclides_algorithm(tester2, number);

//TESTE 4, use um //após o teste
//std::cout<<"TESTE 4.\n";
//std::cout<<"Selection1: "<<selection1 <<"\n";
//std::cout<<"Selection2: "<<selection2 <<"\n";
//std::cout<<"Factor1: "<<factor1 <<"\n";
//std::cout<<"Factor2: "<<factor2 <<"\n";

//Resultado
if(factor1>1 && factor1<number && factor2>1 && factor2<number){
std::cout<<"Fatores encontrados: "<<factor1 <<", "<<factor2<<".\n";
                                                              }
else 
std::cout<<"Teste inconclusivo.\n";
                                       };
//**************************************************************************************************************************
//FIM DO HEADER
#endif
