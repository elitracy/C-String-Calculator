// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl, std::stoll;
bool stringMax(my_string, my_string);

unsigned int digit_to_decimal(char digit) {
    // TODO(student): put your existing implementation here
    int output = digit - 48;

    if(!(std::isdigit(digit))){
        throw std::invalid_argument("invalid argument");
    }
    return output;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): put your existing implementation here
    
    if(decimal > 9){
        throw std::invalid_argument("invalid argument");
    }
    
    char out = '0' + decimal;

    return out;
}

my_string trim_leading_zeros(const my_string& num) {
    // TODO(student): put your existing implementation here

    my_string temp = num;
    if(temp[0] == '-' && temp[1] == '0'){

        int i = 1;
        while(temp[i] == '0'){
            i++;
        }

        temp.erase(1,i);

    }
    
    if(temp[0] == '0'){
        int i = 0;
        while(temp[i] == '0'){
            i++;
        }
        temp.erase(0,i);
    }
    // cout << temp.length() << endl;
    if(temp.length() == 0 || (temp[0] == '-' && temp.length() == 1)){
        temp = "0";
    }
    // num = temp2;
    if(temp.length() == 1 && temp[0] == '\0'){
        temp = "0";
    }
     
    return temp;
}

my_string add(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    my_string tempLHS = trim_leading_zeros(lhs);
    my_string tempRHS = trim_leading_zeros(rhs);
    cout << "ADD: " << tempLHS << " " << tempRHS << endl;
    int tempSum = 0;
    int carry = 0;
    int intNumOne = 0;
    int intNumTwo = 0;
    int i = 0;
    bool lhsSign = true;
    bool rhsSign = true;
    my_string sum = "";
    
    if(tempLHS[0] == '-'){
        //lhs is negative
        lhsSign = false;
        tempLHS.erase(0,1);
    }

    if(tempRHS[0] == '-'){
        //rhs is negative
        rhsSign = false;
        tempRHS.erase(0,1);
    }
    
    if(tempLHS.length() > tempRHS.length()){
        //add zeros to beginning of number
        int difference = tempLHS.length() - tempRHS.length();
        while(difference != 0){
            tempRHS.insert(0,"0");
            difference--;
        }
    }
    if(tempLHS.length() < tempRHS.length()){
        //add zeros to beginning of number
        int difference = tempRHS.length() - tempLHS.length();
        
        while(difference != 0){
            tempLHS.insert(0,"0");
            difference--;
        }
    }

    if(!(lhsSign ^ rhsSign)){

        for(i = tempLHS.length()-1; i >= 0; i--){
        intNumOne = tempLHS[i] - 48;
        intNumTwo = tempRHS[i] - 48;
        
            tempSum = intNumOne + intNumTwo + carry;
            //determine if there is a remainder.
            if(tempSum > 9){
                carry = 1;
                tempSum -= 10;
            }else{
                carry = 0;
            }

            sum.insert(0,to_string(tempSum));

            if(i == 0 && carry == 1){
                sum.insert(0,"1");
            }
        }

        //cout << sum << endl;
        if(!lhsSign && !rhsSign){
            sum.insert(0,"-"); 
        }

        return trim_leading_zeros(sum);

    }else{

        if(!lhsSign && rhsSign){
            if(stringMax(tempLHS,tempRHS)){
                sum = subtract(tempLHS,tempRHS).insert(0,"-");
            }else{
                sum = subtract(tempRHS,tempLHS);
            }

        }else if(lhsSign && !rhsSign){
            if(stringMax(tempLHS,tempRHS)){
                sum = subtract(tempLHS,tempRHS);
            }else{
                sum = subtract(tempRHS,tempLHS).insert(0,"-");
            }
        }
        
        return trim_leading_zeros(sum);
    } 
}

