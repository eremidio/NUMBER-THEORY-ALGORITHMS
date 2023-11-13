//ESTE  ARQUIVO CONTERÁ A CLASSE DO ALGORITMO DA PENEIRA GENERALIZADA DE CORPOS NÚMERICOS

/*
A PENEIRA GENERALIZADA DE CORPOS NÚMERICOS É O ALGORITMO PARA COMPUTAÇÃO CLÁSSICA MAIS EFICIENTE PARA FATORAR GRANDES NÚMEROS INTEIROS (ACIMA DE 100 DÍGITOS DECIMAIS).
ESTE ALGORITMO UTILIZA UMA IDEIA SIMILAR A PENEIRA QUADRÁTICA, BUSCANDO NÚMEROS SUAVES (COMPLETAMENTE FATORADOS) EM RELAÇÃO A UMA BASE DE PRIMOS PREVIAMENTE ESCOLHIDA. 
PORÉM, NA DETERMINAÇÃO DESTES NÚMEROS A PENEIRA GENERALIZADA DE CORPOS NÚMERICOS USA CORPOS ALGÉBRICOS Q(α)=aα+b, COM a,b INTEIROS PARA PRODUZIR UM PAR DE INTEIROS
x E y TAIS QUE x²=y² (mod n), ONDE n É O NÚMERO A SER FATORADO. O USO DESTES CONSTRUTOS PERMITE A ESCOLHA DE NÚMEROS SUAVES USANDO NÚMEROS DE ORDENS DE GRANDEZA SE
COMPARADOS A PENEIRA QUADRÁTICA (NA QUAL A BUSCA POR NÚMEROS SUAVES ENVOLVE VALORES DA ORDEM n^(1/2)).

A ESSÊNCIA DO ALGORITMO SE BASEIA NO SEGUINTE TEOREMA: SEJA α UMA RAIZ DE UM POLINÔMIO f(x) COM COEFICIENTES INTEIROS DE GRAU d TAL QUE EXISTA UM m INTEIRO TAL QUE
f(m) = 0 (mod n). ENTÃO EXISTE UM ÚNICO ISOMORFISMO ENTRE O ANEL DE POLINÔMIOS EM α DE GRAU (d-1) E O GRUPO DOS INTEIROS CONGRUENTE MÓDULO n TAL QUE:
φ(a+b)=φ(a)+φ(b); φ(ab)=φ(a)φ(b); φ(1)= 1(mod n); φ(α)=m (mod n).

EM GERAL PARA UM CORPO ALGÉBRICO Q(α)=aα+b É EXTREMAMENTE COMPLICADO REPRESENTAR SEUS ELEMENTOS EM UM COMPUTADOR. EXISTE UM TEOREMA QUE PERMITE ESTABELECER UM
ISOMORFISMO ENTRE UM Q(α) E UM PAR DE INTEIROS (r, p) COM p PRIMO TAL QUE f(r) = 0 (mod p). ISTO NOS PERMITE CRIAR UMA BASE ALGÉBRICA DE FORMA EXTREMAMENTE SIMPLES E
ESTA POR SUA VEZ PODE SER EMPREGADA PARA O CÁLCULO DE NÚMERO SUAVES EM RELAÇÃO A BASE DE PRIMOS PREVIAMENTE SELECIONADA.

O ALGORITMO COMPLETO USA TRÊS DIFERENTES BASES PARA CRIAR x, y DEFINIDOS ACIMA E ENVOLVE UMA SÉRIE DE PRÉ COMPUTAÇÕES. POR ESTA RAZÃO O ALGORITMO EM QUESTÃO SÓ É
VANTAJOSO DO PONTO DE VISTA COMPUTACIONAL PARA NÚMEROS REALMENTE GRANDES NO QUAL O TEMPO GASTO NA FASE DE PREPARAÇÃO É NEGLIGENCIÁVEL. 

ALGUNS AJUSTES PRINCIPALMENTE NA ESCOLHA DOS POLINÔMIOS USADOS NO ALGORITMO FORNECEM ESPECIALIZAÇÕES PARA NÚMEROS DA FORMA n=(r^e)+s OU n=(r^e)-s, COM s E r PEQUENOS E e
GRANDE. ESTAS VERSÕES ADAPTADAS PARA NÚMEROS DESTA FORMA SÃO CHAMADAS DE PENEIRA ESPECIALIZADA DE CORPOS NÚMERICOS. ESTAS VARIANTES SÃO LIGEIRAMENTE MAIS RÁPIDAS DO QUE 
A VERSÃO MAIS GERAL.

PARA MAIORES INFORMAÇÕES:
http://www.ams.org/notices/199612/pomerance.pdf
https://www.cs.umd.edu/~gasarch/TOPICS/factoring/NFSmadeeasy.pdf#:~:text=The%20NFS%20has%20two%20common,slightly%20slower%20than%20the%20SNFS
https://en.wikipedia.org/wiki/Algebraic_number_field
https://en.wikipedia.org/wiki/Special_number_field_sieve
https://en.wikipedia.org/wiki/General_number_field_sieve
https://www.pvv.ntnu.no/~spaans/master-nfs.pdf
https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.96.6146&rep=rep1&type=pdf

*/


