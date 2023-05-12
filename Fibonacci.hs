--VAMOS ESCREVER UM PROGRAMA QUE USA UMA FUNÇÃO RECURSIVA EN HASKEL PARA CALCULAR A SEQUÊNCIA DE  FIBONNACCI

--DECLARAÇÃO DE FUNÇÃO
fibonacci::Integer ->Integer
fibonacci 0 = 1
fibonacci 1 = 1
fibonacci i = fibonacci(i-1)+ fibonacci(i-2)

fibonacci2::Integer ->[Integer]
fibonacci2 n = map fibonacci[0..n]




--FUNÇÃO PRINCIPAL
main::IO()
main = do
 putStrLn("Digite quantos termos você quer exibir na sequência de Fibonacci:")
 num<-readLn
 putStrLn("Eis a sequência de Fibonacci até o "++ show num++"º-ésimo termo:")
 print(fibonacci2 num)

