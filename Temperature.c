// **********************************************
// Program1: Temperature calculation
// Course: CS451
// Student Name: Andrew Pyscher
// Instructor: Il-Hyung Cho
// Date of submission: 2/8/23
// Program Description: Program that reads in temperature data from a file
// the program then finds the average, lowest temp, and highest temp for that year
// then finds the average of all the years provided
// **********************************************
#include <stdio.h>
#include <stdlib.h>
// struct that contains temperature array, in the indexs of the hottest and coldest day
// in that array, and the average of the tempeature of that year
struct Data {
   float temperatures[12]; 
   int year, coldest, hottest;                     
   float average;
};
struct Data* arr;
// prototype for function to find the averages of all the years 
int yearlyAverage(struct Data temps[], int numOfYears);

int main(){
    char *months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    int numOfYears;
     int year, i, j;
    // prompt the user to enter the file to read from
    char file_name[100];
    printf("Enter temperature file name:");
    scanf("%s", file_name);

    // open the file if it exists
    FILE* ptr = fopen(file_name, "r");
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }
    // scan in the number of years
    fscanf(ptr, "%d", &numOfYears);
   
    float sum;
    arr = malloc(numOfYears *(sizeof(struct Data *)));
    

    printf("\nYear \t Average \t Coldest Month \t Hottest Month\n==== \t ======= \t ============= \t ============= \n");
// outer loop represents the current year, the inner loop is the month of the year
    for(i = 0; i < numOfYears; i++){
        // read in the year
        fscanf(ptr, "%d\n", &year);
        // assign the year and default values for coldest and hottest
        arr[i].year = year;
        arr[i].coldest = 0;
        arr[i].hottest = 0;
        sum = 0;
        // read in the temperature data for each month
        for (j = 0; j < 12; j++) {
            fscanf(ptr, "%f", &arr[i].temperatures[j]);
            sum += arr[i].temperatures[j];
            // check if the temp that was just entered is hotter than the current hottest month
            // if it is, replace the value (with the index so we can use it for the month array as well)
            if(arr[i].temperatures[j] > arr[i].temperatures[arr[i].hottest]){
                arr[i].hottest = j;
            }
            // check if the temp that was just entered is colder than the current colder month
            // if it is, replace the value (with the index so we can use it for the month array as well)
            if(arr[i].temperatures[j] < arr[i].temperatures[arr[i].coldest]){
                arr[i].coldest = j;
            }
        }   
        arr[i].average = sum/12;
        //print out the yearly data
    printf("%d \t ", arr[i].year);
    printf("%.1f \t\t ", arr[i].average);
    printf("%s ", months[arr[i].coldest]);
    printf("(%.1f) \t ", arr[i].temperatures[arr[i].coldest]);
    printf("%s ", months[arr[i].hottest]);
    printf("(%.1f)\n", arr[i].temperatures[arr[i].hottest]);
    }
    // print out the header for average temp, and the months   
    printf("\n%s\n", "Average Temperature:");
    for(i=0; i<12; i++){
        printf("%s\t", months[i]);  
    }
    // call a function that calculates the overall average for each month
    yearlyAverage(arr, numOfYears);
}



//function that calculates the overall average for each month
int yearlyAverage(struct Data temps[], int numOfYears){
    // set the default values of the array to 0 (I had an issue where sometimes they had a default value of a memory address)
    float average[12] = {0};
    int i;
    // loop to add the temperatures for each month
    // could of used 2 for loops but I used this for debugging
    for(i=0; i<numOfYears; i++){
        average[0] += temps[i].temperatures[0];
        average[1] += temps[i].temperatures[1];
        average[2] += temps[i].temperatures[2];
        average[3] += temps[i].temperatures[3];
        average[4] += temps[i].temperatures[4];
        average[5] += temps[i].temperatures[5];
        average[6] += temps[i].temperatures[6];
        average[7] += temps[i].temperatures[7];
        average[8] += temps[i].temperatures[8];
        average[9] += temps[i].temperatures[9];
        average[10] += temps[i].temperatures[10];
        average[11] += temps[i].temperatures[11];
    }
    // print out the results
    printf("\n");
    for(i=0; i<12; i++){
        printf("%.1f\t", average[i]/numOfYears);
    }
 
}
