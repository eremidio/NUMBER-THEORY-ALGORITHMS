#PROGRAMA PARA TESTAR O ARQUIVO COM O PROGRAMA DO TESTE DE PRIMALIDADE DE POCKLINGTON-LEHMER

#IMPORTANDO AS DEPENDÊNCIAS NECESSÁRIAS
from konyagin_pomerance_primality_test import konyagin_pomerance_primality_test


#PROGRAMA PRINCIPAL

#RECEBENDO INPUT DO USUÁRIO
n:int = int(input('Digite um inteiro cuja primalidade será testada:'))

#TESTE DE PRIMALIDADE
test:bool=konyagin_pomerance_primality_test(n)

if(test):
 print(n, ' é primo')
else:
 print(n, ' não é primo')

print('OK!')
 
