//This program is basicaly a simple calculator.
//it takes two int and a mode for the type of calculation (at runtime)
//it check is the given ints can be used to perform the selected calculation
//finally it print the arguments given (int A, int B, and the mode selected) alongside the result

//I tried to not terminate the programms and try to always give result as requested


//#include "std_lib_facilities.h"

#include <iostream>
#include <cmath> // Include the <cmath> header for math functions
using namespace std; // Add the std namespace
string s_mode; // we need this because if a mode imput is incorect then it changes in the function and caned be printed by main


// error() simply disguises throws:
inline void error(const string& s)
{
    throw runtime_error(s);
}

//FastCalculate checks the mode and with the nesessery eceptions performs the selected calculation
//it changes the global string s_mode to the final mode selected (it can change in the function)
//the last one is really not nassasary and can be removed to avoid the global variable
int FastCalculate (int a, int b, int mode){
    try{// cheking the mode given
        if ( !(mode >= 1 && mode <= 5 ) ) throw mode; //if inalide mode we throw the mode 
    }
    catch (int mode){ //catch the invalid mode and we give the user the option for another try 
        cerr << "Invilide mode. Mode muse be a number between 1 and 5, and you gave: " << mode << "\nif you would like to try again give a new mode imput (see menu above) or else give 0 to terminate the programm\n>";
        cin >> mode;
        if (mode !=0 ){ 
            return FastCalculate(a, b, mode);//if he wants to try again recall the fanction with new mode (if not valid again --> all over again)
        }else{ //if user chooses not to output according mesage and abort
            cerr << "\nABORT BY USER.\n"; //er mesage 
            exit(-1); // exit with code -1
            }
    }                                                      //save the finall and corect mode to be printed by main
    if (mode == 1) s_mode = "Multiplication";              //this is here so it still works if the first mode impute is icorect
    if (mode == 2) s_mode = "Division";
    if (mode == 3) s_mode = "Amplitude of the vector";
    if (mode == 4) s_mode = "power";
    if (mode == 5) s_mode = "modulo";
    switch (mode){ //swich for the diferent modes of the calculator 
        case 1://multiplication
            return a * b; // returns result of multiptication
        case 2://division
            try{                             // cheking for division with zero
                if ( b != 0) return a/b;
                throw b;
            } catch(int b){// cathcing and handing division with zero
                cerr << "Invalide second number in conjunction with divide mode as division with zero is not possible and you gave: " << b << " as a divisor\nif you would like to try again give a new imput B or else give 0 to terminate the programm\n>";
                cin >> b;
                if(b != 0){
                return FastCalculate(a, b, mode);//recoling the function for non zero b if given
                }else{
                    cerr << "\nABORT BY USER.\n";//or abord if so chosen by the user
                    exit(2);
                }
            }
        case 3: //Amplitude of the vector (we dont have to check the value under the aq root as it can not be < 0)
            return int(sqrt((a * a + b * b)));
        case 4: //A in the poer of B
            try{//cheking for the invalid calculation of zero in the powe of a number <= 0
                if (!( (a == 0) && ( b < 1) )){ 
                    return pow(a, b); // returning the value
                }else{
                    throw b; //throwing the B if it  creates problem in the calculations
                }
            }catch(int b){  //catch and handle B
                cerr << "You can not give " << b << " as a exponent when you already gave 0 as a base.\nif you would like to try again give a exponent equal or greater than one or else give 0 to terminate the programm\n>";
                cin >> b;
                if(b != 0){
                return FastCalculate(a, b, mode); //recall function with corect b
                }else{
                    cerr << "\nABORT BY USER.\n"; // abord is the  user chooses so
                    exit(4);
                }
            }
        case 5: // modulo
            try{                             // divison is needed to get the modulo so we cant divide by zero 
                if ( b != 0) return a%b; // return the modulo if it can be calculated
                throw b; // throw be if not
            } catch(int b){ // catch and handle error
                cerr << "Invalide second number in conjunction with modulo mode because division is needed to calculate modulo and division with zero is not possible and you gave: " << b << " as a divisor\nif you would like to try again give a new imput or else give 0 to terminate the programm\n>";
                cin >> b;
                if(b != 0){
                return FastCalculate(a, b, mode); // recall with correct valuse i
                }else{
                    cerr << "\nABORT BY USER.\n"; // abord if user chooses so
                    exit(5);
                }
            }
        default : // just in case a worng mode value goes through
            cerr << "something went wrong with the mode plse try again."; // error
            error("something with the mode.");
    }
}


//main takes args with cin and checks the two ints that take part in the clculations, the mode and calls the FastCalulate function
int main(){
    int a, b, mode, res; 
    cout << "Please give a integer A to be used as the first item in the calculation.\n>";
    while (!(cin >> a)){ //chesks if given a char
        cerr << "The imput was NOT an integer.\nPlese give valid imput: "; 
        cin.clear(); 
        cin.ignore(100, '\n'); 
    }
    if (a == 0){ //waring for limited posible calculations for a == 0 in mode 4
        cout << "\nWARNING : The A impute was 0 if you intent to use mode 4 (A^B) your next impute (B) must be greater or equal to 1.\n";
    }
    cout << "\nPlease give a integer B to be used as the second item in the calculation.\n>";
    while (!(cin >> b)){ //chesks if given a char
        cerr << "\nThe imput was not an integer.\nplese give valid imput: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    if ( b == 0 ){ 
        cout << "\nWARNIMG : The B imput was 0 keep in mind that limits the calulation that can be done to modes <1, 3, 4>\n";
    }
    cout << "\nPlease give a mode for the calculator\n1: Multiplication (A * B)\n2: Division (A/B)\n3: Amplitude of the vector ( sqr(a^2 + b^2) )\n4: power (A^B)\n5: modulo (A mod B).\n>";
    while (!(cin >> mode)){ //chesks if given a char
        cerr << "The imput was NOT an integer.\nPlese give valid imput: "; 
        cin.clear(); //clearing cin
        cin.ignore(100, '\n'); //ignoring previous imputes
    } // we let the fanction check the given mode  to make it more compatable
    res = FastCalculate (a, b, mode);// calling the function
    cout << "\nThe result of the integers A = " << a << " and B = " << b << " for the mode <" <<  s_mode << "> is: " << res << endl ;
                                            //printing the result with the variables and the mode

    return 0;
}
