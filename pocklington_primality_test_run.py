#PROGRAMA PARA TESTAR O ARQUIVO COM O PROGRAMA DO TESTE DE PRIMALIDADE DE POCKLINGTON-LEHMER

#IMPORTANDO AS DEPENDÊNCIAS NECESSÁRIAS
from pocklington_primality_test import pocklington_primality_test


#PROGRAMA PRINCIPAL

#RECEBENDO INPUT DO USUÁRIO
n:int = int(input('Digite um inteiro cuja primalidade será testada:'))

#TESTE DE PRIMALIDADE
test:bool=pocklington_primality_test(n)
print('OK!')

