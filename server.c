#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <pthread.h>

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

normalUser retNUser(int ID){
	int i=ID-1000;
	normalUser curuzr;
	int fd=open("nu",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     
	lock.l_len=sizeof(normalUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&curuzr,sizeof(normalUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return curuzr;
}

jointUser retJUser(int ID){
	int i=ID-1000;
	jointUser curuzr;
	int fd=open("ju",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     
	lock.l_len=sizeof(jointUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&curuzr,sizeof(jointUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return curuzr;
}

admin retAdm(int ID){
	int i=ID-1000;
	admin curuzr;
	int fd=open("adm",O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     
	lock.l_len=sizeof(admin);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  
	read(fd,&curuzr,sizeof(admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return curuzr;
}

bool authNU(normalUser curuzr){
	int i=curuzr.userID-1000;
	int fd=open("nu",O_RDONLY,0744);
	bool r;
	normalUser temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     
	lock.l_len=sizeof(normalUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&temp,sizeof(normalUser));
	if(!strcmp(temp.password,curuzr.password) && !strcmp(temp.status,"ACTIVE"))	r=true;
	else						r=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return r;
}

bool authJU(jointUser curuzr){
	int i=curuzr.userID-1000;
	int fd=open("ju",O_RDONLY,0744);
	bool r;
	jointUser temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     
	lock.l_len=sizeof(jointUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&temp,sizeof(jointUser));
	if(!strcmp(temp.password,curuzr.password) && !strcmp(temp.status,"ACTIVE"))	r=true;
	else						r=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return r;
}

bool authAdm(admin curuzr){
	int i=curuzr.userID-1000;
	int fd=open("adm",O_RDONLY,0744);
	bool r;
	admin temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     
	lock.l_len=sizeof(admin);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  
	read(fd,&temp,sizeof(admin));
	if(!strcmp(temp.password,curuzr.password))	r=true;
	else						r=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return r;
}

bool depMoney(int actyp,int ID,float amount){
	int i=ID-1000;
	if(actyp==1){
		int fd=open("nu",O_RDWR,0744);
		bool r;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    
		lock.l_len=sizeof(normalUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		getchar();

		normalUser curuzr;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&curuzr,sizeof(normalUser));
		
		if(!strcmp(curuzr.status,"ACTIVE")){
			curuzr.balance+=amount;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&curuzr,sizeof(normalUser));
			r=true;
		}
		else	r=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;		
	}
	else if(actyp==2){
		int fd=open("ju",O_RDWR,0744);
		bool r;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		getchar();

		jointUser curuzr;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&curuzr,sizeof(jointUser));
		
		if(!strcmp(curuzr.status,"ACTIVE")){
			curuzr.balance+=amount;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&curuzr,sizeof(jointUser));
			r=true;
		}
		else	r=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;	
	}
	return false;
}

bool withDrMoney(int actyp,int ID,float amount){
	int i=ID-1000;
	if(actyp==1){
		int fd=open("nu",O_RDWR,0744);
		bool r;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    
		lock.l_len=sizeof(normalUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		getchar();

		normalUser curuzr;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&curuzr,sizeof(normalUser));
		
		if(!strcmp(curuzr.status,"ACTIVE") && curuzr.balance>=amount){
			curuzr.balance-=amount;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&curuzr,sizeof(normalUser));
			r=true;
		}
		else	r=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;	
	}
	else if(actyp==2){
		int fd=open("ju",O_RDWR,0744);
		bool r;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		getchar();

		jointUser curuzr;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&curuzr,sizeof(jointUser));
		
		if(!strcmp(curuzr.status,"ACTIVE") && curuzr.balance>=amount){
			curuzr.balance-=amount;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&curuzr,sizeof(jointUser));
			r=true;
		}
		else	r=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;
	}
	return false;
}

float retBal(int actyp,int ID){
	int i=ID-1000;
	float r;
	if(actyp==1){
		int i=ID-1000;
		int fd=open("nu",O_RDONLY,0744);
		normalUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    	     
		lock.l_len=sizeof(normalUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	


		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&temp,sizeof(normalUser));
		if(!strcmp(temp.status,"ACTIVE"))	r=temp.balance;
		else					r=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;
	}
	else if(actyp==2){
		int i=ID-1000;
		int fd=open("ju",O_RDONLY,0744);
		jointUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    	     
		lock.l_len=sizeof(jointUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	


		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&temp,sizeof(jointUser));
		if(!strcmp(temp.status,"ACTIVE"))	r=temp.balance;
		else					r=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;
	}
	return 0;
}

bool chgPass(int actyp,int ID,char newPwd[10]){
	int i=ID-1000;
	if(actyp==1){
		int fd=open("nu",O_RDWR,0744);
		bool r;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    
		lock.l_len=sizeof(normalUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	


		normalUser curuzr;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&curuzr,sizeof(normalUser));
		
		if(!strcmp(curuzr.status,"ACTIVE")){
			strcpy(curuzr.password,newPwd);
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&curuzr,sizeof(normalUser));
			r=true;
		}
		else	r=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;
	}
	else if(actyp==2){
		int fd=open("ju",O_RDWR,0744);
		bool r;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	


		jointUser curuzr;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&curuzr,sizeof(jointUser));
		
		if(!strcmp(curuzr.status,"ACTIVE")){
			strcpy(curuzr.password,newPwd);
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&curuzr,sizeof(jointUser));
			r=true;
		}
		else	r=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return r;
	}
	return false;
}

