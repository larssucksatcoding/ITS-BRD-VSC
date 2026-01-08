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

# To-Do:

- [ ] complete the error_handling whoop whoop

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