int findFirstZero(char * array, int length){
	int index = 0;
	int result = -1;
	
	for(; index < length; index++)
		if(0 == array[index]){
			result = index;
			break;
		}
		
	return result;	
}
