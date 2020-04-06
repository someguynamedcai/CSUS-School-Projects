use test;

CREATE TABLE Course (
  CourseNo VARCHAR(50) NOT NULL,
  CourseName VARCHAR(50) NOT NULL,	
  Department VARCHAR(50),
  PRIMARY KEY(CourseNo)
);

CREATE TABLE Section (
  CourseNo VARCHAR(50) NOT NULL REFERENCES Course(CourseNo),
  SectionNo VARCHAR(50) NOT NULL,
  Instructor VARCHAR(50),
  PRIMARY KEY(CourseNo,SectionNo)
);

CREATE TABLE Enrolls (
  SSN INT NOT NULL REFERENCES Student(SSN),
  SectionNo VARCHAR(50) NOT NULL REFERENCES Section(CourseNo),
  CourseNo VARCHAR(50) NOT NULL REFERENCES Section(SectionNo),
  PRIMARY KEY(SSN,SectionNo,CourseNo)
);

CREATE TABLE Student (
  SSN INT NOT NULL,
  FirstName VARCHAR(50) NOT NULL,
  LastName VARCHAR(50),
  Street VARCHAR(50),
  City VARCHAR(50) NOT NULL,
  State VARCHAR(50) NOT NULL,
  Zip INT NOT NULL,
  PRIMARY KEY(SSN)
);

CREATE TABLE Takes (
  SSN INT NOT NULL REFERENCES Student(SSN),
  CourseNo VARCHAR(50) NOT NULL REFERENCES Exam(CourseNo),
  SectionNo VARCHAR(50) NOT NULL REFERENCES Exam(SectionNo),
  ExamNo INT NOT NULL REFERENCES Exam(ExamNo),
  Result VARCHAR(1),
  PRIMARY KEY(SSN,CourseNo,SectionNo,ExamNo)
);

CREATE TABLE Exam (
  CourseNo VARCHAR(50) NOT NULL,
  SectionNo INT NOT NULL,
  ExamNo INT NOT NULL,
  E_Date VARCHAR(50),
  E_Time VARCHAR(50),
  PRIMARY KEY(CourseNo, SectionNo, ExamNo)
);

CREATE TABLE ConductedIn (
  RoomNo INT NOT NULL REFERENCES ClassRoom(RoomNo),
  Building VARCHAR(50) REFERENCES ClassRoom(Building),
  CourseNo VARCHAR(50) NOT NULL REFERENCES Exam(CourseNo),
  SectionNo INT NOT NULL REFERENCES Exam(SectionNo),
  ExamNo INT NOT NULL REFERENCES Exam(ExamNo),
  PRIMARY KEY(RoomNo,Building,CourseNo,SectionNo,ExamNo)
);

CREATE TABLE ClassRoom (
  RoomNo INT NOT NULL,
  Building VARCHAR(50),
  Capacity INT,
  PRIMARY KEY(RoomNo, Building)
);

DESC ClassRoom;
DESC ConductedIn;
DESC Course;
DESC Enrolls;
DESC Exam;
DESC Section;
DESC Student;
DESC Takes	;