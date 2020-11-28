#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

//Student struct - holds first and last name, id, and gpa
struct Student {
  char first[20];
  char last[20];
  int id;
  float gpa;
  Student* next = NULL;
};

//function declaration - note that add and delete pass by reference, to make permanent changes
void generate(int num, Student** &hashTable, int &length);
void addStudent(Student* newStudent, Student** &hashTable, int &length);
void printStudents(Student* hashTable[], int length);
void deleteStudent(Student** &hashTable, int &length);
void rehash(Student** &hashTable, int &length);

int main() {

  cout << "Welcome to Student List - Hash Table version!" << endl;
  cout << "Valid commands are \"GENERATE\", \"ADD\", \"PRINT\", \"DELETE\", and \"QUIT\"" << endl;

  //create hashTable of size 100
  int size = 100;
  Student** hashTable = new Student*[size];
  for (int i = 0; i < size; i++) {
    hashTable[i] = NULL;
  }
  
  char input[10];
  //as long as the user doesn't say QUIT, keep asking for commands
  while (strcmp(input, "QUIT") != 0) {
    cout << ">> ";
    cin >> input;
    if (strcmp(input, "GENERATE") == 0) { //generate given number of students 
      int num;
      cout << "How many students to generate? ";
      cin >> num;
      generate(num, hashTable, size);
    } else if (strcmp(input, "ADD") == 0) { //add student with given info
      Student* newStudent = new Student;
      cout << "First name: ";
      cin >> newStudent->first;
      cout << "Last name: ";
      cin >> newStudent->last;
      cout << "ID: ";
      cin >> newStudent->id;
      cout << "GPA: ";
      cin >> newStudent->gpa;
      addStudent(newStudent, hashTable, size);
      cout << "Student added." << endl;
    } else if (strcmp(input, "PRINT") == 0) { //print students
      printStudents(hashTable, size);
    } else if (strcmp(input, "DELETE") == 0) { //delete student
      deleteStudent(hashTable, size);
    } else if (strcmp(input, "QUIT") != 0) { //anything else (besides quit) wil\
l be invalid
      cout << "Invalid command." << endl;
    }
  }
  cout << "Goodbye!" << endl;
}

//generates a set of random students
void generate(int numStudents, Student** &hashTable, int &length) {
  Student* students[20]; //will hold the 20 random names
  for (int i = 0; i < 20; i++) {
    students[i] = new Student;
  }
  //open and read files
  ifstream firstNames;
  ifstream lastNames;
  srand(time(0));
  
  firstNames.open("firstNames.txt");
  lastNames.open("lastNames.txt");
  if (!firstNames) {
    cout << "Could not open firstNames.txt" << endl;
    exit(1);
  }
  if (!lastNames) {
    cout << "Could not open lastNames.txt" << endl;
    exit(1);
  }

  //put names into list of students (that only has the names)
  char name[20];
  int total = 0;
  while (firstNames >> name) {
    strcpy(students[total]->first, name);
    total += 1;
  }
  total = 0;
  while (lastNames >> name) {
    strcpy(students[total]->last, name);
    total += 1;
  }

  //start at id 1, create students with random GPA (0.00 to 4.00)
  //and random first and last names (from list of students)
  int currentID = 1;
  for (int i = 0; i < numStudents; i++) {
    float randomGPA = static_cast<float> (rand()) / static_cast<float> (RAND_MAX/4);
    int randomFirst = rand() % total;
    int randomLast = rand() % total;

    //make the new student and add with addStudent function
    Student* newStudent = new Student;
    strcpy(newStudent->first, students[randomFirst]->first);
    strcpy(newStudent->last, students[randomLast]->last);
    newStudent->id = currentID;
    newStudent->gpa = randomGPA;
    
    addStudent(newStudent, hashTable, length);
    
    currentID++;
  }
  cout << "Students added." << endl;
}

