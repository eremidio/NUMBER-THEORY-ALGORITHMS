--VAMOS ESCREVER UM PROGRAMA QUE DETERMINA SE UM NÚMERO PERTENCE OU NÃO HÁ SEQUÊNCIA DE FIBONACCI

--[[
UM n NÚMERO PERTENCE A SEQUÊNCIA DE FIBINACCI SE E SOMENTE SE A SEGUINTE CONDIÇÃO FOR SATISFEITA: 5n²+4 OU 5n²-4 FOR UM QUADRADO PERFEITO.
--]]


--FUNÇÕES
--Função que determina se um número é quadrado perfeito
function is_perfect_square(n)
 root=math.floor(math.sqrt(n))
 if((root*root)==n) then
  return true
 else
  return false
 end
end

--Função que determina se um número está na sequência de Fibonacci
function is_fibonacci(n)
 --Casos triviais
 if(n==0 or n==1) then
  return true
 end
 --Caso geral: n>1
 --Variáveis locais
 tester1=(5*n*n)+4
 tester2=(5*n*n)-4

 -- Procedimentos
 --Teste
 if(is_perfect_square(tester1)==true) then
  return true
 end
 if(is_perfect_square(tester2)==true) then
  return true
 end
 --Caso um número não passenos testes acima
 return false
end


--FUNÇÃO PRINCIPAL
--Recebendo input do usuário
io.write("Digite um número inteiro: ")
local number=io.read("*n")

--Testando seo número em questão está na sequência de Fibonacci ou não
if( is_fibonacci(number)==true) then
 io.write("O número ", number, " pertence a sequência de Fibonacci\n")
else
 io.write("O número ", number," não pertence a sequência de Fibonacci\n")
end
