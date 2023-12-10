#include<iostream>
#include<string.h>
using namespace std;

//define class for linked list node
template <class T> class node{
    public: 
    T val;
    node *next;

    node(T x){
        this->val = x;
        this->next = nullptr;
    }
};

//define class for implementing stack using linked list
template <class T> class stack{
    node<T> *front;

    public:
    stack(){
        front = nullptr;
    }

    void push(T x){
        node<T> *newNode = new node<T>(x);
        if(!newNode){
            cout<<"Error: Stack Overflow during push operation"<<endl;
            exit(EXIT_FAILURE);
        }
        newNode->next = front;
        front = newNode;
    }

    void pop(){
        if(front != nullptr){
            node<T> *temp = front;
            front = front->next;
            delete temp;
        }
    }

    T top(){
        if(front != nullptr){
            node <T> *t = front;
            return t->val;
        }
        return T();
    }

    bool isEmpty(){
        return front == nullptr;
    }
};

//function to remove leading zeros from given string
string RemoveLeadingZeros(string s){
    for(int i=0; i<s.size(); i++){
        if(s[i] != '0')
            return s.substr(i);
    }
    return "0";
}

//function to reverse given string
string reverseStr(string s){
    string ans = "";
    int n = s.size();
    for(int i=n-1; i>=0; i--)
        ans += s[i];
    return ans;
}

//function to add two big integers given as strings
string add(string x, string y){
    string ans = "";
    int carry = 0;
    int m = x.size(), n = y.size();
    if(m < n){
        string temp = x;
        x = y;
        y = temp;
        int t = m;
        m = n;
        n = t;
    }
    string temp1 = "", temp2 = "";
    //get reverse of strings x and y
    temp1 = reverseStr(x);
    temp2 = reverseStr(y);

    //perform addition
    for(int i=0; i<n; i++){
        int a = temp1[i]-'0', b = temp2[i]-'0', sum = a+b+carry;
        carry = sum/10;
        int digit = sum%10;
        ans += digit+'0';
    }
    for(int i=n; i<m; i++){
        int a = temp1[i]-'0', sum = a+carry;
        carry = sum/10;
        int digit = sum%10;
        ans += digit+'0';
    }
    if(carry) ans += carry + '0';
    //reverse ans
    ans  = reverseStr(ans);
    ans = RemoveLeadingZeros(ans);
    return ans;
}

//function to subtract two big integers given as strings
string sub(string x, string y){
    string ans = "";
    int borrow = 0;
    int m = x.size(), n = y.size();
    string temp1 = "", temp2 = "";
    //get reverse of strings x and y
    temp1 = reverseStr(x);
    temp2 = reverseStr(y);

    //perform subtraction
    for(int i=0; i<n; i++){
        int a = temp1[i]-'0', b = temp2[i]-'0', diff = a-b-borrow;
        if(diff < 0){
            borrow = 1;
            diff += 10;
        }
        else borrow = 0;
        ans += diff+'0';
    }
    for(int i=n; i<m; i++){
        int a = temp1[i]-'0', diff = a-borrow;
         if(diff < 0){
            borrow = 1;
            diff += 10;
        }
        else borrow = 0;
        ans += diff+'0';
    }
    //reverse ans
    ans  = reverseStr(ans);
    //remove leading zeros if any
    ans = RemoveLeadingZeros(ans);
    return ans;
}

//function to multiply two big integers given as strings
string multiply(string x, string y){
    int m = x.size(), n = y.size();
    string temp1 = reverseStr(x);
    string temp2 = reverseStr(y);
    string ans = "", temp = "";
    int count = 0;
    //perform multiplication 
    //start by selecting unit's place digit of num1 and multiply with all digits of num2
    //considering carry and then adding result at each step
    for(int i=0; i<m; i++){
        int carry = 0;
        int a = temp1[i]-'0';
        for(int j=0; j<n; j++){
            int b = temp2[j]-'0';
            int product = a*b+carry;
            int  digit = product%10;
            carry = product/10;
            temp += digit+'0';
        }
        if(carry)
            temp += carry + '0';
        temp = reverseStr(temp);
        if(count !=0){
            for(int k=count; k>0; k--)
                temp += '0';
            ans = add(temp, ans);
        }
        else{
            ans = temp;
        }
        temp = "";
        carry = 0;
        count++;
    }
    int size = ans.size(), i=0;
    while(i<n && ans[i]=='0')
        i++;
    if(i==n) ans = '0';
    return ans;
}

//function which returns true if a is greater than b
bool isGreater (string a, string b){
    int m = a.size(), n = b.size();
    if(m>n) return true;
    if(m<n) return false;
    for(int i=0; i<m; i++){
        if(a[i] > b[i]) return true;
        else if (a[i] == b[i]) continue;
        else return false;
    }
    return false;
}

