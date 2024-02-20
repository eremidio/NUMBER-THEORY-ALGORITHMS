#VAMOS CRIAR UM PROGRAMA EM PYTHON QUE IMPLEMENTA A PENEIRA DE PRITCHARD PARA CALCULAR NÚMEROS PRIMOS
#NOTA: Usaremos o tipo set disponível como padrão como container principal durante o algoritmo, por permitir operações com conjuntos matemáticos de forma simples.


'''
A PENEIRA DE PRITCHARD É UM ALGORITMO USADO PARA GERAR UMA LISTA DE NÚMEROS PRIMOS ATÉ UM DETERMINADO LIMITE.
FOI O PRIMEIRO ALGORITMO DE PENEIRA PARA GERAÇÃO DE NÚMEROS PRIMOS COM TEMPO DE EXECUÇÃO SUBLINEAR. AO CONTRÁRIO DA PENEIRA DE ERATÓSTENES QUE PERCORRE A LISTA DE
POSSÍVEIS CANDIDATOS A PRIMOS REPETIDAS VEZES, A PENEIRA DE PRITCHARD USA 'RODAS' DE TAMANHOS DIFERENTES EM TAMANHO CRESCENTE PARA COMPUTAR NÚMEROS PRIMOS, DESTA FORMA
O NÚMERO DE INTEIROS NÃO PRIMOS DESCARTADOS É CONSIDERAVELMENTE MENOR, O QUE POR SUA VEZ AUMENTA A EFICIÊNCIA DO ALGORTIMO.

UM EXEMPLO DE COMO O ALGORITMO É EXECUTADO NO CASO PARA COMPUTAR PRIMOS ATÉ 30:
R(i) PARA i INTEIRO DENOTA A i-ÉSIMA RODA, l O TAMANHO DA RODA E p DENOTA O CONJUNTO DE PRIMOS.

NO ALGORITMO INICIAMOS COM UMA RODA DE TAMANHO 1, CONTENDO APENAS UM ELEMENTO R(0)={1} E p={}.

O PROXÍMO INTEIRO É ENTÃO MARCADO COMO PRIMO NO CASO 2, E A RODA É EXTENDIDO PARA l=1X2=2. R(1)={1, 2} E p={2}.
OS MÚLTIPLOS DE ELEMENTOS DO CONJUNTO p EM R(1) SÃO DESCARTADOS E NO CASO R(1)={1}.

O PRÓXIMO INTEIRO É ENTÃO MARCADO COMO PRIMO, NO CASO 3 E A RODA É ENTENDIDA ATÉ l=1X2X3=6. R(2)={1,3,4,5,6} E p={2,3}.
OS MÚLTIPLOS DE ELEMENTOS DO CONJUNTO p EM R(2) SÃO DESCARTADOS E TÊM-SE QUE R(2)={1,5}. O PRIMEIRO NÚMERO APÓS 1 É ANOTADO COMO PRIMO E p={2,3,5}.

A RODA 2 É EXTENDIDA PARA l=1X2X3X5=30 E AGORA R(3)={1,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}.
OS MÚLTIPLOS DE ELEMENTOS DO CONJUNTO p EM R(3) SÃO DESCARTADOS E TÊM-SE QUE R(3)={1,7,11,13,17,19,23,29}.

COMO l JÁ ATINGIU O LIMITE DESEJADO. OBTEMOS OS PRIMOS TOMANDO A UNIÃO DOS CONJUNTOS p E R(3), PRODUZINDO ASSIM A LISTA DE PRIMOS MENORES QUE 30 NO CASO
{2,3,5,7,11,13,17,19,23,29}.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Sieve_of_Pritchard#Pseudocode 

'''

#**************************************************************************
#IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO

#**************************************************************************
#CLASSE DO ALGORITMO
class pritchard_sieve:
 '''Classe que implementa o algoritmo de Pritchard'''
 #-------------------------------------------------------------------------------
 #MEMBROS DA CLASSE
 wheel:set=set([1]) #Lista de números usados para computados primos
 partial_prime_set:set=set([]) #Lista de primos calculados durante  a execução do algoritmo
 prime_set:set=None #Lista de primos calculados durante o algoritmo
 reduced_prime_set:set=set([]) #Lista de final primos calculados até um determinado limite
 length:int=1 #Tamanho da da roda usada no algoritmo
 last_value:int=1 #Ponteiro usado para indexar possíveis candidatos a números primos no intervalo
 next_prime:int=2 #Ponteiro usado para a detecção de números primos
 limit:int=0 #Valor limite usado para a busca de números primos

 #--------------------------------------------------------------------------------
 #MÉTODOS DO ALGORITMO
 #1
 def run(self):
  '''Função principal do algoritmo'''
  #Recebendo input do usuário
  self.limit=int(input("Digite um limitante superior para sua sequência de números primos:"))

  #Loop principal
  while(self.length<self.limit):
   self.update_length() #Atualizando o tamanho da roda
   self.update_wheel() #Atualizando a possíveis candidatos
   self.update_prime_set() #Atualizando  a lista de primos
   self.wheel_sift() #Peneira de elementos múltiplos de primos na roda principal
   self.update_pointers() #Função que atualiza os ponteiros usados na busca de números primos

  #Computando a lista final de primos do algoritmo
  self.prime_set=self.wheel|self.partial_prime_set

  for p in self.prime_set:
   if(p<self.limit):
    self.reduced_prime_set.add(p)
  
 #2
 def update_length(self):
  '''Função que recalcula o tamanho da roda usada no algoritmo'''
  self.length*=self.next_prime

 #3
 def update_wheel(self):
  '''Função que atualiza os elementos da lista de candidatos'''
  #Inserindo elementos na lista
  for i in range(self.last_value, (self.length+1),1):
    self.wheel.add(i)

  '''TESTE USE UM # APÓS A EXECUÇÃO DO TESTE'''
  #print(list(self.wheel))  

 #4
 def update_prime_set(self):
  '''Função que atualiza a lista de primos parciais computados durante o algoritmo'''
  self.partial_prime_set.add(self.next_prime)
 
 #5
 def wheel_sift(self):
  '''Função que elimina múltiplos de primos já computados da roda principal usada no algoritmo'''
  #Variáveis locais
  maximum:int=(self.length+1)//2

  #Removendo elementos da roda principal
  for p in self.partial_prime_set:
   for x in range(maximum+1):
    tester:int=(x*p)
    if(tester>self.length):
     break
    if(tester in self.wheel):
     self.wheel.discard(tester)

 #6
 def update_pointers(self):
  '''Função que atualiza os ponteiros usados na busca de números primos'''
  #Atualização dos ponteiros
  self.last_value=(self.length+1)
  self.next_prime=(self.length+1)

  #Checando se algum primo foi detectado na roda principal
  for p in self.wheel:
   if(p>1):
    self.next_prime=p
    break

 #7 
 def print_result(self):
  '''Função que exibe o resultado da execução do algoritmo'''
  print("Eis a lista de primos até {}:".format(self.limit))
  print(list(self.reduced_prime_set))

#**************************************************************************
#FUNÇÃO PRINCIPAL

#Instanciandoum objeto da classe do algoritmo
prime_generator=pritchard_sieve()

#Executando o algoritmo
prime_generator.run()
prime_generator.print_result()

