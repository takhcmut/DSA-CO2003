#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}
        


void StackFrame::run(string filename) {
    ifstream infile(filename);
  

    string line;
    int lineNumber = 0;
    while (getline(infile, line)) {             // while chạy từng line
        ++lineNumber;

       
        size_t pos = line.find(' ');
        string instruction = (pos == string::npos) ? line : line.substr(0, pos);
        string thamso = (pos == string::npos) ? "" : line.substr(pos + 1);

        
        runInstruction(instruction, lineNumber, thamso); // Thực thi lệnh  
    }   
        infile.close();
}

void StackFrame::runInstruction(const string& instruction, int line, const string& thamso){       
    if (instruction == "iconst") {
        int value;
        value = stoi(thamso);
        iconst(value,line);}
    else if (instruction == "fconst") {
        float value;
        value=stof(thamso);
        fconst(value, line);} 
    else if  (instruction == "iadd") iadd(line); 
    else if  (instruction == "fadd") fadd(line); 
    else if  (instruction == "top") top(line);
    else if  (instruction == "isub") {
        isub(line); 
    } else if (instruction == "imul") {
        imul(line); 
    } else if (instruction == "idiv") {
        idiv(line); 
    } else if (instruction == "ineg") {
        ineg(line); 
    }  else if (instruction == "irem") {
        irem(line); 
    } else if (instruction == "iand") {
        iand(line);
    } else if (instruction == "ior") {
        ior(line); 
    } else if (instruction == "ieq") {
        ieq(line); 
    } 
    else if (instruction == "ineq") {
        ineq(line); 
    }
    else if (instruction == "ilt") {
        ilt(line); 
    } else if (instruction == "igt") {
        igt(line);
    } else if (instruction == "ibnot") {
        ibnot(line); 
    } else if (instruction == "i2f") {
        i2f(line); 
    } else if (instruction == "f2i") {
        f2i(line); 
    } 
    
    else if (instruction == "fsub") {
        fsub(line); 
    } else if (instruction == "fmul") {
        fmul(line); 
    } else if (instruction == "fdiv") {
        fdiv(line); 
    }  else if (instruction == "fneg") {
        fneg(line); 
    } else if (instruction == "feq") {
        feq(line); 
    } else if (instruction == "fneq") {
        fneq(line); 
    } else if (instruction == "flt") {
        flt(line); 
    } else if (instruction == "fgt") {
        fgt(line); }
     else if (instruction == "iload") {
        iload(thamso,line);
    }
    else if (instruction == "fload") {
        fload(thamso, line); 
    } 
    else if (instruction == "istore") {
        istore(thamso,line);

    } else if (instruction == "fstore") {
        fstore(thamso, line); 
    }
    else if (instruction == "val") {
        val(thamso, line); 
    } 
    else if ( instruction=="par"){
        par(thamso,line);
    }
    
}

void StackFrame::iadd( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {c= a+ b;
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);

}
void StackFrame::fadd( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    float c;
    if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)) {
    c= a+ b;
    OperandStack.fpush(c);}
    else throw TypeMisMatch(line);
}

void StackFrame::isub( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {c= a- b;
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);
   

    
}
void StackFrame::fsub( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    float c;
    if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)) {
    c= a - b;
    OperandStack.fpush(c);}
    else throw TypeMisMatch(line);
}



void StackFrame::imul( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {c= a * b;
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);
   

    
}
void StackFrame::fmul( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    float c;
    if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)) {
    c= a* b;
    OperandStack.fpush(c);}
    else throw TypeMisMatch(line);
}


void StackFrame::idiv( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();
    

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {
        if (b==0) throw DivideByZero(line);
        c= a/ b;
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);
    


    
}
void StackFrame::fdiv( int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();
    

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    float c;
   if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)) {
    if (b==0) throw DivideByZero(line);
    c= a/ b;
    OperandStack.fpush(c);}
    else throw TypeMisMatch(line);
}



