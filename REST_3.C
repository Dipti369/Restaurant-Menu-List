/* This Restaurant Menu Program offers following functionalities:
1. Add new items in the menu
2. Display the menu list
3. Modify items in the menu
4. Delete item in the menu
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<dos.h>

struct restaurant
{
    int itemcode, dd, mm, yy;
    char itemname[31], itemcat[31];
    float price;
};

void Item_add();    //Adding new items in menu list
void showlist();    //Showing the items in the menu list
void display(int code);	 //Displaying item info with specified item code
void Item_modify();	//Modifying the items in the list
void Item_del();	//Deleting items from menu list

int main(){
    int choice;
    clrscr();
    printf("\t\t WELCOME TO THE RESTAURANT \n");
    printf("Make a selection: \n");
    printf("1. Add new item in the menu \n");
    printf("2. Display menu items \n");
    printf("3. Modify item in the menu \n");
    printf("4. Delete item in the menu \n");
    printf("5. Exit application \n\n");
    scanf("%d", &choice);
    switch(choice)
    {
	case 1:
	    Item_add();
	    break;
	case 2:
	    showlist();
	    break;
	case 3:
	     Item_modify();
	     break;
	case 4:
		Item_del();
		break;
	case 5:
	     printf("\n Thank You for visiting. Have a Good Day!");
	     getch();
	     exit(0);
	default:
	    printf("Invalid selection made.");
	    printf("Enter any key to exit the program.");

    }
    getch();
    return 0;
}
void Item_add(){
    struct restaurant t;
    struct restaurant te;
    FILE *file;
    char ch, price[10];
    int code=0;
    clrscr();
    printf("ADDITION OF NEW ITEM \n");
    file=fopen("restaur.Dat","rb+");
    while(fread(&te, sizeof(struct restaurant),1,file)==1)
	code=te.itemcode;
    fclose(file);
    code++;
    t.itemcode=code;
    printf("Item code: %d \n \n",t.itemcode);
    printf("Enter the name of the item: ");
    fflush(stdin);
    gets(t.itemname);
    printf("\nEnter the category of the item (veg/nonveg): ");
    fflush(stdin);
    gets(t.itemcat);
    printf("\nEnter price of the item: ");
    //gets(price);
    //t.price=atof(price);
    scanf("%f",&t.price);
    printf("\nDo you wish to save changes made (y/n): ");
    ch=getche();
    ch=toupper(ch);
    if (ch=='N')
	{	printf("\n Changes discarded.");
		printf("\n Press any key to return to main menu...");
		getch();
		main();
	}
    file=fopen("restaur.Dat","ab+");
    fwrite(&t,sizeof(struct restaurant),1,file);
    fclose(file);
    printf("\n\n Changes saved succesfully.");
    printf("\n Press any key to return to main menu...");
    getch();
    main();
}
void showlist(){
    struct restaurant t;
    FILE *file;
    int found=0;
    int d1, m1, y1;
    char ch;
    struct date d;
    getdate(&d);
    d1=d.da_day;
    m1=d.da_mon;
    y1=d.da_year;
    clrscr();
    printf("\n\n \t\t LIST OF ITEMS AS ON %d-%d-%d \n\n", d1,m1,y1);
    printf("CODE# \t\t NAME \t\t CATEGORY \t\t PRICE \n");
    file=fopen("restaur.dat","rb+");
    while(fread(&t,sizeof(struct restaurant),1,file)==1)
    {	found=1;
	printf("%d \t %s \t\t ", t.itemcode, t.itemname);
	printf("%s \t\t Rs. %.2f \n", t.itemcat, t.price);
    }
    if (!found)
    {	printf("Records not found. Exiting application.");

    }
    printf("\n\n\n Press any key to return to main menu...");
    fclose(file);
    getch();
    main();
}

void display(int code)
{	FILE *file;
	struct restaurant t;
	int found=0;
	file=fopen("restaur.Dat","rb+");
	while(fread(&t,sizeof(struct restaurant),1,file))
	{	if (t.itemcode==code)
		{       found=1;
			printf("\nITEM INFORMATION \n");
			printf("Item Code#: %d \n", t.itemcode);
			printf("Name: %s \n", t.itemname);
			printf("Category: %s \n", t.itemcat);
			printf("Price: %.2f \n", t.price);
		}
	 }
	if (found==0)
		printf("Item code# %d does not exist.", code);
	fclose(file);
	getch();
}

void Item_modify()
{	FILE *file;
	FILE *file1;
	struct restaurant t;
	struct restaurant te;
	int code, found=0;
	char ch;
	char name[31], categ[31];
	float price;
	clrscr();
	printf("Enter the code of the item: ");
	scanf("%d", &code);
	file=fopen("restaur.Dat","rb+");
	while(fread(&t, sizeof(struct restaurant),1,file)==1)
	{	if (t.itemcode==code)
		{	found=1;
			break;
		}
	}
	if (found==0)
	{	printf("\n Item code# %d does not exist in menu record.",code);
		printf("\n\n Press any key to return to main menu...");
		getch();
		main();
	}
	else if (found==1)
	{	display(code);
		printf("\n\n Do you wish to modify this record? (y/n): ");
		ch=getche();
		ch=toupper(ch);
		if (ch=='N' || ch!='Y')
		{	printf("\n\n Cancelling item modification.");
			printf("\n Press any key to return to main menu...");
			getch();
			main();
		}
		printf("\n\nMODIFICATION OF ITEM \n");
		printf("Item Code#: %d \n",code);
		printf("Enter new item name: ");
		fflush(stdin);
		gets(name);
		printf("Enter category of the item (veg/nonveg): ");
		fflush(stdin);
		gets(categ);
		printf("Enter price of the item: ");
		//fflush(stdin);
		//gets(price);
		scanf("%f",&price);
		printf("\n\n Do you wish to save changes? (y/n): ");
		ch=getche();
		ch=toupper(ch);
		if (ch=='N'|| ch!='Y')
		{	printf("\n\n Changes discarded.");
			printf("\n Press any key to return to the main menu...");
			getch();
			main();
		}
		else if (ch=='Y')
		{	printf("\n\n Records modified.");
			printf("\n Press any key to return to the main menu...");
		}
		t.itemcode=code;
		strcpy(t.itemname,name);
		strcpy(t.itemcat,categ);
		t.price=price;
		file=fopen("restaur.Dat","rb++");
		file1=fopen("Tempmod.Dat","wb+");
		while(fread(&te,sizeof(struct restaurant),1,file)==1)
		{	if (t.itemcode!=te.itemcode)
				fwrite(&te,sizeof(struct restaurant),1,file1);
			else
				break;
		}
		fwrite(&t,sizeof(struct restaurant),1,file1);
		while (fread(&te, sizeof(struct restaurant),1,file)==1)
			fwrite(&te,sizeof(struct restaurant),1,file1);
		fclose(file);
		fclose(file1);

		file=fopen("restaur.Dat","wb++");
		file1=fopen("Tempmod.Dat","rb++");
		while(fread(&t,sizeof(struct restaurant),1,file1)==1)
			fwrite(&t,sizeof(struct restaurant),1,file);
		fclose(file);
		fclose(file1);
		getch();
		main();
	}
}

void Item_del(){
	struct restaurant t;
	FILE *file;
	FILE *file1;
	int code, found=0;
	char ch;
	clrscr();
	printf("\n Enter the code of the item: ");
	scanf("%d",&code);
	file=fopen("restaur.Dat","rb+");
	while(fread(&t, sizeof(struct restaurant),1,file)==1)
	{	if (t.itemcode==code)
		{	found=1;
			break;
		}
	}
	if (found==0)
	{	printf("\n Item code# %d does not exist.", code);
		printf("\n Press any key to return to the main menu...");
		getch();
		main();
	}
	else if(found==1)
	{	display(code);
		printf("\n\n Do you wish to delete this record? (y/n): ");
		ch=getche();
		ch=toupper(ch);
		if (ch=='N' || ch!='Y')
		{	printf("\n\n Cancelling item deletion.");
			printf("\n Press any key to return to main menu...");
			getch();
			main();
		}

		file=fopen("restaur.Dat","rb+");
		file1=fopen("Tempdel.Dat","wb+");
		while(fread(&t,sizeof(struct restaurant),1,file)==1)
		{	if (t.itemcode!=code)
			{	fwrite(&t,sizeof(struct restaurant),1,file1);
			}
		}
		fclose(file);
		fclose(file1);

		file=fopen("restaur.Dat","wb+");
		file1=fopen("Tempdel.Dat","rb+");
		while(fread(&t,sizeof(struct restaurant),1,file1)==1)
		{	fwrite(&t,sizeof(struct restaurant),1,file);
		}
		fclose(file);
		fclose(file1);
		printf("\n\n Record deleted successfully.");
		printf("\n Press any key to return to main menu...");
		getch();
		main();
	}
}