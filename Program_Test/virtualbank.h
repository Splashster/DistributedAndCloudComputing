/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _VIRTUALBANK_H_RPCGEN
#define _VIRTUALBANK_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct accountInfo {
	char *accountNum1;
	char *accountNum2;
	int amount;
};
typedef struct accountInfo accountInfo;

#define VIRTUALBANK 99
#define VER1 1

#if defined(__STDC__) || defined(__cplusplus)
#define vb_credit 1
extern  int * vb_credit_1(accountInfo *, CLIENT *);
extern  int * vb_credit_1_svc(accountInfo *, struct svc_req *);
#define vb_debit 2
extern  int * vb_debit_1(accountInfo *, CLIENT *);
extern  int * vb_debit_1_svc(accountInfo *, struct svc_req *);
#define vb_transfer 3
extern  int * vb_transfer_1(accountInfo *, CLIENT *);
extern  int * vb_transfer_1_svc(accountInfo *, struct svc_req *);
extern int virtualbank_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define vb_credit 1
extern  int * vb_credit_1();
extern  int * vb_credit_1_svc();
#define vb_debit 2
extern  int * vb_debit_1();
extern  int * vb_debit_1_svc();
#define vb_transfer 3
extern  int * vb_transfer_1();
extern  int * vb_transfer_1_svc();
extern int virtualbank_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_accountInfo (XDR *, accountInfo*);

#else /* K&R C */
extern bool_t xdr_accountInfo ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_VIRTUALBANK_H_RPCGEN */
