//Eric Cai
//CSC 20
//Section 04
//infix.java
import java.io.*;
import MyStackQueue.*;

class infix {

	static Queue infixToPostfix(String s) throws Exception {
      Stack myStack=new Stack();
      Queue myQueue=new Queue();
      Tokenizer T=new Tokenizer(s);
      Token Tkn=T.nextToken();
      
      myStack.push(new Operator('#'));
      while(Tkn!=null){
         if(Tkn instanceof Operand){
            myQueue.enqueue(Tkn);
         }     
         else{
            Operator Opr=(Operator)Tkn;
            if(Opr.operator == '('){
               myStack.push(Opr);
            }   
            else{
               if(Opr.operator == ')'){
                  try{
                     while(((Operator)myStack.top()).operator != '('){
                        myQueue.enqueue((Operator)myStack.top());
                        myStack.pop();
                     }
                     myStack.pop();
                  }
                  catch(Exception e){
                     throw new TooManyRP();
                  }
               }                              
               else{  
                  
                  while(Opr.precedence() <= (((Operator)myStack.top()).precedence())){
                     myQueue.enqueue((Operator)myStack.top());
                     myStack.pop();
                  }  
                  myStack.push(Opr);
               }
            }
         } 
         Tkn=T.nextToken(); 
      }   
      while(((Operator)myStack.top()).operator != '#'){
         if(((Operator)myStack.top()).operator == '('){
            throw new TooManyLP();
         }   
         myQueue.enqueue((Operator)myStack.top());
         myStack.pop();
      }
      return myQueue;
   }
               
                
	static int evaluatePostfix(Queue Post) throws Exception {
      Stack myStack = new Stack(); 
      int answer = 0;
      while(!Post.isEmpty()){
         Token Tkn = (Token)Post.dequeue();
         if(Tkn instanceof Operand){
            myStack.push(Tkn);
         }
         else{
            try{
               int opnd2=((Operand)myStack.top()).operand;
               myStack.pop();
               int opnd1=((Operand)myStack.top()).operand;
               myStack.pop();
                  Operator opr=(Operator)Tkn;
                  switch (opr.operator){
                  case '+': answer = opnd1+opnd2;break;
                  case '-': answer = opnd1-opnd2;break;
                  case '/': answer = opnd1/opnd2;break;
                  case '*': answer = opnd1*opnd2;break;
                  }
                  myStack.push(new Operand(answer));
               }
               catch(Exception e){
                  throw new TooManyOperators();
               }       
         }
            
      }
      myStack.pop();
      if(!myStack.isEmpty()){
         throw new TooManyOperands();
      }   
      return answer;
   }   
               
                  
	

	public static void main(String[] args) throws IOException {
   	Queue Post;
   	System.out.println("Eric's test program");
   	while(true) {
   		System.out.print("Enter infix: ");
   		System.out.flush();
   		InputStreamReader isr = new InputStreamReader(System.in);
   		BufferedReader br = new BufferedReader(isr);
   		String s = br.readLine();  
   		if ( s.equals("") ) break;    
   		try{
            Post = infixToPostfix(s);
      		System.out.println("Postfix is " + Post.toString() + '\n');      
      		int result = evaluatePostfix(Post);
      		System.out.println("Result is " + result + '\n');
         }
         catch(Exception e){
            System.out.println(e.toString());
         }      
   	}  
   }
}
class TooManyRP extends Exception{
   public String toString(){
      return "*****Too many )*****";
   }
}  
class TooManyLP extends Exception{
   public String toString(){
      return "*****Too many (*****";
   }
}  
class TooManyOperands extends Exception{
   public String toString(){
      return "*****Too many operands*****";
   }
}  
class TooManyOperators extends Exception{
   public String toString(){
      return "*****Too many operators*****";
   }
}       
