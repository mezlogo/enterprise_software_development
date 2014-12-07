#define SIZE 100000

#define validation(variable) if (SIZE <= ++variable) variable = 0;

long putIndex = 0;
long getIndex = 0;

char * list[SIZE];

void put(char * variable) {
	validation(putIndex);
		
	list[putIndex] = variable;
}

char * next() {
	validation(getIndex);
	
	return list[getIndex];
}
