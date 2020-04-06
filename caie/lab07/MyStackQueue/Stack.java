//Eric Cai
//Csc 20
//Section 04
public class Stack<E> extends Vector<E> {
public Stack(); // constructor
public Boolean empty();
public E peek();
public E pop();
public E push(E item);
}
class Node {
	public Object Data = null;
	public Node Next = null;
}