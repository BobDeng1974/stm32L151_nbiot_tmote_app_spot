/**
  *********************************************************************************************************
  * @file    dnsconfig.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-05-15
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "dnsconfig.h"
#include "dnsfunc.h"
#include "dnstransport.h"

unsigned char DNS_SendBuf[DNS_BUFFER_SIZE];
unsigned char DNS_RecvBuf[DNS_BUFFER_SIZE];
unsigned char DNS_DataStack[DNS_DATASTACK_SIZE];

/**********************************************************************************************************
 @Function			void DNS_Client_Init(DNS_ClientsTypeDef* pClient, DNS_SocketNetTypeDef* NetSock)
 @Description			DNS_Client_Init						: 初始化DNS客户端
 @Input				pClient								: DNS客户端实例
					NetSock								: DNS Socket 协议栈
 @Return				void
**********************************************************************************************************/
void DNS_Client_Init(DNS_ClientsTypeDef* pClient, DNS_SocketNetTypeDef* NetSock)
{
	pClient->Sendbuf									= DNS_SendBuf;
	pClient->Recvbuf									= DNS_RecvBuf;
	pClient->Sendbuf_size								= sizeof(DNS_SendBuf);
	pClient->Recvbuf_size								= sizeof(DNS_RecvBuf);
	pClient->Sendlen									= 0;
	pClient->Recvlen									= 0;
	pClient->DataProcessStack							= DNS_DataStack;
	pClient->DataProcessStack_size						= sizeof(DNS_DataStack);
	
	pClient->Command_Timeout_Sec							= DNS_COMMAND_TIMEOUT_SEC;
	pClient->Command_Failure_Cnt							= DNS_COMMAND_FAILURE_CNT;
	
	pClient->LetterCounter								= 0;
	
	pClient->AnalysisTick								= 0;
	pClient->AnalysisData[0].hostnameAddr					= (unsigned char*)DNS_ANALYSIS_HOSTNAME1;
	pClient->AnalysisData[1].hostnameAddr					= (unsigned char*)DNS_ANALYSIS_HOSTNAME2;
	pClient->AnalysisData[2].hostnameAddr					= (unsigned char*)DNS_ANALYSIS_HOSTNAME3;
	for (unsigned char i = 0; i < DNS_ANALYSIS_DATA; i++) {
		sprintf((char *)pClient->AnalysisData[i].hostname, "%s", pClient->AnalysisData[i].hostnameAddr);
	}
	
	
	
	
	pClient->ProcessState								= DNS_PROCESS_CREAT_UDP_SOCKET;
	pClient->SocketStack								= NetSock;
}










/********************************************** END OF FLEE **********************************************/
