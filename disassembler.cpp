#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>
#include <utility>
#include <iterator>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include <iomanip>
#define ll long long
using namespace std;
string SICops[] = {"18","40","28","24","3C","30","34","38","48","00","50","08","04","20","44","D8","4C","0C","54","14","E8","10","1C","E0","2C","DC"};
    int SICop[26];
    // convert hex strings into integers
    
pair<string, int> SICXEops[] = {
        make_pair("18", 3), make_pair("58", 3), make_pair("90", 2), make_pair("40", 3),
        make_pair("B4", 2), make_pair("28", 3), make_pair("88", 3), make_pair("A0", 2),
        make_pair("24", 3), make_pair("64", 3), make_pair("9C", 2), make_pair("C4", 1),
        make_pair("C0", 1), make_pair("F4", 1), make_pair("3C", 3), make_pair("30", 3),
        make_pair("34", 3), make_pair("38", 3), make_pair("48", 3), make_pair("00", 3),
        make_pair("68", 3), make_pair("50", 3), make_pair("70", 3), make_pair("08", 3),
        make_pair("6C", 3), make_pair("74", 3), make_pair("04", 3), make_pair("D0", 3),
        make_pair("20", 3), make_pair("60", 3), make_pair("98", 2), make_pair("C8", 1),
        make_pair("44", 3), make_pair("D8", 3), make_pair("AC", 2), make_pair("4C", 3),
        make_pair("A4", 2), make_pair("A8", 2), make_pair("F0", 1), make_pair("EC", 3),
        make_pair("0C", 3), make_pair("78", 3), make_pair("54", 3), make_pair("80", 3),
        make_pair("D4", 3), make_pair("14", 3), make_pair("7C", 3), make_pair("E8", 3),
        make_pair("84", 3), make_pair("10", 3), make_pair("1C", 3), make_pair("5C", 3),
        make_pair("94", 2), make_pair("B0", 2), make_pair("E0", 3), make_pair("F8", 1),
        make_pair("2C", 3), make_pair("B8", 2), make_pair("DC", 3)
    };
    pair<string, string> SICXEinst[] = {
        make_pair("18", "ADD"), make_pair("58", "ADDF"), make_pair("90", "ADDR"), make_pair("40", "AND"),
        make_pair("B4", "CLEAR"), make_pair("28", "COMP"), make_pair("88", "COMPF"), make_pair("A0", "COMPR"),
        make_pair("24", "DIV"), make_pair("64","DIVF"), make_pair("9C", "DIVR"), make_pair("C4", "FIX"),
        make_pair("C0", "FLOAT"), make_pair("F4", "HIO"), make_pair("3C", "J"), make_pair("30", "JEQ"),
        make_pair("34", "JGT"), make_pair("38", "JLT"), make_pair("48", "JSUB"), make_pair("00", "LDA"),
        make_pair("68", "LDB"), make_pair("50", "LDCH"), make_pair("70", "LDF"), make_pair("08", "LDL"),
        make_pair("6C", "LDS"), make_pair("74", "LDT"), make_pair("04", "LDX"), make_pair("D0", "LPS"),
        make_pair("20", "MUL"), make_pair("60", "MULF"), make_pair("98", "MULR"), make_pair("C8", "NORM"),
        make_pair("44", "OR"), make_pair("D8", "RD"), make_pair("AC", "RMO"), make_pair("4C", "RSUB"),
        make_pair("A4", "SHIFTL"), make_pair("A8", "SHIFTR"), make_pair("F0", "SIO"), make_pair("EC", "SSK"),
        make_pair("0C", "STA"), make_pair("78", "STB"), make_pair("54", "STCH"), make_pair("80", "STF"),
        make_pair("D4", "STI"), make_pair("14", "STL"), make_pair("7C", "STS"), make_pair("E8", "STSW"),
        make_pair("84", "STT"), make_pair("10", "STX"), make_pair("1C", "SUB"), make_pair("5C", "SUBF"),
        make_pair("94", "SUBR"), make_pair("B0", "SVC"), make_pair("E0", "TD"), make_pair("F8","TIO"),
        make_pair("2C", "TIX"), make_pair("B8", "TIXR"), make_pair("DC", "WD")
    };
    pair<int,int> SICXEop[59]; // convert hex to int
    pair<int,string> SICXEInst[59];

