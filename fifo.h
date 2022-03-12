#ifndef __FIFO_H__
#define __FIFO_H__

#define SEND_BUF 0
#define RECV_BUF 1



int fifo_write(int fd, void *buf, int count);
int fifo_read(int fd, void *buf, int count);

#endif
