#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class bigint {
private:
    std::string value; // Almacena los dígitos del número en una cadena.
    void remove_leading_zeros(); // Método auxiliar para eliminar ceros iniciales.

public:
    // Constructores
    bigint();                   // Constructor por defecto (0).
    bigint(const std::string &str); // Constructor desde string.
    bigint(unsigned long long num); // Constructor desde entero.
    bigint(const bigint &other); // Constructor de copia.

    // Operadores aritméticos
    bigint operator+(const bigint &other) const;
    bigint& operator+=(const bigint &other);
	bigint operator-(const bigint &other) const;

    // Operadores de desplazamiento de dígitos
    bigint operator<<(size_t shift) const;
    bigint& operator<<=(size_t shift);
    bigint operator>>(size_t shift) const;
    bigint& operator>>=(size_t shift);

    // Operadores de comparación
    bool operator<(const bigint &other) const;
    bool operator>(const bigint &other) const;
    bool operator<=(const bigint &other) const;
    bool operator>=(const bigint &other) const;
    bool operator==(const bigint &other) const;
    bool operator!=(const bigint &other) const;

    // Operadores de incremento
    bigint& operator++();   // Preincremento.
    bigint operator++(int); // Postincremento.

    // Operador de impresión
    friend std::ostream& operator<<(std::ostream &os, const bigint &num);
};

#endif // BIGINT_HPP
