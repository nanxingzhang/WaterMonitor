#include<msp430f5529.h>


#define RXD BIT2
#define TXD BIT3
#define LED BIT0

int BITTIME_1b=(4000000/9600);
int BITTIME_1b5=(4000000/(9600*2));

 char bitcnt=0;//����
unsigned int  uart_buf;

char RXData0=0;//����������ݵ�8λ
char RXBitCnt0;//��������λ
char rx_sign=0;

char msg[32]="hello";		//���յ��ַ�������
char ch;
volatile int Send_flag=0;

void FaultRoutine(){
	while(1);//�쳣����
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
	TA0CTL=TACLR+TASSEL_2;//�����ʱ����ѡ��SMCLK
	TA0CCR0 = BITTIME_1b;		//CCR0��Ϊһλ�Ŀ��
	TA0CCTL0|=CCIE;		//��CCR0�ж�
	bitcnt = 10;	//���͵�λ����1λ��ʼ��8λ���ݣ�1λ����
	uart_buf	= 0x0100; //ֹͣλ
	uart_buf 	|=tchar;	//����8λ
	uart_buf <<=1;	//��ʼλ
	Send_flag=0;
	TA0CTL |=MC_1; //��ʼTimmerA,����ģʽ
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
__interrupt void Timer_A0(){//�����ַ�
	if(bitcnt>0){
		if(uart_buf&0x01){P1OUT|=TXD;}//��������1
		else{ P1OUT&=~TXD;}//��������0
		uart_buf>>=1;
		bitcnt--;
	}
	else{
		P1OUT|=TXD;
		TA0CTL&=~MC_3;//�ر�TA�������ݷ������
		TA0CCTL0 &=~CCIE;//�ر�CCR0�ж�
		Send_flag=1;
	}
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(){//���մ������ݴ������ô���Э���ʱ����
	P1OUT^=LED;
	TA0CCR1+=BITTIME_1b;//����һλ��ʱ���
	if(TA0CCTL1&CAP)//�ж��Ƿ�Ϊ����ģʽ
	{
		RXBitCnt0=0;
	}
	switch(RXBitCnt0){
	case 0:	//������ʼλ�󣬿�ʼ��ȡ����
		RXData0=0;
		TA0CCR1+=BITTIME_1b5;
		TA0CCTL1&=~CAP;//��Ϊ�Ƚ�ģʽ
		RXBitCnt0++;
		break;
	case 9://�Ƚ�ģʽ��Ϊ����ģʽ
		TA0CCTL1=CAP;
		rx_sign=1;
		break;
	default:
		RXData0=RXData0>>1;//���ƶ�һλ���ȴ��¸�����λ
		if(TA0CCTL1&SCCI)RXData0|=0x80;//����λ1
//		else{RXData0&=~0x80;}
		RXBitCnt0++;
		break;
	}
}

