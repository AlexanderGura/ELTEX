#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN_NAME 30
#define LEN_WORK 70
#define COUNT_OF_PHONE 100
#define LEN_PHONE 15
#define COUNT_OF_EMAIL 10
#define LEN_EMAIL 250
#define LEN_LINK 200
#define COUNT_OF_SOCIAL_NETWORK 10
#define LEN_MESSENGER 25
#define COUNT_OF_MESSENGER 15
#define MAX_SIZE 250
#define BUFFER_SIZE 1024

typedef struct Contact{
    int id;
    char firstName[LEN_NAME];
    char lastName[LEN_NAME];
    char fatherName[LEN_NAME];
    char placeOfWork[LEN_WORK];
    char jobTitle[LEN_WORK];
    char phoneNumbers[COUNT_OF_PHONE][LEN_PHONE];
    char emails[COUNT_OF_EMAIL][LEN_EMAIL];
    char linksToSocialNetwork[COUNT_OF_SOCIAL_NETWORK][LEN_LINK];
    char messengers[COUNT_OF_MESSENGER][LEN_MESSENGER];

} Contact;

int equal(Contact*, Contact*);
Contact* createContact(int, char*, char*);
int updateContact(Contact*, char*, char);
int updateValueForArray(Contact*, char*, char, int);
void printOneContactAllInfo(Contact*);
void printOneContactSmallInfo(Contact*);


int equal(Contact *con1, Contact * con2){
    return strcmp(con1->firstName, con2->firstName);
}

Contact* createContact(int id, char* name, char* lastname){
    Contact* contact = (Contact*)malloc(sizeof(Contact));
    if(!contact) return contact;
    strncpy(contact->firstName, name, LEN_NAME);
    strncpy(contact->lastName, lastname, LEN_NAME);
    memset(contact->fatherName, 0, LEN_NAME);
    memset(contact->placeOfWork, 0, LEN_WORK);
    memset(contact->jobTitle, 0, LEN_WORK);
    memset(contact->phoneNumbers[0], 0, LEN_PHONE*COUNT_OF_PHONE);
    memset(contact->emails[0], 0, LEN_EMAIL*COUNT_OF_EMAIL);
    memset(contact->linksToSocialNetwork[0], 0, LEN_LINK*COUNT_OF_SOCIAL_NETWORK);
    memset(contact->messengers[0], 0, LEN_MESSENGER*COUNT_OF_MESSENGER);

    contact->id = id;
    return contact;
}

