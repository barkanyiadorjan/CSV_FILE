#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "csv_wr.h"
#include "csv_db.h"


#define MALLOC(ptr,size) \
	do { \
		ptr=malloc(size);	\
		if (!ptr)		\
			abort();	\
	} while(0)

#define FREE(ptr) \
	do {	\
		free(ptr);	\
		ptr=NULL;	\
	} while(0)


static struct {

	struct tailhead *headp;

	TAILQ_HEAD(tailhead, ROW) head;

} ROW_head;

static struct {
    int list_initialized;
    char *fileName;

} controll = {
    .list_initialized = 0,
    .fileName = NULL
};

/**
    \brief Free the selected struct element, and its sub elements
    \param Param is the struct element which we want to make free
    \return (EXIT_SUCESS)
*/
int CSV_DB_FreePtr(struct ROW *ptr)
{
    if(ptr->field1) FREE(ptr->field1);
    if(ptr->field2) FREE(ptr->field2);
    if(ptr->field3) FREE(ptr->field3);
    if(ptr->field4) FREE(ptr->field4);
    if(ptr->field5) FREE(ptr->field5);
    if(ptr->field6) FREE(ptr->field6);
    if(ptr->field7) FREE(ptr->field7);
    if(ptr->field8) FREE(ptr->field8);
    if(ptr->field9) FREE(ptr->field9);
    if(ptr->field10) FREE(ptr->field10);
    if(ptr->field11) FREE(ptr->field11);
    if(ptr->field12) FREE(ptr->field12);
    if(ptr->field13) FREE(ptr->field13);
    if(ptr->field14) FREE(ptr->field14);
    if(ptr->field15) FREE(ptr->field15);
    if(ptr->field16) FREE(ptr->field16);
    if(ptr->field17) FREE(ptr->field17);
    if(ptr->field18) FREE(ptr->field18);
    if(ptr->field19) FREE(ptr->field19);
    if(ptr->field20) FREE(ptr->field20);
    if(ptr) FREE(ptr);

    return (EXIT_SUCCESS);
}

/**
    \brief Allocate a new space and copy the param data there
    \param Param is the data what we want to copy the new space
    \return The pointer which point to the new space
*/
char *CSV_DB_StrCpy(char *buff)
{
    if(!buff)
        return 0;

    char *ptr;
    MALLOC(ptr,strlen(buff));
    strcpy(ptr,buff);

    return ptr;
}


/**
    \brief It tests the data struct. If it has a not empty variable, then return (EXIT_SUCCESS)
    \param Param is the data struct which we want to test
    \return (EXIT_SUCCESS) if the row is not empty, or it return (EXIT_FAILURE)
*/
int CSV_DB_EmptyLine(struct ROW *ptr)
{
    if(ptr->field1) return (EXIT_SUCCESS);
    if(ptr->field2) return (EXIT_SUCCESS);
    if(ptr->field3) return (EXIT_SUCCESS);
    if(ptr->field4) return (EXIT_SUCCESS);
    if(ptr->field5) return (EXIT_SUCCESS);
    if(ptr->field6) return (EXIT_SUCCESS);
    if(ptr->field7) return (EXIT_SUCCESS);
    if(ptr->field8) return (EXIT_SUCCESS);
    if(ptr->field9) return (EXIT_SUCCESS);
    if(ptr->field10) return (EXIT_SUCCESS);
    if(ptr->field11) return (EXIT_SUCCESS);
    if(ptr->field12) return (EXIT_SUCCESS);
    if(ptr->field13) return (EXIT_SUCCESS);
    if(ptr->field14) return (EXIT_SUCCESS);
    if(ptr->field15) return (EXIT_SUCCESS);
    if(ptr->field16) return (EXIT_SUCCESS);
    if(ptr->field17) return (EXIT_SUCCESS);
    if(ptr->field18) return (EXIT_SUCCESS);
    if(ptr->field19) return (EXIT_SUCCESS);
    if(ptr->field20) return (EXIT_SUCCESS);

    return (EXIT_FAILURE);
}

/**
    \brief It makes the list to default formation. Make every pointer element value to (NULL)
    \param Param is the data struct which we want to make default
    \return (EXIT_SUCCESS)
*/
int CSV_DB_DefaultStruct(struct ROW *ptr)
{
    ptr->field1 = NULL;
    ptr->field2= NULL;
    ptr->field3 = NULL;
    ptr->field4 = NULL;
    ptr->field5 = NULL;
    ptr->field6 = NULL;
    ptr->field7 = NULL;
    ptr->field8 = NULL;
    ptr->field9 = NULL;
    ptr->field10 = NULL;
    ptr->field11 = NULL;
    ptr->field12 = NULL;
    ptr->field13 = NULL;
    ptr->field14 = NULL;
    ptr->field15 = NULL;
    ptr->field16 = NULL;
    ptr->field17 = NULL;
    ptr->field18 = NULL;
    ptr->field19 = NULL;
    ptr->field20 = NULL;

    return (EXIT_SUCCESS);
}

