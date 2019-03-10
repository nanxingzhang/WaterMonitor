/*
 * Turbidity.c
 *通过ads1118检测浊度
 *  Created on: 2019-3-4
 *      Author: 1231
 */
//定义ADS的端口为    4:AIN0-GND
//定义ADS量程为        1:±4.096V


#include<msp430f5529.h>
#include<ADS1118.h>
#include<string.h>

#include <msp430.h>
char a[32]="";
int count=0;
int end_flage=0;

int Init_Turbity(void)
{
	P6OUT&=~BIT5;
	P6OUT&=~BIT4;
//	 P3DIR=0xff
  P3SEL = BIT3+BIT4;                        // P3.4,5 = USCI_A1 TXD/RXD
  UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA1CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA1BR0 = 0x03;                           // 32kHz/9600=3.41 (see User's Guide)
  UCA1BR1 = 0x00;                           //
  UCA1MCTL = UCBRS_3+UCBRF_0;               // Modulation UCBRSx=3, UCBRFx=0
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA1IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt

  __bis_SR_register(GIE);       // interrupts enabled
  __no_operation();                         // For debugger
}

void sendString( char *p){

   while(*p!='\0'){
	   UCA1TXBUF=*p++;
   while (!(UCA1IFG&UCTXIFG));//等待数据可再次发送
          }
}

unsigned char Is_End(unsigned char *p){
	char i;
	char a[6]="\r\n";
	for(i=0;i++;a[i]!='\0'){
		if(*p++!=a[i])return 0;
	}
	return 1;
}
char USCIA1_ReceiveChar(void)
{
	char data = 0;

//阻塞式返回值
	while(!(UCA1IFG & UCRXIFG));  // USCI_A1 TX buffer ready?
	UCA1IFG &= ~UCRXIFG;
	data = UCA1RXBUF;
	return data;


/* 
//非阻塞式返回值
    if(UCA1IFG & UCRXIFG)
  {
UCA1IFG &= ~UCRXIFG;
data = UCA1RXBUF;
}
return data;
*/
}

// 当下位机发送数据时，本机接收到时触发中断函数，每次接收一个8位
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
	 a[count++]=UCA1RXBUF;
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}


//函数：读取一次的浊度值
//入口参数：无
//返回值：无符号整型，值为标准浊度值
float Get_Turbidity(){
	Init_Turbity();
	sendString("AT");
	strcpy(a, "Good News!");
			UCA1IE &= ~UCRXIE;		//停止USCIA0 的uart
			P3SEL =0x0000;
			P6OUT|=BIT4;


	return 0;
}

//将读取到的ADS的值转化为标准浊度值
//入口参数：ADS值
//返回值：类型为浮点的标准浊度值
float Map_ADS_Turbidty(float AdsValue){

	return 0;
}



