#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE FELLOWS-KOBLITZ
'''
O ALGORITMO DE FELLOWS-KOBLITZ TAL COMO O ALGORITMO DE KONYAGIN-POMERANCE É
UM EFICIENTE ALGORITMO QUE PERMITE TESTAR A PRIMALIDADE DE UM NÚMERO 
INTEIRO n EM TEMPO POLINOMIAL PROVIDO QUE UMA DECOMPOSIÇÃO DE n EM FATORES
PRIMOS SEJA PROVIDENCIADA. O TESTE É DETERMINÍSTICO

PARA MAIORES INFORMAÇÕES: Algorithmic Number Theory vol. 1 by E. Bach, J. Shallit

'''

#NOTA: usaremos a bivblioteca SymPy que contém eficientes rotinas para fatorar 
#      números inteiros até 10^100 e biblioteca gmpy2 para aritmética de 
#      multiprecisão. Versão menos robusta pode ser implementadas restrigindo-se
#      as funcionalidades dispon[iveis na biblioteca padrão. 




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


#1.1
def lcm_list(number_list:list)->int:
  '''Função que calcula o lcm de uma lista de números inteiros'''
  #Caso base:
  if(len(number_list)==1):
    return number_list[0]    

  #Variáveis locais
  result:int=0
  prev:int=number_list[0]  
  next:int=number_list[1]
  

  #Procedimentos
  #Primeira parcela do cálculo
  result=lcm(next, prev)
  if(len(number_list)==2):
    return result

  #Loop sobre os elementos da lista
  for j in range(2, len(number_list), 1):
    prev=result
    next=number_list[j]
    result=lcm(prev, next)

    if(j==(len(number_list)-1)):
      break


  #Resultado 
  return result
  

#2
def integer_factorization(n:int)->(list, list):
  '''Função que fatora um inteiro e aloca os fatores primos e seus respectivos expoentes em listas'''

  #Variáveis locais
  factorization_dict:dict=factorint(n)
  prime_list:list=[]
  exponent_list:list=[]


  #Procedimentos: loop principal
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

  
  #Procedimentos: loop principal
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
  N:int=len(prime_list)
  A:int=0
  result:int=M


  #Procedimentos
  #Loop principal: a ordem multiplicativa de a mod n deve dividir (n-1)
  while(j<(N-1)):

    #Ajuste de variáveis
    M//=pow(prime_list[j], exponent_list[j])
    A=pow(a, M)

    #Loop sobre potências do j-ésimo fator primo
    for k in range((exponent_list[j]+1)):
      if((A%n)==1 and M<=result):
        result=M
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
def fellows_koblitz_primality_test(n:int)->bool:
  '''Função que implementa o teste de primalidade de Fellow-Koblitz para testar a primalidade de um número inteiro'''

  #Casos bases: primos inferiores a 100
  if(n<2):
    return False

  prime_under100:list=[2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]
  for p in prime_under100:
    if(n==p):
      return True
    if((n%p)==0):
      return False


  #Etapa 1: fatorando n-1
  n_prime_factor_list:list=None
  n_exponent_list:list=None
  n_prime_factor_list, n_exponent_list=integer_factorization((n-1))

  #Variáveis locais

  #Etapa 2: loop principal do algoritmo
  #2.1: variáveis locais
  multiplicative_order_list:list=[]
  order:int=0
  limit:int=int(gmpy2.log(n)*gmpy2.log(n))

  #2.2: procedimentos  
  for a in range(2, limit+1, 1):

    #2.2.1:Teste de Fermat para rápida detecção de compostos
    if(gmpy2.powmod(a, (n-1), n)!=1):
      return False
    

    #2.2.2: Testes envolvendo a ordem multiplicative ord(a) mod n
    order=multiplicative_order(a, n, n_prime_factor_list, n_exponent_list)
    multiplicative_order_list.append(order)

    order_prime_factors:list=extract_prime_factors(order)
    for f in order_prime_factors:
      factor:int=gmpy2.gcd(n, (pow(a, (order//f)) -1) )
      if(factor>1 and factor<n): #Fator trivial de n encontrado
        print("Fator de ", n, " encontrado: ", factor)
        return False
  


  #Etapa 3: teste adicional envolvendo ordem multiplicativas de  ord(a) mod N para a=2,...,log²(n)
  h:int=lcm_list(multiplicative_order_list)
  if(h<gmpy2.sqrt(n)):
    return False


  #Caso passe nos testes acima um primo foi encontrado
  return True






