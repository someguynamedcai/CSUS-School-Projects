//Eric Cai
//CSC 20
//Section 4
//Semester Project
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Gradebook implements ActionListener{
   static JButton[] StartButtons = new JButton[8];
   static JButton[] ZCButtons = new JButton[2];
   static JButton[] FCButtons = new JButton[2];
   static JPanel[] Cards = new JPanel[8];
   static Container contentPane;
   static CardLayout contentPaneLayout;
   static JFrame frm;
   static ActionListener AL;
   public static void main(String[] args){
      frm = new JFrame("CsC 20 Gradebook by Eric Cai");
      contentPane = frm.getContentPane();
      contentPane.setLayout(contentPaneLayout = new CardLayout());
      JPanel FirstCard = new JPanel(new BorderLayout());
      AL = new Gradebook();
      // Making the frame 
      
      StartButtons[0] = new JButton("0.Create a New Class");
      StartButtons[1] = new JButton("1.Load Students From...");
      StartButtons[2] = new JButton("2.Add New Students");
      StartButtons[3] = new JButton("3.Enter Lab Scores");
      StartButtons[4] = new JButton("4.Sort Studetns");
      StartButtons[5] = new JButton("5.View/Delete Students");
      StartButtons[6] = new JButton("6.Backup Students To...");
      StartButtons[7] = new JButton("7.Exit");
      
      for (int count = 0; count <=7; count++){
         StartButtons[count].addActionListener(AL); 
         }
      //Making the 1st Screen Buttons and adding ActionListeners
      
      JPanel top = new JPanel(new BorderLayout());
      JLabel label = new JLabel("<html><font size = 4><b>Use The Buttons Below to Manage Students</b></html>",JLabel.CENTER);
      top.add(label, BorderLayout.NORTH);
      JPanel labelsTxtF = new JPanel(new FlowLayout());
      JLabel ClassLabel = new JLabel("Class Name:");
      JLabel NumOfStuLabel = new JLabel("Number of Students:");
      JTextField ClassName = new JTextField("",10);
      ClassName.setEditable(false);
      labelsTxtF.add(ClassLabel);
      labelsTxtF.add(ClassName);
      JTextField NumOfStu = new JTextField("0",10);
      NumOfStu.setEditable(false);
      labelsTxtF.add(NumOfStuLabel);
      labelsTxtF.setSize(200,50);
      labelsTxtF.add(NumOfStu);
      top.add(labelsTxtF);
      
      JPanel bot = new JPanel(new GridLayout(2,4,2,2));
      for (int count = 0; count <=7; count++){
         bot.add(StartButtons[count]);
         }
      
      FirstCard.add(top,BorderLayout.NORTH);
      FirstCard.add(bot,BorderLayout.SOUTH);
      contentPane.add(FirstCard);
      Cards[0] = new JPanel(new FlowLayout());
      ZeroButton();
      Cards[1] = new JPanel(new FlowLayout());
      FirstButton();
      frm.pack();
      frm.setSize(600,200);
      frm.setResizable(false);
      frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      frm.setVisible(true);
      }
   public void actionPerformed(ActionEvent e) {
         if (e.getSource() == StartButtons[0]){
            contentPaneLayout.show(contentPane, "Card 0");
            }
         if (e.getSource() == ZCButtons[1]){
            contentPaneLayout.first(contentPane);
            }
         if (e.getSource() == StartButtons[1]) {
            contentPaneLayout.show(contentPane, "Card 1");
            }
         if (e.getSource() == FCButtons[1]){
            contentPaneLayout.first(contentPane);
            }
            
      }
   //Making the Buttons on the First Card work
   
   public static void ZeroButton(){
      JPanel ZeroCardPanel = new JPanel(new BorderLayout());
      JLabel ZeroCardLabel = new JLabel("<html><font size = 4><b>Create a New Class</b></html>",JLabel.CENTER);
      JLabel ZeroCardCN = new JLabel("Class Name:");
      JTextField ZeroCardCNTf = new JTextField("",10);
      ZCButtons[0] = new JButton("Create");
      ZCButtons[0].addActionListener(AL);
      ZCButtons[1] = new JButton("Cancel");
      ZCButtons[1].addActionListener(AL);
      //Creating everything
      
      JPanel ZeroCardMidPanel = new JPanel(new FlowLayout());
      ZeroCardMidPanel.add(ZeroCardCN);
      ZeroCardMidPanel.add(ZeroCardCNTf);
      //Adding the TextField
      
      JPanel ZeroCardBotPanel = new JPanel(new GridLayout(1,2,2,2));     
      ZeroCardBotPanel.add(ZCButtons[0]);
      ZeroCardBotPanel.add(ZCButtons[1]);
      //Adding the Buttons
      
      ZeroCardPanel.add(ZeroCardLabel,BorderLayout.NORTH);
      ZeroCardPanel.add(ZeroCardMidPanel,BorderLayout.CENTER);
      ZeroCardPanel.add(ZeroCardBotPanel,BorderLayout.SOUTH);
      
      Cards[0].add(ZeroCardPanel);
      contentPane.add(Cards[0],"Card 0");
      frm.pack();
      frm.setSize(600,200);
		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frm.setVisible(true);

   }
   public static void FirstButton(){
      JPanel FirstCardPanel = new JPanel(new BorderLayout());
      JLabel FirstCardLabel = new JLabel("<html><font size = 4><b>Load Students From a File</b></html>",JLabel.CENTER);
      JLabel FirstCardCN = new JLabel("Class Name:");
      JTextField FirstCardCNTf = new JTextField("",10);
      FCButtons[0] = new JButton("Load");
      FCButtons[0].addActionListener(AL);
      FCButtons[1] = new JButton("Cancel");
      FCButtons[1].addActionListener(AL);
      
      JPanel FirstCardMidPanel = new JPanel(new FlowLayout());
      FirstCardMidPanel.add(FirstCardCN);
      FirstCardMidPanel.add(FirstCardCNTf);
      //Adding the TextField
      
      JPanel FirstCardBotPanel = new JPanel(new GridLayout(1,2,2,2));     
      FirstCardBotPanel.add(FCButtons[0]);
      FirstCardBotPanel.add(FCButtons[1]);
      //Adding the Buttons
      
      FirstCardPanel.add(FirstCardLabel,BorderLayout.NORTH);
      FirstCardPanel.add(FirstCardMidPanel,BorderLayout.CENTER);
      FirstCardPanel.add(FirstCardBotPanel,BorderLayout.SOUTH);
      
      Cards[1].add(FirstCardPanel);
      contentPane.add(Cards[1],"Card 1");
      frm.pack();
      frm.setSize(600,200);
		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frm.setVisible(true);

      
      }
    }
   //Second Card of the Program
      