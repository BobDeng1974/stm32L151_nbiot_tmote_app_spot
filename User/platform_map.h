#ifndef __PLATFORM_MAP_H
#define   __PLATFORM_MAP_H

#include "sys.h"
#include "platform_config.h"

#define APP_LOWEST_ADDRESS				0x08003800
#define APP_LOWEST_SIZE					0x0001C800

#define TCFG_ENV_BOOTMODE_TOUPDATE			1
#define TCFG_ENV_BOOTMODE_NORMAL			2
#define TCFG_ENV_BOOTMODE_UPDATING			3
#define TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE	4

#define TCFG_FLAGTYPE_GENERAL				0
#define TCFG_FLAGTYPE_MAGAlGORITHM			1
#define TCFG_FLAGTYPE_SECU				2

#define TCFG_X_AXIS						0
#define TCFG_Y_AXIS						1
#define TCFG_Z_AXIS						2

#define EEPROM_BASE_ADDRESS				0x08080000
#define EEPROM_CONFIG_OFFSET				0x08080000
#define EEPROM_CONFIG_SIZE				0x0400

#define TCFG_FACTORY_VENDER_OFFSET			0x0C00
#define TCFG_FACTORY_VENDER_LENGTH			4

#define TCFG_FACTORY_MAC_SN_OFFSET			0x0C04
#define TCFG_FACTORY_MAC_SN_LENGTH			4

#define EEPROM_CONFIG_PAGE1_ADDRESS		0x08080400										//配置页1起始地址 EEPROM_BASE_ADD + 0x0400(1K)
#define EEPROM_CONFIG_PAGE1_SIZE			0x0800											//配置页1大小     0x0800(2K)

#define TCFG_FACTORY_BRAND_SN_OFFSET		0x0400											//0x08080400
#define TCFG_FACTORY_BRAND_SN_LENGTH		8												//Brand SN	4:Brand+4:SN

/**************************** The environment parameters are used both by bootLoader and application *****************************/
#define TCFG_ENVFLAG_OFFSET				TCFG_FACTORY_BRAND_SN_OFFSET + TCFG_FACTORY_BRAND_SN_LENGTH	//0x08080408
#define TCFG_ENVFLAG_LENGTH				4												//"TCLD"
#define TCFG_ENV_BOOTMODE_OFFSET			TCFG_ENVFLAG_OFFSET + TCFG_ENVFLAG_LENGTH				//0x0808040C
#define TCFG_ENV_BOOTMODE_LENGTH			1												//boot app from flash or load app from air
/************************************************************** End **************************************************************/

#define TCFG_HEADFLAG_OFFSET				TCFG_ENV_BOOTMODE_OFFSET + TCFG_ENV_BOOTMODE_LENGTH		//0x0808040D
#define TCFG_HEADFLAG_LENGTH				4												//"TCLD"				状态码
#define TCFG_SN_OFFSET					TCFG_HEADFLAG_OFFSET + TCFG_HEADFLAG_LENGTH				//0x08080411
#define TCFG_SN_LENGTH					4												//SN					SN号
#define TCFG_SPOTID_OFFSET				TCFG_SN_OFFSET + TCFG_SN_LENGTH						//0x08080415
#define TCFG_SPOTID_LENGTH				16												//SPOTID				车位ID
#define TCFG_HEARTINTERVAL_OFFSET			TCFG_SPOTID_OFFSET + TCFG_SPOTID_LENGTH					//0x08080425
#define TCFG_HEARTINTERVAL_LENGTH			2												//Heart Interval		心跳间隔时间
#define TCFG_MAG_SENSITIVITY_OFFSET		TCFG_HEARTINTERVAL_OFFSET + TCFG_HEARTINTERVAL_LENGTH		//0x08080427
#define TCFG_MAG_SENSITIVITY_LENGTH		1												//Sensitivity			传感器灵敏度
#define TCFG_BOOT_VERSION_OFFSET			TCFG_MAG_SENSITIVITY_OFFSET + TCFG_MAG_SENSITIVITY_LENGTH	//0x08080428
#define TCFG_BOOT_VERSION_LENGTH			1												//BootVersion			BOOT版本号

#define TCFG_MAGFLAG_OFFSET				TCFG_BOOT_VERSION_OFFSET + TCFG_BOOT_VERSION_LENGTH		//0x08080429
#define TCFG_MAGFLAG_LENGTH				1												//'T' = 0x54			状态码
#define TCFG_MAG_BACK_X_OFFSET			TCFG_MAGFLAG_OFFSET + TCFG_MAGFLAG_LENGTH				//0x0808042A
#define TCFG_MAG_BACK_X_LENGTH			2												//Mag X Back			地磁X背景值
#define TCFG_MAG_BACK_Y_OFFSET			TCFG_MAG_BACK_X_OFFSET + TCFG_MAG_BACK_X_LENGTH			//0x0808042C
#define TCFG_MAG_BACK_Y_LENGTH			2												//Mag Y Back			地磁Y背景值
#define TCFG_MAG_BACK_Z_OFFSET			TCFG_MAG_BACK_Y_OFFSET + TCFG_MAG_BACK_Y_LENGTH			//0x0808042E
#define TCFG_MAG_BACK_Z_LENGTH			2												//Mag Z Back			地磁Z背景值

#define TCFG_SECUFLAG_OFFSET				TCFG_MAG_BACK_Z_OFFSET + TCFG_MAG_BACK_Z_LENGTH			//0x08080430
#define TCFG_SECUFLAG_LENGTH				1												//'T' = 0x54			状态码
#define TCFG_SECU_BRAND_OFFSET			TCFG_SECUFLAG_OFFSET + TCFG_SECUFLAG_LENGTH				//0x08080431
#define TCFG_SECU_BRAND_LENGTH			6												//BrandCode			生产码
#define TCFG_SECU_BRANDKEY_OFFSET			TCFG_SECU_BRAND_OFFSET + TCFG_SECU_BRAND_LENGTH			//0x08080437
#define TCFG_SECU_BRANDKEY_LENGTH			32												//Reserved			未使用
#define TCFG_SECU_BRANCHKEY_OFFSET			TCFG_SECU_BRANDKEY_OFFSET + TCFG_SECU_BRANDKEY_LENGTH		//0x08080457
#define TCFG_SECU_BRANCHKEY_LENGTH			32												//Reserved			未使用

#define TCFG_RECORD_RUNTIME_OFFSET			TCFG_SECU_BRANCHKEY_OFFSET + TCFG_SECU_BRANCHKEY_LENGTH	//0x08080477
#define TCFG_RECORD_RUNTIME_LENGTH			4												//Reserved			运行时间标志(App运行时间)

