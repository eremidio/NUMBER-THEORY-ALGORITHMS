//ESTE ARQUIVO CONTERÁ ROTINAS USADAS NA COLETA DE DADOS NO ALGORITMO DA PENEIRA QUADRÁTICA


//**********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_SIEVE_DATA_COLECTION_H
#define QUADRATIC_SIEVE_DATA_COLECTION_H
#include"quadratic_sieve_class.h"

//********************************************************************************************************************************************
//FUNÇÕES
//Função que calcula uma base números primos a serem usados no algoritmo
void quadratic_sieve::set_prime_base(){
//Variáveis locais
int64_t i;

//Procedimentos
//Ajuste de variáveis
prime_base.resize(0);
prime_base.push_back(2);

//Loop principal
for(i=3; i<smoothness_bound; ++i){
if(is_int64_prime(i)==false)
continue;

else{
//Usando o critério de Euler para computar os símbolos de Legendre
__int128_t power=(i-1)/2;

if(mod_bin_pow(number, power, i)==1)
prime_base.push_back(i);
    };
                                 };

//TESTE
//for(auto x: prime_base)
//printf("%li ", x);
//printf("\n");
                                      };



//Função que realiza a peneira de números suaves em relação a base de primos selecionada
void quadratic_sieve::sieving_algorithm(){
//*******************************************
//Ajuste de variáveis
sieve_complete=true;//Variável de controle usada para vereficar se o processo de seleção de candidatos para as relações constitutivas foi bem sucedido
a_squared_vector.resize(0);
b_vector.resize(0);

//Ajuste da matriz de paridade usadas no algoritmo
dimension=prime_base.size();
parity_matrix.reshape((dimension+1), dimension);

//*******************************************
//Processo de peneira 
//Variaveis locais
int64_t i, j, k, l, row_number=0, prime_power_counter;
__int128_t argument_value, polynomial_value, temp1, temp2;

//Procedimentos 
/*Vamos usar funções do 2º grau do tipo f(x)=(ax+b)²-n, onde n é o número a ser fatorado, usaremos o resultado da etapa três como um limitante inferior*/
//Iterando sobre possíveis argumentos
for(i=number_square_root; i<(number_square_root+sieve_interval); i++){

//Seleção multipolinomial. Iterando sobre diferentes polinômios
for(j=0; j<13; ++j){
argument_value=(linear_vector1[j]*i)+linear_vector2[j]; //argument_value=(ax+b)
temp1=(argument_value*argument_value);//temp1=argument_value²
polynomial_value=(temp1-number)%number;//p(x)=(temp1²-n)(mod n)
temp2=polynomial_value;//temp2=p(x)

//Ajuste de variáveis
prime_expansion_vector.resize(0);

//Checagem se o valor produzido é suave em relação a base de primos selecionados
for(auto x:prime_base){
prime_power_counter=0;
while((temp2%x)==0){
prime_power_counter++;
temp2/=x;
                   };

prime_expansion_vector.push_back(prime_power_counter);
                      };

//Caso afirmativo uma linha é adicionada a matriz de paridade
if(temp2==1){
//Copiando os valores  de a(N)² e b(N)
a_squared_vector.push_back(temp1);
b_vector.push_back(polynomial_value);

//Gerando uma linha na martriz de paridade
for(k=0; k<dimension; ++k)
parity_matrix.matrix[row_number][k]=(prime_expansion_vector[k])%2;

//Atualizando variáveis para a próxima iteração
row_number++;

//Fim da peneira
if(row_number==(dimension+1))
return;
            };

//Caso o número não seja suave
if(temp2>1)
continue;
                   };//Fim do loop sobre diferentes polinômios

                                                                      };//Fim do loop sobre possíveis argumentos 

//Se oconjunto de números suaves em relação a base de primos selecionadas não for suficiente o algoritmo se encerra
if(row_number<(dimension-1)){
printf("Não foram encontrado números suaves em quantidade suficiente sobre a base de primos selecionada\n");
sieve_complete=false;
                            };


                                         };

//Função que calcula as matrizes usadas na parte do algoritmo que envolve álgebra linear
void quadratic_sieve::build_matrices(){
//Ajuste de matrizes usadas
transpose_parity_matrix=parity_matrix.transpose();
reduced_matrix=parity_matrix*transpose_parity_matrix;
linear_dependence_vector.reshape((dimension+1), 1);

//TESTES
//parity_matrix.print_matrix();
//transpose_parity_matrix.print_matrix();
//reduced_matrix.print_matrix();
                                      };

//********************************************************************************************************************************************
//FIM DO HEADER
#endif