/**
    \brief It copies the param element a new space, and add the new element to the list
    \note Do not forget to FREE the param ptr after the operation
    \param Param is the data struct which we want to copy and add
    \return (EXIT_SUCCESS)
*/
int CSV_DB_AddElement(struct ROW *ptr)
{
    struct ROW *new_ptr;
    MALLOC(new_ptr,sizeof(struct ROW));
    new_ptr->field1 = CSV_DB_StrCpy(ptr->field1);
    new_ptr->field2= CSV_DB_StrCpy(ptr->field2);
    new_ptr->field3 = CSV_DB_StrCpy(ptr->field3);
    new_ptr->field4 = CSV_DB_StrCpy(ptr->field4);
    new_ptr->field5 = CSV_DB_StrCpy(ptr->field5);
    new_ptr->field6 = CSV_DB_StrCpy(ptr->field6);
    new_ptr->field7 = CSV_DB_StrCpy(ptr->field7);
    new_ptr->field8 = CSV_DB_StrCpy(ptr->field8);
    new_ptr->field9 = CSV_DB_StrCpy(ptr->field9);
    new_ptr->field10 = CSV_DB_StrCpy(ptr->field10);
    new_ptr->field11 = CSV_DB_StrCpy(ptr->field11);
    new_ptr->field12 = CSV_DB_StrCpy(ptr->field12);
    new_ptr->field13 = CSV_DB_StrCpy(ptr->field13);
    new_ptr->field14 = CSV_DB_StrCpy(ptr->field14);
    new_ptr->field15 = CSV_DB_StrCpy(ptr->field15);
    new_ptr->field16 = CSV_DB_StrCpy(ptr->field16);
    new_ptr->field17 = CSV_DB_StrCpy(ptr->field17);
    new_ptr->field18 = CSV_DB_StrCpy(ptr->field18);
    new_ptr->field19 = CSV_DB_StrCpy(ptr->field19);
    new_ptr->field20 = CSV_DB_StrCpy(ptr->field20);

    TAILQ_INSERT_TAIL(&ROW_head.head, new_ptr, entries);

    return (EXIT_SUCCESS);
}

