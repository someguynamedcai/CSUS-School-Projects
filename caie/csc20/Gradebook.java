//Eric Cai
//CSC 20
//Section 4
//Semester Project

import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class Student implements Serializable {
   String SSN;
   String Name;
   String Gender;
   String Age;
   String Year;
   int Lab1, Lab2, Lab3, Lab4, Lab5, Lab6, Lab7, Lab8, Lab9, Lab10;
}
public class Gradebook implements ActionListener {
   static JButton[] StartButtons = new JButton[8];
   static JButton[] C0Buttons = new JButton[2];
   static JButton[] C1Buttons = new JButton[2];
   static JButton[] C2Buttons = new JButton[2];
   static JButton C3Button;
   static JButton[] C4Buttons = new JButton[2];
   static JButton[] C5Buttons = new JButton[2];
   static JPanel[] Cards = new JPanel[8];
   
   static Container contentPane;
   static CardLayout contentPaneLayout;
   static JFrame frm;
   static ActionListener AL = new Gradebook();
   
   static JTextField ClassNameTf;
   static JTextField NumOfStuTf;
   
   static JTextField CardZeroCNTf;
   
   static JTextField CardOneCNTf;
   
   static JTextField CardTwoSSNTf;
   static JTextField CardTwoNameTf;
   static JTextField CardTwoAgeTf;
   static JComboBox CardTwoGenderList;
   static JComboBox CardTwoALList;
   static String[] GenderStrings;
   static String[] ALStrings;
   
   static JLabel CardThreeSC;
   static JTextField CardThreeLNTf;
   static JTextField CardThreeSCTf;
   
   static JTable Table = new JTable();
   static JScrollPane ScrollPane = new JScrollPane(); 
   static JScrollPane HoldSP = new JScrollPane();
   static String[][] StudentData;
   static String[] TableHeaders = { " ID ", "Name", "Level", "Gender", "Age", "Lab 01", 
   "Lab 02", "Lab 03","Lab 04", "Lab 05", "Lab 06", "Lab 07", "Lab 08", "Lab 09", "Lab 10"};
   
   static String ClassName = "";
	static Student[] StudentArray = new Student[1000];
	static int StudentCount; 
   static int LabNumber;
   static int CurrentStudent;
   
