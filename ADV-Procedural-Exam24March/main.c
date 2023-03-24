#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct declaration
typedef struct {
	int patientRegNum;
	char firstName[30];
	char sirName[30];
	int gender;
	int age;
	int weight;
	int height;
	float bloodTest1;
	float bloodTest2;
	float bloodTest3;
}patientT;

//declaration of all functions
void init(patientT* patientDetails, int size);
void savePatientDB(patientT* patientDetails, int size);
void mainMenu(patientT* patientDetails, int size);
void addPatient(patientT* patientDetails, int size);
void editPatient(patientT* patientDetails, int size);
void searchPatient(patientT* patientDetails, int size);
void findDiabetes(patientT* patientDetails, int size);

void main() {
	patientT* patientLibrary;
	FILE* fp;
	int numOfPatients;
	int choice;

	printf("Enter 1 to load a previous Patient DB or Enter 2 to create a new patient DB: \n");
	scanf("%d", &choice);

	if (choice == 1) {//loads the previous saved database
		fp = fopen("patient.txt", "r");

		if (fp == NULL) {
			printf("Cannot open file");
		}
		else {
			fscanf(fp, "%d", &numOfPatients);

			patientLibrary = (patientT*)malloc(numOfPatients * sizeof(patientT));

			for (int i = 0; i < numOfPatients; i++) {
				fscanf(fp, "%d %s %s %d %d %d %d %f %f %f", 
					&(patientLibrary + i)->patientRegNum, &(patientLibrary + i)->firstName, &(patientLibrary + i)->sirName, &(patientLibrary + i)->gender, 
					&(patientLibrary + i)->age, &(patientLibrary + i)->weight, &(patientLibrary + i)->height, 
					&(patientLibrary + i)->bloodTest1, &(patientLibrary + i)->bloodTest2, &(patientLibrary + i)->bloodTest3);
			}
			fclose(fp);

			mainMenu(patientLibrary, numOfPatients);
		}
	}
	else if (choice == 2) {//creates a new database
		printf("Please enter the number of patients you would like to have:\n");
		scanf("%d", &numOfPatients);

		patientLibrary = (patientT*)malloc(numOfPatients * sizeof(patientT));

		//initialising the library
		init(patientLibrary, numOfPatients);

		mainMenu(patientLibrary, numOfPatients);//calls mainMenu function and prompts user to add a new patient
	}
}

//initializes the patientT variables
void init(patientT* patientDetails, int size) {
	for (int i = 0; i < size; i++) {
		(patientDetails + i)->patientRegNum = 0;
		strcpy((patientDetails + i)->firstName, "");
		strcpy((patientDetails + i)->sirName, "");
		(patientDetails + i)->gender = 0;
		(patientDetails + i)->age = 0;
		(patientDetails + i)->weight = 0;
		(patientDetails + i)->height = 0;
		(patientDetails + i)->bloodTest1 = 0.0;
		(patientDetails + i)->bloodTest2 = 0.0;
		(patientDetails + i)->bloodTest3 = 0.0;
	}
}

//function to allow for the saving of the patient database to the file patient.txt
void savePatientDB(patientT* patientDetails, int size) {
	FILE* fp;

	fp = fopen("patient.txt", "w");

	if (fp == NULL) {
		printf("Cannot open file!\n");
	}
	else {
		fprintf(fp, "%d\n", size);

		for (int i = 0; i < size; i++) {
			if ((patientDetails + i)->patientRegNum != 0) {//populates the file if there is a patient in the array 
				fprintf(fp,"%d %s %s %d %d %d %d %f %f %f\n",
					(patientDetails + i)->patientRegNum, (patientDetails + i)->firstName, (patientDetails + i)->sirName, (patientDetails + i)->gender,
					(patientDetails + i)->age, (patientDetails + i)->weight, (patientDetails + i)->height,
					(patientDetails + i)->bloodTest1, (patientDetails + i)->bloodTest2, (patientDetails + i)->bloodTest3);
			}
			else {//populates the file with "empty" if that index of the array has no patient
				fprintf(fp, "%d %s %s %d %d %d %d %f %f %f", 
					(patientDetails + i)->patientRegNum, "Empty", "Empty", 0, 0, 0, 0, 0.0, 0.0, 0.0);
			}
		}
		fclose(fp);
		printf("Your file has been saved!\n\n");
	}
}

//menu method allows the user to decide what they want to do with the database
void mainMenu(patientT* patientDetails, int size) {
	int menuChoice = 0;
	while (menuChoice != -1) {//menu loop 
		printf("\nEnter 1 to add a new patient\nEnter 2 to edit a patient\nEnter 3 to search for a patient\nEnter 4 to search for patients with Diabetes\nEnter 5 to save db\nEnter -1 to exit\n");
		scanf("%d", &menuChoice);

		if (menuChoice == 1) {
			addPatient(patientDetails, size);
		}
		else if (menuChoice == 2) {
			editPatient(patientDetails, size);
		}
		else if (menuChoice == 3) {
			searchPatient(patientDetails, size);
		}
		else if (menuChoice == 4) {
			findDiabetes(patientDetails, size);
		}
		else if (menuChoice == 5) {
			savePatientDB(patientDetails, size);
		}
		else if (menuChoice == -1) {
			break;
		}
		else {
			printf("The number you have entered is not an option, please try again!\n");
			menuChoice = 0;
		}
	}
}

