#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdio>
#include<stdio.h>
#include<iomanip>
#include<sstream>
 using namespace std;
 int main();
 void Edit();
 void edit_item(string);
 void is_existed();
 void read_all_record();
 float netamt,grand_total=0;
 void bill_details();

 float calculate(float price,float tax,float discount,float quantity)
 {
         float gross,netamt;
         gross=price+(price*(tax/100));
         netamt=quantity*(gross-(gross*(discount/100)));

         return netamt;
 }

  void genrate_receipt()
        {

            system("cls");

    cout<<"\n\t\t\t*************************************************";
    cout<<"\n\t\t\t\t\t     INVOICE ";
    cout<<"\n\t\t\t*************************************************\n";
    cout<<"\n\t"<<setw(25)<<"Item-ID"<< setw(15)<<"NAME"<<setw(5)<<"      QTY"<<setw(5)<<"     PRICE(per)\n\t";
      ifstream file;
     file.open("file.txt");
     string item_no,name,date,cost,tax,discount,quantity,net_amount;
     while(getline(file,item_no,','))
     {

             vector<string> record;
             getline(file,name,',');
             getline(file,date,',');
             getline(file,cost,',');
             getline(file,tax,',');
             getline(file,discount,',');
             getline(file,quantity,'|');
             getline(file,net_amount,'\n');


             record.push_back(item_no);
             record.push_back(name);
             record.push_back(date);
             record.push_back(cost);
             record.push_back(tax);
             record.push_back(discount);
             record.push_back(quantity);
             record.push_back(net_amount);

             cout<<setw(25)<<record[0]<<setw(15)<<record[1]<<setw(5)<<"       "<<record[6]<<setw(5)<<"       "<<record[3]<<"\n\t";

             stringstream s(record[7]);
             float value=0;
             s>>value;
             grand_total=value+grand_total;


     }

         cout<<"\n\t\t\t*************************************************";
         cout<<"\n\t\t\t Grand-Total :                          "<<grand_total;
         cout<<"\n\t\t\t*************************************************\n";
         cout<<"\t\t\t\t\tThankyou visit again! ";
         grand_total=0;
         cout<<"\n\n\n\n\n\n\t\t\tPress any key to go back to Main Menu...";
     system("pause > nul");
     main();
        }


 bool is_existed(string item)
 {

     ifstream obj("file.txt");
     string c;
     bool found;
     while(getline(obj,c,','))
     {
        if(c==item)
            {
                found=true;
                return found;
            }

        else
            found=false;

        getline(obj,c,'\n');
     }

     if(found==false)
        return found;

}
 void add_element()
 {
     system("cls");
     string item_no,name;
     int date;
     float cost,tax,discount,quantity,net_amount;
    fstream obj("file.txt",ios::out|ios::app);
    cout<<"\n\t\tEnter Item Details\n\t..................................\n\n\n";
    cout<<"\t\tEnter Item-ID. : ";
    cin>>item_no;
    if(is_existed(item_no)==1)
    {
        cout<<"\n\t\t\tItem is already in your cart...\n";
        cout<<"\n\t\t\tTo change its quantity you have to go back to the Editor.....\n\n\n\t\tPress any key to go back.....";

        system("pause>nul");
        Edit();

    }

    else
    {
    cout<<endl<<"\t\tEnter Item name: ";
    cin>>name;

    cout<<endl<<"\t\tEnter Date: ";
    cin>>date;
    cout<<endl<<"\t\tEnter Item Price: ";
    cin>>cost;
    cout<<endl<<"\t\tEnter Tax applied: ";
    cin>>tax;
    cout<<endl<<"\t\tEnter Discount: ";
    cin>>discount;
    cout<<endl<<"\t\tEnter Quantity: ";
    cin>>quantity;

     net_amount=calculate(cost,tax,discount,quantity);

     obj<<item_no<<","<<name<<","<<date<<","<<cost<<","<<tax<<","<<discount<<","<<quantity<<"|"<<net_amount<<"\n";
     cout<<"\n\n\t\t\tItem added successfully\n\n\n";
     obj.close();
     cout<<"\t\tPress any key to go back to Bill details.....";
     system("pause>nul");
     bill_details();
 }

 }
