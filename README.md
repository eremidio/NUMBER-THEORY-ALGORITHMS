# NUMBER-THEORY-ALGORITHMS
THIS REPOSITORY CONTAINS SOME BASIC ALGORITHMS RELATED TO NUMBER THEORY LIKE THE DECOMPOSTION OF AN INTEGER INTO PRIME FACTORS, CALCULATION OF PRIME NUMBERS AND THE EUCLIDEAN/DIVISION ALGORITHM TO FIND THE GREATEST COMMON DIVISOR OF TWO INTEGERS, CALCULATION OF CONTINUED FRACTIONS, CALCULATION OF THE P-ADIC EXPANSION OF INTEGERS AND RATIONAL NUMBERS, AMONG OTHERS. FURTHER ALGORITHMS WILL BE ADDED IN THE FUTURE.

ANY SUGGESTION OR CONTRIBUTION IS ENTIRELY WELLCOME.


# OBSERVATIONS:
THE IMPLEMENTATION OF THE QUADRATIC SIEVE HERE PROVIDED ISN'T OPTIMIZED, BUT IT ILLUSTRATE WELL THE MAIN STEPS OF THE ALGORITHM. MANY OPTMIZATIONS LIKE THE BLOCK LANCZOS ALGORITHM FOR THE LINEAR ALGEBRA PART AND MULTITHREADING IN THE SIEVING PART ARE NOT IMPLEMENTED.

