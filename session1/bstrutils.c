#include "strutils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
void str_reverse(char *str){
	char *end;
	char temp;
	if(str	== NULL || !(*str)) return;
	end = str + strlen(str) - 1;

	while (end > str){
		temp = *str;
		*str = *end;
		*end = temp;
		str++;
		end--;
	}

}
void str_trim(char *str){
	char *end;
	char *start = str;

	while (isspace((unsigned char)*start)){
		start++;
	}
	if (*start == '\0'){
		*str = '\0';
		return;
	}
	end = start +strlen(start) -1;
	while (end > start && isspace((unsigned char)*end)){
		end--;
	}

	//null terminate
	*(end +1 ) = '\0';

	// shift to the start after spaces are removed
	if (start != str){
		memmove(str,start, strlen(start) + 1);
	}

}	
int str_to_int(char *str, int *result){
	errno = 0;
	char *end;
	long value = strtol(str, &end, 10);
	if (end == str||*end != '\0' || errno == ERANGE){
		printf("Error str to int\n");
		return 0;
	} 
	*result = (int)value;
	return 1;

}


