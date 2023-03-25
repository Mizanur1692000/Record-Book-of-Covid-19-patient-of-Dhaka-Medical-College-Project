#include<iostream>
#include<cstdlib>
#include<fstream>
#define max 2600//Total 2600 beds are available in the hospital. So, 2600 patients can be added in tha list
using namespace std;


struct Patient{
  int patientId;
  string patientName;
  string patientAddress;
  string patientCovid19TestReportDate;
  string listOfPreviousDiseases;
  string bloodGroup;
  struct Patient *next;//self referenial pointer
};
//Hospital information
void hospitalInformation(string hospitalName, string hospitalLocation,int establishedYear, int worldRanking, int totalBed, string totalDoctor)
{
  cout<<"Hospital name: "<<hospitalName<<endl<<"Location: "<<hospitalLocation<<endl<<"Eshtablished year: "<<establishedYear<<endl<<"World Ranking: "<<worldRanking<<endl<<"Total beds: "<<totalBed<<endl<<"Total number of doctors: "<<totalDoctor<<endl;
}
//function for insert a new patient's information which take patient id,name,address,covid-19 test report and list of previous diseases of the patient using stack
int count(struct Patient*temp)//Checking overflow or not function
{
  int c=0;
  while(temp!=NULL)
  {
    temp=temp->next;
    c++;
  }
  return (c);
}

void insertPatient(struct Patient**q)
{
  int patientId;
  string patientName;
  string patientAddress;
  string patientCovid19TestReportDate;
  string listOfPreviousDiseases;
  string bloodGroup;
  struct Patient*temp;
  if(count(*q)>=max)
  {
    cout<<"Overflow!!!";
    return ;
  }
  else
  {
  cout<<"Enter the patient id: ";
  cin>>patientId;
  cin.ignore();//we need to clear the input buffer, otherwise it will occupy the buffer of previous variable. By pressing the “Enter” key after the first input, as the buffer of previous variable has space to hold new data, the program skips the following input of container.
  cout<<"Enter the patient name: ";
  //cin>>patientName;
  getline(cin,patientName);
  cout<<"Enter the patient address: ";
  //cin>>patientAddress;
  getline(cin,patientAddress);
  cout<<"Enter the Covid-19 test report date of the patient: ";
  //cin>>patientCovid19TestReportDate;
  getline(cin,patientCovid19TestReportDate);
  cout<<"Enter the list of previous diseases of patient: ";
  //cin>>listOfPreviousDiseases;
  getline(cin,listOfPreviousDiseases);
  cout<<"Enter the blood group of patient: ";
  cin>>bloodGroup;
    temp=(struct Patient*)malloc(sizeof(Patient));//dynamic memory allocation
    temp->patientId=patientId;
    temp->patientName=patientName;
    temp->patientAddress=patientAddress;
    temp->patientCovid19TestReportDate=patientCovid19TestReportDate;
    temp->listOfPreviousDiseases=listOfPreviousDiseases;
    temp->bloodGroup=bloodGroup;
    temp->next=*q;
    *q=temp;
    cout<<"Patient information successfully inserted at the beginning of the list and saved !!!";
  }
}



int searchById(struct Patient** headRef, int patientId)//search the patient's information by id if found then it will porvide the patient's name,address,covid-19 test report and list of previous diseases
{
  struct Patient *current=*headRef;
  while(current!=NULL)
  {
    if(current->patientId==patientId)
    {
      cout<<"Patient record found!!!"<<endl;
      cout<<"After searching patient's name is: "<<current->patientName<<endl<<"Address: "<<current->patientAddress<<endl<<"Covid-19 test report date: "<<current->patientCovid19TestReportDate<<endl<<"Previous diseases: "<<current->listOfPreviousDiseases<<endl<<"Blood group: "<<current->bloodGroup<<endl;
      return 1;

    }
    current=current->next;

  }
  return 0;

}

