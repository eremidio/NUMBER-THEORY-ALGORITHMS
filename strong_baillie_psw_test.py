#VAMOS CRIAR UM MÓDULO EM PYTHON QUE IMPLEMENTA UMA VERSÃO ROBUSTA DO TESTE DE PRIMALIDADE BAILLIE_PSW

'''
O TESTE DE PRIMALIDADE DE BAILLIE-PSW (BAILLIE-POMERANCE-SELFRIDGE-WAGSTAFF)É UM DOS TESTES
DE PRIMALIDADE MAIS EFICIENTES QUE EXISTEM. A IDEIA PRINCIPAL DO TESTE É COMBINAR O TESTE
MILLER-RABIN COM O TESTE DE (SEQUÊNCIAS DE) LUCAS. ATÉ O PRESENTE MOMENTO NÃO SE SABE DA 
EXISTÊNCIA DE NÚMEROS QUE SEJAM PSEUDORPRIMOS RELATIVAMENTE AO DOIS TESTES DE FORMA 
SIMULTÂNEA, DE FORMA QUE O TESTE FUNCIONA PARA GERAR CHAVES PARA O PROTOCOLO RSA DE ATÉ 4096 
BITS COM ELEVADO GRAU DE CONFIABILIDADE. DENTRO DO LIMITE DE 64 BITS O TESTE É DETERMINÍSTICO.

PARA UMA VERSÃO MENOS ROBUSTA (USANDO TESTES DE FERMAT NO LUGAR DE TESTES DE MILLER-RABIN) DO
TESTE PARA INTEIROS DE 64 BITS:
https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/baillie_psw_prime_test.h


PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Baillie–PSW_primality_test
                          https://en.wikipedia.org/wiki/Lucas_pseudoprime#Strong_Lucas_pseudoprimes
                          https://github.com/armchaircaver/Baillie-PSW
 
'''

#--------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS
from math import gcd, sqrt, floor, log2, log

#--------------------------------------------------------------------------------------------------------
#FUNÇÕES

#1
def trial_division(n:int)->bool:
  '''Função que implementa divisão por tentativa e erro para valores  inferiores a 1000'''

  #Variáveis locais
  root:int=int(sqrt(n))


  #Procedimentos
  #Casos triviais:
  if(n<2):
    return False
  if(n==2 or n==3):
    return True
  if(n%2==0 or n%3==0):
    return False


  #Loop principal
  for i in range(2, (root+2), 1):
    if(n%i==0):
      return False

  #Caso passe nos testes acima
  return True


#2
def quick_compositeness_check(n:int)->bool:
  '''Função usada para rápida detecção de compostos'''

  #Etapa 1: testes envolvendo classes residuais mod 210
  if((n%210) not in {1, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 121, 127, 131, 137, 139,
                    143, 149, 151, 157, 163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209}):
    return False 



  #Etapa 2: teste por fatores primos até 1000 usando o algoritmo de Euclides
  common_factor_list:list=[2305567963945518424753102147331756070, 3383080509296917481189798760796480670771162183, 262025664754470334382813071883984477441, 49766523393936228750138598082752980119549, 1227453540237014997887615651109181957903188941, 253056306993037840092244562196981381959, 879031892818978804933065306274691112009314693, 16866467815653776127243907167629319108817, 83623435734606723958852552002152901629917681, 500139990716305530696933027389294139003181]


  for tester in  common_factor_list:
    if(gcd(tester, n)>2):
      return False


  #Caso um número  passe nos testes acima um forte candidato a primo foi encontrado
  return True 



