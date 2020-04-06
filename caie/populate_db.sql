use test;

INSERT INTO Student 
VALUES ('123456789', 'Sam', 'Johnson', 'Apple', 'Sacramento', 'CA', '95819');

INSERT INTO Student 
VALUES ('987654321', 'James', 'Rogers', '65th', 'Elk Grove', 'CA', '95624');

INSERT INTO Student 
VALUES ('023456789', 'Kyle', 'Corver', 'Mayfield', 'Sacramento', 'CA', '95822');

INSERT INTO Student 
VALUES ('111111111', 'Lebron', 'James', 'WhiteRose', 'Elk Grove', 'CA', '95622');

INSERT INTO Student 
VALUES ('222222222', 'Scottie', 'Pippin', 'March', 'Stockton', 'CA', '95712');



INSERT INTO Course 
VALUES ('CSC134', 'Database Management Systems', 'CSC');

INSERT INTO Course 
VALUES ('CSC130', 'Data Structure and Algorithms', 'CSC');

INSERT INTO Course 
VALUES ('CSC133', 'Object-Oriented Computer Graphics', 'CSC');

INSERT INTO Course 
VALUES ('CSC137', 'Computer Organization', 'CSC');

INSERT INTO Course 
VALUES ('CSC190', 'Senior Project', 'CSC');


INSERT INTO Section
VALUES ('CSC134', '1', 'Sun');

INSERT INTO Section
VALUES ('CSC134', '2', 'Jin');

INSERT INTO Section
VALUES ('CSC134', '3', 'Jin');

INSERT INTO Section
VALUES ('CSC133', '1', 'Ozcelik');

INSERT INTO Section
VALUES ('CSC137', '1', 'Faroughi');

INSERT INTO Section
VALUES ('CSC190', '1', 'Buckley');

INSERT INTO Section
VALUES ('CSC130', '1', 'Cheng');


INSERT INTO Enrolls
VALUES ('023456789', '1', 'CSC134');

INSERT INTO Enrolls
VALUES ('123456789', '1', 'CSC134');

INSERT INTO Enrolls
VALUES ('987654321', '1', 'CSC134');

INSERT INTO Enrolls
VALUES ('023456789', '1', 'CSC133');

INSERT INTO Enrolls
VALUES ('023456789', '1', 'CSC137');

INSERT INTO Enrolls
VALUES ('987654321', '1', 'CSC130');



INSERT INTO Exam
VALUES ('CSC134', '1', '1', '4/20/2019', '1000');

INSERT INTO Exam
VALUES ('CSC134', '1', '2', '5/10/2019', '1000');

INSERT INTO Exam
VALUES ('CSC134', '2', '1', '1/5/2019', '1000');

INSERT INTO Exam
VALUES ('CSC137', '2', '1', '2/5/2019', '1230');

INSERT INTO Exam
VALUES ('CSC133', '1', '1', '3/10/2019', '330');


INSERT INTO ConductedIn
VALUES ('1013', 'RVR', 'CSC134', '1', '1');

INSERT INTO ConductedIn
VALUES ('1013', 'RVR', 'CSC137', '2', '1');

INSERT INTO ConductedIn
VALUES ('2000', 'RVR', 'CSC134', '2', '1');

INSERT INTO ConductedIn
VALUES ('3010', 'RVR', 'CSC137', '1', '2');

INSERT INTO ConductedIn
VALUES ('3010', 'RVR', 'CSC133', '1', '1');


INSERT INTO ClassRoom
VALUES ('1013', 'RVR', '40');

INSERT INTO ClassRoom
VALUES ('2000', 'RVR', '40');

INSERT INTO ClassRoom
VALUES ('3010', 'RVR', '50');


INSERT INTO Takes
VALUES ('023456789', 'CSC134', '1', '1', 'A');
	
INSERT INTO Takes
VALUES ('123456789', 'CSC134', '1', '1', 'C');

INSERT INTO Takes
VALUES ('023456789', 'CSC137', '1', '1', 'A');

INSERT INTO Takes
VALUES ('023456789', 'CSC133', '1', '1', 'A');

INSERT INTO Takes
VALUES ('023456789', 'CSC137', '2', '1', 'A');

SELECT * FROM ClassRoom;
SELECT * FROM ConductedIn;
SELECT * FROM Course;
SELECT * FROM Enrolls;
SELECT * FROM Exam;
SELECT * FROM Section;
SELECT * FROM Student;
SELECT * FROM Takes;





