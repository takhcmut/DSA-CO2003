#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {
        
}

void StackFrame::run(string filename) {
    ifstream infile(filename);
    // if (!infile.is_open()) {
    //     throw runtime_error("Khong the mo file: " + filename);
    // }

    string line;
    int lineNumber = 0;
    while (getline(infile, line)) {             // while chạy từng line
        ++lineNumber;

       
        size_t pos = line.find(' ');
        string instruction = (pos == string::npos) ? line : line.substr(0, pos);
        string thamso = (pos == string::npos) ? "" : line.substr(pos + 1);

        try {
            runInstruction(instruction, lineNumber, thamso); // Thực thi lệnh
        } catch (TypeMisMatch& e) {             //check int 1-22, int float cac lenh con lai co xai i f
            cout << e.what() << endl;
            return;
        } catch (StackEmpty& e) {               // check pop
            cout << e.what() << endl;
            return;
        } catch (DivideByZero& e) {             //check o div va rem
            cout << e.what() << endl;
            return;
        } catch (StackFull& e) {                // check push
            cout << e.what() << endl;
            return;
        } catch (UndefinedVariable& e) { 
            cout << e.what() << endl;               //check o array
            return;
        } catch (ArrayOutOfRange& e) {          // xu ly cac lenh dung index
            cout << e.what() << endl;
            return;
        }
    }
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
        int index;
        index= stoi(thamso);
        iload(index,line);
    }
    else if (instruction == "fload") {
        int index;
        index= stoi(thamso);
        fload(index, line); 
    } 
    else if (instruction == "istore") {
        int index;
        index= stoi(thamso);
        istore(index,line);

    } else if (instruction == "fstore") {
        int index;
        index= stoi(thamso);
        fstore(index, line); 
    }
    else if (instruction == "val") {
        int index;
        index= stoi(thamso);
        val(index, line); 
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


void StackFrame::iload(int index,int line){
    if (index<0||index>=LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);
    int a=0;
    if (vs.getcode(index)==-1) throw UndefinedVariable(line);

    if (vs.getcode(index)==0) {
        a= vs.iget(index);
        if (OperandStack.getSize()>=OPERAND_STACK_MAX_SIZE) throw StackFull(line);
        else OperandStack.ipush(a);}
    
     if (vs.getcode(index)==1) throw TypeMisMatch(line);

}
void StackFrame::fload(int index,int line){
    if (index<0||index>=LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);
    float a=0;
    if (vs.getcode(index)==-1) throw UndefinedVariable(line);

    if (vs.getcode(index)==1) {
        a= vs.fget(index);
        if (OperandStack.getSize()>=OPERAND_STACK_MAX_SIZE) throw StackFull(line);
        else OperandStack.fpush(a);}
    if (vs.getcode(index)==0) throw TypeMisMatch(line);
    
}
void StackFrame::istore(int index,int line){
    if (OperandStack.empty()) throw StackEmpty(line);
    
    if(OperandStack.codeTop()==1) throw TypeMisMatch(line);
    else if (OperandStack.codeTop()==0){
            if (index<0||index>=LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);
            else {int a = OperandStack.itop();
            OperandStack.pop();
            vs.iset(a,index);}
    }
    
}
void StackFrame::fstore(int index,int line){
    if(OperandStack.empty()) throw StackEmpty(line);
    
    if(OperandStack.codeTop()==0) throw TypeMisMatch(line);

    else if (OperandStack.codeTop()==1){
            if (index<0||index>=LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);
            float a = OperandStack.ftop();
            OperandStack.pop();
            vs.fset(a,index);
    }
   
}

void StackFrame::val(int index, int line){
    if (index<0||index>=LOCAL_VARIABLE_ARRAY_SIZE) throw ArrayOutOfRange(line);
    if (vs.getcode(index)==-1) throw UndefinedVariable(line);
    if (vs.getcode(index)==0) cout<<vs.iget(index)<<endl;
    if (vs.getcode(index)==1) cout<<vs.fget(index)<<endl;

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