#define TCFG_RECORD_BOOTCNT_OFFSET			TCFG_RECORD_RUNTIME_OFFSET + TCFG_RECORD_RUNTIME_LENGTH	//0x0808047B
#define TCFG_RECORD_BOOTCNT_LENGTH			1												//BootCnt				正常运行标志(Boot启动次数)

#define TCFG_APP_ENV0_OFFSET				TCFG_RECORD_BOOTCNT_OFFSET + TCFG_RECORD_BOOTCNT_LENGTH	//0x0808047C	偏移地址
#define TCFG_APP_ENV0_ADDRESS				EEPROM_BASE_ADDRESS + TCFG_APP_ENV0_OFFSET				//0x0808047C	绝对地址
#define TCFG_APP_ENV0_SIZE				24												//参数区域0
#define TCFG_APP_ENV1_OFFSET				TCFG_APP_ENV0_OFFSET + TCFG_APP_ENV0_SIZE				//0x08080494	偏移地址
#define TCFG_APP_ENV1_ADDRESS				EEPROM_BASE_ADDRESS + TCFG_APP_ENV1_OFFSET				//0x08080494	绝对地址
#define TCFG_APP_ENV1_SIZE				24												//参数区域1

#define TCFG_RECORD_SERVER_OFFSET			TCFG_APP_ENV1_OFFSET + TCFG_APP_ENV1_SIZE				//0x080804AC
#define TCFG_RECORD_SERVER_LENGTH			6												//Server Coap			CDP服务器地址
#define TCFG_WORKMODE_OFFSET				TCFG_RECORD_SERVER_OFFSET + TCFG_RECORD_SERVER_LENGTH		//0x080804B2
#define TCFG_WORKMODE_LENGTH				1												//WorkMode			工作模式
#define TCFG_RADARCOUNT_OFFSET			TCFG_WORKMODE_OFFSET + TCFG_WORKMODE_LENGTH				//0x080804B3
#define TCFG_RADARCOUNT_LENGTH			4												//RadarCount			雷达次数
#define TCFG_RADARDBG_OFFSET				TCFG_RADARCOUNT_OFFSET + TCFG_RADARCOUNT_LENGTH			//0x080804B7
#define TCFG_RADARDBG_LENGTH				1												//RadarDbg			雷达调试
#define TCFG_STATUSCNT_OFFSET				TCFG_RADARDBG_OFFSET + TCFG_RADARDBG_LENGTH				//0x080804B8
#define TCFG_STATUSCNT_LENGTH				4												//StatusCnt			状态改变值
#define TCFG_RFCHANNEL_OFFSET				TCFG_STATUSCNT_OFFSET + TCFG_STATUSCNT_LENGTH			//0x080804BC
#define TCFG_RFCHANNEL_LENGTH				1												//RFChannel			无线通信通道
#define TCFG_ENABLE_NBIOTPSM_OFFSET		TCFG_RFCHANNEL_OFFSET + TCFG_RFCHANNEL_LENGTH			//0x080804BD
#define TCFG_ENABLE_NBIOTPSM_LENGTH		1												//NBIOTPSM			NBPSM模式
#define TCFG_ACTIVE_DEVICE_OFFSET			TCFG_ENABLE_NBIOTPSM_OFFSET + TCFG_ENABLE_NBIOTPSM_LENGTH	//0x080804BE
#define TCFG_ACTIVE_DEVICE_LENGTH			1												//ActiveDevice			设备工作模式
#define TCFG_NBIOT_BOOTCNT_OFFSET			TCFG_ACTIVE_DEVICE_OFFSET + TCFG_ACTIVE_DEVICE_LENGTH		//0x080804BF
#define TCFG_NBIOT_BOOTCNT_LENGTH			4												//NBIOTBootCnt			NB重启次数
#define TCFG_NBIOT_SENTCNT_OFFSET			TCFG_NBIOT_BOOTCNT_OFFSET + TCFG_NBIOT_BOOTCNT_LENGTH		//0x080804C3
#define TCFG_NBIOT_SENTCNT_LENGTH			4												//NBIOTSentCnt			NB发送次数
#define TCFG_DEV_BOOTCNT_OFFSET			TCFG_NBIOT_SENTCNT_OFFSET + TCFG_NBIOT_SENTCNT_LENGTH		//0x080804C7
#define TCFG_DEV_BOOTCNT_LENGTH			2												//DevBootCnt			设备重启次数
#define TCFG_EVENT_TIME_OFFSET			TCFG_DEV_BOOTCNT_OFFSET + TCFG_DEV_BOOTCNT_LENGTH			//0x080804C9
#define TCFG_EVENT_TIME_LENGTH			4												//EventTime			设备运行事件时间
#define TCFG_TEMP_BACKGROUND_OFFSET		TCFG_EVENT_TIME_OFFSET + TCFG_EVENT_TIME_LENGTH			//0x080804CD
#define TCFG_TEMP_BACKGROUND_LENGTH		2												//BackgroundTemp		雷达背景
#define TCFG_MAG_MODE_OFFSET				TCFG_TEMP_BACKGROUND_OFFSET + TCFG_TEMP_BACKGROUND_LENGTH	//0x080804CF
#define TCFG_MAG_MODE_LENGTH				1												//MagMode				地磁模式
#define TCFG_NB_HEART_OFFSET				TCFG_MAG_MODE_OFFSET + TCFG_MAG_MODE_LENGTH				//0x080804D0
#define TCFG_NB_HEART_LENGTH				1												//NBHeart				NB心跳
#define TCFG_RADAR_RANGE_OFFSET			TCFG_NB_HEART_OFFSET + TCFG_NB_HEART_LENGTH				//0x080804D1
#define TCFG_RADAR_RANGE_LENGTH			1												//RadarRange			雷达范围
#define TCFG_CARIN_DELAY_OFFSET			TCFG_RADAR_RANGE_OFFSET + TCFG_RADAR_RANGE_LENGTH			//0x080804D2
#define TCFG_CARIN_DELAY_LENGTH			1												//CarInDelay			车辆进入延时上报时间
#define TCFG_RF_CMDCNT_OFFSET				TCFG_CARIN_DELAY_OFFSET + TCFG_CARIN_DELAY_LENGTH			//0x080804D3
#define TCFG_RF_CMDCNT_LENGTH				1												//RFCmdCnt			RF命令
#define TCFG_NB_CMDCNT_OFFSET				TCFG_RF_CMDCNT_OFFSET + TCFG_RF_CMDCNT_LENGTH			//0x080804D4
#define TCFG_NB_CMDCNT_LENGTH				1												//NBCmdCnt			NB命令
#define TCFG_COAP_CON_TIME_OFFSET			TCFG_NB_CMDCNT_OFFSET + TCFG_NB_CMDCNT_LENGTH			//0x080804D5
#define TCFG_COAP_CON_TIME_LENGTH			4												//CoapConTime			Coap连接时间
#define TCFG_COAP_IDLE_TIME_OFFSET			TCFG_COAP_CON_TIME_OFFSET + TCFG_COAP_CON_TIME_LENGTH		//0x080804D9
#define TCFG_COAP_IDLE_TIME_LENGTH			4												//CoapIdleTime			Coap休眠时间
#define TCFG_MAG_COEF_X_OFFSET			TCFG_COAP_IDLE_TIME_OFFSET + TCFG_COAP_IDLE_TIME_LENGTH	//0x080804DD
#define TCFG_MAG_COEF_X_LENGTH			1												//Temperature Compensation X
#define TCFG_MAG_COEF_Y_OFFSET			TCFG_MAG_COEF_X_OFFSET + TCFG_MAG_COEF_X_LENGTH			//0x080804DE
#define TCFG_MAG_COEF_Y_LENGTH			1												//Temperature Compensation Y
#define TCFG_MAG_COEF_Z_OFFSET			TCFG_MAG_COEF_Y_OFFSET + TCFG_MAG_COEF_Y_LENGTH			//0x080804DF
#define TCFG_MAG_COEF_Z_LENGTH			1												//Temperature Compensation Z
#define TCFG_MAG_BACK_TEMP_OFFSET			TCFG_MAG_COEF_Z_OFFSET + TCFG_MAG_COEF_Z_LENGTH			//0x080804E0
#define TCFG_MAG_BACK_TEMP_LENGTH			2												//Temperature Compensation BACK
#define TCFG_BEEP_OFF_OFFSET				TCFG_MAG_BACK_TEMP_OFFSET + TCFG_MAG_BACK_TEMP_LENGTH		//0x080804E2
#define TCFG_BEEP_OFF_LENGTH				1												//Beep Ctrl OFF		蜂鸣器关闭
#define TCFG_ROLL_INITSENSOR_OFFSET		TCFG_BEEP_OFF_OFFSET + TCFG_BEEP_OFF_LENGTH				//0x080804E3
#define TCFG_ROLL_INITSENSOR_LENGTH		1												//Rollingover Init Sensor
#define TCFG_NBIOT_SENTCOUNT_OFFSET		TCFG_ROLL_INITSENSOR_OFFSET + TCFG_ROLL_INITSENSOR_LENGTH	//0x080804E4
#define TCFG_NBIOT_SENTCOUNT_LENGTH		4												//NBIoT Sent Count		NB发送包数
#define TCFG_NBIOT_RECVCOUNT_OFFSET		TCFG_NBIOT_SENTCOUNT_OFFSET + TCFG_NBIOT_SENTCOUNT_LENGTH	//0x080804E8
#define TCFG_NBIOT_RECVCOUNT_LENGTH		4												//NBIoT Recv Count		NB接收包数
#define TCFG_NBIOT_SENTCNTDAY_OFFSET		TCFG_NBIOT_RECVCOUNT_OFFSET + TCFG_NBIOT_RECVCOUNT_LENGTH	//0x080804EC
#define TCFG_NBIOT_SENTCNTDAY_LENGTH		2												//NBIoT Sent Count Day	NB一天发送包数
#define TCFG_NBIOT_SENTCNTLMT_OFFSET		TCFG_NBIOT_SENTCNTDAY_OFFSET + TCFG_NBIOT_SENTCNTDAY_LENGTH	//0x080804EE
#define TCFG_NBIOT_SENTCNTLMT_LENGTH		2												//NBIoT Sent Count Limit	NB一天限定包数

