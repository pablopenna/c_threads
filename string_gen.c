#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* string_generator(int str_len)
/*arg= string's lenght*/
{
	char* final_string;//[str_len+1];
	char aux;
	int random[str_len];//[A-Z] in ASCII=[65-90]
	int j;


	for(j=0;j<str_len;j++)
	{
		random[j]=(rand()%25)+65;//random=random int from 65 to 90
		aux=random[j];
		strcpy(&final_string[j],&aux);
	}
	strcpy(&final_string[str_len],"\0");
	//printf("%s\n",final_string);
	return final_string;


}
