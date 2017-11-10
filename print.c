#include <stdio.h>

int main () {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j ++) {
			if (i == 6 && j != 0 && j != 11) printf (" 1 ");
			else printf (" 0 ");
		}
		printf ("\n");
	}
	
	return 0;
}
