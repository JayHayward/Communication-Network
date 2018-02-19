#include "CommunicationNetwork.h"
#include <fstream>
using namespace std;

CommunicationNetwork::CommunicationNetwork()
{
  head=NULL;
  tail=NULL;
}
CommunicationNetwork::~CommunicationNetwork()
{
  // deleteNetwork();
}

void CommunicationNetwork::buildNetwork()
{
  head=new City("",NULL,NULL,"");
  tail=new City("",NULL,NULL,"");

  City *Bos=new City("Boston", NULL, NULL,"");   //*bos != Bos
  City *Ny=new City("New York",  Bos, NULL,"");
  City *Was=new City("Washington, D.C.", Ny, NULL,"");
  City *Atl=new City("Atlanta", Was, NULL,"");
  City *Chi=new City("Chicago", Atl, NULL,"");
  City *Lou=new City("St. Louis", Chi, NULL,"");
  City *Dal=new City("Dallas", Lou, NULL,"");
  City *Den=new City("Denver", Dal, NULL,"");
  City *Pho=new City("Phoenix", Den, NULL,"");
  City *La=new City("Los Angeles", Pho, NULL,"");

  Bos->previous=Ny;
  Ny->previous=Was;
  Was->previous=Atl;
  Atl->previous=Chi;
  Chi->previous=Lou;
  Lou->previous=Dal;
  Dal->previous=Den;
  Den->previous=Pho;
  Pho->previous=La;

  head=La;
  tail=Bos;

  // City *walker=head;
  // // cout<<"head:\t"<<head<<"\n\n";
  // cout<<"===CURRENT PATH===\nNULL <- ";
  // while(walker!=NULL)
  // {
  //   if(walker->cityName!="")
  //   {
  //     cout<<walker->cityName;
  //     if(walker->next!=NULL)
  //       cout<<" <-> ";
  //     else
  //       cout<<" -> NULL";
  //   }
  //   walker=walker->next;
  // }
  // cout<<"\n=================="<<endl;
  // cout<<"\n\nhead:\t"<<head<<"\n\n";
}

void CommunicationNetwork::printNetwork()
{
  City *walker=head;
  cout<<"===CURRENT PATH===\n";
  if(head==NULL)
  {
    cout<<"==NULL=="<<endl;
    return;
  }
  else
    cout<<"NULL <- ";
  while(walker!=NULL)
  {
    if(walker->cityName!="")
    {

      if(walker->next!=NULL)
      {
        cout<<walker->cityName;
        cout<<" <-> ";
      }
      else
        cout<<tail->cityName<<" -> NULL";
    }
    walker=walker->next;
  }
  cout<<"\n=================="<<endl;
  cout<<tail->cityName<<endl;
}

void CommunicationNetwork::transmitMsg(char *filename)
{
  ifstream file(filename);
  // ifstream file("messageIn.txt");

  if(file)
  {
    string word;
    bool forward=true;
    while(file>>word)
    {
      City *walker=head;
      forward=true;
      while(walker->next!=NULL)
      {
        walker->message=word;
        cout<<walker->cityName<<" received "<<walker->message<<endl;
        walker=walker->next;
      }
      while (walker->previous!=NULL)
      {
        walker->message=word;
        cout<<walker->cityName<<" received "<<walker->message<<endl;
        walker=walker->previous;
      }
      walker->message=word;
      cout<<walker->cityName<<" received "<<walker->message<<endl;
    }
  }
  else
    cout<<"error reading file"<<endl;
}

void CommunicationNetwork::addCity(string newCityName, string previousCityName)
{
  City *walker=head;
  if(previousCityName=="First") //new head
  {
    City *h=new City(newCityName,NULL,NULL,"");
    h->next=head;
    head=h;
  }

  if(previousCityName=="\"\"") //new tail
  {
    City *t=new City(newCityName,NULL,NULL,"");
    t->previous=tail;
    tail->next = t;
    tail=t;
    // // t->next=tail;
    cout<<tail->cityName<<endl;
    cout<<tail->previous->cityName<<endl;
  }

  while(walker!=NULL)
  {
    if(walker->cityName==previousCityName)
    {
      City *n=new City(newCityName,NULL,NULL,"");
      n->next=walker->next;
      n->previous=walker->previous;
      walker->next=n;
      break;
    }
    walker=walker->next;
  }
}

void CommunicationNetwork::deleteCity(string removeCity)
{
  City *walker=head;
  if(head->cityName==removeCity) //if city is the first in the LL
  {
    City *temp=head->next;
    head->next->previous=NULL;
    delete head;
    head=temp;
    return;
  }
  if(tail->cityName==removeCity)
  {
    City *temp=tail->previous;
    tail->previous->next=NULL;
    delete tail;
    tail=temp;
    return;
  }

  while(walker!=NULL)
  {
    if(walker->cityName==removeCity)
    {
      walker->previous->next=walker->next;
      walker->next->previous=walker->previous;
      walker->next=NULL;
      walker->previous=NULL;
      delete walker;
      return;
    }
    walker=walker->next;
  }
}

void CommunicationNetwork::deleteNetwork()
{
  City *walker=head;
  while(walker!=NULL)
  {
    City *n=walker;
    cout<<"deleting "<<walker->cityName<<endl;
    delete n;
    walker=walker->next;
  }
  head=NULL;
}
