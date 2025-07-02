#ifndef ERR_H
#define ERR_H 1

//	ERRC_BADARG: Bad argument passed to a function
//		if (arg == NULL) return ERRC_BADARG;
#define ERRC_BADARG	-1
//	ERRC_NULPTR: Null Pointer Exception
//	void* pvl = NULL; foo(pvl)
#define ERRC_NULPTR	-1
//	ERRC_FATAL: Fatal error, cannot continue
//		if (fatal_error) return ERRC_FATAL;
#define ERRC_FATAL	-100
//	ERRC_NOMEM: Not enough memory to complete the operation
//		if (malloc_failed) return ERRC_NOMEM;
#define ERRC_NOMEM	-100
// ERRC_OK: No error, operation completed successfully
//		if (success) return ERRC_OK;
#define ERRC_OK		0

#endif // ERR_H
