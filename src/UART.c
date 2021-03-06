////利用定时器A 作串行口波特率发生器用,利用捕捉比较功能实现异步串行通信。
////芯片型号：MSP430FG439           P1.0---TXD   P1.1---RXD
////Timer_A TACLK=ACLK
////波特率为 2400BIT/S TBIT1=14 TBIT0_5=6
////帧格式：(0)XXXXXXXX(1),0为起始位，1为结束位，XXXXXXXXX为8位数据
//#include  <msp430f5529.h>
//#define TBIT1 14;                      //TBIT1 为1 位时间
//#define TBIT0_5 6;                    //TBIT0_5 为半位时间
//#define TXD BIT2                      //使用P1.2作为发送，特殊功能脚，用CCI0A做比较输出
//#define RXD BIT3                      //使用P1.3作为接收，特殊功能脚，用CCI0B做捕获输入
//unsigned int TR_COUNT;                 //发收计数器
//unsigned int T_DATA=0x00;              //发送缓冲器
//unsigned int R_DATA=0x00;             //接收缓冲器
//
//
//// ******************************************************
//// 主函数
//// *****************************************************
////main()
////{
////UART_init();
////	txd(0XFF);//由于发的第一帧会有错，所以先发送无用帧
////	for(int i=0;i<255;i++)//发送0~255的数据
////		  txd(i);
////	while(1)
////	{
////		   rxd();                                 //准备接收
////		   LPM3;                               //进入休眠状态，收到数据后在唤醒
////		   txd(R_DATA);                 //把收到的数据重发
////	}
////}
//
//
//
//
//// ******************************************************
//// 初始化函数
//// *****************************************************
//void UART_init(void)
//{
//    P1DIR |= TXD;                                                 //TXD管脚为输出
//    P1OUT=0x00;
//    P1SEL |= (RXD+TXD);                                      //声明RXD和TXD都为特殊功能脚
//    TA0CCTL0|=OUT;                                                  //CCR0    OUT 设1
//    TA0CTL|=TASSEL_1+MC_2+TAIE;                          //设定时器A 时钟源ACLK，设定时器为连续模式
//    _EINT();                                                            //开中断允许
//}
////******************************************************
////发送一字节数据子程序
////输入参量:unsigned char 类型字节
//// *****************************************************
//void txd(unsigned char byte)
//{
//    T_DATA=byte;           //关键点之一：这里与其它MSP430的软串口例程不同
//    TA0CCR0=TA0R;                        //将TAR 时间存入CCR0,确定第一位 长度。
//    TA0CCR0=TA0CCR0+TBIT1;         //将每1 位时间周期加入CCR0。
//    //uart帧格式：(0)xxxxxxxx(1)
//    T_DATA=T_DATA<<1;         //左移一位
//    T_DATA|=BIT0;                      //最后一位为1
//    TR_COUNT=10;                     //发送计数器。
//    TA0CCTL0=OUTMOD0+CCIE+OUTMOD2;              //重新设置CCTL0(CCIS1-0=00)
//                                                                                     //捕获/比较模块输出模式1,充许模块中断。
//    while(CCIE&TA0CCTL0);               //等待CCIE 是否为0?为0 则表示发送完数据。
//}
//// *****************************************************
////接收准备子程序
////依赖TA0 中断来接收一字节数据。
//// *****************************************************
//void rxd(void)
//{
//    TR_COUNT=8;                             //接收数据位 位数
//    //关键点之一：其它MSP430的软串口都是用下降沿(CM1)，实践中我发现接收的问题就出在这里，所以我用CM0上升沿
//    TA0CCTL0 = SCS + CCIS0 + OUTMOD0 + CM1 + CAP + CCIE;
//    // 比较捕获为输出模式+比较捕获模块为中断允许+"上升沿捕获"+设置为捕获模式
//    //+选择CCI0B 为捕获源+同步捕获
//}
////*******************************************************************************
//#pragma vector=TIMER0_A0_VECTOR       //TIMER_A0 中断函数
//__interrupt void cc10int(void)
//{
//    TA0CCR0=TA0CCR0+TBIT1;                   //重装下一位时间(当前时间+1 位时间)
//    //---------------------------接收处理程序段
//    if(TA0CCTL0 & CCIS0)                    //是处于接收中还是发送中?
//    {
//        if(TA0CCTL0&CAP)                   //是捕获模式还是比较模式?
//        {
//            TA0CCTL0&=~CAP;                //是-开始捕获,将捕获功能改为比较功能
//            TA0CCR0=TA0CCR0+TBIT0_5;           //开始捕获位再加半位时间
//        }
//        else
//        {
//            R_DATA=R_DATA>>1;            //处于比较功能,将前面 那位向低位移.
//            if(TA0CCTL0&SCCI)                       //这句等效于(P1IN&RXD)==1，如果RXD管脚是高电平
//            {
//               R_DATA|=BIT7;                   //则R_DATA的最高位置1
//            }
//            TR_COUNT--;                 //计数器减1
//            if(TR_COUNT==0)              //是否接收完8 位?
//            {
//                R_DATA=R_DATA;      //关键点之一，这里也要用255减一次
//                //*****************************
//                TA0CCTL0&=~CCIE;           //是接收完,捕获/ 比较块停止中断充许
//                LPM3_EXIT;             //退出低功率模式(一般,在进入LPM3 时才使用)
//            }
//        }
//    }                              //接收结束
//    //----------------------------------------------------------------
//    else                                //开始发送程序段
//    {
//        if(TR_COUNT==0)
//        TA0CCTL0&=~CCIE;                //关捕获/比较块中断,发送结束.
//        else
//        {
//            if(T_DATA&0x0001)           //状态寄存器C 位是1,还是0?
//                TA0CCTL0&=~OUTMOD2;         //状态寄存器C 位为0,发送0.
//            else
//                TA0CCTL0|=OUTMOD2;           //状态寄存器C 位为1,发送1.
//            T_DATA=T_DATA>>1;             //将字节数据向右移一位
//            --TR_COUNT;                 //位计数器减1.
//        }
//    }
//}