int delete_item(string item)
{
    vector<string> record;


    ifstream file("file.txt");
    ofstream temp("tmp.txt",ios::trunc);
    string one,two;
    char old[101]="file.txt";
    char name[101]="tmp.txt";

   if(is_existed(item)==1)

      {
        while(getline(file,one,','))
       {
        if(one==item)
           {
               getline(file,two,'\n');
           }
        else
        {
            getline(file,two,'\n');
            temp<<one<<","<<two<<"\n";
        }

       }

      file.close();
      temp.close();

     int n=0;
     ofstream obj1;
     obj1.open("file.txt",ios::trunc);
     ifstream tmp;
     tmp.open("tmp.txt",ios::in);

      while(getline(tmp,one,','))
    {
            getline(tmp,two,'\n');
            obj1<<one<<","<<two<<"\n";
            n=1;
    }

    obj1.close();
    tmp.close();
    if(n=1)
      return 1;

   return 0;
}}

void edit_item()
{
     system("cls");

     string one,two,name,item;
     int date,cost,tax,discount,quantity,n;
     ifstream obj1;
     ofstream obj2;

     cout<<"\n\t\tEnter Item Details\n\t..................................\n\n\n";
     cout<<"\t\tEnter Item no. : ";
     cin>>item;

     n= delete_item(item);
     if(n==1)
     {   cout<<"\n\n\t\t\t\tPress enter to add new details..";
         system("pause>nul");
         add_element();
     }
}




 void Edit()
 {
        system("cls");
        cout<<"\n\n\t\t\t\t======================";
        cout<<"\n\t\t\t\t\tEditor\n";
        cout<<"\t\t\t\t======================\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout<<"\t\t4.Back to Bill Details "<<endl;
        cout<<"\n\tPLease enter the value: ";
        int n;
        cin>>n;

        switch(n)
          {
           case 1:
              add_element();
              break;
           case 2:
             edit_item();
             break;

           case 3:
              {string c;
              int n;
              read_all_record();
              cout<<"\n\t\t\tEnter Item-ID to Delete: ";
              cin>>c;
              n=delete_item(c);
              if(n==1)
                {
                    cout<<"\n\n\t\t\t\t\t\tItem deleted...\n\n\t\t press enter to go back to the bill details...";
                    system("pause>nul");
                    bill_details();

                }
              break;
              }


           case 4:
              {bill_details();
              break;}
          }


 }

  int readrecord(string element )
 {
     system("cls");
     vector<string> record;

     ifstream file;
     file.open("file.txt");

     bool found=false;
     string item_no,name,date,cost,tax,discount,quantity,net_amount;


     while(!found&&getline(file,item_no,','))
     {
         getline(file,name,',');
         getline(file,date,',');
         getline(file,cost,',');
         getline(file,tax,',');
         getline(file,discount,',');
         getline(file,quantity,'|');
         getline(file,net_amount,'\n');


         if(item_no==element)
         {   cout<<"\t\t\t\t\tITEM\n\t\t\t\t---------------------\n\n";
             found=true;
             record.push_back(item_no);
             record.push_back(name);
             record.push_back(date);
             record.push_back(cost);
             record.push_back(tax);
             record.push_back(discount);
             record.push_back(quantity);
             record.push_back(net_amount);
             cout<<"\n\tItem-ID        :"<<record[0]<<"\n\tItem name     :"<<record[1]<<"\n\tDate of entry       : "<<record[2]<<"\n\tPrice      : "<<record[3]<<"\n\tTax applied       :"<<record[4];
              cout<<"\n\tDiscount applicable       : "<<record[5]<<"\n\tQuantity       :  "<<record[6]<<"\n\tNet Amount       :  "<<record[7]<<"\n\n";

            cout<<"\n\n\n\t\t\tPress any key to go back to Main Menu... ";
            system("pause > nul");
            main();
             return 0;
         }


     }

     if(found==false)
     {
         cout<<"\n\n\t\t\tItem does not exist..\n\nPress enter to go back...";
         system("pause>nul");
         main();
         return 0;
     }




 }
 void read_all_record()
 {
          system("cls");
     ifstream file;
     file.open("file.txt");
     string item_no,name,date,cost,tax,discount,quantity,net_amount;

     cout<<"\n\n\t\t\t\t\t\t\t Items in the Cart\n\t\t\t\t\t\t-------------------------------------\n\n"<<endl;
     cout<<setw(25)<<"Item-ID"<< setw(20)<<"NAME"<<setw(15)<<"DATE"<<setw(10)<<"PRICE"<<setw(10)<<"TAX(%)"<<setw(15)<<"DISCOUNT(%)"<<setw(15)<<"QUANTITY"<<setw(15)<<"NET AMOUNT"<<"\n\n";

     while(getline(file,item_no,','))
     {

             vector<string> record;
             getline(file,name,',');
             getline(file,date,',');
             getline(file,cost,',');
             getline(file,tax,',');
             getline(file,discount,',');
             getline(file,quantity,'|');
             getline(file,net_amount,'\n');


             record.push_back(item_no);
             record.push_back(name);
             record.push_back(date);
             record.push_back(cost);
             record.push_back(tax);
             record.push_back(discount);
             record.push_back(quantity);
             record.push_back(net_amount);

             cout<<setw(25)<<record[0]<<setw(20)<<record[1]<<setw(15)<<record[2]<<setw(10)<<record[3]<<setw(10)<<record[4]<<setw(15)<<record[5]<<setw(15)<<record[6]<<setw(15)<<record[7]<<"\n";

             stringstream s(record[7]);
             float value=0;
             s>>value;
             grand_total=value+grand_total;


     }
            cout<<"\n\n\n\t\t\t\t\t\t\tGrand-Total :  "<<grand_total;
            grand_total=0;
 }
  void bill_details()
 {

     system("cls");
     ifstream file;
     file.open("file.txt");
     string item_no,name,date,cost,tax,discount,quantity,net_amount;

     cout<<"\n\n\t\t\t\t\t\t\t Items in the Cart\n\t\t\t\t\t\t-------------------------------------\n\n"<<endl;
     cout<<setw(25)<<"Item-ID"<< setw(20)<<"NAME"<<setw(15)<<"DATE"<<setw(10)<<"PRICE"<<setw(10)<<"TAX(%)"<<setw(15)<<"DISCOUNT(%)"<<setw(15)<<"QUANTITY"<<setw(15)<<"NET AMOUNT"<<"\n\n";

     while(getline(file,item_no,','))
     {

             vector<string> record;
             getline(file,name,',');
             getline(file,date,',');
             getline(file,cost,',');
             getline(file,tax,',');
             getline(file,discount,',');
             getline(file,quantity,'|');
             getline(file,net_amount,'\n');


             record.push_back(item_no);
             record.push_back(name);
             record.push_back(date);
             record.push_back(cost);
             record.push_back(tax);
             record.push_back(discount);
             record.push_back(quantity);
             record.push_back(net_amount);

             cout<<setw(25)<<record[0]<<setw(20)<<record[1]<<setw(15)<<record[2]<<setw(10)<<record[3]<<setw(10)<<record[4]<<setw(15)<<record[5]<<setw(15)<<record[6]<<setw(15)<<record[7]<<"\n";

             stringstream s(record[7]);
             float value=0;
             s>>value;
             grand_total=value+grand_total;


     }
            cout<<"\n\n\n\t\t\t\t\t\t\tGrand-Total :  "<<grand_total;
            grand_total=0;

            int n;
            cout<<"\n\n\n\n\t\t     Press\n\t\t\t1.To Generate Invoice\n\t\t\t2.To Add/Delete/Edit item\n\t\t\t3.To go back to Main menu  \n\t\tPress the required value : ";
            cin>>n;
            switch(n)
            {
            case 1:
                genrate_receipt();
                break;
            case 2:
               Edit();
               break;
            case 3:
                main();
                break;


            }



 }


 int main()
 {
    system("cls");
    cout<<"\n\t\t\t====================================";
    cout<<"\n\t\t\t\tSuper Market Billing ";
    cout<<"\n\t\t\t====================================\n\n";
    cout<<"\n\t\t1.Bill Details\n\n";
    cout<<"\t\t2.Generate Receipt\n\n";
    cout<<"\t\t3.Exit\n\n";
    cout<<"\t\tPlease Enter Required Option: ";
    int n;
    cin>>n;
    switch(n)
    {

    case 1:
        bill_details();
        break;

    case 2:
        genrate_receipt();
        break;

    case 3:
        cout<<"\n\n\t\t\t\t..Exited...";
        system("pause>nul");
        system("cls");
        break;

    }


     return 0;
 }
