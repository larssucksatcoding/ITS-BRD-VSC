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

This is the result of a test - the test has been committed and therefore is in repo's git history
(test: push-pull/ open-drain)

# To-Do:
- [ ] Modulkonzept entwerfen
- [ ] mit Kommentaren

- [ ] importieren des Timer Moduls

## Aufgabe 1:
- [ ] Read ROM implementieren (bzw. ganz simple Search ROM? " Mit dem in der Vorlesung dargestellten Ablauf ..." (GS_Aufgabe4_1-Wire_Bus.pdf, S. 1, letzter Abschnitt))
- [ ] Checksum der ROM prüfen
- [ ] zyklisches Abfragen der ROM 
- [ ] Ausgabe auf Display
- [ ] Fehlermeldung falls kein Sensor angeschlossen
- [ ] Reset implementieren

## Aufgabe 2:
- [ ] bekannte ROMS können verwendet (hardcodiert) werden (Konstanten oder #define)
- [ ] Implementierung Temperaturmessung
    - [ ] Convert T
    - [ ] Read Scratchpad
    - [ ] Temperatur berechnen
- [ ] Display Ausgabe
    - [ ] Family Code
    - [ ] ROM Number
    - [ ] Temperatur

## Aufgabe 3:
- [ ] Search Rom (jetzt richtig, au weia)


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