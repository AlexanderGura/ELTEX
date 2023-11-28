#ifndef CONTACT_H_
#define CONTACT_H_

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

#endif
