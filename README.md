*This project has been created as part
of the 42 curriculum by \<aseveri\>, \<elvigonz\>.*

# push_swap

## Descrizione

`push_swap` ordina una sequenza di numeri interi distinti usando due stack, `a` e
`b`, e un insieme ristretto di undici operazioni (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`,
`rb`, `rr`, `rra`, `rrb`, `rrr`), con l'obiettivo di farlo nel minor numero possibile
di operazioni.

Il punto di interesse di questo progetto non è l'ordinamento in sé, ma la
complessità algoritmica: lo stesso problema viene risolto da quattro
strategie distinte, ciascuna costruita per collocarsi in una specifica classe di
complessità, tutte incorporate nello stesso binario e selezionabili a runtime.
L'implementazione non tratta l'ordinamento a due stack come un'unica procedura
fissa, ma come una famiglia di algoritmi che realizzano un diverso compromesso tra
il costo computazionale impiegato per decidere le mosse e il numero di mosse
effettivamente prodotte; tale compromesso viene misurato direttamente nella
grandezza rilevante ai fini del subject: il numero di operazioni di `push_swap`
generate, non la complessità asintotica di un ordinamento classico su array.

Le quattro strategie:

<table>
<tr><th>Strategia</th><th>Flag</th><th>Classe di complessità</th><th>Introduzione generale</th></tr>
<tr><td>Simple</td><td><code>--simple</code></td><td>O(n²)</td><td>Longest Increasing Subsequence: la LIS resta ferma in <code>a</code>, il resto viene spinto in <code>b</code> e reinserito in modo greedy in base al costo di rotazione</td></tr>
<tr><td>Medium</td><td><code>--medium</code></td><td>O(n&radic;n)</td><td>Suddivisione in circa &radic;n bucket annidati a strati, con un meccanismo di parcheggio per ricostruire <code>a</code> in ordine decrescente di target</td></tr>
<tr><td>Complex</td><td><code>--complex</code></td><td>O(n log n)</td><td>Radix sort ricorsivo in base 3 (ternario), con una ricodifica affine dei rank ad ogni ricorsione per mantenere i tre bucket bilanciati</td></tr>
<tr><td>Adaptive</td><td><code>--adaptive</code> (default)</td><td>sceglie una delle precedenti</td><td>Seleziona Simple / Medium / Complex a runtime in base a una metrica di <code>disorder</code> misurata sull'input</td></tr>
</table>

Al di sotto di `SB_MAX = 5` elementi, tutte e quattro le strategie ricadono nella
stessa routine: una ricerca in ampiezza (BFS) sullo spazio degli stati
(piccolo e finito) delle configurazioni di stack, che garantisce il numero ottimo di
operazioni per blocchi di quella taglia.

## Istruzioni

Compilazione:

```
make
```

Questo genera il binario `push_swap`. `make re` forza una ricompilazione completa,
`make clean` / `make fclean` rimuovono i file oggetto e il binario.

Esecuzione:

```
./push_swap [--simple|--medium|--complex|--adaptive] [--bench] N1 N2 N3 ...
```

- La lista di interi, che deve seguire gli eventuali flag, costituisce il
  contenuto iniziale dello stack `a` (il primo intero fornito è in cima).
- Il flag di strategia è opzionale; `--adaptive` è il default se non ne viene
  specificato nessuno.
- `--bench` è opzionale e può essere combinato con un flag di strategia, in
  entrambi gli ordini. Stampa, solo su `stderr`, il disorder misurato dell'input, la
  strategia e la classe di complessità effettivamente usate, il numero totale di
  operazioni e un conteggio per tipo di operazione. Il flusso delle operazioni resta
  sempre su `stdout`, quindi `--bench` non interferisce mai con l'inoltro
  dell'output a un checker tramite pipe.
- Senza argomenti, il programma non stampa nulla e ritorna.
- Su qualunque input non valido (argomenti non numerici, valori fuori dal range di
  `int`, valori duplicati, flag in conflitto o sconosciuti), il programma stampa
  `Error` su `stderr` ed esce con uno stato diverso da zero.

Esempi:

```
./push_swap 2 1 3 6 5 8
./push_swap --complex 4 67 3 87 23
./push_swap --bench --adaptive $(shuf -i 0-9999 -n 500) 2>bench.txt >/dev/null
```

## Algoritmi e scelte progettuali

### Perché queste quattro strategie, e perché la metrica di disorder

Il subject richiede un algoritmo per ciascuna classe di complessità più una
strategia adattiva che scelga tra questi in base a quanto l'input è disordinato. La
metrica di `disorder` usata qui è la frazione di inversioni tra tutte le coppie
dell'input (0 se già ordinato, 1 nel caso peggiore possibile), calcolata una sola
volta prima di eseguire qualunque mossa. La strategia adattiva instrada verso
`--simple` sotto `0.2`, verso `--medium` tra `0.2` e `0.5`, e verso `--complex` da
`0.5` in su — soglie scelte in modo che la strategia più economica (in termini di
costo decisionale) gestisca i casi in cui è già di per sé sufficiente, riservando le
strategie più elaborate agli input in cui il lavoro extra ripaga davvero in mosse
risparmiate.

### Simple — O(n²)

Lo stack viene analizzato una sola volta calcolando, tramite programmazione
dinamica, la Longest Increasing Subsequence (`simple_push_to_b.c`): gli elementi
della LIS restano fermi in `a`, ogni altro elemento viene spinto in `b`. Il
reinserimento da `b`, tuttavia, non segue l'ordine di push: `best_pos_b`
(`simple_search_best_b.c`) calcola, per ogni candidato ancora presente in `b`, il
costo delle rotazioni per inserirlo nella sua posizione corretta in `a`, quindi
recupera l'elemento che in quel momento risulta più economico da posizionare.
Un secondo meccanismo (`absorb_next_from_b`) verifica, immediatamente dopo il
posizionamento di un elemento della LIS, se il valore richiesto successivamente
nella sequenza si trova già in cima a `b`; in tal caso viene recuperato senza
costo di rotazione aggiuntivo, invece di essere lasciato a un passaggio successivo.

### Medium — O(n√n)

L'input viene partizionato in circa `√n` bucket per rank, processati in ordine
crescente (`medium_push_to_b.c`). Ogni bucket è a sua volta suddiviso, rispetto alla
propria mediana, in una metà superiore e una metà inferiore. Gli elementi della metà
superiore vengono spinti (`pb`) e restano in cima, formando un nuovo strato esterno
sopra a quanto già presente in `b`. Gli elementi della metà inferiore vengono spinti
e quindi ruotati (`pb` seguita da `rb`); poiché `rb` ruota l'intero stack `b`, non
solo la porzione di competenza del bucket corrente, ciascuno di questi elementi viene
portato fino in fondo, al di sotto di ogni bucket processato fino a quel momento —
sia della sua metà superiore sia di quella inferiore. La struttura risultante è
annidata, assimilabile a una matrioska: mentre i bucket vengono processati in
sequenza, ciascuno aggiunge un nuovo guscio in cima e, contemporaneamente, ne avvolge
un altro sotto tutto ciò che è già presente. La ricostruzione di `a`
(`medium_rebuild_a.c`) percorre quindi i rank target in ordine decrescente; un
elemento non immediatamente utilizzabile non viene scartato in modo arbitrario, ma
parcheggiato — spinto in `a` e ruotato in fondo — e tenuto traccia come parte di una
catena di target consecutivi. Quando una tale catena viene recuperata
(`medium_recover_parked_chain.c`), i suoi elementi non vengono estratti
indiscriminatamente con `rra`: l'implementazione determina quanti elementi della
catena possono essere recuperati tramite `rrr`, che ruota simultaneamente `b` verso
la posizione del prossimo elemento richiesto, confrontando questa direzione con il
costo di ottenere lo stesso allineamento usando `b` da sola. Esattamente quel numero
di elementi viene recuperato tramite `rrr`; gli eventuali elementi restanti della
catena vengono recuperati tramite semplici `rra`. Una catena costituita da un solo
elemento si riduce banalmente a un'unica `rra` finale.

### Complex — O(n log n)

Un radix sort ricorsivo in base 3. A ogni livello di ricorsione, entrambi gli stack
sono trattati come suddivisi in un segmento top e un segmento bottom; il blocco
corrente viene partizionato in tre bucket in base alla cifra ternaria più alta
ancora da considerare, e ciascun bucket viene ricorso indipendentemente, con il ramo
ricorsivo attivo che determina quale dei due segmenti — top o bottom, su `a` o su
`b` — sia oggetto dell'operazione (`complex_sort_core.c`, `complex.c`). La
componente distintiva è `complex_encoded_rank.c`: un rank non modificato non
produce in modo affidabile tre bucket bilanciati a ogni ricorsione, poiché la sua
cifra più alta può non arrivare abbastanza in alto nella finestra ternaria; il terzo
bucket può risultare vuoto o debole, sbilanciato rispetto agli altri, quindi in casi
estremi far degenerare la suddivisione in una ripartizione binaria, in generale
quindi aumentando il numero di chiamate ricorsive richieste.
I rank vengono quindi ricodificati tramite una trasformazione affine,
`encoded_rank = mult * rank + offset`, scelta in modo che lo split sulla cifra più
alta produca tre bucket il più possibile vicini in dimensione; la derivazione di
`mult` e `offset` è documentata per intero nel file stesso. `complex_recode.c` e
`complex_recode_dispatcher.c` ricodificano i rank prima di ogni chiamata ricorsiva
successiva (ripristinando il rank originario dove necessario), inclusa una codifica
personalizzata applicata immediatamente prima degli ultimi blocchi, calibrata su
come il solver BFS descritto sotto li elabora.

### Il solver per le taglie piccole (`SB_MAX = 5`)

Tutte e quattro le strategie terminano su blocchi di al massimo 5 elementi, risolti
tramite una ricerca in ampiezza (BFS) su ogni configurazione di stack
raggiungibile (`small_bfs.c`), che garantisce il numero minimo di operazioni per un
blocco di quella taglia. Lo spazio degli stati per 5 elementi è piccolo ed
esattamente delimitato — `small_bfs_additions.h` lo deriva direttamente come
`(n + 1) * n!` stati, cioè 720 per `n = 5` — e `small_bfs_state.c` sfrutta questo
limite per codificare ogni stato come un intero univoco in `[0, 720)`, tramite una
codifica basata sul codice di Lehmer e sulla notazione factoradic della
permutazione sottostante, riducendo il controllo "questo stato è già stato
visitato?" a un singolo accesso ad array al posto di una scansione lineare. La
biiezione coinvolta (permutazione ↔ codice di Lehmer ↔ intero in notazione
factoradic) è documentata per intero nel file.

### Il peephole optimizer

Una volta che una strategia ha prodotto la propria sequenza preliminare di
operazioni, `peephole_optimizer_*.c` la riscrive individuando ripetutamente brevi
sottosequenze a fronte di una tabella di pattern con regole, sostituendoli con
equivalenti strettamente più corti (per esempio, `ra` seguita immediatamente da `rra`
si annullano; `sa` seguita da `sb` si fondono in `ss`). Ciascuna sostituzione è
governata da una regola che ne esprime la condizione di equivalenza, formulata come
le dimensioni minime di `a` e `b` sotto le quali la sostituzione è garantita
produrre lo stesso stato finale dello stack della sottosequenza originale; la
sostituzione viene applicata solo quando tale condizione è soddisfatta. Attualmente
sono definite 179 regole di questo tipo,
distribuite nei vari file `try_*`.

---

# Checker (bonus)

## Cos'è

Un **checker** è un programma separato che controlla se una sequenza di mosse (`sa`, `pb`, `ra`, ...) ordina davvero correttamente i numeri passati come argomento. Non ordina lui stesso i numeri: legge le mosse decise da `push_swap` e verifica che, applicandole una per una, si arrivi a una pila ordinata.

**Come si usa:**
```bash
./push_swap 3 1 2 | ./checker 3 1 2
```
`push_swap` stampa le mosse una per riga; il checker le legge dallo **standard input** (il flusso di testo che arriva "in pipe", tramite il simbolo `|`, invece che da tastiera) e alla fine stampa:
- `OK` se la pila risulta ordinata e la seconda pila è vuota,
- `KO` se qualcosa non torna,
- `Error` (su standard error, il canale separato dedicato agli errori) se gli argomenti numerici non sono validi (numeri doppi, non numerici, troppo grandi) o se una delle mosse lette non esiste.

## Come si compila

```bash
make        # compila, crea l'eseguibile "checker"
make clean  # cancella i file .o (compilati a metà, intermedi)
make fclean # cancella anche l'eseguibile
make re     # fclean + all, ricompila tutto da zero
```

## Struttura dei file

| File | Cosa contiene |
|---|---|
| `checker.h` | Le "schede" dati (`t_stack`, `t_checker`), le costanti delle mosse (`OP_SA`, ecc.), tutti i prototipi delle funzioni. |
| `checker_stack.c` | Creazione/distruzione delle pile, e il controllo finale "è tutto ordinato?" (`organize_check`). |
| `checker_parse.c` | Validazione e conversione degli argomenti da riga di comando in numeri, controllo dei doppioni. |
| `checker_ops1.c` | Le operazioni `sa`, `sb`, `ss`, `pa`, `pb`, più lo smistamento iniziale delle mosse. |
| `checker_ops2.c` | Le operazioni di rotazione: `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`. |
| `checker_exec.c` | Riconoscimento del testo di una mossa (es. `"sa"` → numero `OP_SA`). |
| `checker_gnl.c` | Le funzioni base di lettura riga per riga (versione "fatta in casa" di una funzione chiamata `get_next_line`, spesso abbreviata **GNL**). |
| `checker_gnl2.c` | La logica che accumula i pezzi letti e restituisce una riga alla volta. |
| `checker_main.c` | Il punto di partenza (`main`): legge gli argomenti, legge le mosse, stampa il risultato. |

Nota: `checker_gnl`/`checker_gnl2` e `checker_ops1`/`checker_ops2` sono divisi in due file per rispettare la norma di 42, che vieta più di 5 funzioni per file `.c`.

## Come funziona, passo per passo

Immagina il checker come un arbitro che segue una partita a carte:

1. **`build_stack`**: prepara il "mazzo" iniziale (pila `a`) con i numeri passati da riga di comando, controllando che siano validi e senza doppioni.
2. **`read_instructions`**: legge le mosse una alla volta dallo standard input (usando `get_next_line`) e le esegue subito sulle pile, una dopo l'altra.
3. **`final_check`**: a mosse finite, controlla se la pila `a` è ordinata e la pila `b` è vuota, e stampa `OK` o `KO`.

Se durante la lettura delle mosse ne arriva una non valida (o un argomento numerico non valido all'inizio), il programma si ferma subito e stampa `Error`.

---

# Risultati dei test

Dati estratti dagli screenshot dei test eseguiti (uno per riga di tabella), raggruppati per algoritmo e per tipo di test. Le mosse prodotte da `push_swap` sono state sempre passate al checker per confermare `OK` prima di registrare il conteggio delle operazioni; in tutte le tabelle sotto, `KO` è sempre risultato `0`.

## Complex

**Test generico** (`testgeneric_flag.py`) — input completamente casuali:

| N | test | limite mosse | media | min | max | sfori ≥ limite | % sfori |
|---|---|---|---|---|---|---|---|
| 500 | 5000 | 5500 | 3903.5886 | 3813 | 3983 | 0 / 5000 | 0.0% |
| 100 | 5000 | 700 | 554.1668 | 514 | 591 | 0 / 5000 | 0.0% |

**Test per livello di disorder** (`test_complex_disorder.py`) — N = 500, 5000 test per riga:

| target disorder | avg disorder reale | min disorder reale | max disorder reale | media mosse | min mosse | max mosse | sfori ≥ 5500 |
|---|---|---|---|---|---|---|---|
| 0.60 | 0.6830 | 0.6235 | 0.7456 | 3944.50 | 3846 | 4027 | 0 / 5000 |
| 0.70 | 0.7328 | 0.6703 | 0.7980 | 3951.41 | 3851 | 4042 | 0 / 5000 |
| 0.80 | 0.7997 | 0.7435 | 0.8462 | 3947.32 | 3833 | 4050 | 0 / 5000 |
| 0.90 | 0.8862 | 0.8404 | 0.9305 | 3895.92 | 3693 | 4025 | 0 / 5000 |
| 0.95 | 0.9376 | 0.8909 | 0.9658 | 3777.86 | 3450 | 3959 | 0 / 5000 |
| 1.00 | 1.0000 | 1.0000 | 1.0000 | 2397.00 | 2397 | 2397 | 0 / 5000 |

**Test per livello di disorder** — N = 100, 5000 test per riga:

| target disorder | avg disorder reale | min disorder reale | max disorder reale | media mosse | min mosse | max mosse | sfori ≥ 700 |
|---|---|---|---|---|---|---|---|
| 0.60 | 0.6821 | 0.5479 | 0.8026 | 560.96 | 518 | 601 | 0 / 5000 |
| 0.70 | 0.7310 | 0.5964 | 0.8521 | 562.82 | 512 | 604 | 0 / 5000 |
| 0.80 | 0.8039 | 0.6749 | 0.9115 | 562.83 | 499 | 601 | 0 / 5000 |
| 0.90 | 0.8939 | 0.8010 | 0.9675 | 552.84 | 431 | 603 | 0 / 5000 |
| 0.95 | 0.9373 | 0.8503 | 0.9986 | 538.15 | 417 | 599 | 0 / 5000 |
| 1.00 | 1.0000 | 1.0000 | 1.0000 | 441.00 | 441 | 441 | 0 / 5000 |

## Medium

**Test generico** (formato analogo a `testgeneric_flag.py`) — input completamente casuali:

| N | test | limite mosse | media | min | max | sfori ≥ limite | % sfori |
|---|---|---|---|---|---|---|---|
| 100 | 5000 | 700 | 489.6598 | 447 | 548 | 0 / 5000 | 0.0% |
| 500 | 5000 | 5500 | 4280.3656 | 4017 | 4561 | 0 / 5000 | 0.0% |

**Test per numero di scambi** (`test_medium_disorder.py`) — N = 100, 5000 test per riga:

| swaps | valid tests | scartati (disorder ≥ 0.5) | avg disorder | max disorder | media mosse | min mosse | max mosse |
|---|---|---|---|---|---|---|---|
| 1 | 5000 / 5000 | 0 | 0.01320 | 0.03980 | 265.91 | 0 | 348 |
| 2 | 5000 / 5000 | 0 | 0.02614 | 0.06949 | 317.88 | 0 | 416 |
| 3 | 5000 / 5000 | 0 | 0.03849 | 0.09475 | 345.76 | 150 | 436 |
| 5 | 5000 / 5000 | 0 | 0.06231 | 0.13596 | 377.58 | 167 | 464 |
| 8 | 5000 / 5000 | 0 | 0.09583 | 0.17657 | 404.00 | 269 | 492 |
| 10 | 5000 / 5000 | 0 | 0.11631 | 0.21212 | 416.45 | 321 | 509 |
| 15 | 5000 / 5000 | 0 | 0.16234 | 0.27576 | 438.89 | 355 | 523 |
| 20 | 5000 / 5000 | 0 | 0.20262 | 0.33253 | 454.65 | 382 | 543 |
| 30 | 5000 / 5000 | 0 | 0.26798 | 0.40768 | 472.45 | 402 | 553 |
| 50 | 5000 / 5000 | 0 | 0.35527 | 0.48929 | 485.94 | 427 | 543 |
| 75 | 4910 / 5000 | 90 | 0.41693 | 0.49939 | 489.11 | 440 | 543 |
| 100 | 4506 / 5000 | 494 | 0.44524 | 0.49980 | 489.70 | 442 | 538 |
| 125 | 3919 / 5000 | 1081 | 0.45892 | 0.49980 | 489.37 | 444 | 541 |
| 150 | 3387 / 5000 | 1613 | 0.46495 | 0.49980 | 489.11 | 441 | 551 |
| 175 | 3091 / 5000 | 1909 | 0.46843 | 0.49980 | 489.08 | 448 | 547 |
| 200 | 2842 / 5000 | 2158 | 0.47015 | 0.49980 | 489.51 | 444 | 543 |
| 225 | 2714 / 5000 | 2286 | 0.47195 | 0.49980 | 489.36 | 447 | 542 |
| 250 | 2565 / 5000 | 2435 | 0.47216 | 0.49980 | 489.07 | 451 | 539 |
| 300 | 2529 / 5000 | 2471 | 0.47194 | 0.49980 | 489.64 | 447 | 534 |
| 350 | 2484 / 5000 | 2516 | 0.47315 | 0.49980 | 489.08 | 449 | 538 |
| 400 | 2505 / 5000 | 2495 | 0.47324 | 0.49980 | 488.83 | 442 | 556 |
| 500 | 2505 / 5000 | 2495 | 0.47330 | 0.49980 | 489.68 | 439 | 539 |

**Test per numero di scambi** — N = 500, 500 test per riga:

| swaps | valid tests | scartati (disorder ≥ 0.5) | avg disorder | max disorder | media mosse | min mosse | max mosse |
|---|---|---|---|---|---|---|---|
| 1 | 500 / 500 | 0 | 0.00262 | 0.00780 | 1773.57 | 1410 | 2143 |
| 2 | 500 / 500 | 0 | 0.00536 | 0.01392 | 2018.77 | 1457 | 2575 |
| 3 | 500 / 500 | 0 | 0.00787 | 0.01689 | 2201.28 | 1632 | 2771 |
| 5 | 500 / 500 | 0 | 0.01297 | 0.02487 | 2435.85 | 1814 | 2951 |
| 8 | 500 / 500 | 0 | 0.02055 | 0.03471 | 2681.10 | 2102 | 3229 |
| 10 | 500 / 500 | 0 | 0.02550 | 0.04290 | 2800.66 | 2164 | 3203 |
| 15 | 500 / 500 | 0 | 0.03752 | 0.05836 | 3011.65 | 2433 | 3467 |
| 20 | 500 / 500 | 0 | 0.04950 | 0.07410 | 3152.44 | 2685 | 3570 |
| 30 | 500 / 500 | 0 | 0.07272 | 0.10067 | 3329.88 | 2934 | 3626 |
| 50 | 500 / 500 | 0 | 0.11517 | 0.15176 | 3535.71 | 3205 | 3866 |
| 75 | 500 / 500 | 0 | 0.16136 | 0.20288 | 3712.52 | 3430 | 4047 |
| 100 | 500 / 500 | 0 | 0.20087 | 0.25186 | 3842.54 | 3527 | 4192 |
| 125 | 500 / 500 | 0 | 0.23670 | 0.27630 | 3945.46 | 3689 | 4216 |
| 150 | 500 / 500 | 0 | 0.26648 | 0.30960 | 4019.23 | 3748 | 4295 |
| 175 | 500 / 500 | 0 | 0.29383 | 0.34903 | 4083.98 | 3763 | 4521 |
| 200 | 500 / 500 | 0 | 0.31739 | 0.37024 | 4125.92 | 3857 | 4365 |
| 225 | 500 / 500 | 0 | 0.33744 | 0.38869 | 4156.72 | 3920 | 4406 |
| 250 | 500 / 500 | 0 | 0.35446 | 0.40242 | 4186.20 | 3904 | 4426 |
| 300 | 500 / 500 | 0 | 0.38484 | 0.43788 | 4222.68 | 4006 | 4452 |
| 350 | 500 / 500 | 0 | 0.40870 | 0.45288 | 4244.32 | 4044 | 4509 |
| 400 | 500 / 500 | 0 | 0.42693 | 0.47577 | 4257.81 | 4052 | 4494 |
| 500 | 499 / 500 | 1 | 0.45203 | 0.49208 | 4267.87 | 4032 | 4456 |

## Simple

**Test per numero di scambi** (con lo stesso script di `test_medium_disorder.py`, adattato al flag `--simple`) — N = 100, 500 test per riga:

| swaps | valid tests | scartati (disorder ≥ 0.5) | avg disorder | max disorder | media mosse | min mosse | max mosse |
|---|---|---|---|---|---|---|---|
| 1 | 500 / 500 | 0 | 0.01336 | 0.03859 | 118.56 | 0 | 196 |
| 2 | 500 / 500 | 0 | 0.02644 | 0.06869 | 159.29 | 50 | 214 |
| 3 | 500 / 500 | 0 | 0.03811 | 0.09111 | 181.96 | 71 | 230 |
| 5 | 500 / 500 | 0 | 0.06224 | 0.13556 | 200.71 | 129 | 247 |
| 8 | 500 / 500 | 0 | 0.09570 | 0.16848 | 220.78 | 145 | 295 |
| 10 | 500 / 500 | 0 | 0.11641 | 0.19939 | 237.15 | 156 | 309 |
| 15 | 500 / 500 | 0 | 0.16180 | 0.25535 | 285.53 | 201 | 380 |
| 20 | 500 / 500 | 0 | 0.20301 | 0.32283 | 328.66 | 252 | 398 |
| 30 | 500 / 500 | 0 | 0.26823 | 0.37919 | 387.09 | 304 | 464 |
| 50 | 500 / 500 | 0 | 0.35389 | 0.44242 | 462.49 | 379 | 540 |
| 75 | 488 / 500 | 12 | 0.41609 | 0.49657 | 507.33 | 411 | 582 |
| 100 | 451 / 500 | 49 | 0.44654 | 0.49980 | 528.92 | 447 | 602 |

**Test per numero di scambi** — N = 500, 500 test per riga:

| swaps | valid tests | scartati (disorder ≥ 0.5) | avg disorder | max disorder | media mosse | min mosse | max mosse |
|---|---|---|---|---|---|---|---|
| 1 | 500 / 500 | 0 | 0.00262 | 0.00780 | 579.38 | 49 | 985 |
| 2 | 500 / 500 | 0 | 0.00536 | 0.01392 | 773.85 | 207 | 1122 |
| 3 | 500 / 500 | 0 | 0.00787 | 0.01689 | 875.11 | 338 | 1150 |
| 5 | 500 / 500 | 0 | 0.01297 | 0.02487 | 949.94 | 511 | 1208 |
| 8 | 500 / 500 | 0 | 0.02055 | 0.03471 | 989.36 | 721 | 1203 |
| 10 | 500 / 500 | 0 | 0.02550 | 0.04290 | 1009.99 | 750 | 1197 |
| 15 | 500 / 500 | 0 | 0.03752 | 0.05836 | 1068.40 | 880 | 1509 |
| 20 | 500 / 500 | 0 | 0.04950 | 0.07410 | 1163.39 | 984 | 1612 |
| 30 | 500 / 500 | 0 | 0.07272 | 0.10067 | 1449.18 | 1162 | 1893 |
| 50 | 500 / 500 | 0 | 0.11517 | 0.15176 | 1945.02 | 1594 | 2253 |
| 75 | 500 / 500 | 0 | 0.16136 | 0.20288 | 2362.83 | 1990 | 2735 |
| 100 | 500 / 500 | 0 | 0.20087 | 0.25186 | 2744.43 | 2392 | 3133 |

---

# Script di test

Script Python usati per generare input e misurare le prestazioni delle varie strategie, tutti basati sul `checker` per confermare che ogni sequenza di mosse prodotta da `push_swap` sia effettivamente valida (`OK`) prima di contare le operazioni.

## Generazione di una sequenza casuale (senza seed)

Genera 500 numeri casuali e stampa direttamente il comando da eseguire con la strategia `--complex`.

```python
python3 -c "import random; nums = random.sample(range(-100000, 100000), 500); print('./push_swap --bench --complex ' + ' '.join(map(str, nums)))"
```

## Generazione di una sequenza casuale (con seed fisso)

Stessa cosa, ma con `random.seed(42)`: utile per ottenere sempre lo stesso input, così i test sono riproducibili e confrontabili tra loro.

```python
python3 -c "import random; random.seed(42); nums = random.sample(range(-100000, 100000), 500); print('./push_swap --bench --complex ' + ' '.join(map(str, nums)))"
```

## Risorse

- *Introduction to Algorithms* (Cormen, Leiserson, Rivest, Stein) — complessità
  asintotica, radix sort, programmazione dinamica (Longest Increasing Subsequence).
- Riferimenti standard sul codice di Lehmer e sulla notazione fattoriale
  (factoradic), usati in `small_bfs_state.c` per indicizzare in tempo costante gli
  stati della BFS.
- Il subject PDF di `push_swap` fornito da 42, per la semantica delle operazioni, la
  metrica di disorder e le classi di complessità richieste.

## Contributi

<table>
<tr><th>Login</th></tr>
<tr><td>&lt;aseveri&gt;</td></tr>
<tr><td>&lt;elvigonz&gt;</td></tr>
</table>
