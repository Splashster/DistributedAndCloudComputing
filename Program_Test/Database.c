#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <errno.h>
#include "Database.h"

typedef struct{
	int bank_location;
	int remaining_balance;
	int id;
}db_data;

void closeDB(sqlite3* db){
	sqlite3_close(db);
}

int created_db1 = 0;
int created_db2 = 0;
int created_db3 = 0;

static int lookUpQueryCallback(void *Used, int argc, char **argv, char **azColName) {
   db_data *theData = (db_data *)Used;
   theData->bank_location = atoi(argv[0]);

   return 0;
}

static int addQueryCallback(void *NotUsed, int argc, char **argv, char **azColName) {
   return 0;
}

static int fundsQueryCallback(void *Used, int argc, char **argv, char **azColName){
	db_data *theData = (db_data *)Used;
    theData->remaining_balance = atoi(argv[0]);

   	return 0;
}

static int idQueryCallback(void *Used, int argc, char **argv, char **azColName){
	db_data *theData = (db_data *)Used;
    theData->id = atoi(argv[0]);
 
   	return 0;
}


int addQuery(sqlite3 *db, char* sql){
	int result;
	char *zErrMsg = 0;

	result = sqlite3_exec(db, sql, addQueryCallback, 0, &zErrMsg);

	if(result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);

   	} 

   	return result;
}

int lookUpQuery(sqlite3 *db, char* sql, db_data theData){
	int result;
	char *zErrMsg = 0;

	result = sqlite3_exec(db, sql, lookUpQueryCallback, &theData, &zErrMsg);

   	return theData.bank_location;
}

int fundsQuery(sqlite3 *db, char* sql, db_data theData){
	int result;
	char *zErrMsg = 0;

	result = sqlite3_exec(db, sql, fundsQueryCallback, &theData, &zErrMsg);

	return theData.remaining_balance;
}

int idQuery(sqlite3 *db, char* sql, db_data theData){
	int result;
	char *zErrMsg = 0;

	result = sqlite3_exec(db, sql, idQueryCallback, &theData, &zErrMsg);

	return theData.id;
}

void initializeDB(sqlite3 *db, char* filename, char* bank){
	char sql[300];
	int result;
	FILE *file;
	char line[300];
	int id = 0;
	char* accountNum;
	char* transactionType;
	int amount = 0;
	int balance = 0;
	int bank_location = 0;


	if(strcmp(bank,"VIRTUALBANK") == 0){
		sprintf(sql, "CREATE TABLE ACCOUNT_MAPPING (ID INTEGER PRIMARY KEY NOT NULL, ACCOUNT_NUMBER VARCHAR(50) NOT NULL, BANK_LOCATION INTEGER NOT NULL)");
		addQuery(db, sql);

	  file = fopen(filename, "r");
		if(!file){
		}
		else{
			while(fgets(line, 300, file)!= NULL){
				if(line[0] != '\n'){
						id = atoi(strtok(line, " "));
						accountNum = strtok(NULL, " ");
						bank_location = atoi(strtok(NULL, " "));

		   			sprintf(sql,"INSERT INTO ACCOUNT_MAPPING (ID, ACCOUNT_NUMBER, BANK_LOCATION) VALUES (%i, '%s', %i)", id, accountNum , bank_location);
		   			addQuery(db, sql);
		   		}
		   	}
		   	fclose(file);
		}
	}else{
		sprintf(sql, "CREATE TABLE TRANSACTIONS (ID INTEGER PRIMARY KEY NOT NULL, ACCOUNT_NUMBER VARCHAR(50) NOT NULL, TRANSACTION_TYPE VARCHAR(10) NOT NULL, TRANSACTION_AMOUNT DECIMAL(10,2) NOT NULL, CURRENT_BALANCE DECIMAL(10,2) NOT NULL)");
		addQuery(db, sql);

	  file = fopen(filename, "r");
		if(!file){}
		else{
			while(fgets(line, 300, file)!= NULL){
				if(line[0] != '\n'){
					id = atoi(strtok(line, " "));
					accountNum = strtok(NULL, " ");
					transactionType = strtok(NULL, " ");
					amount = atoi(strtok(NULL, " "));
					balance = atoi(strtok(NULL, " "));
		   			sprintf(sql,"INSERT INTO TRANSACTIONS (ID, ACCOUNT_NUMBER, TRANSACTION_TYPE, TRANSACTION_AMOUNT, CURRENT_BALANCE) VALUES (%i, '%s', '%s', %i, %i)", id, accountNum ,transactionType, amount, balance);
		   			addQuery(db, sql);
		   		}
		   	}
		   	fclose(file);
		}
	}
}

sqlite3* openDBConnection(int bank, sqlite3* db){

	int result = 0;

	if(bank == 1){
			result = sqlite3_open("bank1.db", &db);

			if(result){
					fprintf(stderr, "There was a problem with the bank1 db: %s\n", sqlite3_errmsg(db));
			}
	}else if(bank == 2){
			result = sqlite3_open("bank2.db", &db);

			if(result){
				fprintf(stderr, "There was a problem with the bank2 db: %s\n", sqlite3_errmsg(db));
			}
	}else{
		result = sqlite3_open("virtualbank.db", &db);

		if(result){
			fprintf(stderr, "There was a problem with the bank2 db: %s\n", sqlite3_errmsg(db));
		}
	}

	return db;
}