/**
    \brief It initializes the list. If the param file do not avaible, then it makes one with param name
    \note It loads te element to the list too
    \param Param is the file name what we want to open
    \return (EXIT_SUCCESS) if OK, else return (EXIT_FAILURE)
*/
int CSV_DB_Init(char *file_name)
{
    if(!file_name)
        return (EXIT_FAILURE);

    TAILQ_INIT(&ROW_head.head);

    int isntAvaible = CSV_WR_FileExist(file_name);

    MALLOC(controll.fileName,strlen(file_name));
    strcpy(controll.fileName,file_name);

    if(isntAvaible) //Akkor nem létezik
    {
        CSV_WR_CreateFile(file_name);
        controll.list_initialized=1;
        return (EXIT_SUCCESS);
    }

    //Megnyitjuk olvasásra
    FILE *file_ptr;
    file_ptr = fopen((const char*)file_name,"r");
    char buffer[50];
    int i = 0;
    char c;
    int elemszam = 0;
    memset(buffer,'\0',50);

    struct ROW *ptr = NULL;
    MALLOC(ptr,sizeof(struct ROW));
    CSV_DB_DefaultStruct(ptr);

        if (file_ptr)
        {
            while ((c = getc(file_ptr)) != EOF)
            {

                //új sor
                if(c==';')//string vége
                {
                    buffer[i]='\0';
                    i=0;
                    switch(elemszam)
                    {
                        case 0:
                            MALLOC(ptr->field1,strlen(buffer));
                            strcpy(ptr->field1,buffer);
                            break;
                        case 1:
                            MALLOC(ptr->field2,strlen(buffer));
                            strcpy(ptr->field2,buffer);
                            break;
                        case 2:
                            MALLOC(ptr->field3,strlen(buffer));
                            strcpy(ptr->field3,buffer);
                            break;
                        case 3:
                            MALLOC(ptr->field4,strlen(buffer));
                            strcpy(ptr->field4,buffer);
                            break;
                        case 4:
                            MALLOC(ptr->field5,strlen(buffer));
                            strcpy(ptr->field5,buffer);
                            break;
                        case 5:
                            MALLOC(ptr->field6,strlen(buffer));
                            strcpy(ptr->field6,buffer);
                            break;
                        case 6:
                            MALLOC(ptr->field7,strlen(buffer));
                            strcpy(ptr->field7,buffer);
                            break;
                        case 7:
                            MALLOC(ptr->field8,strlen(buffer));
                            strcpy(ptr->field8,buffer);
                            break;
                        case 8:
                            MALLOC(ptr->field9,strlen(buffer));
                            strcpy(ptr->field9,buffer);
                            break;
                        case 9:
                            MALLOC(ptr->field10,strlen(buffer));
                            strcpy(ptr->field10,buffer);
                            break;
                        case 10:
                            MALLOC(ptr->field11,strlen(buffer));
                            strcpy(ptr->field11,buffer);
                            break;
                        case 11:
                            MALLOC(ptr->field12,strlen(buffer));
                            strcpy(ptr->field12,buffer);
                            break;
                        case 12:
                            MALLOC(ptr->field13,strlen(buffer));
                            strcpy(ptr->field13,buffer);
                            break;
                        case 13:
                            MALLOC(ptr->field14,strlen(buffer));
                            strcpy(ptr->field14,buffer);
                            break;
                        case 14:
                            MALLOC(ptr->field15,strlen(buffer));
                            strcpy(ptr->field15,buffer);
                            break;
                        case 15:
                            MALLOC(ptr->field16,strlen(buffer));
                            strcpy(ptr->field16,buffer);
                            break;
                        case 16:
                            MALLOC(ptr->field17,strlen(buffer));
                            strcpy(ptr->field17,buffer);
                            break;
                        case 17:
                            MALLOC(ptr->field18,strlen(buffer));
                            strcpy(ptr->field18,buffer);
                            break;
                        case 18:
                            MALLOC(ptr->field19,strlen(buffer));
                            strcpy(ptr->field19,buffer);
                            break;
                        case 19:
                            MALLOC(ptr->field20,strlen(buffer));
                            strcpy(ptr->field20,buffer);
                            break;

                    }
                    memset(buffer,'\0',50);
                    elemszam++;
                }
                else if(c=='\n')//sor vége
                {
                    buffer[i]='\0';
                    i=0;
                    elemszam=0;
                    memset(buffer,'\0',50);

                    //Csak akkor adjuk hozzá a sort, ha nem üres
                    if(!CSV_DB_EmptyLine(ptr))
                        CSV_DB_AddElement(ptr);

                    if(ptr)
                        CSV_DB_FreePtr(ptr);

                    MALLOC(ptr,sizeof(struct ROW));
                    CSV_DB_DefaultStruct(ptr);
                }
                else
                {
                    buffer[i]=c;
                    i++;
                }

            }
            //Utolsó elem hozzáadása, ha nem üres
            if(!CSV_DB_EmptyLine(ptr))
                CSV_DB_AddElement(ptr);

            CSV_DB_FreePtr(ptr);
	    }

    fclose(file_ptr);
    controll.list_initialized=1;

    return (EXIT_SUCCESS);
}

/*
*************************************
            STATUS FUNC.
*************************************
*/

/**
    \brief It tests whether the list is empty
    \return TAILQ_EMPTY function
*/
int CSV_DB_IsEmpty()
{
    return TAILQ_EMPTY(&ROW_head.head);
}

