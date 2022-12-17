#include "../inc/chain.hh"

// Main functions test out three cases
// First is the insertEnd function which works without any trouble
// Next is insert middle. Works up to 64 lines but split does not work properly
// Then is remove
int main() {

    Chain c;
    string str = "Hello, World!";
    string other = "Welcome aboard:";
    string another = "Lets go to LaLaLand.";
    string yetanother = "Lets go to LaLaLand, again";
    string insrStart = "Add to beginning";

    /*
       cout << "Read from file? Type Y/y if not N/n" << endl;
       char input;
       string inFileName;
       cin >> input;
       */

    string middle = "This is the middle entry";
    c.insertEnd(str);
    c.insertEnd(other);
    c.insertEnd(another);
    cout << "Insert three entries to end" << endl;
    c.printTree();
    cout << "Insert End to do multiple splits" <<endl;
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(other);
    c.insertBeginning(insrStart);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);

    string thisNew = " This line needs to be cahnged hakuna matata";
    c.insertEnd(thisNew);
    string extrastring = "Please work";
    c.insertEnd(extrastring);
    c.insertEnd(str);
    for(int i = 0; i < 43; i++)
    {
        c.insertEnd(extrastring);
    }
    c.insertEnd(another);
    c.insertEnd(yetanother);
    string hugeTest = "Add 65th line woop woop";
    c.insertEnd(hugeTest);
    
    string biggerTest = "This is the 66 the line";
    c.insertEnd(biggerTest);
    c.printTree();


    Chain c2;
    cout << "Insert 3 strings into a new chain." << endl;  
    c2.insertEnd(str);
    c2.insertEnd(other);
    c2.insertEnd(yetanother);
    c2.printTree();
    cout << "Then insert middle to second position" << endl;
    c2.insertMiddle(middle, 2);
    c2.printTree();


    Chain c3;
    cout << "Testing of remove function by first inserting 16 lines to End" << endl;
    c3.insertEnd("a00");
    c3.insertEnd("b01");
    c3.insertEnd("c02");
    c3.insertEnd("d03");
    c3.insertEnd("e04");
    c3.insertEnd("f05");
    c3.insertEnd("g06");
    c3.insertEnd("h07");
    c3.insertEnd("i08");
    c3.insertEnd("j09");
    c3.insertEnd("k10");
    c3.insertEnd("l11");
    c3.insertEnd("m12");
    c3.insertEnd("n13");
    c3.insertEnd("o14");
    c3.insertEnd("p15");

    c3.printTree();
    c3.remove(5);
    c3.remove(4);
    c3.remove(3);
    cout << "Removing positions 3-5 from chain" << endl;
    c3.printTree();


//This was some previous work done to read in and write out files
//Most of it was removed since we could not get to that part due to the restart from b-trees
    /*
       if(input == 'y' || input == 'Y')
       {
       cout << "Enter File Name: ";
       cin >> inFileName;
       ifstream readFile;
       readFile.open(inFileName);
       c.readFile(readFile);
       }
       else if(input != 'N' || input != 'n')
       {
       cout << "Invalid response!" << endl;
       return -1;
       }
       else
       {
       c.insertEnd(str);
       c.insertEnd(other);
       c.insertEnd(another);
       c.insertEnd(yetanother);
       c.insertEnd(str);
       c.insertEnd(other);
       c.insertEnd(yetanother);
       c.insertEnd(str);
       c.insertEnd(other);
       c.insertEnd(another);
       c.insertEnd(yetanother);
       string thisNew = " This line needs to be cahnged hakuna matata";
       c.insertEnd(thisNew);
       string extrastring = "Please work";
       c.insertEnd(extrastring);
       c.insertEnd(str);
       for(int i = 0; i < 43; i++)
       {
       c.insertEnd(extrastring);
       }
       c.insertEnd(another);
       c.insertEnd(yetanother);
       string hugeTest = "Add 65th line woop woop";
       c.insertEnd(hugeTest);
       }
*/
    //c.remove(3);
    //c.printTree();
    cout << "Finsihed printing" << endl;
    return 0;
}
