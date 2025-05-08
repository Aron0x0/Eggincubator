#pragma once


bool ExternalStorageInit();
void WriteExternalStorage();
void Log(String ErrorCode, char Type);
String GetErrorDescription(String ErrorCode);