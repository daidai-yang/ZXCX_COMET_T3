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

//��������
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
#define DEV_ERR_T3_RETCODE_NOK							-1			//��������δ֪ԭ��
#define DEV_ERR_T3_RETCODE_OK							0			//������д��ɹ���
#define DEV_ERR_T3_RETCODE_NACK							1			//д��ʧ�ܣ���Ӧ��
#define DEV_ERR_T3_RETCODE_ERR_TIMEOUT					102			//��ȡ / д�볬ʱ
#define DEV_ERR_T3_RETCODE_ERR_BUFFER_FULL				103			//������������磺ͨѶ�ӿ�RX / TX ��������
#define DEV_ERR_T3_RETCODE_ERR_TOO_MANY_PARAMETERS		104			//����ֵ���ڷ���ֵ
#define DEV_ERR_T3_RETCODE_ERR_TOO_FEW_PARAMETERS		105			//����ֵС�ڷ���ֵ
#define DEV_ERR_T3_RETCODE_ERR_INVALID_PARAMETER		106			//����ֵ���ɽ���
#define DEV_ERR_T3_RETCODE_ERR_INVALID_NUMBER			107			//������Ч���ֱ��루�� HEX �� FLOAT ��ϣ�
#define DEV_ERR_T3_RETCODE_ERR_FRAMING_ERROR			108			//����֡��������
#define DEV_ERR_T3_RETCODE_ERR_UNKNOWN_COMMAND			109			//��֧�ֽ���ֵ
#define DEV_ERR_T3_RETCODE_ERR_INTERNAL_ERROR			110			//�ڲ������������ϵCOMET��
#define DEV_ERR_T3_RETCODE_ERR_NOT_ALLOWED				111			//������ʵ�ʲ���ģʽ�µ��������
#define DEV_ERR_T3_RETCODE_ERR_ACCESS_DENIED			112			//��û��Ȩ�޷�������
#define DEV_ERR_T3_RETCODE_ERR_BUSY						113			//������Ҫ����Դæµ�������������޷�ʵ��
#define DEV_ERR_T3_RETCODE_ERR_NO_DEVICE				114			//�����豸��ַ�˿ڲ����ڣ������������޷�ʵ��

#define MTC_SUB								'I'
#define MTC_DEVICE							'D'

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DLL RESPONSE ERROR CODE
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DT_SUCCESS							0x00				//�ɹ�ִ��
#define DT_CLOSEFAIL						0x33				//�ɹ�ִ��
#define	DT_FAILURE							0x34				//ʧ��
#define DT_ERROR_ALREADYOPEN				0x35				//�豸�Ѵ�
#define DT_ERROR_LOADLIBRARY				0x36				//���ض�̬��ʧ��
#define DT_ERROR_SENDSOCKET					0x37				//���͵�Socket
#define DT_ERROR_WAITSOCKET					0x38				//WaitCom Error


#endif