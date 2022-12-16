#include "../inc/chain.hh"

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
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertMiddle(middle, 3);
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(other);
    //c.insertBeginning(insrStart);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    //c.insertEnd(str);
    //c.insertEnd(other);
    //c.insertEnd(another);
    //c.insertEnd(yetanother);
/*
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
    */

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
       c.insertEnd(another);
       c.insertEnd(yetanother);
       c.insertEnd(str);
       c.insertEnd(other);
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
       }
*/
    c.printTree();
    cout << "Finsihed printing" << endl;
    return 0;
}
