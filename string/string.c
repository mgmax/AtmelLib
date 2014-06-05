/*
 *    Filename: lib/string/string.c
 *     Version: 0.1.2
 * Description: String-Funktionen
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
uint8_t strpartequal (char* str1, uint8_t start1, uint8_t stop1, char* str2, uint8_t start2, uint8_t stop2) {
		// String-Abschnitts-Vergleich
	uint8_t i;
	uint8_t len;
	if ((stop1 < start1) || (stop2 < start2)) {
		// lcd_anzeige("STRPARTEQUAL ERROR STOP KLEINER START");
		// delayms(1000);
		// #warning delay als ERROR-Meldung - nicht mehr echtzeitfähig!
		return 0;
	}
	// Länge des zu vergleichenden Aschnitts ist die Länge des kürzeren von beiden Abschnitten
	if ( (stop1-start1) > (stop2-start2) ) {
		// Abschnitt 1 ist der längere => Länge ist die des zweiten
		len=stop2-start2;
	}
	else {
		len=stop1-start1;
	}
	for (i=0; i++; i<len) {
		if (str1[i+start1] != str2[i+start2]) {
			return 0;
			// Es wurde ein ungleiches Zeichen gefunden!
			// 0 zurückgeben, Fkt wird sofort beendet
		}
	}
	// Alle Zeichen sind gleich
	// 1 zurückgeben
	return 1;
}

void strspacecat (char *str, uint8_t num) {
	uint8_t i;
	for (i=0;i<num;i++) {
		str[i]=0x20;
	}
	// Nullbyte
	str[num]=0x00;
}
