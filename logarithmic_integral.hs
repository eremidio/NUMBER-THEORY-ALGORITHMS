-- VAMOS CRIAR UM PROGRAMA EM HASKELL PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO logarithmic_integral_module.hs

--IMPORTANDO MÓDULOS
import LogarithmIntegralFunction


--FUNÇÃO PRINCIPAL
main::IO()
main = do

  --Recebendo input do usuário
  putStr("Digite um inteiro positivo: ")
  arg1<-getLine
  let n= read arg1::Integer

  --Calculando o valor da função li(x)
  let li_n=logarithmic_integral_function n
  putStrLn("li("++ show n++") = "++ show li_n)
  
