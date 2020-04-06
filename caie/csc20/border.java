//Eric Cai
//CSC 20
//Section 4
//Lab 8
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class border implements ActionListener{
   public static void main(String[] args){
      JFrame frm = new JFrame("Calculator Thing");
      Container contentPane = frm.getContentPane();
      contentPane.setLayout(new FlowLayout());
      ActionListener AL = new border();
      
      JPanel top = new JPanel(new BorderLayout());
      JLabel label = new JLabel("Csc 20 Lab 08",JLabel.CENTER);
      JTextField tf = new JTextField("0",29);
      tf.setHorizontalAlignment(JTextField.RIGHT);
      top.add(label, BorderLayout.NORTH);
      top.add(tf, BorderLayout.SOUTH);
      
      JPanel mid = new JPanel(new GridLayout(4,4,2,2));

      mid.add(new JButton("C"));
      mid.add(new JButton("CE"));
      mid.add(new JButton("      +/-     "));
      mid.add(new JButton("/"));
	   mid.add(new JButton("7"));
      mid.add(new JButton("8"));
      mid.add(new JButton("9"));
      mid.add(new JButton("*"));
      mid.add(new JButton("4"));
      mid.add(new JButton("5"));
      mid.add(new JButton("6"));
      mid.add(new JButton("-"));
      mid.add(new JButton("1"));
      mid.add(new JButton("2"));
      mid.add(new JButton("3"));
      mid.add(new JButton("+"));
      JPanel bot= new JPanel(new GridLayout(1,2,2,2));
      bot.add(new JButton("        .       "));
      bot.add(new JButton("="));
      JPanel zero = new JPanel(new GridLayout(1,2,2,2));
      zero.add(new JButton("0"));
      zero.add(bot);
      contentPane.add(top);
      contentPane.add(mid);
      contentPane.add(zero);
      
		   frm.pack();
		   frm.setSize(340,220);
		   frm.setResizable(false);
		   frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		   frm.setVisible(true);
   }
}

