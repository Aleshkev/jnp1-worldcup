Kryteria oceny zadania Wyjście z Grupy
Języki i narzędzia programowania 1, edycja 2022/23

## Ocena z testów automatycznych: 0 – 6 pkt.

Po jednym punkcie za przejście wszystkich testów z grup od 1xx do 6xx.

## Ocena jakości kodu: 0 – 4 pkt.

Odejmujemy po jednym punkcie za:
1)  niezgodność zawartości repozytorium ze specyfikacją
2)  ostrzeżenia wypisywane przez kompilator
3)  brak header guard
4)  braki const
5)  brak wirtualnych destruktorów (tam gdzie trzeba)
6)  problemy z zarządzaniem pamięci, niekorzystanie ze sprytnych wskaźników
7)  brak wyodrębnionych klas dla gracza, planszy, pola
8)  brak polimorficznych pól lub akcji pól
9)  brak wyodrębnionej klasy reprezentującej kostki
10) cykliczne zależności (w szczególności pomiędzy graczem oraz polem)
11) brak właściwej enkapsulacji, m.in. zwracanie modyfikowalnych struktur danych,
    zbyt duże możliwości modyfikacji stanu obiektu (zbyt dużo publicznych metod,
    „głupie” publiczne settery i gettery)
12) brzydki styl (zbyt duże klasy lub metody, nieprzejrzysty kod, zbyt dużo powiązań)
13) brak komentarzy wyjaśniających założenia projektowe