/************************************** The environment parameters are used both by extend ***************************************/
#define EEPROM_CONFIG_PAGE2_ADDRESS		0x08080E00										//配置页2起始地址 EEPROM_BASE_ADD + 0x0E00(3.5K)
#define EEPROM_CONFIG_PAGE2_SIZE			0x0200											//配置页2大小     0x0200(512Byte)
#define TCFG_EEPROM_CONFIG_PAGE2_OFFSET		0x0E00

#define TCFG_COAP_SENTCNT_OFFSET			TCFG_EEPROM_CONFIG_PAGE2_OFFSET						//0x08080E00
#define TCFG_COAP_SENTCNT_LENGTH			4												//CoapSentCnt			COAP发送包数
#define TCFG_COAP_RECVCNT_OFFSET			TCFG_COAP_SENTCNT_OFFSET + TCFG_COAP_SENTCNT_LENGTH		//0x08080E04
#define TCFG_COAP_RECVCNT_LENGTH			4												//CoapRecvCnt			COAP接收包数
#define TCFG_MQTTSN_SENTCNT_OFFSET			TCFG_COAP_RECVCNT_OFFSET + TCFG_COAP_RECVCNT_LENGTH		//0x08080E08
#define TCFG_MQTTSN_SENTCNT_LENGTH			4												//MqttSentCnt			MQTTSN发送包数
#define TCFG_MQTTSN_RECVCNT_OFFSET			TCFG_MQTTSN_SENTCNT_OFFSET + TCFG_MQTTSN_SENTCNT_LENGTH	//0x08080E0C
#define TCFG_MQTTSN_RECVCNT_LENGTH			4												//MqttRecvCnt			MQTTSN接收包数

#define TCFG_RF_DPRINT_LV_OFFSET			TCFG_MQTTSN_RECVCNT_OFFSET + TCFG_MQTTSN_RECVCNT_LENGTH	//0x08080E10
#define TCFG_RF_DPRINT_LV_LENGTH			1												//RFDPrintLv			RF调试信息输出等级
#define TCFG_COAP_RA_TIME_OFFSET			TCFG_RF_DPRINT_LV_OFFSET + TCFG_RF_DPRINT_LV_LENGTH		//0x08080E11
#define TCFG_COAP_RA_TIME_LENGTH			1												//CoapRATime			RA间隔发送普通包时间

#define TCFG_UPDATA_LIMITRSSI_OFFSET		TCFG_COAP_RA_TIME_OFFSET + TCFG_COAP_RA_TIME_LENGTH		//0x08080E12
#define TCFG_UPDATA_LIMITRSSI_LENGTH		2												//UpdataLimitRssi		升级限制Rssi值
#define TCFG_UPDATA_LIMITSNR_OFFSET		TCFG_UPDATA_LIMITRSSI_OFFSET + TCFG_UPDATA_LIMITRSSI_LENGTH	//0x08080E14
#define TCFG_UPDATA_LIMITSNR_LENGTH		2												//UpdataLimitSnr		升级限制Snr值

