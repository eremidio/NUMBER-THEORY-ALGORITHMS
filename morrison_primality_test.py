#VAMOS CRIAR UM MODULO QUE IMPLEMENTA UM TESTE DETERMINÍSTICO DE PRIMALIDADE USANDO O TEOREMA DE MORRISON

'''
O SEGUINTE TEOREMA (DEVIDO A MORRISON) PODE SER USADO PARA TESTAR  A PRIMALIDADE DE UM INTEIRO n SE UMA
FATORAÇÃO PARCIAL DE (n+1) ESTIVER DISPONÍVEL.

TEOREMA:  SEJA f UM FATOR DE (n+1) TAL QUE f>[n^(1/2)+1], a E b TAIS QUE  f(x)=x²-ax+b E Δ=a²-4b TAL
QUE (Δ|n)=(-1) (SÍMBOLO DE JACOBI) E mdc(2b,n)=1; SE PARA CADA FATOR PRIMO DE q DE f U(n+1)=0 (mod n) E 
mdc(U((n+1)/q), n)=1, ENTÃO n É PRIMO, QUALQUER FATOR PRIMO p DE n OBEDECE A RELAÇÃO p=(Δ|p) (mod F).

O PRESENTE TEOREMA É O ANÁLOGO DO TEOREMA DE POCKLINGTON (QUE USA UMA FATORAÇÃO PARCIAL DE (n-1)), QUE
EMPREGA SEQUÊNCIAS DE LUCAS DO PRIMEIRO TIPO USANDO UMA FATORAÇÃO PARCIAL DE (n+1).

TEOREMAS MAIS SOFISTICADOS DETERMINAM CONDIÇÕES PARA QUE A EXTRAÇÃO DE FATORES PRIMOS DE ORDEM DE 
GRANDEZA n^k COM k<(1/2) SEJAM  SUFICIENTES PARA FORNECERUM CERTFICADO DE PRIMALIDADE DE UM NÚMERO
(VER REFERÊNCIAS).

PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          https://t5k.org/prove/prove3_2.html


'''


######################################################################################################################
#
#0: IMPORTANDO BIBLIOTECAS NECESSÁRIAS
from sympy import factorint
from gmpy2 import gcd
from math import log, sqrt




######################################################################################################################
#
#1: FUNÇÕES AUXILIARES

#1.1
def extract_prime_factors(n:int)->list:
    '''Função que coleta fatores primos cujo produro seja superior a sua raíz quadrada do número a ser testado'''

    #Variáveis locais
    factorization_dict:dict=factorint((n+1)) #Invocamos a rotina que decompõe (n+1) em fatores primos usando a biblioteca sympy
    prime_factor_list:list=[]
    root:int=int(sqrt(n))
    factored_part:int=1

    #Procedimentos
    
    #Coletando fatores primos de (n-1)
    temp_list:list=[]
    for key, value in factorization_dict.items():
        temp_list.append(key)

    #Reduzindo a lista de fatores primos: o critério de Morrison pode ser testado apenas em fatores primos
    #tais que a porção fatorada seja superior a raíz quadrada do número a ser testado
    for i in range((len(temp_list)-1), 0, (-1)):
        prime_factor_list.append(temp_list[i])
        factored_part*=temp_list[i]

        if(factored_part>root):
            break
        
    #Resultado
    return prime_factor_list



#2.2
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


#2.3
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


#2.4
'''Função auxiliar para computar sequências de Lucas do primeiro tipo a menos de uma relação de congruência'''
div2mod = lambda x,n: ((x+n)>>1)%n if x&1 else (x>>1)%n


#2.5
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


#2.6
def U_V_subscript2(k, P, D):
  '''Função que computa os k-ésimos termos da sequência de Lucas'''

  # Variáveis
  U = 1
  V = P
  digits = bin(k)[2:]

  ####Procedimentos
  #Loop principal
  for digit in digits[1:]:
    U, V = U * V, (V * V + D * U * U)  

    if digit == '1':
      U, V = P * U + V, D * U + P * V  

  #Resultado
  return U


######################################################################################################################
#
#2: ALGORITMO PRINCIPAL


#2.1
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


#2.2
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


#2.3:
def lucas_problable_prime_test(n:int, D:int, P:int, Q:int): 
  '''Função que implementa o teste de primalidade usando sequências de Lucas'''

  assert (n & 1)
  U, V = U_V_subscript(n+1, n, P, D)
  return U==0
      

#2.4
def morrison_primality_test(n:int)->bool:
  '''Função que implementa o teste de primalidade usando o teorema de Morrison'''

  #Casos bases: números inaferores a 1000
  if(n<1000):
    if(trial_division(n)==True):
      return True
    else:
      return False

  #Teste para rápida detecção de compostos usando aritmética modular básica e busca por pequenos fatores primos
  if(quick_compositeness_check(n)==False):
    return False

  #Variáveis locais
  D:int=set_D_parameter(n)
  bound:int=1000
  P:int=1
  Q:int=(1-D)//4
  lucas_index:int=1
  Uk:int=0
  negative_results:int=0


  ####Procedimentos  

  #Etapa 1: calculando fatores primos de (n-1)
  prime_factor_list:list=extract_prime_factors(n)
  

  while(P<bound):

    #Etapa 2: Teste de Lucas
    if(lucas_problable_prime_test(n,D,P,Q)==False and D>bound):
      return False


    #Etapa 3: Busca por fatores primos de n
    for p in prime_factor_list:
      lucas_index=(n+1)//p
      Uk=U_V_subscript2(lucas_index, P, D)
      if(gcd(n, Uk)>1 and P>bound):
        return False

    #Atualizando variáveis para a próxima iteração
    Q+=(P+1)
    P+=2


  #Caso passe nosteste acima um primo foi encontrado
  return True
  