   public static void main(String[] args){
      frm = new JFrame("CsC 20 Gradebook by Eric Cai");
      contentPane = frm.getContentPane();
      contentPane.setLayout(contentPaneLayout = new CardLayout());
      JPanel BeginCard = new JPanel(new BorderLayout());
      // Making the frame 
      
      StartButtons[0] = new JButton("0.Create a New Class");
      StartButtons[1] = new JButton("1.Load Students From...");
      StartButtons[2] = new JButton("2.Add New Students");
      StartButtons[3] = new JButton("3.Enter Lab Scores");
      StartButtons[4] = new JButton("4.Sort Students");
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
      
      JPanel labelsTf = new JPanel(new FlowLayout());
      JLabel ClassLabel = new JLabel("Class Name:");
      JLabel NumOfStuLabel = new JLabel("Number of Students:");
      ClassNameTf = new JTextField("",10);
      ClassNameTf.setEditable(false);
      labelsTf.add(ClassLabel);
      labelsTf.add(ClassNameTf);
      
      NumOfStuTf = new JTextField("0",10);
      NumOfStuTf.setText("" + StudentCount);
      NumOfStuTf.setEditable(false);
      
      labelsTf.add(NumOfStuLabel);
      labelsTf.setSize(200,50);
      labelsTf.add(NumOfStuTf);
      top.add(labelsTf);
      
      JPanel bot = new JPanel(new GridLayout(2,4,2,2));
      for (int count = 0; count <=7; count++) {
         bot.add(StartButtons[count]);
         }
      
      BeginCard.add(top,BorderLayout.NORTH);
      BeginCard.add(bot,BorderLayout.SOUTH);
      
      contentPane.add(BeginCard);
      for (int count = 0; count<=7; count++){
         Cards[count] = new JPanel(new FlowLayout());
         }
      CardZero();
      CardOne();
      CardTwo();
      CardThree();
      CardFour();
      CardFive();
      frm.pack();
      frm.setSize(750,220);
      frm.setResizable(true);
      frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      frm.setVisible(true);
      }
   public static void CardZero(){
      JPanel CardZeroPanel = new JPanel(new BorderLayout());
      JLabel CardZeroLabel = new JLabel("<html><font size = 4><b>Create a New Class</b></html>",JLabel.CENTER);
      JLabel CardZeroCN = new JLabel("Class Name:");
      CardZeroCNTf = new JTextField("",10);
      CardZeroCNTf.addActionListener(AL);
      
      C0Buttons[0] = new JButton("Create");
      C0Buttons[1] = new JButton("Cancel");
      C0Buttons[0].addActionListener(AL);
      C0Buttons[1].addActionListener(AL);
      //Creating all Components 
      
      JPanel CardZeroMidPanel = new JPanel(new FlowLayout());
      CardZeroMidPanel.add(CardZeroCN);
      CardZeroMidPanel.add(CardZeroCNTf);
      //Adding the TextField. Formatting becomes almost the same with the other buttons
      
      JPanel CardZeroBotPanel = new JPanel(new GridLayout(1,2,2,2));     
      CardZeroBotPanel.add(C0Buttons[0]);
      CardZeroBotPanel.add(C0Buttons[1]);
      //Adding the Buttons
      
      CardZeroPanel.add(CardZeroLabel,BorderLayout.NORTH);
      CardZeroPanel.add(CardZeroMidPanel,BorderLayout.CENTER);
      CardZeroPanel.add(CardZeroBotPanel,BorderLayout.SOUTH);
      
      Cards[0].add(CardZeroPanel);
      //Adding them to the card itself
      
      contentPane.add(Cards[0],"Card 0");
      }
   //Card Zero of the Program
   
   public static void CardOne(){
      JPanel CardOnePanel = new JPanel(new BorderLayout());
      JLabel CardOneLabel = new JLabel("<html><font size = 4><b>Load Students From a File</b></html>",JLabel.CENTER);
      JLabel CardOneCN = new JLabel("Class Name:");
      CardOneCNTf = new JTextField("",10);
      
      C1Buttons[0] = new JButton("Load");
      C1Buttons[1] = new JButton("Cancel");
      C1Buttons[0].addActionListener(AL);
      C1Buttons[1].addActionListener(AL);
      
      JPanel CardOneMidPanel = new JPanel(new FlowLayout());
      CardOneMidPanel.add(CardOneCN);
      CardOneMidPanel.add(CardOneCNTf);
      
      JPanel CardOneBotPanel = new JPanel(new GridLayout(1,2,2,2));     
      CardOneBotPanel.add(C1Buttons[0]);
      CardOneBotPanel.add(C1Buttons[1]);
      
      CardOnePanel.add(CardOneLabel,BorderLayout.NORTH);
      CardOnePanel.add(CardOneMidPanel,BorderLayout.CENTER);
      CardOnePanel.add(CardOneBotPanel,BorderLayout.SOUTH);
      
      Cards[1].add(CardOnePanel);
      contentPane.add(Cards[1],"Card 1");
      }
   //Card One of the program
   
