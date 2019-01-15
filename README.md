# minix_fun

Zadanie polega na dodaniu nowego wywołania systemowego

int pstree(pid_t pid, int uid);

do serwera PM (Process Manager).

Funkcja ta powinna być zadeklarowana w pliku unistd.h.

Funkcja pstree(pid, uid) wypisuje na standardowe wyjście drzewo pidów
dla żywych procesów, które są potomkami procesu o zadanym pid i które należą do
użytkownika o zadanym uid (interesuje nas real_uid). Proces o zadanym pid też
jest wypisywany, pod warunkiem że taki proces istnieje i należy do odpowiedniego
użytkownika. Funkcja wypisuje tylko procesy należące do grupy głównej użytkownika
(interesuje nas real_gid procesów), który wywołał funkcję.

Poniższy przykład ilustruje oczekiwany format wyniku.
Załóżmy, że użytkownik o uid=1 stworzył proces o pid=187, a ten proces w wyniku
funkcji fork stworzył trzy procesy o pidach 188, 189 i 190. Następnie proces
o pid 188 stworzył proces o pid 191. Wtedy wywołanie:

pstree(187, 1);

powinno wypisać na standardowe wyjście:
187
---188
------191
---189
---190
Kolejność wypisywania dzieci powinna być zgodna z rosnącymi numerami pid. Każdy
kolejny poziom potomków powinien być wypisywany z liczbą poprzedzających
myślników większą o 3 od poprzedniego poziomu. Gdy potomek Y procesu X nie
spełnia warunków wymaganych do jego wypisania, to funkcja nie powinna wypisać
żadnego z potomków procesu Y, nawet gdy takie potomne procesy spełniają warunki
do wypisania – nie wypisujemy drzew „z dziurami”.

Należy założyć że proces nie może być swoim ojcem, a odpowiednie wpisy w tablicy
procesów dla procesu init są tylko konwencjami. Funkcja pstree powinna dobrze
obsługiwać wypisywanie procesu init.

Wskazówka: serwer PM przechowuje informacje o procesach w tablicy mproc
zadeklarowanej w pliku mproc.h. Żywe procesy mają ustawioną flagę IN_USE.

Funkcja pstree(pid, uid) przekazuje w wyniku 0, jeśli nie wystąpił błąd.
W przypadku błędu funkcja zwraca -1. Sytuacji, w której wywołamy funkcję,
podając uid nieistniejącego użytkownika lub pid nieistniejącego procesu,
nie traktujemy jako błąd. Przy takim wywołaniu nie powinny zostać wypisane
żadne procesy.
