#include <iostream>
using namespace std;
#include <string>

class Node {
    public:
        int data;
        Node* previous;
        Node* next;
    
        Node(int in_data, Node* in_previous, Node* in_next){
            data = in_data;
            previous = in_previous;
            next = in_next;
        };
};

class Stack {
    private:
        Node *head = NULL;
        Node *tail = NULL;
        int size = 0;
        
    public:    
        int isEmpty()
        {
            return size == 0;
        }
        
        int peek_head(void){
            int return_val = -1;
            
            if(size!=0){
                cout<<"peak_head: "<<head->data<<endl;
                return_val = head->data;
            }
            else{
                cout<<"peek_head: stack empty"<<endl;
            }
            return return_val;
        }
        
        int peek_tail(void){
            int return_val = -1;
            
            if(size!=0){
                cout<<"peak_tail: "<<tail->data<<endl;
                return_val = tail->data;
            }
            else{
                cout<<"peek_tail: stack empty"<<endl;
            }
            return return_val;
        }
        
        void head_memory_location(){
            if(head){
                cout<<"head_memory_location: "<<head<<endl;
            }
            else{
                cout<<"head NULL"<<endl;
            }
        }
        
        void tail_memory_location(){
            if(tail){
                cout<<"tail_memory_location: "<<tail<<endl;
            }
            else{
                cout<<"tail NULL"<<endl;
            }
        }
    
        void display(void){
            Node* pNode;
            pNode = tail;
            
            int idx = 0;
            
            cout<<"display: ";
            while (pNode){
                cout<<"["<<idx<<"]="<<pNode->data<<" ";
                pNode = pNode->next;
                idx++;
            }
            cout<<endl;
        }

        void display_reverse(void){
            Node* pNode;
            pNode = head;
            
            int idx = size-1;
            
            cout<<"display_reverse: ";
            while (pNode){
                cout<<"["<<idx<<"]="<<pNode->data<<" ";
                pNode = pNode->previous;
                idx--;
            }
            cout<<endl;
        }
                
        void display_memory_locations(){
            Node* pNode;
            pNode = tail;
            cout<<"display_memory_locations: ";
            while (pNode){
                cout<<pNode<<" ";
                pNode = pNode->next;
            }
            cout<<endl;
        }
        
        void display_memory_locations_reverse(){
            Node* pNode;
            pNode = head;
            cout<<"display_memory_locations_reverse: ";
            while (pNode){
                cout<<pNode<<" ";
                pNode = pNode->previous;
            }
            cout<<endl;
        }
        
        void push(int data){
            
            cout<<"push("<<data<<")"<<endl;
            if (size==0){
                Node* new_node = new Node(data, NULL, NULL);
                tail = new_node;
                head = new_node;
            }
            else{
                Node* new_node = new Node(data, head, NULL);
                head->next = new_node;
                head = new_node;                
            }
            
            size += 1;
        }
        
        bool insert_at(int idx, int data){
            bool inserted = false;
            Node* current_node = tail;
            
            cout<<"insert_at("<<idx<<","<<data<<");"<<endl;
            
            //make sure idx is equal or greater than 0
            if(idx>=0){
                //insert to empty stack, use the standard push() function which handles empty stack case
                if(size==0){
                    cout<<"insert_at(): 'size==0'"<<endl;
                    push(data);
                    inserted = true;
                }
                //stack is non-empty. 
                else{
                    //insert idx is greater than size, push to the head as standard LIFO behavior using push()
                    if(idx >= size){
                        cout<<"insert_at(): 'idx >= size'"<<endl;
                        push(data);
                        inserted = true;
                    }
                    //insert into the middle
                    else if(idx > 0){
                        cout<<"insert_at(): idx > 0"<<endl;
                        for(int i = 0; i < idx;i++){
                            current_node = current_node->next;
                        }
                        
                        Node* new_node = new Node(data, current_node->previous, current_node);
                        current_node->previous->next=new_node;
                        current_node->previous = new_node;
                        size += 1;
                        inserted = true;
                    }
                    //idx is 0
                    else{
                        cout<<"insert_at(): 'idx==0'"<<endl;
                        Node* new_node = new Node(data, NULL, tail);
                        tail->previous = new_node;
                        tail = new_node;
                        size += 1;
                        inserted = true;
                    }
                }
            }
            return inserted;
        }
    
