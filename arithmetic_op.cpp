#include<bits/stdc++.h>
using namespace std;

int int_value(char c);

vector<int> pos_num; // vector to contain positive numbers only
vector<int> neg_num; // vector to contain negative numbers only

void operation(char f_s, char f_oprnd, char optr, char s_s, char s_oprnd )
{
    int res;    // calculated value which is to be pushed back in positive or negative vector according to the sign
    int sign;   // denotes positive and negative sign of the elements

    if(optr != '%'){

        if((f_s == '+' && s_s == '-') || (f_s == '-' && s_s == '+')) sign = -1;  // +- = -  || -+ = -
        else sign = 1;

        if(optr == '*') res = int_value(f_oprnd) * int_value(s_oprnd);  // operation to be performed according to the operator
        if(optr == '/') res = int_value(f_oprnd) / int_value(s_oprnd);  // operation to be performed according to the operator

        if(sign == 1) pos_num.push_back(res);               //if sign is positive the push the value to positive vector
        else if (sign == -1) neg_num.push_back(res);       //if sign is negative the push the value to negative vector
    }

    if(optr == '%'){

        if(s_s == '-') sign = -1;           // sign would be negative if right side operand is negative
        else if (s_s == '+' ) sign = 1;     // sign would be positive if right side operand is positive

        res = int_value(f_oprnd) % int_value(s_oprnd); // operation to be performed according to the operator

        if(sign == 1) pos_num.push_back(res);                //if sign is positive the push the value to positive vector
        else if (sign == -1) neg_num.push_back(res);         //if sign is negative the push the value to negative vector
    }
}
int int_value(char c) // converts a char in int value according to ascii table
{
    return c - 48;
}
int main()
{
    string s ;
    cin >> s;

    s.insert(0, "+");       //Inserts + symbol at the beginning

    for(int i = 0; i < s.size(); i++){
        if( s[ i ] >= '0' && s[ i ] <= '9' && (s[i - 1] == '/' || s[i - 1] == '*' || s[i - 1] == '%'))
            s.insert(i, "+");   //Insert + wherever there is no +/- symbol just before an number
    }

    for(int i = 0; i < s.size(); i++){
        if(s[i] == '/' || s[i] == '%' || s[i] == '*'){
            operation(s[i-2], s[i-1], s[i], s[i+1], s[i+2]);   // Performs arithmetic operation according to operator
            for(int j = 0; j < 5; j++) s.erase(s.begin() + (i - 2));  // deletes the 5 consecutive elements as with operator in middle to leave the string only with positive or negative numbers which are to be pushedback to postive and negative vectors later
            i = 0;  //resets i = 0 for detection of each and every symbol in the string
        }
    }

    for(int i = 0; i < s.size(); i++){
        if(s[i] == '+')
            pos_num.push_back( int_value( s[i+1] ) ); //push positive numbers to positive vector after conversion from char to int
        else if(s[i] == '-')
            neg_num.push_back( int_value( s[i+1] ) ); // push negative numbers to negative vector after conversion from char to int
    }

    int neg_acc = accumulate(neg_num.begin(), neg_num.end(), 0);  // Adds all the elements of the positive vector
    int pos_acc = accumulate(pos_num.begin(), pos_num.end(), 0);  // Adds all the elements of the negative vector

    int answer = pos_acc - neg_acc;

    cout  << "The answer of arithmetic erpression : " << answer << endl;
    return 0;
}

