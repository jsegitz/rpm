#ifndef _H_RPMFC_
#define _H_RPMFC_

/*@notchecked@*/
extern int _rpmfc_debug;

typedef struct rpmfc_s * rpmfc;

struct rpmfc_s {
    int nfiles;		/*!< no. of files */
    int fknown;		/*!< no. of classified files */
    int fwhite;		/*!< no. of "white" files */
    int ix;		/*!< current file index */
    ARGV_t fn;		/*!< (#files) file names */
    ARGI_t fcolor;	/*!< (#files) file colors */
    ARGI_t fcdictx;	/*!< (#files) file class dictionary indices */
    ARGI_t fddictx;	/*!< (#files) file depends dictionary start */
    ARGI_t fddictn;	/*!< (#files) file depends dictionary no. entries */
    ARGV_t cdict;	/*!< (#classes) file class dictionary */
    ARGV_t ddict;	/*!< (#dependencies) file depends dictionary */
    ARGI_t ddictx;	/*!< (#dependencies) file->dependency mapping */
    ARGV_t provides;	/*!< (#provides) package provides */
    ARGV_t requires;	/*!< (#requires) package requires */
};

enum FCOLOR_e {
    RPMFC_BLACK			= 0,
    RPMFC_ELF32			= (1 <<  0),
    RPMFC_ELF64			= (1 <<  1),
#define	RPMFC_ELF	(RPMFC_ELF32|RPMFC_ELF64)

    RPMFC_EXECUTABLE		= (1 <<  8),
    RPMFC_SCRIPT		= (1 <<  9),
    RPMFC_TEXT			= (1 << 10),
    RPMFC_DATA			= (1 << 11),	/* XXX unused */
    RPMFC_DOCUMENT		= (1 << 12),
    RPMFC_STATIC		= (1 << 13),
    RPMFC_NOTSTRIPPED		= (1 << 14),
    RPMFC_COMPRESSED		= (1 << 15),

    RPMFC_DIRECTORY		= (1 << 16),
    RPMFC_SYMLINK		= (1 << 17),
    RPMFC_DEVICE		= (1 << 18),
    RPMFC_LIBRARY		= (1 << 19),
    RPMFC_ARCHIVE		= (1 << 20),
    RPMFC_FONT			= (1 << 21),
    RPMFC_IMAGE			= (1 << 22),
    RPMFC_MANPAGE		= (1 << 23),

    RPMFC_PERL			= (1 << 24),
    RPMFC_JAVA			= (1 << 25),
    RPMFC_PYTHON		= (1 << 26),
    RPMFC_PHP			= (1 << 27),
    RPMFC_TCL			= (1 << 28),

    RPMFC_WHITE			= (1 << 29),
    RPMFC_INCLUDE		= (1 << 30),
    RPMFC_ERROR			= (1 << 31)
};
typedef	enum FCOLOR_e FCOLOR_t;

struct rpmfcTokens_s {
/*@observer@*/
    const char * token;
    int colors;
};

typedef struct rpmfcTokens_s * rpmfcToken;

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
int rpmfcColoring(const char * fmstr)
	/*@*/;

/**
 */
void rpmfcPrint(const char * msg, rpmfc fc, FILE * fp)
	/*@globals fileSystem @*/
	/*@modifies *fp, fileSystem @*/;
/**
 */
/*@null@*/
rpmfc rpmfcFree(/*@only@*/ /*@null@*/ rpmfc fc)
	/*@modifies fc @*/;

/**
 */
rpmfc rpmfcNew(void)
	/*@*/;

/**
 * Build file class dictionary and mappings.
 */
int rpmfcClassify(rpmfc fc, ARGV_t argv)
	/*@modifies *fcp @*/;

/**
 * BUild file/package dependency dictionary and mappings.
 */
int rpmfcApply(rpmfc fc)
	/*@modifies fc @*/;

#ifdef __cplusplus
}
#endif

#endif /* _H_RPMFC_ */
