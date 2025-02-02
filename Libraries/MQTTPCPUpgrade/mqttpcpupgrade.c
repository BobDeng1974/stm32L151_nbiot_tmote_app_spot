/**
  *********************************************************************************************************
  * @file    mqttpcpupgrade.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-09-25
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "mqttpcpupgrade.h"
#include "platform_config.h"
#include "platform_map.h"
#include "stm32l1xx_config.h"
#include "delay.h"
#include "usart.h"
#include "hal_spiflash.h"
#include "hal_rtc.h"
#include "hal_beep.h"
#include "hal_iwdg.h"
#include "radio_rf_app.h"
#include "radio_hal_rf.h"

static void MqttSNSTMFLASH_ReadBuffer(uint32_t addr, uint8_t *buf, uint32_t length)
{
	while (length--) {
		*buf++ = *(__IO uint8_t *)addr++;
	}
}

u8 MqttSNCalculateSumCheckCode(u32 regCode, uint8_t* buf, uint32_t length)
{
	u32 sumCheckCode = regCode;
	
	while (length--) {
		sumCheckCode += *buf++;
	}
	
	sumCheckCode %= 0xFF;
	
	return sumCheckCode;
}

u8 MqttSNCalculateStringToHex(u8 HighChar, u8 LowChar)
{
	u8 val = 0;
	
	if ((HighChar >= '0') && (HighChar <= '9')) {
		val |= ((HighChar - '0') << 4);
	}
	else if ((HighChar >= 'A') && (HighChar <= 'F')) {
		val |= ((HighChar - 'A' + 10) << 4);
	}
	else if ((HighChar >= 'a') && (HighChar <= 'f')) {
		val |= ((HighChar - 'a' + 10) << 4);
	}
	
	if ((LowChar >= '0') && (LowChar <= '9')) {
		val |= (LowChar - '0');
	}
	else if ((LowChar >= 'A') && (LowChar <= 'F')) {
		val |= (LowChar - 'A' + 10);
	}
	else if ((LowChar >= 'a') && (LowChar <= 'f')) {
		val |= (LowChar - 'a' + 10);
	}
	
	return val;
}

/**********************************************************************************************************
 @Function			MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_BackupCurrentAPP(MqttSNPCP_ClientsTypeDef* pClient)
 @Description			MqttPCP_Upgrade_BackupCurrentAPP		: PCP升级备份当前APP
 @Input				pClient							: PCP客户端实例
 @Return				void
**********************************************************************************************************/
MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_BackupCurrentAPP(MqttSNPCP_ClientsTypeDef* pClient)
{
#ifdef GD25Q_80CSIG
	MqttSNPCP_ResultCodeTypeDef PCPResultCodeStatus = MQTTSN_PCP_ExecuteSuccess;
	u8 STMFlashCheckCode = 0;
	u8 SPIFlashCheckCode = 0;
	int BackupTimes = 3;
	
	MQTTSN_PCP_DEBUG_LOG_PRINTF("Backup APP ...");
	Radio_Rf_Interrupt_Deinit();
	GD25Q_SPIFLASH_WakeUp();
	GD25Q_SPIFLASH_Init();
	
	if (GD25Q80CSIG_OK != GD25Q_SPIFLASH_Get_Status()) {
		GD25Q_SPIFLASH_PowerDown();
		PCPResultCodeStatus = MQTTSN_PCP_InternalAnomaly;
		goto exit;
	}
	
#if UPGRADE_BACKUP_APP_WRITE_TYPE == UPGRADE_BACKUP_APP_WRITE_DISABLE
	if (GD25Q_SPIFLASH_GetByte(APP2_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
		if (GD25Q_SPIFLASH_GetWord(APP2_INFO_UPGRADE_SOFTVER_OFFSET) == ((SOFTWAREMAJOR<<16)|(SOFTWARESUB<<0))) {
			/* 备份区已有当前版本APP */
			GD25Q_SPIFLASH_PowerDown();
			MQTTSN_PCP_DEBUG_LOG_PRINTF("APP has been backed");
			PCPResultCodeStatus = MQTTSN_PCP_LatestVersion;
			goto exit;
		}
	}
#endif
	
	/* 备份区没有当前APP或APP版本不同 */
	do {
		IWDG_Feed();
		/* 擦除APP2区 */
		GD25Q_SPIFLASH_EraseBlock(APP2_BASE_ADDR + 0 * GD25Q80_BLOCK_BYTE_SIZE);
		GD25Q_SPIFLASH_EraseBlock(APP2_BASE_ADDR + 1 * GD25Q80_BLOCK_BYTE_SIZE);
		GD25Q_SPIFLASH_EraseBlock(APP2_BASE_ADDR + 2 * GD25Q80_BLOCK_BYTE_SIZE);
		GD25Q_SPIFLASH_EraseBlock(APP2_BASE_ADDR + 3 * GD25Q80_BLOCK_BYTE_SIZE);
		/* 写入APP2DATA */
		for (int packIndex = 0; packIndex < 228; packIndex++) {
			MqttSNSTMFLASH_ReadBuffer(APP_LOWEST_ADDRESS + packIndex * 512, pClient->DataProcessStack, 512);
			GD25Q_SPIFLASH_WriteBuffer(pClient->DataProcessStack, APP2_DATA_ADDR + packIndex * 512, 512);
			STMFlashCheckCode = CalculateSumCheckCode(STMFlashCheckCode, pClient->DataProcessStack, 512);
		}
		/* 校验APP2DATA */
		for (int packIndex = 0; packIndex < 228; packIndex++) {
			GD25Q_SPIFLASH_ReadBuffer(pClient->DataProcessStack, APP2_DATA_ADDR + packIndex * 512, 512);
			SPIFlashCheckCode = CalculateSumCheckCode(SPIFlashCheckCode, pClient->DataProcessStack, 512);
		}
		BackupTimes--;
	} while ((STMFlashCheckCode != SPIFlashCheckCode) && (BackupTimes > 0));
	
	if (STMFlashCheckCode != SPIFlashCheckCode) {
		GD25Q_SPIFLASH_PowerDown();
		MQTTSN_PCP_DEBUG_LOG_PRINTF("APP backup up fail");
		goto exit;
	}
	
	/* 写入APP2INFO */
	GD25Q_SPIFLASH_SetByte(APP2_INFO_UPGRADE_STATUS_OFFSET, 0x55);										//标识升级包
	GD25Q_SPIFLASH_SetWord(APP2_INFO_UPGRADE_BASEADDR_OFFSET, APP2_DATA_ADDR);								//升级包基地址
	GD25Q_SPIFLASH_SetHalfWord(APP2_INFO_UPGRADE_BLOCKNUM_OFFSET, 228);									//升级包块数
	GD25Q_SPIFLASH_SetHalfWord(APP2_INFO_UPGRADE_BLOCKLEN_OFFSET, 512);									//升级包块长度
	GD25Q_SPIFLASH_SetHalfWord(APP2_INFO_UPGRADE_DATALEN_OFFSET, 512);									//升级包块有效数据长度
	
	GD25Q_SPIFLASH_SetWord(APP2_INFO_UPGRADE_SOFTVER_OFFSET, ((SOFTWAREMAJOR<<16)|(SOFTWARESUB<<0)));			//升级包版本号
	GD25Q_SPIFLASH_SetWord(APP2_INFO_DOWNLOAD_TIME_OFFSET, RTC_GetUnixTimeToStamp());						//升级包下载时间
	GD25Q_SPIFLASH_SetWord(APP2_DATA_CHECK_CODE_OFFSET, SPIFlashCheckCode);
	
	GD25Q_SPIFLASH_PowerDown();
	MQTTSN_PCP_DEBUG_LOG_PRINTF("APP backup over code %X", STMFlashCheckCode);
	
exit:
	return PCPResultCodeStatus;
#endif
}

/**********************************************************************************************************
 @Function			MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_NewVersionNotice(MqttSNPCP_ClientsTypeDef* pClient)
 @Description			MqttPCP_Upgrade_NewVersionNotice		: PCP升级新版本通知处理
 @Input				pClient							: PCP客户端实例
 @Return				void
**********************************************************************************************************/
MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_NewVersionNotice(MqttSNPCP_ClientsTypeDef* pClient)
{
#ifdef GD25Q_80CSIG
	MqttSNPCP_ResultCodeTypeDef PCPResultCodeStatus = MQTTSN_PCP_ExecuteSuccess;
	u32 MajorVer = 0, SubVer = 0;
	
	MQTTSN_PCP_DEBUG_LOG_PRINTF("NewVer APP ...");
	
	/* 信号质量与信噪比低中断升级 */
	if ((TCFG_Utility_Get_Nbiot_Rssi_IntVal() < UPGRADE_LOW_LIMIT_RSSI) || (TCFG_Utility_Get_Nbiot_RadioSNR() < UPGRADE_LOW_LIMIT_SNR)) {
		MQTTSN_PCP_DEBUG_LOG_PRINTF("Signal Difference");
		PCPResultCodeStatus = MQTTSN_PCP_SignalqualityDifference;
		goto exit;
	}
	
	/* 升级前备份当前APP */
	MqttPCP_Upgrade_BackupCurrentAPP(pClient);
	
	Radio_Rf_Interrupt_Deinit();
	GD25Q_SPIFLASH_WakeUp();
	GD25Q_SPIFLASH_Init();
	
	if (GD25Q80CSIG_OK != GD25Q_SPIFLASH_Get_Status()) {
		GD25Q_SPIFLASH_PowerDown();
		PCPResultCodeStatus = MQTTSN_PCP_InternalAnomaly;
		goto exit;
	}
	
	if (sscanf((const char*)pClient->Parameter.PlatformSoftVersion, "V%d.%d", &MajorVer, &SubVer) <= 0) {
		PCPResultCodeStatus = MQTTSN_PCP_InternalAnomaly;
		goto exit;
	}
	if (GD25Q_SPIFLASH_GetWord(APP1_INFO_UPGRADE_SOFTVER_OFFSET) == ((MajorVer<<16)|(SubVer<<0))) {
		if (GD25Q_SPIFLASH_GetByte(APP1_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
			/* 备份区已有当前升级版本APP */
			GD25Q_SPIFLASH_PowerDown();
			MQTTSN_PCP_DEBUG_LOG_PRINTF("APP has been latestVer");
			PCPResultCodeStatus = MQTTSN_PCP_LatestVersion;
			goto exit;
		}
		else {
			/* 备份区已有该APP正在升级 */
			/* 分片序号调至未下载数据包,实现断点续传 */
			pClient->UpgradeExecution.PackSliceIndex += GD25Q_SPIFLASH_GetNumofByte(APP1_PACKSLICE_STATUS_OFFSET, APP_PACKSLICE_NUM, 0x00);
			if (pClient->Parameter.UpgradePackSliceNum <= pClient->UpgradeExecution.PackSliceIndex) {
				pClient->UpgradeExecution.PackSliceIndex = pClient->Parameter.UpgradePackSliceNum - 1;
			}
			GD25Q_SPIFLASH_PowerDown();
			MQTTSN_PCP_DEBUG_LOG_PRINTF("APP Upgradeing");
			PCPResultCodeStatus = MQTTSN_PCP_ExecuteSuccess;
			goto exit;
		}
	}
	
	/* 备份区没有当前升级APP或APP版本不同 */
	/* 擦除APP1区 */
	GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 0 * GD25Q80_BLOCK_BYTE_SIZE);
	GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 1 * GD25Q80_BLOCK_BYTE_SIZE);
	GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 2 * GD25Q80_BLOCK_BYTE_SIZE);
	GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 3 * GD25Q80_BLOCK_BYTE_SIZE);
	/* 写入APP1INFO */
	GD25Q_SPIFLASH_SetWord(APP1_INFO_UPGRADE_BASEADDR_OFFSET, APP1_DATA_ADDR);								//升级包基地址
	GD25Q_SPIFLASH_SetHalfWord(APP1_INFO_UPGRADE_BLOCKNUM_OFFSET, pClient->Parameter.UpgradePackSliceNum);		//升级包块数
	GD25Q_SPIFLASH_SetHalfWord(APP1_INFO_UPGRADE_BLOCKLEN_OFFSET, UPGRADE_PACK_SLICE_BLOCK_SIZE);				//升级包块长度
	GD25Q_SPIFLASH_SetHalfWord(APP1_INFO_UPGRADE_DATALEN_OFFSET, pClient->Parameter.UpgradePackSliceSize);		//升级包块有效数据长度
	
	GD25Q_SPIFLASH_SetWord(APP1_INFO_UPGRADE_SOFTVER_OFFSET, ((MajorVer<<16)|(SubVer<<0)));					//升级包版本号
	GD25Q_SPIFLASH_SetWord(APP1_INFO_DOWNLOAD_TIME_OFFSET, RTC_GetUnixTimeToStamp());						//升级包下载时间
	GD25Q_SPIFLASH_SetWord(APP1_DATA_CHECK_CODE_OFFSET, CalculateStringToHex(pClient->Parameter.UpgradePackCheckCode>>8, pClient->Parameter.UpgradePackCheckCode&0xFF));
	
	GD25Q_SPIFLASH_PowerDown();
	MQTTSN_PCP_DEBUG_LOG_PRINTF("APP will start upgrade");
	
