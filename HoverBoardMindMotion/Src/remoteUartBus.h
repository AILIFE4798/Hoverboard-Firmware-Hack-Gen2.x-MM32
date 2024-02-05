#ifndef REMOTE_UART_H
#define REMOTE_UART_H


#define REMOTE_BAUD 19200

#define SREIALTIMEOUT 1000   //stop when serial is disconnected

// Only master communicates with steering device
#ifdef MASTER_OR_SINGLE

void AnswerMaster(void);


#endif	// MASTER

#endif