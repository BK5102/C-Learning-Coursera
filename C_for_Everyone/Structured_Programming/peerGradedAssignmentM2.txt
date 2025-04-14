/* Week 2 Assignment: Using Struct*/

/* Write enumerated types that supports dates—such as december 12. Then add a function that produces a next day. 
 So nextday(date) of december 12 is december 13. Also write a function printdate(date) that prints a date legibly.
 The function can assume that February has 28 days and it most know how many days are in each month. Use a struct 
 with two members; one is the month and the second  is the day of the month—an int (or short).
    Then print out  the date January 1  and print  the next day Jan 2.
    Do this for the following dates:  February 28, March 14, October 31, and  December 31.
 */


 #include <stdio.h>

 typedef enum month { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec } month;
 
 typedef struct date {
     month m;
     int d;
 } date;
 
 // Days in each month (index matches month enum)
 int days_in_month[] = {
     31, // jan
     28, // feb (not considering leap years)
     31, // mar
     30, // apr
     31, // may
     30, // jun
     31, // jul
     31, // aug
     30, // sep
     31, // oct
     30, // nov
     31  // dec
 };
 
 char* month_names[] = {
     "January", "February", "March", "April", "May", "June",
     "July", "August", "September", "October", "November", "December"
 };
 
 // Function to get the next day
 date nextday(date d) {
     date next = d;
     if (d.d < days_in_month[d.m]) {
         next.d++;
     } else {
         next.d = 1;
         next.m = (d.m + 1) % 12;
     }
     return next;
 }
 
 // Function to print the date
 void printdate(date d) {
     printf("%s %d\n", month_names[d.m], d.d);
 }
 
 int main() {
     date dates[] = {
         {jan, 1},
         {feb, 28},
         {mar, 14},
         {oct, 31},
         {dec, 31}
     };
 
     int n = sizeof(dates)/sizeof(dates[0]);
 
     for (int i = 0; i < n; i++) {
         printdate(dates[i]);
         date next = nextday(dates[i]);
         printf("Next day: ");
         printdate(next);
         printf("\n");
     }
 
     return 0;
 }
 