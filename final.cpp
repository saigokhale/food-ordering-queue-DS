/******************************************************************************

CAFETERIA MANAGEMENT SYSTEM

Group:
(2331, C22019221333, Grishma Deshmukh)
(2346, C22019221348, Sai Gokhale)
(2353 ,C22019221355, Maitrayee Joshi)
(2354 , C22019221356 , Rucha Joshi)


*******************************************************************************/
#include<iostream>
using namespace std;

//Order Node
class Node{
    public:
    int index;      // order number
    int order[3];  //max item limit =3
    float total;  //bill of the order
    Node *next;
    
    Node() {
        index=1;
        order[0]=0;
        order[1]=0;
        order[2]=0;
        next = NULL;
        total= 0.0;
    }
};

class Queue{
    Node *front, *rear;
    public:
    Queue(){
        front=NULL;
        rear=NULL;
    }
    void placeOrder(int idx);       //enqueue
    void collect_order();           //dequeue
    void deleteOrder(int n);        // delete from a node
    int isempty();                  // checks if queue is empty
    void display();                 //displays the queue
    void display_cur(Node *temp);   //displays passed node
    void calc_total(Node *temp);    //Calculates bill total of passed node
    bool check_ord(int on);         //Checks if order exists
    void new_total(Node *temp, int ino); // calculate bill after deletion of an item
};


int Queue::isempty(){
 if(front==NULL && rear==NULL){ return 1; }
 else{ return 0; }
}

void Queue::calc_total(Node *temp){
    Node *ptr = new Node();
    ptr=temp;
    float orderTotal=0.0;
    for(int i=0; i<=3; i++){
        if(ptr->order[i]==0){  
            orderTotal+=0;
        }
        else if(ptr->order[i]<4 ){
            orderTotal+=150;
        }
        else if(ptr->order[i]>3 && ptr->order[i]<8){    
            orderTotal+=20;
        }
    }
    ptr->total= orderTotal;
}

// Total after refund due to item cancellation
void Queue::new_total(Node *temp, int ino){
    Node *ptr = new Node();
    ptr=temp;
    float new_total=0.0;
    cout<<"Only 80% of total will be returned"<<endl;
    for(int i=0; i<=3; i++){
        if(ino<4){
            new_total= ptr->total - (120); //150*0.8=120
        }
        else{
            new_total= ptr->total - (16); //20*0.8=16
        }
    }
    ptr->total= new_total;
}

//enqueue
void Queue::placeOrder(int idx){
    int count=0;
    char choice='y';
    Node *temp=new Node();
    cout<<"Place Your Order (Maximum 3 orders)"<<endl;
    
    while(choice=='y' && count<3){
        cout<<"Enter item number: ";
        cin>>temp->order[count];
        
        //invalid item number
        if(temp->order[count]>7 || temp->order[count]==0 ){
            cout<<"Invalid choice"<<endl;
            goto lb;
        }
        
        count++;
        
        if (isempty()==1){
            front = temp;
            rear = temp; 
        rear->next=NULL;
        }
        else{
            rear->next=temp;
            rear=temp;
            rear->next=NULL;
        }
        
        lb:
          
        // Max limit reached
        if(count==3){
            choice='n';
            cout<<"\nYou've reached maximum order limit"<<endl;
        }
        
        else{
            cout<<"Do you want to order more?(y/n): ";
            cin>>choice;
        }
    }
    temp->index=idx;
    calc_total(temp);  
    
    cout<<"Order placed successfully!!!"<<endl;
    display_cur(temp);
}

//dequeue
void Queue::collect_order(){
    int ord_n;
    cout<<"Enter your order number: ";
    cin>>ord_n;
    
    //Order doesn't exist
    if(check_ord(ord_n)==false){
        cout<<"Order doesn't exist :/";
    }
    
    //Order isn't ready
    else if(front->index!=ord_n){
        cout<<"Your order Is not ready :("<<endl;
    }
    
    //Order is ready
    else{
        float cash;
       Node *temp=NULL;
        cout<<"Your Reciept:";
        display_cur(front);
        
        //cash payment
        cout<<"***BILL PAYMENT***"<<endl;
        cout<<"Your total bill is: Rs. "<< front->total <<endl;
        pay:
            
        cout<<"\nEnter cash payment amount: Rs. ";
        cin>>cash;
        
        // total bill not paid
        if(cash<front->total){
            front->total=front->total - cash;
            cout<<"Remaining amount to be paid is: Rs. "<<front->total<<endl;
            goto pay;
        }
        
        // balance remaining
        else if(cash>front->total){
            cout<<"Balance amount is: Rs. "<<(cash - (front->total))<<endl;
            cout<<"THANK YOU :)"<<endl;
            front->total=0;
        }
        
        //Exact amount paid
        else{
            front->total=0;
            cout<<"THANK YOU :)"<<endl;
        }
        
        // only one order in the queue
        if(front==rear){
            temp=front;
            front = NULL;
            rear = NULL; 
            cout<<"YOUR ORDER IS READY!!!"<<endl;
        }
        // multiple orders in the queue
        else{
            temp=front;
            front = front->next; 
            cout<<"\nYOUR ORDER IS READY!!!"<<endl;
            
        }
    }
}

