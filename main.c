#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//strcat not working not gen-ning at the moment

typedef struct _list_{
    char *uniCode;
    int *date;
    int duration;
    double price;

    struct _list_ *next;
}list;

list *root=NULL;
list *rootX=NULL;
list *node;
list *nodeX;
list *tmp;

void end();
void addExcursion();
int checkUnique();
void writeBinary();
void readBinary();
void printAll();
void checkLongest();
void Delete(char *_code_);
void checkExpired(int year, int month, int day);
void expiredList();
void freeList();
int deleteExpired(int year, int month, int day);

int main()
{
    int i, k, _year, _month, _day;
    int choice;
    char *_code_;
    char *menu[]={"==============================================",
                  "|1.Add a new excursion.                      |",
                  "|2.Show info about the longest excursion.    |",
                  "|3.Show info about all expired excursions.   |",
                  "|4.Delete an excursion with a code by choice.|",
                  "|5.Show info about all excursions.           |",
                  "|6.Delete all expired                        |",
                  "|7.Quit.                                     |",
                  "=============================================="};
    readBinary();

    do
    {
        system("cls");

        for(i=0;i<9; i++)
        printf("%s\n", menu[i]);

        printf("\n\nChoose a mode->");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1: addExcursion(); system("pause"); break;
            case 2: checkLongest(); system("pause"); break;
            case 3: printf("Enter the year: ");
                    scanf("%d", &_year);
                    while(1)
                    {
                        printf("Enter the month: ");
                        scanf("%d", &_month);
                        if(_month<=12&&_month>0) break;
                        else printf("There is no such month!\n");
                    }
                    while(1)
                    {
                        printf("Enter the day: ");
                        scanf("%d", &_day);
                        if(_day<=31&&_day>0) break;
                        else printf("There is no such day of the month!\n");
                    }
                    checkExpired(_year, _month, _day); system("pause"); break;
            case 4: printf("\nEnter a unique code you want to delete->");
                    _code_= (char *) malloc(6);
                    gets(_code_);
                    Delete(_code_); system("pause"); break;
            case 5: printAll(); system("pause"); break;
            case 6: printf("Enter the year: ");
                    scanf("%d", &_year);
                    while(1)
                    {
                        printf("Enter the month: ");
                        scanf("%d", &_month);
                        if(_month<=12&&_month>0) break;
                        else printf("There is no such month!\n");
                    }
                    while(1)
                    {
                        printf("Enter the day: ");
                        scanf("%d", &_day);
                        if(_day<=31&&_day>0) break;
                        else printf("There is no such day of the month!\n");
                    }
                    do{
                    k=deleteExpired(_year, _month, _day);
                    }while(k!=1);
                    system("pause"); break;
            case 7: freeList(); system("cls"); printf("\nGoodbye!\n"); break;
            default: printf("\nYou haven't entered a valid choice!"); break;
        }
    }while(choice!=7);

    return 0;
}

void addExcursion()
{
    int a=0, i=0, k;
    time_t t;
    char Rletter ='ABCDEFGHIJKLMNOPQRSTUVWXYZ' + (rand()%24 +1);
    char Rnumb = '0123456789' + (rand()%10 +1);

    srand((unsigned) time(&t));
    end();
    if(root==NULL)
    {
        root=(list *) calloc(1, sizeof(list));
        root->next=NULL;
        node=root;
    }
    else
    {
        node->next=(list *) calloc(1, sizeof(list));
        node=node->next;
        node->next=NULL;
    }

    do
    {
        printf("\nEnter a UNIQUE number(consisting of a character letter and 4 digits): ");
        node->uniCode = (char *) malloc(6);
        strcat(node->uniCode, Rletter);
        for(k=0;k<4; k++)
        {
            strcat(node->uniCode, Rnumb);
        }
//        fgets(node->uniCode, 6, stdin);
        getchar();
        a=checkUnique();
    }while(a!=0);

    node->date= (int *) malloc(3*sizeof(int));
    printf("\nEnter the year of departure: ");
    scanf("%d", &node->date[0]);
    while(1)
    {
        printf("\nEnter the month of departure: ");
        scanf("%d", &node->date[1]);
        if((node->date[1]>=1)&&(node->date[1]<=12)) break;
        else printf("\nThere is no such month!");
    }

    while(1)
    {
        printf("\nEnter the day of departure(No departures at the end of a month!): ");
        scanf("%d", &node->date[2]);
        if((node->date[1]>=2)&&((node->date[2]>=1)&&(node->date[2]<=27))) break;
        else if((node->date[1]!=2)&&((node->date[2]>=1)&&(node->date[2]<=30))) break;
        else printf("\nNo such date!");
    }
    printf("\nEnter the length of the excursion(days): ");
    scanf("%d", &node->duration);

    printf("\nEnter the price of the excursion: ");
    scanf("%lf", &node->price);
    writeBinary(i);
}

