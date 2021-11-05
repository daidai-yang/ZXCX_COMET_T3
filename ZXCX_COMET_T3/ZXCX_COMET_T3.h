// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZXCXCOMETT3_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZXCXCOMETT3_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ZXCXCOMETT3_EXPORTS
#define ZXCXCOMETT3_API __declspec(dllexport)
#else
#define ZXCXCOMETT3_API __declspec(dllimport)
#endif

ZXCXCOMETT3_API CString WINAPI GetRtStr(BYTE code);

ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_Connect(CString ip, DWORD port);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_Disconnect(void);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_GetVersion(void);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_Reset(void);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_GetSYSStatus(char* status);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_GetHVStatus(char* status);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_OpenHV(void);
ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_CloseHV(void);

ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_Calibrate(int flg);

ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_SetkV(char* value);

ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_SetmA(char* value);

ZXCXCOMETT3_API int WINAPI fnZXCX_COMETT3_SetFocsl(char* value);

