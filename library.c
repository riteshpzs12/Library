#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 30   /* Size of any names*/

struct member{
       char uname[N];
       long long int phone;
       int issue[4];
       int u_id;
       int pass;
       }user[50];

struct books{
	char bname[N];
    char author[N];
    int b_id;
    int check;
} book[50];
int user_cnt;

int login();
void create();
void deposit(int);
void issue(int);
void update(int);
void write_user();
void write_books();
void load_user();
void load_books();


int main()
{
    int i, j, k, loc, ch1, ch2;
    char tch;
    load_books();
	load_user();
	for(;;)
    {
    	printf("\n1 - creeate new account\n2 - login\n3 - exit\nenter ur choice\n");
    	fflush(stdin);	
	    scanf("%d", &ch1);
		switch(ch1)
           {
                case 1: create();
                        break;
                case 2: loc = login();
                        if(loc == -1)
                               break;
                        else
                        {
                            printf("\n1 - issue book\n2 - deposit book\n3 - update information\n4 - exit\nenter ur choice: ");
                            scanf("%d",&ch2);
                            fflush(stdin);
                            for(;;)
                                      switch(ch2)
                                      {
                                          case 1: issue(loc);
                                               break;
                                          case 2: deposit(loc);
                                               break;
                                          case 3:update(loc);
                                               break;
                                          case 4: break;
                                          default: printf("error in choice....retry\n");
                                      }   
                        }
                        break;
                case 3: exit(0);
                default: printf("\nerror in choice....retry\n");
           }
    }
    write_books();
}
void create()
{
     int i;
	 if(user_cnt == 20)
     {
	 	printf("error.... nomore member we can have\n");
        return;
	 }
     else
     {
       // fflush(stdin);
	     printf("\nEnter ur name: ");
         scanf("%29s", user[user_cnt].uname); 
         fflush(stdin);
	     printf("Enter ur phone no.: "); 	     
         fflush(stdin);
	     scanf("%lld", &user[user_cnt].phone);
	     printf("enter password[numeicals only...6 digits max]\n");
	     scanf("%d",&user[user_cnt].pass);
	     user[user_cnt].u_id = user_cnt;
	     printf("ur user id is :%d\n",user_cnt);
	     user[user_cnt].u_id = user_cnt;
	     user_cnt++;
		 for(i=0;i<4;i++)
		 	user[user_cnt].issue[i] = 0;
	}
		write_user();
}


int login()
{
     int passward, id, i;
     printf("enter ur id:\n");
     scanf("%d",&id);
     printf("enter ur password\n");
     scanf("%d",&passward);
     if(user[id].pass == passward)                
     {
                      printf("Login successful\nWELCOME\t%s\n",user[id].uname);
                      return id;
     }                 
     else {
     	printf("error failedd to login\n\n");
        return -1;
	 }
}