int check_opcode_in_SICXE(int op){
    int l = -1; // to return the no of bytes
    int i;
    for(i=0;i<59;i++){
        if(op == SICXEop[i].first){
            l = SICXEop[i].second;
            return l;
        }
    }
    return l;
}
int findop(string s){
    string t= s.substr(0,2);
    return stoi(t,0,16);
}
bool check_opcode_in_SIC(int op){
    bool t= false;
    int i;
    for(i=0;i<26;i++)
    {
        
        if(op == SICop[i]){
            t=true;
            return t;
        }
    }
    return t;
}
string check_validity(string s){
    int i;
    // string s;
     // take input of string in hex
    
    int n = s.length()/2; // here n is number of bytes
    int op = findop(s); // this give the op code with n and i
    if(s.length()%2 == 1 || n>4){ // check for invalid lenght
       return "Invalid: This is an Invalid lenght";
        
    }
    

    if(op%4==0 && n==3){ // this means it is an SIC instruction
          
        if(!check_opcode_in_SIC(op)){ // check if the opcode is present or not
        // cout<<op<<endl;
            return"Invalid: This opcode is not present in the list of SIC instructions";
            
        }
        if(op == 76){ // case for RSUB
            if(s.substr(2,4) != "0000"){
                return "Invalid: The operand in RSUB should be zero";
                
            }
            
        }
        
        return "Valid"; // all cases passed for an SIC instruction
        // return;
        
    }
    if(op%4==0 && n==4){
        return "Invalid: SIC instruction cannot have 4 bytes";
        
    }
    
    
    // means it is an SICXE instruction
        int op2 = op - (op%4);
        int max_byte = check_opcode_in_SICXE(op2); // (type number) this funtion returns the max allowable bytes for an instruction
        if(max_byte == -1){
            return "Invalid: This opcode is not present in the list of SICXE instructions";
            
        }
        //case for RSUB
        if(op == 79 ){
            if(s.substr(2,4) != "0000"){
                return "Invalid: The operand in RSUB should be zero";
               
            }
            
        }
        if(op2 == 76 ){
            return "Invalid: RSUB can only have both n and i set";
            
        }
        if(max_byte == 1){ // if it is type-1 
            if(n!=1){
                return "Invalid: This is a type-1 instructions i.e it must have only 1 byte but it has ";
                
            }
            return"Valid";
            
        }

        if(max_byte == 2){ //if it is type-2
            if(n!=2){
                return "Invalid: This is a type-2 instructions i.e it must have only 1 byte but it has  bytes";
                
            }
            if(op%4 !=0){
                return "Invalid: a format two instruction's opcode should be a multiple of 4";
            }
            
            if(op2 ==  stoi("B0",0,16)){ // for SVC case it is always valid
                return "Valid";
                // return;
            }
            if(op2 == stoi("A4",0,16) ||op2 == stoi("A8",0,16)){ // shift instructions
                int r1 = stoi(s.substr(2,2),0,16);
                if((r1>9||r1==7)){
                    return "Invalid: this is an invalid register value";
                    
                }else{
                    if(r1 == 6 ){ // register-register cant have floating point numbers
                    return "Invalid: these register instructions doesnot suppport floating point numbers";
                    
                }
                }
                return "Valid";
                
            }
            // register-register cases
            int r1 = stoi(s.substr(2,1),0,16);
            int r2 = stoi(s.substr(3,1),0,16);
            if(op2 == 184 || op2 == 180){
                if(r2!=0){
                    return "Invalid: r2 value should be zero for CLEAR and TIXR instructions";
                    
                }else{
                    if((r1>9||r1==7)){
                        return "Invalid: this is an invalid register value";
                        
                    }else{
                        if(r1 == 6 || r2 == 6){// register-register cant have floating point numbers
                        return "Invalid: these register instructions doesnot suppport floating point numbers";
                        
                }
                    }
                }
            }
            if((r1>9||r1==7) || (r2>9||r2==7)){ // check for validity of registers P.S i took the case that it is theroitically possible to access status and PC registers also 
                return"Invalid: this is an invalid register value";
                
            }else{
                if(r1 == 6 || r2 == 6){
                    return"Invalid: these register instructions doesnot suppport floating point numbers";
                    
                }
            }
            return"Valid";
            
        }
        if(max_byte == 3){
            
            if (n==3 || n==4 ){ // check for max_bytes for type 3

            }else{
                return "Invalid: This is a type-3 instructions i.e it must have only 1 byte but it has  bytes";
            }
            // get the values of nixbpe
            int ni = op%4;
            int i = ni%2;
            // int n = (ni>>1)%2;
            int xbpe = stoi(s.substr(2,1),0,16);
            
            int e = xbpe%2;
        
            int p = (xbpe>>1)%2;
            int b = (xbpe>>2)%2;
            int x = (xbpe>>3)%2;
            if(x== 1 && ni !=3){
                return "Invalid: X addressing cant be used with immediate";
            }

            // case where x =1 but no of bytes do not match or when x=0 and bytes do not match
            if(e==0&&n==4){
                return "Ivalid: here x is set to 0 but has lenght of 4 bytes";
                
            }
            if(e==1 && n==3){
                return "Ivalid: here x is set to 1 but has lenght of 3 bytes";
                
            }
            // the case where e == 1 but p and p are set
            if(e==1 && b+p!=0){
                return "Invalid: here used type 4 but b, p are not set to zero";
                
            }
            // the case where both b and p are set
            if(b==1 && p==1){
                return "Invalid: both b and p are set to 1 i.e attempting to use both base and PC relative";
                
            }
            // the case where c x=1 can only be used in simple addressing
            if(((n==0&&i==1)||(n==1&&i==0))&&(x==1)){
                return "Invalid: x==1 can only be used in simple addressing";
            }
            // all cases passed
            return "Valid";
            

            

        }
        return "Valid";

}

