//Eric Cai
//Csc 20
//Section 04
public class SortedList 
{
	SortedList() {
		System.out.println("Instructor's Test Sorted Class");
	}
	private DLNode current, Head, Tail;

	public void insert(double n)
   {
	   DLNode current = Head;
	   DLNode prv = null;
      while(current!=null && current.data<=n) { prv = current;  current = current.Next;}
      {
   	DLNode tmp = new DLNode(); tmp.data = n;
   	if (prv!=null) prv.Next = tmp; else Head = tmp;
   	tmp.Prev = prv;
   	tmp.Next = current;
   	if (current!=null) current.Prev = tmp; else Tail = tmp;
      }
   }

	public void listAscending() 
   {         
      DLNode current = Head;
      int count = 0;
      while (current != null)
      {
         System.out.printf("%f ", current.data);
         current = current.Next;
         count++;
         if (count == 5)
         {
            System.out.println();
            count = 0;
         }
      }
	}

	public void listDescending() 
   {
      DLNode current = Tail;
      int count = 0;
      while (current != null)
      {
         System.out.printf("%f ", current.data);
         current = current.Prev;
         count++;
         if (count == 5)
         {
            System.out.println();
            count = 0;
         }
      }

	}

}