exit:
	return PCPResultCodeStatus;
#endif
}

/**********************************************************************************************************
 @Function			MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_DataDownload(MqttSNPCP_ClientsTypeDef* pClient, u16 SliceIndex, u8* UpgradeData, u16 UpgradeDataLength)
 @Description			MqttPCP_Upgrade_DataDownload			: PCP升级包下载处理
 @Input				pClient							: PCP客户端实例
					SliceIndex						: PCP分片序号
					UpgradeData						: 升级包数据
					UpgradeDataLength					: 升级包长度
 @Return				void
**********************************************************************************************************/
MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_DataDownload(MqttSNPCP_ClientsTypeDef* pClient, u16 SliceIndex, u8* UpgradeData, u16 UpgradeDataLength)
{
#ifdef GD25Q_80CSIG
	MqttSNPCP_ResultCodeTypeDef PCPResultCodeStatus = MQTTSN_PCP_ExecuteSuccess;
	
	Radio_Rf_Interrupt_Deinit();
	GD25Q_SPIFLASH_WakeUp();
	GD25Q_SPIFLASH_Init();
	
	if (GD25Q80CSIG_OK != GD25Q_SPIFLASH_Get_Status()) {
		GD25Q_SPIFLASH_PowerDown();
		PCPResultCodeStatus = MQTTSN_PCP_InternalAnomaly;
		goto exit;
	}
	
	if ((SliceIndex + 1) == pClient->UpgradeExecution.PackSliceNum) {
		/* 该分片为最后一包分片获取其长度 */
		pClient->UpgradeExecution.PackLastSliceSize = UpgradeDataLength;
	}
	
	if (GD25Q_SPIFLASH_GetByte(APP1_PACKSLICE_STATUS_OFFSET + SliceIndex) != 0xFF) {
		/* 该分片数据已写入 */
		pClient->UpgradeExecution.PackSliceIndex = SliceIndex + 1;
		GD25Q_SPIFLASH_PowerDown();
		MQTTSN_PCP_DEBUG_LOG_PRINTF("Slice has been write");
		goto exit;
	}
	
	if (UpgradeDataLength > pClient->UpgradeExecution.PackSliceSize) {
		/* 该分片数据长度异常 */
		GD25Q_SPIFLASH_PowerDown();
		MQTTSN_PCP_DEBUG_LOG_PRINTF("Slice Size Fail");
		goto exit;
	}
	
	/* 分片数据写入分片地址 */
	/* 写入APP1DATA */
	GD25Q_SPIFLASH_WriteBuffer(UpgradeData, APP1_DATA_ADDR + SliceIndex * UPGRADE_PACK_SLICE_BLOCK_SIZE, UpgradeDataLength);
	GD25Q_SPIFLASH_SetByte(APP1_PACKSLICE_STATUS_OFFSET + SliceIndex, 0x00);
	
	pClient->UpgradeExecution.PackSliceIndex = SliceIndex + 1;
	GD25Q_SPIFLASH_PowerDown();
	MQTTSN_PCP_DEBUG_LOG_PRINTF("Slice write to flash");
	
exit:
	return PCPResultCodeStatus;
#endif
}

