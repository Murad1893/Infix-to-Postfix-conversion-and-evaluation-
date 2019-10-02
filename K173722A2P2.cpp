#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

template <class t>
class _stack{
	private:
	t* arr;
	int top;	
	int size;
		
	public:
	_stack(){
		top=-1;
		arr=NULL;
		size=0;
	}
	_stack(int a){
		size=a;
		top=-1;
		arr=new t[a];
	}
	
	void push(t a){
		if(top>size){
			cout<<"\nStack is full\n";
		}
		top++;
		arr[top]=a;
	}
	
	t pop(){
		if(top!=-1){
		t a;
		a=arr[top];
		arr[top]=0;
		top--;
		return a;
	    }
	    else cout<<"\nstack is empty\n";
	}
	
	int getsize(){
		if(top!=-1)
		return top+1;
		else return -1;
	}
	
	t gettop(){
		if(top!=-1){
			return arr[top];
		}
		else cout<<"\nstack is empty\n";
	}
	
	bool isempty(){
		if(top!=-1){
			return false;
		}
		else return true;
	}
    
    void emptystack(){
    	while(!isempty()){
    		pop();
		}
	}
    
	bool isFull(){
		if(top+1==size){
			return true;
		}
		else return false;
	}
	
	void printstack(){
		for(int i=0;i<top+1;i++){
			cout<<arr[i]<<" ";
		}
	}
	
	void infix_to_postfix(fstream& obj,fstream& obj1){
	
	int priority[5]={6,5,4,3,2}; //priority set for all the operators
    char op[5]={'/','*','/','+','-'};

    char c,temp;
    
    if(!obj){
    	exit(0);
	}
	else{
    while(!obj.eof()){
    	string s1;
    	obj>>s1; //reads the whole line as a string
    	for(int i=0;i<s1.length();i++){ //runs the loop for all elements of the string
		if(s1[i]=='('){
			push(s1[i]); // If it is opening parenthesis, push it on stack. 
		}
		else if(s1[i]=='+' || s1[i]=='*' || s1[i]=='-' || s1[i]=='/' || s1[i]=='^'){ // If it is an operator, then 
			cout<<" ";
    		obj1<<" ";
			while(2){
			label:
			if(isempty()){ //stack is empty, push operator on stack. 
				push(s1[i]);
				break;
			}
		    temp=gettop();
			if(temp=='('){ //the top of the stack is opening parenthesis, push operator on stack. 
				if(s1[i]!='(' || s1[i]!=')'){ //given that the character pushed is an operator and not a paranthesis
					push(s1[i]);
					break;
				}
			}
			else{ // If it has higher priority than the top of stack, push operator on stack. (operator priorities ^, *, /, +, and - 
				int c_priority=0;
				int top_priority=0;
				char d=gettop();
				for(int j=0;j<5;j++){
					if(s1[i]==op[j]){
						c_priority=priority[j];
					}
				}
				for(int j=0;j<5;j++){
					if(d==op[j]){
						top_priority=priority[j];
					}
				}
				if(top_priority>=c_priority){
					char temp=pop();  //Else pop the operator from the stack and output it, repeat step 4. 
					if(temp!=')' || temp!='('){
						cout<<temp<<" ";
						obj1<<temp;
						obj1<<" ";
					}
					goto label; //repeating step 4
				}
				else{
					push(s1[i]); // If it has higher priority than the top of stack, push operator on stack.
					break;
				}
				
				}
				}
			}
			else if(s1[i]==')'){
				cout<<" ";
    		    obj1<<" ";
				while(2){
					char temp=pop();
					if(temp=='('){ //If it is a closing parenthesis, pop operators from the stack and output them until an opening parenthesis is encountered. pop and discard the opening parenthesis. 

					break;
					}
					else{
					if(temp!=')' || temp!='('){
						cout<<temp;
						obj1<<temp;
					}
					continue;
				    }
				}
			}
			else{
		    	cout<<s1[i];
		    	obj1<<s1[i];
			}
		    }
		    while(!isempty()){ //If there is no more input, unstack the remaining operators to output. 
		    	temp=pop();
		    	if(temp=='+' || temp=='-' || temp=='*' || temp=='/' || temp=='^'){
		    		cout<<" "<<temp;
		    		obj1<<" "<<temp;
				}
			}
			obj1<<"\n";
		    cout<<"\n";
		    }
		
	}
	}

		
};

void postfix_evaluation(){
	
	_stack<int> s(100);
    fstream obj2;
    obj2.open("A2P2-out.txt",ios::in);
    string s1;
    int number;
    int result=0; //to store the result
    int i=0; //to store the string count
    int j=0; //to store the array count
    bool detect=false;
	int arr[10];
    
    for(int k=0;k<10;k++){
    	arr[k]=0;
	}
    
    getline(obj2,s1);
    
    while(i<s1.length()){
    	
    	if(s1[i]>='0' && s1[i]<='9'){ //if an operand occurs then move it to array until we get a space or an operator signifying it is >1 digit number
    		arr[j]=s1[i];
    	    detect=true;
		}
		
		if(s1[i]>='a' && s1[i]<='z'){ //if a variable occurs then cant be evaluated
		obj2.close();
		obj2.open("A2P2-out.txt",ios::out | ios::app);
		obj2<<"\nCannot evaluate expression";	
		obj2.close();
		cout<<"\nCannot evaluate expression";	
		exit(0);
		}
		
		if(s1[i]==' ' && detect){
			int p=0;
			for(int k=j-1;k>=0;k--){
				number+=(arr[p]-48)*pow(10,k); //this is for number that is more than one digit hence at it reads by character so 3 0 0 is seperately hence we must first calculate it by tens unit hundreds then supply it to an integer
				p++;
			}
			s.push(number); //after character number evaluated then we can push it
			j=0; //the array is reset
			number=0;
			for(int k=0;k<10;k++)
			arr[k]=0;
			i++;
			detect=false; //detect bool is set off
			continue;
		}
		//evaluating and pushing the result
		if(s1[i]=='*'){
		
			if(s.getsize()>=2){
				result=s.pop();
				result=s.pop()*result;
				s.push(result);	
			}
			j=-2; 
			
		}
		
		if(s1[i]=='/'){
			
			if(s.getsize()>=2){
				result=s.pop();
				result=s.pop()/result;
				s.push(result);	
			}
			j=-2;
			
		}
		if(s1[i]=='+'){
			
		    if(s.getsize()>=2){
				result=s.pop();
				result=s.pop()+result;
				s.push(result);	
			}
			j=-2;
		}
		if(s1[i]=='-'){
			
			if(s.getsize()>=2){
				result=s.pop();
				result=s.pop()-result;
				s.push(result);	
			}
			j=-2;
		}
		i++;
		j++;
	}
	
	obj2.close();
	cout<<"\nresult: "<<result;
	obj2.open("A2P2-out.txt",ios::out | ios::app);
	obj2<<"\nResult: "<<result;	
}

int main(){ 
    _stack<char> s(100);
    
    fstream obj,obj1,obj2;
    ///*********hardcoded testcase. You can manually input your testcase file name here***************
    obj.open("1.txt",ios::in); 
    
    if(!obj){
    	cout<<"File not found";
    	exit(0);
	}
    
    obj1.open("A2P2-out.txt",ios::out | ios::trunc);
    s.infix_to_postfix(obj,obj1); //file objetcs passed into the fucntion
    
    obj.close();
    obj1.close();
    
    postfix_evaluation();
    
}
