/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "bank1.h"

bool_t
xdr_accountInfo (XDR *xdrs, accountInfo *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)&objp->accountNum1, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->accountNum2, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->amount))
		 return FALSE;
	return TRUE;
}
