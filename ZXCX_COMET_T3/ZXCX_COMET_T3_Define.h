#pragma once

#ifndef DEFINE_H
#define DEFINE_H


#define SENDRECV_BUFFER_LEN					1025

#define TIMEOUT_RESPONSE					2000

#define NAME_SUB_MODEL						"ZXCX.COMET_T3"

#define TIME_LOOP							50


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMET CMD CODE
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEV_CMD_CONTST						"TA60S0007--|CONTST"
#define DEV_CMD_SYSSTAT						"TA60S0008--|SYSSTAT"
#define DEV_CMD_HVSTAT						"TA60S0007--|HVSTAT"
#define DEV_CMD_GET_HIVO					"TA60S0005--|HIVO"
#define DEV_CMD_HIVOM						"TA60S0006--|HIVOM"
#define DEV_CMD_GET_TUCU					"TA60S0005--|TUCU"
#define	DEV_CMD_TUCUM						"TA60S0006--|TUCUM"
#define	DEV_CMD_GET_FOCSL					"TA60S0006--|FOCSL"
#define DEV_CMD_FOCSZ						"TA60S0006--|FOCSZ"
#define DEV_CMD_WUPCD						"TA60S0006--|WUPCD"

#define DEV_CMD_CONTST_CODE					0x60
#define DEV_CMD_SYSSTAT_CODE				0x61
#define DEV_CMD_HVSTAT_CODE					0x62
#define DEV_CMD_GET_HIVO_CODE				0x63
#define DEV_CMD_HIVOM_CODE					0x64
#define DEV_CMD_GET_TUCU_CODE				0x65
#define DEV_CMD_TUCUM_CODE					0x66
#define DEV_CMD_GET_FOCSL_CODE				0x67
#define DEV_CMD_FOCSZ_CODE					0x68
#define DEV_CMD_WUPCD_CODE					0x69

#define DEV_CMD_HIVO_CODE					0x70
#define DEV_CMD_TUCU_CODE					0x71
#define DEV_CMD_FOCSL_CODE					0x72
#define DEV_CMD_HVEN_CODE					0x73

//变量命令
#define DEV_CMD_TA							"TA10S000"
#define DEV_CMD_TA__						"--|"
#define DEV_CMD_HIVO						"HIVO="
#define DEV_CMD_E3							"e3"
#define DEV_CMD_TUCU						"TUCU="
#define DEV_CMD_E3_							"e+3"
#define DEV_CMD_E_3							"e-3"
#define DEV_CMD_FOCSL						"FOCSL="
#define DEV_CMD_HVEN						"HVEN="

#define DEV_CMD_FENHAO						";"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMET ERROR CODE
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEV_ERR_T3_RETCODE_NOK							-1			//非正常（未知原因）
#define DEV_ERR_T3_RETCODE_OK							0			//正常（写入成功）
#define DEV_ERR_T3_RETCODE_NACK							1			//写入失败（无应答）
#define DEV_ERR_T3_RETCODE_ERR_TIMEOUT					102			//读取 / 写入超时
#define DEV_ERR_T3_RETCODE_ERR_BUFFER_FULL				103			//缓冲区溢出（如：通讯接口RX / TX 缓冲区）
#define DEV_ERR_T3_RETCODE_ERR_TOO_MANY_PARAMETERS		104			//接收值大于发送值
#define DEV_ERR_T3_RETCODE_ERR_TOO_FEW_PARAMETERS		105			//接收值小于发送值
#define DEV_ERR_T3_RETCODE_ERR_INVALID_PARAMETER		106			//接收值不可解析
#define DEV_ERR_T3_RETCODE_ERR_INVALID_NUMBER			107			//存在无效数字编码（如 HEX 和 FLOAT 混合）
#define DEV_ERR_T3_RETCODE_ERR_FRAMING_ERROR			108			//数据帧解析错误
#define DEV_ERR_T3_RETCODE_ERR_UNKNOWN_COMMAND			109			//不支持接收值
#define DEV_ERR_T3_RETCODE_ERR_INTERNAL_ERROR			110			//内部软件错误（请联系COMET）
#define DEV_ERR_T3_RETCODE_ERR_NOT_ALLOWED				111			//不允许实际操作模式下的命令或动作
#define DEV_ERR_T3_RETCODE_ERR_ACCESS_DENIED			112			//你没有权限发送命令
#define DEV_ERR_T3_RETCODE_ERR_BUSY						113			//由于需要的资源忙碌，动作或命令无法实现
#define DEV_ERR_T3_RETCODE_ERR_NO_DEVICE				114			//由于设备地址端口不存在，动作或命令无法实现

#define MTC_SUB								'I'
#define MTC_DEVICE							'D'

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DLL RESPONSE ERROR CODE
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DT_SUCCESS							0x00				//成功执行
#define DT_CLOSEFAIL						0x33				//成功执行
#define	DT_FAILURE							0x34				//失败
#define DT_ERROR_ALREADYOPEN				0x35				//设备已打开
#define DT_ERROR_LOADLIBRARY				0x36				//加载动态库失败
#define DT_ERROR_SENDSOCKET					0x37				//发送到Socket
#define DT_ERROR_WAITSOCKET					0x38				//WaitCom Error


#endif