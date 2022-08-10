#include<unistd.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef struct normalUser{
	int userID;
	char username[30];
	char password[10];
	int account_no;
	float balance;
	char status[20];
}normalUser;

typedef struct jointUser{
	int userID;
	char username1[30];
	char username2[30];
	char password[10];
	int account_no;
	float balance;
	char status[20];
}jointUser;

typedef struct admin{
	int userID;
	char username[30];
	char password[10];
}admin;

int input,currID;
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);
void LoginAsNorUser(int sd);
void LoginAsJointUser(int sd);
void AdminLogin(int sd);
void intromenu(int sd);
void DepMoney(int sd);
void WithMoney(int sd);
void Balance(int sd);
void changePassword(int sd);
void View(int sd);

void choosemenu(int sd){
	while(1){
		write(1,"Choose an option : \n",sizeof("Choose an option : \n"));

		write(1,"1 : Normal User Login\n",sizeof("1 : Normal-User Login\n"));
		write(1,"2 : Joint Account-User Login\n",sizeof("2 : Joint Account-User Login\n"));
		write(1,"3 : Admin Login\n",sizeof("3 : Admin Login\n"));
		
		scanf("%d",&input);
		printf("Option chosen: %d\n",input);

		switch (input)
		{
		case 1:{
			LoginAsNorUser(sd); 
			break;
		}
		case 2:{
			LoginAsJointUser(sd);
			break;
		}
		case 3:{
			AdminLogin(sd);
			break;
		}
		default:
			write(1,"Invalid input!!\n\n",sizeof("Invalid input\n\n"));
			break;
		}
	
	}
	return;
}

void intromenu(int sd){
	int menuoption;
	if(input==1 || input==2){
		write(1,"Choose an option : \n",sizeof("Choose an option : \n"));
		write(1,"1 : Deposit Money\n",sizeof("1 : Deposit Money\n"));
		write(1,"2 : Withdraw Money\n",sizeof("2 : Withdraw Money\n"));
		write(1,"3 : Balance Enquiry\n",sizeof("3 : Balance Enquiry\n"));
		write(1,"4 : Password Change\n",sizeof("4 : Password Change\n"));
		write(1,"5 : View Details\n",sizeof("5 : View Details\n"));
		write(1,"6 : Exit\n",sizeof("6 : Exit\n"));

		scanf("%d",&menuoption);
		printf("Option : %d\n",menuoption);
		
		switch(menuoption){
		case 1 :
			DepMoney(sd);
			break;
		case 2 :
			WithMoney(sd);
			break;
		case 3 :
			Balance(sd);
			break;
		case 4 :
			changePassword(sd);
			break;
		case 5 :
			View(sd);
			break;
		case 6 :
			write(sd,&menuoption,sizeof(int));
			write(1,"Thank you for visiting the bank\n",sizeof("Thank you for visiting the bank\n"));
			exit(0);
		default :
			write(1,"Invalid option\n\n",sizeof("Invalid option\n\n"));
			intromenu(sd);
			break;
		}
	}
	else if(input==3){
		write(1,"1 : Add Account\n",sizeof("1 : Add Account\n"));
		write(1,"2 : Delete Account\n",sizeof("2 : Delete Account\n"));
		write(1,"3 : Modify Account\n",sizeof("3 : Modify Account\n"));
		write(1,"4 : Search Account\n",sizeof("4 : Search Account\n"));
		write(1,"5 : Exit\n",sizeof("6 : Exit\n"));

		write(1,"Choose an option : ",sizeof("Choose an option : "));
		scanf("%d",&menuoption);
		printf("Option : %d\n",menuoption);
		
		switch(menuoption){
		case 1 :
			addAccount(sd);
			break;
		case 2 :
			deleteAccount(sd);
			break;
		case 3 :
			modifyAccount(sd);
			break;
		case 4 :
			searchAccount(sd);
			break;
		case 5 :
			write(sd,&menuoption,sizeof(int));
			write(1,"Thank you\n",sizeof("Thank you\n"));
			exit(0);
		default :
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			intromenu(sd);
			break;
		}
	}
}

