# AT2N2
Trabalho de estrutura de dados sobre o jogo do grupo: "jogo de adivinhação"

O jogo é um desafio de adivinhação de cartas.

O jogador deve informar seu nome, o baralho é "embaralhado" e em cada uma das 5 rodadas do código, uma carta é sorteada, e o jogador deve adivinhar o valor da carta de 1 a 13 
se você acertar, você ganha o ponto, porém se errar, não ganha, respectivamente, no final a pontuação é mostrada em um placar
para você poder jogar, você tem que ir ao VSCODE na parte superior do programa,escolher as seguintes opções:

Terminal > New Terminal

logo,você abrirá a terminal, e você poderá compilar, com o seguinte código:

"Gcc jogo.c -o jogo" (sem as aspas)
e para rodar o jogo:

./jogo.exe

em termos mais técnicos, as funções principais deste código são "sortear carta()"
pois sorteia ou remove uma carta aleatória do baralho
o "Main()" no qual faz a exibição do menu e controla o fluxo do programa, entre outras

Aqui está uma descrição mais leve e acessível do jogo de cartas em C:
Elementos do Jogo: A struct é usada para organizar as informações das cartas e dos jogadores.

Organização do Baralho: As cartas são mantidas numa lista, o que torna o manuseio mais fácil.

Aleatoriedade: A função rand() é usada para criar um embaralhamento e sorteio aleatórios.

Registro de Pontuação: Os resultados são guardados no arquivo placar.txt para histórico.

Opções Iniciais: Logo ao abrir, você escolhe entre iniciar uma partida ou ver a pontuação.

Em resumo: é um jogo simples, com cartas aleatórias e registro de pontos. Nada de muito complexo.
