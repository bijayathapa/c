#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct contact{

	double phone;
	char name[50], address[50], email[50];
	int num;
}contact_list;

char name[50], name_query[50];


int menu();
void heading();
void addContact();
void displayContact();
void editContact();
void searchContact();
void deleteContact();

int main(){

	menu();

}


void heading() {
    printf("\t###########################################################################");
	printf("\n\t############              Contact management System            ############");
	printf("\n\t############                (UNDER DEVELOPMENT)                ############");
	printf("\n\t###########################################################################");
	printf("\n\n");
}


int menu(){

	system("clear");
	char exit_choice;
	int choice;
	label:
	do{
		heading();

		printf("\t\t\t******-- MENU -- ******\n");
		printf("\t\t\t1. Add Contact\n");
		printf("\t\t\t2. Display All Contact\n");
		printf("\t\t\t3. Edit Contact\n");
		printf("\t\t\t4. Search Contact\n");
		printf("\t\t\t5. Delete Contact\n");
		printf("\t\t\t6. Exit\n");

		printf("\t\tEnter your choice.\n");
		scanf("%d",&choice);

		switch(choice){

			case 1:
				printf("Add Contacts\n");
				addContact();
				break;

			case 2:
				printf("Display Contact\n");
				displayContact();
				break;

			case 3: 
				printf("Edit Contact\n");
				//editContact();
				break;

			case 4:
				printf("Search Contact\n");
				searchContact();
				break;

			case 5: 
				printf("Delete Contact\n");
				deleteContact();
				break;

			case 6:
				printf("Exit? (y/n)\n");
				scanf("%s",&exit_choice);
				if(exit_choice == 'y' || exit_choice == 'Y'){
					break;
				}
				if(exit_choice == 'n' || exit_choice == 'N'){
					goto label;
				}
				break;

			default:
				printf("ENTER VALID CHOICE\n");

		}
	}while(choice != 6);

	return 0;
}

void addContact(){

	FILE *fpC;

	fpC = fopen("contact.bin","ab");

	if(fpC == NULL){
		printf("FILE NOT AVAILABLE\n");
	}

	printf("Contact No.:\n");
	scanf("%d",&contact_list.num);
	printf("Contact Name: \n");
	scanf("%s",contact_list.name);
	//gets(contact_list.name);
	printf("Contact Address: \n");
	scanf("%s",contact_list.address);
	//gets(contact_list.address);

	printf("Email: \n");
	scanf("%s",contact_list.email);
	//gets(contact_list.email);
	printf("Contact Phone: \n");
	scanf("%lf",&contact_list.phone);

	fwrite(&contact_list, sizeof(contact_list),1,fpC);

	fclose(fpC);
	printf("Contact Added Successfully\n");

}

void displayContact(){

	FILE *fpR;
	fpR = fopen("contact.bin","rb");

	if(fpR == NULL){
		printf("No Such File\n");
	}
	//printf("No.\t Name\t Address\t\t Email\t\t Phone\n");
	while(fread(&contact_list, sizeof(contact_list), 1, fpR) == 1){

		printf("%d\t %s\t %s\t\t %s\t\t %0.0lf\n",contact_list.num,contact_list.name, contact_list.address, contact_list.email, contact_list.phone);
	}

	fclose(fpR);
}

void editContact(){

	FILE *fpR;
	FILE *fpW;

	fpR = fopen("contact.bin","rb");
	fpW = fopen("temp.bin","wb");

	printf("EDIT CONTACT\n\n Enter the name of the contact to edit: \n");
	scanf("%s",name);

	while(fread(&contact_list, sizeof(contact_list),1,fpR) == 1){
		if(strcmp(name,contact_list.name) != 0){
			fwrite(&contact_list, sizeof(contact_list),1,fpW);
		}
	}
		printf("New Name: \n");
		scanf("%s",contact_list.name);
		printf("New Address: \n");
		scanf("%s",contact_list.address);
		printf("New Email: \n");
		scanf("%s",contact_list.email);
		printf("New Phone: \n");
		scanf("%lf",&contact_list.phone);

		fwrite(&contact_list, sizeof(contact_list),1,fpW);

	
	fclose(fpR);
	fclose(fpW);
	remove("contact.bin");
	rename("temp.bin","contact.bin");

	printf("EDIT SUCCESSFUL\n");
}

void searchContact(){
	int found = 0,name_length;
	printf("Enter the name to be searched : \n");
	scanf("%s", name_query);

	FILE *fpS;
	fpS = fopen("contact.bin","rb");

	name_length = strlen(name_query);
	while(fread(&contact_list, sizeof(contact_list),1,fpS)==1){

		for(int i = 0; i < name_length; i++){
			name[i] = contact_list.name[i];
			name[name_length] = '\0';
		}
			if(strcmp(name,name_query)==0){
				printf("No: %d\n Name: %s\n Address:%s\n Email:%s\n Phone:%0.0lf\n ",contact_list.num, contact_list.name, contact_list.address, contact_list.email, contact_list.phone);
				found++;
			}
		
	}

	if(found == 0){
		printf("No matches found\n");
	}

	fclose(fpS);
	
}


void deleteContact(){
	int num, flag = 0;

	FILE *fpR, *fpW;

	heading();

	fpR = fopen("contact.bin","rb");
	if(fpR ==  NULL){
		printf("Unable to get the record\n");
	}

	fpW = fopen("temp.bin","wb");
	printf("Enter the contact number to be deleted:\n");
	scanf("%d",&num);

	while(fread(&contact_list, sizeof(contact_list), 1, fpR)){
		if(num != contact_list.num){
			fwrite(&contact_list, sizeof(contact_list), 1, fpW);
		}
		else{
			printf("Contact Deleted\n");
			flag = 1;
		}
	}
	if(flag == 0){
		printf("No such contact exist\n");
	}

	fclose(fpR);
	fclose(fpW);
	remove("contact.bin");
	rename("temp.bin","contact.bin");

}