#define TCFG_RESERVED1_OFFSET				TCFG_UPDATA_LIMITSNR_OFFSET + TCFG_UPDATA_LIMITSNR_LENGTH	//0x08080E16
#define TCFG_RESERVED1_LENGTH				2												//RESERVED1			保留
#define TCFG_RESERVED2_OFFSET				TCFG_RESERVED1_OFFSET + TCFG_RESERVED1_LENGTH			//0x08080E18
#define TCFG_RESERVED2_LENGTH				2												//RESERVED2			保留
#define TCFG_RESERVED3_OFFSET				TCFG_RESERVED2_OFFSET + TCFG_RESERVED2_LENGTH			//0x08080E1A
#define TCFG_RESERVED3_LENGTH				2												//RESERVED3			保留

#define TCFG_ONENET_SENTCNT_OFFSET			TCFG_RESERVED3_OFFSET + TCFG_RESERVED3_LENGTH			//0x08080E1C
#define TCFG_ONENET_SENTCNT_LENGTH			4												//OneNETSentCnt		ONENET发送包数
#define TCFG_ONENET_RECVCNT_OFFSET			TCFG_ONENET_SENTCNT_OFFSET + TCFG_ONENET_SENTCNT_LENGTH	//0x08080E20
#define TCFG_ONENET_RECVCNT_LENGTH			4												//OneNETRecvCnt		ONENET接收包数

#define TCFG_SOFTWARE_MAJOR_OFFSET			TCFG_ONENET_RECVCNT_OFFSET + TCFG_ONENET_RECVCNT_LENGTH	//0x08080E24
#define TCFG_SOFTWARE_MAJOR_LENGTH			1												//SoftwareMajor		软件版本号
#define TCFG_SOFTWARE_SUB_OFFSET			TCFG_SOFTWARE_MAJOR_OFFSET + TCFG_SOFTWARE_MAJOR_LENGTH	//0x08080E25
#define TCFG_SOFTWARE_SUB_LENGTH			1												//SoftwareSub			软件版本号

#define TCFG_DEVICE_RBTMODE_OFFSET			TCFG_SOFTWARE_SUB_OFFSET + TCFG_SOFTWARE_SUB_LENGTH		//0x08080E26
#define TCFG_DEVICE_RBTMODE_LENGTH			1												//DeviceRebootMode		设备重启方式

#define TCFG_MQTTSN_SERVER_OFFSET			TCFG_DEVICE_RBTMODE_OFFSET + TCFG_DEVICE_RBTMODE_LENGTH	//0x08080E27
#define TCFG_MQTTSN_SERVER_LENGTH			6												//Server MqttSN		MqttSN服务器地址

#define TCFG_RADAR_COVER_GAIN_OFFSET		TCFG_MQTTSN_SERVER_OFFSET + TCFG_MQTTSN_SERVER_LENGTH		//0x08080E2D
#define TCFG_RADAR_COVER_GAIN_LENGTH		1												//Gain in Cover		Radar覆水增益

#define TCFG_RADAR_GAIN_OFFSET			TCFG_RADAR_COVER_GAIN_OFFSET + TCFG_RADAR_COVER_GAIN_LENGTH	//0x08080E2E
#define TCFG_RADAR_GAIN_LENGTH			1												//Gain in				Radar增益

#define TCFG_SENSE_MODE_OFFSET			TCFG_RADAR_GAIN_OFFSET + TCFG_RADAR_GAIN_LENGTH			//0x08080E2F
#define TCFG_SENSE_MODE_LENGTH			1												//Sense Mode			传感器模式

#define TCFG_MAG_MANUALBACK_X_OFFSET		TCFG_SENSE_MODE_OFFSET + TCFG_SENSE_MODE_LENGTH			//0x08080E30
#define TCFG_MAG_MANUALBACK_X_LENGTH		10												//Mag X Back			地磁X背景值
#define TCFG_MAG_MANUALBACK_Y_OFFSET		TCFG_MAG_MANUALBACK_X_OFFSET + TCFG_MAG_MANUALBACK_X_LENGTH	//0x08080E3A
#define TCFG_MAG_MANUALBACK_Y_LENGTH		10												//Mag Y Back			地磁Y背景值
#define TCFG_MAG_MANUALBACK_Z_OFFSET		TCFG_MAG_MANUALBACK_Y_OFFSET + TCFG_MAG_MANUALBACK_Y_LENGTH	//0x08080E44
#define TCFG_MAG_MANUALBACK_Z_LENGTH		10												//Mag Z Back			地磁Z背景值

#define TCFG_RADAR_HIGHPASS_OFFSET			TCFG_MAG_MANUALBACK_Z_OFFSET + TCFG_MAG_MANUALBACK_Z_LENGTH	//0x08080E4E
#define TCFG_RADAR_HIGHPASS_LENGTH			1												//RadarHighPass		Radar高通滤波值

#define TCFG_RADAR_SAMPLEINTERVAL_OFFSET	TCFG_RADAR_HIGHPASS_OFFSET + TCFG_RADAR_HIGHPASS_LENGTH	//0x08080E4F
#define TCFG_RADAR_SAMPLEINTERVAL_LENGTH	1												//RadarSampleInterval	Radar采样频率
/************************************************************** End **************************************************************/

enum TCFG_SENSITIVITY																	//传感器灵敏度
{
	SENSE_HIGHEST 						= 0x01,
	SENSE_HIGH						= 0x02,
	SENSE_MIDDLE						= 0x03,
	SENSE_LOW							= 0x04,
	SENSE_LOWEST						= 0x05
};

enum TCFG_DEVICERBTRBTMODE																//设备重启方式
{
	RBTMODE_MODE_NONE					= 0x00,
	RBTMODE_SYSTEM_OVERTIME				= 0x01,
	RBTMODE_RADIO_COMMAND				= 0x02,
	RBTMODE_COAP_COMMAND				= 0x03,
	RBTMODE_MQTT_COMMAND				= 0x04,
	RBTMODE_RADIO_UPGRADE				= 0x05,
	RRTMODE_COAP_UPGRADE				= 0x06,
	RBTMODE_MQTT_UPGRADE				= 0x07,
	RBTMODE_NBHDRBTERR_OVER				= 0x08
};