void deleteDiedPatient(struct Patient** head,int id)//delete function....User can delete any petient's record from record book by using patient's name
{
  struct Patient *temp = *head,*prev;
  if(temp!=NULL && temp->patientId == id){
    *head = temp->next;
    free(temp);
    return;
  }

  while(temp !=NULL && temp->patientId !=id){
    prev = temp;
    temp = temp->next;
  }
  if(temp==NULL)
    return;

  prev->next = temp->next;
  free(temp);
}
void deleteRecoveryPatient(struct Patient** head,int id)//delete function....User can delete any petient's record from record book by using patient's name
{
  struct Patient *temp = *head,*prev;
  if(temp!=NULL && temp->patientId == id){
    *head = temp->next;
    free(temp);
    return;
  }

  while(temp !=NULL && temp->patientId !=id){
    prev = temp;
    temp = temp->next;
  }
  if(temp==NULL)
    return;

  prev->next = temp->next;
  free(temp);
}
void updatePatientInformation(struct Patient**headRef,int id,int updateId,string updateName,string updateAddress,string updateCovid19TestReportDate)//update funcition by address...user can update any patient's address by using the previous address
{
  if(*headRef==NULL)
  {
    cout<<"Patient record file is empty!!!";
  }
  struct Patient *current=*headRef;
  while(current!=NULL)
  {
    if(current->patientId==id)
    {
      current->patientId=updateId;
      current->patientName=updateName;
      current->patientAddress=updateAddress;
      current->patientCovid19TestReportDate=updateCovid19TestReportDate;
      cout<<endl<<id<<" found and replaced with "<<updateId<<endl<<"Name: "<<updateName<<endl<<"Address: "<<updateAddress<<endl<<"Covid-19 test report date: "<<updateCovid19TestReportDate<<endl;
    }
    current=current->next;
  }
}

//Merge sort function for getting the patient information in accending order
Patient* mergeList(Patient* split1,Patient* split2){
    //merging two sorted list
    Patient* newhead=NULL;
    //base cases
    if(split1==NULL)
    return split2;
    if(split2==NULL)
    return split1;
    //recursively merge
    if(split1->patientId<=split2->patientId){
        newhead=split1;
        newhead->next=mergeList(split1->next,split2);
    }
    else{
        newhead=split2;
        newhead->next=mergeList(split1,split2->next);
    }

    return newhead;

}
//Merge sort funciton
void splitList(Patient* head,Patient** split1,Patient** split2){
    //similar to flyod's tortoise algorithm
    Patient* slow=head;
    Patient* fast=head->next;

    while(fast!=NULL){
        fast=fast->next;
        if(fast!=NULL){
            slow=slow->next;
            fast=fast->next;
        }
    }

    *split1=head;
    *split2=slow->next;
    //spliting
    slow->next=NULL;
}
//Merge sort
void mergeSort(Patient** refToHead){
    Patient* head=*refToHead;
    Patient* split1,*split2;
    //base case
    if(head==NULL || head->next==NULL){
        return;
    }
    //split the list in two halves
    splitList(head,&split1,&split2);
    //recursively sort the two halves
    mergeSort(&split1);
    mergeSort(&split2);
    //merge two sorted list
    *refToHead=mergeList(split1,split2);

    return;

}


void display(struct Patient *head)//display functio which display the record book of patients after inserting the patients information properly
{
  //NodePtr p = head;
  cout<<endl;
  while(head!=NULL){
    cout<<"\tPatient Id = "<<head->patientId<<endl<<"\tPatient name = "<<head->patientName<<endl<<"\tPatient address = "<<head->patientAddress<<endl<<"\tCovid-19 test report data = "<<head->patientCovid19TestReportDate<<endl<<"\tList of pervious diseases = "<<head->listOfPreviousDiseases<<endl<<"\tBlood group = "<<head->bloodGroup<<endl<<endl;
    head=head->next;
  }
  cout<<endl;
}

//File handling part
typedef Patient* NodePtr;
class LinkedList{
  private:
    NodePtr head;
  public:
    LinkedList(){
      head = NULL;
    }
    NodePtr& addLinkedList(NodePtr& head,int patientId,string patientName, string patientAddress, string patientCovid19TestReportDate, string listOfPreviousDiseases, string bloodGroup){
      NodePtr NewPtr = new Patient();
      NewPtr->patientId = patientId;
      NewPtr->patientName = patientName;
      NewPtr->patientAddress = patientAddress;
      NewPtr->patientCovid19TestReportDate = patientCovid19TestReportDate;
      NewPtr->listOfPreviousDiseases = listOfPreviousDiseases;
      NewPtr->bloodGroup=bloodGroup;

      NewPtr->next = NULL;

      NodePtr p = head;

      if(p == NULL)
        head = NewPtr;
      else
      {
          while(p->next != NULL)
            p = p->next;
          p->next = NewPtr;
      }
      return head;
    }

    void fileWrite(NodePtr& head){
      ofstream os("patientList.txt", ios::out | ios::app);
      for (NodePtr p = head; p != NULL; p = p->next){
          cout <<endl<<"Patient id: "<< p->patientId<<endl <<"Patient name: "<<p->patientName<<endl<<"Patient address: "<<p->patientAddress<<endl<<"Patient Coved-19 tese report date: "<<p->patientCovid19TestReportDate<<endl<<"List of previous diseases of patient: "<<p->listOfPreviousDiseases<<endl<<"Blood group: "<<p->bloodGroup<<endl;
          os <<endl<<"Patient id: "<<p->patientId <<endl<<"Patient name: "<<p->patientName<<endl<<"Patient address: "<<p->patientAddress<<endl<<"Patient Coved-19 tese report date: "<<p->patientCovid19TestReportDate<<endl<<"List of previous diseases of patient: "<<p->listOfPreviousDiseases<<endl<<"Blood group: "<<p->bloodGroup<<endl;
      }
      os.close();
    }
};