   public static void CardTwo() {
      String[] GenderStrings = {"Male","Female"};
      String[] ALStrings = {"Freshman", "Sophomore", "Junior", "Senior"};
      
      JPanel CardTwoPanel = new JPanel(new BorderLayout());
      JPanel CardTwoPanel2 = new JPanel(new GridLayout(5,2));
      JLabel CardTwoLabel = new JLabel("<html><font size = 4><b>Enter Student Information</b></html>",JLabel.CENTER);
      JLabel CardTwoSSNLabel = new JLabel("SSN");
      JLabel CardTwoNameLabel = new JLabel("Name:");
      JLabel CardTwoGenderLabel = new JLabel("Gender:");
      JLabel CardTwoAgeLabel = new JLabel("Age");
      JLabel CardTwoALLabel = new JLabel("Academic Level:");
      
      CardTwoSSNTf = new JTextField("",15);
      CardTwoNameTf = new JTextField("",15);
      CardTwoAgeTf = new JTextField("",15);
      
      CardTwoGenderList = new JComboBox(GenderStrings);
      CardTwoALList = new JComboBox(ALStrings);
      CardTwoGenderList.addActionListener(AL);
      CardTwoALList.addActionListener(AL);
      
      C2Buttons[0] = new JButton("Save & Add Student");
      C2Buttons[1] = new JButton("Back To Top Menu");
      C2Buttons[0].addActionListener(AL);
      C2Buttons[1].addActionListener(AL);
      
      JPanel CardTwoBotPanel = new JPanel(new GridLayout(1,2,2,2));
      CardTwoBotPanel.add(C2Buttons[0]);
      CardTwoBotPanel.add(C2Buttons[1]);
      
      CardTwoPanel2.add(CardTwoLabel);
      CardTwoPanel2.add(CardTwoSSNLabel);
      CardTwoPanel2.add(CardTwoSSNTf);
      CardTwoPanel2.add(CardTwoNameLabel);
      CardTwoPanel2.add(CardTwoNameTf);
      CardTwoPanel2.add(CardTwoGenderLabel);
      CardTwoPanel2.add(CardTwoGenderList);
      CardTwoPanel2.add(CardTwoAgeLabel);
      CardTwoPanel2.add(CardTwoAgeTf);
      CardTwoPanel2.add(CardTwoALLabel);
      CardTwoPanel2.add(CardTwoALList);
      
      CardTwoPanel.add(CardTwoLabel,BorderLayout.NORTH);
      CardTwoPanel.add(CardTwoPanel2,BorderLayout.CENTER);
      CardTwoPanel.add(CardTwoBotPanel,BorderLayout.SOUTH);
      Cards[2].add(CardTwoPanel);
      contentPane.add(Cards[2],"Card 2");
      }
   //Card Two of the program
   
   public static void CardThree() {
      JPanel CardThreePanel = new JPanel(new BorderLayout());
      JLabel CardThreeLabel = new JLabel("<html><font size = 4><b>Enter Lab Scores</b></html>",JLabel.CENTER);
      JLabel CardThreeLN = new JLabel("Lab Number:");
      CardThreeSC = new JLabel("Score for :");
      
      CardThreeLNTf = new JTextField("",3);
      CardThreeSCTf = new JTextField("",7);
      C3Button = new JButton("Back To Top Menu");
      CardThreeLNTf.addActionListener(AL);
      CardThreeSCTf.addActionListener(AL);
      C3Button.addActionListener(AL);
      
      JPanel CardThreeMidPanelOne = new JPanel(new FlowLayout());
      CardThreeMidPanelOne.add(CardThreeLN);
      CardThreeMidPanelOne.add(CardThreeLNTf);
      
      JPanel CardThreeMidPanelTwo = new JPanel(new FlowLayout());
      CardThreeMidPanelTwo.add(CardThreeSC);
      CardThreeMidPanelTwo.add(CardThreeSCTf);
      
      JPanel CardThreeMidPanelThree = new JPanel(new BorderLayout());
      CardThreeMidPanelThree.add(CardThreeMidPanelOne,BorderLayout.NORTH);
      CardThreeMidPanelThree.add(CardThreeMidPanelTwo,BorderLayout.SOUTH);
      
      CardThreePanel.add(CardThreeLabel,BorderLayout.NORTH);
      CardThreePanel.add(CardThreeMidPanelThree,BorderLayout.CENTER);
      CardThreePanel.add(C3Button,BorderLayout.SOUTH);
      
      Cards[3].add(CardThreePanel);
      contentPane.add(Cards[3],"Card 3");
      }
   //Card Three of the Program
      
