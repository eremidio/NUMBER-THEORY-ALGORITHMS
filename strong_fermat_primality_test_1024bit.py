#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VARIANTE DO TESTE DE PRIMALIDADE FERMAT CAPAZ DE DETECTAR NÚMEROS DE CARMICHAEL

'''
PARA REFERÊNCIAS: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/strong_fermat_primality_test.h
                  https://arxiv.org/pdf/math/0604376

Nota usaremos a biblioteca gmpy2 para rápida exponenciação modular. Usando a função pow() da biblioteca padrão
também funciona, para um número de 300 dígitos decimais (cerca de 1024 bits) a versão usando somente a
biblioteca padrão demora cerca de 2 horas. A versão com a biblioteca gmpy2 foi testada em inteiros da ordem de
10^500 usando gerador de números primos online. Números de Carmichael da ordem de 10^18 foram usados para se 
testar o algoritmo.

'''

#----------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS
from math import gcd, log
import gmpy2

#----------------------------------------------------------------------------------------------------------------------
#FUNÇÕES

#1
def strong_fermat_primality_test_1024bit(n:int)->bool:
  '''Função que implementa a variante determinística do teste de Fermat que detecta números de Carmichael'''
  #Casos bases:
  if(n<2):
    return False
  if(n in {2,3,5,7,11,13,17}):
    return True


  #Variáveis locais
  mod:int=0
  max_mod:int=int(2*log(n)*log(n))


  #Procedimentos
  #Etapa 1: teste de Fermat nas bases 2,3,5 para rápida detecção de compostos
  if(gmpy2.powmod(2, (n-1), n)!=1 or gmpy2.powmod(3, (n-1), n)!=1  or gmpy2.powmod(5, (n-1), n)!=1 ):
    return False


  #Etapa 2: detectando números de Carmichael que satisfazem o pequeno teorema de Fermat
  for b in range(2, max_mod+1, 1):
   if(gcd(n, b)>1):
    return False

   mod=(b-1)*n
   if(gmpy2.powmod(b, n, mod)!=b):
     return False

  #Caso passe nos testes acima um primo foi encontrado
  return True