typedef struct
{
	unsigned char						SoftVersion[20];									//软件版本
	unsigned char						HardVersion[20];									//硬件版本
	unsigned int						SubSn;											//设备号
	unsigned char						SubMacSN[9];										//设备标识号
	unsigned char						SubVender[4];										//设备厂商号
	unsigned char						BuildTime[16];										//编译日期
	unsigned short						Heartinterval;										//心跳间隔
	unsigned char						Sensitivity;										//灵敏度
	unsigned char						BootVersion;										//Boot版本号
	unsigned short						MagBackgroundX;									//地磁背景值X
	unsigned short						MagBackgroundY;									//地磁背景值Y
	unsigned short						MagBackgroundZ;									//地磁背景值Z
	short							MagBackgroudTemp;									//地磁背景温度值
	signed char						MagCoefX;											//地磁温飘计算值X
	signed char						MagCoefY;											//地磁温飘计算值Y
	signed char						MagCoefZ;											//地磁温飘计算值Z
	short							MagBackManualX[5];									//地磁手动背景值X
	short							MagBackManualY[5];									//地磁手动背景值Y
	short							MagBackManualZ[5];									//地磁手动背景值Z
	unsigned char						WorkMode;											//工作模式
	unsigned char						WorkModeStr[10];									//工作模式名
	unsigned char						RFChannel;										//无线通道
	unsigned char						RFDprintLv;										//无线调试信息输出等级
	unsigned char						MagMode;											//地磁模式
	unsigned char						SenseMode;										//传感器模式
	unsigned int						RadarCount;										//雷达次数
	unsigned char						RadarRange;										//雷达检测范围
	unsigned char						CoverGain;										//雷达覆水增益
	unsigned char						RadarGain;										//雷达增益
	unsigned char						RadarHighPass;										//雷达高通滤波值
	unsigned char						RadarSampleInterval;								//雷达采样频率
	unsigned char						CarInDelay;										//车辆进入延时上报时间
	unsigned int						SpotStatusCount;									//车位检测车辆次数
	unsigned char						NBIotHeart;										//NBIot心跳间隔
	unsigned int						NBIotBootCount;									//NBIot重启次数
	unsigned int						NBIotSentCount;									//NBIot发送包数
	unsigned int						NBIotRecvCount;									//NBIot接收包数
	unsigned short						NBIotSentCountDay;									//NBIot一天发送包数
	unsigned char						RFCommandCount;									//RF命令接收条数
	unsigned char						NBCommandCount;									//NB命令接收条数
	unsigned short						DeviceBootCount;									//设备重启次数
	unsigned char						CoapRATimeHour;									//Coap间隔时间发送普通数据包用于接收下行数据
	unsigned int						CoapConnectTime;									//Coap保持连接时间
	unsigned int						CoapIdleTime;										//Coap休眠时间
	short							UpgradeLimitRssi;									//信号值限制下限
	short							UpgradeLimitSnr;									//信号质量限制下限
	unsigned short						NBIdleLifetime;									//NBIot休眠模式保活时间(10S)
	unsigned char						BeepCtrlOff;										//蜂鸣器控制
	unsigned char						RollingOverInitSensor;								//翻转初始化控制
	unsigned char						DeviceRbtMode;										//设备重启方式
	unsigned char						NBCoapCDPServerIP[16];								//NB核心网IP地址
	unsigned char						NBCoapCDPServerPort[6];								//NB核心网IP端口
	NBIOT_ServerAddr					NBCoapCDPServer;									//NB核心网地址
	unsigned char						NBMqttSNServerIP[16];								//MqttSN服务器IP地址
	unsigned char						NBMqttSNServerPort[6];								//MqttSN服务器IP端口
	NBIOT_ServerAddr					NBMqttSNServer;									//MqttSN服务器地址
}TCFG_SystemDataTypeDef;

extern TCFG_SystemDataTypeDef				TCFG_SystemData;


void			TCFG_EEPROM_SystemInfo_Init(void);												//系统信息初始化
void			TCFG_EEPROM_WriteConfigData(void);												//写入系统配置信息
void			TCFG_EEPROM_ReadConfigData(void);												//读取系统配置信息

void			TCFG_EEPROM_SetSoftwareMajor(unsigned char softwaremajor);							//保存softwaremajor软件版本号
unsigned char	TCFG_EEPROM_GetSoftwareMajor(void);											//读取softwaremajor软件版本号

void			TCFG_EEPROM_SetSoftwareSub(unsigned char softwaresub);								//保存softwaresub软件版本号
unsigned char	TCFG_EEPROM_GetSoftwareSub(void);												//读取softwaresub软件版本号

bool			TCFG_EEPROM_CheckNewSoftware(void);											//检查新软件版本号
void			TCFG_EEPROM_WriteParameterData(void);											//写入系统参数信息

void			TCFG_EEPROM_SetBootMode(char bootmode);											//保存Boot启动模式
char			TCFG_EEPROM_GetBootMode(void);												//读取Boot启动模式

void			TCFG_EEPROM_SetSpotID(char* spotID);											//保存SpotID
void			TCFG_EEPROM_GetSpotID(char* spotID);											//读取SpotID

void			TCFG_EEPROM_SetHeartinterval(unsigned short val);									//保存Heartinterval
unsigned short	TCFG_EEPROM_GetHeartinterval(void);											//读取Heartinterval

void			TCFG_EEPROM_SetSavedSensitivity(unsigned char val);								//保存Sensitivity
unsigned char	TCFG_EEPROM_GetSavedSensitivity(void);											//读取Sensitivity

void			TCFG_EEPROM_SetBootVersion(unsigned char val);									//保存BootVersion
unsigned char	TCFG_EEPROM_GetBootVersion(void);												//读取BootVersion

void			TCFG_EEPROM_SetMagBackgroud(int16_t x_axis, int16_t y_axis, int16_t z_axis);			//保存地磁背景值
unsigned short	TCFG_EEPROM_GetMagBackgroud(char axis);											//读取地磁背景值

void			TCFG_EEPROM_SetMagManualBack(uint8_t i, int16_t x_axis, int16_t y_axis, int16_t z_axis);	//保存手动地磁背景值
short		TCFG_EEPROM_GetMagManualBack(uint8_t i, char axis);								//读取手动地磁背景值

void			TCFG_EEPROM_SetMagTempCoef(signed char coef_x, signed char coef_y, signed char coef_z);	//保存地磁温飘计算值
void			TCFG_EEPROM_GetMagTempCoef(signed char* coef_x, signed char* coef_y, signed char* coef_z);//读取地磁温飘计算值

void			TCFG_EEPROM_SetMagBackgroudTemp(short temp);										//保存MagBackgroudTemp
short		TCFG_EEPROM_GetMagBackgroudTemp(void);											//读取MagBackgroudTemp

void			TCFG_EEPROM_SetSubSN(unsigned int subsn);										//保存SubSN
unsigned int	TCFG_EEPROM_GetSubSN(void);													//读取SubSN

void			TCFG_EEPROM_SetBrandCode(unsigned int brand);									//保存BrandCode
unsigned int	TCFG_EEPROM_GetBrandCode(void);												//读取BrandCode

