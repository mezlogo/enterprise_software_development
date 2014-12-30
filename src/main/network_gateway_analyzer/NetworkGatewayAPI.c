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

void initThread(pthread_t* thread, void* (*method)()) {
	int err = pthread_create(thread, NULL, method, NULL);
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
	
	//Пока клиент не закончил отправлять пакеты ИЛИ мы не все приняли, обрабатываем
	while (receiveCount < sendCount || SENDER_IS_DONE != isDone) {
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

void startForCollection(char (*find)(Key* key), char (*insert)(Key* key), char (*alter)(Key* source,
						Key* target), char (*initCollection)(int size), char* collectionName) {
	Collection collection = {find, insert, alter, initCollection};

	if (HASH_TABLE_INIT_FAIL == collection.initCollection(TRANSMITTERS_COUNT)) { printf("%s", "Can't init collection\n"); exit(-1);}


	printf("%s", "<<<<Reinit block>>>>\n");
	reset();
	initTransmitters();

	Key* transmitters = getTransmitters();
	int index = 0;

	for (; index < TRANSMITTERS_COUNT; index++) {
		if (INSERT_FAIL == collection.insert(&transmitters[index])) { printf("%s", "\nInit insert error!\n"); }
	}

	initClientServer(2500);

	initMessageHandlerCollection(&collection);

	startAnalyzer();
	show(collectionName);
}

void start() {
	setFileLoggerOutput();

	printf("%s", "\n<<<<<HASH TABLE>>>>>\n");
	startForCollection(&findHashTable, &insertHashTable, &alterHashTable, &initHashTable, "Hash");

	printf("%s", "\n<<<<<AVL TREE>>>>>\n");
	startForCollection(&findAVLTree, &insertAVLTree, &alterAVLTree, &initAVLTree, "AVL");

	printf("%s", "\n<<<<<B TREE>>>>>\n");
	startForCollection(&findBTree, &insertBTree, &alterBTree, &initBTree, "BI");
}
