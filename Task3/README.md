# Novomatic Zadanie 3
#### English version below

## Operacja Binarna
Zadanie ma na celu implementację funkcji, która n-krotnie zaaplikuje na argumencie operację binarną 'f'. Szablon tej funkcji został podany w poleceniu:
```c++
template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation)
{
    { operation(first, second) } -> std::convertible_to<T>;
    { T::identity() } -> std::convertible_to<T>;
};
template <class BinaryOp, class ValueType>
    requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp& f);
```

## Implementacja

Implementacje rozwiązania wykonano w pliku Binary.hpp natomiast do jej testów stworzono również klasę FloatType wraz z jej klasami pochodnymi FloatTypeI0 gdzie Identity było równe 0 oraz FloatTypeI1 gdzie Identity było równe 1.

## Testy

Do zadania napisano proste testy z klasami FloatTypeI1 oraz FloatTypeI0 na operacjach dodawania floatów i mnożenia ich przez siebie (potęgowania).

---
# Novomatic Task 3

## Binary Operation
The goal of this task is to implement a function that applies a binary operation f to a given argument n times. The template for this function was provided in the assignment:
```c++
template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation)
{
    { operation(first, second) } -> std::convertible_to<T>;
    { T::identity() } -> std::convertible_to<T>;
};
template <class BinaryOp, class ValueType>
    requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp& f);
```

## Implementation
The implementation is provided in the Binary.hpp file. For testing purposes, a FloatType class was created along with two derived classes: FloatTypeI0, where the identity is 0, and FloatTypeI1, where the identity is 1.

## Tests
Simple tests were written using the FloatTypeI1 and FloatTypeI0 classes, covering operations such as float addition and multiplication (exponentiation).