/**********************************************************************************************************
 @Function			MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_DataAssemble(MqttSNPCP_ClientsTypeDef* pClient)
 @Description			MqttPCP_Upgrade_DataAssemble			: PCP升级包组装校验处理
 @Input				pClient							: PCP客户端实例
 @Return				void
**********************************************************************************************************/
MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_DataAssemble(MqttSNPCP_ClientsTypeDef* pClient)
{
#ifdef GD25Q_80CSIG
	MqttSNPCP_ResultCodeTypeDef PCPResultCodeStatus = MQTTSN_PCP_ExecuteSuccess;
	u8 SPIFlashCheckCode = 0;
	
	Radio_Rf_Interrupt_Deinit();
	GD25Q_SPIFLASH_WakeUp();
	GD25Q_SPIFLASH_Init();
	
	if (GD25Q80CSIG_OK != GD25Q_SPIFLASH_Get_Status()) {
		GD25Q_SPIFLASH_PowerDown();
		PCPResultCodeStatus = MQTTSN_PCP_InternalAnomaly;
		goto exit;
	}
	
	/* 校验数据包是否下载完成 */
	if (pClient->UpgradeExecution.PackSliceNum != GD25Q_SPIFLASH_GetNumofByte(APP1_PACKSLICE_STATUS_OFFSET, pClient->UpgradeExecution.PackSliceNum, 0x00)) {
		/* 数据包没有下载完成 */
		GD25Q_SPIFLASH_EraseSector(APP1_INFORMATION_ADDR);
		GD25Q_SPIFLASH_PowerDown();
		MQTTSN_PCP_DEBUG_LOG_PRINTF("Upgrade Check Fail");
		PCPResultCodeStatus = MQTTSN_PCP_UpgradePacketCheckFail;
		goto exit;
	}
	
	/* 校验升级包数据 */
	for (int packIndex = 0; packIndex < (pClient->UpgradeExecution.PackSliceNum - 1); packIndex++) {
		GD25Q_SPIFLASH_ReadBuffer(pClient->DataProcessStack, APP1_DATA_ADDR + packIndex * UPGRADE_PACK_SLICE_BLOCK_SIZE, pClient->UpgradeExecution.PackSliceSize);
		SPIFlashCheckCode = CalculateSumCheckCode(SPIFlashCheckCode, pClient->DataProcessStack, pClient->UpgradeExecution.PackSliceSize);
	}
	GD25Q_SPIFLASH_ReadBuffer(pClient->DataProcessStack, APP1_DATA_ADDR + ((pClient->UpgradeExecution.PackSliceNum - 1) * UPGRADE_PACK_SLICE_BLOCK_SIZE), pClient->UpgradeExecution.PackLastSliceSize);
	SPIFlashCheckCode = CalculateSumCheckCode(SPIFlashCheckCode, pClient->DataProcessStack, pClient->UpgradeExecution.PackLastSliceSize);
	if (GD25Q_SPIFLASH_GetWord(APP1_DATA_CHECK_CODE_OFFSET) != SPIFlashCheckCode) {
		/* 校验码错误 */
		GD25Q_SPIFLASH_EraseSector(APP1_INFORMATION_ADDR);
		GD25Q_SPIFLASH_PowerDown();
		MQTTSN_PCP_DEBUG_LOG_PRINTF("Upgrade Check Fail");
		PCPResultCodeStatus = MQTTSN_PCP_UpgradePacketCheckFail;
		goto exit;
	}
	
	GD25Q_SPIFLASH_PowerDown();
	MQTTSN_PCP_DEBUG_LOG_PRINTF("Upgrade Check Ok");
	
exit:
	return PCPResultCodeStatus;
#endif
}