/**
    \brief It test whether the param string is in the list
    \param Param is the string what we want to search
    \return (EXIT_SUCCESS) if we find it, else it returns (EXIT_FAILURE)
*/
int CSV_DB_IsElement(char *ptr)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(row_ptr->field1)
            if(!strcmp(row_ptr->field1,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field2)
            if(!strcmp(row_ptr->field2,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field3)
            if(!strcmp(row_ptr->field3,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field4)
            if(!strcmp(row_ptr->field4,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field5)
            if(!strcmp(row_ptr->field5,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field6)
            if(!strcmp(row_ptr->field6,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field7)
            if(!strcmp(row_ptr->field7,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field8)
            if(!strcmp(row_ptr->field8,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field9)
            if(!strcmp(row_ptr->field9,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field10)
            if(!strcmp(row_ptr->field10,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field11)
            if(!strcmp(row_ptr->field10,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field12)
            if(!strcmp(row_ptr->field12,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field13)
            if(!strcmp(row_ptr->field13,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field14)
            if(!strcmp(row_ptr->field14,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field15)
            if(!strcmp(row_ptr->field15,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field16)
            if(!strcmp(row_ptr->field16,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field17)
            if(!strcmp(row_ptr->field17,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field18)
            if(!strcmp(row_ptr->field18,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field19)
            if(!strcmp(row_ptr->field19,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field20)
            if(!strcmp(row_ptr->field20,ptr)) return (EXIT_SUCCESS);
    }

    return (EXIT_FAILURE);
}

/**
    \brief It test whether the param string is in the list. It searches only the selected column
    \param Param is the string what we want to search, and the column where we want to search
    \return (EXIT_SUCCESS) if we find it, else it returns (EXIT_FAILURE)
*/
int CSV_DB_IsElementIsColumn(char *ptr, int column)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(row_ptr->field1 && column==1)
            if(!strcmp(row_ptr->field1,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field2 && column==2)
            if(!strcmp(row_ptr->field2,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field3 && column==3)
            if(!strcmp(row_ptr->field3,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field4 && column==4)
            if(!strcmp(row_ptr->field4,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field5 && column==5)
            if(!strcmp(row_ptr->field5,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field6 && column==6)
            if(!strcmp(row_ptr->field6,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field7 && column==7)
            if(!strcmp(row_ptr->field7,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field8 && column==8)
            if(!strcmp(row_ptr->field8,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field9 && column==9)
            if(!strcmp(row_ptr->field9,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field10 && column==10)
            if(!strcmp(row_ptr->field10,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field11 && column==11)
            if(!strcmp(row_ptr->field10,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field12 && column==12)
            if(!strcmp(row_ptr->field12,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field13 && column==13)
            if(!strcmp(row_ptr->field13,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field14 && column==14)
            if(!strcmp(row_ptr->field14,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field15 && column==15)
            if(!strcmp(row_ptr->field15,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field16 && column==16)
            if(!strcmp(row_ptr->field16,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field17 && column==17)
            if(!strcmp(row_ptr->field17,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field18 && column==18)
            if(!strcmp(row_ptr->field18,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field19 && column==19)
            if(!strcmp(row_ptr->field19,ptr)) return (EXIT_SUCCESS);

        if(row_ptr->field20 && column==20)
            if(!strcmp(row_ptr->field20,ptr)) return (EXIT_SUCCESS);
    }

    return (EXIT_FAILURE);

}

/**
    \brief It counts the list elements number
    \return Return the number of the list elements
*/
int CSV_DB_RowCount()
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;
    int i = 0;

    if(TAILQ_EMPTY(&ROW_head.head))
        return 0;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
        i++;


    return i;
}


/*
*************************************
              GET FUNC.
*************************************
*/

/**
    \brief It searches the param string to the list, and if it find it, then return the list element
    \param Param is the string what we want to search
    \return Return the list element which contains the item we look for
*/
int CSV_DB_GetRow(char *ptr)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;
    int row = 1;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(row_ptr->field1)
            if(!strcmp(row_ptr->field1,ptr)) return row;

        if(row_ptr->field2)
            if(!strcmp(row_ptr->field2,ptr)) return row;

        if(row_ptr->field3)
            if(!strcmp(row_ptr->field3,ptr)) return row;

        if(row_ptr->field4)
            if(!strcmp(row_ptr->field4,ptr)) return row;

        if(row_ptr->field5)
            if(!strcmp(row_ptr->field5,ptr)) return row;

        if(row_ptr->field6)
            if(!strcmp(row_ptr->field6,ptr)) return row;

        if(row_ptr->field7)
            if(!strcmp(row_ptr->field7,ptr)) return row;

        if(row_ptr->field8)
            if(!strcmp(row_ptr->field8,ptr)) return row;

        if(row_ptr->field9)
            if(!strcmp(row_ptr->field9,ptr)) return row;

        if(row_ptr->field10)
            if(!strcmp(row_ptr->field10,ptr)) return row;

        if(row_ptr->field11)
            if(!strcmp(row_ptr->field10,ptr)) return row;

        if(row_ptr->field12)
            if(!strcmp(row_ptr->field12,ptr)) return row;

        if(row_ptr->field13)
            if(!strcmp(row_ptr->field13,ptr)) return row;

        if(row_ptr->field14)
            if(!strcmp(row_ptr->field14,ptr)) return row;

        if(row_ptr->field15)
            if(!strcmp(row_ptr->field15,ptr)) return row;

        if(row_ptr->field16)
            if(!strcmp(row_ptr->field16,ptr)) return row;

        if(row_ptr->field17)
            if(!strcmp(row_ptr->field17,ptr)) return row;

        if(row_ptr->field18)
            if(!strcmp(row_ptr->field18,ptr)) return row;

        if(row_ptr->field19)
            if(!strcmp(row_ptr->field19,ptr)) return row;

        if(row_ptr->field20)
            if(!strcmp(row_ptr->field20,ptr)) return row;

        row++;
    }

    return 0;
}

/**
    \brief It searches the param string to the list, and if it find it, then return the list element
    \note It searches only the selected column
    \param Param is the string what we want to search, and the column where we want to search
    \return Return the list element which contains the item we look for, if it doesn't find it, then return (0)
*/
int CSV_DB_GetRowInColumn(char *ptr, int column)
{
    struct ROW *row_ptr = NULL;
    int row = 1;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(row_ptr->field1 && column==1)
            if(!strcmp(row_ptr->field1,ptr)) return row;

        if(row_ptr->field2 && column==2)
            if(!strcmp(row_ptr->field2,ptr)) return row;

        if(row_ptr->field3 && column==3)
            if(!strcmp(row_ptr->field3,ptr)) return row;

        if(row_ptr->field4 && column==4)
            if(!strcmp(row_ptr->field4,ptr)) return row;

        if(row_ptr->field5 && column==5)
            if(!strcmp(row_ptr->field5,ptr)) return row;

        if(row_ptr->field6 && column==6)
            if(!strcmp(row_ptr->field6,ptr)) return row;

        if(row_ptr->field7 && column==7)
            if(!strcmp(row_ptr->field7,ptr)) return row;

        if(row_ptr->field8 && column==8)
            if(!strcmp(row_ptr->field8,ptr)) return row;

        if(row_ptr->field9 && column==9)
            if(!strcmp(row_ptr->field9,ptr)) return row;

        if(row_ptr->field10 && column==10)
            if(!strcmp(row_ptr->field10,ptr)) return row;

        if(row_ptr->field11 && column==11)
            if(!strcmp(row_ptr->field10,ptr)) return row;

        if(row_ptr->field12 && column==12)
            if(!strcmp(row_ptr->field12,ptr)) return row;

        if(row_ptr->field13 && column==13)
            if(!strcmp(row_ptr->field13,ptr)) return row;

        if(row_ptr->field14 && column==14)
            if(!strcmp(row_ptr->field14,ptr)) return row;

        if(row_ptr->field15 && column==15)
            if(!strcmp(row_ptr->field15,ptr)) return row;

        if(row_ptr->field16 && column==16)
            if(!strcmp(row_ptr->field16,ptr)) return row;

        if(row_ptr->field17 && column==17)
            if(!strcmp(row_ptr->field17,ptr)) return row;

        if(row_ptr->field18 && column==18)
            if(!strcmp(row_ptr->field18,ptr)) return row;

        if(row_ptr->field19 && column==19)
            if(!strcmp(row_ptr->field19,ptr)) return row;

        if(row_ptr->field20 && column==20)
            if(!strcmp(row_ptr->field20,ptr)) return row;

        row++;
    }

    return 0;
}

/**
    \brief We can select a cell, and get the value
    \param Param is the row and column, what we want to select
    \return Return the string, what is in the cell
*/
char *CSV_DB_GetField(int row, int column)
{
    struct ROW *row_ptr = NULL;
    int i = 1;
    char *str;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(i==row)
        {
             if(column==1) return row_ptr->field1;
             if(column==2) return row_ptr->field2;
             if(column==3) return row_ptr->field3;
             if(column==4) return row_ptr->field4;
             if(column==5) return row_ptr->field5;
             if(column==6) return row_ptr->field6;
             if(column==7) return row_ptr->field7;
             if(column==8) return row_ptr->field8;
             if(column==9) return row_ptr->field9;
             if(column==10) return row_ptr->field10;
             if(column==11) return row_ptr->field11;
             if(column==12) return row_ptr->field12;
             if(column==13) return row_ptr->field13;
             if(column==14) return row_ptr->field14;
             if(column==15) return row_ptr->field15;
             if(column==16) return row_ptr->field16;
             if(column==17) return row_ptr->field17;
             if(column==18) return row_ptr->field18;
             if(column==19) return row_ptr->field19;
             if(column==20) return row_ptr->field20;
        }

        i++;
    }

    return (NULL);
}

/**
    \brief We can select the row, and get the element address
    \param Param is the row what we want to select
    \return Return the element address
*/
struct ROW *CSV_DB_GetElement(int row)
{
    if(!controll.list_initialized)
        return (NULL);

    if(row>CSV_DB_RowCount())
        return (NULL);

    struct ROW *row_ptr = NULL;
    int i = 1;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(i==row)
        {
            return row_ptr;
        }
    }

    return (NULL);
}



/*
*************************************
                FUNC.
*************************************
*/
/**
    \brief We can select a cell, and overwrite the value
    \note It free the selected cell, and allocate a new space and copy the param value to there
    \param Param is the row and column, what we want to select, and the string what we want to copy
    \return (EXIT_SUCCESS) if everything is OK, else return (EXIT_FAILURE)
*/
int CSV_DB_WriteField(int row, int column, char *ptr)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;
    int i = 1;
    char *str;
    MALLOC(str,strlen(ptr));
    strcpy(str,ptr);

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(i==row)
        {
             if(column==1)
             {
                FREE(row_ptr->field1);
                row_ptr->field1 = str;
                return (EXIT_SUCCESS);
             }

             if(column==2)
             {
                FREE(row_ptr->field2);
                row_ptr->field2 = str;
                return (EXIT_SUCCESS);
             }

             if(column==3)
             {
                FREE(row_ptr->field3);
                row_ptr->field3 = str;
                return (EXIT_SUCCESS);
             }

             if(column==4)
             {
                FREE(row_ptr->field4);
                row_ptr->field4 = str;
                return (EXIT_SUCCESS);
             }

             if(column==5)
             {
                FREE(row_ptr->field5);
                row_ptr->field5 = str;
                return (EXIT_SUCCESS);
             }

             if(column==6)
             {
                FREE(row_ptr->field6);
                row_ptr->field6 = str;
                return (EXIT_SUCCESS);
             }

             if(column==7)
             {
                FREE(row_ptr->field7);
                row_ptr->field7 = str;
                return (EXIT_SUCCESS);
             }

             if(column==8)
             {
                FREE(row_ptr->field8);
                row_ptr->field8 = str;
                return (EXIT_SUCCESS);
             }

             if(column==8)
             {
                FREE(row_ptr->field8);
                row_ptr->field8 = str;
                return (EXIT_SUCCESS);
             }

             if(column==8)
             {
                FREE(row_ptr->field8);
                row_ptr->field8 = str;
                return (EXIT_SUCCESS);
             }

             if(column==9)
             {
                FREE(row_ptr->field9);
                row_ptr->field9 = str;
                return (EXIT_SUCCESS);
             }

             if(column==10)
             {
                FREE(row_ptr->field10);
                row_ptr->field10 = str;
                return (EXIT_SUCCESS);
             }

             if(column==11)
             {
                FREE(row_ptr->field11);
                row_ptr->field11 = str;
                return (EXIT_SUCCESS);
             }

             if(column==12)
             {
                FREE(row_ptr->field12);
                row_ptr->field12 = str;
                return (EXIT_SUCCESS);
             }

             if(column==13)
             {
                FREE(row_ptr->field13);
                row_ptr->field13 = str;
                return (EXIT_SUCCESS);
             }

             if(column==14)
             {
                FREE(row_ptr->field14);
                row_ptr->field14 = str;
                return (EXIT_SUCCESS);
             }

             if(column==15)
             {
                FREE(row_ptr->field15);
                row_ptr->field15 = str;
                return 0;
             }

             if(column==16)
             {
                FREE(row_ptr->field16);
                row_ptr->field16 = str;
                return (EXIT_SUCCESS);
             }

             if(column==17)
             {
                FREE(row_ptr->field17);
                row_ptr->field17 = str;
                return (EXIT_SUCCESS);
             }

             if(column==18)
             {
                FREE(row_ptr->field18);
                row_ptr->field18 = str;
                return (EXIT_SUCCESS);
             }

             if(column==19)
             {
                FREE(row_ptr->field19);
                row_ptr->field19 = str;
                return (EXIT_SUCCESS);
             }

             if(column==20)
             {
                FREE(row_ptr->field20);
                row_ptr->field20 = str;
                return (EXIT_SUCCESS);
             }
        }

        i++;
    }

    return (EXIT_FAILURE);
}

/**
    \brief It is make a new struct element, and copy the param cell values to it
    \note It allocate a new space for it, and copy everything to it. It is not the list, it will be just an element.
    \param Param is the field elements
    \return The address of the new element.
*/
struct ROW* CSV_DB_MakeNewElement
(char *f1,char *f2,char *f3,char *f4,char *f5,char *f6,char *f7,char *f8,char *f9,
char *f10,char *f11,char *f12,char *f13,char *f14,char *f15,char *f16,char *f17,char *f18,char *f19,char *f20)
{
    struct ROW *ptr;
    MALLOC(ptr,sizeof(struct ROW));

    if(f1 && *f1){ MALLOC(ptr->field1,strlen(f1)); strcpy(ptr->field1,f1);}
    else { ptr->field1=NULL; }

    if(f2 && *f2){ MALLOC(ptr->field2,strlen(f2)); strcpy(ptr->field2,f2);}
    else { ptr->field2=NULL; }

    if(f3 && *f3){ MALLOC(ptr->field3,strlen(f3)); strcpy(ptr->field3,f3);}
    else { ptr->field3=NULL; }

    if(f4 && *f4){ MALLOC(ptr->field4,strlen(f4)); strcpy(ptr->field4,f4);}
    else { ptr->field4=NULL; }

    if(f5 && *f5){ MALLOC(ptr->field5,strlen(f5)); strcpy(ptr->field5,f5);}
    else { ptr->field5=NULL; }

    if(f6 && *f6){ MALLOC(ptr->field6,strlen(f6)); strcpy(ptr->field6,f6);}
    else { ptr->field6=NULL; }

    if(f7 && *f7){ MALLOC(ptr->field7,strlen(f7)); strcpy(ptr->field7,f7);}
    else { ptr->field7=NULL; }

    if(f8 && *f8){ MALLOC(ptr->field8,strlen(f8)); strcpy(ptr->field8,f8);}
    else { ptr->field8=NULL; }

    if(f9 && *f9){ MALLOC(ptr->field9,strlen(f9)); strcpy(ptr->field9,f9);}
    else { ptr->field9=NULL; }

    if(f10 && *f10){ MALLOC(ptr->field10,strlen(f10)); strcpy(ptr->field10,f10);}
    else { ptr->field10=NULL; }

    if(f11 && *f11){ MALLOC(ptr->field11,strlen(f11)); strcpy(ptr->field11,f11);}
    else { ptr->field11=NULL; }

    if(f12 && *f12){ MALLOC(ptr->field12,strlen(f12)); strcpy(ptr->field12,f12);}
    else { ptr->field12=NULL; }

    if(f13 && *f13){ MALLOC(ptr->field13,strlen(f13)); strcpy(ptr->field13,f13);}
    else { ptr->field13=NULL; }

    if(f14 && *f14){ MALLOC(ptr->field14,strlen(f14)); strcpy(ptr->field14,f14);}
    else { ptr->field14=NULL; }

    if(f15 && *f15){ MALLOC(ptr->field15,strlen(f15)); strcpy(ptr->field15,f15);}
    else { ptr->field15=NULL; }

    if(f16 && *f16){ MALLOC(ptr->field16,strlen(f16)); strcpy(ptr->field16,f16);}
    else { ptr->field16=NULL; }

    if(f17 && *f17){ MALLOC(ptr->field17,strlen(f17)); strcpy(ptr->field17,f17);}
    else { ptr->field17=NULL; }

    if(f18 && *f18){ MALLOC(ptr->field18,strlen(f18)); strcpy(ptr->field18,f18);}
    else { ptr->field18=NULL; }

    if(f19 && *f19){ MALLOC(ptr->field19,strlen(f19)); strcpy(ptr->field19,f19);}
    else { ptr->field19=NULL; }

    if(f20 && *f20){ MALLOC(ptr->field20,strlen(f20)); strcpy(ptr->field20,f20);}
    else { ptr->field20=NULL; }

    return ptr;
}

/**
    \brief It adds the param element to the end of the list
    \param Param is the new list element
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_Insert_ROW(struct ROW *ptr)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;

    TAILQ_INSERT_TAIL(&ROW_head.head, ptr, entries);

    return (EXIT_SUCCESS);
}

/**
    \brief It adds the param element to the selected place of the list
    \param Param is the new list element
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_Insert_ROW_InPos(int row, struct ROW *ptr)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;

    int i = 1;

    if(row==0)
        return (EXIT_FAILURE);

    if(row==1)
    {
        TAILQ_INSERT_HEAD(&ROW_head.head,ptr,entries);
        return (EXIT_SUCCESS);
    }

    if(row==CSV_DB_RowCount())//Akkor az utolsó elem
    {
        TAILQ_INSERT_TAIL(&ROW_head.head, ptr, entries);
        return (EXIT_SUCCESS);
    }

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(i==row-1)
        {
            TAILQ_INSERT_AFTER(&ROW_head.head,row_ptr,ptr,entries);
            return (EXIT_SUCCESS);
        }

        i++;
    }

    return (EXIT_FAILURE); //Ha túl nagy szám akkor kilép hibával
}

/**
    \brief It deletes the first row from the list, and FREE it
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_Delete_FirstROW()
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = TAILQ_FIRST(&ROW_head.head);
    struct ROW *row_ptr_buff = row_ptr;

    TAILQ_REMOVE(&ROW_head.head,row_ptr,entries);
    CSV_DB_FreePtr(row_ptr_buff);

    return (EXIT_SUCCESS);
}

/**
    \brief It deletes the last row from the list, and FREE it
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_Delete_LastROW()
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = TAILQ_LAST(&ROW_head.head,tailhead);
    struct ROW *row_ptr_buff = row_ptr;

    TAILQ_REMOVE(&ROW_head.head,row_ptr,entries);
    CSV_DB_FreePtr(row_ptr_buff);

    return (EXIT_SUCCESS);
}

/**
    \brief It deletes the selected row from the list, and FREE it
    \param Param is the selected row what we want to dell
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_Delete_ROW(int row)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;
    struct ROW *row_ptr_buff = NULL;

    int i = 1;

    if(row==0)
        return (EXIT_FAILURE);

    if(row>CSV_DB_RowCount())
        return (EXIT_FAILURE);

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        if(i==row)
        {
            row_ptr_buff=row_ptr;
            TAILQ_REMOVE(&ROW_head.head,row_ptr,entries);
            CSV_DB_FreePtr(row_ptr_buff);
            return (EXIT_SUCCESS);
        }

        i++;
    }

    return (EXIT_FAILURE);

}


int CSV_DB_Move_ROW(int act_row, int dest_row)
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    if(act_row>CSV_DB_RowCount() || dest_row>CSV_DB_RowCount() || act_row==dest_row)
        return (EXIT_FAILURE);

    if(!act_row || !dest_row)
        return (EXIT_FAILURE);


    struct ROW *row_ptr = CSV_DB_GetElement(act_row);


    /*ITTTTTTTTTTTTTTTT
    TARTOOOOOOOK
    */


    /*struct ROW *row_buff = CSV_DB_MakeNewElement(row_ptr->field1,row_ptr->field2,row_ptr->field3,row_ptr->field4,
    row_ptr->field5,row_ptr->field6,row_ptr->field7,row_ptr->field8,row_ptr->field9,row_ptr->field10,
    row_ptr->field11,row_ptr->field12,row_ptr->field13,row_ptr->field14,row_ptr->field15,row_ptr->field16,
    row_ptr->field17,row_ptr->field18,row_ptr->field19,row_ptr->field20);
*/

    //struct ROW *row_buff = CSV_DB_MakeNewElement("Cell1","Cell2","Cellc","","cell5","","","","","","","","","","","","","","","");

    //CSV_DB_Insert_ROW_InPos(dest_row,row_buff);
    //CSV_DB_Delete_ROW(act_row);



    return (EXIT_SUCCESS);
}




/**
    \brief It deletes the full list
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_FreeList()
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;
    struct ROW *row_ptr_buff = NULL;

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        row_ptr_buff = row_ptr;
        TAILQ_REMOVE(&ROW_head.head,row_ptr,entries);
        CSV_DB_FreePtr(row_ptr_buff);
    }
    return (EXIT_SUCCESS);
}


/**
    \brief It export the CSV file
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_CloseFile()
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *row_ptr = NULL;

    if(CSV_WR_ReCreateFile(controll.fileName))
        return (EXIT_FAILURE);

    TAILQ_FOREACH(row_ptr, &ROW_head.head, entries)
    {
        CSV_WR_WriteLine(controll.fileName,(char* [])
        {row_ptr->field1,row_ptr->field2,row_ptr->field3,row_ptr->field4,row_ptr->field5
        ,row_ptr->field6,row_ptr->field7,row_ptr->field8,row_ptr->field9,row_ptr->field10
        ,row_ptr->field11,row_ptr->field12,row_ptr->field13,row_ptr->field14,row_ptr->field15
        ,row_ptr->field16,row_ptr->field17,row_ptr->field18,row_ptr->field19,row_ptr->field20},FIELD_COUNT);
    }

    CSV_DB_FreeList();


    return (EXIT_SUCCESS);
}


/**
    \brief It is simple print the list
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_DB_ListElements()
{
    if(!controll.list_initialized)
        return (EXIT_FAILURE);

    struct ROW *ptr = NULL;


    TAILQ_FOREACH(ptr, &ROW_head.head, entries)
    {
        if(ptr->field1) { printf("%s ",ptr->field1); }
        if(ptr->field2) { printf("%s ",ptr->field2); }
        if(ptr->field3) { printf("%s ",ptr->field3); }
        if(ptr->field4) { printf("%s ",ptr->field4); }
        if(ptr->field5) { printf("%s ",ptr->field5); }
        if(ptr->field6) { printf("%s ",ptr->field6); }
        if(ptr->field7) { printf("%s ",ptr->field7); }
        if(ptr->field8) { printf("%s ",ptr->field8); }
        if(ptr->field9) { printf("%s ",ptr->field9); }
        if(ptr->field10) { printf("%s ",ptr->field10); }
        if(ptr->field11) { printf("%s ",ptr->field11); }
        if(ptr->field12) { printf("%s ",ptr->field12); }
        if(ptr->field13) { printf("%s ",ptr->field13); }
        if(ptr->field14) { printf("%s ",ptr->field14); }
        if(ptr->field15) { printf("%s ",ptr->field15); }
        if(ptr->field16) { printf("%s ",ptr->field16); }
        if(ptr->field17) { printf("%s ",ptr->field17); }
        if(ptr->field18) { printf("%s ",ptr->field18); }
        if(ptr->field19) { printf("%s ",ptr->field19); }
        if(ptr->field20) { printf("%s ",ptr->field20); }

        printf("\n");
	}


	return (EXIT_SUCCESS);
}