void LoginAsNorUser(int sd){
	bool r;
	normalUser currUser;
	printf("User ID: ");
	scanf("%d",&currUser.userID);
	currID=currUser.userID;
	printf("Password: ");
	scanf("%s",currUser.password);

	write(sd,&input,sizeof(int));  //to the server
	write(sd,&currUser,sizeof(normalUser));

	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		printf("Invalid login\n\n");
		choosemenu(sd);
	}
	else{
		printf("Login successful\n\n");
		intromenu(sd);
	}
	return;
}

void LoginAsJointUser(int sd){
	bool r;
	jointUser currUser;
	printf("User ID : ");
	scanf("%d",&currUser.userID);
	currID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	//to the server
	write(sd,&input,sizeof(int));
	write(sd,&currUser,sizeof(jointUser));

	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		printf("Invalid login\n\n");
		choosemenu(sd);
	}
	else{
		printf("Login successful\n\n");
		intromenu(sd);
	}
	return;
}

void AdminLogin(int sd){
	bool r;
	admin currUser;
	printf("User ID: ");
	scanf("%d",&currUser.userID);
	currID=currUser.userID;
	printf("Password: ");
	scanf("%s",currUser.password);


	write(sd,&input,sizeof(int));	//to the server
	write(sd,&currUser,sizeof(admin));

	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		printf("Invalid login\n\n");
		choosemenu(sd);
	}
	else{
		printf("Login successful\n\n");
		intromenu(sd);
	}
	return;
}

void DepMoney(int sd){
	
	bool r;
	float amount;
	int select=1;


	printf("Amount to Deposit : ");
	scanf("%f",&amount);

	while(amount<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Deposit : ",sizeof("Amount to Deposit : "));
		scanf("%f",&amount);
	}

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,&amount,sizeof(float));

	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		printf("Error in deposting\n\n");
	}
	else{
		printf("Succesfully deposited\n\n");
	}
	intromenu(sd);
	return;
}

void WithMoney(int sd){
	bool r;
	float amount;
	int select=2;


	write(1,"Amount to Withdraw : ",sizeof("Amount to Withdraw : "));
	scanf("%f",&amount);

	while(!amount>0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Withdraw : ",sizeof("Amount to Withdraw : "));
		scanf("%f",&amount);
	}

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,&amount,sizeof(float));

	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		write(1,"Error in withdrawal\n\n",sizeof("Error in withdrawal\n\n"));
	}
	else{
		write(1,"Succesful withdrawal!!\n\n",sizeof("Succesful withdrawal!!\n\n"));
	}
	intromenu(sd);
	return;
}

void Balance(int sd){
	
	int slt=3;
	float amount;

	write(sd,&slt,sizeof(int));
	
	read(sd,&amount,sizeof(float));
	printf("Available Balance :: Rs.%0.2f\n\n",amount);

	intromenu(sd);
	return;
}

void changePassword(int sd){

	char newpass[10];
	bool r;
	int select=4;


	printf("Enter new password: ");
	scanf("%s",newpass);

	write(sd,&select,sizeof(int));
	write(sd,newpass,sizeof(newpass));

	read(sd,&r,sizeof(r));

	if(!r){
		write(1,"Error while changing your password\n\n",sizeof("Error while changing your password\n\n"));
	}
	else{
		write(1,"Succesfully changed your password\n\n",sizeof("Succesfully changed your password\n\n"));
	}
	intromenu(sd);
	return;
}

void View(int sd){
	int select=5;

	//to the server
	write(sd,&select,sizeof(int));

	if(input==1){
		normalUser us1;
		read(sd,&us1,sizeof(normalUser));
		
		printf("User ID : %d\n",us1.userID);
		printf("Name : %s\n",us1.username);
		printf("Account Number : %d\n",us1.account_no);
		printf("Available Balance : Rs.%0.2f\n",us1.balance);
		printf("Status : %s\n\n",us1.status);
	}
	else if(input==2){
		jointUser uj;
		read(sd,&uj,sizeof(jointUser));
		
		printf("User ID : %d\n",uj.userID);
		printf("First Account Holder's Name : %s\n",uj.username1);
		printf("Second Account Holder's Name : %s\n",uj.username2);
		printf("Account Number : %d\n",uj.account_no);
		printf("Available Balance : Rs.%0.2f\n",uj.balance);
		printf("Status : %s\n\n",uj.status);
	}
	intromenu(sd);
	return;
}

