struct accountInfo{
		string accountNum1<50>;
		string accountNum2<50>;
		int amount;
};

program	VIRTUALBANK{
	version VER1 {
		int vb_credit(accountInfo) = 1;
		int vb_debit(accountInfo) = 2;
		int vb_transfer(accountInfo) = 3;

	} = 1;
} = 99;
