import java.util.*;
public class Multiply	{
	public static void main (String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.println("First number?");
		int firstN = kb.nextInt();
		System.out.println("Second number?");
		int secondN = kb.nextInt();

		int fN1 = firstN%10;
		int fN2 = (((firstN - fN1)/10)%10); 
		int fN3 = ((firstN - (firstN%100))/100);

		int sN1 = secondN%10;
		int sN2 = (((secondN - sN1)/10)%10); 
		int sN3 = ((secondN - (secondN%100))/100);

		int xN1 = (fN1 * sN1)%10;
		int xN2 = ((fN2 * sN1)%10) + ((((fN1 * sN1) -  xN1))/10)%10;
		int xN3 = ((fN3 * sN1) + ((fN2*sN1) - (fN2*sN1)%10)/10);
	
		int yN1 = (fN1 * sN2)%10;
		int yN2 = ((fN2 * sN2)%10) + ((((fN1 * sN2) - yN1))/10)%10; 
		int yN3 = ((fN3 * sN2)) + ((fN2*sN2) - (fN2*sN2)%10)/10;


		int zN1 = (fN1 * sN3)%10;
		int zN2 = ((fN2 * sN3)%10) + ((((fN1 * sN3) - zN1))/10)%10; 
		int zN3 = ((fN3 * sN3) + ((fN2*sN3) - (fN2*sN3)%10)/10);

		System.out.printf("%15s\n", firstN);
		System.out.print("X");
		System.out.printf("%14s\n" ,secondN);
		System.out.println("-------------------");
		System.out.printf("%15s\n", xN3 + "" + xN2 + "" + xN1);
		System.out.printf("%14s\n", yN3 + "" + yN2 + "" + yN1);
		System.out.printf("%13s\n", zN3 + "" + zN2 + "" + zN1);
		System.out.println("-------------------");
		System.out.printf("%15s\n", firstN*secondN);
      }
      }