        void pop(void){
            Node* temp;
        
            if(size == 1){
                temp = head;
                head = NULL;
                tail = NULL;
                free(temp);           
                size -=1;
            }
            else if(!isEmpty()){
                temp = head;
                head = temp->previous;
                head->next = NULL;    
                free(temp);           
                size -=1;
            }
        }

        void empty_stack(){
            while(!isEmpty()){
                pop();
            }
        }
        
        void show_stuff(){
            peek_head();  
            peek_tail();
            tail_memory_location();
            head_memory_location();
            display();
            display_reverse();
        }
};

void test_standard(){
    Stack mystack;
    
    mystack.peek_head();  
    mystack.peek_tail();
    mystack.tail_memory_location();
    mystack.head_memory_location();
    mystack.display();
    mystack.display_reverse();
    
    for(int i = 1; i <= 5; i++){
        mystack.push(i); 
        
        mystack.peek_head();
        mystack.peek_tail();
        
        mystack.tail_memory_location();
        mystack.head_memory_location();
        mystack.display();
        mystack.display_reverse();
    }
    
    mystack.display_memory_locations();
    mystack.display_memory_locations_reverse();    
    mystack.display();
    mystack.display_reverse();
    
    while(!mystack.isEmpty()){
        mystack.peek_head();
        mystack.peek_tail();
        
        mystack.tail_memory_location();
        mystack.head_memory_location();
            
        mystack.display();
        mystack.display_reverse();
        mystack.pop();
    }   
    
    mystack.peek_head();
    mystack.peek_tail();
        
    mystack.tail_memory_location();
    mystack.head_memory_location();
    mystack.display();
    mystack.display_reverse();
    
    //try to pop one more off the stack even though it's already empty
    mystack.pop();   
    
    cout<<endl;
}

void test_insert_at(){
    Stack mystack;
    
    cout<<"========== insert_at to empty at 0 idx=========="<<endl;
    mystack.show_stuff();  
    mystack.insert_at(0,1);
    mystack.show_stuff();   
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;
    
    cout<<"========== insert_at to empty at non-0 idx=========="<<endl;
    mystack.show_stuff();  
    mystack.insert_at(3,1);
    mystack.show_stuff();   
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;
    
    cout<<"========== insert_at to non-empty at end =========="<<endl;
    mystack.push(2);
    mystack.push(4);
    
    mystack.show_stuff();
    
    mystack.insert_at(2,5);
    
    mystack.show_stuff();
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;
    
    cout<<"========== insert_at to non-empty at greater than end =========="<<endl;
    mystack.push(2);
    mystack.push(4);
    
    mystack.show_stuff();
    
    mystack.insert_at(5,5);
    
    mystack.show_stuff();
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;
    
    cout<<"========== insert_at to non-empty at middle =========="<<endl;
    mystack.push(2);
    mystack.push(4);
    
    mystack.show_stuff();
    
    mystack.insert_at(1,3);
    
    mystack.show_stuff();
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;
    
    cout<<"========== insert_at to non-empty at idx-0 =========="<<endl;
    mystack.push(2);
    mystack.push(4);
    
    mystack.show_stuff();
    
    mystack.insert_at(0,1);
    
    mystack.show_stuff();
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;
    
    cout<<"========== push after insert_at =========="<<endl;
    mystack.show_stuff();  
    mystack.insert_at(3,2);
    mystack.show_stuff();   
    mystack.insert_at(0,1);
    mystack.show_stuff();
    mystack.push(3);
    mystack.show_stuff();
    mystack.empty_stack();
    mystack.show_stuff();
    
    cout<<"========== insert_at negative index =========="<<endl;
    mystack.show_stuff();  
    mystack.insert_at(-1,1);
    mystack.show_stuff();   
    mystack.empty_stack();
    mystack.show_stuff();
    cout<<endl;    
}
    
int main ()
{   
    test_standard();
    test_insert_at();
    
    cout<<"goodbye"<<endl;

  return 0;
}