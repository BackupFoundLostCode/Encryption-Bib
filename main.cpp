#include <bitset>
#include <vector>

#include "crypt.h"





int main() {
    /* GENERELLE IDEEN:
     * 1. Nochmal substring anschauen.
     * 2. Effizienz des codes verbesser, wenn alles fertig ist.
     *
     * PROGRAMMIERZIEL GERADE:
     * TRIVIUM
     * Schieberegister mit Rückkoblungskoeffizenten.
     * Schieberegister mit Rückk.Koeffiz. speziell für Trivium (müssen sich gegenseitig füttern). NE OHNE ABER IM GRUNDE IST ES RICHTIG: DAS MIT DEM EFFIZEINTEN IST WAS ANDERES.
     * Initialisierungsvektor (IV) für Trivium erzeugen. (nur bitset mit 80 bit und random bits). hab ich im grunde.
     *
     * ANMERKUNGEN:
     * 1. Bitsets alleine funktionieren wie arrays also setzen über i auslesen über i usw.
     * 2. Bitset kann ich auch ture und false setzen anstatt 0 und 1 (intern egal aber nur das es nicht vergessen wird).
     * 3. bitset nutzt die Indizes eigentlich genauso wie ein Array: Wir fangen bei 0 an und gehen bis Länge - 1. Aber bei der Ausgabe werden die Bits umgekehrt dargestellt: bitset[0] steht ganz rechts und bitset[Länge - 1] ganz links.bitset nutzt die Indizes eigentlich genauso wie ein Array: Wir fangen bei 0 an und gehen bis Länge - 1. Aber bei der Ausgabe werden die Bits umgekehrt dargestellt: bitset[0] steht ganz rechts und bitset[Länge - 1] ganz links.
     * 4. BITSET IST ANDERS ALS ARRAYS VOM INDEX HER:
     *    Ausgabe:     1 1 0 0 0 0 1 1
     *    Index:       7 6 5 4 3 2 1 0
     *                 ↑             ↑
     *                [7]           [0]
     *
     * 5. XOR: ^ oder auch (a+b)%2 (mit Bits)
     * 6. AND: & oder auch a*b (mit Bits)
     * 7. OR: | oder auch (bit1 +bit2) -(bit1*bit2)
     * 8. NOT: ~ im grunde wird einfach das bit umgedreht, sagen wir A = 1 dann ist NOT A = 0. Wenn es Bitfolgen sind, also A = 10001 dann ist NOT A = 01110.
     * 9. NAND: ~(a&b)
     * 10. NOR: ~(a|b)
     * 11. XNOR: ~(a^b)
     *
     * ERLEDIGT:
     * 1. Echter Zufallsgerator zwischen 0 und 1 über Halbleiter.
     * 2. Affine Verschlüsselung.
     * 3. One-Time-Pad (OTP).
     * 4. LFSR
     */

    //Check ob der iv random befüllt wird:
    std::vector<bool> message = {false,true,true,false,true,true};
    std::vector<bool> iv = advance::trivium::keystream_trivium(message);

    for (int i = 0; i < iv.size(); i++) {
        std::cout << iv[i];
    }






    return 0;
}