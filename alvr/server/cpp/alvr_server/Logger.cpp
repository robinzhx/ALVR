#include "Logger.h"

void _log(const char *format, va_list args, void (*logFn)(const char *))
{
	char buf[1024];
	int count = vsnprintf(buf, sizeof(buf), format, args);
	if (count > 0 && buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	logFn(buf);

	//TODO: driver logger should concider current log level
	DriverLogVarArgs(format, args);
}

Exception MakeException(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	Exception e = FormatExceptionV(format, args);
	va_end(args);

	return e;
}

void Error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	_log(format, args, LogError);
	va_end(args);
}

void Warn(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	_log(format, args, LogWarn);
	va_end(args);
}

void Info(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	_log(format, args, LogInfo);
	va_end(args);
}

void Debug(const char *format, ...)
{
#ifdef _DEBUG
	va_list args;
	va_start(args, format);
	_log(format, args, LogDebug);
	va_end(args);
#endif
}