//add a new student to the vector, prompting for the necesary components
void addStudent(Student* newStudent, Student** &hashTable, int &length) {
  //if slot is empty, just add
  if (!hashTable[newStudent->id % length]) {
    hashTable[newStudent->id % length] = newStudent;
  } else { //slot is not empty, must chain with linked lists
    Student* current = hashTable[newStudent->id % length];
    int chainLength = 1;
    while (current->next) { //get to end of linked list
      current = current->next;
      chainLength++;
    }
    current->next = newStudent; //add to end of list
    if (chainLength == 3) { //rehash if more than 3 students in this slot
      cout << "More than 3 students in a slot. ";
      rehash(hashTable, length);
    }
  }

  //rehash if over half full
  int slotsFull = 0;
  for (int i = 0; i < length; i++) {
    if (hashTable[i]) {
      slotsFull++;
    }
  }
  if (slotsFull > (length / 2)) {
    cout << "Table over half full. ";
    rehash(hashTable, length);
  }
}

//print out all the information for each student, or "[No students]" if no stud\
ents
void printStudents(Student* hashTable[], int length) {
  for (int i = 0; i < length; i++) {
    Student* current = hashTable[i];
    if (current) { //if not null, print the data
      cout << i << ": " << current->first << " " << current->last << ", " << current->id << ", " << fixed << setprecision(2) << current->gpa << endl;
      while (current->next) { //if a linked list, print all the linked pieces
        current = current->next;
	for (int j = 0; j < floor(log10(i)); j++) { //keep chained pieces lined up
	  cout << " "; 
	}
	cout << "   " << current->first << " " << current->last << ", " << current->id << ", " << fixed << setprecision(2) << current->gpa << endl;
      }
    }
  }
  cout << "Size of hash table: " << length << endl;
}

//deletes a student given their ID
void deleteStudent(Student** &hashTable, int &length) {
  //receive an ID to delete
  int givenID;
  cout << "ID of student: ";
  cin >> givenID;

  //go through table
  bool flag = false;
  for (int i = 0; i < length; i++) {
    Student* current = hashTable[i];
    //if not null and id matches, delete and set to whatever was next (either NULL or chained students)
    if (current && current->id == givenID) {
      Student* temp = current->next;
      delete current;
      hashTable[i] = temp;
      break;
    }
    //check all the chained students, too
    while (current && current->next) {
      //if the next id in chain matches, set next to the next next (NULL is fine), and delete the original next
      if (current->next->id == givenID) {
        Student* temp = current->next;
	current->next = current->next->next;
	delete temp;
	flag = true; //break out of outer for loop, too
	break;
      }
      current = current->next;
    }
    if (flag) {
      break;
    }
  }
}

//rehashes the function with double the size of the array
void rehash(Student** &hashTable, int &length) {
  cout << "Rehashing..." << endl;
  //double length, create a new table twice as big
  length *= 2;
  Student** newTable = new Student*[length];
  for (int i = 0; i < length; i++) {
    newTable[i] = NULL;
  }

  //for every element in the old array...
  for (int i = 0; i < length / 2; i++) {    
    if (hashTable[i]) { //if it is not NULL
      //create a new student that is a new copy of the original
      Student* original = new Student;
      strcpy(original->first, hashTable[i]->first);
      strcpy(original->last, hashTable[i]->last);
      original->id = hashTable[i]->id;
      original->gpa = hashTable[i]->gpa;
      original->next = hashTable[i]->next;

      //add the student, set next to NULL
      addStudent(hashTable[i], newTable, length);
      newTable[original->id % length]->next = NULL;
      while (original->next) { //for everything chained to the original
	//move to the next one, make a copy with next as NULL, and add it
	original = original->next;
	Student* current = new Student;
	strcpy(current->first, original->first);
        strcpy(current->last, original->last);
        current->id = original->id;
        current->gpa = original->gpa;
        current->next = NULL;
        
	addStudent(current, newTable, length);
      }
    }
  }
 
  hashTable = newTable;
}
