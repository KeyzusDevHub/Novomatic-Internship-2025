# Novomatic Zadanie 2
#### English version below

## Kolizja trójkątów
Zadanie ma na celu zaimplementowanie metody do sprawdzenia czy dwa trójkąty są ze sobą w kolizji. Zadanie to dodatkowo ma zwizualizować cały proces i sygnalizować użytkownikowi jeżeli kolizja zajdzie. Innym ważnym punktem było to, żeby choć jednym z trójkątów dało się sterować.

## Implementacja

Implementacja oparta jest o OpenGL. Do zadania użyto zasugerowanej w poleceniu struktury vec2 oraz triangle wraz z rozszerzeniem klasy triangle o konstruktory oraz przesunięcie na ekranie i rotację. Tylko główny poruszający się po ekranie trójkąt ma sygnalizowaną kolizję poprzez zmianę koloru (brak kolizji: zielony, kolizja: czerwony). Pozostałe statyczne trójkąty są porozrzucane po 4 krawędziach ekranu i są zawsze koloru niebieskiego. 

## Testy

Do zadania napisano testy wyłącznie dla funkcji isColliding. Testy przeprowadzono na trójkątach które stykają się w wielu punktach w jednym punkcie lub nie stykają się wcale, a także dodano testy na kolizję przy wielu trójkątach z których każdy mógł być z innym w kolizji.

---
# Novomatic Task 2

## Triangle Collision
The goal of this task is to implement a method to detect whether two triangles are colliding. Additionally, the task aims to visualize the entire process and notify the user when a collision occurs. Another important requirement was to allow at least one of the triangles to be controllable.

## Implementation
The implementation is based on OpenGL. The task uses the vec2 and triangle structures suggested in the assignment, with the triangle class extended to include constructors as well as methods for on-screen translation and rotation. Only the main triangle, which can be moved around the screen, changes its color to indicate a collision (green for no collision, red for collision). The remaining static triangles are placed along the four edges of the screen and are always blue.

## Tests
Tests were written exclusively for the isColliding function. The tests cover cases where triangles touch at multiple points, at a single point, or do not touch at all. Additional tests check for collisions involving multiple triangles, each of which could potentially collide with another.