// Delete item from an order
void Queue::deleteOrder(int n){
    Node *ptr= front;
    int ino,j=0;
    int flag=0;
    int count=0;
    
    //Order doesn't exist
    if(check_ord(n)==false){
        cout<<"Order doesn't exist"<<endl;
    }
    
    //Order exists
    else{
        // counts number of items in the order
        for(int j=0; j<3; j++){
            if(ptr->order[j]!=0){
                count++;
            }
        }
        
        if(count>1){
            while((ptr->index!=n) && (ptr!=NULL)){
                ptr=ptr->next;
            }
            
            cout<<"Enter item number to be cancelled: ";
            cin>>ino;
            
            // to check if item exists (flag=1 if item exists)
            for(int i=0; i<3; i++){
                if(ino==ptr->order[i]){
                    flag=1;
                }
            }
            
            // item exists
            if(flag==1){   
                while(j<3){
                    if(ptr->order[j]==ino){
                        ptr->order[j]=0; 
                    }
                    j++;
                }
                new_total(ptr, ino);
                cout<<"YOUR ORDER HAS BEEN UPDATED!!"<<endl;
                display_cur(ptr);
            }
            
            // item does not exist
            else{
                cout<<"This item doesn't exist in your order"<<endl;
            }
        }
        else{
            cout<<"Cannot delete more items"<<endl;
        }
    }
}


void Queue::display_cur(Node *temp){
    Node *ptr = new Node();
    ptr=temp;
    cout<<"\n------------------------------------------------------"<<endl;
    cout<<"REMEMBER YOUR ORDER NUMBER AND QUEUE!"<<endl;
    cout<<"\nYour order number is: "<<ptr->index<<endl;
    cout<<"Your order choices are: ";
    for(int k=0;k<3;k++){
        if(ptr->order[k]==0){
            cout<<" ";
        }
        else{
          cout<<"["<<ptr->order[k]<<"]  ";
        }
    }
    cout<<"\nThe total is: Rs."<<ptr->total<<endl;
    cout<<"\n--------------------------------------------------------"<<endl;
}


//Displays the queue
void Queue::display(){
    //Queue empty
    if(isempty()==1){
         cout << "Queue is Empty" << endl;
    }
    //Queue not empty
    else{
        Node *ptr=front;
         
        while(ptr!=NULL){
            cout<<"Order Number: "<<ptr->index<<endl;
            cout<<"Items in your order are: ";
            for(int k=0;k<3;k++){
                if(ptr->order[k]==0){
                    cout<<" ";
                }
                else{
                    cout<<"["<<ptr->order[k]<<"]  ";
                }
            }
            cout<<"\nThe total is: Rs."<<ptr->total<<endl;
            cout<<endl;
            
            ptr=ptr->next;
        }
        cout<<"-----------------------------------------------------"<<endl;
    }
}

// checks if order exists
bool Queue::check_ord(int on){
     Node *ptr=front;
    while(ptr!=NULL){
        if(ptr->index==on){
            return true;
        }
        else{
            return false;
        }
         ptr=ptr->next;
    }
}

