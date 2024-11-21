#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> // Para write

typedef struct {
    const char *expr;
    int pos;
} Parser;

// Prototipos de funciones
int parse_expr(Parser *p);
int parse_term(Parser *p);
int parse_factor(Parser *p);
void unexpected_token(Parser *p);

// Función principal
int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Usage: ./vbc <expression>\n", 26);
        return 1;
    }

    Parser p = {argv[1], 0};

    int result = parse_expr(&p);

    // Verificar si hay tokens adicionales
    if (p.expr[p.pos] != '\0') {
        unexpected_token(&p);
    }

    printf("%d\n", result);
    return 0;
}

// Función para procesar expresiones (maneja '+' entre términos)
int parse_expr(Parser *p) {
    int result = parse_term(p);

    while (p->expr[p->pos] == '+') {
        p->pos++;
        result += parse_term(p);
    }

    return result;
}

// Función para procesar términos (maneja '*' entre factores)
int parse_term(Parser *p) {
    int result = parse_factor(p);

    while (p->expr[p->pos] == '*') {
        p->pos++;
        result *= parse_factor(p);
    }

    return result;
}

// Función para procesar factores (maneja números y paréntesis)
int parse_factor(Parser *p) {
    if (p->expr[p->pos] == '(') 
    {
        p->pos++; // Saltar '('
        int result = parse_expr(p);
        if (p->expr[p->pos] != ')')
            unexpected_token(p);
        p->pos++; // Saltar ')'
        return result;
    } else if (isdigit(p->expr[p->pos])) {
        return p->expr[p->pos++] - '0'; // Convertir carácter a número
    } else {
        unexpected_token(p);
    }

    return 0; // Nunca debería llegar aquí
}

// Manejo de errores
void unexpected_token(Parser *p) {
    
	if (p->expr[p->pos] == '\0') {
        write(2, "Unexpected end of input\n", 24);
    } else {
        //char buffer[50];
        //int len =
		write(2, "Unexpected token '", 18);
		write(2, &p->expr[p->pos], 1);
		write(2, "'\n", 2);
		//printf("Unexpected token '%c'\n", p->expr[p->pos]);
        //write(2, buffer, len);
    }
    exit(1);
}
