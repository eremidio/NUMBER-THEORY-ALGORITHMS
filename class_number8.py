#VAMOS CRIAR UM PROGRAMA EM PYTHON QUE COMPUTA O NÚMERO DE CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS REAIS

'''

O NÚMERO DE CLASSE PODE SER COMPUTADO ANALITICAMENTE PARA CORPOS QUADRÁTICOS REAIS CUJO DISCRIMINANTE É FUNDAMENTAL
USANDO-SE A SEGUINTE FÓRMULA: 2h(D)R(D) = Σ(D|n){[√D/n]erfc(n√(π/D))+Ei(πn²/D)}, ONDE erfc(x) DENOTA A FUNÇÃO DE
ERRO COMPLEMENTAR E Ei(x) DENOTA A FU7NÇÃO EXPONENCIAL INTEGRAL. A SOMA É FEITA SOBRE VALORES DE n=1,2,...,
|_√|D|_|. TAL FÓRMULA FUNCIONA DE FORMA EFICIENTE PARA DISCRIMINANTES DA ORDEM DE 10^15. 


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/class_number7.h


'''


#-------------------------------------------------------------------------------------------------------------------
#1: IMPORTANDO BIBLIOTECAS
import math
from scipy.special import exp1
import gmpy2


#-------------------------------------------------------------------------------------------------------------------
#2: FUNÇÕES
def kronecker(d:int, n:int)->int:
    """
    Função que computa símbolos de Kronecker
    Uma implementação em C está disponível em: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/kronecker_symbol.h
    """
    #Casos base
    if n == 0:
        return 1 if abs(d) == 1 else 0
    if n == 1:
        return 1
    if n == -1:
        return 1 if d >= 0 else -1

    #Ajuste da paridade
    s = 1
    while n % 2 == 0:
        n //= 2
        if d % 8 in [3, 5]:
            s = -s

    #Caso base: n=2^k
    if n == 1:
        return s

    #Usando a lei da reciprocidade quadrática
    if math.gcd(d, n) != 1:
        return 0
    if d < 0:
        d = -d
        if n % 4 == 3:
            s = -s
    if d % 4 == 3 and n % 4 == 3:
        s = -s
    return s * kronecker(n, d % n)


def compute_fundamental_unit(D:int)->(int, int):
    """
      Função que computa a unidade fundamental de um corpo quadrático real
      A implementação aqui é uma adaptação da função correspondente em
      https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/class_number7.h
    """

    #Variáveis locais
    u = 0
    v = 0

    d = math.isqrt(D)
    b = d if ((D - d) & 1) == 0 else (d - 1)

    A = 0
    t = 0

    u1 = -b
    u2 = 2
    v1 = 1
    v2 = 0

    p = b
    q = 2

    #Loop principal
    while True:

        #Redução euclidiana
        A = (p + d) // q
        t = p
        p = A * q - p

        if t == p and v2 != 0:
            break

        t = A * u2 + u1
        u1 = u2
        u2 = t

        t = A * v2 + v1
        v1 = v2
        v2 = t

        t = q
        q = (D - p * p) // q

        #Cálculo da unidade fundamental para ciclos de ordem ímpar na expansão de -σ(τ)
        if q == t and v2 != 0:
            u = (u1 * u2 + D * v1 * v2) // q
            if u < 0:
                u = -u

            v = (u1 * v2 + u2 * v1) // q
            if v < 0:
                v = -v

            break

    #Cálculo da unidade fundamental para ciclos de ordem par na expansão de -σ(τ)
    if u == 0:
        u = (u2 * u2 + D * v2 * v2) // q
        if u < 0:
            u = -u

        v = (2 * u2 * v2) // q
        if v < 0:
            v = -v

    #Resultado
    return u, v


def regulator(D:int, T:int, U:int)->float:
  '''
    Função que calcula o regulador de um corpo quadrático real
  '''
  return gmpy2.log(0.5*(T+U*gmpy2.sqrt(D)))


def compute_transcedental_sum(D:int)->float:
  '''
    Função que computa o somatório da fórmula analítica para o  número de classe de corpos quadráticos reais.
  '''

  #####Variáveis locais
  partial_sum = 0.0
  limit = math.isqrt(D)
  root_D = math.sqrt(D)
  root_pi = math.sqrt(math.pi)

  ####Loop principal
  for n in range(1, limit+1):

    kr = kronecker(D, n)
    if kr == 0:
      continue

    arg1 = (root_pi*n)/root_D
    arg2 = (math.pi*n*n)/D
    C = root_D/n

    partial_sum += kr*(C*math.erfc(arg1) + exp1(arg2))

  ####Resultado
  return partial_sum


def compute_class_number(D:int, RD:float)->int:
  '''
    Função que computa o número de classe de um corpo quadrático real
  '''
  #Variáveis locais
  L:float=compute_transcedental_sum(D)

  #Resultado
  return round(L/(2*RD))



#-------------------------------------------------------------------------------------------------------------------
#3:PROGRAMA PRINCIPAL

#Recebendo input do usuário
D:int=int(input('[Inteiro] D>0:'))

#Calculando a unidade fundamental, o regulador e o número de classe de um corpo algébrico quadrático real
T, U = compute_fundamental_unit(D)
if(T<1e30 and U<1e30):
  print(f"[Unidade fundamental] η=(1/2)({T}+{U}√{D})")

RD:float=regulator(D, T, U)
print(f"[Regulador] R({D})={RD}")


hD:int=compute_class_number(D, RD)
print(f"[Número de classe] h({D})={hD}")
