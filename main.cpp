#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

void add(int added, int num, int* &heap);
void print (int added, int* heap, int index, int count);
void deleteMax(int &added, int* &heap);
void removeAll(int &added, int* &heap);

int main(){
  int* heap = new int[100];

  bool playing = true;
  int index = 1;
  int added = 0;

  while (playing == true){
    cout << "type in a command: ADD, PRINT, DELETE, QUIT, REMOVEALL" << endl;
    char command[10];
    cin >> command;

    if (strcmp(command, "ADD") == 0){
      cout << "do you want to add from file or manual. type f or m" << endl;
      char a;
      cin >> a;
      if (a == 'f'){
	// prompt for filename etc
	char file[20];
	cout << "What's the name of the file to use?" << endl;
	cin >> file;

	ifstream fin;
	fin.open(file);
	int input;
	while(fin>>input) {
	  add(added, input, heap);
	  added++;
      }
      }

      else {

      int number;
      cout << "what number do you want to add?" << endl;
      cin >> number;
      add(added, number, heap);
      added++;
      }

    }

    else if (strcmp(command, "PRINT") == 0){
      print (added, heap, 1, 0);
    }

    else if (strcmp(command, "DELETE") == 0){
      deleteMax(added, heap);
    }

    else if (strcmp(command, "REMOVEALL") == 0){
      removeAll(added, heap);
    }


    else if (strcmp(command, "QUIT") == 0){
      cout << "exiting program" << endl;
      playing = false;
    }
  }
}

/*void add(int &added, int num, int* &heap, int &index){
  heap[index] = num;
  int count = index;
  int j = floor(count/2);
  if (num > heap[j]){
    j = floor(count/2);
    swap(heap[count], heap[count / 2]);
    count = count / 2;
  }

  added++;
  index++;  // Increment the index for the next insertion
  cout << num << " has been added" << endl;
}
*/


void add(int added, int num, int* &heap) {
  
  int a = floor((added+1)/2);
  
  if (added==0) { //empty heap case
    heap[1] = num;
  }
  
  
  else if (heap[a] > num) { //no swap needed
    
    heap[added+1] = num;
  }
  else { //swap needed
    
    int currentIndex = added+1; //put it in as usual before swap
    heap[currentIndex] = num;
    int prev = floor(currentIndex/2);
    
    while(heap[prev] < heap[currentIndex] && prev > 0) { //while loop for swapping
      int p = heap[prev];
      heap[prev] = num;
      heap[currentIndex] = p;
      int x = prev;
      currentIndex = x;
      prev = floor(currentIndex/2);
      //ok swap function not working manual swapping rip
    }
  }
}


void deleteMax(int &added, int* &heap) {

  // removes the head of the tree
  
  heap[1] = heap[added];
  heap[added] = 0;
  added = added - 1;
  
  int current = 1;
  int left = heap[current*2];
  int right = heap[(current*2)+1];
  
  while (left > heap[current] || right > heap[current]) { //child is bigger than parent oh no
    
    if (left > right) {
      // left bigger than right so swap to left
      //update: swap function failing, gotta manual swap 
      int temp = heap[current];
      heap[current] = left;
      heap[current*2] = temp;
      current = current*2;
    }
    else {
      // right child bigger than left so swap to right
      int temp = heap[current];
      heap[current] = right;
      heap[(current*2)+1] = temp;
      current = (current*2)+1;
    }
    left = heap[current*2];
    right = heap[(current*2)+1];
    
  }
  //cout << "removed" << endl;
  
}
  



void print(int added, int* heap, int index, int count) {
  // this function was heavily inspired by Mr. Galbraith's code on the whiteboard

  if (((index*2)+1) < added+1) {
    print(added, heap, ((index*2)+1), (count+1));
    
  }

  for (int i = 0; i < count; i++) {
    cout << '\t' ;
  }
  cout << heap[index] << endl;
  if ((index*2) < added+1) {
    print(added, heap, (index*2), count+1);
  }
  
}



void removeAll(int &added, int* &heap) {

  int x = added; //ask galbraith why i had to add this, function was breaking if i used added in for loop
  // self explanatory function name
  
  for (int i = 0; i < x; i++) {
    deleteMax(added, heap);
  }

  cout << "tree has been cleared" << endl;
}
