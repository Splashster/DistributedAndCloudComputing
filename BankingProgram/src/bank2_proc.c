/*************************************************************************
The bank2_proc.c file is the handles the transactions for accounts
located in the bank2 database.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>
#include "database.h"
#include "bank2.h"

int *b2_credit_3(struct bank2AccountInfo *vals, CLIENT *cl){
	static int result = 0;
	result = credit(2, vals->accountNum, vals->amount);
	
	return &result;
}

int *b2_debit_3(struct bank2AccountInfo *vals, CLIENT *cl){
	static int result = 0;
	result = debit(2, vals->accountNum, vals->amount);

	return &result;
}


int *b2_credit_3_svc(struct bank2AccountInfo *vals,
   struct svc_req *svc) {
  CLIENT *client;
  return(b2_credit_3(vals,client));
}

int *b2_debit_3_svc(struct bank2AccountInfo *vals,
   struct svc_req *svc) {
  CLIENT *client;
  return(b2_debit_3(vals,client));
}
