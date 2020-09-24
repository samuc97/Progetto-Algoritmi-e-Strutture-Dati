# Progetto-Algoritmi-e-Principi-Dell-Informatica (2018)

Simulatore di macchine di Turing non deterministiche

Implementazione in linguaggio C standard (con la sola libc) di un interprete di Macchine di Turing non-deterministiche, nella variante a nastro singolo e solo accettori.

La struttura del file di ingresso è la seguente: prima viene fornita la funzione di transizione, quindi gli stati di accettazione e un limite massimo sul numero di passi da effettuare per una singola computazione (per evitare in maniera banale il problema delle macchine che non terminano), infine una serie di stringhe da far leggere alla macchina.

In uscita ci si attende un file contenente 0 per le stringhe non accettate e 1 per quelle accettate; essendoci anche un limite sul numero di passi, il risultato può anche essere U se non si è arrivati ad accettazione.

## Convenzioni: 
Per semplicità i simboli di nastro sono dei char, mentre gli stati sono int. Il carattere "_" indica il simbolo "blank".
La macchina parte sempre dallo stato 0 e dal primo carattere della stringa in ingresso.
Si assume, come al solito, che il nastro sia illimitato sia a sinistra che a destra e che contenga in ogni posizione il carattere "_".
I caratteri "L", "R", "S" vengono usati, come al solito, per il movimento della testina.
Il file di ingresso viene fornito tramite lo standard input, mentre quello in uscita è sullo standard output.

# Struttura del file di ingresso
Il file di ingresso è diviso in 4 parti: una prima parte, che inizia con "tr", contiene le transizioni, una per linea - ogni carattere può essere separato dagli altri da spazi. Per esempio, 0 a c R 1 significa che con la transizione si va dallo stato 0 allo stato 1, leggendo a e scrivendo c. La testina viene spostata a destra (R).
La parte successiva, che inizia con "acc", elenca gli stati di accettazione, uno per linea.
Per evitare problemi di computazioni infinite, nella sezione successiva, che inizia con "max", viene indicato il numero di mosse massimo che si possono fare per accettare una stringa. 
La parte finale, che inizia con "run", è un elenco di stringhe da fornire alla macchina, una per linea.

# Esempio: MT per ww

tr
0 a a R 0
0 b b R 0
0 a c R 1
0 b c R 2
1 a c L 3
2 b c L 3
3 c c L 3
3 a c R 4
3 b c R 5
4 c c R 4
4 a c L 3
5 c c R 5
5 b c L 3
3 _ _ R 6
6 c c R 6
6 _ _ S 7

acc
7
max
800
run
aababbabaa
aababbabaaaababbabaa
aababbabaaaababbabaab
aababbabaaaababbabaabbaababbabaaaababbabaa
aababbabbaaababbabaabbaababbabaaaababbabaa

Standard output:
1
1
0
U
0
