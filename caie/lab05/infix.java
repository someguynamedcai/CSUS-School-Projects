//Eric Cai
//Csc 20
//Section 04
// infix.java
import java.io.*;
import MyStackQueue.*;

class infix {

	static Queue infixToPostfix(String s) 
   {
      Stack myStack = new Stack();
      Queue myQueue = new Queue();
      Tokenizer T = new Tokenizer(s);
      Token Tkn = T.nextToken();
      
      myStack.push(new Operator('#'));
      while (Tkn != null)
      {
           if (Tkn instanceof Operand)
           {
             myQueue.enqueue(Tkn);
           }
           else
           {
            Operator Opr = (Operator)Tkn;
            if (Opr.operator == '(' )
            {
               myStack.push(new Operator('('));
            }
            else
            {
               if (Opr.operator == ')')
               {
                  while (((Operator)myStack.top()).operator != '(')
                  {
                     myQueue.enqueue(myStack.pop());
                  }
                  myStack.pop();
               }
               else
               {                  
                  while (((Operator)myStack.top()).precedence() >= Opr.precedence())
                     {     
                        myQueue.enqueue(myStack.pop());
                     }
                  myStack.push(Opr);
               }
            }
           }
           Tkn = T.nextToken();
      }
      while (((Operator)myStack.top()).operator != '#')
         {
            myQueue.enqueue(myStack.pop());
         }
      return myQueue;

	}

	static int evaluatePostfix(Queue Post) 
   {
      Stack myStack = new Stack();
      String post = Post.toString();
      int result = 0;
      while (!Post.isEmpty())
      {
         Token Tkn = (Token)Post.dequeue();
         if (Tkn instanceof Operand)
         {
            myStack.push(Tkn);
         }
         else
         {
            Operator Opr = (Operator)Tkn;
            int opnd2 = ((Operand)myStack.pop()).operand;
            int opnd1 = ((Operand)myStack.pop()).operand;
            switch(Opr.operator)
            {
               case '+': result = opnd1 + opnd2; break;
               case '*': result = opnd1 * opnd2; break;
               case '-': result = opnd1 - opnd2 ; break;
               case '/': result = opnd1 /opnd2; break;
            }
            myStack.push(new Operand(result));
         }
      }
      return result; 
	}

	public static void main(String[] args) throws IOException 
   {
	   Queue Post;
	   System.out.println("Instructor's test program");
	   while(true) 
      {
		   System.out.print("Enter infix: ");
		   System.out.flush();
		   InputStreamReader isr = new InputStreamReader(System.in);
		   BufferedReader br = new BufferedReader(isr);
		   String s = br.readLine();
		   if ( s.equals("") ) break;
		   Post = infixToPostfix(s);
		   System.out.println("Postfix is " + Post.toString() + '\n');
		   int result = evaluatePostfix(Post);
		   System.out.println("Result is " + result + '\n');
	}
     }
}
