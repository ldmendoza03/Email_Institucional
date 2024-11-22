/*
 * Universidad de las Fuerzas Armadas "ESPE"
 * Enunciado: Creacion de Correo a partir de Nombres y Apellidos
 * Autor: Leandro Mendoza
 * Fecha de Creación: 20 de Noviembre del 2024
 * Fecha de Modificación: 21 de Noviembre del 2024
 * NRC: 1978
 * Curso: Estructura de Datos
 * Docente: Edgar Solis
 */

#ifndef EMAILLIST_H
#define EMAILLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

template <typename T>
struct Nodo {
    T* data;
    Nodo* next;
};

template <typename T>
struct EmailList {
    Nodo<T>* head;
};

template <typename T>
void initEmailList(EmailList<T>* list) {
    list->head = NULL;
}

template <typename T>
int emailExists(const char* email, const EmailList<T>* list) {
    Nodo<T>* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, email) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

template <typename T>
char* generateEmail(const char* nombre1, const char* nombre2, const char* apellido, int count, EmailList<T>* list) {
    size_t length = strlen(apellido) + 20; // Espacio para iniciales y contador
    char* email = (char*)malloc(length);
    if (email == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        exit(1);
    }

    if (count == 0) {
        snprintf(email, length, "%c%c%s@espe.edu.ec",
                 tolower(nombre1[0]), tolower(nombre2[0]), apellido);
    } else {
        snprintf(email, length, "%c%c%s%d@espe.edu.ec",
                 tolower(nombre1[0]), tolower(nombre2[0]), apellido, count);
    }

    for (char* p = email; *p; ++p) {
        *p = tolower(*p);
    }

    if (emailExists(email, list)) {
        free(email);
        return generateEmail(nombre1, nombre2, apellido, count + 1, list);
    }

    return email;
}

template <typename T>
void addEmailRecursive(Nodo<T>** node, const char* nombre1, const char* nombre2, const char* apellido, int count, EmailList<T>* list) {
    if (*node == NULL) {
        char* email = generateEmail(nombre1, nombre2, apellido, count, list);
        *node = (Nodo<T>*)malloc(sizeof(Nodo<T>));
        if (*node == NULL) {
            printf("Error: No se pudo asignar memoria.\n");
            exit(1);
        }
        (*node)->data = email;
        (*node)->next = NULL;
    } else {
        addEmailRecursive(&((*node)->next), nombre1, nombre2, apellido, count, list);
    }
}

template <typename T>
void addEmail(EmailList<T>* list, const char* nombre1, const char* nombre2, const char* apellido) {
    addEmailRecursive(&(list->head), nombre1, nombre2, apellido, 0, list);
}

template <typename T>
void showEmails(const EmailList<T>* list) {
    Nodo<T>* current = list->head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

template <typename T>
void destroyEmailList(EmailList<T>* list) {
    Nodo<T>* current = list->head;
    while (current != NULL) {
        Nodo<T>* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

#endif