   public static void CardFour() {
      JPanel CardFourPanel = new JPanel(new BorderLayout());
      JLabel CardFourLabel = new JLabel("<html><font size = 4><b>Sort Students</b></html>",JLabel.CENTER);
      
      JRadioButton SortID = new JRadioButton("By ID");
      JRadioButton ByName = new JRadioButton("By Name");
      SortID.addActionListener(AL);
      ByName.addActionListener(AL);
      
      C4Buttons[0] = new JButton("Sort");
      C4Buttons[1] = new JButton("Top Menu");
      C4Buttons[0].addActionListener(AL);
      C4Buttons[1].addActionListener(AL);
      
      ButtonGroup CardFourButtonGroup = new ButtonGroup();
      CardFourButtonGroup.add(SortID);
      CardFourButtonGroup.add(ByName);
      
      JPanel CardFourMidPanel = new JPanel(new FlowLayout());
      CardFourMidPanel.add(SortID);
      CardFourMidPanel.add(ByName);
      
      JPanel CardFourBotPanel = new JPanel(new GridLayout(1,2,2,2));
      CardFourBotPanel.add(C4Buttons[0]);
      CardFourBotPanel.add(C4Buttons[1]);
      
      CardFourPanel.add(CardFourLabel,BorderLayout.NORTH);
      CardFourPanel.add(CardFourMidPanel,BorderLayout.CENTER);
      CardFourPanel.add(CardFourBotPanel,BorderLayout.SOUTH);
      
      Cards[4].add(CardFourPanel);
      contentPane.add(Cards[4],"Card 4");
   }
   // Card Four of the program
   public static void CardFive() {
      JPanel CardFivePanel = new JPanel(new BorderLayout());
      JLabel CardFiveLabel = new JLabel("<html><font size = 4><b>Student List</b></html>",JLabel.CENTER);
      
      C5Buttons[0] = new JButton("Delete Student");
      C5Buttons[1] = new JButton("Cancel");
      C5Buttons[0].addActionListener(AL);
      C5Buttons[1].addActionListener(AL);
      
      JPanel CardFiveBotPanel = new JPanel(new GridLayout(1,2,2,2));
      CardFiveBotPanel.add(C5Buttons[0]);
      CardFiveBotPanel.add(C5Buttons[1]);

      CardFivePanel.add(CardFiveLabel,BorderLayout.NORTH);
      CardFivePanel.add(CardFiveBotPanel,BorderLayout.SOUTH);
      CardFivePanel.add(ScrollPane);
      Cards[5].add(CardFivePanel);
      contentPane.add(Cards[5], "Card 5");
      }
   // Card Five of the program
   