class State{
public:
    bool isMem;
    bool isX;
    bool opisLit;
    string LabelSuf;
    string LabelPre;
    string inst;
    string lit;
    int reg[2];
    int format;
    int borp;
    int type; // 1 -> immediate , 2 -> indirect, 3/0 -> simple;
    bool x;
    bool base;
    bool opisLab;
    int Oper;
    string memType; // RESW or Word ot RESB or BYTE
    string objectCode;
    ll mem;
public:
    State(){
        opisLit = false;
        isMem = false;
        lit="";
        isX = false;
        LabelSuf = "";
        LabelPre = "";
        inst = "";
        opisLab = false;
        Oper = -1;
        objectCode = "";
        format = 0;
        base = false;

    }

public:
    




};

int return_format(int op){
    int l = -1; // to return the no of bytes
    int i;
    for(i=0;i<59;i++){
        if(op == SICXEop[i].first){
            l = SICXEop[i].second;
            return l;
        }
    }
    return l;
}

string return_inst(int op){
    string l = ""; // to return the no of bytes
    int i;
    for(i=0;i<59;i++){
        if(op == SICXEInst[i].first){
            return SICXEInst[i].second;
        }
    }
    return l;
}



void solve(map<ll,State> &ins,vector <pair<ll,ll> > text,map <ll, pair<string,string> > symtab,string mem[], ll tot, ll fiest,ll stAddr,bool check[], ll &B,map <ll, pair<string,ll> > littab){
    
    ll cur = fiest;
    while(cur <= tot && cur>=stAddr){
        // loop breaks when RSUB is encountered and not in Sub routine
        
       
        if((mem[cur] == "4F" || mem[cur] == "4C")){
            
            if(mem[cur+1] != "00" || mem[cur+2] !="00"){
                cout<<"Invalid RSUB instruction"<<endl;
                return;
            }
            // if no error create obj and store
            State st = State();
            st.inst = "RSUB";
            // if any label assigned
            if(symtab.find(cur) != symtab.end()){
                st.LabelPre = symtab[cur].first;
            }
            ins[cur] = st;
            check[cur] = true;
            check[cur+1] = true;
            check[cur+2] = true;
            cur +=2;
            // break;
            
            return;
        }
        
        
        ll op = stoi(mem[cur],0,16);
      
        ll opr = op - (op%4);
        if(!check_opcode_in_SICXE(opr)){
           
            return ;

        }

        ll ni = op%4;
        State st = State();
        ll format = return_format(opr);
        string obj;
        switch(format){
            case 1:
                obj = mem[cur];
                break;
            case 2:
                obj = mem[cur]+mem[cur+1];
                break;
            case 3:
                
                if(op %4 ==0){
                    obj = mem[cur]+mem[cur+1]+mem[cur+2];
                }else{
                    
                    if(stoi(mem[cur+1].substr(0,1),0,16)%2 == 1){
                    obj = mem[cur]+mem[cur+1]+mem[cur+2]+mem[cur+3];
                }else{
                    obj = mem[cur]+mem[cur+1]+mem[cur+2];
                }

                }
                
                break;

        }
        string res = check_validity(obj);
        cout<<obj<<endl;
        cout<<res<<endl;
        
        st.format = format;
        st.inst = return_inst(opr);
        cout<<st.inst<<endl;
        cout<<"\n";
        //check for labels
        if(symtab.find(cur) != symtab.end() && symtab[cur].second != "A"){
                st.LabelPre = symtab[cur].first;
            }
        
        // case if the inst is format-1  
        if(format == 1){
            string ch = mem[cur]; // pass through checker
            st.objectCode = ch;
            // do nothing all already assigned
            check[cur] = true;
            // cur++;
        }else{
            if(format == 2){
                // fill the registers
                //if TIXR it takes only r1
                string ch = mem[cur]+mem[cur+1]; // pass through checker
                st.objectCode = ch;
                
                if(opr == 184 || opr == 180){
                    st.reg[0] = stoi(mem[cur+1].substr(0,1),0,16);
                    st.reg[1] = -1;
                }else{ // rest all takes two reg values
                    st.reg[0] = stoi(mem[cur+1].substr(0,1),0,16);
                    st.reg[1] = stoi(mem[cur+1].substr(1,1),0,16);
                }
                check[cur] = true;
                check[cur+1] = true;
                check[cur+2] = true;
                
                // cur +=2;
            }else{ // for format 3 and 4
                // get x,b,p,e
                if(ni == 0){ // SIC instrction
                    st.format = 3;
                    
                    ll ta = stoi(mem[cur+1]+mem[cur+2],0,16);
                    // ll x = (ta >> 15)%2;
                    ll x = ta &(0x8000);
                    if( x == 0x8000){
                        
                        st.isX = true;
                    }
                  
                    ta  = ta &(0x7FFF);
               
                    st.opisLab = true;
                    if(symtab.find(ta) != symtab.end()){
                    st.LabelSuf = symtab[ta].first;
                    }
                    check[cur] = true;
                    check[cur+1] = true;
                    check[cur+2] = true;
                    ins[cur] = st;
                    if(opr == 60 || opr == 48 || opr == 52 || opr == 56 || opr == 72 ){
                    if(!check[ta]){
                        
                        solve(ins,text,symtab,mem,tot,ta,stAddr,check,B,littab);
                    }
                    }

                    cur += 3;
                    continue;
                }else{
                    
                ll xbpe = stoi(mem[cur+1].substr(0,1),0,16);
                int e = xbpe %2;
                int p = (xbpe >> 1)%2;
                int b = (xbpe >> 2)%2;
                int x = (xbpe >> 3)%2;
                if(x==1){
                    st.isX = true;
                }
                //check cases for ni ;
                st.type = ni; // 1 -> immediate , 2 -> indirect, 3/0 -> simple;
                ll disp;
                ll next;
                if(e == 1){
                    st.objectCode = mem[cur]+mem[cur+1]+mem[cur+2]+mem[cur+3];
                    st.format = 4;
                    
                    
                    string dis = mem[cur+1].substr(1,1) + mem[cur+2] + mem[cur+3];
                 
                    disp = stoi(dis,0,16);
                    if(disp>0x80000){
                        disp = disp - 0xFFFFF-1;
                    }
                    next = cur +4;
                    // disp = 
                }else{
                    st.objectCode = mem[cur]+mem[cur+1]+mem[cur+2];
                    st.format = 3;
                    string dis = mem[cur+1].substr(1,1) + mem[cur+2];
               
                    disp = stoi(dis,0,16);
                    if(disp>0x800){
                        disp = disp - 0xFFF-1;
                    }
                    next = cur+3;
                 
                }
                
                ll ta = disp ;// for simple and direct
          
                if(p == 1){
                    ta +=next;
                }
                if(b == 1){
                    // later
                    ta +=B;
                }
                // check is there is a label for the tA
            
                if(symtab.find(ta) != symtab.end()){
                    st.opisLab = true;
                    st.LabelSuf = symtab[ta].first;
                }else{
                    if(littab.find(ta) != littab.end()){
                        
                        st.opisLit = true;
                        st.lit = littab[ta].first;
                      
                        

                        
                    }else{
                        st.opisLab = false;
                        st.Oper = ta;
                    }
                    
                }
                // calculate base
                if(opr == 104){
                    if(st.type == 0 || st.type == 3){
                        string hel = mem[ta]+mem[ta+1]+mem[ta+2];
                        
                        B = stoi(hel, 0,16);
                    }else{
                        if(st.type == 1){
                            B = ta;
                        }else{
                            if(st.type == 2){
                                string hel = mem[ta]+mem[ta+1]+mem[ta+2];
                                
                                ll newTa = stoi(hel, 0,16);
                                hel =  mem[newTa]+mem[newTa+1]+mem[newTa+2];
                               
                                B = stoi(hel, 0,16);

                            }
                        }
                    }
                }
                

                check[cur] = true;
                check[cur+1] = true;
                check[cur+2] = true;
                if(e==1){
                    check[cur+3] = true;
                }
                // for jump intructions check
                if(opr == 60 || opr == 48 || opr == 52 || opr == 56 || opr == 72 ){
                    
                   
                    if(!check[ta]){
                     
                        solve(ins,text,symtab,mem,tot,ta,stAddr,check,B,littab);
                    }
                }
               
                }
               
            }
        }
        ins[cur] = st;
        
        cur+=st.format;

    }
    // now assign memory

}

