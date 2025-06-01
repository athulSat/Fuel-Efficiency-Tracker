#include"fuel_record.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void loadFuelRecordsFromFile(FuelRecord**head,char *filename)
{
    FILE*file=fopen(filename,"r");
    if(!file)
    {
        printf("FILE not found \n");
        return ;
    }
    int recordID;
    char date[15];
    int odometerReading;
    float FuelQuantity;
    float FuelPrice;
    char FuelType[20];
    while(fscanf(file," %d, %14[^,] ,%d ,%f, %f, %19[^\n]" ,&recordID,date,&odometerReading,&FuelQuantity,&FuelPrice,FuelType)==6)
    {
        addFuelRecord(head,recordID,date,odometerReading,FuelQuantity,FuelPrice,FuelType);
    }
    fclose(file);
    printf("Loaded Fuel Records Succesfully \n");
    
}
void saveFuelRecordsToFile(FuelRecord*head,char *filename)
{
    FILE *file=fopen(filename,"w");
    if(!file)
    {
        printf("Error opening file");
        return;
    }
    FuelRecord *temp=head;
    while (temp)
    {
        fprintf(file,"%d,%s,%d,%f,%f,%s\n",temp->recordID,temp->date,temp->odometerReading,temp->FuelQuantity,temp->FuelPrice,temp->FuelType);
        temp=temp->next;
    }
    fclose(file);

}
void addFuelRecord(FuelRecord **head, int recordID, char *date, int odometerReading, float FuelQuantity, float FuelPrice, char *FuelType)
{

    FuelRecord *dup = *head;
    while (dup) {
        if (dup->recordID == recordID) {
            printf("Duplicate Record ID %d \n", recordID);
            return;
        }
        dup = dup->next;
    }

    FuelRecord *newrecord = (FuelRecord*)malloc(sizeof(FuelRecord));
    if (!newrecord) {
        printf("Memory Allocation Failed\n");
        return;
    }

    newrecord->recordID = recordID;
    strcpy(newrecord->date, date);
    newrecord->odometerReading = odometerReading;
    newrecord->FuelQuantity = FuelQuantity;
    newrecord->FuelPrice = FuelPrice;
    strcpy(newrecord->FuelType, FuelType);
    newrecord->next = NULL;

    if (*head == NULL || strcmp((*head)->date, date) > 0) {
        if (*head && odometerReading < (*head)->odometerReading) {
            printf(" Odometer reading less than existing first record.\n");
            free(newrecord);
            return;
        }
        newrecord->next = *head;
        *head = newrecord;
        return;
    }

    FuelRecord *temp = *head;
    while (temp->next && strcmp(temp->next->date, date) < 0) {
        temp = temp->next;
    }

    if (temp->odometerReading > odometerReading) {
        printf("Odometer reading less than previous record.\n");
        free(newrecord);
        return;
    }

    newrecord->next = temp->next;
    temp->next = newrecord;
}

void removeFuelRecord(FuelRecord ** head,int recordID)
{
    if(!head)
    {
        printf("No Fuels Record Found \n");
        return ;
    }
    FuelRecord *temp=*head, *prev=NULL;
    if(temp && temp->recordID==recordID)
    {
        *head = temp->next;
        free(temp);
        printf("recordID %d removed successfully.\n", recordID);
        return;
    }
    while (temp && temp->recordID != recordID) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("recordID %d not found.\n", recordID);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("recordID %d removed successfully.\n", recordID);



}
FuelRecord *searchFuelRecord(FuelRecord *head,int recordID)
{
    FuelRecord *temp=head;
    while(temp)
    {
        if(temp->recordID==recordID)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
void displayFuelRecord(FuelRecord *head)
{
    if(!head)
    {
        printf("No Fuel Records Found\n");
        return ;
    }
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n","RecordID", "Date", "Odometer", "Quantity", "Price", "FuelType");
    FuelRecord *temp = head;
    while (temp) 
    {
        printf("%-10d %-15s %-10d %-10.2f %-10.2f %-10s\n",
        temp->recordID, temp->date, temp->odometerReading,
        temp->FuelQuantity, temp->FuelPrice, temp->FuelType);
        temp = temp->next;
    }
}
float calculateAvgEfficiency(FuelRecord*head)
{
    if (head == NULL || head->next == NULL)
    {
        return 0.0;
    }
    float totalfuel=0.0;
    int final_odometer_reading=0,initial_odometer_reading=0;
    initial_odometer_reading=head->odometerReading;
    FuelRecord *temp=head,*prev=NULL;
    while(temp)
    {
        prev=temp;
        totalfuel+=temp->FuelQuantity;
        temp=temp->next;
    }
    final_odometer_reading=prev->odometerReading;

    return ((float)(final_odometer_reading-initial_odometer_reading)/totalfuel);

}
void displayMonthlyStatistics(FuelRecord*head, char* month)
{
    int odometer_start_of_the_month_reading=0,odometer_final_end_of_the_month=0,total_distance=0;
    float totalFuel = 0.0,totalCost = 0.0,Average_efficiency=0.0,Average_cost_per_km = 0.0;
    bool found=0;
    FuelRecord *temp=head;
    while(temp)
    {
        if (strncmp(temp->date, month, 7) == 0)
        {
            if (!found) {
                odometer_start_of_the_month_reading = temp->odometerReading;
                found = 1;
            }
        odometer_final_end_of_the_month=temp->odometerReading;
        totalFuel+=temp->FuelQuantity;
        totalCost+=(temp->FuelQuantity*temp->FuelPrice);
        }
        temp=temp->next;
    }
    
    total_distance=(odometer_final_end_of_the_month -odometer_start_of_the_month_reading);

    if(totalFuel >0 && total_distance>0)
    {
        Average_efficiency= ((odometer_final_end_of_the_month-odometer_start_of_the_month_reading)/totalFuel);
        Average_cost_per_km=(totalCost/total_distance);
    }
    printf(" Monthly Statistics for %s \n", month);
    printf("Total Fuel used: %.2f liters\n", totalFuel);
    printf("Total Cost: %.2f\n", totalCost);
    printf("Distance Travelled: %d km\n",total_distance );
    printf("Average Efficiency: %.2f km/l\n", Average_efficiency);
    printf("Average Cost per Kilometer: %.2f/km\n", Average_cost_per_km);
   
}
void FreeFuelRecordList(FuelRecord **head)
{
    FuelRecord *temp=NULL;
    while(*head)
    {
        temp=*head;
        (*head)=(*head)->next;
        free(temp);
    }

}