THE MOST EFFICIENT CLASSICAL ALGORITHM TO COMPUTE THE FACTORS OF A VERY LARGE NUMBER IS THE GENERAL NUMBER FIELD SIEVE AND ITS VARIANT KNOWN AS SPECIAL NUMBER FIELD SIEVE. THESE KIND OF ALGORITHM FOLLOW AN IDEA SIMILAR TO THE QUADRATIC SIEVE, BUT THEY DO SIEVING ON ALGEBRAIC NUMBER FIELDS AND ARE SUITABLE ONLY FOR VERY LARGE INTEGERS ABOVE ONE HUNDRED DECIMAL DIGITS. THE IMPLEMENTATION HERE PROVIDED WAS NOT TESTED IN ITS ENTIRITY, BUT INDIVDUAL PARTS ARE WORKING FINE. THIS WAS DONE FOR PEDADGOGICAL AND LEARNING PURPOSES ONLY (I'M NOT A PROFESSIONAL MATHEMATICIAN). 

AMONG ALL FACTORIZATION ALGORITHMS WHOSE RUNNING TIME IS DETERMINED RIGOROUSLY, THE FASTEST DETERMINISTIC ONE IS THE STRASSEN-POLLARD ALGORITHM. THE FASTEST PROBABILISTIC ALGORITHM IN THE SAME SENSE IS THE CLASS GROUP METHOD DUE TO SCHNORR–SEYSEN–LENSTRA THAT USES IDEAL CLASS GROUPS OF BINARY QUADRATIC FORMS. HERE WE DON'T PROVIDE AN IMPLEMENTATION OF THE SUBEXPONENTIAL CLASS GROUP METHOD, BUT I DO PROVIDE AN IMPLEMENTATION OF SHANKS' EXPONENTIAL ALGORITHM THAT EMPLOYS SIMILAR IDEAS. FUTHER REFERENCES CAN BE FOUND IN THE BIBLIOGRAPHY.

THERE'S SOME IMPLEMENTATIONS OF THESE ALGORITHMS IN LANGUAGES LIKE C/C++ EASILY AVAILABLE ON THE INTERNET. ONE SHOULD USE ONE OF THESE BATTLE TESTED AND ROBUST IMPLEMENTATION FOR CRYPTOGRAPHIC APPLICATIONS AND RELATED STUFF.

SEE: https://vtechworks.lib.vt.edu/bitstream/handle/10919/36618/etd.pdf
http://www-personal.umich.edu/~msgsss/factor/qs_rep.pdf
http://kmgnfs.cti.gr/kmGNFS/Home.html

FOR SOME LARGE INTEGERS OF SPECIAL FORM, THE SO-CALLED AURIFEUILLAN (ALGEBRAIC) FACTORIZATION USING CYCLOTMIC POLINOMIALS IS USEFUL IN COMPUTING PRIME AND NON-PRIME FACTORS, THE WIKIPEDIA LINK (https://en.wikipedia.org/wiki/Aurifeuillean_factorization) CONTAINS SOME USEFUL REFERENCES FOR THE SUBJECT.


FOR THE REASON OF COMPLEXITY WE HAVEN'T IMPLEMENTED YET THE ECPP (ELLIPTIC CURVE) PRIMALITY TEST AND THE APR-CL PRIMALITY TEST (WHICH USE ARITHMETIC ON CYCLOTOMIC FIELDS). THEY ARE THE MOST EFFICIENT PRIMALITY TESTS IN USE AVAILABLE TODAY (THEY HAVE BETTER RUNTIME THAN THE AKS TEST). GOOD IMPLEMENTATIONS ARE AVAILABLE ONLINE. SEE FOR INSTANCE: https://github.com/wacchoz/APR_CL/blob/master/APR_CL.py AND  https://github.com/onechip/ecpp

DUE TO ITS COMPLEXITY WE SHALL NOT PROVIDE AN IMPLEMENTATION OF THE NUMBER FIELD SIEVE AND THE ALGEBRAIC FUNCTION FIELD SIEVE FOR THE DISCRETE LOGARITHM PROBLEM. THE READER INTERESTED MAY CONSULT THE BIBLIOGRAPHY: https://ntnuopen.ntnu.no/ntnu-xmlui/bitstream/handle/11250/2394427/14190_FULLTEXT.pdf?sequence=1&isAllowed=; https://jbootle.github.io/Misc/snfs.pdf, https://core.ac.uk/download/pdf/82604499.pdf. THE FOLLOWING IMPLEMENTATIONS ARE AVAILABLE IN LANGUAGES LIKE C/C++:https://github.com/pankajcharpe/FunctionFieldSeieve/tree/main; https://github.com/onechip/dlog-nfs

THE FOLLOWING LINKS CONTAINS A LIST (WHICH WILL BE UPDATING AS SOON AS NEW INTERESTING MATERIAL IS FOUND) OF NEW INTERESTING ALGORITHMS FOR FACTORING INTEGERS (OR TESTING ITS PRIMALITY), GENERATE PRIMES AND SO ON, WHOSE IMPLEMENTATIONS ARE NOT PROVIDED, BUT THAT USE MANY IDEAS OR CONCEPTS FROM OTHER ALGORITHMS PROVIDED IN THIS REPOSITORY:

https://www.mdpi.com/2624-800X/1/4/33

https://www.datasciencecentral.com/new-probabilistic-approach-to-factoring-big-numbers/

https://www.codeproject.com/Articles/5291827/Integer-Factorization-Another-Approach-to-Trial-D

https://ar5iv.labs.arxiv.org/html/1408.2608

https://projecteuclid.org/journals/bulletin-of-the-american-mathematical-society/volume-30/issue-9-10/Methods-for-finding-factors-of-large-integers/bams/1183486232.pdf 

https://www.mdpi.com/2624-800X/1/4/33

https://arxiv.org/pdf/1308.2891.pdf

https://eprint.iacr.org/2021/933.pdf

https://zienjournals.com/index.php/tjet/article/download/3636/3020

https://www.cse.iitk.ac.in/users/nitin/papers/integerFact.pdf

https://arxiv.org/pdf/2001.09076

https://arxiv.org/pdf/1608.08766

https://cr.yp.to/factorization/eecm-20090120.pdf

https://arxiv.org/pdf/2006.16729

https://www.ams.org/journals/mcom/2011-80-276/S0025-5718-2011-02489-0/S0025-5718-2011-02489-0.pdf

https://math.dartmouth.edu/~carlp/aks111216.pdf

https://www.math.leidenuniv.nl/~lenstrahw/PUBLICATIONS/1982e/art.pdf

https://cr.yp.to/bib/2003/damgard.pdf

https://ieeexplore.ieee.org/document/5662138/authors#authors

http://www.mat.uniroma3.it/users/pappa/sintesi/20_Bedodi.pdf

https://arxiv.org/pdf/1003.3261

http://vigir.missouri.edu/~gdesouza/Research/Conference_CDs/IEEE_WCCI_2020/CEC/Papers/E-24289.pdf

https://arxiv.org/pdf/math/0610612

https://github.com/armchaircaver/Baillie-PSW

https://www.ams.org/journals/mcom/2002-71-240/S0025-5718-02-01424-2/S0025-5718-02-01424-2.pdf

https://eprint.iacr.org/2005/462

https://arxiv.org/pdf/2309.15162

https://www.scientific.net/AMR.931-932.1432

https://www.ams.org/journals/mcom/1991-56-194/S0025-5718-1991-1068808-2/S0025-5718-1991-1068808-2.pdf

https://fse.studenttheses.ub.rug.nl/31985/1/bMATH_2024_ColellaD.pdf

https://math.dartmouth.edu/~carlp/lucasprime3.pdf

https://www.math.leidenuniv.nl/~lenstrahw/PUBLICATIONS/1990c/art.pdf

https://arxiv.org/pdf/2212.04463

https://www.ams.org/journals/mcom/1983-40-162/S0025-5718-1983-0689483-8/S0025-5718-1983-0689483-8.pdf

https://link.springer.com/chapter/10.1007/978-3-642-34135-9_12

http://archive.numdam.org/item/SB_1980-1981__23__243_0.pdf

https://arxiv.org/pdf/math/0702227

https://repository.rit.edu/cgi/viewcontent.cgi?article=1660&context=theses

https://cs-people.bu.edu/tromer/papers/tromer-phd.pdf

https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=8901977

https://arxiv.org/pdf/math/0702227

https://repository.rit.edu/cgi/viewcontent.cgi?article=1660&context=theses

https://cs-people.bu.edu/tromer/papers/tromer-phd.pdf

https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=8901977

https://www.ams.org/journals/mcom/1975-29-130/S0025-5718-1975-0384673-1/S0025-5718-1975-0384673-1.pdf

https://msp.org/pjm/1959/9-4/pjm-v9-n4-p23-p.pdf

https://projecteuclid.org/journals/duke-mathematical-journal/volume-21/issue-4/Prime-divisors-of-second-order-recurring-sequences/10.1215/S0012-7094-54-02163-8.short

https://cs.uwaterloo.ca/journals/JIS/VOL13/Luca/luca33.pdf

https://open.library.ubc.ca/media/download/pdf/51869/1.0107231/1

https://web.archive.org/web/20180421064540id_/http://siauliaims.su.lt/pdfai/2008/ericksen-08.pdf

https://mae.ufl.edu/~uhk/IMPROVED-METHOD-LARGE-N.pdf

https://cir.nii.ac.jp/crid/1571698602310086656

https://docs.lib.purdue.edu/dissertations/AAI3263600/

https://www.unioviedo.es/grau/ARTICULOS%20PUBLICADOS/articulo69.pdf

https://www.sciencedirect.com/science/article/abs/pii/S0378475421000677

https://www.cambridge.org/core/journals/bulletin-of-the-australian-mathematical-society/article/generalised-lucasian-primality-test/77D299F8E525D7E77CFAC6941E2D57AD

http://mpqs.free.fr/LucasPseudoprimes.pdf

https://wstein.org/edu/2010/414/projects/stueve.pdf

https://ouci.dntb.gov.ua/en/works/4ko8gmW4/

https://colab.ws/articles/10.1090%2Fs0025-5718-1976-0414473-6

https://link.springer.com/article/10.1007/s00145-002-0107-y

https://www.lse.epita.fr/lse-summer-week-2015/slides/lse-summer-week-2015-07-primality_factoring.pdf

https://www.tandfonline.com/doi/abs/10.1080/00150517.1985.12429856

https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=fd0c04dad5a5b5397719ebbf117f7b24ee196b0a

https://digitalcommons.pace.edu/cgi/viewcontent.cgi?article=1025&context=csis_tech_reports

https://link.springer.com/chapter/10.1007/978-94-011-5020-0_41

https://www.mdpi.com/2227-7390/12/17/2624

https://www.researchgate.net/publication/304025431_Two_pentagonal_number_primality_tests_and_twin_prime_counting_in_arithmetic_progressions_of_modulus_24

https://www.mat.uniroma3.it/scuola_orientamento/alumni/laureati/bedodi/Tesi.pdf

https://www.journals.vu.lt/nonlinear-analysis/article/download/15165/14170/23644

https://arxiv.org/abs/1307.1840

https://arxiv.org/pdf/2411.01638

https://eprint.iacr.org/2023/195.pdf

https://dl.acm.org/doi/abs/10.1145/3465002.3465004

https://scik.org/index.php/jmcs/article/view/4921

https://dl.acm.org/doi/10.1145/3207677.3278049

https://scispace.com/pdf/two-pentagonal-number-primality-tests-and-twin-prime-3aycrk761a.pdf

https://seminariomatematico.polito.it/rendiconti/80-1/Dutto.pdf

https://onlinelibrary.wiley.com/doi/epdf/10.1155/2022/7034529

https://www.ams.org/journals/mcom/1986-46-174/S0025-5718-1986-0829639-7/S0025-5718-1986-0829639-7.pdf

https://dl.acm.org/doi/10.1145/363235.363247

https://marcjoye.github.io/papers/JPV00gen.pdf

https://arxiv.org/pdf/1904.11822

https://math.colgate.edu/~integers/v109/v109.pdf

https://vixra.org/pdf/2406.0134v3.pdf

https://arxiv.org/pdf/2106.01327

https://www.sciencedirect.com/science/article/pii/0196885886900230

https://arxiv.org/pdf/2002.08062

https://web.stanford.edu/class/archive/cs/cs265/cs265.1254/Lectures/Lecture3/l3.pdf

https://vixra.org/pdf/1202.0029v3.pdf

THE FOLLOWING LINK CONTAIN A LIST OF USEFUL FUNCTIONS AND MATHEMATICAL CONSTANTS WHICH CAN APPROXIMATED BY USING INFINITE CONTINUED FRACTIONS: https://link.springer.com/content/pdf/bbm:978-94-91216-37-4/1. ONE CAN USE SOME VARIANT OF THE CODE PROVIDED HERE TO COMPUTE ALL FUNCTION AND CONSTANTS AT ONCE BY PROVIDING A LIST OF PARTIAL NUMERATORS AND DENOMINATORS UP TO SOME TRUNCATION POINT.

THE PRESENT REPOSITORY COVERS ELEMENTARY ASPECTS OF NUMBER THEORY. THE READER INTERESTED MAY CONSULT THE FOLLOWING BIBLIOGRAPHY: 

Introduction to Modern Number Theory, by Yuri I. Manin and Alexei A. Panchishkin

Elements of Number Theory by I. M. Vinogradov

A Course In Computational Algebraic Number Theory by Henri Cohen

Advanced Topics In Computational Number Theory by Henry Cohen

Prime Numbers And Computer Methods For Factorization, by Hans Riesel

Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

The Joy Of Factoring by Samuel Wagstaff Jr

Elementary Methods in Number Theory, by Melvin B. B. Nathanson

Number Theoretical Algorithms in Criptography by O. N. Vasilenko

A Computational Introduction to Number Theory and Algebra  by Victor Shoup 

Algorithmic Number Theory: Lattices, Number Fields, Curves And Cryptography by J.P. Buhler and P. Stevenhagen

Introduction to Analytic Number Theory by T. M. Apostol

Computational Number Theory by Abhijit Das

