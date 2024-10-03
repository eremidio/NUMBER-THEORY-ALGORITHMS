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

THE FOLLOWING LINKS CONTAINS A LIST (WHICH WILL BE UPDATING AS SOON AS NEW INTERESTING MATERIAL IS FOUND) OF NEW INTERESTING ALGORITHMS FOR FACTORING INTEGERS (OR TESTING ITS PRIMALITY) WHOSE IMPLEMENTATIONS ARE NOT PROVIDED, BUT THAT USE MANY IDEAS OR CONCEPTS FROM OTHER ALGORITHMS PROVIDED IN THIS REPOSITORY:

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
