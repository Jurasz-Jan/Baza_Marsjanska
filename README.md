#Baza_Marsjanska
##Projekt na Algorytmy i Struktury Danych II. Autorzy: Jan Jurasz, Adam Migdalski, Paweł Kopeć.

##Baza marsjańska
Na obcej planecie zakładana jest ziemska kolonia. Początkowo astronauci mają do dyspozycji tylko jeden moduł pełniący funkcję bazy. Do tego modułu podłączane są następne części (zasoby). Graf zadań opisuje zadania, które wykonują poszczególne sekcje bazy (wierzchołki) oraz ilość danych (d) przesyłanych pomiędzy zasobami (krawędzie). Moduły można podzielić na 2 rodzaje:

Ogólnego przeznaczenia - mogące wykonywać więcej niż jedno zadanie (wykonują zadanie wolno, ale niskim kosztem)
Specjalizowane - mogące wykonywać tylko jedno zadanie (koszt wykonania zadania przez te zasoby jest wysoki, ale czas wykonania niewielki)
Każdy moduł bazy musi być połączony kanałami komunikacyjnymi (odpowiedzialne są za transmisję danych; czas transmisji wynosi O jeśli 2 sąsiednie zadania są wykonywane przez ten sam zasób, w innym przypadku jest równy: t =). Genotyp opisuje dodawanie kolejnych zasobów do systemu. W każdym węźle drzewa znajduje się procent pobranych zadań od poprzednika (zadania pobierane są losowo aż do momentu osiągnięcia odpowiedniej wartości) oraz opcja według której wybierany jest kolejny dołączany zasób. Opcjami mogą być:

Najtańszy zasób ogólnego przeznaczenia
Najszybszy zasób (wykonujący najszybciej przejęte zadania)
Dla którego iloczyn sumy czasów przejętych zadań i sumy kosztu wykonania przejętych zadań jest najmniejszy
Ten sam co dla poprzedniego węzła
Najrzadziej alokowany
Każda z powyższych opcji posiada prawdopodobieństwo wyboru (numer opcji - prawdopodobieństwo):
1-0,1
2-0,1
3-0,4
4-0,2
5-0,2

Opcje wyboru kanału komunikacyjnego pomiędzy modułami (w nawiasach obok opcji znajdują się wartości prawdopodobieństwa) mogą być następujące:

Najtańszy kanał komunikacyjny
Kanał komunikacyjny o największej przepustowości
Ten sam co dla poprzednika
Najrzadziej używany
Pokolenie początkowe

##	Pokolenie początkowe
Losowo wygenerowane (n) genotypów (П=anz) zależne od liczby wierzchołków w grafie zadań (n) oraz liczby zasobów (z). Wielkość pokolenia początkowego jest sterowana przez użytkownika programu poprzez parametr a (podawany z klawiatury).

Krzyżowanie
Przy pomocy operatora selekcji wybieranych jest w genotypów (w=y*n; parametr y jest podawany przez użytkownika z klawiatury spomiędzy wartości 0-1; 0<y<1). Następnie osobniki łączone są losowo w pary, losowo wybierany jest punkt przecięcia i następuje wymiana poddrzew pomiędzy rozwiązaniami.

Mutacja
Przy pomocy operatora selekcji wybieranych jest genotypów (Q=ẞ*П; parametr ẞ jest podawany przez użytkownika z klawiatury spomiędzy wartości 0-1; 0<B<1). Następnie losowo wybierany jest węzeł (dla każdego rozwiązania osobno) i zamieniana jest opcja znajdująca się w wybranym węźle na inną (uwzględniając prawdopodobieństwo wyboru poszczególnych opcji).

Klonowanie
Przy pomocy operatora selekcji wybieranych jest O genotypów (D=8*П; parametr 8 jest podawany przez użytkownika z klawiatury spomiędzy wartości 0-1; 0<8<1). Genotypy te są kopiowane do następnego pokolenia.

Selekcja
Do wyboru.

Warunek stop
Jeśli w ε kolejnych rozwiązań lepsze rozwiązanie nie zostanie znalezione, algorytm kończy działanie.

Mapowanie genotypu w fenotyp
Wykonanie wszystkich funkcji w węzłach genotypu, obliczenie czasu i kosztu rozwiązania.

Cel algorytmu
Celem jest uzyskanie najtańszego systemu nie przekraczającego ograniczeń czasowych (ograniczenie czasowe to maksymalny czas, w którym wszystkie zadania powinny zostać wykonane, jest on podawany przez użytkownika programu z klawiatury).