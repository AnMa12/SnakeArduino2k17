# SnakeArduino2k17
Arduino Snake Game With Matrix

Joc: SNAKE


1.	Start-ul sa fie cu input de la user: Jocul incepe cu un flashing text “SNAKE” acesta disparnd abia cand user-ul apasa pe butonul de start. Dupa actionarea butonului de start vor aparea pe matrice primul mar si capul sarpelui. 
2.	Sfarsitul sa fie la fel: la final trebuie sa iti arate informatia despre cum ai jucat si aceasta informatie dispare cu un input de la user: Dupa ce sarpele se loveste singur, va aparea un joc de lumini ce va curate tabla, urmat de un flashing text ce prezinta scorul obtinut, urmat de un joc de lumini care se opreste doar la actiuniea butonului de catre user. Dupa ce butonul apasat sterge si jocul luminos se afiseaza printr-un alt flashing text mesajul: ”SEE YA SOON!”
3.	Trebuie sa indeplnieasca cel putin doua(*) din urmatoarele conditii:
*Sa aiba dificultate: are dificultate progresiva, viteza creste cu cat mananci mai multe mere
*Sa aiba scor
4.	Trebuie sa poata fi jucat de cineva cu experienta mediocra cel putin 45 secunde: viteza creste gradual cu o viteza moderata
5.	End game-ul este atins atunci cand sarpele isi atinge coada cu capul

Documentatie:

	Hardware:

	Pentru a realiza jocul am folosit urmatoarele componete hardware:
•	Matrice de leduri – pentru a afisa grafica jocului
•	Joystick – pentru a controla sarpele stanga, dreapta, sus, jos
•	Button – activare start joc sau final joc
•	Fire + Breadbord pentru a lega componentele intre ele

Software

Ideea ce sta la baza codului se rezuma la a lua doi indici i si j care sa memoreze pozitiile capului sarpelui. Acesta se va misca dupa actiunea joystickului la stanga, dreapta, sus sau jos neincetat dupa ce a fost actionat Joystick-ul. Urmatorii indici ce trebuie memoarti sunt indicii de pe pozitia marului. Marul se va aseza random pe matrice, iar dupa ce va fi mancat, (indicii capului sarpelui vor fi aceeasi cu indicii marului) marul va disparea si va a aparea un nou mar random undeva pe matrice. Pentru ca sarpele trebuie sa creasca atunci cand mananca marul, luam un vector de tip structura care sa retina toate pozitiile i si j ale elementelor cozii. Pentru a urmari coada, mereu primul element va fi de fapt spatele capului, iar pentru ca aceasta coada sa se deplaseze ne ajutam de o interschimbare secventiala. Cand capul loveste coada, (coordonatele capului sunt exact aceeleasi cu cele ale unui elemnt din coada) jocul se incheie.