int updateContact(Contact* contact, char* str, char whatUpdate){
    if(!contact) return -12;
    int countNotNull = 0;
    if(whatUpdate == 'a'){
        strncpy(contact->firstName, str, LEN_NAME);
    } else if(whatUpdate == 'b'){
        strncpy(contact->lastName, str, LEN_NAME);
    } else if(whatUpdate == 'c'){
        strncpy(contact->fatherName, str, LEN_NAME);
    } else if(whatUpdate == 'd'){
        strncpy(contact->placeOfWork, str, LEN_WORK);
    } else if(whatUpdate == 'e'){
        strncpy(contact->jobTitle, str, LEN_WORK);
    } else if(whatUpdate == 'f'){
        for(; strlen(contact->phoneNumbers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_PHONE-1) return -2;
        strncpy(contact->phoneNumbers[countNotNull], str, LEN_PHONE);
    } else if(whatUpdate == 'g'){
        for(; strlen(contact->emails[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_EMAIL-1) return -3;
        strncpy(contact->emails[countNotNull], str, LEN_EMAIL);
    } else if(whatUpdate = 'j'){
        for(; strlen(contact->linksToSocialNetwork[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_SOCIAL_NETWORK-1) return -4;
        strncpy(contact->linksToSocialNetwork[countNotNull], str, LEN_LINK);
    } else if(whatUpdate == 'k'){
        for(; strlen(contact->messengers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_MESSENGER-1) return -5;
        strncpy(contact->messengers[countNotNull], str, LEN_MESSENGER);
    }else return -1;
    return 0;
}

int updateValueForArray(Contact* contact, char* str, char whatUpdate, int num_change){
    if(!contact) return -12;
    int countNotNull = 0;
    if(whatUpdate == 'f'){
        for(; strlen(contact->phoneNumbers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_PHONE-1 || num_change >= countNotNull) return -2;
        strncpy(contact->phoneNumbers[num_change], str, LEN_PHONE);
    }else if(whatUpdate == 'g'){
        for(; strlen(contact->emails[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_EMAIL-1 || num_change >= countNotNull) return -3;
        strncpy(contact->emails[num_change], str, LEN_EMAIL);
    } else if(whatUpdate == 'j'){
        for(; strlen(contact->linksToSocialNetwork[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_SOCIAL_NETWORK-1|| num_change >= countNotNull) return -4;
        strncpy(contact->linksToSocialNetwork[num_change], str, LEN_LINK);
    } else if(whatUpdate == 'k'){
        for(; strlen(contact->messengers[countNotNull])!=0; countNotNull++);
        if(countNotNull>=COUNT_OF_MESSENGER-1 || num_change >= countNotNull) return -5;
        strncpy(contact->messengers[num_change], str, LEN_MESSENGER);
    }
    return 0;
}

void printOneContactAllInfo(Contact* contact){
    if(!contact) return;
    int countNotNull = 1;
    printf("%d\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", contact->id,
        contact->firstName, contact->lastName, contact->fatherName,
        contact->placeOfWork, contact->jobTitle,
        contact->phoneNumbers[0], contact->emails[0],
        contact->linksToSocialNetwork[0], contact->messengers[0]);
        for(; strlen(contact->messengers[countNotNull])!=0 || strlen(contact->phoneNumbers[countNotNull])!=0 || strlen(contact->linksToSocialNetwork[countNotNull]) !=0 || strlen(contact->emails[countNotNull])!=0; countNotNull++) 
            printf("\t\t\t\t\t\t\t\t\t%d. %-15s\t%-10s\t%-10s\t%-10s\n", countNotNull, 
            contact->phoneNumbers[countNotNull], contact->emails[countNotNull],
            contact->linksToSocialNetwork[countNotNull], contact->messengers[countNotNull]);
}

void printOneContactSmallInfo(Contact* contact){
    if(!contact) return;
    printf("%d\t%-10s\t%-10s\t%-10s\t%-10s\n", contact->id,
        contact->firstName, contact->lastName,
        contact->phoneNumbers[0], contact->emails[0]);
}


typedef struct Node{
    struct Contact* contact;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List{
    unsigned int size;
    struct Node* head;
    struct Node* last;
} List;

List* createList();
int insert(List *, Contact*);
List* fromArray(Contact*, int, int);
void deleteList(List *);
int printList(List **);
int printListSmall(List *);
int swapContact(Node*, Node*);
int inserting(List *, Contact*);
int deleteContact(List* , int);
int changeContactName(List*, int, char*);
Contact* _deleteNodeSaveCont(List*, int);
Contact* getContact(List* list, int index);
int updateIndexContact(List* list);

List* createList(){         // создать структуру список
    List* list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->last = NULL;
    return list;
}
Contact* getContact(List* list, int index) {        // найти контакт с определённым индексом
    Node *tmp = list->head;
 
    while (tmp && tmp->contact->id != index) {
        tmp = tmp->next;
    }
    if(!tmp) return NULL;
    return tmp->contact;
}


int deleteContact(List* list, int index) {        // удаление контакта с определённым индексом.
    Node *tmp = list->head;
    
    while (tmp && tmp->contact->id != index) {
        tmp = tmp->next;
    }
    if (!tmp) return -1;
    if(tmp == list->head){
        list->head = tmp->next;
        if(tmp->next)
        tmp->next->prev = NULL;
    } else if (tmp == list->last) {
        list->last = tmp->prev;
        if(tmp->prev)
        tmp->prev->next = NULL;
    }else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    } 
    if(!tmp->prev && !tmp->next) {list->last = NULL; list->head = NULL;}
    free(tmp->contact);
    free(tmp);
    list->size--;
    return 0;
}

Contact* _deleteNodeSaveCont(List* list, int index) {        // удаление ноды является вспомогательной функцией
    Node *tmp = list->head;
    Contact* tmpCon;
    while (tmp && tmp->contact->id != index) {
        tmp = tmp->next;
    }
    if (!tmp) return NULL;
    if(tmp == list->head){
        list->head = tmp->next;
        tmp->next->prev = NULL;
    } else if (tmp == list->last) {
        list->last = tmp->prev;
        tmp->prev->next = NULL;
    }else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }  
    tmpCon = tmp->contact;
    free(tmp);
    list->size--;
    return tmpCon;
}

int swapContact(Node* node1, Node* node2){      // перебрасывание указателя на конакт с одной ноды на другую
    if(!node1 || !node2) return -1;
    Contact* tmp = node1->contact;
    node1->contact = node2->contact;
    node2->contact = tmp;
    return 0;
}

int inserting(List * list, Contact* con){           // вставка элементов в список, во время вставки ищется подходящее место для элемента
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) exit(1);
    tmp->contact = con;
    tmp->next = NULL;
    tmp->prev = NULL;
    Node* next = list->head;
    Node* prev = NULL;
    if(next == NULL) list->head = tmp;
    if (list->last == NULL) {           // обработка ситуации, когда список пуст
        list->last = tmp;
        list->size++;
        return 0;
    }
    while(equal(tmp->contact, next->contact)>=0 && next != NULL){   // пока разница между контактами больше нуля идём по циклу
        prev = next;
        next = next->next;
        if(!next) break;
    }
    if(next == NULL){
        list->last = tmp;
        tmp->prev = prev;
        prev->next = tmp;
    }else if (prev == NULL){
        list->head = tmp;
        tmp->next = next;
        next->prev = tmp;
    }else{
        tmp->next = next;
        tmp->prev = prev;
        prev->next = tmp;
        next->prev = tmp;
    }

    list->size++;
}

int insert(List * list, Contact* con){          // вставка в начало (не используется)
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) exit(1);
    tmp->contact = con;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->last == NULL) {
        list->last = tmp;
    }
    //while(equal(tmp->contact))
    list->size++;
}

int printList(List ** list){         
    Node* tmp = list->head;

    while(tmp){
        printOneContactAllInfo(tmp->contact);
        tmp=tmp->next;
    }
}

int printListSmall(List * list){         
    Node* tmp = list->head;

    while(tmp){
        printOneContactSmallInfo(tmp->contact);
        tmp=tmp->next;
    }
}

void deleteList(List * list){
    Node* tmp = (*list)->head;
    Node* next = NULL;
    while(tmp){
        next = tmp->next;
        free(tmp->contact);
        free(tmp);
        tmp = next;
    }
    (*list) = NULL;
}

int changeContactName(List* list, int index, char* name) {
    Contact* tmpCon = _deleteNodeSaveCont(list, index);
    updateContact(tmpCon, name, 'a');
    inserting(list, tmpCon);
}

int updateIndexContact(List* list){
    Node* tmp = list->head;
    int index = 0;
    while(tmp){
        tmp->contact->id = index;
        index++;
        tmp=tmp->next;
    }
    return index;
}


int main()
{
    char BUFFER[BUFFER_SIZE], BUFFER11[BUFFER_SIZE], operation;
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
            case 6:
                deleteList(&listContact);
                return 0;
                break; 
            default:
                
        }
    }
}