void assignMemory(map<ll,State> &ins,vector <pair<ll,ll> > text,map <ll, pair<string,string> > symtab,string mem[], ll tot, ll fiest,ll stAddr,bool check[], ll &B,vector<ll> dataSeq,map <ll, pair<string,ll> > littab){
    // iterate through checks and assignmemory
 
    ll i;
    
    for(i=stAddr;i<tot;i++){
        if(check[i]){
            continue;
        }else{
            
            
            State st = State();
            st.isMem = true;
            if(symtab.find(i) != symtab.end()){
                st.LabelPre = symtab[i].first;
            }
                if(littab.find(i) != littab.end()){
                  
                    st.LabelPre = "*";
                    st.memType = littab[i].first;
                    st.mem = 0;
                    int k;
                    for(k=i;k<i+littab[i].second;k++){
                        check[k] =true;
                    }
                    ins[i] = st;
                    continue;
                }
            
            ll c=0;
            ll cur = i;
            if(mem[cur] == "" && cur <=tot-1 ){
                cur++;
                c++;
                check[cur] = true;

                
                while(mem[cur] == "" && cur <=tot-1 && symtab.find(cur) == symtab.end()){
                    
                    check[cur] = true;
                    cur++;
                    c++;
                }
                
                if(c % 3 == 0){
                st.memType = "RESW";
                st.mem = c/3;
                }else{
                st.memType = "RESB";
                st.mem = c;
                }
                
                

                
                
            }else{
                
                check[cur] = true;
                string p = "";
                p+=mem[cur];
                cur++;
                c++;
                while((symtab.find(cur) == symtab.end())&& cur <=tot-1){
                    check[cur] = true;
                    p = p +mem[cur];
                    cur++;
                    c++;
                    
                }
                if(c ==3 ){
                st.memType = "WORD";
                }else{
                st.memType = "BYTE";
                }
               
                st.mem = stoi(p,0,16);

            }
            ins[i] = st;
            
        }
    }

}

