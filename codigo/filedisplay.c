#include <stdio.h>
#include <stdlib.h>
#define DATAFILE "/var/www/cgidata/data.txt"

int main(void) {
    FILE *f = fopen("/var/www/cgidata/Registro.html","r");
    int ch;
    if(f == NULL) {
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<TITLE>Failure</TITLE>\n");
        printf("<P><EM>Unable to open data file, sorry!</EM>"); }
    else {
	printf("%s%c%c\n", "Content-Type:text/html; charset=UTF-8 ",13,10);
        while((ch=getc(f)) != EOF)
            putchar(ch);
        fclose(f); 
    }
    return 0;
}
