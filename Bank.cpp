#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>

class Customer
{	int   AccNo;
	char  Name[50];
	float Balance;
     public:
	void  Getdata(int);
	void  Showdata();
	int   RetAccNo();
	char *RetName();
	void  Transaction();
	void  Edit();
};

//	**************************** INPUT AN OBJECT *****************************
void Customer::Getdata(int AN)
{	AccNo=AN;
	cout<<"\n\nEnter Name : "; gets(Name);
	cout<<"Enter Opening Balance : "; cin>>Balance;
}

//	**************************** DISPLAY AN OBJECT *****************************
void Customer::Showdata()
{	cout<<"\n\nAccount Number : "<<AccNo<<endl;
	cout<<"Name : "<<Name<<endl;
	cout<<"Current Balance : "<<Balance<<endl<<endl;
}

//	**************************** RETURN ACCOUNT NUMBER OF AN OBJECT *****************************
int Customer::RetAccNo()
{	return AccNo;
}

//	**************************** RETURN NAME OF AN OBJECT *****************************
char *Customer::RetName()
{
	return Name;
}


//	**************************** WITHDRAW/DEPOSIT FOR AN OBJECT *****************************
void Customer::Transaction()
{
	float amount;
	char ch;
	do{
		cout<<"\n\nCurrent Balance : "<<Balance<<endl;
		cout<<"\n\nPress W if you want to Withdraw  \n";
		cout<<"Press D if you want to Deposit \n";
		cout<<"Press Q if you want to Quit from this Menu\n";
		cout<<"Enter your option :";
		ch=getche();
		switch(ch)
		{
			case 'W':
			case 'w': 	cout<<"\nEnter the amount to be Withdrawn : ";
					cin>>amount;
					if (Balance>amount)
						Balance -= amount;
					    else 
						cout<<"SORRY !! Insufficient Balance in the Account !!\n";
					cout<<"The Currenct Balance : "<<Balance<<endl;
					break;
			case 'D':
			case 'd': 	cout<<"\nEnter the amount to be Deposited : ";
					cin>>amount;
					if (amount>0)
						Balance += amount;
					    else
						cout<<"SORRY !! Not a Valid Amount !!\n";
					cout<<"The Currenct Balance : "<<Balance<<endl;
					break;
			case 'Q':
			case 'q': 	break;
			default :	cout<<"\nWrong Option !! Try Again !!";
		}
	}while(ch!='Q' && ch!='q');
}


//	**************************** EDIT/ MODIFY AN OBJECT *****************************
void Customer::Edit()
{
	char ch;
	do{
		cout<<"Detail of the Record :\n\n";
		Showdata();
		cout<<"\n\nPress A if you want to change Name \n";
		cout<<"Press B if you want to change Current Balance \n";
		cout<<"Press C if you want no more change \n";
		cout<<"Enter your option :";
		ch=getche();
		switch(ch)
		{
			case 'A':
			case 'a': 	cout<<"\nEnter new Name : ";
					gets(Name);
					break;
			case 'B':
			case 'b': 	cout<<"\nEnter new Balance : ";
					cin>>Balance;
					break;
			case 'C':
			case 'c': 	break;

			default :	cout<<"\nWrong Option !! Try Again !!";
		}
	}while(ch!='C' && ch!='c');
}













//	**************************** DAY TO DAY TRANSACTION (DEPOSIT/WITHDRAW) *****************************
void Transaction()
{
	int san;
	Customer C;
	int Done = 0;

	cout<<"\n\nEnter the Account Number : ";
	cin>>san;


	fstream f1,f2;
	f1.open("BANK.DAT",ios::binary|ios::in);
	f2.open("TEMP.DAT",   ios::binary|ios::out);

	while( f1.read((char*) &C, sizeof(C)) )
	{
		if(C.RetAccNo()==san)
		{
			Done++ ;
			C.Transaction();
		}
		f2.write((char *) &C, sizeof(C));
	}

	f1.close();
	f2.close();

	if (Done == 0)
		cout<<"\n\n NO MATCH FOUND !! \n\n";
	     else
		{
			remove("BANK.DAT");
			rename("TEMP.DAT" , "BANK.DAT");
		}

}





//	**************************** APPEND (ADD) A NEW RECORD *****************************
void Append()
{
	Customer C;
	int NewAccNo;
	int Found ;

	do{
		cout<<"\n\nEnter the Account Number to be created : ";
		cin>>NewAccNo;

		Found = 0;

		fstream f1;
		f1.open("BANK.DAT",ios::binary|ios::in);

		while( f1.read((char*) &C, sizeof(C)) )
		{
			if(C.RetAccNo()==NewAccNo)
			{
				Found++ ;
			}
		}
		f1.close();
		if (Found != 0)
		cout<<"\n\n SORRY ! THIS ACCOUNT NUMBER ALREADY EXISTS!! \n\n";
	}while(Found!=0);

	cout<<"\nEnter the Detail of the Account Number : "<<NewAccNo<<endl;
	C.Getdata(NewAccNo);

	fstream f2;
	f2.open("BANK.DAT",ios::binary|ios::app);

	f2.write((char*) &C, sizeof(C));
	f2.close();

}




