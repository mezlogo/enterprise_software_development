#ifndef KEY_H
#define KEY_H

//#define packed_data __attribute__((__packed__))

struct Key {
	unsigned int ip;
	unsigned short port;
} __attribute__((packed));

typedef struct Key Key;

#endif
