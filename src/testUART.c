#include<msp430f5529.h>


#define RXD BIT2
#define TXD BIT3
#define LED BIT0

int BITTIME_1b=(4000000/9600);
int BITTIME_1b5=(4000000/(9600*2));

 char bitcnt=0;//计数
unsigned int  uart_buf;

char RXData0=0;//储存接收数据的8位
char RXBitCnt0;//接收数据位
char rx_sign=0;

char msg[32]="hello";		//接收的字符串数据
char ch;
volatile int Send_flag=0;

void FaultRoutine(){
	while(1);//异常挂起
}

//void ConfigClocks(){
//	unsigned int  i;
//	for(i=0;i<0xffff;i++);
//		_BIS_SR(OSCOFF);
//	if(CALBC1_1MHZ==0xff||CALDCO_1MHZ==0xff){while(1);}
//	BCSCTL1=CALBC1_1MHZ;
//	DCOCTL=CALDCO_1MHZ;
//	BCSCTL2|=SELM_0+DIVM_0;
//}

void ConfigPins(){
	P1DIR|=TXD+LED+BIT6;
	P1SEL|=RXD;
	P1DIR&=~RXD;
//	P1REN|=RXD;
	P1OUT|=TXD;
	P1OUT&=~LED;
}

void send_char(unsigned char tchar){
	TA0CTL=TACLR+TASSEL_2;//清零计时器，选择SMCLK
	TA0CCR0 = BITTIME_1b;		//CCR0设为一位的宽度
	TA0CCTL0|=CCIE;		//打开CCR0中断
	bitcnt = 10;	//发送的位数，1位开始，8位数据，1位结束
	uart_buf	= 0x0100; //停止位
	uart_buf 	|=tchar;	//数据8位
	uart_buf <<=1;	//开始位
	Send_flag=0;
	TA0CTL |=MC_1; //开始TimmerA,上升模式
	_BIS_SR(GIE);
	while(!Send_flag);
	Send_flag=1;
}

void RXReady(){
	TA0CTL=TASSEL_2+MC_2+TACLR;
	TA0CCTL1=CM_2+CAP+SCS+CCIE+CCIS_0;
	rx_sign=0;
	_BIS_SR(GIE);
	while(!rx_sign){}
			rx_sign=0;
			ch=RXData0;
		//	ch='b';
}
void Send_String(char a[]){
	char i;
	send_char(0xfe);
	for(i=0;i<5;i++)send_char(a[i]);
}

void RX_String(){
	int i=0;
	for(i=0;i<3;i++){
		RXReady();
		msg[i]=RXData0;
	}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(){//发送字符
	if(bitcnt>0){
		if(uart_buf&0x01){P1OUT|=TXD;}//发送数据1
		else{ P1OUT&=~TXD;}//发送数据0
		uart_buf>>=1;
		bitcnt--;
	}
	else{
		P1OUT|=TXD;
		TA0CTL&=~MC_3;//关闭TA，当数据发送完毕
		TA0CCTL0 &=~CCIE;//关闭CCR0中断
		Send_flag=1;
	}
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(){//接收串口数据处理，利用串口协议的时间间隔
	P1OUT^=LED;
	TA0CCR1+=BITTIME_1b;//增加一位定时间隔
	if(TA0CCTL1&CAP)//判断是否为捕获模式
	{
		RXBitCnt0=0;
	}
	switch(RXBitCnt0){
	case 0:	//捕获起始位后，开始读取数据
		RXData0=0;
		TA0CCR1+=BITTIME_1b5;
		TA0CCTL1&=~CAP;//改为比较模式
		RXBitCnt0++;
		break;
	case 9://比较模式改为捕获模式
		TA0CCTL1=CAP;
		rx_sign=1;
		break;
	default:
		RXData0=RXData0>>1;//右移动一位，等待下个数据位
		if(TA0CCTL1&SCCI)RXData0|=0x80;//输入位1
//		else{RXData0&=~0x80;}
		RXBitCnt0++;
		break;
	}
}

