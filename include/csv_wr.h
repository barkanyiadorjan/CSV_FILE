#ifndef CSV_WR_H_INCLUDED
#define CSV_WR_H_INCLUDED



int CSV_WR_FileExist(char *file_name);

int CSV_WR_CreateFile(char *file_name);
int CSV_WR_ReCreateFile(char *file_name);
int CSV_WR_WriteToFile(char *file_name,char *data, int data_length);


int CSV_WR_Line_Char_Length(char *str_list[],int length);
char* CSV_WR_Generate_Line(char *str_list[],int length);


int CSV_WR_WriteLine(char *file_name,char *str_list[], int length);

#endif // CSV_WR_H_INCLUDED
