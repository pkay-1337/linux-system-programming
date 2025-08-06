#include <stdio.h>

int main(){
	char ttyname[256];
	ctermid(ttyname);
	printf("%s\n", ttyname);
	return 0;
}
