/*Query 1 Retrieve information (SSN, first name and last name) about students who take the course ‘Database Management Systems’.*/
SELECT DISTINCT Student.SSN,FirstName,LastName 
FROM Student JOIN Enrolls ON (Student.SSN = Enrolls.SSN) JOIN Section ON (Enrolls.CourseNo = Section.CourseNo) JOIN Course ON (Section.CourseNo = Course.CourseNo)
WHERE CourseName = "Database Management Systems";

/*Query 2 Retrieve the courses (List course name and number of sections) that have more than 2 sections. */
SELECT DISTINCT Course.CourseName, COUNT(Section.CourseNo)
FROM Course JOIN Section ON (Course.CourseNo = Section.CourseNo)
GROUP BY Section.CourseNo
HAVING COUNT(Section.CourseNo) > 2;

/*Query 3 List each course number, course name and section number which have 3 or more students in the section. */
SELECT DISTINCT Course.CourseNo,Course.CourseName,Section.SectionNo
FROM Course JOIN Section ON (Course.CourseNo = Section.CourseNo) JOIN Enrolls ON (Section.SectionNo = Enrolls.SectionNo)
GROUP BY SectionNo;

/*Query 4 Retriev		e the information (SSN, first name, and last name) of students who got Grade ‘A’ in at least 3 exams. */
SELECT DISTINCT Student.SSN,FirstName,LastName
FROM Student JOIN Takes ON (Student.SSN = Takes.SSN)
HAVING COUNT(Result = "A") > 3;

/*Query 5 Obtain information (exam number, exam date, course number and section number) about exams taking place in building ‘RVR’. Along with that get the room’s capacity and room number. */
SELECT DISTINCT Exam.ExamNo, Exam.E_DATE, Exam.CourseNo, Exam.SectionNo, ClassRoom.Capacity, ClassRoom.RoomNo
FROM Exam JOIN ConductedIn ON(Exam.CourseNo = ConductedIn.CourseNo) JOIN ClassRoom ON (ConductedIn.Building = ClassRoom.Building)
WHERE ClassRoom.Building = "RVR";

/*Query 6 Retrieve information (SSN, first name and last name) about students who are enrolled in both the course ‘CSC133’ and ‘CSC137’. ‘CSC133’ and ‘CSC137’ are both course numbers. */
SELECT DISTINCT Student.SSN, FirstName, LastName
FROM Student JOIN Enrolls ON(Student.SSN = Enrolls.SSN) 
WHERE Enrolls.CourseNo = "CSC133" 
UNION
SELECT DISTINCT Student.SSN, FirstName, LastName
FROM Student JOIN Enrolls ON(Student.SSN = Enrolls.SSN) 
WHERE Enrolls.CourseNo = "CSC137"; 

/*Query 7 Get the information (SSN, first name and last name) about students who take the course ‘Data structure and algorithms’. Also get the section number in which they have enrolled in the course, as well as the instructor of the section. */
SELECT DISTINCT Student.SSN, FirstName, LastName, Enrolls.SectionNo, Section.Instructor
FROM Student JOIN Enrolls ON(Student.SSN = Enrolls.SSN) JOIN Section ON(Enrolls.CourseNo = Section.CourseNo) JOIN Course ON(Section.CourseNo = Course.CourseNo)
WHERE CourseName = "Data Structure and Algorithms";
