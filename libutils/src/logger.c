#include <stdio.h>
#include <stdarg.h>
#include <logger.h>

///////////////////////////////////////////////////////////////////
// Function					: AuxLogDebug
// Author					: MAHA
// Description				: Auxiliar function to log debug messages
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
static void AuxLogDebug(const char* message, va_list args) {
	(void)args;
	(void)message;
#ifdef DEBUG
	vfprintf(stdout,message,args);
	printf("\n");
	fflush(stdout);
#endif
}

///////////////////////////////////////////////////////////////////
// Function					: AuxLogInfo
// Author					: MAHA
// Description				: Auxiliar function to log info messages
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
static void AuxLogInfo(const char* message, va_list args) {
	(void)args;
	(void)message;
	vfprintf(stdout,message,args);
	printf("\n");
	fflush(stdout);
}

///////////////////////////////////////////////////////////////////
// Function					: AuxLogWarning
// Author					: MAHA
// Description				: Auxiliar function to log warning messages
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
static void AuxLogWarning(const char* message, va_list args) {
	(void)args;
	(void)message;
#ifdef WARNING
	vfprintf(stdout,message,args);
	printf("\n");
	fflush(stdout);
#endif
}

///////////////////////////////////////////////////////////////////
// Function					: AuxLogError
// Author					: MAHA
// Description				: Auxiliar function to log error messages
// Date of Creation			: 24/06/2025
// Date of Modification		: 24/06/2025
/////////////////////////////////////////////////////////////////////
static void AuxLogError(const char* message, va_list args) {
	(void)args;
	(void)message;
	vfprintf(stderr,message,args);
	printf("\n");
	fflush(stderr);
}

///////////////////////////////////////////////////////////////////
// Function					: DefLogDebug
// Author					: MAHA
// Description				: Logs a generic log with debug level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogDebug(const char* message, ...) {
	(void)message;
#ifdef DEBUG
	printf("[ DEBUG ]  |  ");
#endif
	va_list args;
	va_start(args,message);
	AuxLogDebug(message,args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////
// Function					: DefLogError
// Author					: MAHA
// Description				: Logs a generic log with error level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogError(const char* message, ...) {
	(void)message;
	printf("[\033[31m ERROR\033[37m ]  |  ");
	va_list args;
	va_start(args,message);
	AuxLogError(message,args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////
// Function					: DefLogInfo
// Author					: MAHA
// Description				: Logs a generic log with info level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogInfo(const char* message, ...) {
	(void)message;
	printf("[ INFO  ]  |  ");
	va_list args;
	va_start(args,message);
	AuxLogInfo(message,args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////
// Function					: DefLogWarning
// Author					: MAHA
// Description				: Logs a generic log with warning level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogWarning(const char* message, ...) {
	(void)message;
#ifdef WARNING
	printf("[WARNING]  |  ");
#endif
	va_list args;
	va_start(args,message);
	AuxLogWarning(message,args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////
// Function					: Log
// Author					: MAHA
// Description				: Logs descriptive messages to the user.
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void Log(LogLevel level, const char* function, const char* message, ...) {
	va_list args;
	va_start(args,message);

	switch(level) {
		case sDEBUG:
#ifdef DEBUG
			printf("[ DEBUG ]  |  %s: ",function);
			AuxLogDebug(message,args);
#endif
			break;

		case sINFO:
			printf("[ INFO  ]  |  %s: ",function);
			AuxLogInfo(message,args);
			break;

		case sWARNING:
#ifdef WARNING
			printf("[WARNING]  |  %s: ",function);
			AuxLogWarning(message,args);
#endif
			break;

		case sERROR:
			printf("[ ERROR ]  |  %s: ",function);
			AuxLogInfo(message,args);
			break;
	}
	va_end(args);
}
