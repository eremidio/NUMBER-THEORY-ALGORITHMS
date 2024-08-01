#VAMOS CRIAR UM PROGRAMA EM PYTHON QUE IMPLEMENTA O ALGORTITMO DE KONYAGIN-POMERANCE PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO


'''
O TESTE DE PRIMALIDADE DE KONYAGIN-PORMERANCE É UM ALGORITMO COM TEMPO DE EXECUÇÃO POLINOMIAL
QUE PERMITE DETECTAR A PRIMALIDADE DE UM INTEIRO n PROVIDO QUE UMA FATORAÇÃO COMPLETA DE
(n-1) SEJA PROVIDÊNCIADA.

A IDEIA FUNDAMENTAL DO ALGORITMO É QUE USANDO A FATORAÇÃO COMPLETA DE (n-1) PODEMOS DETERMINAR
PARA UM INTEIRO a, COPRIMO COM n FACILMENTE A SUA ORDEM MULTIPLICATIVA, ISTO É, O MENOR
INTEIRO r TALQUE QUE a^r=1 (mod n). TESTES ENVOLVENDO A ORDEM MULTIPLICATIVA DE UM GRUPO
FINITO COMBINADO COMO TESTE DE FERMAT NOS PERMITEM DETERMINAR A PRIMALIDADE DO NÚMERO A SER
TESTADO.

PARA MAIORES INFORMAÇÕES: Number Theoretical Algorithms in Criptography by O. N. Vasilenko

''' 

#-------------------------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO
from math import sqrt
from sympy import factorint
import gmpy2

#-------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÕES

#1
def lcm(a:int, b:int)->int:
 '''Função que calcula o mmc de dois inteiros'''
 return ((a*b)//gmpy2.gcd(a,b))

#2
def integer_factorization(n:int)->(list, list):
 '''Função que fatora um inteiro e aloca os fatores primos e seus respectivos expoentes em listas'''
 #Variáveis locais
 factorization_dict:dict=factorint(n)
 prime_list:list=[]
 exponent_list:list=[]


 #Procedimentos
 for keys,values in factorization_dict.items():
  prime_list.append(keys)
  exponent_list.append(values)
  
 #Resultado
 return prime_list, exponent_list


#2.1
def extract_prime_factors(n:int)->list:
 '''Função que fatora um inteiro e aloca os fatores primos uma lista'''
 #Variáveis locais
 factorization_dict:dict=factorint(n)
 prime_list:list=[]

 #Procedimentos
 for keys,values in factorization_dict.items():
  prime_list.append(keys)
    
 #Resultado
 return prime_list



#3
def multiplicative_order(a:int, n:int, prime_list:list, exponent_list:list)->int:
 '''Função que calcula a ordem multiplicativa de um inteiro E(a), a^E(a) =1 (mod n), provido a decomposição de (n-1) em fatores primos'''
 
 #Variáveis locais
 M:int=(n-1)
 j:int=0
 result:int=M
 N:int=len(prime_list)
 A:int=0

 #Procedimentos
 #Loop principal: a ordem multiplicativa de a deve dividir (n-1)
 while(j<(N-1)):

  #Ajuste de variáveis
  M//=pow(prime_list[j], exponent_list[j])
  A=pow(a, M)

  #Loop sobre potências do j-ésimo fator primo
  for k in range((exponent_list[j]+1)):

   if((A%n)==1 and M<result):
    result = M
    break
   else:
    M*=prime_list[j]

   temp:int=pow(a, M)
   A=temp

  #Atualizando variáveis para a próxima iteração
  j+=1

 #Resultado
 return result




#4
def generate_prime_list(n:int)->list:
 '''Função que gera uma pequena lista de números primos até log²(n)+1, onde n é o valor a ser testado'''

 #Variáveis locais
 limit:int=int((gmpy2.log(n)*gmpy2.log(n))+1)
 small_prime_list:list=[]

 #Procedimentos
 for i in range(2, (limit+1)):
  if(gmpy2.is_prime(i)):
   small_prime_list.append(i)


 #Resultado
 return small_prime_list


#5
def konyagin_pomerance_primality_test(n:int)->bool:
 '''Função que implementa o teste de primalidade de Konyagin-Pomerance para testar a primalidade de um inteiro'''

 #Casos triviais
 if(n<100):
  return small_prime_check(n)

 #Variáveis locais
 small_prime_list:list=generate_prime_list(n) #Estágio 1 do algoritmo
 root_n:int=int(sqrt(n))
 Fa:int=1
 Fa_1:int=1 #F(1)=1
 prime_order:int=0
 n_minus_prime_factors:list=None
 n_minus_exponents:list=None
 multiplicative_order_prime_factors:list=None

 #Procedimento
 #Teste por divisão com primos inferiores a 100
 for prime in small_prime_list:
  if(n==prime):
   return True
  if((n%prime)==0):
   return False

 #Calculando a lista de fatores primos e expoentes de (n-1)
 n_minus_prime_factors, n_minus_exponents=integer_factorization((n-1))


 #Loop principal
 for a in small_prime_list:

  #Calculando o valor da função F(a)
  if(gmpy2.is_prime(a)==False or (gmpy2.is_prime(a)==True and gmpy2.powmod(a, Fa_1, n)==1)):
   Fa=Fa_1
  else:
   #Teste de composição de Fermat
   if(gmpy2.powmod(a, (n-1), n)!=1):
    return False

  #Calculando a ordem multiplicativa para um primo da lista de primos pré-computados no estágio 1 do algoritmo
  prime_order=multiplicative_order(a, n, n_minus_prime_factors, n_minus_exponents)
  multiplicative_order_prime_factors=extract_prime_factors(prime_order)

 #Teste envolvendo a ordem multiplicativa de a
 tester1:int=1

 for p in multiplicative_order_prime_factors:
  tester1=tester1*(pow(a, (prime_order//p)))

 if(gmpy2.gcd(tester1, n)>1):
  return False


 #Testes envolvendo os valores de F(a)
 Fa=lcm(Fa_1, prime_order)
 if(Fa>=root_n):
  return True

 
 #Resultado: primalidade não detectada na parte principal do algoritmo
 return False

