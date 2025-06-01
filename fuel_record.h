#ifndef FUEL_RECORDS_H
#define FUEL_RECORDS_H

typedef struct FuelRecord
{
    int recordID;
    char date[15];
    int odometerReading;
    float FuelQuantity;
    float FuelPrice;
    char FuelType[20];
    struct FuelRecord *next;
}FuelRecord;
void loadFuelRecordsFromFile(FuelRecord**head,char *filename);
void saveFuelRecordsToFile(FuelRecord*head,char *filename);
void addFuelRecord(FuelRecord **head,int recordID,char *date,int odometerReading,float FuelQuantity,float FuelPrice,char *FuelType);
void removeFuelRecord(FuelRecord ** head,int recordID);
FuelRecord *searchFuelRecord(FuelRecord *head,int recordID);
void displayFuelRecord(FuelRecord *head);
float calculateAvgEfficiency(FuelRecord*head);
void displayMonthlyStatistics(FuelRecord*head, char* month);
void FreeFuelRecordList(FuelRecord **head);


#endif