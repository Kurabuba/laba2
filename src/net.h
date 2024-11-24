#ifndef NET_H
#define NET_H
#include <stdio.h>

#define MAX_LENGTH 50 //максимальная длинна текста

// Структура для хранения информации
typedef struct Film {
   	char name[MAX_LENGTH];
    	int year;
    	char country[MAX_LENGTH];
	float rating;
    	struct Film* next; // Указатель на следующий узел
} Film;

// Структура для списка фильмов
typedef struct FilmList{
   	Film* first;
    	Film* last;
} FilmList;

// Функцияи
void input(Film* film);
void addF(FilmList* list, int t);
void removeF(FilmList* list, char* name);
void find(FilmList* list, char* name, int year);
void print(FilmList* list);
void edit(FilmList* list, char* name);
void save(const char* filename, FilmList* list);
void load(char* filename, FilmList* list);
#endif 
