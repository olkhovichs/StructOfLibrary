#include <stdio.h>
#include <stdlib.h>

struct author
{
    char surname[15];
    char title[10];
    char publishing[10];
    int year;
    char subject[10];
};

typedef struct author DataType;

struct List
{
    DataType data;
    struct List* next;
};

typedef struct List* list;

DataType input_author(void);
list read_file(char* filename, list begin);
list add(list begin, DataType author);
void write_file(char* filename, list begin);
void delete_list(list begin);
void show(list);
void year(list begin);
list del(list);

int main(void)
{
    char file[50];
    char menu;
    list author = NULL;
    puts("Enter the file name");
    gets(file);
    author = read_file(file, author);
    do
    {
        system("CLS");
        puts("1. Add");
        puts("2. Show");
        puts("3. Year");
        puts("4. Delete record");
        puts("5. Exit");
        menu = getchar();
        switch (menu)
        {
        case '1': author = add(author, input_author()); break;
        case '2': show(author); break;
        case '3': year(author); break;
        case '4': author = del(author);
        }
    } while (menu != '5');
    getchar();
    puts("Enter the file name");
    gets(file);
    write_file(file, author);
    delete_list(author);
    return 0;
}

DataType input_author(void)
{
    DataType author;
    getchar();
    puts("Surname");
    gets(author.surname);
    puts("Title");
    gets(author.title);
    puts("Publishing");
    gets(author.publishing);
    puts("Subject");
    gets(author.subject);
    puts("Year");
    scanf("%d", &author.year);

    return author;
}

list add(list begin, DataType author)
{
    list temp;
    if (begin == NULL)
    {
        begin = (list)malloc(sizeof(struct List));
        temp = begin;
    }
    else
    {
        temp = begin;
        while (temp->next) temp = temp->next;
        temp->next = (list)malloc(sizeof(struct List));
        temp = temp->next;
    }
    temp->data = author;
    temp->next = NULL;
    return begin;
}

list read_file(char* filename, list begin)
{
    FILE* f;
    DataType author;
    if ((f = fopen(filename, "rb")) == NULL)
    {
        perror("Error open file");
        //  getch();
        return begin;
    }
    while (fread(&author, sizeof(author), 1, f))
        begin = add(begin, author);
    fclose(f);
    return begin;
}

void delete_list(list begin)
{
    list temp = begin;
    while (temp)
    {
        begin = temp->next;
        free(temp);
        temp = begin;
    }
}

void write_file(char* filename, list begin)
{
    FILE* f;
    if ((f = fopen(filename, "wb")) == NULL)
    {
        perror("Error create file");
        system("pause");
        return;
    }
    while (begin)
    {
        fwrite(&begin->data, sizeof(DataType), 1, f);
        begin = begin->next;
    }
}

void print1(list pos)
{
    printf("%s\nSurname : %s\nTitle : %s\nPublishing : %s\nSubject : %d\nyear : %.2f\n", pos->data.surname,
        pos->data.title, pos->data.publishing, pos->data.subject, pos->data.year);
}

/*void print2 (list pos)
 {
 printf ("Title : %s\n", pos->data.title);
 }
 */
void show(list begin)
{
    int k = 0;
    system("CLS");
    if (begin == NULL)
    {
        puts("List is empty");
        system("pause");
        return;
    }
    puts("|Number |    Surname     |    Title   |Publishing |  Subject  | Year|");
    puts("-------------------------------------------------------------------------------");
    while (begin)
    {
        printf("|%6d |%15s | %10s |%10s |%10s |%4d |\n", ++k, begin->data.surname,
            begin->data.title, begin->data.publishing, begin->data.subject, begin->data.year);
        begin = begin->next;
    }
    puts("--------------------------------------------------------------------------------");
    system("pause");
}

void year(list begin)
{
    char surname[15];
    int year, k = -1;
    list pos;
    system("CLS");
    if (!begin) // если список пуст
    {
        puts("List is empty");
        system("pause");
        return;
    }
    getchar();
    puts("Surname?");
    scanf("%c", &surname);
    while (begin) //пока в списке есть эл-ты
    {
        k++;
        if (begin->data.surname == surname && begin->data.year > 2000)
        {
            year = begin->data.year;
            pos = begin;
        }
        begin = begin->next; // переставляем указатель на след эл-т
        //        free (temp); // удаляем первый
    }
    if (year <= 0 || year >= 2020) puts("No");
    else printf("Title : %s\n", pos->data.title);
    system("pause");
}


list del(list begin)
{
    int n, k = 1;
    char yes;
    list temp, temp1;
    system("CLS");
    if (begin == NULL)
    {
        puts("List is empty");
        system("pause");
        return NULL;
    }
    puts("Number record for delete?");
    scanf("%d", &n);
    if (n < 1)
    {
        puts("Error");
        system("pause");
        return begin;
    }
    if (n == 1)
    {
        print1(begin);
        puts("Delete? (y/n)");
        do
            yes = getchar();
        while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
        if (yes == 'y' || yes == 'Y')
        {
            temp = begin->next;
            free(begin);
            return temp;
        }
        else return begin;
    }
    if (begin->next == NULL && n > 1)
    {
        puts("Error");
        system("pause");
        return begin;
    }
    temp = begin;
    temp1 = temp->next;
    while (temp1->next && k < n - 1)
    {
        temp = temp1;
        temp1 = temp->next;
        k++;
    }
    if (k < n - 1)
    {
        puts("Error");
        system("pause");
        return begin;
    }
    print1(temp1);
    puts("Delete? (y/n)");
    do
        yes = getchar();
    while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
    if (yes == 'y' || yes == 'Y')
    {
        temp->next = temp1->next;
        free(temp1);
    }
    return begin;
}