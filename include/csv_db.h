#ifndef CSV_DB_H_INCLUDED
#define CSV_DB_H_INCLUDED

#include <sys/queue.h>

#define FIELD_COUNT 20

struct ROW
{
    char *field1; char *field2;
    char *field3; char *field4;
    char *field5; char *field6;
    char *field7; char *field8;
    char *field9; char *field10;
    char *field11; char *field12;
    char *field13; char *field14;
    char *field15; char *field16;
    char *field17; char *field18;
    char *field19; char *field20;

    TAILQ_ENTRY(ROW) entries;
};

//Init
int CSV_DB_Init(char *file_name);

//STATUS
int CSV_DB_IsEmpty();
int CSV_DB_IsElement(char *ptr);
int CSV_DB_IsElementIsColumn(char *ptr, int column);
int CSV_DB_RowCount();

//GET
int CSV_DB_GetRow(char *ptr);
int CSV_DB_GetRowInColumn(char *ptr, int column);//csak az adott oszlopban keres
char *CSV_DB_GetField(int row,int column);
struct ROW *CSV_DB_GetElement(int row);


//Function
int CSV_DB_WriteField(int row, int column, char *ptr);

struct ROW* CSV_DB_MakeNewElement
(char *f1,char *f2,char *f3,char *f4,char *f5,char *f6,char *f7,char *f8,char *f9,
char *f10,char *f11,char *f12,char *f13,char *f14,char *f15,char *f16,char *f17,char *f18,char *f19,char *f20);

int CSV_DB_Insert_ROW(struct ROW *ptr);//utolsó helyre rak egyet
int CSV_DB_Insert_ROW_InPos(int row, struct ROW *ptr);
int CSV_DB_Delete_FirstROW();
int CSV_DB_Delete_LastROW();
int CSV_DB_Delete_ROW(int row);

int CSV_DB_Move_ROW(int act_row, int dest_row);
int CSV_DB_Swap_ROWS(int row1, int row2);

int CSV_DB_FreeList();
int CSV_DB_CloseFile();


int CSV_DB_ListElements();


#endif // CSV_DB_H_INCLUDED
