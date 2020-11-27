#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <fstream>

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
void generate(int num, Student* hashTable[], int length);
void addStudent(Student* hashTable[]);
void printStudents(Student* hashTable[], int length);
void deleteStudent(Student* hashTable[], int length);

int main() {

  cout << "Welcome to Student List - Hash Table version!" << endl;
  cout << "Valid commands are \"GENERATE\", \"ADD\", \"PRINT\", \"DELETE\", and \"QUIT\"" << endl;

  Student* hashTable[100];
  for (int i = 0; i < 100; i++) {
    hashTable[i] = NULL;
  }
  
  char input[10];
  //as long as the user doesn't say QUIT, keep asking for commands
  while (strcmp(input, "QUIT") != 0) {
    cout << ">> ";
    cin >> input;
    if (strcmp(input, "GENERATE") == 0) {
      int num;
      cout << "How many students to generate? ";
      cin >> num;
      generate(num, hashTable, sizeof(hashTable) / sizeof(hashTable[0]));
    } else if (strcmp(input, "ADD") == 0) {
      addStudent(hashTable);
    } else if (strcmp(input, "PRINT") == 0) {
      printStudents(hashTable, sizeof(hashTable) / sizeof(hashTable[0]));
    } else if (strcmp(input, "DELETE") == 0) {
      deleteStudent(hashTable, sizeof(hashTable) / sizeof(hashTable[0]));
    } else if (strcmp(input, "QUIT") != 0) { //anything else (besides quit) wil\
l be invalid
      cout << "Invalid command." << endl;
    }
  }
  cout << "Goodbye!" << endl;
}

//generates a set of random students
void generate(int numStudents, Student* hashTable[], int length) {
  Student* students[20]; //will hold the 20 random names
  for (int i = 0; i < 20; i++) {
    students[i] = new Student;
  }
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

  int currentID = 1;
  for (int i = 0; i < numStudents; i++) {
    float randomGPA = static_cast<float> (rand()) / static_cast<float> (RAND_MAX/4);
    int randomFirst = rand() % total;
    int randomLast = rand() % total;
    hashTable[currentID % length] = new Student;
    strcpy(hashTable[currentID % length]->first, students[randomFirst]->first);
    strcpy(hashTable[currentID % length]->last, students[randomLast]->last);
    hashTable[currentID % length]->id = currentID;
    hashTable[currentID % length]->gpa = randomGPA;
    currentID++;
  } 
}

//add a new student to the vector, prompting for the necesary components
void addStudent(Student* hashTable[]) {
  Student* newStudent = new Student;
  cout << "First name: ";
  cin >> newStudent->first;
  cout << "Last name: ";
  cin >> newStudent->last;
  cout << "ID: ";
  cin >> newStudent->id;
  cout << "GPA: ";
  cin >> newStudent->gpa;

  if (!hashTable[newStudent->id % 100]) {
    hashTable[newStudent->id % 100] = newStudent;
  } else { //TODO: move current definition out?
    Student* current = hashTable[newStudent->id % 100];
    int length = 1;
    while (current->next) {
      current = current->next;
      length++;
    }
    current->next = newStudent;
  }
  cout << "Student added." << endl;
}

//print out all the information for each student, or "[No students]" if no stud\
ents
void printStudents(Student* hashTable[], int length) {
  for (int i = 0; i < length; i++) {
    Student* current = hashTable[i];
    if (current) {
      cout << current->first << " " << current->last << ", " << current->id << ", " << fixed << setprecision(2) << current->gpa << endl;
      while (current->next) {
	current = current->next;
	cout << current->first << " " << current->last << ", " << current->id << ", " << fixed << setprecision(2) << current->gpa << endl;
      }
    }
  }
}

//deletes a student given their ID
void deleteStudent(Student* &hashTable[], int length) {
  int givenID;
  cout << "ID of student: ";
  cin >> givenID;
  
  for (int i = 0; i < length; i++) {
    if (hashTable[i] && hashTable[i]->id == givenID) {
      hashTable[i] = NULL;
      break;
    }
  }
}

//rehashes the function with double the size of the array
void rehash(Student* &hashTable[], int length) {
  Student* newTable[length * 2];
  for (int i = 0; i < length * 2; i++) {
    newTable[i] = NULL;
  }

  for (int i = 0; i < length; i++) {
    Student* current = hashTable[i];
    
  }
}
