#include "fifo.h"
#include <string.h>


#define FIFO_SIZE 512

typedef struct {
	int front;
	int rear;
	int used;
	unsigned char buf[FIFO_SIZE];
} FIFO, *PFIFO;

static FIFO send_buf, recv_buf;

int fifo_write(int fd, void *buf, int count) {
	PFIFO pfifo = (fd == SEND_BUF) ? &send_buf : &recv_buf;
	if (FIFO_SIZE - pfifo->used < count) return 0;
	unsigned char *pbuf = (unsigned char *)buf;
	for (int i = 0; i < count; i++) {
		pfifo->buf[pfifo->rear] = *pbuf;
		pfifo->rear = (pfifo->rear == FIFO_SIZE - 1) ? 0 : pfifo->rear + 1;
		pfifo->used++;
		pbuf++;
	}
	return count;
}

int fifo_read(int fd, void *buf, int count) {
	PFIFO pfifo = (fd == SEND_BUF) ? &send_buf : &recv_buf;
	if (pfifo->used < count) return 0;
	unsigned char *pbuf = (unsigned char *)buf;
	for (int i = 0; i < count; i++) {
		*pbuf = pfifo->buf[pfifo->front];
		pfifo->front = (pfifo->front == FIFO_SIZE - 1) ? 0 : pfifo->front + 1;
		pfifo->used--;
		pbuf++;
	}
	return count;
}
