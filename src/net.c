#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"

// функция для получения информации
void input(Film* film){
	printf("Введите название фильма Netflix (1 слово): ");
	scanf("%s", film->name);
	while (1){
		printf("Введите год: ");
		if(scanf("%i", &film->year)==1)
			break;
		else {
			printf("Введите корректное число\n");	
			while(getchar() != '\n');}}

	printf("Введите страну: ");
	scanf("%s", film->country);
	while (1){
    		printf("Введите рейтинг (0-10):  ");
    		if(scanf("%f", &film->rating)==1)
			if(film->rating>=0&&film->rating<=10) 
        			break;
   	 	else { 
        		printf("Введите корректное число\n");
        		while(getchar() != '\n');}
	}
}

// Функция для добавления фильма 
void addF(FilmList* list, int t) {
	Film* new_film = malloc(sizeof(Film)); //выделяем память
    	if (new_film == NULL) { //проверка на успех
        	return ;
    }    
	if(t)
    		input(new_film);

    	new_film->next = NULL;

    	if (list->first == NULL) {//если список пустой, new_film становится первым и последним
        	list->first = new_film;
        	list->last = new_film;}
    	else {
        	list->last->next = new_film;
        	list->last = new_film;}//добавляем в конец
}

// Функция для удаления фильма по названию
void removeF(FilmList* list, char* name) {
    	Film* cur = list->first;
    	Film* prev = NULL;//начинаем с первого. Указатель на предыдущий

    	while (cur != NULL) {
        	if (strcmp(cur->name, name) == 0) {
            		if (prev == NULL) {
                		list->first = cur->next;// Удаляем первый элемент
            		} else {
                		prev->next = cur->next; // пропускаем элемент
            }

            	if (cur == list->last) {
                	list->last = prev; //удаляем последний элемент
            }

            	free(cur);
            	printf("Фильм %s удален.\n", name);
            	return ;
        }       
		prev = cur;
		cur = cur->next;//переход к следующему элементу 
    }
    printf("Фильм %s не найден.\n", name);
}


// Функция для поиска фильма по названию и году 
void find(FilmList* list, char* name, int year) {
    	Film* cur = list->first;
	int bul = 0;
   	 while (cur != NULL) {
		if ((strcmp(cur->name, name) == 0)&&(cur->year == year)){
			printf("Найдено: %s, Год: %i, Страна: %s, Рейтинг: %.1f\n", cur->name, cur->year, cur->country, cur->rating);
			bul = 1;}
       		else if ((strcmp(cur->name, name) == 0)||(cur->year == year)) { //проверка по названию и году 
            		printf("Cовпадение по названию или году: %s, Год: %i, Страна: %s, Рейтинг: %.1f\n", cur->name, cur->year, cur->country, cur->rating);
        		bul =1; }
        	cur = cur->next;
    }
	if(!bul){
    		printf("Фильм %s за %i год не найден.\n", name, year);
		return ;}
}


// Функция для вывода списка 
void print(FilmList* list) {
	Film* cur = list->first;
    	if (cur == NULL) {
        	printf("Список фильмов пуст.\n");
        	return;
    	}

    	printf("\nСписок фильмов Netflix:\n");
    	while (cur != NULL) {
        	printf("Название: %s, Год: %i, Страна: %s, Рейтинг: %.1f\n", cur->name, cur->year, cur->country, cur->rating);
        	cur = cur->next;
    	}
}

// Функция для изменения значений 
void edit(FilmList* list, char* name) {
    	Film* cur = list->first;
    	while (cur != NULL) {
        	if (strcmp(cur->name, name) == 0) {
            		printf("Редактирование фильма %s:\n", name);
            		input(cur); 
            		return;
        	}
        	cur = cur->next;
    	}
    	printf("Фильм %s не найден.\n", name);
}

// Функция для сохранения в файл
void save(const char* filename, FilmList* list) {
    	FILE* file = fopen(filename, "w");
    	if (file == NULL) {
        	return;
    	}
    	Film* cur = list->first;
    	while (cur != NULL) {
        	fprintf(file, "%s,%i,%s,%.1f\n", cur->name, cur->year, cur->country, cur->rating);
        	cur = cur->next;
    	}
	
    	fclose(file);
}

// Функция для загрузки
void load(char* filename, FilmList* list) {
    	FILE* file = fopen(filename, "r");
    	if (file == NULL) {
         	return;
    	}
    	char buffer[256];
    	while (fgets(buffer, sizeof(buffer), file) != NULL) {
        	Film film;//временная переменная для хранения инфы о фильме
        	buffer[strcspn(buffer, "\n")] = 0; // Убираем символ новой строки
        	sscanf(buffer, "%49[^,],%i,%49[^,],%f", film.name, &film.year, film.country, &film.rating);
        	addF(list, 0); // Добавление
        	memcpy(list->last, &film, sizeof(Film)); // Копируем данные в последний фильм
        	list->last->next = NULL; 
    	}
    	fclose(file);
}








