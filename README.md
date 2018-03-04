# Codificator-de-siruri

Programul citește de la tastatură caractere, cuvinte sau numere, fiecare pe câte o linie, și afisează la consolă mesajul rezultat în urma 
codificării după următorul algoritm.
Prima oară se identifică tipul de termen, după care se aplică o codificare pentru fiecare termen.
Pentru cuvinte se determină cel mai mare divizor comun d al numărului de caractere al cuvântului (diferit de lungimea cuvântului), iar 
primele d caractere ale cuvântului se mută la finalul acestuia. Dacă cuvântului conține o cifră, restul caracterelor vor fi în ordine 
inversă.
Pentru caractere, se determină din mesajul obținut până în acel moment caracterul cu cel mai mic număr de apariții, respectiv caracterul 
cu cel mai mare număr de apariții. Înaintea caracterului citit de la tastatură se adaugă caracterul determinat ca având cel mai mare număr
de apariții, iar după caracterul citit de la tastatură se adaugă caracterul cu cel mai mic număr de apariții. Aceste 3 caractere se 
concatenează la mesajul final.
Pentru numere se determină cel mai mare număr ce se poate obține din acesta prin rotație ciclică a cifrelor sale, în cazul în care avem un 
număr pozitiv, respectiv cel mai mic număr ce se poate obține prin rotația cifrelor în cazul în care numărul este negativ.
La sfârșit de ia mesajul obținut și se împarte într-un număr de bucăți egal cu numărul de componente n citit imediat înaintea întâlnirii
lui END (care încheie citirea). Dacă ultima bucată are mai puțin de n caractere, ele vor face parte din ultima componentă cu n caractere. 
Fiecare componenta va avea o complexitate (media codurilor ASCII ale caracterelor ce compun bucata de mesaj). Dacă 2 componente au aceeași 
complexitate, se sortează lexicografic. Mesajul final va fi compus din aceste componente ordonate descrescător după complexitate.