void			TCFG_EEPROM_SetBootCount(unsigned char count);									//保存BootCount
unsigned char	TCFG_EEPROM_GetBootCount(void);												//读取BootCount

void			TCFG_EEPROM_SetServerIP(unsigned int val);										//保存ServerIP
unsigned int	TCFG_EEPROM_GetServerIP(void);												//读取ServerIP

void			TCFG_EEPROM_SetServerPort(unsigned short val);									//保存ServerPort
unsigned short	TCFG_EEPROM_GetServerPort(void);												//读取ServerPort

char*		TCFG_EEPROM_Get_ServerIP_String(void);											//读取ServerIP字符串
char*		TCFG_EEPROM_Get_ServerPort_String(void);										//读取ServerPort字符串

void			TCFG_EEPROM_SetWorkMode(unsigned char val);										//保存WorkMode
unsigned char	TCFG_EEPROM_GetWorkMode(void);												//读取WorkMode
char*		TCFG_EEPROM_Get_WorkMode_String(void);											//读取WorkMode字符串

void			TCFG_EEPROM_SetRadarCount(unsigned int val);										//保存RadarCount
unsigned int	TCFG_EEPROM_GetRadarCount(void);												//读取RadarCount
void			TCFG_AddRadarCount(void);													//RadarCount++
unsigned int	TCFG_GetRadarCount(void);													//获取RadarCount

void			TCFG_EEPROM_SetStatusCount(unsigned int val);									//保存StatusCount
unsigned int	TCFG_EEPROM_GetStatusCount(void);												//读取StatusCount

void			TCFG_EEPROM_SetRfChannel(unsigned char val);										//保存RfChannel
unsigned char	TCFG_EEPROM_GetRfChannel(void);												//读取RfChannel

void			TCFG_EEPROM_SetRFDprintLv(uint8_t val);											//保存RFDprintLv
unsigned char	TCFG_EEPROM_GetRFDprintLv(void);												//读取RFDprintLv

void			TCFG_EEPROM_SetActiveDevice(unsigned char val);									//保存ActiveDevice
unsigned char	TCFG_EEPROM_GetActiveDevice(void);												//读取ActiveDevice

void			TCFG_EEPROM_SetNbiotBootCnt(unsigned int val);									//保存NbiotBootCnt
unsigned int	TCFG_EEPROM_GetNbiotBootCnt(void);												//读取NbiotBootCnt

void			TCFG_EEPROM_SetNBIotSentCount(unsigned int val);									//保存NBIotSentCount
unsigned int	TCFG_EEPROM_GetNBIotSentCount(void);											//读取NBIotSentCount

void			TCFG_EEPROM_SetNBIotRecvCount(unsigned int val);									//保存NBIotRecvCount
unsigned int	TCFG_EEPROM_GetNBIotRecvCount(void);											//读取NBIotRecvCount

void			TCFG_EEPROM_SetNBIotSentCountDay(unsigned short val);								//保存NBIotSentCountDay
unsigned short	TCFG_EEPROM_GetNBIotSentCountDay(void);											//读取NBIotSentCountDay

void			TCFG_EEPROM_SetNBIotSentCountLimit(unsigned short val);							//保存NBIotSentCountLimit
unsigned short	TCFG_EEPROM_GetNBIotSentCountLimit(void);										//读取NBIotSentCountLimit

void			TCFG_EEPROM_SetDevBootCnt(unsigned short val);									//保存DevBootCnt
unsigned short	TCFG_EEPROM_GetDevBootCnt(void);												//读取DevBootCnt

void			TCFG_EEPROM_SetEventTime(unsigned int val);										//保存EventTime
unsigned int	TCFG_EEPROM_GetEventTime(void);												//读取EventTime

void			TCFG_EEPROM_SetBackgroundTemp(int16_t val);										//保存BackgroundTemp
int16_t		TCFG_EEPROM_GetBackgroundTemp(void);											//读取BackgroundTemp

void			TCFG_EEPROM_SaveConfigInformation(unsigned int subSN);								//保存配置信息和SN
bool			TCFG_EEPROM_CheckHeadFlag(char flagtype);										//检测保存信息标志位

bool			TCFG_EEPROM_CheckInfoBurned(void);												//检测生产商信息
bool			TCFG_EEPROM_CheckNewSNorBrand(void);											//检测新的设备号或厂牌信息
void			TCFG_EEPROM_SetSNfromBrandKey(unsigned int val);									//保存SNfromBrandKey
unsigned int	TCFG_EEPROM_GetSNfromBrandKey(void);											//读取SNfromBrandKey
void			TCFG_EEPROM_SetFactoryBrand(unsigned int val);									//保存FactoryBrand
unsigned int	TCFG_EEPROM_GetFactoryBrand(void);												//读取FactoryBrand

void			TCFG_EEPROM_Set_MAC_SN(unsigned int sn);										//保存MAC SN
unsigned int	TCFG_EEPROM_Get_MAC_SN(void);													//读取MAC SN
char*		TCFG_EEPROM_Get_MAC_SN_String(void);											//读取MAC SN字符串

void			TCFG_EEPROM_SetVender(char* vender);											//保存Vender
void			TCFG_EEPROM_GetVender(char* vender);											//获取Verder
char*		TCFG_EEPROM_Get_Vender_String(void);											//读取vender字符串

void			TCFG_EEPROM_SetMagMode(uint8_t val);											//保存MagMode
unsigned char	TCFG_EEPROM_GetMagMode(void);													//读取MagMode

void			TCFG_EEPROM_SetSenseMode(uint8_t val);											//保存 sense mode
unsigned char	TCFG_EEPROM_GetSenseMode(void);												//读取 sense mode

void			TCFG_EEPROM_SetNbiotHeart(uint8_t val);											//保存NbiotHeart
unsigned char	TCFG_EEPROM_GetNbiotHeart(void);												//读取NbiotHeart

void			TCFG_EEPROM_SetRadarRange(uint8_t val);											//保存RadarRange
unsigned char	TCFG_EEPROM_GetRadarRange(void);												//读取RadarRange

void			TCFG_EEPROM_SetCoverGain(unsigned char val);										//保存 radar gain in cover
unsigned char	TCFG_EEPROM_GetCoverGain(void);												//读取 radar gain in cover

void			TCFG_EEPROM_SetRadarGain(unsigned char val);										//保存 radar gain
unsigned char	TCFG_EEPROM_GetRadarGain(void);												//读取 radar gain

void			TCFG_EEPROM_SetHighPass(unsigned char val);										//保存 cut-off frequency of high pass
unsigned char	TCFG_EEPROM_GetHighPass(void);												//读取 cut-off frequency of high pass

