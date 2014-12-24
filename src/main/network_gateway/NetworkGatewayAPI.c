#include <stdio.h>

#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <sys/mman.h>  /* mmap */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* _exit, fork */
#include <string.h>

#include <pthread.h>

#include "ClientServer.h"
#include "Logger.h"
#include "HashTable.h"
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

    printf("%s%d\n", "Client and server start on port: ", port);

}

void initBlock() {
    printf("%s", "<<<<Reinit block>>>>\n");
    reset();
    initTransmitters();
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

    //printf("sendCount: %d\n", sendCount);
    //Отправить MESSAGE_COUNT_TO_SEND раз
    while (sendCount < MESSAGE_COUNT_TO_SEND) {
	//Сформировать сообщение и отправить сообщение
	generateMessage(messageToSend, sendCount);
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

void start() {
    Collection collection = {};

    collection.insert = &insertHashTable;
    collection.find = &findHashTable;
    collection.alter = &alterHashTable;

    initBlock();
    initHashTable(TRANSMITTERS_COUNT);
    initCollection(&collection);

    startAnalyzer();
    show();
}
