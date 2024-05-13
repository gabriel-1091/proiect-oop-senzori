Acest proiect își propune să realizeze gestiunea profilelor senzorilor IoT dedicați măsurării calității apei potabile dintr-un sistem asemănător rețelei publice de alimentare cu apă pe baza mai multor indicatori.

În acest exemplu, vom lucra cu două categorii de senzori IoT: standard și premium (derivati din cei standard, având funcționalități extra) - amplasați în diverse locații/cartiere din București.

Senzorii STANDARD rețin informații referitoare la:

-	id (unic pentru fiecare senzor)
-	denumirea producătorului 
-	nr. de măsurători al valorilor pH-ului apei
-	valorile pH-ului (indică caracterul acid sau bazic al unei substanțe)
-	concentrația de clor din apă (măsurată în mg/l)
-	temperatura apei: ultimele 5 valori (în grade Celsius)
-	turbiditate: măsoară transparență apei ; unitate de măsură-UNT (Unități Nefelometrice de Turbiditate)
-	cartier: locația în care este amplasat senzorul
-	starea senzorului: măsoară durata de viață a senzorului în procente ; sub un anumit prag se va recomanda înlocuirea
-	adâncimea senzorului (în metri)
-	remote access: variabilă booleană ce ne indică dacă senzorul poate fi accesat de la distanță


Senzorii PREMIUM rețin informații referitoare la:
-	TOATE CELE DE MAI SUS
-	concentrația de nitrați (măsurată în mg/l)
-	prezența bacteriei E.Coli (variabilă booleană - valoarea true declară automat sursa de apă drept PERICULOASĂ)
-	nr. de măsurători al conductivității apei
-	valorile conductivității: indică totalitatea sărurilor minerale (K, Că, Mg, Fe) dizolvate în apă 

Pentru o analiză complexă a stării sistemului public de alimentare cu apă, vom presupune de la început că toți senzorii amplasați în locațiile din capitală sunt de tip PREMIUM. 

Datele despre toți senzorii noștri vor fi preluate dintr-un fișier .txt denumit "inputSenzoriPremium" cu următoarea structură:
-	[nr. total de senzori]
-	[denumire producător]
-	[adâncime senzor]
-	[stare senzor]
-	[cartier]
-	[remote access]
-	[concentrație clor]
-	[turbiditate]
-	[nr. măsurători pH]
-	[măsurători pH]
-	[temperatura - 5 măsurători]
-	[spațiu gol]
-	[nitrați]
-	[e.Coli]
-	[nr. măsurători conductivitate]
-	[măsurători conductivitate]
-	[…următorul senzor…]

Profilul senzorilor cuprinde următoarele funcționalități implementate:
-	afișarea tuturor datelor din fișierul "inputSenzoriPremium" către utilizator, la consolă
-	adăugarea de noi senzori standard/premium de la tastatură
-	scrierea într-un fișier .txt de output al senzorilor standard/premium
-	determinarea gradului de inteligenta (siguranta apei potabile) pe baza unui algoritm propriu si scrierea rezultatelor intr-un fisier .txt (denumirea si calea sunt alese de utilizator)

Intervale de siguranță pentru indicatorii vizați:
-	concentrație clor: între 0.1 - 0.5 până la 1 mg/l
-	turbiditate: între 1-250 (între 1 și 5 pt. apa potabilă)
-	pH: între 6.5- 8.5 pt. apa potabilă
-	temperatura: între 4-12 grade celsius
-	nitrați: < 10 mg/l
-	conductivitate: < 2500 microSiemens/cm
-	e.Coli = 0

    Prin gradul de inteligență al acestui sistem IoT înțelegem capacitatea de a identifica sursele sigure, cât și pe cele nesigure de apă potabilă

 	Analiza efectuată este una modulară, în funcție de indicatorii măsurați. Majoritatea indicatorilor prezintă intervale de siguranță (prezentate mai sus).

 	Spre exemplu, sursele care prezintă valori peste limita admisă medie a pH-ului sau prezintă orice cantitate de bacterii E.Coli, automat sunt declarate nesigure. Locațiile în care senzorii măsoară valori normale, în limitele admise, sunt declarate sigure și este continuată monitorizarea