//*********************************************************************************************************************************************************************
//CABEÇALHO
#ifndef GENERAL_NUMBER_FIELD_SIEVE_H
#define GENERAL_NUMBER_FIELD_SIEVE_H 
#include"int128.h"
#include"mod_bin_exponentiation128.h"
#include"polynomials.h"
#include"polynomial_root.h"
#include"matrix.h"
#include"general_number_field_sieve_auxiliary_functions.h"
#include<stdio.h>

//*********************************************************************************************************************************************************************
//CLASSE DO ALGORITMO
class general_number_field_sieve{
public:
//Membros da classe
__int128_t number;//Número a ser fatorado
__int128_t factor1, factor2;//Fatores encontrados pelo algoritmo


polynomial<__int128_t> f_polynomial, f_derivative;//Polinômio usado no algoritmo
__int128_t m; //Raíz do polinômio

std::vector<__int128_t> rational_factor_base;//Base racional de primos
std::vector<__int128_t> algebraic_factor_base_r;//Base algébrica de primos
std::vector<__int128_t> algebraic_factor_base_p;//Base algébrica de primos
std::vector<__int128_t> quadratic_factor_base_r;//Base quadrática de primos
std::vector<__int128_t> quadratic_factor_base_p;//Base quadrática de primos
int64_t factor_base_upper_bound1, factor_base_upper_bound2;//Limitante para busca de fatores algébricos

std::vector<__int128_t> a_vector;//Números (a, b) suaves em relação as bases algébricas e racionais de primos
std::vector<__int128_t> b_vector;//Números (a, b) suaves em relação as bases algébricas e racionais de primos
std::vector<__int128_t> a_test_vector;//Números (a, b) suaves em relação as bases algébricas e racionais de primos
std::vector<__int128_t> b_test_vector;//Números (a, b) suaves em relação as bases algébricas e racionais de primos
__int128_t sieving_tester;//Fatores a+bm e a+bθ usados para se testar se um número completamente fatorável pelas bases fatores primos do encontrado
int64_t sieving_size, sieving_counter;//Números de pares (a, b) selecionados 
bool sieving_failure;
int64_t N, a, b; //Parâmetros usados na seleção números suaves em relação a base de primos racionais e algébrica


Matrix<int64_t> parity_matrix;//Matriz de paridade dos coeficientes de expansão dos números (a,b) nas bases de fatores primos algébricos e racionais
Matrix<int64_t> transpose_parity_matrix;//Transposta da matriz de paridade dos coeficientes
__int128_t factoring_tester;//Variável auxiliar usada no cálculo da fatoração sobre bases algébricas e racionais
std::vector<int64_t> prime_decomposition_vector;//Linha da matriz de paridade
int64_t prime_power_counter;//Expoentes de decomposição de um número em fatores primos


Matrix<int64_t> reduced_matrix, check_vector, congruence_vector;//Matrizes usadas na busca de relações do tipo x²=y² (mod n)

__int128_t rational_selection, rational_square_root;//Variáveis usadas na busca por quadrados perfeitos na base racional
__int128_t algebraic_selection, algebraic_square_root;//Variáveis usadas na busca por quadrados perfeitos na base algébrica


//Construtores e destruidores
general_number_field_sieve(){ };
virtual ~general_number_field_sieve(){ };

//Métodos da classe
//Função principal do algoritmo
void run();

//Funções de preparação da GNFS
void polynomial_root_selection();//Função de seleção de polinômio e escolha da raíz m tal que f(m)=0 (mod n)
void set_rational_factor_base();//Função que define uma base racional de fatores primos
void set_algebraic_factor_base();//Função que define uma base algébrica de fatores primos
void set_quadratic_factor_base();//Função que define uma base quadrática de fatores primos

//Funções relacionadas a peneira de números suaves em relação às bases de números algébricas e racionais
void sieving_algorithm_setup();//Função de ajuste de parâmetros do algoritmo de seleção de números suaves
void rational_sieving_algorithm();//Função que seleciona possíveis candidatos em relação a base racional de fatores primos
bool is_algebraic_factorable(__int128_t, __int128_t);//Função que determina se um número (a, b) é completamente fatorado pela base algébrica de fatores primos
void sieving_algorithm();//Função de seleção de números suaves em relação às bases de números algébricas e racionais


//Função relacionada aconstrução da matriz de fatores primos
void build_matrix();//Função que constrói a matriz de fatores primos módulo 2
void build_transpose_matrix();//Função que constrói a transposta da matriz de fatores primos módulo 2

//Funções relacionadas a determinação de uma relação do tipo x²=y² (mod n)
void congruence_finder_algorithm_setup();//Função de ajuste de parâmetros usados nocálculo de matrizes
void generate_check_vector(int64_t);//Função que gera combinações lineares das matrizes reduzidas do sistema
void congruence_finder_algorithm();//Algoritmo usado para selecionar números (a,b) usados para determinação de uma relação do tipo x²=y² (mod n)

//Funções usadas na busca por fatores primos 
void rational_square_finder_algorithm();//Função que calcula quadrados perfeitos sobre a base de fatores primos racional
void algebraic_square_finder_algorithm();//Função que calcula quadrados perfeitos sobre a base de fatores primos algébrica
void factor_calculation();//Função que calcula fatores primos

//Função que exibe o resultado do algoritmo
void print_result();
                                };


//*********************************************************************************************************************************************************************
//FIM DO HEADER
#endif