void			TCFG_EEPROM_SetSampleInterval(unsigned char val);									//保存 采样间隔
unsigned char	TCFG_EEPROM_GetSampleInterval(void);											//读取 采样间隔

void			TCFG_EEPROM_SetCarInDelay(uint8_t val);											//保存CarInDelay
unsigned char	TCFG_EEPROM_GetCarInDelay(void);												//读取CarInDelay

void			TCFG_EEPROM_SetRFCmdCnt(uint8_t val);											//保存RFCmdCnt
unsigned char	TCFG_EEPROM_GetRFCmdCnt(void);												//读取RFCmdCnt

void			TCFG_EEPROM_SetNBCmdCnt(uint8_t val);											//保存NBCmdCnt
unsigned char	TCFG_EEPROM_GetNBCmdCnt(void);												//读取NBCmdCnt

void			TCFG_EEPROM_SetCoapRATimeHour(unsigned char val);									//保存CoapRATimeHour
unsigned char	TCFG_EEPROM_GetCoapRATimeHour(void);											//读取CoapRATimeHour

void			TCFG_EEPROM_SetCoapConnectTime(unsigned int val);									//保存CoapConnectTime
unsigned int	TCFG_EEPROM_GetCoapConnectTime(void);											//读取CoapConnectTime

void			TCFG_EEPROM_SetCoapIdleTime(unsigned int val);									//保存CoapIdleTime
unsigned int	TCFG_EEPROM_GetCoapIdleTime(void);												//读取CoapIdleTime

void			TCFG_EEPROM_SetUpgradeLimitRssi(short val);										//保存UpgradeLimitRssi
short		TCFG_EEPROM_GetUpgradeLimitRssi(void);											//读取UpgradeLimitRssi

void			TCFG_EEPROM_SetUpgradeLimitSnr(short val);										//保存UpgradeLimitSnr
short		TCFG_EEPROM_GetUpgradeLimitSnr(void);											//读取UpgradeLimitSnr

void			TCFG_EEPROM_SetBeepOff(uint8_t val);											//保存BeepOff
unsigned char	TCFG_EEPROM_GetBeepOff(void);													//读取BeepOff

void			TCFG_EEPROM_SetRollingOverInitSensor(uint8_t val);								//保存RollingOverInitSensor
unsigned char	TCFG_EEPROM_GetRollingOverInitSensor(void);										//读取RollingOverInitSensor

void			TCFG_EEPROM_SetDeviceRbtMode(uint8_t val);										//保存DeviceRbtMode
unsigned char	TCFG_EEPROM_GetDeviceRbtMode(void);											//读取DeviceRbtMode

void			TCFG_EEPROM_SetMqttSNIP(unsigned int val);										//保存MqttSNIP
unsigned int	TCFG_EEPROM_GetMqttSNIP(void);												//读取MqttSNIP
void			TCFG_EEPROM_SetMqttSNPort(unsigned short val);									//保存MqttSNPort
unsigned short	TCFG_EEPROM_GetMqttSNPort(void);												//读取MqttSNPort

char*		TCFG_EEPROM_Get_MqttSNIP_String(void);											//读取MqttSNIP字符串
char*		TCFG_EEPROM_Get_MqttSNPort_String(void);										//读取MqttSNPort字符串

void			TCFG_Utility_Add_Device_BootCount(void);										//Device重启次数累加
unsigned short TCFG_Utility_Get_Device_BootCount(void);										//Device重启次数获取
void			TCFG_Utility_Add_Nbiot_BootCount(void);											//NBIot重启次数累加
unsigned int	TCFG_Utility_Get_Nbiot_BootCount(void);											//NBIot重启次数获取

void			TCFG_Utility_Add_NBIot_SentCount(void);											//NBIot 发送次数累加
unsigned int	TCFG_Utility_Get_NBIot_SentCount(void);											//NBIot 发送次数获取
void			TCFG_Utility_Add_NBIot_RecvCount(void);											//NBIot 接收次数累加
unsigned int	TCFG_Utility_Get_NBIot_RecvCount(void);											//NBIot 接收次数获取
void			TCFG_Utility_Add_NBIot_SentCountDay(void);										//NBIot 一天发送次数累加
unsigned short	TCFG_Utility_Get_NBIot_SentCountDay(void);										//NBIot 一天发送次数获取
unsigned short	TCFG_Utility_Get_NBIot_SentCountLimit(void);										//NBIot 一天剩余次数获取

void			TCFG_Utility_Set_Nbiot_IdleLifetime(unsigned short val);							//NBIot 休眠模式保活时间设置
unsigned short	TCFG_Utility_Get_Nbiot_IdleLifetime(void);										//NBIot 休眠模式保活时间获取
void			TCFG_Utility_Sub_Nbiot_IdleLifetime(void);										//NBIot 休眠模式保活时间递减

char*		TCFG_Utility_Get_Nbiot_Iccid_String(void);										//读取Nbiot Iccid字符串
char*		TCFG_Utility_Get_Nbiot_Imei_String(void);										//读取Nbiot Imei字符串
char*		TCFG_Utility_Get_Nbiot_Imeisv_String(void);										//读取Nbiot Imeisv字符串
char*		TCFG_Utility_Get_Nbiot_Imsi_String(void);										//读取Nbiot Imesi字符串
int			TCFG_Utility_Get_Nbiot_Rssi_IntVal(void);										//读取Nbiot Rssi值
unsigned char	TCFG_Utility_Get_Nbiot_Rssi_UnCharVal(void);										//读取Nbiot Rssi值
unsigned char	TCFG_Utility_Get_Nbiot_WorkMode(void);											//读取Nbiot WorkMode值
unsigned char	TCFG_Utility_Get_Nbiot_Registered(void);										//读取Nbiot Registered值
unsigned char	TCFG_Utility_Get_Nbiot_NetStateIdentification(void);								//读取Nbiot NetStateIdentification值

unsigned int	TCFG_Utility_Get_Nbiot_NetworkRegStatusTac(void);									//读取Nbiot NetworkRegStatusTac值
unsigned int	TCFG_Utility_Get_Nbiot_NetworkRegStatusCellID(void);								//读取Nbiot NetworkRegStatusCellID值

