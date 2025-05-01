#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include<string>


class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
public:

    /*
    Constructor of StackFrame
    
    */
   StackFrame();
   class OpStack {      
public: 
    class Node {
    public:
        int iVal;
        float fVal;
        int code;
        Node* right;
        Node* left;

        Node(){
            iVal=0;
            fVal=0;
            code =-1;
            right=left=nullptr;
        }
        Node(int x){
            this->iVal=x;
            right=left=nullptr;
            this->code=0;
        }
        Node ( float x){
            this->fVal=x;
            right=left=nullptr;
            this->code=1;
        }
    };

protected:
    int size;
    int count;
    Node* head;
    Node* tail;

public:
    OpStack(int size = 32) : size(size), count(0), head(nullptr), tail(nullptr) {}

    void fpush( float fVal) {
        for (int i=0;i<2;i++){
        Node* tmp = new Node( fVal);

    if (this->count==0) head=tail=tmp;
    else { 
        tail->right= tmp;
        tmp->left= tail;
        tail=tmp;
    }

    this->count++;}
    }

    void ipush( int iVal) {
        for (int i=0;i<2;i++){
        Node* tmp = new Node(iVal);

    if (this->count==0) head=tail=tmp;
    else { 
        tail->right= tmp;
        tmp->left= tail;
        tail=tmp;
    }

    this->count++;}
    }
    

    void pop() {
        for (int i=0;i<2;i++){
        Node* temp = tail;
        tail = tail->left;
        if (tail) {
            tail->right = nullptr;
        } else {
            head = nullptr;    
        }
        delete temp;
        this->count--;}
        
    }

    bool empty()  {
        return count == 0;
    }

    int getSize()  {
        return this->count;
    }

    int codeTop(){
        if(tail!=nullptr) return tail->code;
        else return -1;                     //return -1 neu stack rong
    }

    float ftop()  {
        if (tail!=nullptr) return tail->fVal;
        else return -999;                   //return -999 neu stack rong
    }

    int itop(){
        if (tail!=nullptr)  return tail->iVal;
        else return -999;                    //return -999 neu stack rong
    }   
};
        OpStack OperandStack;


    class VarSpace {
private:
    int size;
    int count;
    OpStack::Node* arr;

public:
    VarSpace(int size = 256) : size(size), count(0) {
        arr = new OpStack::Node[size];
        for (int i=0;i<256;i++){
            arr[i] = OpStack::Node();                   //chỗ này khởi tạo theo constructor 1 để code của các node =-1 - > node trống
        }
    }

    ~VarSpace() {
        delete[] arr;
    }

    // void setVariable(int index, int iVal, float fVal) {
    //     if (index >= 0 && index < size) {
    //         arr[index] = OpStack::Node(iVal, fVal);
    //         if (index >= count) {
    //             count = index + 1;
    //     } 
    // }}

    void iset(int iVal, int index){
        if (index >= 0 && index < size) {
            arr[index] = OpStack::Node(iVal);
            arr[index+1] = OpStack::Node(iVal);
            }}

    void fset(float fVal, int index)
    {       if (index >= 0 && index < size) {
            arr[index] = OpStack::Node(fVal);
            arr[index+1] = OpStack::Node(fVal);
            }

    }
    int iget(int index){
        return arr[index].iVal;
    }
    float fget(int index){
        return arr[index].fVal;
    }

    int getcode(int index){
        return arr[index].code;
    }
    // OpStack::Node getVariable(int index)  {
    //     if (index >= 0 && index < count) {
    //         return arr[index];
    //     } 
    // }

    // void clear() {
    //     for (int i = 0; i < count; ++i) {
    //         arr[i] = OpStack::Node();  // Reset to default node
    //     }
    //     count = 0;
    // }

    // int getCount(){
    //     return count;
    // }

    int getSize() {
        return size;
    }
};

    VarSpace vs;
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
    void runInstruction(const std::string& instruction, int line, const std::string & thamso); 

    void iadd(int line); 
    
    void top(int line) ;
    void isub(int line); 
    void imul(int line); 
    void idiv(int line); 
    void ineg(int line); 
    void irem(int line); 
    void iand(int line); 
    void ior(int line); 
    void ieq(int line); 
    void ineq(int line); 
    void ilt(int line); 
    void igt(int line); 
    void ibnot(int line); 
    void i2f(int line); 
    void f2i(int line); 
    void fadd(int line); 
    void fsub(int line); 
    void fmul(int line); 
    void fdiv(int line); 
    void fneg(int line);
    void feq(int line); 
    void fneq(int line); 
    void flt(int line); 
    void fgt(int line); 

    void val(int index, int line); 
    
    void iconst(int value, int line); 
    void fconst(float value, int line); 
   
    void iload(int index, int line);
    void fload(int index, int line); 
    void fstore(int index, int line); 
    void istore(int index, int line); 





};

#endif // !__STACK_FRAME_H__