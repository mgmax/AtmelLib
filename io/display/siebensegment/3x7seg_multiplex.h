/*
 *    Filename: lib/io/display/siebensegment_3digits_10pins.h
 *     Version: 0.0.1
 * Description: Beispieldatei
 *     License: GPLv2 or later
 *     Depends: (none)
 *
 *      Author: Copyright (C) Max Gaukler <development@maxgaukler.de>
 *        Date: 2007-12-12
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*
*  Programm für eine 3-stellige Siebensegmentanzeige im Multiplex-Betrieb.
*  Funktioniert nur mit bestimmten Anzeigen, diese MÜSSEN 10 Pins haben und
*  intern gemultiplext sein.
*/

#ifndef _HAVE_LIB_IO_DISPLAY_SIEBENSEGMENT_3x7SEG_MULTIPLEX_H
#define _HAVE_LIB_IO_DISPLAY_SIEBENSEGMENT_3x7SEG_MULTIPLEX_H

// Warning ausgeben und Fkt ausblenden, wenn für siebensegment_3stellig die Defines nicht gesetzt sind
#ifndef SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_DIGITS
#define SIEBENSEGMENT_3x7SEG_MULTIPLEX_H_PRINT_WARNING
#endif

#ifndef SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON
#define SIEBENSEGMENT_3x7SEG_MULTIPLEX_H_PRINT_WARNING
#endif

#ifndef SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON_OFFSET
#define SIEBENSEGMENT_3x7SEG_MULTIPLEX_H_PRINT_WARNING
#endif

#ifdef SIEBENSEGMENT_3x7SEG_MULTIPLEX_H_PRINT_WARNING

#ifndef SIEBENSEGMENT_3x7SEG_MULTIPLEX_H_PRINT_WARNING_OFF
#warning aufgrund fehlender Defines wurde die Library 3x7seg_multiplex.h ausgeblendet.
#warning um die Funktion siebensegment_3stellig zu nutzen, muss folgendes definiert sein:
#warning SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_DIGITS ist der Port der einzelnen Segmente (7 Pins)
#warning SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON ist der Port für das gemeinsame Plus jeder Displaystelle
#warning SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON_OFFSET ist z.B. 2 wenn die ersten 2 Pins des Ports übersprungen werden
#warning um dieses WARNING zu unterdrücken: #define SIEBENSEGMENT_3x7SEG_MULTIPLEX_H_PRINT_WARNING_OFF
#endif

#else


# warning Diese Datei ist noch experimentell und nicht getestet - bitte testen und die Warnung entfernen

// Siebensegment_port:
// Ansteuerung einer Siebensegment-Ziffer-Anzeige
// Die 7 niederwertigsten Bits (PX0...PX6) des Ports werden erst genullt (port &= 0x80)
// und dann je nach Zahl gesetzt (port |= 0x..)
inline unsigned char int2siebensegment(int x) {
	// links/rechts oben |
	#define LO 1<<0
	#define RO 1<<1
	// links/rechts unten |
	#define LU 1<<2
	#define RU 1<<3
	// oberer/mittlerer/unterer Querstrich _
	#define OQ 1<<4
	#define MQ 1<<5
	#define UQ 1<<6
	
	switch (x) {
		case 0: return LO | RO | LU | RU | OQ | UQ;
		case 1: return LO | LU;
		case 2: return OQ | RO | MQ | LU | UQ;
		case 3: return OQ | MQ | UQ | RO | RU;
		case 4: return LO | MQ | RO | RU;
		case 5: return OQ | MQ | UQ | LO | RU;
		case 6: return OQ | MQ | UQ | LO | LU | RU;
		case 7: return OQ | RO | RU;
		case 8: return OQ | MQ | UQ | LO | RO | LU | RU;
		case 9: return LO | OQ | MQ | UQ | RO | RU;
	}
}

void siebensegment_3x7seg_multiplex(int in)
{
	int tmp;
	if (in>999) {
		in=999;
	}
	if (in<1) {
		in=0;
	}
	for (i=0;i++;i<3) {
		// Multiplex-Bits leeren
		SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON&=~(0x07 << SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON_OFFSET);
		// Multiplex-Bit setzen
		SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON|= 1<<(SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_COMMON_OFFSET+i);
		// Segmente setzen
		SIEBENSEGMENT_3x7SEG_MULTIPLEX_PORT_DIGITS=int2siebensegment(in%10);
		in=in/10;
		// leuchten bis die nächste Anzeige drankommt
		delayms(3);
	}
	delayms(1);
}
#endif

#endif