//function that allows the user to add a patient to the database
void addPatient(patientT* patientDetails, int size) {
	for (int i = 0; i < size; i++) {
		if ((patientDetails + i)->patientRegNum == 0) {
			printf("Please enter the patient Registration number:\n");
			scanf("%d", &(patientDetails + i)->patientRegNum);

			printf("Please enter First Name:\n");
			scanf("%s", (patientDetails + i)->firstName);

			printf("Please enter Surname:\n");
			scanf("%s", (patientDetails + i)->sirName);

			printf("Please enter gender, 1 for male or 2 for female:\n");
			scanf("%d", &(patientDetails + i)->gender);

			printf("Please enter age:\n");
			scanf("%d", &(patientDetails + i)->age);

			printf("Please enter weight:\n");
			scanf("%d", &(patientDetails + i)->weight);

			printf("Please enter height:\n");
			scanf("%d", &(patientDetails + i)->height);

			printf("Please enter blood test 1:\n");
			scanf("%f", &(patientDetails + i)->bloodTest1);

			printf("Please enter blood test 2:\n");
			scanf("%f", &(patientDetails + i)->bloodTest2);

			printf("Please enter blood test 3:\n");
			scanf("%f", &(patientDetails + i)->bloodTest3);
			return;
		}
	}
	printf("Sorry the library is full\n");
}

//function that allows you to change the blood sugar test results of the patient
void editPatient(patientT* patientDetails, int size) {
	int findpatient;

	printf("\nPlease enter the patient registration number of the patient that you want to edit:\n");
	scanf("%d", &findpatient);

	for (int i = 0; i < size; i++)
	{
		if ((patientDetails + i)->patientRegNum == findpatient) {
			printf("Please enter the new blood test 1:\n");
			scanf("%f", &(patientDetails + i)->bloodTest1);

			printf("Please enter the new blood test 2:\n");
			scanf("%f", &(patientDetails + i)->bloodTest2);

			printf("Please enter the new blood test 3:\n");
			scanf("%f", &(patientDetails + i)->bloodTest3);
			return;
		}
	}
	//throws error if the patient reg number could not be found
	printf("The patient Registration number %ld could not be found!\n", findpatient);
}

//function to allow the user to search for a patient and display all of the data related to them
void searchPatient(patientT* patientDetails, int size) {
	int findPatient;

	printf("Please enter the patient registration number of the patient that you want to find:\n");
	scanf("%d", &findPatient);

	for (int i = 0; i < size; i++)
	{
		if ((patientDetails + i)->patientRegNum == findPatient) {
			printf("Patient Reg Number: %d\nFirst Name:%s\nSurname: %s\n Gender(1 for male, 2 for female): %d\nAge: %d\nWeight: %d\nHeight: %d\nBlood Sugar Test 1: %f\nBlood Sugar Test 2: %f\nBlood Sugar Test 3: %f\n",
				(patientDetails + i)->patientRegNum, (patientDetails + i)->firstName, (patientDetails + i)->sirName, (patientDetails + i)->gender,
				(patientDetails + i)->age, (patientDetails + i)->weight, (patientDetails + i)->height,
				(patientDetails + i)->bloodTest1, (patientDetails + i)->bloodTest2, (patientDetails + i)->bloodTest3);
			return;
		}
	}
	printf("The patient could not be found!\n");
}

//function that allows the user to find the patients that have diabetes based on the parameters set in the IF statement
void findDiabetes(patientT* patientDetails, int size) {
	for (int i = 0; i < size; i++) {
		if ((patientDetails + i)->bloodTest1>= 11.1 && (patientDetails + i)->bloodTest2 >= 7.0 && (patientDetails + i)->bloodTest3 >= 9.1) {
			printf("\nPatient Reg Number: %d\nFirst Name:%s\nSurname: %s\n Gender(1 for male, 2 for female): %d\nAge: %d\nWeight: %d\nHeight: %d\nBlood Sugar Test 1: %f\nBlood Sugar Test 2: %f\nBlood Sugar Test 3: %f\n",
				(patientDetails + i)->patientRegNum, (patientDetails + i)->firstName, (patientDetails + i)->sirName, (patientDetails + i)->gender,
				(patientDetails + i)->age, (patientDetails + i)->weight, (patientDetails + i)->height,
				(patientDetails + i)->bloodTest1, (patientDetails + i)->bloodTest2, (patientDetails + i)->bloodTest3);
			return;
		}
	}


}