void StackFrame::irem(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {
    if (b==0) throw DivideByZero(line);
    c = a - (a/b)*b; 
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);

}


void StackFrame::ineg(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    if(OperandStack.codeTop() == 0) {
            int a= -OperandStack.itop();
            OperandStack.pop();
            OperandStack.ipush(a);
        }
    else if((OperandStack.codeTop() == 1)) throw TypeMisMatch(line);
}


void StackFrame::fneg(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    if(OperandStack.codeTop() == 1) {
            float a= -OperandStack.ftop();
            OperandStack.pop();
            OperandStack.fpush(a);
        }
    else if((OperandStack.codeTop() == 0)) {
        float a= - static_cast<float>(OperandStack.itop());
        OperandStack.pop();
        OperandStack.fpush(a);
    }
        }

void StackFrame::iand(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {c= a & b;
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);
        }

void StackFrame::ior(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    int c;
    if ( (b_type == a_type)&& (a_type ==0)) {c= a | b;
    OperandStack.ipush(c);}
    
    else throw TypeMisMatch(line);
        
        }

void StackFrame::ieq(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    if ( (b_type == a_type)&& (a_type ==0)) {
        if (a==b) OperandStack.ipush(1);
        else OperandStack.ipush(0);}
    
    else throw TypeMisMatch(line);
}
void StackFrame::feq(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    
    if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)) {
    if (a==b) OperandStack.ipush(1);
    else OperandStack.ipush(0);}
}

void StackFrame::ineq(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    if ( (b_type == a_type)&& (a_type ==0)) {
        if (a==b) OperandStack.ipush(0);
        else OperandStack.ipush(1);}
    
    else throw TypeMisMatch(line);
}

void StackFrame::fneq(int line){
     if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    
    if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)){
    if (a==b) OperandStack.ipush(0);
    else OperandStack.ipush(1);}
    
}


void StackFrame::ilt(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    if ( (b_type == a_type)&& (a_type ==0)) {
        if (a<b) OperandStack.ipush(1);
        else OperandStack.ipush(0);}
    
    else throw TypeMisMatch(line);
}
void StackFrame::igt(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    int b=OperandStack.itop();
    int b_type=OperandStack.codeTop();
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);
    int a=OperandStack.itop();
    int a_type = OperandStack.codeTop();
    OperandStack.pop();
    if ( (b_type == a_type)&& (a_type ==0)) {
        if (a>b) OperandStack.ipush(1);
        else OperandStack.ipush(0);}
    
    else throw TypeMisMatch(line);
}

void StackFrame::flt(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    
    if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)){
    if (a<b) OperandStack.ipush(1);
    else OperandStack.ipush(0);}
}

void StackFrame::fgt(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    float b;
    int b_type=OperandStack.codeTop();
    if ( b_type==0) b= static_cast<float>(OperandStack.itop());
    else {b =OperandStack.ftop();}
    OperandStack.pop();

    if(OperandStack.empty()) throw StackEmpty(line);

    float a;
    int a_type=OperandStack.codeTop();
    if ( a_type==0) a= static_cast<float>(OperandStack.itop());
    else {a =OperandStack.ftop();}
    
    OperandStack.pop();

    
  if ( (a_type==1 && b_type==1)||(a_type==0 && b_type==1)||(a_type==1 && b_type==0)||(a_type==0 && b_type==0)) {
    if (a>b) OperandStack.ipush(1);
    else OperandStack.ipush(0);}
}

void StackFrame::ibnot(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    if(OperandStack.codeTop()==0){
            int a = OperandStack.itop();
            OperandStack.pop();
            if (a==0) OperandStack.ipush(1);
            else OperandStack.ipush(0);
    }
    else throw TypeMisMatch(line);
}




void StackFrame::fconst(float value,int line){
    if (OperandStack.getSize()>=OPERAND_STACK_MAX_SIZE) throw StackFull(line);      //*check typemissmatch??
    OperandStack.fpush(value);

}

