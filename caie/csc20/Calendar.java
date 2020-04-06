/* 
Lab Number : 2
Eric Cai
Section Number: 4
*/

import java.util.*;
public class Calendar {
	public static void main(String[]args) 
   {
      JulianDate JD = new JulianDate();
		Scanner kb = new Scanner(System.in);
		System.out.print("Type in a Year:");
		int year = kb.nextInt();
		int date = JD.toJulian(year,1,1);
      int dayOfWeek = (date+1)%7; // 0 means Sunday, 1 means Monday, etc.

		System.out.printf("%11d\n", year);
      String monthName = "";
      int days = 31;
      for (int month = 1; month <=12; month++)
         {
         System.out.println();
            switch(month) 
            {
            case 1:  monthName = "January";
                     days = 31;
                     break;
            case 2:  monthName = "February";
                     days = 28;
                     if (year % 100 == 0)
                     {
                        if (year % 400 == 0)
                        {
                           days = 29;
                        }
                     }
                     else
                     {
                        if (year % 4 == 0)
                        {
                           days = 29;
                        }
                     }
                     break;
            case 3:  monthName = "March";
                     days = 31;
                     break;
            case 4:  monthName = "April";
                     days = 30;
                     break;
            case 5:  monthName = "May";
                     days = 31;
                     break;
            case 6:  monthName = "June";
                     days = 30;
                     break;
            case 7:  monthName = "July";
                     days = 31;
                     break;
            case 8:  monthName = "August";
                     days = 31;
                     break;
            case 9:  monthName = "September";
                     days = 30;
                     break;
            case 10: monthName = "October";
                     days = 31;
                     break;
            case 11: monthName = "November";
                     days = 30;
                     break;
            case 12: monthName = "December";
                     days = 31;
                     break;
            }
            System.out.printf("%"+(10+monthName.length()/2)+"s\n", monthName);
            System.out.printf("%3s%3c%3s%3c%3s%3c%3c\n","Su",'M',"Tu",'W',"Th",'F','S');
            int dayCount = 1;
            if (dayOfWeek > 0)
            {
               System.out.printf("%" + (dayOfWeek*3) + "c",' '); 
               
            }
            while (dayCount <= days)
            {
               System.out.printf("%3d", dayCount);
               dayOfWeek++;
               if (dayOfWeek == 7)
               {
                  dayOfWeek = 0;
                  System.out.println();
               }
               dayCount++;
            }
            System.out.println();
            
         }
   }
                      }
      