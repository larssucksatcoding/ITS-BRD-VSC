# README

## Modulkonzept

Das grafische Modulkonzept liegt als `modulkonzept.png` im gleichen Ordner wie diese README.

**Begründung für gewählte Modulunterteilung**

Da der Taschenrechner auf einem Stack basiert, macht es Sinn diesen in einem eigenen Modul zu implementieren (siehe `stack.h`). Der Stack enthält eine Methode, die die obersten zwei Werte zurückgibt (`popTopTwoElements`), da alle Matheoperationen und `r` die obersten zwei Werte vom Stack brauchen und es keinen Sinn ergibt, die hiermit verbundenen Fehler außerhalt von `stack.c` zu überprüfen. Außerdem wird für `P` zum printen des Stacks die Funktion `getCopyOfStack` benötigt, da wir das printen als Funktion seperat vom Stack haben wollten.

Da Errorcodes an mehreren Stellen wiederverwendet werden müssen und nicht wirklich direkt an ein anderes Modul angebunden sind, gehören sie in ihr eigenes Modul (siehe `errno.h`).

Für die gegebenen Einfabefunktionen haben wir uns dazu entschieden, zwei Module zu implementieren. Ein Modul für die Matheoperationen `+-*/` (siehe `operator.h`) und ein Modul für die Stackoperationen `pPCdr` (siehe `command.h`). Theoretisch wäre es leichter den Code dadurch wiederzuverwenden. Wenn z.B. ein anderes Programm einen Stack braucht und Werte davon printen möchte, wäre das möglich, ohne die Matheoperationen unnötig mit importieren zu müssen. Da der Stack seperat von diesen Funktionen wiederverwendbar sein soll, sind diese seperat von ihm implementiert worden, auch wenn beide ihn benutzen.

## Rückmeldung von Fehlern

Die Fehler werden als Errorcode zurückgegeben (siehe `Inc/errno.h`). Um zu verhindert dass sich die Errorcodes mit den Werten von richtigen Ergebnissen nicht überschneiden, werden die Ergebnisse in call-by-reference Paramter geschrieben, die den jeweiligen Funktionen übergeben werden (siehe z.B. `Inc/operator.h`).


## Geplante Testfälle

### Generelle Testfälle 

**Gegebener Testfall:**

`25 8 6 7 + r / p` gibt den Wert 3 aus.
`INT_MAX INT_MIN /` gibt den Wert 0 aus.
`1 2 3 4 5  + - * / p` gibt den Wert -3 aus.

### Division durch Null

`3 0 /` sollte DIVISION_BY_ZERO error werfen.
`0 3 /` sollte NO_ERROR zurückgeben und 0 schreiben.

### Bereichsüberschreitung

**Addition:**

`INT_MAX  1 +` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX  0 +` sollte NO_ERROR zurückgeben und INT_MAX schreiben.

`INT_MIN -1 +` sollte ARITHMETIC_OVERFLOW werfen
`INT_MIN  0 +` sollte NO_ERROR zurückgeben und INT_MIN schreiben.

**Subtraktion:**

`INT_MIN 1 -` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MIN 0 -` sollte NO_ERROR zurückgeben und INT_MIN schreiben.

`0 INT_MIN -`  sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX -1 -` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX  0 -` sollte NO_ERROR zurückgeben und INT_MAX schreiben.

**Multiplikation:**

`INT_MIN -1 *` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX -1 *` sollte NO_ERROR und -INT_MAX zurückgeben.

### STACK_OVERFLOW

`1 2 3 4 5 6 7 8 9` sollte STACK_OVERFLOW werfen (bei MAX_SIZE = 8).
`1 d d d d d d d d` sollte STACK_OVERFLOW werfen.
`1 2 3 C 1 2 3 4 5` sollte NO_ERROR zurückgeben.

### STACK_UNDERFLOW

`r` sollte STACK_UNDERFLOW werfen.
`1 r` sollte STACK_UNDERFLOW werfen.
`1 2 r` sollte NO_ERROR zurückgeben.
`1 d r` sollte NO_ERROR zurückgeben. (setzt `d` size korrect?)

`p` sollte STACK_UNDERFLOW werfen.
`1 p 2 p p` sollte STACK_UNDERFLOW werfen. (wird size korrekt gesetzt?)
`1 2 3 4 C 1 p p` sollte STACK_UNDERFLOW werfen. (wird size zurückgesetzt?)

`d` sollte STACK_OVERFLOW werfen.
`1 d` sollte NO_ERROR zurückgeben.


## TODOs

Kann man sich nicht vor drücken:
- [ ] Lars: `operator.h` Kommentare (und generell auch xd)
- [ ] Funktion zum printen von Zahlen (nicht sprintf!)
- [ ] Main Loop
- [ ] Noah: Was macht `getFirst()` wenn der Stack keine Elemente hat?

Kann man sich vllt vor drücken:
- [ ] Vllt macht es wegen `getCopyOfStack` Sinn für den Stack einen eigenes struct zu definieren, damit man den Typ davon als Parameter benutzen kann? (z.B. `getCopyOfStack(T_stack* stack)` statt `getCopyOfStack(int[] copy)`).
- [ ] Vllt macht es Sinn einen eigenen Datentypen für die Fehler zu implementieren damit man bei Funktionen die Fehler zurückgeben können klar sehen kann, dass der Rückgabewert ein Fehler ist? (z.B. `T_Error add(int* result)` statt `int add(int* result)`). 
