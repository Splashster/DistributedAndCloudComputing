/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "bank2.h"

bool_t
xdr_bank2AccountInfo (XDR *xdrs, bank2AccountInfo *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->accountNum1, 50))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->accountNum2, 50))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->amount))
		 return FALSE;
	return TRUE;
}
