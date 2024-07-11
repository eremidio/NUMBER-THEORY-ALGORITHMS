--VAMOS CRIAR UM MÓDULO EM HASKELL PARA COMPUTAR A FUNÇÃO LOGARÍTMICA INTEGRAL

{-
A FUNÇÃO LOGARÍTMICA INTEGAL li(x) É DEFINIDA PELA SEGUINTE FÓRMULA SEJA: f(x)=[ln(x)]-¹,
li(x) É O VALOR DA INTEGRAL DE f(x) DE 0 ATÉ x. A CHAMADA FUNÇÃO INTEGRAL DE EULER Li(x)
É POR DEFINIÇÃO DADA PELA INTEGRALDEFINIDA DE f(x) DE 2 ATÉ x, TEMOS QUE li(x)=li(2)+Li(x).

A FUNÇÃO li(x) É DEGRANDE IMPORTÂNCIA EM TEORIA DOS NÚMEROS. O CHAMADO TEOREMA DO NÚMEROS
PRIMOS AFIRMA QUE PARA GRANDES VALORES DE x: π(x)≃li(x), ONDE π(x) É A FUNÇÃO DE CONTAGEM
DE NÚMEROS PRIMOS ABAIXO DE x. ESTIMATIVAS RAZOÁVEIS BASEADAS NAHIPÓTESE DE RIEMANN
AFIRMAM QUE |π(x)-li(x)| ~ O((√x)ln(x)).

USAREMOS UMA REPRESENTAÇÃO EM SÉRIE DEVIDO A RAMANUJAN, QUE CONVERGE RAPIDAMENTE PARA O
VALOR CORRETO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Prime-counting_function
                          https://en.wikipedia.org/wiki/Logarithmic_integral_function


-} 


--DECLARANDO O MÓDULO
module LogarithmIntegralFunction(
logarithmic_integral_function
)where


--FUNÇÕES

--Constante de Euler-Mascheroni
euler_mascheroni::Double
euler_mascheroni=0.57721566490153286060651209008240243

--Função que calcula o fatorial de um inteiro
factorial::Integer->Integer
factorial 0 = 1
factorial n = product [1..n]

--Função que calcula o somatório de Σ 1/(2k+1) do recíproco de números ímpares
odd_inverse::Integer -> Double
odd_inverse n = 1.0/(2*fromInteger(n)+1)

odd_inverse_sum :: Integer -> Double
odd_inverse_sum n = sum( map(\i -> odd_inverse i) [0..n])

--Função que calcula o sinal do somatório para aproximação em série da integral logarítmica
get_signal::Integer ->Int
get_signal n
  | mod (n-1) 2==0 = 1
  | mod (n-1) 2==1 = (-1)

--Função que calcula um termo do somatório para aproximação em série da integral logarítmica
term_function::Integer->Double->Double
term_function n x = fromIntegral (get_signal n) * 2 * ((log x / 2) ^ n) * odd_inverse_sum (floor (fromIntegral (n - 1) / 2)) / fromIntegral (factorial n)

sum_term_function::Integer->Double->Double
sum_term_function n x = sum (map (\i -> term_function i x) [1..n])

--Função que calcula a função logaritmíca integral
--NOTA: O segundo parâmetro na chamada da função sum_term_function pode ser alterado para se 
--      a precisão do resultado
logarithmic_integral_function::Integer->Double
logarithmic_integral_function n = euler_mascheroni + log (log (fromIntegral n)) + sqrt (fromIntegral n) * sum_term_function 50 (fromIntegral n)


