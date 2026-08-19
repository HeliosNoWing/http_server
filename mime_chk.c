#include "mime_chk.h" 
#include <string.h> 
#define ENTRY_SIZE 100
#define NUM_ENTRY 10
typedef struct look_up
{
	char response_str[ENTRY_SIZE];
	char mime_str[ENTRY_SIZE];
}look_up;

look_up table [NUM_ENTRY];
look_up* table_init()
{
	const char* mime[ENTRY_SIZE] =
	{"NULL", "apng", "avit", "css", "gif", "html", "png", "systXML", "txt", "wlop"};
	const char* response[ENTRY_SIZE] =
	{"NULL","image/apng","image/avit","txt/css","image/gif","text/html","image/png","image/systXML","text/text","image/wlop"};

	for(int i = 0; i<NUM_ENTRY; i++)
	{
		strcpy(table[i].mime_str,mime[i]); 
		strcpy(table[i].response_str,response[i]);
	}
	return table;	
}

char* mime_extract(char* file_path)
{
	char*s = file_path;
	if(!strcmp(file_path,"/")) return "html";
	while(*s != '.') s++;
	s++;
	return s;
}
char* mime_lookup(char* mime)
{
	look_up* look_up_table = table_init();
	int i  = 0;
	int j = NUM_ENTRY-1;
	while(i<=j)
	{
		int mid = i+(j-i)/2;
		int table_chk = strcmp(mime,look_up_table[mid].mime_str);
		if(table_chk == 0) return look_up_table[mid].response_str;
		if(table_chk > 0) i = mid+1; 
		else j = mid-1;
	}
	return "NO RESPONES";
} 