   public void actionPerformed(ActionEvent e) {
         if (e.getSource() == StartButtons[0]){
            contentPaneLayout.show(contentPane, "Card 0");
            }
         if (e.getSource() == C0Buttons[0]) { 
            ClassName = CardZeroCNTf.getText();
            StudentCount = 0;
            ClassNameTf.setText(CardZeroCNTf.getText());
            NumOfStuTf.setText("" + StudentCount);
            contentPaneLayout.first(contentPane);
            }
         //Actions for the Create a Class Card

         if (e.getSource() == StartButtons[1]) {
            contentPaneLayout.show(contentPane, "Card 1");
            }
         if (e.getSource() == C1Buttons[0]) {
            ClassName = CardOneCNTf.getText(); 
            ClassNameTf.setText(ClassName);
            StudentCount = 0;
			   try { 
               FileInputStream fis = new FileInputStream(ClassName);
				   ObjectInputStream ois = new ObjectInputStream(fis);
				   while (true) {
					   StudentArray[StudentCount] = (Student)ois.readObject(); 
                  StudentCount++;
				   }
			   } 
            catch(EOFException x) {
            }  
            catch(Exception x) { 
               x.printStackTrace(); 
			   }
		      ClassNameTf.setText(ClassName); 
            NumOfStuTf.setText("" + StudentCount);
			   contentPaneLayout.first(contentPane);
		   }
         
         if (e.getSource() == StartButtons[2]) {
            contentPaneLayout.show(contentPane, "Card 2");
            }
         if (e.getSource() == C2Buttons[0]) {
            Student Temp = new Student();
			   Temp.SSN = CardTwoSSNTf.getText();
			   Temp.Name = CardTwoNameTf.getText();
            Temp.Age = CardTwoAgeTf.getText();
            Temp.Gender = ((String)CardTwoGenderList.getSelectedItem());
			   Temp.Year = ((String)CardTwoALList.getSelectedItem());
			   StudentArray[StudentCount] = Temp;
			   StudentCount++; String IntToString = String.valueOf(StudentCount); 
            NumOfStuTf.setText(IntToString);
			   CardTwoSSNTf.setText(""); 
            CardTwoNameTf.setText(""); 
            CardTwoAgeTf.setText("");
			   CardTwoGenderList.setSelectedIndex(0); 
            CardTwoALList.setSelectedIndex(0);
            }
 
         if (e.getSource() == StartButtons[3]) {
            contentPaneLayout.show(contentPane, "Card 3");
            }
         if (e.getSource() ==CardThreeLNTf) {
            CurrentStudent = 0;
			   LabNumber = Integer.valueOf(CardThreeLNTf.getText()).intValue();
			   CardThreeSC.setText("Score For " + StudentArray[CurrentStudent].Name + ": ");
		   }
         if (e.getSource() == CardThreeSCTf) {
            int Score = Integer.valueOf(CardThreeSCTf.getText()).intValue();
			   switch (LabNumber)
			   {
			   	case 1: StudentArray[CurrentStudent].Lab1 = Score; break;
			   	case 2: StudentArray[CurrentStudent].Lab2 = Score; break;
			   	case 3: StudentArray[CurrentStudent].Lab3 = Score; break;
			   	case 4: StudentArray[CurrentStudent].Lab4 = Score; break;
			   	case 5: StudentArray[CurrentStudent].Lab5 = Score; break;
			   	case 6: StudentArray[CurrentStudent].Lab6 = Score; break;
			   	case 7: StudentArray[CurrentStudent].Lab7 = Score; break;
			   	case 8: StudentArray[CurrentStudent].Lab8 = Score; break;
			   	case 9: StudentArray[CurrentStudent].Lab9 = Score; break;
			   	case 10: StudentArray[CurrentStudent].Lab10 = Score; break;
			   	case 0: System.out.println("Invalid");
               CurrentStudent ++;
			      CardThreeSCTf.setText("");
               
			      if (CurrentStudent >= StudentCount) { 
               LabNumber = 0; 
               CardThreeLNTf.setText(""); 
               CardThreeSCTf.setText("");
               CardThreeSC.setText("Score For: "); 
               return; 
               }
			      else { 
                  CardThreeSC.setText("Score For " + StudentArray[CurrentStudent].Name + ": "); 
                  }
		         }
            }
         if (e.getSource() == StartButtons[4]) {
            contentPaneLayout.show(contentPane, "Card 4");
            }
         if (e.getSource() == StartButtons[5]) {
            String[][] StudentData = new String[StudentCount][15];
            for (int i = 0; i < StudentCount; i++) {
			   	StudentData[i][0] = StudentArray[i].SSN; 
               StudentData[i][1] = StudentArray[i].Name;
			   	StudentData[i][2] = StudentArray[i].Year; 
               StudentData[i][4] = StudentArray[i].Age;
			   	StudentData[i][3] = StudentArray[i].Gender + ""; 
               StudentData[i][5] = StudentArray[i].Lab1 + "";
			   	StudentData[i][6] = StudentArray[i].Lab2 + ""; 
               StudentData[i][7] = StudentArray[i].Lab3 + "";
			   	StudentData[i][8] = StudentArray[i].Lab4 + ""; 
               StudentData[i][9] = StudentArray[i].Lab5 + "";
			   	StudentData[i][10] = StudentArray[i].Lab6 + ""; 
               StudentData[i][11] = StudentArray[i].Lab7 + "";
			   	StudentData[i][12] = StudentArray[i].Lab8 + ""; 
               StudentData[i][13] = StudentArray[i].Lab9 + "";
			   	StudentData[i][14] = StudentArray[i].Lab10 + "";
			      }
			   Table = new JTable(StudentData, TableHeaders);	   
            HoldSP = new JScrollPane(Table);
			   ScrollPane.setViewport(HoldSP.getViewport());
            contentPaneLayout.show(contentPane, "Card 5");
            }
         if (e.getSource() == C5Buttons[0]) {
			   int StudentIndex = Table.getSelectedRow();
			   for (int i = StudentIndex; i < StudentCount; i += 1) {
				   StudentArray[i] = StudentArray[i + 1];
			      }
			   StudentCount--;
			   String[][] StudentData = new String[StudentCount][15];
			   for (int i = 0; i < StudentCount; i += 1) {
				   StudentData[i][0] = StudentArray[i].SSN; 
               StudentData[i][1] = StudentArray[i].Name;
			   	StudentData[i][2] = StudentArray[i].Year; 
               StudentData[i][4] = StudentArray[i].Age;
			   	StudentData[i][3] = StudentArray[i].Gender + ""; 
               StudentData[i][5] = StudentArray[i].Lab1 + "";
			   	StudentData[i][6] = StudentArray[i].Lab2 + ""; 
               StudentData[i][7] = StudentArray[i].Lab3 + "";
			   	StudentData[i][8] = StudentArray[i].Lab4 + ""; 
               StudentData[i][9] = StudentArray[i].Lab5 + "";
			   	StudentData[i][10] = StudentArray[i].Lab6 + ""; 
               StudentData[i][11] = StudentArray[i].Lab7 + "";
			   	StudentData[i][12] = StudentArray[i].Lab8 + ""; 
               StudentData[i][13] = StudentArray[i].Lab9 + "";
			   	StudentData[i][14] = StudentArray[i].Lab10 + "";
			      }			
			   Table = new JTable(StudentData, TableHeaders); 
			   JScrollPane HoldSP2 = new JScrollPane(Table);
			   ScrollPane.setViewport(HoldSP2.getViewport());
			   NumOfStuTf.setText(StudentCount + "");
			   contentPaneLayout.show(contentPane, "Card 5");
		   }
         if (e.getSource() == StartButtons[6]) {
            try { 
               FileOutputStream fos = new FileOutputStream(ClassName, false);
				   ObjectOutputStream oos = new ObjectOutputStream(fos);
				   for (int count = 0; count < StudentCount; count++)
				   {
				   	oos.writeObject(StudentArray[count]);
				   }
				   oos.close();
			   } 
            catch (FileNotFoundException ex) { 
               ex.toString(); 
               } 
            catch(IOException ex) { 
               ex.printStackTrace(); 
               }
		   }
         
         if (e.getSource() == C0Buttons[1] || e.getSource() == C1Buttons[1] || e.getSource() == C2Buttons[1] || e.getSource() == C3Button || e.getSource() == C4Buttons[1] || e.getSource() == C5Buttons[1]) {
            contentPaneLayout.first(contentPane);
            }
         if (e.getSource() == StartButtons[7]) {
            System.exit(0);
            }          
      }
   
}