void issue(int loc)
{
     int j ,k ,id = 0;
     printf("here are the books\n");
     for(j=0;j<50;j++)
     {
                      if(book[j].check == 0)
                      {
                                       printf("NAME - %s\tBOOK ID - %d\n",book[j].bname,book[j].b_id);
                      }                 
     }
     printf("enetr the book id u want to issue\nor press 99 to exit\n");
     scanf("%d",&id);
     if(id == 99)
     	exit(0);
     else if(id <= 50)
     {
                     for(k=0;k<4;k++)
                     {
                                      if(user[loc].issue[k] == 0)
                                       {
                                               user[loc].issue[k] = id;
                                               break;
                                       }
                     book[id].check = 1;
                     }
     }
     else
         printf("wrong id\n\n");
   //  write_user();
     write_books();
}
void deposit(int loc)
{
     int id ,i=0;
     int ch = 0;
     printf("issued books are\n");
     while(i<4)
     {
       if(user[loc].issue[i] != 0)
       {
          printf("%d\t",user[loc].issue[i]);
	      printf("%s",book[user[loc].issue[i]].bname);
  	      printf("\n\n");
       	  ch = 1;
	   }
	   if(ch == 0)
	   		printf("no books have been issued\n");
       i++;
    }
     printf("enter the book  id u want to deposit\n");
     scanf("%d",&id);
     for(i=0;i<4;i++)
	      if(user[loc].issue[i] == id)
		  {
                user[loc].issue[i] = 0;
                break;
          }
     book[id].check = 0;
     printf("deposit successful\n");
     write_user();
     write_books();
}
void update(int loc)
{
     int ch ,i ;
     char name[N];
    for(;;)
	{
		printf("\n1 - update name\n2 - update phone no\n3 - update password\n4 - exit\n");
     	scanf("%d",&ch);
        switch(ch)
          {
               case 1:printf("enter new name ...");
                      scanf("%[^\n]s", user[loc].uname);
                      // strcpy(user[loc].uname,NULL);
                      // strcpy(user[loc].uname,name);
                      break;
               case 2:user[loc].phone = 0;
                      printf("enter ur new phone no\n");
                      scanf("%lld",&user[loc].phone);
                      break;
               case 3:user[loc].pass = 0;
                      printf("enter new passsword\n\n");
                      scanf("%d",&user[loc].pass);
                      break;
               case 4:exit(0);
               default: printf("wrong choice\n");
                        break;
          }             
     write_user();
 	}
}

void load_books() {
    FILE *fp;
    fp = fopen("BNAME.txt","r");
	int i=0;
	while(!feof(fp)) {
		fscanf(fp, "%[^;]s", book[i].bname);
		fscanf(fp, ";%[^;]s", book[i].author);
		fscanf(fp, ";%d;%d\n",&book[i].b_id,&book[i].check);
//		printf("Name: %s\nAuthor: %s\nBook-ID: %d\nCheck: %d\n\n", \
			book[i].bname, book[i].author,book[i].b_id,book[i].check);
		i++;
	}
	fclose(fp);
}

void load_user() {
    FILE *fp;
    fp = fopen("UNAME.txt","r");
	int i=0;
	while(!feof(fp)) {
		fscanf(fp, "%[^;]s", user[i].uname);
		fscanf(fp, ";%lld", &user[i].phone);
		fscanf(fp, ";%d;%d\n",&user[i].u_id,&user[i].pass);
		fscanf(fp, ";%d;%d;%d;%d\n",&user[i].issue[0],&user[i].issue[1],&user[i].issue[2],&user[i].issue[3]);
	//		printf("Name: %s\nAuthor: %s\nBook-ID: %d\nCheck: %d\n\n", \
			book[i].bname, book[i].author,book[i].b_id,book[i].check);
		i++;
	}
	fclose(fp);
}

void write_user() 
{
    FILE *fp;
    fp = fopen("UNAME.txt","a");
	int i = 0;
	while(i < user_cnt)
	{
	fprintf(fp, "%s;", user[i].uname);
	fprintf(fp, "%lld;", user[i].phone);
	fprintf(fp, "%d;%d;",user[i].u_id,user[i].pass);
	fprintf(fp, "%d;%d;%d;%d\n",user[i].issue[0],user[i].issue[1],user[i].issue[2],user[i].issue[3]);
//		printf("Name: %s\nAuthor: %s\nBook-ID: %d\nCheck: %d\n\n", \
			book[i].bname, book[i].author,book[i].b_id,book[i].check);
			i++;
	}
	fclose(fp);
}

void write_books()
{
    FILE *fp;
    fp = fopen("BNAME.txt","w");
	int i=0;
	while(i < 50)
	{
		fprintf(fp, "%s;", book[i].bname);
		fprintf(fp, "%s;", book[i].author);
		fprintf(fp, "%d;%d\n",book[i].b_id,book[i].check);
//		printf("Name: %s\nAuthor: %s\nBook-ID: %d\nCheck: %d\n\n", \
			book[i].bname, book[i].author,book[i].b_id,book[i].check);
		i++;
	}
	fclose(fp);
}

