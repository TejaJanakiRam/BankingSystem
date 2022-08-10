/*Populating records*/
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>

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

int newUserTyp1();
int newUserTyp2();
int newUserTyp3();

int newUserTyp1(){
	int fd=open("nu",O_RDONLY,0744);
	normalUser record;
	lseek(fd,-sizeof(normalUser),SEEK_END);
	read(fd,&record,sizeof(normalUser));
	close(fd);
	return record.userID+1;
}

int newUserTyp2(){
	int fd=open("ju",O_RDONLY,0744);
	jointUser record;
	lseek(fd,-sizeof(jointUser),SEEK_END);
	read(fd,&record,sizeof(jointUser));
	close(fd);
	return record.userID+1;
}

int newUserTyp3(){
	int fd=open("adm",O_RDONLY,0744);
	admin record;
	lseek(fd,-sizeof(admin),SEEK_END);
	read(fd,&record,sizeof(admin));
	close(fd);
	return record.userID+1;
}

int main(){
	int fd=open("adm",O_RDWR | O_CREAT,0744);
	int choice=0;
	admin newAdm;
	printf("Enter the name of the admin: ");
	scanf(" %s",newAdm.username);
	printf("Enter the password(max 10 characters): ");
	scanf(" %s",newAdm.password);
	newAdm.userID=1000;
	printf("Your userID is : %d\n",newAdm.userID);
	write(fd,&newAdm,sizeof(newAdm));
	printf("Do you want to continue(0-No/1-Yes) ?");
	scanf("%d",&choice);
	while(choice){
		printf("Enter the name of the admin: ");
		scanf(" %[^\n]",newAdm.username);
		printf("Enter the password(max 10 characters): ");
		scanf(" %[^\n]",newAdm.password);
		newAdm.userID=newUserTyp3();
		printf("Your userID is : %d\n",newAdm.userID);
		write(fd,&newAdm,sizeof(admin));
		printf("Do you want to continue(0-No/1-Yes) ?");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("nu",O_RDWR | O_CREAT,0744);
	choice=1;
	normalUser newNu;
	printf("Enter the name of the normal user: ");
	scanf(" %[^\n]",newNu.username);
	printf("Enter the password(max 10 characters): ");
	scanf(" %[^\n]",newNu.password);
	newNu.userID=1000;
	newNu.balance=1000;
	newNu.account_no=(newNu.userID-1000)+100000;
	printf("Your userID is : %d\n",newNu.userID);
	strcpy(newNu.status,"ACTIVE");
	write(fd,&newNu,sizeof(normalUser));
	printf("Do you want to continue(0-No/1-Yes) ?");
	scanf("%d",&choice);
	while(choice){
		printf("Enter the name of the normal user: ");
		scanf(" %[^\n]",newNu.username);
		printf("Enter the password(max 10 characters): ");
		scanf(" %[^\n]",newNu.password);
		newNu.userID=newUserTyp1();
		newNu.balance=1000;
		newNu.account_no=(newNu.userID-1000)+100000;
		printf("Your userID is : %d\n",newNu.userID);
		strcpy(newNu.status,"ACTIVE");
		write(fd,&newNu,sizeof(normalUser));
		printf("Do you want to continue(0-No/1-Yes) ?");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("ju",O_RDWR | O_CREAT,0744);
	choice=1;
	jointUser newJ;
	printf("Enter the main name of the joint user: ");
	scanf(" %[^\n]",newJ.username1);
	printf("Enter the second name of the joint user: ");
	scanf(" %[^\n]",newJ.username2);
	printf("Enter the password(max 10 characters): ");
	scanf(" %[^\n]",newJ.password);
	newJ.userID=1000;
	newJ.balance=1000;
	newJ.account_no=(newJ.userID-1000)+100000;
	printf("Your userID is : %d\n",newJ.userID);
	strcpy(newJ.status,"ACTIVE");
	write(fd,&newJ,sizeof(jointUser));
	printf("Do you want to continue(0-No/1-Yes) ?");
	scanf("%d",&choice);
	while(choice){
		printf("Enter the main name of the joint user: ");
		scanf(" %[^\n]",newJ.username1);
		printf("Enter the second name of the joint user: ");
		scanf(" %[^\n]",newJ.username2);
		printf("Enter the password(max 10 characters): ");
		scanf(" %[^\n]",newJ.password);
		newJ.userID=newUserTyp2();
		newJ.balance=1000;
		newJ.account_no=(newJ.userID-1000)+100000;
		printf("Your userID is : %d\n",newJ.userID);
		strcpy(newJ.status,"ACTIVE");
		write(fd,&newJ,sizeof(jointUser));
		printf("Do you want to continue(0-No/1-Yes) ?");
		scanf("%d",&choice);
	}
	close(fd);
	return 0;
}


