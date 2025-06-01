#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fuel_record.h"

int main() {
    FuelRecord *fuel = NULL;
    char *filename = "fuel_records.txt";
    loadFuelRecordsFromFile(&fuel, filename);

    int choice;
    int recordID;
    char date[15];
    int odometerReading;
    float FuelQuantity;
    float FuelPrice;
    char FuelType[20];
    char month[9];

    do {
        printf("\nFuel Records \n");
        printf("1. Add new reading \n2. Remove readings \n3. Search readings \n4. Display fuel records\n5. calculateAvgEffieciency \n6. displayMonthlyStatistics \n7. Exit \n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  

        switch(choice) {

            case 1: {
                printf("Enter recordID: ");
                scanf("%d", &recordID);
                
                if (searchFuelRecord(fuel, recordID) != NULL) {
                    printf("Fuel record  %d already exists.\n", recordID);
                    break;  
                }
            
                getchar(); 
            
                printf("Enter Date (YYYY-MM-DD): ");
                fgets(date, 15, stdin);
                date[strcspn(date, "\n")] = 0; 

                printf("Enter odometer Reading: ");
                scanf("%d", &odometerReading);

                printf("Enter Fuel Quantity: ");
                scanf("%f", &FuelQuantity);

                printf("Enter Fuel Price: ");
                scanf("%f", &FuelPrice);
                
                getchar(); 
                printf("Enter Fuel Type (Petrol,Disel,Electric): ");
                fgets(FuelType, 20, stdin);
                FuelType[strcspn(FuelType, "\n")] = 0;  
             
                addFuelRecord(&fuel,recordID,date,odometerReading,FuelQuantity,FuelPrice,FuelType);

                printf("Fuel Record added successfully.\n");
                saveFuelRecordsToFile(fuel,filename); 
                break;
            }

            case 2:
                printf("Enter recordID to be removed ");
                scanf("%d", &recordID);
                if (searchFuelRecord(fuel, recordID) == NULL) {
                    printf("Record ID %d does not exist\n",recordID);
                    break;
                }
                removeFuelRecord(&fuel,recordID);;
                saveFuelRecordsToFile(fuel,filename);
                break;

            case 3:
                printf("Enter record to search: ");
                scanf("%d", &recordID);

                FuelRecord *search =searchFuelRecord(fuel, recordID);
                if (search) 
                {
                    printf("Fuel Record Found: \n");
                    printf("Record ID : %d\n ,Date : %s\n, Odometer Reading : %d\n,Fuel Quantity : %.2f\n,Fuel Price: %.2f\n,Fuel Type : %s\n",
                           search->recordID, search->date, search->odometerReading, search->FuelQuantity, search->FuelPrice,search->FuelType);
                }
                else 
                    printf("Fuel record not  found.\n");
                break;

            case 4:
            displayFuelRecord(fuel);
             break;  

            case 5:
            calculateAvgEfficiency(fuel);
                break;  
            
            case 6:
            printf("Enter the year and month (YYYY-MM):");
            scanf("%s",month);
            displayMonthlyStatistics(fuel,month);
            break;
            case 7:
            printf("Exiting program\n");
            break;

        }
    } while (choice != 7);

    FreeFuelRecordList(&fuel);
    return 0;
}
