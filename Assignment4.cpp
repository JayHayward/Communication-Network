//CSCI 2270
//Assignment4
//Justin Hayward

#include "CommunicationNetwork.cpp"
using namespace std;

int printMenu()
{
  cout<<"======Main Menu======"<<endl;
  cout<<"1. Build Network"<<endl;
  cout<<"2. Print Network Path"<<endl;
  cout<<"3. Transmit Message Coast-To-Coast"<<endl;
  cout<<"4. Add City"<<endl;
  cout<<"5. Delete City"<<endl;
  cout<<"6. Clear Network"<<endl;
  cout<<"7. Quit"<<endl;

  string selection;
  int a=0;
  while(a==0) //makes sure avalid input is collected
  {
    cin>>selection;
    if((selection<"1")||(selection>"7"))
      cout<<"Invalid"<<endl;
    else
      a=1;
  }
  return stoi(selection);
}

int main(int argc, char *argv[])
{
  CommunicationNetwork cn;
  int sel=printMenu();
  for(;;)
  {
    if(sel==1)
    {
      cn.buildNetwork();
      cn.printNetwork();
      sel=printMenu();
      continue;
    }
    if(sel==2)
    {
      cn.printNetwork();
      sel=printMenu();
      continue;
    }
    if(sel==3)
    {
      cn.transmitMsg(argv[1]);
      sel=printMenu();
      continue;
    }
    if(sel==4)
    {
      string newC,prevC;
      cout<<"Enter a city name:\n";
      cin>>newC;
      cout<<"Enter a previous city name:\n";
      cin>>prevC;
      cn.addCity(newC,prevC);
      sel=printMenu();
      continue;
    }
    if(sel==5)
    {
      string delC;
      cout<<"Enter a city name:\n";
      cin>>delC;
      cn.deleteCity(delC);
      sel=printMenu();
      continue;
    }
    if(sel==6)
    {
      cn.deleteNetwork();
      sel=printMenu();
      continue;
    }
    if(sel==7) //why isthis calling deleteNetwork?
    {
      cout<<"Goodbye!";
      return 0;
    }
  }
}
