#include <stdio.h>
#include "strutils.h"

int main(){
 	char input[256];
    int number; 

 	printf("input a string: \n");
 	scanf("%s", input);

 	str_trim(input);
 	printf("Trimmed string: %s\n",input);

 	str_reverse(input);
 	printf("Reversed string: %s\n", input);

 	if (str_to_int(input, &number)) {
        printf("Successfully converted to integer: %d\n", number);
    } else {
        printf("Failed to convert '%s' to an integer.\n", input);
    }

 	return 0;
}

