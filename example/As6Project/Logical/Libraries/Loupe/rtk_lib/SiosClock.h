
/* sequential io scheduler clock */

#ifndef _SIOS_CLOCK_H_
#define _SIOS_CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif


/*  SIOS Aufloesung auslesen.
    Der Rueckgabeparameter liefert die die tatsaechliche SIOS-Zykluszeit in Nanosekunden. Dieser Wert entspricht
    auch gleichzeitig der Aufloesung der SIOS-Clock. Die Aufloesung der SIOS-Clock wird staendig korrigiert und
    angepasst. Bei Verwendung des Wertes genuegt es also nicht ihn nur einmal zu Beginn auszulesen, er muss
    von Zeit zu Zeit aktualisiert werden.
*/
void siosClockGetRes(unsigned long* resolution);

/*  SIOS Zeit auslesen.
    Die beiden Rueckgabeparameter, aufgeteilt in einen Sekunden- und einen Nanosekunden- Anteil, liefern die
    Uhrzeit zum Beginn des laufenden SIOS-Zyklus. Beide Werte beziehen sich auf den festgelegten Zeitpunkt:
    01.01.1970, 00:00:000000000.
*/
void siosClockGetTime(unsigned long* seconds, unsigned long* nanoscs);


#if AR_CORE
#include <private/SiosClockP.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