//	**************************** DISPLAY ALL RECORDS *****************************
void DisplayAll()
{
	Customer C;
	fstream f1;
	f1.open("BANK.DAT",ios::binary|ios::in);
	while( f1.read((char*) &C, sizeof(C)) )
	{
		C.Showdata();
	}
	f1.close();
}


//	**************************** SEARCH A RECORD BY ACCOUNT NUMBER *****************************
void Search1()
{
	int san;
	Customer C;
	int Found = 0;
	cout<<"\n\nEnter the Account Number to be searched : ";
	cin>>san;
	fstream f1;
	f1.open("BANK.DAT",ios::binary|ios::in);
	while( f1.read((char*) &C, sizeof(C)) )
	{
		if(C.RetAccNo()==san)
		{
			Found++ ;
			C.Showdata();
		}
	}
	f1.close();
	if (Found == 0)
		cout<<"\n\n NO MATCH FOUND !! \n\n";
	     else
		cout<<"\n\n TOTAL "<< Found << " RECORD(S) FOUND !! \n\n";
}




//	**************************** SEARCH A RECORD BY NAME *****************************
void Search2()
{

	char sn[50];
	Customer C;
	int Found = 0;

	cout<<"\n\nEnter the Name to be searched : ";
	gets(sn);

	fstream f1;
	f1.open("BANK.DAT",ios::binary|ios::in);

	while( f1.read((char*) &C, sizeof(C)) )
	{
		if(strcmp(C.RetName(), sn)==0)
		{
			Found++ ;
			C.Showdata();

		}
	}

	f1.close();

	if (Found == 0)
		cout<<"\n\n NO MATCH FOUND !! \n\n";
	     else
		cout<<"\n\n TOTAL "<< Found << " RECORD(S) FOUND !! \n\n";
}











//	**************************** EDIT/ MODIFY A RECORD *****************************
void Modify()
{
	int san;
	Customer C;
	int Modified = 0;

	cout<<"\n\nEnter the Account Number to be modified : ";
	cin>>san;


	fstream f1,f2;
	f1.open("BANK.DAT",ios::binary|ios::in);
	f2.open("TEMP.DAT",   ios::binary|ios::out);

	while( f1.read((char*) &C, sizeof(C)) )
	{
		if(C.RetAccNo()==san)
		{
			Modified++ ;
			C.Edit();
		}
		f2.write((char *) &C, sizeof(C));
	}

	f1.close();
	f2.close();



	if (Modified == 0)
		cout<<"\n\n NO MATCH FOUND !! \n\n";
	     else
		{
			remove("BANK.DAT");
			rename("TEMP.DAT" , "BANK.DAT");
		}
}




//	**************************** DELETE A RECORD *****************************
void Delete()
{
	int san;
	Customer C;
	int Deleted = 0;

	cout<<"\n\nEnter the Account Number to be deleted : ";
	cin>>san;


	fstream f1,f2;
	f1.open("BANK.DAT",ios::binary|ios::in);
	f2.open("TEMP.DAT",   ios::binary|ios::out);

	while( f1.read((char*) &C, sizeof(C)) )
	{
		if(C.RetAccNo()==san)
			Deleted ++ ;
		     else
			f2.write((char *) &C, sizeof(C));
	}

	f1.close();
	f2.close();



	if (Deleted == 0)
		cout<<"\n\n NO MATCH FOUND !! \n\n";
	     else
		{
			remove("BANK.DAT");
			rename("TEMP.DAT" , "BANK.DAT");
		}

}





void main()
{
	char choice;
	do{
		clrscr();
		cout<<"Menu\n";
		cout<<"Press 1 for TRANSACTION (DEPOSITE/WITHDRAWL) \n";
		cout<<"Press 2 for OPENNING A NEW ACCOUNT \n";
		cout<<"Press 3 for DISPLAY DETAILS ALL CUSTOMERS \n";
		cout<<"Press 4 for SEARCH BY ACCOUNT NUMBER \n";
		cout<<"Press 5 for SEARCH BY NAME OF CUSTOMER \n";
		cout<<"Press 6 for MODIFY AN ACCOUNT \n";
		cout<<"Press 7 for DELETE AN ACCOUNT \n";
		cout<<"Press 8 for QUIT \n";
		cout<<"Enter your choice : ";
		choice=getche();
		switch(choice)
		{
			case '1': Transaction();break;
			case '2': Append();	break;
			case '3': DisplayAll();	break;
			case '4': Search1();	break;
			case '5': Search2();	break;
			case '6': Modify();	break;
			case '7': Delete();	break;
			case '8': 		break;
			default :cout<<"\nWrong Choice Entered !!\n\n";
		}
		getch();
	}while(choice!='8');
}