#3
def miller_rabin(n:int)->bool:
  '''Função que implementa o teste de Miller-Rabin para inteiros até 10^25, será usado como subrotina no algoritmo principal'''

  #Variáveis locais
  prime_seed:list = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113]
  n_even:int = (n-1)
  s:int = 0
  d:int=0
  y:int=0
  x:int=0
  is_prime:bool = False

  #Procedimentos
  #Caso base:
  if(n<2):
    return False
 
  #Cálculo dos parâmetros s e d usados no algoritmo  
  while((n_even%2) == 0):
    n_even //= 2
    s += 1
    d = n_even


  #Loop principal usando a base de primos 
  for a in prime_seed:
    if(a>=n):
      break

    x =pow(a, d, n)


    for i in range(s):
      y=pow(x, 2, n)
      if(y==1 and x!=1 and x!=n-1):
        return False
      x=y

    #Condições que determinam falha no teste
    if(y!=1):
      return False
    


  #Caso passe nos testes acima um provável primo foi encontrado
  return True


#4
def jacobi_symbol(a:int, n:int)->int:
  '''Função que computa o símbolo de Jacobi'''

  #Variáveis locais
  result:int = 1
 
  #Procedimentos

  #Reduzindo o expoente
  a %= n

  #Loop principal
  while a != 0:
      #Eliminando fatores primos 2
      while a % 2 == 0:
          a //= 2
          
          if( (n&7) in (3, 5)):
              result = -result
      a, n = n, a

      #Aplicando a lei da reciprocidade quadrática
      if((a&3) == 3 and (a&3) == 3):
          result = -result
      a %= n

  #Resultado
  if n == 1:
      return result
  else:
      return 0


#5
def set_D_parameter(n:int)->int:
  '''Função que determina parâmetros a serem usados no teste de Lucas'''
  
  #Variáveis locais
  D=5

  #Procedimentos
  #Loop principal 
  while(-1):
    if(jacobi_symbol(D, n)==(-1)):
      return D
  
    #Ajuste de variáveis
    abs_D:int=abs(D)+2

    if(D>0):
      D=(-1)*abs_D
    elif(D<0):
      D=abs_D


  #Caso de falha
  return 0


#6
'''
ADAPTAÇÃO IMPLEMENTAÇÃO DO TESTE DE PRIMALIDADE USANDO SEQUÊNCIAS DE LUCAS
ORIGINALMENTE DISPONÍVEL EM: https://github.com/armchaircaver/Baillie-PSW
TODOS OS CRÉDITOS AO AUTOR.
'''

#6.1
div2mod = lambda x,n: ((x+n)>>1)%n if x&1 else (x>>1)%n


#6.2
def U_V_subscript(k, n, P, D):
  '''Função que computa os k-ésimos termos da sequência lucas a menos de uma relação de congruência'''

  #Variáveis
  U:int=1
  V:int=P
  digits:list = bin(k)[2:]

  #Procedimentos
  #Loop principal
  for digit in digits[1:]:
    U, V = (U*V) % n,  div2mod(V*V + D*U*U, n)

    if digit == '1':
      U,V = div2mod(P*U + V, n), div2mod(D*U + P*V, n)

  #Resultado
  return U, V


#6.3:
def lucas_problable_prime_test(n,D,P,Q): 
  '''Função que implementa o teste de primalidade usando sequências de Lucas'''

  assert (n & 1)
  U, V = U_V_subscript(n+1, n, P, D)
  return U==0
      



#7
def strong_baillie_psw_test(n:int)->bool:
  '''Função que implementa o teste de Primalidade de Baillie-PSW'''
  
  #Etapa 1: números ineferiores a 1000 (divisão por tentativa e erro)
  if(n<1000):
    return trial_division(n)

  #Etapa 2: rápida detecção de compostos, testes por pequenos fatores primos
  if(quick_compositeness_check(n)==False):
    return False

  #Etapa 3: teste de Miller-Rabin para bases inferiores a 120
  if(miller_rabin(n)==False):
    return False


  #Etapa 4: determinação de parâmetros para a sequência de Lucas
  D:int=set_D_parameter(n)
  P:int=1
  Q:int=(1-D)//4

  
  #Etapa 5: testes de pseudoprimalidade usando sequências de Lucas
  if(lucas_problable_prime_test(P, Q, D, n)==False):
    return False


  #Etapa 6: se um número passar nos testes acima um primo foi encontrado
  return True
  


