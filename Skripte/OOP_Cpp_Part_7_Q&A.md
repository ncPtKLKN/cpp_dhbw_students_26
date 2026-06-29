# Q&A – OOP_Cpp_Part 7.pdf - Die STL: Container, Iteratoren, Algorithmen & Templates

> **Zweck:** Kurze Wiederholung, um nach der Vorlesungspause wieder ins Thema zu kommen.
>
> Themen: STL-Container & Grundlagen · Sequentielle Container · Assoziative Container · Iteratoren & Algorithmen · Templates

---

<!-- markdownlint-disable MD033 -->
## 1. STL-Container – Grundlagen

**F1.1 – Was ist ein Container, und welche gemeinsamen Methoden haben sie?**
<details><summary>Antwort</summary>

    Ein Container speichert eine Menge von Variablen strukturiert – immer nur ein Datentyp.

    Container speichern Werte, nicht Referenzen.

    Gemeinsame Methoden: insert(), clear(), begin(), end(), size(). Container unterscheiden sich teils deutlich in Funktionsumfang und Laufzeit.
    Beispiel: std::vector (gilt als Standardcontainer).
</details>

**F1.2 – Wie ist ein `std::vector` intern aufgebaut?**
<details><summary>Antwort</summary>

    Eine Sequenz von Elementen gleichen Typs, die aufeinanderfolgend auf dem Heap liegen.

    Ein „Handler" speichert zusätzlich Zeiger auf das erste Element, hinter das letzte Element und hinter den gesamt allokierten Speicher, dazu einen Allokator.

    Daraus folgt: size() = Anzahl der Elemente, capacity() = reservierter Platz (kann größer sein als size, damit nicht bei jedem push_back neu allokiert werden muss).
</details>

**F1.3 – Warum ist der Index-Zugriff beim std::vector so effizient, und wann ist er die schlechte Wahl?**
<details><summary>Antwort</summary>

    Weil die Elemente lückenlos hintereinander liegen, ist die Adresse jedes Elements direkt berechenbar (Basis + index × Elementgröße) → Zugriff in O(1), zusätzlich cache-freundlich.

    Schlechte Wahl, wenn häufig mitten im Array eingefügt/gelöscht wird – dann müssen alle nachfolgenden Elemente verschoben (oder neu allokiert und umgezogen) werden.
</details>

---

## 2. Sequentielle Container

**F2.1 – Wann nutzt man `std::array` statt `std::vector`?**
<details><summary>Antwort</summary>

    Wenn die Größe schon zur Compile-Zeit feststeht und sich nicht ändert. std::array hat eine fixe Größe, braucht weniger Speicher und ist beim Zugriff genauso effizient.

    Besonderheit: std::array ist der einzige Standard-Container, der seine Elemente inline (ohne Heap-Allokation) speichert – alle anderen allokieren ihren Element-Speicher auf dem Heap.
</details>

**F2.2 – Was unterscheidet `std::deque` und `std::list` vom std::vector?**
<details><summary>Antwort</summary>

    - std::deque (Double-Ended-Queue): kann an beiden Enden – vorne und hinten – effizient einfügen/löschen (beim std::vector ist nur das Ende effizient).

    - std::list (doppelt verkettete Liste): effizientes Einfügen/Löschen an beliebiger Position, aber ineffizienter Positionszugriff (O(n), kein wahlfreier Zugriff – man muss vom Anfang durchhangeln). Bietet „stable storage": andere Elemente werden beim Einfügen/Entfernen nicht verschoben.
</details>

**F2.3 – Was ist der Unterschied zwischen `std::stack` und `std::queue`?**
<details><summary>Antwort</summary>

    - std::stack: LIFO (Last in, first out) – nur top, push, pop; man kommt nur an das oberste Element. Beispiel: der Callstack.
    - std::queue: FIFO (First in, first out) – hinten anfügen, vorne wegnehmen.
    Beide sind Adapter und nutzen intern standardmäßig eine deque.
</details>

---

## 3. Assoziative Container

**F3.1 – Was ist eine `std::map`, und worauf muss man beim Nachschlagen achten?**
<details><summary>Antwort</summary>

    Ein Container aus Key-Value-Paaren mit schnellem Zugriff auf den Wert bei gegebenem Key. Intern ein sortierter Suchbaum → Zugriff/Suche in O(log n), Iteration in sortierter Reihenfolge.

    Vorsicht: operator[] legt bei einem unbekannten Key still einen neuen Eintrag an (Wert default-initialisiert). Zum reinen Nachschlagen daher besser die find() oder count() Methode verwenden.