void setupDB(int bank){
	sqlite3* db;

	if(bank == 1 && created_db1 == 0){
		db = openDBConnection(1, db);
		initializeDB(db, "/home/coursework/DistributedAndCloudComputing/Program_Test/Bank1.txt", "BANK1");
		created_db1 = 1;
	}else if(bank == 2 && created_db2 == 0){
		db = openDBConnection(2, db);
		initializeDB(db, "/home/coursework/DistributedAndCloudComputing/Program_Test/Bank2.txt", "BANK2");
		created_db2 = 1;
	}else if(bank == 3 && created_db3 == 0){
		db = openDBConnection(3, db);
		initializeDB(db, "/home/coursework/DistributedAndCloudComputing/Program_Test/AccountMapping.txt", "VIRTUALBANK");
		created_db3 = 1;
	}

	closeDB(db);
}

int accountLookUP(char* accountNum){
	char sql[300];
	db_data theData;
	theData.bank_location = 0;
	sqlite3* virtual_db;

	virtual_db = openDBConnection(3, virtual_db);

	sprintf(sql, "SELECT BANK_LOCATION FROM ACCOUNT_MAPPING where ACCOUNT_NUMBER = '%s' LIMIT 1", accountNum);
	theData.bank_location = lookUpQuery(virtual_db, sql, theData);

	closeDB(virtual_db);
	return theData.bank_location;
}

int credit(int bank, char*accountNum, int amount){
	sqlite3* db;
	char sql[300];
	db_data theData;
	theData.remaining_balance = 0;
	theData.bank_location = 0;
	theData.id = 0;
	int transactionProcessed = 1;

	db = openDBConnection(bank, db);

	sprintf(sql, "SELECT ID FROM TRANSACTIONS ORDER BY ID DESC LIMIT 1");
	theData.id = idQuery(db,sql, theData);


	sprintf(sql, "SELECT CURRENT_BALANCE FROM TRANSACTIONS WHERE ACCOUNT_NUMBER = '%s' ORDER BY ID DESC LIMIT 1", accountNum);
	theData.remaining_balance = fundsQuery(db,sql, theData);
	printf("Current Balance for Account: %s is: %i\n", accountNum, theData.remaining_balance);

	theData.remaining_balance += amount;
	theData.id += 1;

	sprintf(sql, "INSERT INTO TRANSACTIONS (ID, ACCOUNT_NUMBER, TRANSACTION_TYPE, TRANSACTION_AMOUNT, CURRENT_BALANCE) VALUES (%i, '%s', 'credit', %i, %i)", theData.id , accountNum, amount, theData.remaining_balance);
	addQuery(db, sql);

	sprintf(sql, "SELECT CURRENT_BALANCE FROM TRANSACTIONS WHERE ACCOUNT_NUMBER = '%s' ORDER BY ID DESC LIMIT 1", accountNum);
	theData.remaining_balance = fundsQuery(db,sql,theData);
	printf("New Balance for Account: %s is: %i\n", accountNum, theData.remaining_balance);

	closeDB(db);
	return transactionProcessed;
}

int debit(int bank, char* accountNum, int amount){
	int transactionProcessed = 0;
	sqlite3* db;
	char sql[300];
	db_data theData;
	theData.id = 0;
	theData.remaining_balance = 2;


	db = openDBConnection(bank, db);

	sprintf(sql, "SELECT ID FROM TRANSACTIONS ORDER BY ID DESC LIMIT 1");
	theData.id = idQuery(db,sql, theData);

	sprintf(sql, "SELECT CURRENT_BALANCE FROM TRANSACTIONS WHERE ACCOUNT_NUMBER = '%s' ORDER BY ID DESC LIMIT 1", accountNum);
	theData.remaining_balance = fundsQuery(db,sql, theData);
	printf("Current Balance for Account: %s is: %i\n", accountNum, theData.remaining_balance);

	if((theData.remaining_balance - amount) >= 0){
		theData.remaining_balance -= amount;
		theData.id += 1;
		sprintf(sql, "INSERT INTO TRANSACTIONS (ID, ACCOUNT_NUMBER, TRANSACTION_TYPE, TRANSACTION_AMOUNT, CURRENT_BALANCE) VALUES (%i, '%s', 'credit', %i, %i)", theData.id , accountNum, amount, theData.remaining_balance);
		addQuery(db, sql);
		sprintf(sql, "SELECT CURRENT_BALANCE FROM TRANSACTIONS WHERE ACCOUNT_NUMBER = '%s' ORDER BY ID DESC LIMIT 1", accountNum);
		theData.remaining_balance = fundsQuery(db,sql,theData);
		printf("New Balance for Account: %s is: %i\n",accountNum, theData.remaining_balance);
		transactionProcessed = 1;

	}

	closeDB(db);

	return transactionProcessed;
}
