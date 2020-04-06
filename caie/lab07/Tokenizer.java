/*
Augustine Orozco
CSC 20 Wang
Section 4
Lab 06
10/15/15
*/
//import java.util.*;
class Tokenizer {
   private char [] Buf;
   private int cur;
   
   Tokenizer(String infixExpression) {
      Buf = infixExpression.toCharArray();
      cur = 0;
   }
   
   Token nextToken() {
      if(cur>=Buf.length){
         return null;
      }
      while(Buf[cur] == ' '){
         cur++;
      }
      if(Buf[cur]>=0x30 && Buf[cur]<=0x39){
         String Digits="";
         while(Buf[cur]>=0x30 && Buf[cur]<=0x39){
               Digits=Digits+Buf[cur];
               cur++;
               if(cur>=Buf.length){
                  break;
               }   
         }
         int num=Integer.valueOf(Digits).intValue();
         Operand opnd=new Operand(num);
         return opnd;
      }        
      else{
         Operator opr=new Operator(Buf[cur]);
         cur++;   
         return opr;
      }   
   }                          
         //Skip Blanks
         //if(cur>=Buf.length) return null;
         //if next char=digit, convert to int. Keep going until !digit
}      