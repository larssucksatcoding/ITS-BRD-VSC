A module concept has been shared among the participants of this project.

Please proceed with care.

Currently there is such an enormous To-Do-List that I will not start adding any To-Dos. Adding To-Dos might take an even longer timer than actually implementing the project. 

I am aware, that this statement is blasphemic since writing these lines is not necessary and  I could have spent my time creating a purposeful To-Do-List instead of publishing nonsense.

Now I will accomplish my duty after all:

# How to set the Pins in Push-Pull & Open-Drain?

Open-Drain:     the Bus is high, if PD1 and PD0 are high.
*               one goes low - Bus goes low/zero

Push-Pull:      the Bus is very high, if PD0 is on. 
*               PD1 does not seem to make any difference 
*               BEWARE: task says we're supposed to leave PD1 on in Push-Pull Mode
*               (Reason for that is that else the current will be to high,
*               since the resistor can be avoided)

This is the result of a test - the test has been committed and therefore is in repo's git history(test: push-pull/open-drain)

# How does the Search ROM algorithm work?

Wir haben Slaves mit folgenden ROM-Nummern 

0  1  2  3  4  5  6  7 
----------------------------
d  0  1  1  1  0  0  1  0
b  0  0  1  0  1  0  0  0
c  0  1  1  1  0  0  0  1
a  0  0  1  0  0  0  0  0

1. Durchlauf 
Unterschied Bit 1  weiter mit 0
diff = 1
Unterschied Bit 4 weiter mit 0
diff = 4
Slave a detected
last_difference = 4

2. Durchlauf 
Durchlauf bis (exklusiv) Bit 4 (kopie von bit 0-3 von Slave a )
währenddessen: diff = 1
Bit 4 jetzt 1 wählen
Slave b detected
last_difference = 1

3. Durchlauf
Durchlauf bis (exklusiv) Bit 1 (kopiere bit 0 von b )
Unterschied Bit 6 
diff = 6
Slave c detected
last_difference = 6

4. Durchlauf 
Durchlauf bis (exklusiv) Bit 6 (kopiere bit 0-5 von c )
kein weiterer Unterschied
Slave d detected
last_difference = -1 (oder auch einfach so lassen?)

-> Alle Slaves  erkannt


# To-Do:

## Aufgabe 1:

## Aufgabe 2:

## Aufgabe 3:

### DONE 

- [x] Modulkonzept entwerfen
- [x] mit Kommentaren
- [x] importieren des Timer Moduls
- [x] implement receive() in bit_talk.c
- [x] check scratchpad length of DS18S20 (0x10) (it's the same uuh yeah)
- [x] figure out how to create a const (u) char array which can be provided to check crc
        - [x] i did not I provide a non constant char - is illegal? no it's not
- [x] I came up with two ideas to copy an array:
        char other_rom[ROM_LENGTH];
        char *rom = other_rom;

        char other_rom[ROM_LENGTH];
        char rom[ROM_LENGTH];
        copy_arr(ROM_LENGTH, other_rom, rom);
        which one is better? do it einheitlich!
- [x] in copy_arr(...) (manager) can source array be bigger than size?
- [x] test receive() with oscilloscope
        - [x] test everything with oscilloscope?
- [x] implement a  recovery time between bytes (or figure out if this is necessary)
            not necessary
- [x] complete the error_handling whoop whoop
- [x] private function rom_detected in slaves.c can we delete it? - yes, we can!

#### Aufgabe 1
- [x] Read ROM implementieren (bzw. ganz simple Search ROM? " Mit dem in der Vorlesung dargestellten Ablauf ..." (GS_Aufgabe4_1-Wire_Bus.pdf, S. 1, letzter Abschnitt))
- [x] Checksum der ROM prüfen
- [x] Ausgabe auf Display
- [x] zyklisches Abfragen der ROM 
- [x] Fehlermeldung falls kein Sensor angeschlossen
- [x] Reset implementieren
    - [x] should we check for presence pulse more than once? reset() commands.c
                we do this now


#### Aufgabe 2
- [x] Implementierung Temperaturmessung
    - [x] Convert T
    - [x] Read Scratchpad
    - [x] Temperatur berechnen
- [x] Display Ausgabe
    - [x] Family Code
    - [x] ROM Number
    - [x] Temperatur
- [x] bekannte ROMS können verwendet (hardcodiert) werden (Konstanten oder #define)
        einfach search rom vorher implementiert


#### Aufgabe 3
- [x] Search Rom (jetzt richtig, au weia)

# Templates

Templates

/**
* @file     -
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    -
*/


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/