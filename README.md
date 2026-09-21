# Projeto-N1---Analise-de-algoritmos
Projeto e Análise de Algoritmos II - Backup offline do professor Leonardo

Integrantes do grupo:
- Beatriz savazzi Del Bianco - RA: 10735936
- Laura Yummi Rodrigues Shiguemori  - RA: 10735619


Link do vídeo no YouTube: https://youtu.be/V-BmV4AKPKM?is=6LzlIzle5RE1-O-J

Compilar:  gcc -o backup backup.c
Executar:  ./programa <ARQUIVO_ENTRADA> <ARQUIVO_SAÍDA>

1) Técnica de projeto utilizada
Programação Dinâmica, aplicada ao problema da soma de subconjuntos (subset sum).
Como cada pendrive tem capacidade cap = L/2, basta encontrar um subconjunto de
arquivos (Pendrive A) com soma S tal que (total - cap) <= S <= cap. Os arquivos
restantes vão para o Pendrive B e cabem automaticamente. Um vetor
alcancavel[s] indica se é possível formar a soma s com os arquivos vistos até
agora; um vetor origem[s] guarda o último arquivo usado, permitindo reconstruir
quais arquivos foram para o Pendrive A. Entre as somas válidas, escolhemos a
mais equilibrada entre os dois pendrives.
Complexidade: O(T * L/2) tempo e O(L/2) memória.

(Observação: a primeira versão usava uma técnica gulosa, que decidia
arquivo por arquivo sem voltar atrás. Ela foi substituída por falhar em casos
com solução, por exemplo L=64 e arquivos 13, 7, 30, 10.)

2) A técnica utilizada sempre apresenta o melhor resultado? Justifique.
Sim. A programação dinâmica testa implicitamente todos os subconjuntos
possíveis de arquivos, pois alcancavel[s] fica verdadeiro se, e somente se,
existe algum subconjunto com soma s. Logo, se existir qualquer forma de gravar
todos os arquivos nos dois pendrives, o algoritmo a encontra, e só declara
"Impossível" quando realmente não há solução. Uma abordagem gulosa não teria
essa garantia: com pendrives de 32 GB e arquivos 13, 7, 30, 10, o guloso coloca
13 no A e 7 no B, e então o 30 não cabe em nenhum, embora a solução exista
(A = 13+7+10, B = 30). A ressalva é que o algoritmo é pseudo-polinomial: o custo
cresce com a capacidade L, o que não é problema para os valores em GB deste
projeto.