int main(){
    Queue student;
    Queue teacher;
    int order[5];
    char ch;
    int op,t;
    int tidx=1,sidx=1;
    int count=0;
    cout<<"----------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t\t INSTRUCTIONS"<<endl;
    cout<<"-Two separate queues for teachers & students."<<endl;
    cout<<"\n-First Come First Serve policy strictly followed "<<endl;
    cout<<"\n-Maximum of 3 items in one order."<<endl;
    cout<<"\n-You cannot add items to your order after placing it."<<endl;
    cout<<"\n-Cancelling items is allowed but the entire order cannot be cancelled."<<endl;
    cout<<"\n-Only 80% will be refund on deletion on an item"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------"<<endl;
    
    do{ 
        cout<<"\nWhich of the following do you want to perform?"<<endl;
        cout<<"1. Place order"<<endl;
        cout<<"2. Collect order"<<endl;
        cout<<"3. Delete item from the order"<<endl;
        cout<<"4. Dislay queue"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"ENTER CHOICE: ";
        cin>>op;
        cout<<"\n";
        switch(op){ 
            case 1: 
                // PLACE ORDER (ENQUEUE)
                cout<<"____________________________________"<<endl;
                cout<<"| \t\tMENU\t\t   |"<<endl;
                cout<<"|----------------------------------|"<<endl;
                cout<<"| 1] Chinese combo       | Rs. 150 |"<<endl;
                cout<<"| 2] South Indian combo  | Rs. 150 |"<<endl;
                cout<<"| 3] North Indian combo  | Rs. 150 | "<<endl;
                cout<<"| 4] Vadapav             | Rs. 20  |"<<endl;
                cout<<"| 5] Maggi               | Rs. 20  |"<<endl;
                cout<<"| 6] Cold coffee         | Rs. 20  |"<<endl;
                cout<<"| 7] Tea                 | Rs. 20  |"<<endl;
                cout<<"|________________________|_________|"<<endl;
                
                cout<<"\nAre you a student or a teacher?(0/1): ";
                cin>>t;
                if(t==0){
                    cout<<"You're now in STUDENTS' Queue! \n"<<endl;
                    student.placeOrder(sidx);
                    sidx++;
                }
                else if(t==1){
                    cout<<"You're now in the TEACHERS' Queue! \n"<<endl;
                    teacher.placeOrder(tidx);
                    tidx++;
                    
                }
                else{
                    cout<<"Invalid choice"<<endl;
                    break;
                }
                break;
                
            case 2:
                // COLLECT ORDER (DEQUEUE)
                if(student.isempty() && teacher.isempty()){
                    cout<<"No orders in either queues"<<endl;
                    break;
                }
                else{
                    cout<<"\nAre you a student or a teacher?(0/1): ";
                    cin>>t;
                    if(t==0){
                        if(student.isempty()){
                            cout<<"Queue is empty, please place your order first"<<endl; 
                        }
                        else{
                            student.collect_order();
                        }
                        
                    }
                    else if(t==1){
                        if(teacher.isempty()){
                            cout<<"Queue is empty, please place your order first"<<endl;
                        }
                        else{
                        teacher.collect_order();
                        }
                    }
                    else{
                        cout<<"Invalid choice"<<endl;
                        break;
                    }
                }
                break;
            
            case 3:
                // DELETE ITEM IN AN ORDER
                if(student.isempty() && teacher.isempty()){
                    cout<<"No orders in either queues"<<endl;
                    break;
                }
                else{
                    int ord_no;
                    cout<<"\nAre you a student or a teacher?(0/1): ";
                    cin>>t;
                    cout<<"Enter your order number: ";
                    cin>>ord_no;
                    if(t==0){
                        if(student.isempty()){
                            cout<<"Queue is empty, please place your order first"<<endl;
                        }
                        else{
                         student.deleteOrder(ord_no);
                        }
                    }
                    else if(t==1){
                        if(teacher.isempty()){
                            cout<<"Queue is empty, please place your order first"<<endl;
                        }
                        else{
                            teacher.deleteOrder(ord_no);
                        }
                    }
                    else{
                        cout<<"Invalid choice"<<endl;
                        break;
                    }
                }
                break;
                
                
            case 4:
                cout<<"------------------TEACHER'S QUEUE-------------------"<<endl;
                teacher.display();
                cout<<"------------------STUDENT'S QUEUE--------------------"<<endl;
                student.display();
                cout<<"-----------------------------------------------------";
                break;
                
            default:
                cout<<"invalid option";
        }
        
        label: 
            
        cout<<"\nDo you want to continue operations?(y/n):";
        cin>>ch;
        
        if((ch!='y'&& ch!='Y') && (ch!='n'&& ch!='N')){
            cout<<"Invalid response. Enter (y/n) only"<<endl;
            goto label;
        }
        
    }while(ch=='y'||ch=='Y');

   return 0;
}




