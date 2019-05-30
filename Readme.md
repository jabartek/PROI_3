# Statki – gra turowa (Projekt C++ w ramach PROI)

## Założenia

Założeniem projektu jest zrealizowanie funkcjonalnej gry w statki dla dwóch z interaktywnym interfejsem z użyciem biblioteki _New Curses_ oraz z możliwością zapisywania i wczytywania stany gry.

## Klasy w ramach projektu

### Ship

Polimorficzna klasa reprezentująca statek. W celu realizacji funkcji ustawiania na mapie, usuwania z mapy, strzelania i wyświetlania stanu posiada następujące funkcje/procedury:

- bool placeAtXY – ustawienie na danym polu danej planszy z danym skierowaniem, zwraca informację o powodzeniu ustawiania
- void removeFromMap – usuwa statek z mapy (jeśli jest na jakiejś ustawiony)
- bool isValid – weryfikuje ustawialność statku w danej pozycji
- int shotAtTile – strzał w określony segment statku, zwraca liczbę uderzeń, którą otrzymał ten segment – potencjalnie zostanie tu zrealizowana obsługa wyjątków (max. 1 strzał na pole)
- int damageTile – zwiększa licznik uszkodzeń na danym segmencie, zwraca sumę tychże
- int getTile – zwraca liczbę dotychczas zebranych przez dany segment obrażeń
- int getSize – zwraca wielkość statku
- bool isDead – weryfikuje, czy statek został już zatopiony
- char renderTile – umożliwia wyrenderowanie konkretnego segmentu statku zależnie od parametru (wyświetlaj zawsze/tylko jeśli trafione, wyświetlaj obrażenia/wszystkie pola jednakowo)

Ship posiada 4 klasy dziedziczące z niego – Carrier, Battleship, Cruiser, Destroyer, odpowiadające poszczególnym wielkościom stataków (5, 4, 3, 2). W ramach tych dziedziczących klas realizowane są funkcje damageTile i getTile. To w ramach tych klas przechowywane są tablice obrażeń. Pozostałe dane (lokalizacja, wielkość) przechowywane są na poziomie klasy Ship

### Grid

Klasa reprezentująca mapę ze statkami. Zawiera 4 tablice wielkości mapy, w których przechowuje dane:

- Ship\* ships\_ - przechowująca wskaźniki na statki znajdujące się na danych polach,
- int neighbors\_ - przechowująca informację o liczbie statków na sąsiadujących polach,
- int tileNum\_ - przechowująca informację o tym, który segment statku znajduje się na danym polu,
- bool revealed\_ - przechowująca informację o tym, czy pole zostało odkryte,

a także przechowuje informację o liczbie pozostających przy życiu statków.

Dla każdej z tablic posiada funkcje służące wypisywaniu i umieszczaniu danych. Poza nimi istotne funkcje wykorzystywane w innych częściach programu to:

- int getXSize, int getYSize – zwracające wielkość mapy w osiach x i y
- int shotAtXY – służąca strzelaniu w dane pole planszy, zwraca liczbę dotychczasowych trafień dla statku, 0 dla pustego pola
- char renderXY – służąca wyświetleniu danego pola planszy w ramach parametru (statki tylko na odkrytych/z obrażeniami/etc.)

Konstruktor klasy dba o wyzerowanie wszystkich tablic i ustalenie wartości, w ramach destruktora statki z planszy są usuwane z gry (delete).

### Player

Klasa Player jest kontenerem do przechowywania wszystkich informacji związanych z danym graczem. Jest to wskaźnik do mapy (Grid) do umieszczenia statków oraz lista (std::list) statków, które oczekują na umieszczenie. Funkcje, które realizuje Player to:

- Grid\* getGrid – zwracająca wskaźnik do mapy
- bool isDead – weryfikująca, czy gracz przegrał już grę
- void giveShip – dodająca statek do listy tych do umieszczenia
- bool placeShip – służąca przemieszczeniu statku z listy na mapę

### Game

Klasa Game odpowiada za realizowanie rozgrywki. Przechowuje wszystkie ważne dla uruchomienia gry dane (wielkość planszy, liczby statków), aktualny stan gry (gracz, którego tura jest wykonywana) oraz dwie instancje klasy Player, w ramach których przechowywane są dane o samym przebiegu gry. Poza funkcjami przekazującymi wskaźniki do instancji klasy Player, Game implementuje:

- bool saveGame – oparta na wypisaniu do strumienia funkcja zapisująca aktualny stan gry
- void loadGame – procedura wczytująca stan gry ze strumienia i uruchamiająca ją od zapisanego stanu

## Zastosowane techniki programistyczne

- Dziedziczenie – jest zrealizowane w ramach klasy Ship i wariantów statków
- Funkcje wirtualne – występują w klasie Ship i wariantach statków
- Współpraca ze strumieniami – zostanie zrealizowana w ramach klasy Game
- Klasy kontenerowe i iteratory – są w użyciu w ramach klasy Player (lista statków)
- Obsługa sytuacji wyjątkowych – zostanie zrealizowana w ramach obsługi strzelania

## Przebieg gry

1. Inicjalizacja – ustala się wartości dla klasy Game i uruchamia grę (startGame)
2. Ustawianie – gracze ustawiają statki list (znalazły się tam w ramach pkt. 1) na mapę
3. Bitwa – gracze naprzemiennie strzelają (shotAtXY) w planszę przeciwnika, odkrywając kolejne pola i uszkadzając statki
4. Koniec gry – gra dobiega końca, gdy wszystkie statki jednego z graczy są zatopione (isDead)

## Interfejs użytkownika

Interfejs użytkownika zostanie zrealizowany przy użyciu biblioteki _New Curses_ (ncurses.h). Użytkownik będzie miał do czynienia z 4 oknami:

- Statki własne – informacja o liście własnych statków (umieszczonych i nieumieszczonych na mapie)
- Statki przeciwnika - informacja o liście statków przeciwnika (umieszczonych i nieumieszczonych na mapie)
- Mapa własna – wyświetlająca mapę gracza, zawsze odkryta
- Mapa przeciwnika – wyświetlająca mapę przeciwnika – pola odkryte to jedynie te, w które strzelano

W początkowej fazie (ustawianie) gracz prowadzi interakcję ze Statkami własnymi i Mapą własną. W późniejszej (bitwa) – z Mapą przeciwnika.