int			TCFG_Utility_Get_Nbiot_RadioSignalpower(void);									//读取Nbiot RadioSignalpower值
int			TCFG_Utility_Get_Nbiot_RadioTotalpower(void);									//读取Nbiot RadioTotalpower值
int			TCFG_Utility_Get_Nbiot_RadioTXpower(void);										//读取Nbiot RadioTXpower值
unsigned int	TCFG_Utility_Get_Nbiot_RadioTXtime(void);										//读取Nbiot RadioTXtime值
unsigned int	TCFG_Utility_Get_Nbiot_RadioRXtime(void);										//读取Nbiot RadioRXtime值
unsigned int	TCFG_Utility_Get_Nbiot_RadioCellID(void);										//读取Nbiot RadioCellID值
int			TCFG_Utility_Get_Nbiot_RadioECL(void);											//读取Nbiot RadioECL值
int			TCFG_Utility_Get_Nbiot_RadioSNR(void);											//读取Nbiot RadioSNR值
int			TCFG_Utility_Get_Nbiot_RadioEARFCN(void);										//读取Nbiot RadioEARFCN值
int			TCFG_Utility_Get_Nbiot_RadioPCI(void);											//读取Nbiot RadioPCI值
int			TCFG_Utility_Get_Nbiot_RadioRSRQ(void);											//读取Nbiot RadioRSRQ值

int			TCFG_Utility_Get_Nbiot_CellEarfcn(void);										//读取Nbiot CellEarfcn值
int			TCFG_Utility_Get_Nbiot_CellPhysicalCellID(void);									//读取Nbiot PhysicalCellCellID值
int			TCFG_Utility_Get_Nbiot_CellPrimaryCell(void);									//读取Nbiot PrimaryCellCell值
int			TCFG_Utility_Get_Nbiot_CellRsrp(void);											//读取Nbiot CellRsrp值
int			TCFG_Utility_Get_Nbiot_CellRsrq(void);											//读取Nbiot CellRsrq值
int			TCFG_Utility_Get_Nbiot_CellCellrssi(void);										//读取Nbiot CellCellrssi值
int			TCFG_Utility_Get_Nbiot_CellSnr(void);											//读取Nbiot CellSnr值

unsigned int	TCFG_Utility_Get_Nbiot_NetworkRegistStatusTac(void);								//读取Nbiot NetworkRegistStatusTac值
unsigned int	TCFG_Utility_Get_Nbiot_NetworkRegistStatusCellID(void);							//读取Nbiot NetworkRegistStatusCellID值

unsigned int	TCFG_Utility_GetCoapConnectTime(void);											//读取Nbiot CoapConnectTime值
unsigned int	TCFG_Utility_GetCoapIdleTime(void);											//读取Nbiot CoapIdleTime值

char*		TCFG_Utility_Get_Nbiot_PCPPlatformSoftVersion(void);								//读取Nbiot PCPPlatformSoftVersion值
unsigned char	TCFG_Utility_Get_Nbiot_PCPPlatformSoftVersionMajor(void);							//读取Nbiot PCPPlatformSoftVersionMajor值
unsigned char	TCFG_Utility_Get_Nbiot_PCPPlatformSoftVersionSub(void);							//读取Nbiot PCPPlatformSoftVersionSub值
unsigned short	TCFG_Utility_Get_Nbiot_PCPUpgradePackSliceSize(void);								//读取Nbiot PCPUpgradePackSliceSize值
unsigned short	TCFG_Utility_Get_Nbiot_PCPUpgradePackSliceNum(void);								//读取Nbiot PCPUpgradePackSliceNum值
unsigned short	TCFG_Utility_Get_Nbiot_PCPUpgradePackSliceIndex(void);								//读取Nbiot PCPUpgradePackSliceIndex值
unsigned short	TCFG_Utility_Get_Nbiot_PCPUpgradePackCheckCode(void);								//读取Nbiot PCPUpgradePackCheckCode值
unsigned short	TCFG_Utility_Get_Nbiot_PCPUpgradeStartTimes(void);								//读取Nbiot PCPUpgradeStartTimes值

char*		TCFG_Utility_Get_Nbiot_Manufacturer(void);										//读取Nbiot Manufacturer值
char*		TCFG_Utility_Get_Nbiot_Manufacturermode(void);									//读取Nbiot Manufacturermode值
char*		TCFG_Utility_Get_Nbiot_ModelVersion(void);										//读取Nbiot ModelVersion值
char*		TCFG_Utility_Get_Nbiot_PDPType(void);											//读取Nbiot PDPType值
char*		TCFG_Utility_Get_Nbiot_APN(void);												//读取Nbiot APN值
char*		TCFG_Utility_Get_Nbiot_PDPContext_APN(void);										//读取Nbiot PDPContext APN值
unsigned int	TCFG_Utility_Get_Nbiot_SentCount(void);											//读取Nbiot SentCount值
unsigned int	TCFG_Utility_Get_Nbiot_RecvCount(void);											//读取Nbiot RecvCount值
unsigned short	TCFG_Utility_Get_Device_Batt_ShortVal(void);										//读取Device Batt值
short		TCFG_Utility_Get_Device_Temperature(void);										//读取Device Temperature值
char*		TCFG_Utility_Get_Build_Time_String(void);										//读取Build Time字符串
unsigned int	TCFG_Utility_Get_Run_Time(void);												//读取系统运行时间
unsigned short TCFG_Utility_Get_Mvb_ModelType(void);											//读取设备类型
unsigned char	TCFG_Utility_Get_RadarLibNum(void);											//读取雷达库版本号
unsigned char	TCFG_Utility_Get_AlgoLibNum(void);												//读取检测算法库版本号
unsigned char	TCFG_Utility_Get_SoftResetFlag(void);											//读取设备重启标识符
unsigned short TCFG_Utility_Get_ReInitModuleCount(void);										//读取模块异常初始化次数
unsigned short TCFG_Utility_Get_DistanceRange(void);											//读取雷达检测范围
unsigned char	TCFG_Utility_Get_GainCover(void);												//读取雷达覆水增益
unsigned char	TCFG_Utility_Get_RadioGatewayNearby(void);										//读取小无线网关接收值
unsigned char	TCFG_Utility_Get_Major_Softnumber(void);										//读取Major_Softnumber
unsigned char	TCFG_Utility_Get_Sub_Softnumber(void);											//读取Sub_Softnumber
unsigned char	TCFG_Utility_Get_Major_Hardnumber(void);										//读取Major_Hardnumber
char*		TCFG_Utility_Get_Softwear_Version_String(void);									//读取Softwear Version字符串
char*		TCFG_Utility_Get_Hardwear_Version_String(void);									//读取Hardwear Version字符串

void			TCFG_EEPROM_SetStandardByte(unsigned int Address, unsigned char val);
void			TCFG_EEPROM_SetStandardHalfWord(unsigned int Address, unsigned short val);
void			TCFG_EEPROM_SetStandardWord(unsigned int Address, unsigned int val);

unsigned char	TCFG_EEPROM_GetStandardByte(unsigned int Address);
unsigned short	TCFG_EEPROM_GetStandardHalfWord(unsigned int Address);
unsigned int	TCFG_EEPROM_GetStandardWord(unsigned int Address);

#endif
