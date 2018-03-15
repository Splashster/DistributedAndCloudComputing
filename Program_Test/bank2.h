/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _BANK2_H_RPCGEN
#define _BANK2_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct bank2AccountInfo {
	char *accountNum1;
	char *accountNum2;
	int amount;
};
typedef struct bank2AccountInfo bank2AccountInfo;

#define BANK2 102
#define VER3 3

#if defined(__STDC__) || defined(__cplusplus)
#define b2_credit 5
extern  int * b2_credit_3(bank2AccountInfo *, CLIENT *);
extern  int * b2_credit_3_svc(bank2AccountInfo *, struct svc_req *);
#define b2_debit 6
extern  int * b2_debit_3(bank2AccountInfo *, CLIENT *);
extern  int * b2_debit_3_svc(bank2AccountInfo *, struct svc_req *);
extern int bank2_3_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define b2_credit 5
extern  int * b2_credit_3();
extern  int * b2_credit_3_svc();
#define b2_debit 6
extern  int * b2_debit_3();
extern  int * b2_debit_3_svc();
extern int bank2_3_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_bank2AccountInfo (XDR *, bank2AccountInfo*);

#else /* K&R C */
extern bool_t xdr_bank2AccountInfo ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_BANK2_H_RPCGEN */
