
#define ERR_SUCESS 0
#define ERR_UNKNOW -1
#define ERR_GENERIC -2
#define ERR_ALLOC -3


errStrings[][20]=
{
	"Sucess",
	"Unknow error",
	"Generic error",
	"Memory allocation error",
	NULL
};

void err(int errCode);