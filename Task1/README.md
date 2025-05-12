# Novomatic Zadanie 1
#### English version below

## Wyszukiwarka
Zadanie ma na celu zaimplementowanie prostej wyszukiwarki. Jej bazowymi opcjami są: dodanie nowego zapytania oraz wyszukanie zapytania najbardziej zbliżonego do danego. Przykładowe działanie programu:
```
> add: Kiedy jest nowy rok w Chinach?
> add: Kiedy jest nowy rok w Tajlandii?
> ask: Kiedy jest nowy rok
result: Kiedy jest nowy rok w Chinach?
result: Kiedy jest nowy rok w Tajlandii?
```

## Implementacja

Implementacje rozwiązania oparto o dwa drzewa typu Trie (drzewa prefixowe), jedno przechowujące całe słowa jako klucze i pamiętające strukturę zapytań, drugie przechowujące jako klucze litery i pamiętające występujące w zapytaniach słowa. To podejście daje dużą elastyczność np. przy naprawie błędnie zapisanych słów, gdyż te obsługuje osobne drzewo. Obecna implementacja przewiduje szukanie wyłącznie zapytania po nadłuższym prefixie.

## Testy

Do zadania napisano proste testy zawierające przykładowy input i oczekiwany output. Testy mają za zadanie sprawdzić czy program prawidłowo radzi sobie z obsługą dobrych oraz błędnych zapytań.

---
# Novomatic Task 1

## Search Engine
The goal of this task is to implement a simple search engine. Its basic functionalities are: adding a new query and searching for the query most closely matching a given prefix. Example program behavior:
```
> add: When is the New Year in China?
> add: When is the New Year in Thailand?
> ask: When is the New Year
result: When is the New Year in China?
result: When is the New Year in Thailand?
```

## Implementation
The solution is based on two Trie (prefix tree) data structures: one that stores complete words as keys and keeps the structure of queries, and another that stores characters as keys and remembers individual words used in queries. This approach provides high flexibility, for example, for handling misspelled words, since those are managed by a separate Trie. The current implementation supports searching only by the longest matching prefix.

## Tests
Simple tests have been written for this task using sample input and expected output. The tests verify whether the program handles both valid and invalid queries correctly.