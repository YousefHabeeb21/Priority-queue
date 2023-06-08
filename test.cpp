#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <iostream>
#include <map>


// test for size and tostring 
TEST(priorityqueuetesting1, one) {
  
    map <int, vector<int> > compare;
    priorityqueue<int> numbers;
    int count = 8;
    int values[] = {1,12,3,4,9,5,6,7};
    int priorities[] ={1,2,3,4,5,1,11,3};
  
    for(int i = 0; i< count; i++){
     numbers.enqueue(values[i],priorities[i]);
    }
    EXPECT_EQ(count,numbers.Size());
      for(int i = 0; i<count; i++){
       compare[priorities[i]].push_back(values[i]);
      }

    stringstream ss;
    for(auto i: compare){
      
      int priority = i.first;
      
      vector<int>value = i.second;
      for (size_t p = 0; p < value.size(); p++){
        ss << priority << " value: " << value[p] << endl;
      }

    }

  EXPECT_EQ(numbers.toString(), ss.str());

}


// test for size and tostring 
TEST(priorityqueuetesting2, two) {
    map<int, vector<string> > compare;
    priorityqueue<string> numbers;
  
    int num = 8;
    string values[] = {"bob", "alice", "ben", "gerald", "rick", "hunter", "nancy", "brad"};
    int priorities[] ={1,2,3,4,5,1,2,3};
  
    for(int i = 0; i< num; i++){
     numbers.enqueue(values[i],priorities[i]);
    }
  
    EXPECT_EQ(num,numbers.Size());
    for(int i = 0; i< num; i++){
     compare[priorities[i]].push_back(values[i]);
    }

    stringstream ss;
    for(auto i: compare){
      int priority = i.first;
      vector<string> value = i.second;
      for (size_t p = 0; p < value.size(); p++){
        ss << priority << " value: " << value[p] << endl;
      }

    }

  EXPECT_EQ(numbers.toString(), ss.str());

}


// test for destructor and size
TEST(priorityqueuetesting3, three) {
    map<int, vector<string> > compare;
    priorityqueue<string> numbers;
  
    int num = 8;
    string values[] = {"bob", "alice", "ben", "gerald", "rick", "hunter", "nancy", "brad"};
    int priorities[] ={1,2,3,4,5,1,2,3};
  
    for(int i = 0; i< num; i++){
     numbers.enqueue(values[i],priorities[i]);
    }

    numbers.~priorityqueue();

    num = 0;
  
    EXPECT_EQ(num,numbers.Size());
    for(int i = 0; i< num; i++){
     compare[priorities[i]].push_back(values[i]);
    }
}


// test for dequeue and peek
TEST(priorityqueuetesting4, four) {
    map<int, vector<string> > compare;
    priorityqueue<string> vals;
  
    int num = 8;
    string values[] = {"bob", "alice", "ben", "gerald", "rick", "hunter", "nancy", "brad"};
    int priorities[] ={1,2,3,4,5,8,2,9};
  
    for(int i = 0; i< num; i++){
     vals.enqueue(values[i],priorities[i]);
    }

    vals.dequeue();
    EXPECT_EQ(vals.dequeue(),values[0]);
    
  
    vals.peek();
  
    EXPECT_EQ(vals.peek(),values[1]);

}

//testing for dequeue and peek but peek should have no value
TEST(priorityqueuetesting5, five) {
    map<int, vector<string> > compare;
    priorityqueue<string> vals;
  
    int num = 8;
    string values[] = {"bob", "alice", "ben", "gerald", "rick", "hunter", "nancy", "brad"};
    int priorities[] ={1,2,3,4,5,8,2,9};
  
    for(int i = 0; i< num; i++){
     vals.enqueue(values[i],priorities[i]);
    }

    for(int i = 0; i< num; i++){
     vals.dequeue(values[i],priorities[i]);
      num--;
    }

    EXPECT_EQ(nums,numbers.Size());
  
    
  
    vals.peek();
  
    EXPECT_EQ(vals.peek(),nullptr);

}