bool addNU(normalUser record){
	int fd=open("nu",O_RDWR,0744);
	bool r;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(normalUser);    
	lock.l_len=sizeof(normalUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	normalUser endUser;
	lseek(fd,(-1)*sizeof(normalUser),SEEK_END);  
	read(fd,&endUser,sizeof(normalUser));
		
	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(normalUser));
	if(j!=0)	r=true;
	else	r=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return r;	
}

bool addJU(jointUser record){
	int fd=open("ju",O_RDWR,0744);
	bool r;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser endUser;
	lseek(fd,(-1)*sizeof(jointUser),SEEK_END);  
	read(fd,&endUser,sizeof(jointUser));
		
	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(jointUser));
	if(j!=0)	r=true;
	else	r=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return r;	
}

bool delNU(int ID){
	int i=ID-1000;
	int fd=open("nu",O_RDWR,0744);
	bool r;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    
	lock.l_len=sizeof(normalUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	normalUser curuzr;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&curuzr,sizeof(normalUser));
	
	if(!strcmp(curuzr.status,"ACTIVE")){	
		strcpy(curuzr.status,"CLOSED");
		curuzr.balance=0;
		
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&curuzr,sizeof(normalUser));
		if(j!=0)	r=true;
		else		r=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return r;	
}

bool delJU(int ID){
	int i=ID-1000;
	int fd=open("ju",O_RDWR,0744);
	bool r;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser curuzr;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&curuzr,sizeof(jointUser));
	
	if(!strcmp(curuzr.status,"ACTIVE")){	
		strcpy(curuzr.status,"CLOSED");
		curuzr.balance=0;
		
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&curuzr,sizeof(jointUser));
		if(j!=0)	r=true;
		else		r=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return r;	
}

bool modNU(normalUser modUser){
	int i=modUser.userID-1000;
	int fd=open("nu",O_RDWR,0744);
	bool r=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    
	lock.l_len=sizeof(normalUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	normalUser curuzr;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&curuzr,sizeof(normalUser));
	
	if(!strcmp(curuzr.status,"ACTIVE") && (modUser.account_no==curuzr.account_no)){	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(normalUser));
		if(j!=0)	r=true;
		else		r=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return r;	
}

bool modJU(jointUser modUser){
	int i=modUser.userID-1000;
	int fd=open("ju",O_RDWR,0744);
	bool r=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser curuzr;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&curuzr,sizeof(jointUser));
	
	if(!strcmp(curuzr.status,"ACTIVE")  && (modUser.account_no==curuzr.account_no)){	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(jointUser));
		if(j!=0)	r=true;
		else		r=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return r;	
}