string get_reg(int n){
    switch(n){
        case 0: 
            return "A";
        case 1:
            return "X";
        case 2:
            return "L";
        case 3:
            return "B";
        case 4:
            return "S";
        case 5:
            return "T";
        case 6:
            return "F";
        default:
            return "None";
    }
}

void print_inst(State st, ofstream out){
    if(!st.isMem){
        string s = st.inst;
        if(st.format == 4){
            s = "+"+s;
            
        }
        string operand;
        switch(st.format){
            case 1: operand = "";
            break;
            case 2: 
                if(st.reg[1] == -1){
                    operand = get_reg(st.reg[0]);
                }else{
                    operand = get_reg(st.reg[0])+" ,"+get_reg(st.reg[1]);

                }
                break;
            case 3:
                if(st.opisLab){
                    operand += st.LabelSuf;

                }else{
                    operand +=to_string(st.Oper);

                }
                break;
            case 4:
                if(st.opisLab){
                    operand += st.LabelSuf;

                }else{
                    operand +=to_string(st.Oper);

                }
                break;
            default:
                break;

        }
        switch(st.type){
            case 1:
                operand = "#" + operand;
                break;
            case 2:
                operand = "@" + operand;
                break;
            default:
                break;
            }
        if(st.isX){
            operand +=", X";
        }
        out<<setw(10)<<st.LabelPre<<setw(10)<<s<<setw(10)<<operand<<endl;
        if(st.inst == "LDB"){
             out<<setw(10)<<st.LabelPre<<setw(10)<<s<<setw(10)<<operand<<endl;

        }

    }else{


        out<<setw(10)<<st.LabelPre<<setw(10)<<st.memType<<setw(10)<<st.mem<<endl;

    }
}

