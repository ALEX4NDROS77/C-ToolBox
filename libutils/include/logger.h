#ifndef LOGGER_H
#define LOGGER_H 1

#define sDEBUG		LOG_DEBUG
#define sINFO		LOG_INFO
#define sWARNING	LOG_WARNING
#define sERROR		LOG_ERROR

typedef enum {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
} LogLevel;

///////////////////////////////////////////////////////////////////
// Function					: DefLogDebug
// Author					: MAHA
// Description				: Logs a generic log with debug level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogDebug(const char* message, ...);

///////////////////////////////////////////////////////////////////
// Function					: DefLogError
// Author					: MAHA
// Description				: Logs a generic log with error level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogError(const char* message, ...);

///////////////////////////////////////////////////////////////////
// Function					: DefLogInfo
// Author					: MAHA
// Description				: Logs a generic log with info level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogInfo(const char* message, ...);

///////////////////////////////////////////////////////////////////
// Function					: DefLogWarning
// Author					: MAHA
// Description				: Logs a generic log with warning level
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void DefLogWarning(const char* message, ...);

///////////////////////////////////////////////////////////////////
// Function					: Log
// Author					: MAHA
// Description				: Logs descriptive messages to the user.
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void Log(LogLevel level,const char* function, const char* message, ...);

#endif // LOGGER_H