void addAccount(int sd){
	int select=1;
	int type;
	bool r;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser newUser;
		write(1,"Account holder's name : ",25);
		scanf(" %[^\n]",newUser.username);
		write(1,"Password(maximum 10 characters) : ",35);
		scanf("%s",newUser.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&newUser.balance);
		write(sd,&newUser,sizeof(normalUser));
	}

	if(type==2){
		jointUser newJ;
		write(1,"Primary Username : ",20);
		scanf(" %[^\n]",newJ.username1);
		write(1,"Secondary Username",19);
		scanf(" %[^\n]",newJ.username2);
		write(1,"Password(max 10 characters) : ",sizeof("Password(max 10 characters) : "));
		scanf("%s",newJ.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&newJ.balance);
		write(sd,&newJ,sizeof(jointUser));
	}
	
	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		write(1,"Error adding the account!!\n\n",sizeof("Error adding the account!!\n\n"));
	}
	else{
		write(1,"Succesfully added the account!!\n\n",sizeof("Succesfully added the account!!\n\n"));
	}
	intromenu(sd);
	return;
}

void deleteAccount(int sd){
	int select=2;
	int type,userID;
	bool r;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);
	
	write(sd,&type,sizeof(int));

	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&userID);
	write(sd,&userID,sizeof(int));
	
	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		write(1,"Error deleting the account ,please re-check the User ID!!\n\n",sizeof("Error deleting the account ,please re-check the User ID!!\n\n"));
	}
	else{
		write(1,"Succesfully deleted the account!!\n\n",sizeof("Succesfully deleted the account!!\n\n"));
	}
	intromenu(sd);
	return;
}

void modifyAccount(int sd){
	int select=3;
	int type;
	bool r;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser modUser1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser1.userID);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser1.account_no);
		write(1,"New Name of the account holder : ",sizeof("New Name of the account holder : "));
		scanf(" %[^\n]",modUser1.username);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser1.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser1.balance);
		write(sd,&modUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser modUser2;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser2.userID);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser2.account_no);
		write(1,"New Name of the primary account holder : ",sizeof("New Name of the primary account holder : "));
		scanf(" %[^\n]",modUser2.username1);
		write(1,"New Name of the other account holder : ",sizeof("New Name of the other account holder : "));
		scanf(" %[^\n]",modUser2.username2);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser2.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser2.balance);
		write(sd,&modUser2,sizeof(jointUser));
	}
	
	read(sd,&r,sizeof(r)); //from the server

	if(!r){
		write(1,"Error modifying the account ,please re-check the User ID and Account No!!\n\n",sizeof("Error modifying the account ,please re-check the User ID and Account No!!\n\n"));
	}
	else{
		write(1,"Succesfully modified the account!!\n\n",sizeof("Succesfully modified the account!!\n\n"));
	}
	intromenu(sd);
	return;
}

void searchAccount(int sd){
	int select=4;
	int type,len;
	bool r;

	write(sd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser searchUser1;
		int userID;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser1,sizeof(normalUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser1.userID);
			printf("Name : %s\n",searchUser1.username);
			printf("Account Number : %d\n",searchUser1.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
			printf("Status : %s\n\n",searchUser1.status);
		}
	}

	if(type==2){
		jointUser searchUser2;
		int userID1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID1);
		write(sd,&userID1,sizeof(int));
		
		len=read(sd,&searchUser2,sizeof(jointUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser2.userID);
			printf("Main Account Holder's Name : %s\n",searchUser2.username1);
			printf("Other Account Holder's Name : %s\n",searchUser2.username2);
			printf("Account Number : %d\n",searchUser2.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.balance);
			printf("Status : %s\n\n",searchUser2.status);
		}
	}
	intromenu(sd);
	return;
}

int main(){
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char r;


	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1"); 
	server.sin_port=htons(5557);
	connect(sd,(struct sockaddr *)&server,sizeof(server));

	choosemenu(sd);
	intromenu(sd);	

	close(sd);

	return 0;
}

