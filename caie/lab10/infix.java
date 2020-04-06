//Eric Cai
//CSC 20
//Section 04
//Lab 10
//infix.java
import java.io.*;
import java.util.*;

class infix{

	static LinkedList<Token> infixToPostfix(String s) throws Exception {
      Stack <Operator> myStack=new Stack <Operator>();
      LinkedList <Token> myQueue=new LinkedList <Token>(); 
      Tokenizer T=new Tokenizer(s);
      Token Tkn=T.nextToken();
      
      myStack.push(new Operator('#'));
      while(Tkn!=null){
         if(Tkn instanceof Operand){
            myQueue.addLast(Tkn);
         }     
         else{
            Operator Opr=(Operator)Tkn;
            if(Opr.operator == '('){
               myStack.push(Opr);
            }   
            else{
               if(Opr.operator == ')'){
                  try{
                     while(((myStack.peek())).operator != '('){
                        myQueue.addLast((myStack.peek()));
                        myStack.pop();
                     }
                     myStack.pop();
                  }
                  catch(Exception e){
                     throw new infixException(errorType.ExcessRightParenthesis);
                  }
               }                              
               else{  
                  
                  while(Opr.precedence() <= ((myStack.peek()).precedence())){
                     myQueue.addLast(myStack.peek());
                     myStack.pop();
                  }  
                  myStack.push(Opr);
               }
            }
         } 
         Tkn=T.nextToken(); 
      }   
      while((myStack.peek()).operator != '#'){
         if((myStack.peek()).operator == '('){
            throw new infixException(errorType.ExcessLeftParenthesis);
         }   
         myQueue.addLast(myStack.peek());
         myStack.pop();
      }
      return myQueue;
   }
               
                
	static int evaluatePostfix(LinkedList<Token> Post) throws Exception {
      Stack<Operand> myStack = new Stack<Operand>(); 
      int answer = 0;
      while(!Post.isEmpty()){
      
         Token Tkn = Post.removeFirst();
         if(Tkn instanceof Operand){
            myStack.push((Operand)Tkn);
         }
         else{
            try{
               int opnd2= myStack.pop().operand;
               int opnd1=(myStack.pop()).operand;
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
                  throw new infixException(errorType.ExcessOperator);
               }       
         }
            
      }
      myStack.pop();
      if(!myStack.empty()){
         throw new infixException(errorType.ExcessOperand);
      }   
      return answer;
   }   
               
                  
	

	public static void main(String[] args) throws IOException {
   	LinkedList<Token> Post;
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
      		System.out.print("Postfix is ");
            for (Token t: Post){
               System.out.print(t.toString()+" ");
            }
            System.out.println();      
      		int result = evaluatePostfix(Post);
      		System.out.println("Result is " + result + '\n');
         }
         catch(Exception e){
            System.out.println(e.toString());
         }      
   	}  
   }
}
enum errorType { ExcessLeftParenthesis, ExcessRightParenthesis, ExcessOperator, ExcessOperand};
class infixException extends Exception {
private errorType etype;
public infixException(errorType et) {
etype = et;
}
public String toString() {
return etype.name();
}
} 
