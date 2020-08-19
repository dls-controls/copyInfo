/* waveform support for copying info field into the VAL of the record */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "devSup.h"
#include "dbCommon.h"
#include "dbAccess.h"
#include "dbStaticLib.h"
#include "waveformRecord.h"

/* must be last include */
#include "epicsExport.h"

static long read_wf(waveformRecord *prec) {
    char * buf = prec->bptr;
    DBENTRY *pdbentry = dbAllocEntry(pdbbase);
    int status = dbFindRecord(pdbentry, prec->name);
    if (status) {
	printf("Can't find record %s\n", prec->name);
	return -1;
    }
    const char * infoStr = dbGetInfo(pdbentry, "copyInfo");
    if (!infoStr) {
	printf("Can't find info(copyInfo, ...) for record '%s'\n", prec->name);
	return -1;
    }
    size_t N = strlen(infoStr) + 1;  // include the NULL
    if (N > prec->nelm)
        N = prec->nelm;
    prec->nord = N;
    memcpy(buf, infoStr, N);
    return 0;
}

// Declare this here to support R3.14
static struct {
    long number;
    long (*dev_report)(int);
    long (*init)(int);
    long (*init_record)(waveformRecord *);
    long (*get_ioint_info)(int, dbCommon *, IOSCANPVT *);
    long (*read_wf)(waveformRecord *);
} devCopyInfo = {
    5, NULL, NULL, NULL, NULL, read_wf
};
epicsExportAddress(dset,devCopyInfo);
