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

static long init_record(waveformRecord *prec) {
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
    // free the previously allocated bptr and replace it with the info ptr
    free(prec->bptr);
    prec->bptr = infoStr;
    prec->ftvl = DBF_UCHAR;
    size_t N = strlen(infoStr) + 1;  // include the NULL
    prec->nelm = N;
    prec->nord = N;
    return 0;
}

static long read_wf(waveformRecord *prec) {
    // Do nothing as we already have initialized it above
    return 0;
}

static struct {
    long number;
    long (*dev_report)(int);
    long (*init)(int);
    long (*init_record)(waveformRecord *);
    long (*get_ioint_info)(int, dbCommon *, IOSCANPVT *);
    long (*read_wf)(waveformRecord *);
} devCopyInfo = {
    5, NULL, NULL, init_record, NULL, read_wf
};
epicsExportAddress(dset,devCopyInfo);
