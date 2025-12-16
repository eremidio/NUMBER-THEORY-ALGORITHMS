#VAMOS CRIAR UM PROGRAMA EM PYTHON QUE COMPUTA O NÚMERO DE CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS IMÁGINÁRIOS
#Nota: usaremos a biblioteca Scipy que provê uma implementação da função de erro complementar erfc()

'''

O NÚMERO DE CLASSE PODE SER COMPUTADO ANALITICAMENTE PARA CORPOS QUADRÁTICOS IMAGINÁRIOS CUJO DISCRIMINANTE É FUNDAMENTAL
USANDO-SE A SEGUINTE FÓRMULA: h(D) = Σ(D|n){erfc(n√(π/D))+ (1/nπ)e^(-πn²/|D|)}; erfc(x) DENOTA A FUNÇÃO DE ERRO
COMPLEMENTAR E (|) DENOTA O SÍMBOLO DE KRONECKER, A SOMA É FEITA SOBRE VALORES DE n=1,2,..., |_√|D|ln|D|/(2π)_|

TAL FÓRMULA FUNCIONA DE FORMA EFICIENTE PARA DISCRIMINANTES DA ORDEM DE 10^15. PARA CORPOS QUADRÁTICOS REAIS EXISTE UMA
FÓRMULA SIMILAR ENVOLVENDO A FUNÇÃO EXPONENCIAL INTEGRAL Ei(x). 


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

'''


#-------------------------------------------------------------------------------------------------------------------
#1: IMPORTANDO BIBLIOTECAS
import math
from scipy.special import erfc


#-------------------------------------------------------------------------------------------------------------------
#2: FUNÇÕES AUXILIARES
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


def generate_fundamental_discriminant(d:int)->int:
    '''
    Função que computa o discriminante fundamental associado a corpo quadrático imaginário
    '''
    
    #Resultado
    if(d%4==3):
        return d*4
    return d


#-------------------------------------------------------------------------------------------------------------------
#3: FÓRMULA ANALÍTICA PARA O NÚMERO DE CLASSE
def class_number_analytical(d):
    '''
    Função que computa o número de classe de corpos algébricos quadráticos imaginários usando a fórmula analítica.
    '''

    #Caso base
    if(d>0):
        return (-1) 

    #Variáveis locais
    D:int = -d
    pi:int = math.pi
    sum_h:floar = 0.0
    bound:int = int(math.sqrt(D * math.log(D) / (2 * pi)))


    #Loop principal
    for n in range(1, bound+1):
        k:int = kronecker(D, n)
        if k == 0:
            continue
        arg1:float = n * math.sqrt(pi / D)
        arg2:float = math.sqrt(D) / (pi * n)
        sum_h += k * (erfc(arg1) + arg2 * math.exp(-pi * n**2 / D))


    #Resultado   
    return round(sum_h)


#-------------------------------------------------------------------------------------------------------------------
#4:PROGRAMA PRINCIPAL

#Recebendo input do usuário
d:int=int(input('[Inteiro] d<0:'))

#Calculando o discriminante fundamental e o número de classe h(D) do corpo algébrico quadrático imaginário associado
D:int=generate_fundamental_discriminant(d)
print(f"[Discriminante Fundamental associado] D: {D}")
print(f"[Número de classe] h({D}) =", class_number_analytical(D)) 

