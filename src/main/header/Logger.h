void reset();

void logPrimary(unsigned long time);

void logSecondary(unsigned long time);

void show();

void (*showMeasure)(char * name, unsigned long* array,	unsigned long length, char* measuringName, unsigned long maxValue, unsigned long averageValue, unsigned long minValue);

void setFileLoggerOutput();