int checkUnique()
{
    int a=0;
    tmp=root;
    while(1)
    {
        if(tmp->next==node->next)
            {
                if(tmp->next!=NULL)tmp=tmp->next;
                else
                {
                    a=0;
                    break;
                }
            }
        if(strcmp(tmp->uniCode, node->uniCode)==0)
        {
            printf("\nThis number already exists!");
            free(node->uniCode);
            a=1;
            break;
        }
        if(tmp->next==NULL){a=0; break;}
        tmp=tmp->next;
    }

    return a;
}

void end()
{
    if(root==NULL) return;
    node=root;
        while(1)
        {
            if(node->next==NULL) break;
            else node = node->next;
        }
}

void writeBinary(int i)
{
    FILE *fin = NULL;
    int len;

    if(i==0)
    fin=fopen("Excursions.bin", "ab+");
    else
    fin=fopen("Excursions.bin", "wb+");

    if(fin==NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    while(1)
    {
    len = strlen(node->uniCode);
    node->uniCode[len]='\0';
    fwrite(&len, sizeof(int), 1, fin);
    fwrite(node->uniCode, sizeof(char), len, fin);
    fwrite(&node->date[0], sizeof(int), 1, fin);
    fwrite(&node->date[1], sizeof(int), 1, fin);
    fwrite(&node->date[2], sizeof(int), 1, fin);
    fwrite(&node->price, sizeof(double), 1, fin);
    fwrite(&node->duration, sizeof(int), 1, fin);

    if(node->next==NULL) break;
    else node=node->next;
    }

    fclose(fin);
}

void readBinary()
{
    FILE *fin = NULL;
    int len=0, choice;

    fin=fopen("Excursions.bin", "rb+");

    node=root;
    if(fin==NULL)
    {
        printf("\nError opening file!");
        while(1)
        {
            printf("\nIs this the first time the program is running?\nyes->1\nno->2\n");
            scanf("%d", &choice);
            getchar();
            if(choice==2)
            {
                printf("Closing program!");
                system("pause");
                exit(1);
            }
            else if(choice==1) return;
            else
            {
                printf("\nYou haven't entered a valid choice!");
            }
        }
    }
    while(1)
    {
        if(root==NULL)
        {
            root=(list *) calloc(1, sizeof(list));
            root->next=NULL;
            node=root;
        }
        else
        {
            tmp=node;
            node->next=(list *) calloc(1, sizeof(list));
            node=node->next;
            node->next=NULL;
        }

        if(fread(&len, sizeof(int), 1, fin)!=1) break;
        node->uniCode = (char *) malloc(6);
        fread(node->uniCode, sizeof(char), len, fin);
        node->date=(int *) malloc(3*sizeof(int));
        fread(&node->date[0], sizeof(int), 1, fin);
        fread(&node->date[1], sizeof(int), 1, fin);
        fread(&node->date[2], sizeof(int), 1, fin);
        fread(&node->price, sizeof(double), 1, fin);
        fread(&node->duration, sizeof(int), 1, fin);
    }
    tmp->next=NULL;
    free(node);

    fclose(fin);
}

void printAll()
{
	if (root==NULL)
	{
        printf("No list entered!");
        return;
	}
	node=root;

	while (1)
	{
        printf("\nUnique code: %s\n", node->uniCode);
        printf("Departure date: %d.%d.%d\n", node->date[2], node->date[1], node->date[0]);
        printf("Duration: %d\n", node->duration);
        printf("Price: %g\n", node->price);
		if ( node->next == NULL ) break ;
		else node=node->next;
	}
}

void checkLongest()
{
    if (root==NULL)exit(1);
	tmp=node=root;

    while(1)
    {
        if(tmp->duration<node->duration)
            {
                tmp=node;
                if(node->next==NULL) break;
                else node=node->next;
            }
        else
            {
                if(node->next==NULL) break;
                else node=node->next;
            }
    }

    printf("\nUnique code: %s\n", tmp->uniCode);
    printf("Departure date: %d.%d.%d\n", tmp->date[2], tmp->date[1], tmp->date[0]);
    printf("Duration: %d\n", tmp->duration);
    printf("Price: %g\n", tmp->price);
}

void Delete(char *_code_)
{
    int i=1;
    tmp = node = root;
    if (root==NULL) return;
    while(1)
    {
        if(!(strcmp(node->uniCode, _code_))) break;
        else if(node->next!=NULL)
        {
            tmp=node;
            node=node->next;
        }
        else return;
    }
    if(root==node)
        root=root->next;
    else
        tmp->next = node->next;

    free(node->uniCode);
    free(node->date);
    free(node);

    node=root;
    writeBinary(i);
}

void checkExpired(int year, int month, int day)
{
    node=root;

    while(1)
    {
        if(year>node->date[0]) expiredList();
        if((year==node->date[0])&&(month>node->date[1])) expiredList();
        if(((year==node->date[0])&&(month==node->date[1]))&&(day>node->date[2])) expiredList();

        if ( node->next == NULL ) break ;
		else node=node->next;
    }

    if(rootX==NULL)
    {
        printf("There no åxcursions before this date");
        return;
    }
    nodeX=rootX;
	while (1)
	{
        printf("\nUnique code: %s\n", nodeX->uniCode);
        printf("Departure date: %d.%d.%d\n", nodeX->date[2], nodeX->date[1], nodeX->date[0]);
        printf("Duration: %d\n", nodeX->duration);
        printf("Price: %g\n", nodeX->price);
		if ( nodeX->next == NULL ) break ;
		else nodeX=nodeX->next;
	}
    while (rootX != NULL)
    {
       nodeX = rootX;
       rootX = rootX->next;
       free(nodeX->uniCode);
       free(nodeX->date);
       free(nodeX);
    }
}
void expiredList()
{
            if(rootX==NULL)
            {
                rootX=(list *) calloc(1, sizeof(list));
                rootX->next=NULL;
                nodeX=rootX;
            }
            else
            {
                nodeX->next=(list *) calloc(1, sizeof(list));
                nodeX=nodeX->next;
                nodeX->next=NULL;
            }

            nodeX->uniCode=(char *) malloc(50);
            strcpy(nodeX->uniCode, node->uniCode);
            nodeX->date=(int *) malloc(3*sizeof(int));
            nodeX->date[0]=node->date[0];
            nodeX->date[1]=node->date[1];
            nodeX->date[2]=node->date[2];
            nodeX->price=node->price;
            nodeX->duration=node->duration;
}

void freeList()
{
   while (root != NULL)
    {
       node = root;
       root = root->next;
       free(node->uniCode);
       free(node->date);
       free(node);
    }
}
int deleteExpired(int year, int month, int day)
{
    int i=1;
    tmp = node = root;
    if (root==NULL) return 1;

    while(1)
    {
        if(year>node->date[0]) break;
        if((year==node->date[0])&&(month>node->date[1])) break;
        if(((year==node->date[0])&&(month==node->date[1]))&&(day>node->date[2])) break;
        else if(node->next!=NULL)
        {
            tmp=node;
            node=node->next;
        }
        else return 1;
    }
    if(root==node)
        root=root->next;
    else
        tmp->next = node->next;

    free(node->uniCode);
    free(node->date);
    free(node);

    node=root;
    writeBinary(i);
    return 0;
}