//testing for deque and tostring
TEST(priorityqueuetesting6, six) {
    map<int, vector<string> > compare;
    priorityqueue<string> vals;
  
    int num = 8;
    string values[] = {"bob", "alice", "ben", "gerald", "rick", "hunter", "nancy", "brad"};
    int priorities[] ={1,2,3,4,5,1,9,8};
  
    for(int i = 0; i< num; i++){
     vals.enqueue(values[i],priorities[i]);
    }

    for(int i = 0; i< 3; i++){
     vals.dequeue(values[i],priorities[i]);
      count--;
    }

  for(int i = 0; i<count; i++){
    compare[priorities[i]].push_back(values[i]);
  }
     stringstream ss;
    for(auto i: compare){
      int priority = i.first;
      vector<string> value = i.second;
      for (size_t p = 0; p < value.size(); p++){
        ss << priority << " value: " << value[p] << endl;
      }

    }

  EXPECT_EQ(numbers.toString(), ss.str());

}






//testing for deque and tostring
TEST(priorityqueuetesting7, seven) {
    map<int, vector<string> > compare;
    priorityqueue<string> vals;
  
    int num = 8;
    string values[] = {"bob", "alice", "ben", "gerald", "rick", "hunter", "nancy", "brad"};
    int priorities[] ={1,2,3,4,5,1,9,8};
  
    for(int i = 0; i< num; i++){
     vals.enqueue(values[i],priorities[i]);
    }

    for(int i = 0; i< 3; i++){
     vals.dequeue(values[i],priorities[i]);
      count--;
    }

  for(int i = 0; i<count; i++){
    compare[priorities[i]].push_back(values[i]);
  }
     stringstream ss;
    for(auto i: compare){
      int priority = i.first;
      vector<string> value = i.second;
      for (size_t p = 0; p < value.size(); p++){
        ss << priority << " value: " << value[p] << endl;
      }

    }

  EXPECT_EQ(numbers.toString(), ss.str());

}


//testing equal operator with size
TEST(priorityqueuetesting8, eight){
   priorityqueue<int> original;
   priorityqueue<int> copy;
   int values[100];
   int priorities[100];
   int x = 0;
   int y = 0;
    
   for(int i = 0 ; i< 100; i++){
    x = rand() % 100;
    y = rand() % 100; 
    priorities[i] = x;
    values[i] = y;
   }
   for(int i = 0 ; i<100; i++){
    original.enqueue(values[i],priorities[i]);
   }
  
   string val = "";
   val = original.toString();
   copy = original;
  
   string copy2 = "";
   copy2 = copy.toString();
    
  
   EXPECT_EQ(val,copy2);
   EXPECT_EQ(100,copy.Size());
}



// testing equal operator


// TO DO: write lots of tests here. 
int main(){
  
    priorityqueue<string> p; 

    p.enqueue("bobby", 8); 
    p.enqueue("musteeef", 11);
    p.enqueue("aj", 2);     
    p.enqueue("Ben", 8);      
    p.enqueue("adnan", 5);   
    p.enqueue("alice", 3);            
    p.enqueue("ali", 4);               
    p.enqueue("nancy", 2);          
    p.enqueue("sohail", 2);               
    p.enqueue("iftequar", 7);   
   
    string val;       
    int o;  
          
    bool check;    
    cout <<"the size is "<< p.Size()<< endl;    
    string x = p.toString();         
    cout << x <<endl;      
       
    // p.~priorityqueue();           
    // x = p.toString();                    
      
    val = p.peek();        
    cout<<val<<endl;           
             
    p.begin();        
              
             
     val = p.dequeue(); 
  cout<<val<<endl;
     val = p.dequeue(); 
  cout<<val<<endl;
     val = p.dequeue();  
  cout<<val<<endl;
     val = p.dequeue();   
  cout<<val<<endl;
     val = p.dequeue();    
  cout<<val<<endl;
     val = p.dequeue(); 
  cout<<val<<endl;
     val = p.dequeue();  
  cout<<val<<endl;
     val = p.dequeue();  
  cout<<val<<endl;
     val = p.dequeue();  
  cout<<val<<endl;
     val = p.dequeue();
  cout<<val<<endl;
     val = p.dequeue();
  cout<<val<<endl;
      

         
  
    
   // while (p.next(val,o)) { 
   //   cout <<endl<<  o << " value: " << val << endl;  
   // }    
   // cout << o << " value: " << val << endl; 
    
      

    return 0;   
}                  