int main(){
 
    ll i;
    for(i=0;i<26;i++){
        SICop[i]=stoi(SICops[i],0,16);
    }
    for(i=0;i<59;i++){
        SICXEop[i].first = stoi(SICXEops[i].first,0,16);
        SICXEop[i].second = SICXEops[i].second;
        
        SICXEInst[i].first = stoi(SICXEinst[i].first,0,16),
        SICXEInst[i].second = SICXEinst[i].second;

    }
    
    //setting in and out

    ofstream out;
    out.open("output.txt");
    ifstream in;
    in.open("input.txt");
    ll size; // in bytes
    string s;
    in>>s;
    // header record
    string name  ;
    
    ll stAddr ;
    
    if(s.length()<7){
        if(s.length() <2){
            cout<<"INVALID header length"<<endl;
        }
        name = s.substr(1,s.length()-1);
        string k;
        in>>k;
        for(int j=0;j<7;j++){
            k = "*"+k;
        }
        if(k.length() != 19){
            cout<<"INVALID header length"<<endl;
        }
        size = stoi(k.substr(13,6),0,16);
        stAddr = stoi(k.substr(7,6),0,16);

    }else{
        if(s.length() != 19){
            cout<<"INVALID header length"<<endl;
        }
    name = s.substr(1,6);
    size = stoi(s.substr(13,6),0,16);
    stAddr = stoi(s.substr(7,6),0,16);

    }
    cout<<"header done"<<endl;
    

    ll tot = stAddr+size;
    ll B;
    
    string mem[tot]; // store all bytes
    bool check[tot];
    for(i=0;i<tot;i++){
        mem[i]="";
        check[i] = false;
    }
    vector <pair<ll,ll> > text;
    ll feinst;
    // text record
    int e=0;
    while(true){
        in>>s;
        if(s.length() <3){
            cout<<"no end record"<<endl;
        }
        if(s[0] == 'M'){
            continue;
        }
        if(s[0] == 'E'){
            e++;
            break;
        }
        if(s.length() > 69){
            cout<<"error text record cannot have more than 69 columns"<<endl;
        }
        
        ll st = stoi(s.substr(1,6),0,16);
        ll len = stoi(s.substr(7,2),0,16);
        text.push_back(make_pair(st,len)); // store text record start and end
        ll max = s.length();
        if((s.length()-9 )%2 !=0 ||(s.length()-9 )/2 != len){
            cout<<"INVALID text record length"<<endl;
        }

        ll cur = 9;
        while(cur<=max){
            mem[st] = s.substr(cur,2);
            cur+=2;
            st++;
        }
        


    }
    if(e==0){
        cout<<"no end record";
    }
    if(s[0] == 'E'){
        if(s.length()!=7){
            cout<<"Invalid end record lenght"<<endl;
        }
        feinst = stoi(s.substr(1,6),0,16);
    }
    map <ll, pair<string,string> > symtab;
    int n;
    in>>n;
    for(i=0;i<n;i++){
        string s,v,c;
        in>>s>>v>>c;
        symtab[stoi(v,0,16)] = make_pair(s,c);
    }
    map<ll,pair<string,string> > :: iterator tt;
    vector<ll> dataSeq;
    for(tt = symtab.begin();tt!=symtab.end(); ++tt){
        dataSeq.push_back(tt->first);
        
    }
    map <ll, pair<string,ll> > littab;
    //take number for literals
    int k;
    in>>k;
   
    for(i=0;i<k;i++){
        string lit,add;
        ll len;
        in>>lit>>len>>add;
        // literals
        
        littab[stoi(add,0,16)] = make_pair(lit,len);
    }
   
    map <ll, pair<string,ll> >::const_iterator it1;
    





    // upto this point we have the entire memory i.e the text records the start of each text records lengths, symTab etc
    //now start processing
    


    map <ll,State> ins;
    // to the solve function I need to pass a map to store an obj for each location, the symtab, the memory, (Sic things are slready present outside), the first executable instruction
    



solve(ins,text,symtab,mem,tot,feinst,stAddr,check,B,littab);


// for(i=0;i<tot;i++){
//     cout<<mem[i]<<" ";
// }
// cout<<"\n";
// for(i=0;i<tot;i++){
//     cout<<check[i]<<" ";
// }
assignMemory(ins,text,symtab,mem,tot,feinst,stAddr,check,B,dataSeq,littab);

    
    out<<setw(10)<<name<<setw(10)<<"FIRST"<<setw(10)<<stAddr<<endl;
    map<ll,State> :: iterator it;

    for(it = ins.begin();it!=ins.end(); ++it){
        // print_inst(it->second,out);
        State st = it->second;
        if(!st.isMem){
        string s = st.inst;
        if(st.format == 4){
            s = "+"+s;
            
        }
        string operand;
        switch(st.format){
            case 1: operand = "";
            break;
            case 2: 
                if(st.reg[1] == -1){
                    operand = get_reg(st.reg[0]);
                }else{
                    operand = get_reg(st.reg[0])+" ,"+get_reg(st.reg[1]);

                }
                break;
            case 3:
                if(st.opisLab){
                    operand += st.LabelSuf;

                }else{
                    operand +=to_string(st.Oper);

                }
                break;
            case 4:
                if(st.opisLab){
                    operand += st.LabelSuf;

                }else{
                    operand +=to_string(st.Oper);

                }
                break;
            default:
                break;

        }
        switch(st.type){
            case 1:
                operand = "#" + operand;
                break;
            case 2:
                operand = "@" + operand;
                break;
            default:
                break;
            }
        if(st.isX){
            operand+=", X";
        }
        if(st.opisLit){
            operand = st.lit;
        }

        out<<setw(10)<<st.LabelPre<<setw(10)<<s<<setw(10)<<operand<<endl;
        if(st.inst == "LDB"){
            if(symtab.find(B) != symtab.end()){

                out<<setw(10)<<""<<setw(10)<<"BASE"<<setw(10)<<symtab[B].first<<endl;
            }else{
                out<<setw(10)<<""<<setw(10)<<"BASE"<<setw(10)<<B<<endl;
            }
        }

    }else{

        if(st.LabelPre == "*"){
            out<<setw(10)<<st.LabelPre<<setw(10)<<st.memType<<setw(10)<< " "<<endl;

        }else{

        out<<setw(10)<<st.LabelPre<<setw(10)<<st.memType<<setw(10)<< st.mem<<endl;
        }


    }
        
    }
    // print all absolute ones
    

    map<ll,pair<string,string> > :: iterator it3;
    for(it3 = symtab.begin();it3!= symtab.end();++it3){
     
        if(it3->second.second == "A"){  
            out<<setw(10)<<it3->second.first<<setw(10)<<"EQU"<<setw(10)<<it3->first<<endl;

        }

    }
    
    out<<setw(10)<<""<<setw(10)<<"END"<<setw(10)<<symtab[feinst].first<<endl;

    

    cout<<"Check output file"<<endl;
   



}



