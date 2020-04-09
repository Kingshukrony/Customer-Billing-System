#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct date{
	   int month;
	   int day;
	   int year;
};

struct account {
	int number;
	char name[100];
	char acc_no;
	char mobile_no[11];
	char street[100];
	char city[100];
	char acct_type;
	float oldbal;
	float newbal;
	float payment;
	struct date lastpayment;
}customer;

int getTotalCustomer(){
	FILE *fp1;	
	char c;
	int totalCustomer=0;
	
	fp1=fopen("a.txt","r+");	
	fscanf(fp1,"%d",&totalCustomer);
	if(totalCustomer==0){  		//when no customer exist
		fprintf(fp1,"%d\n",0);
		FILE *fp;
		fp=fopen("database.txt","r+");
		fprintf(fp,"\n");
		fclose(fp);
	}
	fclose(fp1);
	return totalCustomer;
}
void updateTotCustomer(int newTotalCustomer){
	FILE *fp1;	
	fp1=fopen("a.txt","r+");
	fprintf(fp1,"%d\n",newTotalCustomer);
	fclose(fp1);
}

void custInput(int custAccountNo){
	FILE *fp;	
	fp=fopen("database.txt","r+");
	fseek(fp,0L,2);		//move file pointer at the last position of file
				
	fprintf(fp,"%d|",custAccountNo);
	fflush(stdin);		//empty the buffer
	printf("         Name:");
	gets(customer.name);
	fprintf(fp,"%s|",customer.name);
	fflush(stdin);
	printf("         mobile no:");
	gets(customer.mobile_no);
	fprintf(fp,"%s|",customer.mobile_no);
	fflush(stdin);
	printf("         Street:");
	gets(customer.street);
	fprintf(fp,"%s|",customer.street);
	fflush(stdin);
	printf("         City:");
	gets(customer.city);
	fprintf(fp,"%s|",customer.city);
	fflush(stdin);
	printf("         Previous Due Balance:");
	scanf("%f",&customer.oldbal);
	fprintf(fp,"%.2f|",customer.oldbal);
	fflush(stdin);
	printf("         Current payment:");
	scanf("%f",&customer.payment);
	fprintf(fp,"%.2f|",customer.payment);
	fprintf(fp,"%.2f|",customer.oldbal-customer.payment);
	fflush(stdin);
	printf("         Payment date(mm/dd/yyyy):");
	scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
	fprintf(fp,"%d/%d/%d|",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
	fprintf(fp,"\n");
	fclose(fp);
}

char tempOutput[30];
void display(FILE *fp){
	int i=0;
	char c;
	
	strcpy(tempOutput,"");
	c=getc(fp);	
	while(c!='|' && c!='\n'){
		tempOutput[i]=c;
		i++;
		c=getc(fp);
	}
	tempOutput[i]='\0';
}
void searchCustomer(int choice){
	FILE *fp;
	int totalCustomer, AcNoSearch, flag=0;	//flag=0 match not found, flag=1 match found
	char c;
	char nameSearch[20];
	
	totalCustomer=getTotalCustomer();
	
	if(choice==1){	
		printf("Enter Account Number to search : ");
		scanf("%d",&AcNoSearch);
	}else{
		printf("Enter name to search : ");
		fflush(stdin);
		gets(nameSearch);
	}
	
	fp=fopen("database.txt","r");
	while((c=getc(fp))!=EOF){
		int tempSearch=0;
		char tempNameSearch[20]="";
		if(c=='\n'){
			totalCustomer--;
			if(totalCustomer>=0){
				c=getc(fp);
				while(c!='|'){			//fetching the account number from file
					tempSearch=tempSearch*10+((int)c-48);	
					c=getc(fp);									
				}				
				if(choice==1){
					if(tempSearch==AcNoSearch){
						printf("\n         Account No:\t\t\t%d",tempSearch);					
						printf("\n\n         Name:\t\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         mobile no:\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         Street:\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         City:\t\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         Previous Due Balance:\t\t");
						display(fp);
						puts(tempOutput);												
						printf("\n         Current payment:\t\t");
						display(fp);
						puts(tempOutput);						
						printf("\n         New Due Balance:\t\t");	
						display(fp);
						puts(tempOutput);					
						printf("\n         Payment date(mm/dd/yyyy):\t");
						display(fp);	
						puts(tempOutput);
						flag=1;								
						break;
					}
				}else{
					int i=0;
					c=getc(fp);
					while(c!='|'){			//fetching name from file		
						tempNameSearch[i]=c;
						i++;
						c=getc(fp);									
					}
					tempNameSearch[i]='\0';
					
					if(strcmp(tempNameSearch,nameSearch)==0){
						printf("\n         Account No:\t\t\t%d",tempSearch);					
						printf("\n\n         Name:\t\t\t\t");
						puts(nameSearch);
						printf("\n         mobile no:\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         Street:\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         City:\t\t\t\t");
						display(fp);
						puts(tempOutput);
						printf("\n         Previous Due Balance:\t\t");
						display(fp);
						puts(tempOutput);												
						printf("\n         Current payment:\t\t");
						display(fp);
						puts(tempOutput);						
						printf("\n         New Due Balance:\t\t");	
						display(fp);
						puts(tempOutput);
						printf("\n         Payment date(mm/dd/yyyy):\t");
						display(fp);	
						puts(tempOutput);
						
						flag=1;									
						break;
					}
				}
				
			}
		}
	}
	if(flag==0){
		if(choice==1){
			printf("\nNo match found for account number %d",AcNoSearch);
		}else{
			printf("\nNo match found for name ");
			puts(nameSearch);
		}		
	}	
}

void update(){
	FILE *fp1, *fp2;
	int i=0;
	int AcNoSearch;
	char c;
	
	fp1=fopen("database.txt","r");
	fp2=fopen("database1.txt","w");
	
	printf("Enter Account Number:");
	scanf("%d",&AcNoSearch);
	
	while((c=getc(fp1))!=EOF){
		if(c=='\n'){
			i++;
			if(i==AcNoSearch){
				putc(c,fp2);
				int j=0;
				while((c=getc(fp1))!='\n'){
					if(c=='|'){
						j++;
						if(j==5){
							while((c=getc(fp1))!='|');
							while((c=getc(fp1))!='|');
							putc(c,fp2);					
														
							int oldBal=0;
							c=getc(fp1);
							while(c!='.'){			//fetching the account number from file
								oldBal=oldBal*10+((int)c-48);	
								c=getc(fp1);									
							}				
							fprintf(fp2,"%.2f|",(float)oldBal);
							
							fflush(stdin);
							printf("         Current payment:");
							scanf("%f",&customer.payment);
							fprintf(fp2,"%.2f|",customer.payment);
							
							fprintf(fp2,"%.2f|",oldBal-customer.payment);
							fflush(stdin);
							printf("         Payment date(mm/dd/yyyy):");
							scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
							fprintf(fp2,"%d/%d/%d|",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
							
							while((c=getc(fp1))!='\n');
							break;
						}
						
					}
					putc(c,fp2);
				}
			}
		}
		putc(c,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	fp1=fopen("database.txt","w");
	fp2=fopen("database1.txt","r");
	while((c=getc(fp2))!=EOF){
		putc(c,fp1);
		
	}
	fclose(fp1);
	fclose(fp2);
	remove("database1.txt");
	//rename("database1.txt","database.txt");
}

int main(){
	int i;
	int addCustNo, totalCustomer=0;
	int choice;
	char c[200];
	
	printf("\n\n    CUSTOMER BILLING SYSTEM:");
	puts("\n-----------------------------\n");
	printf(" ===============================\n");
	printf("| 1-> Add Account in List       |\n");
	printf("| 2-> Search Customer Account   |\n");
	printf("| 3-> Update Payment Details    |\n");
	printf("| 4-> Exit                      |");
	printf("\n ===============================\n");
	
	do{
		printf("\nPlease Provide an Input: ");
		fflush(stdin);
		scanf("%d",&choice);
	}while(choice<1 || choice>4);
	
	switch(choice){
		case 1:
			printf("\nHow Many Customer Accounts You Wish To Add?");
			scanf("%d",&addCustNo);
			for(i=0;i<addCustNo;i++){
				totalCustomer=getTotalCustomer();	
				printf("\nEnter Details for Account %d :\n\n",totalCustomer+i+1);
				custInput(totalCustomer+i+1);				
			}
			updateTotCustomer(totalCustomer+addCustNo);  //addition of new customer increase total customer number 
			main();	
		case 2:
			puts("\n-------------------------");
			printf("\nPlease Choose Valid Input."); 
			puts("\n------------------------");
			printf("\n1.Enter Customer Number");
			printf("\n2.Enter Customer Name: Case Sensitive\n");
			scanf("%d",&choice);
			searchCustomer(choice);
			main();
		case 3:
			printf("\nUpdate Bill\n");
			update();			
			main();
		case 4:
			printf("\n-------------------------------\n");
			printf("      A PROJECT By Area 69");
			printf("\n-------------------------------\n");
			exit(0);	
			break;	
	}
	
	return 0;
}
