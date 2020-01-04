#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_wr.h"

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

/**
    \brief If the file exist, return EXIT_SUCCESS
    \param Param is the file name
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int  CSV_WR_FileExist(char *file_name)
{
    FILE *ptr;

    ptr = fopen((const char*)file_name,"r");

    if(!ptr)//Then it isn't exist
        return (EXIT_FAILURE);

    fclose(ptr);
    return (EXIT_SUCCESS);

}

/**
    \brief Create a new file
    \note If the file is already exist, return (EXIT_FAILURE)
    \param Param is the file name
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_WR_CreateFile(char *file_name)
{
    if(!CSV_WR_FileExist(file_name)) //File already exist
        return 1;

    FILE *ptr;

    ptr = fopen((const char*)file_name,"w");

    if(!ptr)//Then unable to create file
        return 1;

    fclose(ptr);
    return 0;
}

/**
    \brief Recreate the selected file (delete all content)
    \note If the file isn't exist, return (EXIT_FAILURE)
    \param Param is the file name
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_WR_ReCreateFile(char *file_name)
{
    if(CSV_WR_FileExist(file_name)) //File is not exist
        return (EXIT_FAILURE);

    FILE *ptr;

    ptr = fopen((const char*)file_name,"w");

    if(!ptr)//Then unable to create file
        return (EXIT_FAILURE);

    fclose(ptr);
    return (EXIT_SUCCESS);
}

/**
    \brief Append the param string to the selected file
    \param Params are the file name, data, and data lenght
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_WR_WriteToFile(char *file_name,char *data, int data_length)
{
    FILE *ptr;
    int i = 0;

    ptr = fopen((const char*)file_name,"a");

    if(!ptr)//Then unable to create or open file
        return (EXIT_FAILURE);

    for(i=0;i<data_length;i++)
    {
        fputc(*data,ptr);
        data++;
    }

    fclose(ptr);

    return (EXIT_SUCCESS);
}

/**
    \brief Calculete the neccessery lenght the output data for the CSV file
    \note  It is calculate the binary null and the ';' too
    \param Params are the str list, and the list length
    \return Return the neccessery length
*/
int CSV_WR_Line_Char_Length(char *str_list[],int length)
{
    int i = 0;
    int hossz = 0;

    for(i;i<length;i++)
    {
        if(str_list[i])
            hossz+=strlen(str_list[i]);
    }

    hossz+=length*2; //bináris nullákat és pontosvesszőke hozzáadjuk, mert azt nem számolja

    return hossz;
}

/**
    \brief Copy the string to the destanition
    \note  You can select the shift value to the selected dest. It will be add a plus ';' char to the end
    \param Params are the destination, the src, and the shift value
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_WR_StrCpyFrom(char *dest, char *src,int pos)
{
    if(!src || !dest)
        return (EXIT_FAILURE);

    int i = 0;
    int hossz = strlen(src);

    for(i;i<pos;i++)
        dest++;

    i = 0;
    for(i;i<hossz;i++)
    {
        *dest=*src;
        dest++;
        src++;
    }


    *dest=';';

    return (EXIT_SUCCESS);
}

/**
    \brief It generates a line from the input string array
    \note It is allocate a new space to the data
    \param Params are the input string array, and the arrray lenght
    \return Return the pointer to the new data
*/
char* CSV_WR_Generate_Line(char *str_list[],int length)
{
    int enought_length = CSV_WR_Line_Char_Length(str_list,length);
    char *new_ptr;
    MALLOC(new_ptr,enought_length);
    memset(new_ptr,'\0',enought_length);

    char *ptr_buff = new_ptr;
    int i = 0;
    int elozo_hossz = 0;

    for(i;i<length;i++)
    {
        if(!str_list[i])//Akkor null pointer
        {
            CSV_WR_StrCpyFrom(new_ptr,"",elozo_hossz);
            elozo_hossz++;
        }
        else
        {
            CSV_WR_StrCpyFrom(new_ptr,str_list[i],elozo_hossz);
            elozo_hossz += strlen(str_list[i])+1; //+1 a ';' miatt
        }
    }

    return new_ptr;
}


/**
    \brief It writes a new line to the selected CSV file
    \param Params are the file name, input string array, and the arrray lenght
    \return (EXIT_SUCCESS) if OK, else (EXIT_FAILURE)
*/
int CSV_WR_WriteLine(char *file_name,char *str_list[], int length)
{
    FILE *file;
	file = fopen(file_name, "a");

	if (!file)
        return (EXIT_FAILURE);

    char *ptr = CSV_WR_Generate_Line(str_list,length);

    fputc('\n',file);
    fputs(ptr,file);

    FREE(ptr);
    fclose(file);

    return (EXIT_SUCCESS);
}




