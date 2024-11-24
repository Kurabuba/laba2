#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"

// Главная функция
int main() {

FilmList list = {NULL, NULL};
load("movies.txt", &list);
int choice;//для выбора
char title[MAX_LENGTH];//для названия

do {
	printf("\nВыберите действие:\n");
        printf("1. Добавить фильм\n");
        printf("2. Удалить фильм\n");
        printf("3. Найти фильм\n");
        printf("4. Вывести список фильмов\n");
        printf("5. Изменить данные о фильме\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%i", &choice);
	printf("\n");
	
switch (choice) {
	case 1:
		addF(&list, 1);
		save("movies.txt", &list);
		print(&list);
               	break;
	case 2:
                printf("Введите название фильма для удаления: ");
                scanf("%s", title);
                removeF(&list, title);
		save("movies.txt", &list);
		print(&list);
                break;
	case 3:
                printf("Введите название фильма для поиска: ");
                scanf("%s", title);
                int year;
                printf("Введите год: ");
                scanf("%i", &year);
                find(&list, title, year);
                break;
	case 4:
                print(&list);
                break;
	case 5:
               printf("Введите название фильма для редактирования: ");
               scanf("%s", title);
               edit(&list, title);
	       save("movies.txt", &list);
	       print(&list);
               break;
	case 0:
               break;
        default:
               printf("Неверный выбор. Попробуйте снова.\n");
               break;
	}
        
} while (choice != 0);

// Освобождение памяти перед выходом
Film* cur = list.first;
while (cur != NULL) {
	Film* next1 = cur->next;
	free(cur);
        cur = next1;
    }

    return 0;
}
