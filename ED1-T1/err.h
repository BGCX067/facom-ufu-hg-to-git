
#define ERR_SUCESS 0
#define ERR_UNKNOW -1
#define ERR_GENERIC -2
#define ERR_ALLOC -3
#define ERR_ORDFUNC -4
#define ERR_UNKNOWFUNCTION -5

char const *errStrings[]=
{
	"Sucess",			/*  0 */
	"Unknow error",		/* -1 */
	"Generic error",	/* -2 */
	"Memory allocation error", /* -3 */
	"Ordenation function fails", /* -4 */
	"Pointer to a function not know", /* -5 */
	NULL
};

void err(int errCode, char file[], int line);