int countPatient(struct Patient*temp)
{
  int i=0;
  while(temp!=NULL)
  {
    i++;
    temp=temp->next;
  }
return i;
}


int main()//main function....all the fuction is called from this function...user can choice 1 to 8 options for the patient record book....if used choice 9 the program will exit otherwise user take any other choice(without 1 t0 9) the program will show invalid choice!!! try again...then user can choice any option again from 1 to 8....
{

  int choice;
  string name,previousDisease;
  struct Patient* patient=NULL;
  struct Patient hospitalName, hospitalLocation, establishedYear, worldRanking, totalBed, totalDoctor;
  LinkedList k;
  NodePtr head;
  while(1)
  {
   cout << "\n\t\tWelcome to the Record Book of Covid-19 patient of Dhaka Medical College: "
          "\n\n\t\t Press\n\t\t 1 to see hospital information\n\t\t 2 to "
                "insert a patient\n\t\t 3 to search a "
                "patient record by id\n\t\t 4 to remove a died patient's record\n\t\t 5 to remove a recovery patient's record\n\t\t 6 to update patient information\n\t\t 7 to view the records of all patient\n\t\t 8 to view the records in ascending order(Merge sort)\n\t\t 9 to see the total number of admited patient\n\t\t10 to save patient information permanently. If you save all information, you can not add any information\n\t\t11 to Exit\n";
    cout << "\n\tEnter your Choice\n";
   cin>>choice;
    if(choice==1)
   {
     /*cout<<"Hospital name: Dhaka Medical College and Hospital."<<endl<<"Location: Dhaka, Bangladesh."<<"Eshtablished: 1946"<<endl<<"World Ranking: 10763"<<endl<<"Total beds: 2600"<<endl<<"Total number of doctors: 594 (199 female and 395 male)"<<endl;*/
     hospitalInformation("Dhaka Medical College and Hospital.","Dhaka, Bangladesh.", 1946, 10763, 2600, "594 (199 female and 395 male)");
     }
   else if(choice==2)
   {
     insertPatient(&patient);
     //user should take unique id for each patient
   }
   else if(choice==3)
   {
     int id;
     cout<<"Enter the id of the patient to search: ";
     cin>>id;
     if(searchById(&patient,id))
     cout<<"Record of the patient showed!!!";
     else
     cout<<"Record of the patient not found!!!";
   }
   else if(choice==4)
   {
     int id;
     cout<<"Enter the id of the died patient to delete: ";
     cin>>id;
     deleteDiedPatient(&patient,id);
     cout<<"The record of the died patient id "<<id<<" deleted!!!"<<endl;
   }
    else if(choice==5)
   {
     int id;
     cout<<"Enter the id of the recovery patient to delete: ";
     cin>>id;
     deleteRecoveryPatient(&patient,id);
     cout<<"The record of the recovery patient id "<<id<<" deleted!!!"<<endl;
   }
    else if(choice==6)
   {
     int id,updateId;
     string updateName,updateAddress,updateCovid19TestReportDate;
     cout<<"Enter the id of the patient to update patients information: ";
     cin>>id;

     cout<<"Enter the update id: ";
     cin>>updateId;
     cin.ignore();
     cout<<"Enter the update name: ";
     getline(cin,updateName);
     cout<<"Enter the update address: ";
     getline(cin,updateAddress);
     cout<<"Enter update covid-19 test report date: ";
     getline(cin,updateCovid19TestReportDate);
     updatePatientInformation(&patient,id,updateId,updateName,updateAddress,updateCovid19TestReportDate);
     cout<<"Patient id, name, address, covid-19 test report date updated!!!";
   }
    else if(choice==7)
   {
     cout<<"Records of the patients are: ";
     display(patient);
   }
    else if(choice==8)
   {
     cout<<"Records of the patients after Merge sort are: ";
     mergeSort(&patient);
     display(patient);
   }
       else if(choice==9)
   {
    cout<<"Total number of patient is: "<<countPatient(patient);
   }
   else if(choice==10)
   {
    k.fileWrite(patient);
     cout<<"The information of the patients are saved as a list permanently and program end!!!";
     exit(0);
   }

    else if(choice==11)
   {
     exit(0);
   }
   else
   {
     cout<<"Invalid choice!!!";
     cout<<"Try again!!!"<<endl;
   }
  }
}