my_string subtract(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    my_string tempLHS = trim_leading_zeros(lhs);
    my_string tempRHS = trim_leading_zeros(rhs);

    cout << "SUBTRACT: " << tempLHS << " " << tempRHS << endl;

    my_string sum = "";
    bool lhsSign = true;
    bool rhsSign = true;
    int difference;

    if(tempLHS[0] == '-'){
        //lhs is negative
        lhsSign = false;
        tempLHS.erase(0,1);
    }

    if(tempRHS[0] == '-'){

        //rhs is negative
        rhsSign = false;
        tempRHS.erase(0,1);
    }

    if(!(lhsSign ^ rhsSign)){

        //swap to put larger value on top
        bool swapped = false;
        if(!stringMax(tempLHS,tempRHS)){
            my_string tempString = tempRHS;
            tempRHS = tempLHS;
            tempLHS = tempString;
            swapped = true;
        }

        //put leading zeros on bottom number
        difference = tempLHS.length() - tempRHS.length();

        cout << tempLHS << " " << tempRHS << endl;
        cout << tempLHS.length() << " " << tempRHS.length() << endl;
        cout << difference << endl;

        while(difference != 0){
            tempRHS.insert(0,"0");
            difference--;
            
        }
        for(int i = tempLHS.length()-1; i >= 0; i--){

            int m = tempLHS[i] - 48;
            int l = tempRHS[i] - 48;
            int n = 0;

            cout << "SUM: " << sum << endl;
            //if result of subtraction is below zero, then pull from digit to the left
            if(m-l < 0){
            
                //check if last digit in num1
                if (i == 0){
                    //cout << "last digit" << endl;
                    sum.insert(0,to_string((m-l)));

                }else{
                        //add 10 to number being subtracted from
                    m += 10;
                    sum.insert(0,to_string(m-l));
                    //search for first non-zero number
                    int j = 1;
                    while(i-j > 0 && tempLHS[i-j] == '0'){
                        // +1 to each 0 index
                        n = tempLHS[i-j] - 39;
                        tempLHS[i-j] = n + '0';   
                        j++;
                    }
                    //subtract one from last index 1 is pulled from
                    n = tempLHS[i-j] - 49;
                    tempLHS[i-j] = n + '0';
                }
            }else{
                    sum.insert(0,to_string(m-l));
            }
    }

        //if both values are true
        if(lhsSign && rhsSign){

            if(swapped){
                sum.insert(0,"-");
            }    

        //if both are negative
        }else if(!lhsSign && !rhsSign){

            if(!swapped){
                sum.insert(0,"-");
            } 
        }
    }else{

        if(!lhsSign && rhsSign){
            sum = add(tempLHS,tempRHS).insert(0,"-");
        }else if(lhsSign && !rhsSign){
            sum = add(tempLHS,tempRHS);

        }

    }
        
    return trim_leading_zeros(sum);
} 

my_string multiply(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    
    my_string tempLHS = trim_leading_zeros(lhs);
    my_string tempRHS = trim_leading_zeros(rhs);
    long long temp = 0;

    bool lhsSign = true;
    bool rhsSign = true;

    if(tempLHS[0] == '-'){
        lhsSign = false;
        tempLHS.erase(0,1);
    }
    if(tempRHS[0] == '-'){
        rhsSign = false;
        tempRHS.erase(0,1);
    }

    long long newLHS = std::atoi(tempLHS.getData());
    long long newRHS = std::atoi(tempRHS.getData());

    if(!(lhsSign ^ rhsSign)){
        temp = newLHS * newRHS;
        return to_string(temp);
    }else{
        cout << -1*newLHS*newRHS << endl;
        temp = -1*newLHS*newRHS;
        return to_string(temp);
    }
}

bool stringMax(my_string lhs, my_string rhs){
    //lhs larger = 1
    //rhs larger = 0



    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    if(lhs.length() == rhs.length()){
        
        int lengthyBoi = lhs.length();

        for(int i = 0; i < lengthyBoi; i++){
            if(int(lhs[i] - '0') > (rhs[i] - '0')){
                return true;

            }else if((lhs[i] - '0') < (rhs[i] - '0')){

                return false;
            }
        }    

    }else if(lhs.length() > rhs.length()){
        return true;

    }else{
        return false;
    }
    return true;
}