/* OUTPUT
----------------------------------------------------------------------------------------------------
		 INSTRUCTIONS
-Two separate queues for teachers & students.

-First Come First Serve policy strictly followed 

-Maximum of 3 items in one order.

-You cannot add items to your order after placing it.

-Cancelling items is allowed but the entire order cannot be cancelled.

-Only 80% will be refund on deletion on an item
----------------------------------------------------------------------------------------------------

Which of the following do you want to perform?
1. Place order
2. Collect order
3. Delete item from the order
4. Dislay queue
5. Exit
ENTER CHOICE: 1

____________________________________
| 		MENU		     |         |
|----------------------------------|
| 1] Chinese combo       | Rs. 150 |
| 2] South Indian combo  | Rs. 150 |
| 3] North Indian combo  | Rs. 150 | 
| 4] Vadapav             | Rs. 20  |
| 5] Maggi               | Rs. 20  |
| 6] Cold coffee         | Rs. 20  |
| 7] Tea                 | Rs. 20  |
|________________________|_________|

Are you a student or a teacher?(0/1): 1
You're now in the TEACHERS' Queue! 

Place Your Order (Maximum 3 orders)
Enter item number: 7
Do you want to order more?(y/n): n
Order placed successfully!!!

------------------------------------------------------
REMEMBER YOUR ORDER NUMBER AND QUEUE!

Your order number is: 1
Your order choices are: [7]    
The total is: Rs.20

--------------------------------------------------------

Do you want to continue operations?(y/n):y

Which of the following do you want to perform?
1. Place order
2. Collect order
3. Delete item from the order
4. Dislay queue
5. Exit 
ENTER CHOICE: 1

____________________________________
| 		MENU		     |		   |	
|----------------------------------|
| 1] Chinese combo       | Rs. 150 |
| 2] South Indian combo  | Rs. 150 |
| 3] North Indian combo  | Rs. 150 | 
| 4] Vadapav             | Rs. 20  |
| 5] Maggi               | Rs. 20  |
| 6] Cold coffee         | Rs. 20  |
| 7] Tea                 | Rs. 20  |
|________________________|_________|

Are you a student or a teacher?(0/1): 0
You're now in STUDENTS' Queue! 

Place Your Order (Maximum 3 orders)
Enter item number: 1
Do you want to order more?(y/n): y
Enter item number: 6
Do you want to order more?(y/n): y
Enter item number: 5

You've reached maximum order limit
Order placed successfully!!!

------------------------------------------------------
REMEMBER YOUR ORDER NUMBER AND QUEUE!

Your order number is: 1
Your order choices are: [1]  [6]  [5]  
The total is: Rs.190

--------------------------------------------------------

Do you want to continue operations?(y/n):y

Which of the following do you want to perform?
1. Place order
2. Collect order
3. Delete item from the order
4. Dislay queue
5. Exit
ENTER CHOICE: 4

------------------TEACHER'S QUEUE-------------------
Order Number: 1
Items in your order are: [7]    
The total is: Rs.20

-----------------------------------------------------
------------------STUDENT'S QUEUE--------------------
Order Number: 1
Items in your order are: [1]  [6]  [5]  
The total is: Rs.190

-----------------------------------------------------
-----------------------------------------------------
Do you want to continue operations?(y/n):y

Which of the following do you want to perform?
1. Place order
2. Collect order
3. Delete item from the order
4. Dislay queue
5. Exit
ENTER CHOICE: 3


Are you a student or a teacher?(0/1): 0
Enter your order number: 1
Enter item number to be cancelled: 5
Only 80% of total will be returned
YOUR ORDER HAS BEEN UPDATED!!

------------------------------------------------------
REMEMBER YOUR ORDER NUMBER AND QUEUE!

Your order number is: 1
Your order choices are: [1]  [6]   
The total is: Rs.174

--------------------------------------------------------

Do you want to continue operations?(y/n):y

Which of the following do you want to perform?
1. Place order
2. Collect order
3. Delete item from the order
4. Dislay queue
5. Exit
ENTER CHOICE: 2


Are you a student or a teacher?(0/1): 1
Enter your order number: 1
Your Reciept:
------------------------------------------------------
REMEMBER YOUR ORDER NUMBER AND QUEUE!

Your order number is: 1
Your order choices are: [7]    
The total is: Rs.20

--------------------------------------------------------
***BILL PAYMENT***
Your total bill is: Rs. 20

Enter cash payment amount: Rs. 50
Balance amount is: Rs. 30
THANK YOU :)
YOUR ORDER IS READY!!!

Do you want to continue operations?(y/n):y

Which of the following do you want to perform?
1. Place order
2. Collect order
3. Delete item from the order
4. Dislay queue
5. Exit
ENTER CHOICE: 4

------------------TEACHER'S QUEUE-------------------
Queue is Empty
------------------STUDENT'S QUEUE--------------------
Order Number: 1
Items in your order are: [1]  [6]   
The total is: Rs.174

-----------------------------------------------------
-----------------------------------------------------
Do you want to continue operations?(y/n):n

*/

