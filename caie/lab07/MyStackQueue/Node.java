package MyStackQueue;

public class Node{
   Object Data=null;
   Node Next=null;
   public Node(Object Element){
      Data=Element;
   }
   public void setNext(Node N){
      Next=N;
   }
   public Node getNext(){
      return Next;
   }
   public Object getElement(){
      return Data;
   }
   public void setElement(Object Element){
      Data=Element;
   }
}                     