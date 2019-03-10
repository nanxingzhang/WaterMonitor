/*
 * testUART.h
 *
 *  Created on: 2019-3-10
 *      Author: 1231
 */

#ifndef TESTUART_H_
#define TESTUART_H_
void ConfigClocks();
void ConfigPins();
void send_char(unsigned char);
void RXReady();
void Send_String(char a[]);
void RX_String();
extern  char RXData0;
extern char rx_sign;
extern char msg[32];
extern char ch;
#endif /* TESTUART_H_ */