void StackFrame::iconst(int value,int line){
    if (OperandStack.getSize()>=OPERAND_STACK_MAX_SIZE) throw StackFull(line);       //*check typemissmatch??
    OperandStack.ipush(value);

}

void StackFrame:: i2f(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    if(OperandStack.codeTop()==0){
        float a= static_cast<float>(OperandStack.itop());
        OperandStack.pop();
        OperandStack.fpush(a);
}
    else throw TypeMisMatch(line);
    
}

void StackFrame::f2i(int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    if(OperandStack.codeTop()==1){
        int a= (int)OperandStack.ftop();
        OperandStack.pop();
        OperandStack.ipush(a);
}
    else throw TypeMisMatch(line);
    
}

void StackFrame::top(int line) {
    if (OperandStack.empty()) throw StackEmpty(line);
    if (OperandStack.codeTop() == 0) {
        std::cout << OperandStack.itop()<<endl;  // condition for return itop
    } 
    else if (OperandStack.codeTop() == 1) {
        std::cout << OperandStack.ftop()<<endl;// condition for return ftop
    }
}


void StackFrame::iload(string var,int line){
    OpStack::Node * tmp = get(AVLroot,var);
    if(tmp==nullptr) throw UndefinedVariable(line);
    int a=0;
   

    if (tmp->code==0) {
        a= tmp-> iVal;
        if (OperandStack.getSize()>=OPERAND_STACK_MAX_SIZE) throw StackFull(line);
        else OperandStack.ipush(a);}
    
    else if (tmp->code==1) throw TypeMisMatch(line);

}
void StackFrame::fload(string var,int line){
    OpStack::Node * tmp = get(AVLroot,var);
    if(tmp==nullptr) throw UndefinedVariable(line);
    float a=0;
    

        if (tmp->code==1) {
 
        a= tmp-> fVal;
        if (OperandStack.getSize()>=OPERAND_STACK_MAX_SIZE) throw StackFull(line);
        else OperandStack.fpush(a);}
    else if (tmp->code==0) throw TypeMisMatch(line);
    
}

void StackFrame::istore(string var,int line){                                                   //! co ve da dung
    if (OperandStack.empty()) throw StackEmpty(line);   
    
    if(OperandStack.codeTop()==1) throw TypeMisMatch(line);
    else if (OperandStack.codeTop()==0){
            if (getSize(AVLroot) >= LOCAL_VARIABLE_SPACE_SIZE/2) throw LocalSpaceFull(line);
            else {int a = OperandStack.itop();
            OperandStack.pop();
            AVLroot= iinsert(AVLroot,var,a);}
    }
    
}
void StackFrame::fstore(string var,int line){                           //! co ve da dung
    if(OperandStack.empty()) throw StackEmpty(line);
    
    if(OperandStack.codeTop()==0) throw TypeMisMatch(line);

    else if (OperandStack.codeTop()==1){
            if (getSize(AVLroot)>=LOCAL_VARIABLE_SPACE_SIZE/2) throw LocalSpaceFull(line);
            float a = OperandStack.ftop();
            OperandStack.pop();
            AVLroot= finsert(AVLroot,var,a);;
    }
   
}

void StackFrame::val(string var, int line){         //! co ve da dung
    OpStack::Node * tmp= get(AVLroot,var);

    if (tmp==nullptr) throw UndefinedVariable(line);      // root rong va ko tim thay deu tra ve null -> undefined het

    if(tmp->code==0) cout<< tmp->iVal<<endl;
    else if(tmp->code==1) cout<< tmp->fVal<<endl;

}



void StackFrame::par(string var, int line ){
    OpStack::Node * tmp = getpar(AVLroot,var);
    if (tmp!=nullptr) cout<< tmp->key<<endl;
    else if (tmp==nullptr && AVLroot->key==var) cout<< "null"<<endl;    //*truong hop root null
    else throw UndefinedVariable(line);
}