/**********************************************************************************************************
 @Function			MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_AfterUpdata(MqttSNPCP_ClientsTypeDef* pClient)
 @Description			MqttPCP_Upgrade_AfterUpdata			: PCP升级包开始升级处理
 @Input				pClient							: PCP客户端实例
 @Return				void
**********************************************************************************************************/
MqttSNPCP_ResultCodeTypeDef MqttPCP_Upgrade_AfterUpdata(MqttSNPCP_ClientsTypeDef* pClient)
{
#ifdef GD25Q_80CSIG
	MqttSNPCP_ResultCodeTypeDef PCPResultCodeStatus = MQTTSN_PCP_ExecuteSuccess;
	
	MQTTSN_PCP_DEBUG_LOG_PRINTF("Start Btup APP ...");
	Radio_Rf_Interrupt_Deinit();
	GD25Q_SPIFLASH_WakeUp();
	GD25Q_SPIFLASH_Init();
	
	if (GD25Q80CSIG_OK != GD25Q_SPIFLASH_Get_Status()) {
		GD25Q_SPIFLASH_PowerDown();
		PCPResultCodeStatus = MQTTSN_PCP_InternalAnomaly;
		goto exit;
	}
	
	if (GD25Q_SPIFLASH_GetByte(APP1_INFO_UPGRADE_STATUS_OFFSET) == 0xFF) {
		GD25Q_SPIFLASH_SetByte(APP1_INFO_UPGRADE_STATUS_OFFSET, 0x55);									//标识有升级包且可升级
	}
	
	TCFG_EEPROM_SetBootMode(TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE);										//设置升级模式
	BEEP_CtrlRepeat_Extend(5, 50, 50);
	Stm32_System_Software_Reboot(RBTMODE_MQTT_UPGRADE);
	
exit:
	return PCPResultCodeStatus;
#endif
}

/********************************************** END OF FLEE **********************************************/
