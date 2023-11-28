#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "contact.h"
#include "list.h"

int main()
{
    char BUFFER[BUFFER_SIZE], BUFFER1[BUFFER_SIZE], operation;
    int BUFFINT, BUFFINT2, whatdo, index = 0;
    List* listContact = createList();

    Contact* cont = createContact(index++,"Ivan","Ivanov");

    inserting(listContact, cont);
    printOneContactAllInfo(cont);
    updateContact(cont, "Студент", 'e');
    updateContact(cont, "Вуз", 'd');
    updateContact(cont, "vk.com/id01010101", 'j');
    updateContact(cont, "123@hotmail.ru", 'g');
    updateContact(cont, "123@gmail.ru", 'g');
    updateContact(cont, "123@mail.ru", 'g');
    updateContact(cont, "+79876543210", 'f');
    updateContact(cont, "+79123456789", 'f');

    cont = createContact(index++,"Naruto","Udzumake");
    inserting(listContact, cont);
    updateContact(cont, "Студент", 'e');
    updateContact(cont, "ВУЗ", 'd');
    updateContact(cont, "vk.com", 'j');
    updateContact(cont, "@anime", 'k');
    updateContact(cont, "+79834561665", 'f');
    updateContact(cont, "+79834561665", 'f');
    updateContact(cont, "456@mail.ru", 'g');

    cont = createContact(index++,"Kirill", "Temnikov");
    inserting(listContact, cont);
    updateContact(cont, "88005553535", 'f');
    updateContact(cont, "reclama@adddd.ru", 'g');

    inserting(listContact, createContact(4,"Bulat", "Okudjava"));
    inserting(listContact, createContact(5,"Aang", "Avatar"));
    inserting(listContact, createContact(6,"Zarina", "Temnikova"));

    changeContactName(listContact, 1, "Artem");
    printListSmall(listContact);

    while(1) {
        system("clear");
        fflush(stdin);
        printf("Список контактов:\n");
        printf("%s\t%-15s\t%-10s\t%-10s\t%-10s\n","ID","|Имя","|Фамилия","|Телефон","|Эл.почта\n");
        printListSmall(listContact);
        printf("Текушее количество контактов: %d\n",listContact->size);    
        printf("Выбери действие:\n");
        printf("1 - Создать новый контакт\n"
        "2 - Удалить контакт\n"
        "3 - Обновить контакт\n"
        "4 - Вывести полную информацию о контактах\n"
        "5 - Обновить индексацию контактов\n"
        "6 - Выйти\n");
        scanf("%d", &whatdo);

        switch(whatdo){
            case 1:
                printf("Введите имя и фамилию:\n");
                scanf("%s %s", BUFFER,BUFFER1);
                inserting(listContact, createContact(index++,BUFFER, BUFFER1));
		index = updateIndexContact(listContact);
                break;
            case 2:
                printf("ВведитеID удаляемого контакта:\n");
                scanf("%d", &BUFFINT);
                deleteContact(listContact, BUFFINT);
                if(listContact->size > 0)
                index = updateIndexContact(listContact);
                break;
            case 3:
                printf("Введите ID обновляемого контакта:\n");
                scanf("%d", &BUFFINT);
                if(BUFFINT > listContact->size-1) break;
                cont = getContact(listContact ,BUFFINT);
		if(!cont) break;
                printf("ID\t|Имя(a)\t|Фамилия(b)\t|Отчество(c)\t|Место_работы(d)\t|Должность(e)\t|Телефон(f)\t|Эл.почта(g)\t|Соцсеть(j)\t|Мессенджер(k) |\n");
                printOneContactAllInfo(cont);
                printf("Введите, что вы хотите обновить (введите один символ который указан после нужного поля)\n");
                scanf("%c", &operation);
                while(operation=='\n') scanf("%c", &operation);
                if(operation == 'f' || operation == 'g' || operation == 'j' || operation == 'k'){
                    printf("Вы хотите перезаписать или добавить ещё одно значение? (1 - перезаписать; 0 - добавить)\n");
                    scanf("%d", &BUFFINT2);
                    if(BUFFINT2){
                        printf("Введите номер изменяемого поля (Самое первое поле имеет номер 0)\n");
                        scanf("%d", &BUFFINT2);
                        printf("Введите новое значение поля:\n");
                        scanf("%s", BUFFER);
                        updateValueForArray(cont, BUFFER, operation, BUFFINT2);
                        break;
                    }
                }
                printf("Введите новое значение поля:\n");
                scanf("%s", BUFFER);
                if(operation == 'a') changeContactName(listContact, BUFFINT,BUFFER);
                else updateContact(cont, BUFFER, operation);
                cont = NULL;
                break;
            case 4:
                printf("%s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "ID", "|Имя","|Фамилия","|Отчество","|Место_работы","|Должность",
                "|Телефон","|Эл.почта","|Соцсеть", "|Мессенджер\n");
                printList(listContact);
                getc(stdin);
                printf("\n.....Нажмите Enter.....\n");
                getc(stdin);
                break;
            case 5:
                index = updateIndexContact(listContact);
                break;
            case 6:
                deleteList(&listContact);
                return 0;
                break;
            default:
                break;
        }
    }
}
