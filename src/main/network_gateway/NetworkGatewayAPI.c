#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#include "ClientServer.h"
#include "Logger.h"
#include "HashTable.h"
#include "AVLTree.h"
#include "BTree.h"
#include "Configuration.h"
#include "FakeTransmitters.h"
#include "Collection.h"
#include "MessageHandler.h"

void initThread(pthread_t* thread,
				void* (*method)()) {
	int err = pthread_create(thread, NULL, method,
							 NULL);

	if (err != 0)	{ printf("%s[%s]\n", "Can't create thread: ", strerror(err)); }
}


void initClientServer(int port) {
	void stClient() {
		startClient(port);
	}

	void stServer() {
		startServer(port);
	}

	pthread_t threadA;
	pthread_t threadB;

	initThread(&threadB, (void*) &stServer);
	initThread(&threadA, (void*) &stClient);

	pthread_join(threadB, NULL);
	pthread_join(threadA, NULL);

	printf("%s%d\n",
		   "Client and server start on port: ", port);

}

void initBlock(Collection* collection) {
	printf("%s", "<<<<Reinit block>>>>\n");
	reset();
	initTransmitters();

	Key* transmitters = getTransmitters();

	int index = 0;

	Key* currentTransmitter;

	for (; index < TRANSMITTERS_COUNT; index++) {
		if (INSERT_FAIL == collection->insert(currentTransmitter = &transmitters[index]))
		{ printf("%s", "\nInit insert error!\n"); }

		else {printf("%s%08x port: %04x\n", "Init ip: ", currentTransmitter->ip, currentTransmitter->port);}
	}

	initClientServer(2500);
}


#define SENDER_IS_DONE 1
#define SENDER_ISNT_DONE -1

unsigned char isDone = SENDER_ISNT_DONE;
unsigned long receiveCount = 0;
unsigned long sendCount = 0;

void threadSender() {
	isDone = SENDER_ISNT_DONE;
	sendCount = 0;
	char messageToSend[MESSAGE_SIZE];

	//Отправить MESSAGE_COUNT_TO_SEND раз
	while (sendCount < MESSAGE_COUNT_TO_SEND) {
		//Сформировать сообщение и отправить сообщение
		generateMessage(messageToSend, sendCount + 1);
		sendMessage(messageToSend);

		sendCount++;
	}

	printf("sendCount: %lu\n", sendCount);

	isDone = SENDER_IS_DONE;
}

void threadReceiver() {
	char messageToReceive[MESSAGE_SIZE];
	receiveCount = 0;
	sleep(1);

	//Пока клиент не закончил отправлять пакеты ИЛИ мы не все приняли, обрабатываем
	while (receiveCount < sendCount ||
			SENDER_IS_DONE != isDone) {
		readMessage(messageToReceive);
		handleMessage(messageToReceive);
		receiveCount++;
	}

	printf("receiveCount: %lu\n", receiveCount);
}

void startAnalyzer() {
	pthread_t threadA;
	pthread_t threadB;

	initThread(&threadB, (void*) &threadReceiver);
	initThread(&threadA, (void*) &threadSender);

	pthread_join(threadA, NULL);
	pthread_join(threadB, NULL);

	closeClient();
	closeServer();
}

void startForCollection(Collection* collection) {
	collection->initCollection(TRANSMITTERS_COUNT);
	initBlock(collection);
	initCollection(collection);

	startAnalyzer();
	show();
}

void start() {
	Collection collection = {};

	printf("%s", "\n\n<<<<<HASH TABLE>>>>>\n\n");
	collection.insert = &insertHashTable;
	collection.find = &findHashTable;
	collection.alter = &alterHashTable;
	collection.initCollection = &initHashTable;
	startForCollection(&collection);

	printf("%s", "\n\n<<<<<AVL TREE>>>>>\n\n");
	collection.insert = &insertAVLTree;
	collection.find = &findAVLTree;
	collection.alter = &alterAVLTree;
	collection.initCollection = &initAVLTree;
	startForCollection(&collection);
	
	printf("%s", "\n\n<<<<<B TREE>>>>>\n\n");
	collection.insert = &insertBTree;
	collection.find = &findBTree;
	collection.alter = &alterBTree;
	collection.initCollection = &initBTree;
	startForCollection(&collection);
}
