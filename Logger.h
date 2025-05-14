#pragma once


bool ExternalStorageInit();
void WriteExternalStorage();
void Log(String ErrorCode, char Type);
String GetErrorDescription(String ErrorCode);
void LogMsg(String ACTION, String MSG, int XTSPOINT, int YTSPOINT);
void LogMsg(String ACTION, String MSG);