//function which performs integer division/modulo operation for two big integers and return result based on input flag
//div flag = true: division
//div flag = false: mod
string divide_mod(string dividend, string divisor, bool div){
    //handle base cases
    if(dividend == divisor){
        if(div) return "1";
        else return "0";
    }
    dividend = RemoveLeadingZeros(dividend);
    divisor = RemoveLeadingZeros(divisor);
    int m = dividend.size(), n = divisor.size();
    if(isGreater(divisor,dividend)){
        //for integer division, if divisor greater than dividend then return 0
        if(div) return "0";
        else return dividend;
    }
    string ans = "", num = "";
    int i=0;
    while(!isGreater(num,divisor)){
        //select num just larger than divisor
        num += dividend[i];
        i++;
    }
    while(isGreater(num,divisor)){
        long long int count = 0;
        while(isGreater(num,divisor) || num == divisor){
            //perform repeated subtraction and keep count of quotient
            num = sub(num, divisor);
            count++;
        }
        ans += to_string(count);
        //take next digits of dividend in num
        while(i<m){
            num += dividend[i];
            num = RemoveLeadingZeros(num);
            i++;
            if(!isGreater(num,divisor)){
                if(num == divisor){
                    ans += "1";
                    num = "0";
                }
                else
                    ans += "0";
            }
            else   
                break;
        }
    }
    if(div)
        return ans; //division
    else return RemoveLeadingZeros(num); //mod
}

//function to calculate power of big integer
string exponent(string base, long long int power){
    if(power == 0) return "1";
    string ans = "1";
    while(power > 0){
        if(divide_mod(to_string(power),"2",0) == "1"){
            //if power is odd, then make it even
            ans = multiply(ans, base);
        }
        power = stoll(divide_mod(to_string(power), "2", 1)); //divide power by 2
        base = multiply(base,base); // square base
    }
    return ans;
}

//function to find Greates Common Divisor of two big integers
string GCD(string a, string b){
    if(divide_mod(a,b,0) == "0")
        return b;
    return GCD(b, divide_mod(a,b,0));
}

//function to find factorial of given integer
string factorial(int n){
    if(n==0 || n==1) return "1";
    string ans = "1";
    for(int i=2; i<=n; i++){
        ans = multiply(to_string(i),ans);
    }
    RemoveLeadingZeros(ans);
    return ans;
}

//function which returns true if given char is one of the operator (+,-,x,/)
bool isOperator(char c){
    if(c == '+' || c == '-' || c == 'x' || c == '/')
        return true;
    return false;
}

//function which returns precedence of operator. Higher return value if higher precedence
int getPrecedence(char op){
    //cout<<"checking precedence for "<<op<<endl;
    if(op == '+' || op == '-') return 1;
    if(op == 'x' || op == '/') return 2;
    return 0;
}

//function to perform required mathematical operation based on input operator
string performOperation(string op1, string op2, char op){
    string ans = "";
    if(op == '+'){
        ans = add(op1,op2);
        return ans;
    }
    if(op == '-'){
        ans = sub(op1,op2);
        return ans;
    }
    if(op == 'x'){
        ans = multiply(op1,op2);
        return ans;
    }
    ans = divide_mod(op1,op2,1);
    return ans;

}

//function which checks if given input expression has digits and operators only as part of string
int isExpressionValid(string s){
    for(char c:s){
        if(isOperator(c) || (c >= '0' && c <= '9'))
            continue;
        else return 0;
    }
    return 1;
}

//function which solves given expression and returns the result
string SolveExp(string exp){
    if(!isExpressionValid(exp)) return "Expression entered is invalid.";
    stack <string> s_operand;
    stack <char> s_operator;
    string res = exp, operand = "";
    for(char c: exp){
        if(!isOperator(c)){
            //form operand string
            operand += c;
            continue;
        }
        else{ //found operator so push operand on stack and check precedence
            s_operand.push(operand);
            operand = "";
            if(s_operator.isEmpty() || getPrecedence(c) > getPrecedence(s_operator.top())){
                //if stack empty or current operator has higher precedence then push on stack
                s_operator.push(c);
                continue;
            }
            //pop operator and operands and perform operation until there is higher precedence operator present on top of stack
            while(!s_operator.isEmpty() && getPrecedence(s_operator.top()) >= getPrecedence(c)){
                char op = s_operator.top();
                s_operator.pop();
                string op2 = s_operand.top();
                s_operand.pop();
                string op1 = s_operand.top();
                s_operand.pop();
                res = performOperation(op1,op2,op);
                s_operand.push(res);
            }
            s_operator.push(c); //push current operator on stack
        }
    }
    if(operand != "") s_operand.push(operand);
    while(!s_operator.isEmpty()){
        char op = s_operator.top();
        s_operator.pop();
        string op2 = s_operand.top();
        s_operand.pop();
        string op1 = s_operand.top();
        s_operand.pop();
        res = performOperation(op1,op2,op);
        s_operand.push(res);
    }
    return res;
}

int main(){

    int t;
    cin>>t;
    while(t--)
    {
    int operation;
    cin>>operation; //get type of operation

    switch (operation)
    {
        case 1:
        {
            //solve expression
            string s = "";
            cin>>s;
            cout<<SolveExp(s)<<endl;
            break;
        }
        case 2:
        {
            //exponent
            string s1, s2;
            cin>>s1>>s2; //base, exponent
            cout<<exponent(s1, stoll(s2))<<endl;
            break;
        }
        case 3:
        {
            //GCD
            string s1, s2;
            cin>>s1>>s2;
            cout<<GCD(s1, s2)<<endl;
            break;
        }
        case 4:
        {
            //factorial
            string s;
            cin>>s;
            cout<<factorial(stoi(s))<<endl;
            break;
        }
        default:
        {
            //Invalid choice of operation specified
            //cout<<"Invalid Operation code. Operation Code must be in range 1 to 4 (inclusive)"<<endl;
            break;
        }
        
    }
   
    }
    return 0;
}
