#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include<string>
#include<stack>


class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarSpaceSize;  // size of local variable array
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
        std::string key; // !key để quản lý trong avl
        int height;

        
        Node(int x){
            this->iVal=x;
            right=left=nullptr;
            this->code=0;
            this->key="0";
            this->height=1;
        }
        Node ( float x){
            this->fVal=x;
            right=left=nullptr;
            this->code=1;
            this->key="0";
            this->height=1;

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

        //! LOCAL VARSPACE O DAY 
 OpStack::Node * AVLroot= nullptr;


   int height(OpStack::Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  

int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
   
OpStack::Node *rightRotate(OpStack::Node *y)  
{  
    OpStack::Node *x = y->left;  
    OpStack::Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
OpStack::Node *leftRotate(OpStack::Node *x)  
{  
    OpStack::Node *y = x->right;  
    OpStack::Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(OpStack::Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) -  
        height(N->right);  
}  
  
OpStack::Node* iinsert(OpStack::Node* node, std::string k, int value)           //! node nay la root
{  
    /* 1. Perform the normal BST rotation */  
    if (node == NULL)  
        {
            OpStack::Node* tmp = new OpStack::Node(value);
            tmp->key=k;
            return tmp;
        }  
  
    if (k < node->key)  
        node->left = iinsert(node->left, k,value);  
    else if (k > node->key)  
        node->right = iinsert(node->right, k, value);  
        // truong hop key da ton tai
    else {
        
        node ->iVal =value;
        node->code=0;
        return node;
        
    }
  
    /* 2. Update height of this ancestor node */  
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    /* 3. Get the balance factor of this 
        ancestor node to check whether 
        this node became unbalanced */  
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && k < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && k > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && k > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && k< node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */  
    return node;  
}  

OpStack::Node* finsert(OpStack::Node* node, std::string k, float value)           //! node nay la root
{  
    /* 1. Perform the normal BST rotation */  
    if (node == NULL)  
        {
            OpStack::Node* tmp = new OpStack::Node(value);
            tmp->key=k;
            return tmp;
        }  
  
    if (k < node->key)  
        node->left = finsert(node->left, k,value);  
    else if (k > node->key)  
        node->right = finsert(node->right, k, value);  
        // truong hop key da ton tai
    else {
        
        node ->fVal =value;
        node->code=1;
        return node;
        
    }
  
    /* 2. Update height of this ancestor node */  
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    /* 3. Get the balance factor of this 
        ancestor node to check whether 
        this node became unbalanced */  
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && k < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && k > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && k > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && k < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */  
    return node;  
}  
  

OpStack::Node* get(OpStack::Node* root, std::string k) {             //getter
        if(root==nullptr) return nullptr;           //! cay avl trong -> return nullptr

        if (root->key == k) return root;

        OpStack::Node* leftResult = get(root->left, k);
        if (leftResult != nullptr)  return leftResult;

        OpStack::Node* rightResult = get(root->right, k);
        if (rightResult != nullptr) return rightResult;
        
        return nullptr; // Trả về null nếu không tìm thấy khóa         //! cho nay se throw
}


OpStack::Node* getpar(OpStack::Node* root, const std::string& k) {
    if (root == nullptr) {
  // Trường hợp cây trống
        return nullptr; 
    }
    
    if(root->key == k) {
         // Trường hợp node cần tìm là gốc
        return nullptr;
    }

    // Kiểm tra nếu root là cha của nút có khóa k
    if ((root->left != nullptr && root->left->key == k) || 
        (root->right != nullptr && root->right->key == k)) {
        return root;
    }

    // Tìm trong cây con trái
    OpStack::Node* leftResult = getpar(root->left, k);
    if (leftResult != nullptr) // Nếu tìm thấy trong cây con trái
        return leftResult;

    // Nếu không tìm thấy trong cây con trái, tiếp tục tìm trong cây con phải
    return getpar(root->right, k);
}

int getSize(OpStack::Node* root) {
    if (root == NULL)
        return 0; // Nếu cây trống, kích thước là 0

    // Kích thước của cây là tổng kích thước của cây con trái, cây con phải và nút gốc
    return 1 + getSize(root->left) + getSize(root->right);
}





    
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

    
    
    void iconst(int value, int line); 
    void fconst(float value, int line); 
   
    void iload(std::string var, int line);
    void fload(std::string var, int line); 
    void fstore(std::string var, int line); 
    void istore(std::string var, int line);
    void val(std::string var, int line);  
    void par(std::string var ,int line);





};

#endif // !__STACK_FRAME_H__