</details>

**F3.2 – Welche weiteren assoziativen Container gibt es?**
<details><summary>Antwort</summary>

    - std::set: Sammlung eindeutiger Schlüssel, automatisch sortiert (kein Wert, nur „ist X enthalten?").

    - std::multiset: wie set, aber doppelte Schlüssel erlaubt.

    - std::multimap: wie map, aber doppelte Schlüssel erlaubt.
</details>

**F3.3 – Was ist der Unterschied zwischen ordered und unordered Containern?**
<details><summary>Antwort</summary>

    - ordered (map/set): sortiert gespeichert (Suchbaum), in Reihenfolge iterierbar, Zugriff in O(log n).

    - unordered (unordered_map, unordered_set, …): Hash-Tabellen-basiert. Eine Hash-Funktion berechnet aus dem Schlüssel direkt ein „Fach" → Zugriff in O(1) im Schnitt, aber nicht in sortierter Reihenfolge iterierbar.

    Faustregel: ordered für sortierte Iteration/Bereichsabfragen, unordered für maximal schnellen Zugriff.
</details>

---

## 4. Iteratoren & Algorithmen

**F4.1 – Was ist ein Iterator und wozu dient er?**
<details><summary>Antwort</summary>

    Ein Objekt, das auf ein Element in einer Folge zeigt; die elementarste Form ist ein Pointer.

    Iteratoren sind das Bindeglied zwischen Containern und Algorithmen: Ein Algorithmus (z. B. sort) kennt den Container nicht, sondern arbeitet nur über Iteratoren – deshalb läuft derselbe Algorithmus auf vector, array, list usw.

    begin() zeigt auf das erste Element, end() hinter das letzte (end() ist kein gültiges Element und darf nicht dereferenziert werden).
</details>

**F4.2 – Warum sollte man STL-Algorithmen nutzen, statt selbst zu implementieren?**
<details><summary>Antwort</summary>

    Effizienz/Optimierung, Fehlervermeidung (z. B. Off-by-one), bessere Lesbarkeit und Wartbarkeit, Konsistenz, Zeitersparnis und Portabilität.

    Die Algorithmen sind getestet und überall gleich verfügbar.
</details>

**F4.3 – Wie sortiert man einen Container, und wie ändert man die Sortierreihenfolge?**
<details><summary>Antwort</summary>

    Mit std::sort(begin, end) aus <algorithm>. Standardmäßig wird der <-Operator zum Vergleichen benutzt.

    Die Reihenfolge ist überschreibbar, indem man eine eigene Vergleichsfunktion bzw. ein Lambda übergibt (z. B. absteigend oder nach eigenem Kriterium).

    Hinweis: std::list hat ein eigenes sort(), weil das freie std::sort Random-Access-Iteratoren braucht, die eine Liste nicht hat.
</details>

---

## 5. Templates

**F5.1 – Was sind Templates und wozu dienen sie?**
<details><summary>Antwort</summary>

    Sie erlauben, eine Funktion (oder Klasse) zu schreiben, die mit verschiedenen Datentypen funktioniert – gleicher Code, beliebiger Typ.

    Genau das ermöglicht die STL über-haupt erst (Container und Algorithmen für beliebige Typen).

    Syntax: template <class T> vor der Funktion, T als Platzhalter für den Typ. Für mehrere Parameter: template <class T, class U>. T kann auch als Rückgabetyp dienen.
</details>

**F5.2 – Was passiert intern beim Kompilieren eines Templates, und welcher Nachteil ergibt sich?**
<details><summary>Antwort</summary>

    Der Compiler erzeugt für jeden tatsächlich genutzten Typ eine eigene Version der Funktion/Klasse.

    Nachteil: Die ausführbare Datei wird größer (ROM bzw. Code-Größe steigt).

    Templates nutzt man längst unbewusst, z. B. vector<string> (intern push_back(T value)). Statt class kann auch typename verwendet werden (äquivalent).
</details>

---
*Grundlage: OOP mit C++ – Teil 7 (Kapitel 4: Die Standard Template Library – Container, Iteratoren, Algorithmen, Templates).*