void srvTsk(int nsd){
	int msgLength,slct,type,option,actyp,curUzrId;
	bool r;
	while(1){
		read(nsd,&option,sizeof(option));
		printf("Option : %d\n",option);

		if(option==1){
			normalUser currUser1;
			actyp=1;
			msgLength=read(nsd,&currUser1,sizeof(normalUser));
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			curUzrId=currUser1.userID;
			r=authNU(currUser1);
			write(nsd,&r,sizeof(r));
		}
		else if(option==2){
			jointUser currUser2;
			actyp=2;
			msgLength=read(nsd,&currUser2,sizeof(jointUser));
			curUzrId=currUser2.userID;
			printf("Username : %d\n",currUser2.userID);
			printf("Password : %s\n",currUser2.password);
			r=authJU(currUser2);
			write(nsd,&r,sizeof(r));
		}
		else if(option==3){
			admin currUser3;
			actyp=3;
			msgLength=read(nsd,&currUser3,sizeof(admin));
			curUzrId=currUser3.userID;
			printf("Username : %d\n",currUser3.userID);
			printf("Password : %s\n",currUser3.password);
			r=authAdm(currUser3);
			write(nsd,&r,sizeof(r));
		}
		else{
			r=false;
			write(nsd,&r,sizeof(r));
		}
		if(r)	break;		
	}

	while(1){
		read(nsd,&slct,sizeof(int));
		if(option==1 || option==2){
			if(slct==1){
				float amount;
				read(nsd,&amount,sizeof(float));
				r=depMoney(actyp,curUzrId,amount);
				write(nsd,&r,sizeof(r));
			}
			else if(slct==2){
				float amount;
				read(nsd,&amount,sizeof(float));
				r=withDrMoney(actyp,curUzrId,amount);
				write(nsd,&r,sizeof(r));
			}
			else if(slct==3){
				float amount;
				amount=retBal(actyp,curUzrId);
				write(nsd,&amount,sizeof(float));
			}
			else if(slct==4){
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				r=chgPass(actyp,curUzrId,pwd);
				write(nsd,&r,sizeof(r));
			}
			else if(slct==5){
				if(option==1){
					normalUser user1=retNUser(curUzrId);
					write(nsd,&user1,sizeof(normalUser));
				}
				else if(option==2){
					jointUser user2=retJUser(curUzrId);
					write(nsd,&user2,sizeof(jointUser));
				}
			}
			else if(slct==6)	break;
		}
		else if(option==3){
			read(nsd,&type,sizeof(int));
			if(slct==1){
				if(type==1){
					normalUser newUser1;
					read(nsd,&newUser1,sizeof(normalUser));
					r=addNU(newUser1);
					write(nsd,&r,sizeof(r));
				}
				else if(type==2){
					jointUser newUser2;
					read(nsd,&newUser2,sizeof(jointUser));
					r=addJU(newUser2);
					write(nsd,&r,sizeof(r));
				}
			}
			else if(slct==2){
				if(type==1){
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					r=delNU(delUserID1);
					write(nsd,&r,sizeof(r));
				}
				else if(type==2){
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					r=delJU(delUserID2);
					write(nsd,&r,sizeof(r));
				}
			}
			else if(slct==3){
				if(type==1){
					normalUser modUser1;
					read(nsd,&modUser1,sizeof(normalUser));
					r=modNU(modUser1);
					write(nsd,&r,sizeof(r));
				}
				else if(type==2){
					jointUser modUser2;
					read(nsd,&modUser2,sizeof(jointUser));
					r=modJU(modUser2);
					write(nsd,&r,sizeof(r));
				}
			}
			else if(slct==4){
				if(type==1){
					normalUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=retNUser(userID1);
					write(nsd,&searchUser1,sizeof(normalUser));
				}
				else if(type==2){
					jointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=retJUser(userID2);
					write(nsd,&searchUser2,sizeof(jointUser));
				}
			}
			else if(slct==5)	break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

void *connection_handler(void *nsd) {
	int nsfd = *(int*)nsd;
	srvTsk(nsfd);
}


int main(){
	struct sockaddr_in server,client;
	pthread_t thrds;
	bool r;
	int sd,nsd,cliSz;

	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5557);

	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);
	
	write(1,"Waiting for the client...\n",sizeof("Waiting for the client...\n"));
	while(1){
		cliSz=sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&cliSz);

		write(1,"Connected to the client...\n",sizeof("Connected to the client...\n"));
		if(pthread_create(&thrds,NULL,connection_handler,(void*) &nsd)<0){
			perror("Couldn't create thread");
			return 1;
		}		
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}
