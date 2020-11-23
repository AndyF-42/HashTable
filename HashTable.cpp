#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

//Student struct - holds first and last name, id, and gpa
struct Student {
  char first[20];
  char last[20];
  int id;
  float gpa;
};

//Node struct - holds pointer to next node and student
struct Node {
  Node* next;
  Student student;
};


//function declaration - note that add and delete pass the vector by reference,\
 to make permanent changes
void addStudent(Node (&hashTable)[100]);
void printStudents(Node hashTable[100]);
void deleteStudent(Node (&hashTable)[100]);

int main() {

  cout << "Welcome to Student List - Hash Table version!" << endl;
  cout << "Valid commands are \"ADD\", \"PRINT\", \"DELETE\", and \"QUIT\"" << endl;
  
  Node hashTable[100];

  char input[10];
  //as long as the user doesn't say QUIT, keep asking for commands
  while (strcmp(input, "QUIT") != 0) {
    cout << ">> ";
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      addStudent(hashTable);
    } else if (strcmp(input, "PRINT") == 0) {
      printStudents(hashTable);
    } else if (strcmp(input, "DELETE") == 0) {
      deleteStudent(hashTable);
    } else if (strcmp(input, "HELP") == 0) { //HELP tells them valid commands
      cout << "Valid commands: ADD, PRINT, DELETE, HELP, QUIT" << endl;
    } else if (strcmp(input, "QUIT") != 0) { //anything else (besides quit) wil\
l be invalid
      cout << "Invalid command. Type HELP for list of valid commands." << endl;
    }
  }
  cout << "Goodbye!" << endl;
}

//add a new student to the vector, prompting for the necesary components
void addStudent(Node (&hashTable)[100]) {
  Student newStudent;
  cout << "First name: ";
  cin >> newStudent.first;
  cout << "Last name: ";
  cin >> newStudent.last;
  cout << "ID: ";
  cin >> newStudent.id;
  cout << "GPA: ";
  cin >> newStudent.gpa;

  hashTable[id % 100].student = newStudent;
  cout << "Student added." << endl;
}

//print out all the information for each student, or "[No students]" if no stud\
ents
void printStudents(Node hashTable[100]) {
  for (int i = 0; i < vPtr->size(); i++) {
    Student* s = vPtr->at(i);
    cout << s->first << " " << s->last << ", " << s->id << ", " << fixed << set\
precision(2) << s->gpa << endl;
  }
  if (vPtr->size() == 0) {
    cout << "[No students]" << endl;
  }
}

//deletes a student given their ID
void deleteStudent(Node (&hashTable)[100]) {
  int toDelete;
  cout << "ID: ";
  cin >> toDelete;

  //search through the vector to find the matching ID
  for (int i = 0; i < vPtr->size(); i++) {
    if (vPtr->at(i)->id == toDelete) {
      vPtr->erase(vPtr->begin() + i);
      cout << "Student deleted." << endl;
      return;
    }
  }
  cout << "Student not found." << endl; //if it went through all the students w\
/out deleting, say not found
}
