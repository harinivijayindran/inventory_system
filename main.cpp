#include<iostream>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include <string.h>
#include<windows.h>



using namespace std;
class item {
    int itemno,stock;
    char iname[50],cname[50];
    float price;
public:
    void getdata()
    {
        system("cls");

        cout << "\nPlease Enter The Item ID Of The Item --> \t";
        cin >> itemno;
        cout << "\nPlease Enter The Name Of The Item -->\t ";
        cin>>iname;
        cout << "\nPlease Enter The Price Of The Item -->\t ";
        cin >> price;
        cout<<"\n Please Enter The Quantity of Item-->";
        cin>>stock;
        cout<<"\n Please Enter The Company Name Of The Item -->";
        cin>>cname;






    }

    void showdata()
    {
        system("cls");
        cout << "\nThe Item Id Of The Item :" << itemno;
        cout << "\nThe Name Of The Item :" << iname;
        cout << "\nThe Price of The Item :" << price;
        cout<<"\nThe Quantity of Item:"<<stock;
        cout<<"\nThe Company Name Of The Item:"<<cname;
        Sleep(2000);


    }
    void place_order();
    int retitemno() { return itemno; }

    float retprice() { return price; }

    char* retiname() { return iname; }

    int retstock() {return stock;}

    char* retcname() { return cname; }



};

fstream f;
fstream f1;
item i;

void write_to_file()
{
    f.open("inventory.dat", ios::out | ios::app);
    i.getdata();
    f.write((char*)&i,sizeof(i));
    f.close();
    cout << "\n\nThe Item Has Been Created ";

}

void disp_all()
{
    system("cls");
    cout << "\n\n\n\t\tDisplay All Records !!!\n\n";
    f.open("inventory.dat", ios::in);
    while(f.read((char*)&i,sizeof(i)))
    {
        i.showdata();
        cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    f.close();
}

void display_sp(char *name)
{
    f.open("inventory.dat", ios::in);
    if(!f)
        cout<<"\nFile not found";
    else
        {
        f.read((char*)&i,sizeof(i));
        while(!f.eof())
            {
            if(!strcmp(name,i.retiname()))
                i.showdata();
            f.read((char*)&i,sizeof(i));
        }
        f.close();
    }

}
void menu()
{
    system("cls");
    f.open("inventory.dat", ios::in);
    if (!f)
    {
        cout << "Error! file not found\n\n\n Go to main menu to create file";
        cout << "\n\n\n Program is closing!";
        exit(0);
    }
    cout << "\n\n\t\t Item Menu\n\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Item ID\t\tName\t\tPrice\t\tQuantity\t\tCompany Name\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    while (f.read((char*) &i, sizeof(i)))
    {
        cout << i.retitemno() << "\t\t" << i.retiname() << "\t\t" << i.retprice() <<"\t\t"<< i.retstock()<<"\t\t"<<i.retcname()<<endl;
    }
    f.close();
    Sleep(2000);
}
void modify()
{
    int no, found = 0;
    system("cls");
    menu();
    cout<<"\n\n\tTo Modify ";
    cout<<"Please Enter The Item ID Of The Item";
    cin>>no;
    f.open("inventory.dat", ios::in | ios::out);
    while (f.read((char*)&i, sizeof(i)) && found == 0)
    {
        if (i.retitemno() == no)
        {
            i.showdata();
            system("cls");

            cout << "\nPlease Enter The New Details Of The Item" << endl;
            i.getdata();
            int pos = -1*((int) sizeof(i));
            f.seekp(pos,ios::cur);
            f.write((char*)&i,sizeof(i));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    f.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
Sleep(2000);
}




void deleterec()
{
    int no;
    system("cls");
    menu();
    cout << "\n\n\n\tDelete Record ";
    cout << "\n\nPlease Enter The Item Id That You Want To Delete";
    cin >> no;
    f.open("inventory.dat", ios::in | ios::out);
    fstream f2;
    f2.open("temp.dat", ios::out);
    f.seekg(0, ios::beg);
    while (f.read((char *) &i, sizeof(i)))
    {
        if (i.retitemno() != no)
        {
            f2.write((char *) &i, sizeof(i));
        }

    }
    f2.close();
    f.close();
    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");
    cout << "\n\n\tRecord Deleted.";
Sleep(2000);
}


void item::place_order()
{
    system("cls");

    int order_arr[50], quan[50], c = 0, cardnum, cvv;
    float amt, total = 0;
    char uname[50];
    char ch = 'y';
    menu();
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "     \n       Place Your Order";
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;
    do {
        cout << "\n\nEnter The Item ID Of The Product: \n";
        cin >> order_arr[c];
        cout << "\n Quantity in number :\n";
        cin >> quan[c];
        c++;
cout << "Do You Want To Order Another Product?(Y/N) \t";
cin>>ch;
cout << "\nPayment Details\n";
                      cout << "\nEnter Your Name:";
                      cin >>uname;
                      cout << "\nEnter Your Card Number:";
                      cin >> cardnum;
                      cout << "\nEnter YOUR CVV Number: ";
                      cin >> cvv;

}while (ch == 'y' || ch == 'Y');
cout << "\n\n Thank You Placing The Order";
cout<<"\n\n~~~~~~~~Invoice~~~~~~~~~\n";
    cout<<"\nItem ID\tName\tQuantity\tPrice\tAmount\n";
    for (int x = 0; x <= c; x++)
    {
        f.open("inventory.dat", ios::in);
        f.read((char *) &i, sizeof(i));
        while (!f.eof())
        {
            if (i.retitemno() == order_arr[x])
            {
                amt=i.retprice() * quan[x];
                cout<<"\n"<<order_arr[x]<<"\t"<<i.retiname()<<"\t"<<quan[x]<<"\t\t"<<i.retprice()<<"\t"<<amt;
                total+=amt;
            }
           f.read((char *) &i, sizeof(i));
        }
            f.close();

    }
    cout<<"\n\n\n\nTotal="<<total;
    Sleep(2000);
}


    void file_orders()
    {
        f1.open("orders.dat", ios::out | ios::app);
        i.place_order();
        f1.write((char*)&i,sizeof(i));
        f1.close();
        cout << "\n\nOrder Placed ";

    }

void admin_menu() {
    system("cls");
    char ch2;
    cout << "\n\n\t Admin Menu";
    cout << "\n\t1.Create Product";
    cout << "\n\t2.Display all Products";
    cout << "\n\t3.Search by specific product name ";
    cout << "\n\t4.Modify Product";
    cout << "\n\t5.Delete Product";
    cout << "\n\t6.Back To Main Menu";
    cout << "\n\n\tPlease Enter Your Choice(1-6)\t";
    cin >> ch2;
    switch (ch2) {
        case '1':
            system("cls");
            write_to_file();
            break;
        case '2':
            disp_all();
            break;
        case '3':
            char name[20];
            system("cls");
            cout << "\n\n\tPlease Enter The Product Name ";
            cin >> name;
            display_sp(name);
            break;
        case '4':
            modify();
            break;
        case '5':
            deleterec();

            break;
        case '6':
            menu();
            //getch();b
            break;
        default:
            cout << "\a";
            admin_menu();
    }


}
void user_menu()
{
    system("cls");
    char ch3;
    cout << "\n\n\tUser Menu";
    cout << "\n\t 1.List Products";
    cout << "\n\t 2.Search by Product Name ";
    cout << "\n\t 3.Buy Product ";
    cout << "\n\t 4.Back To Main Menu";
    cout << "\n\n\tPlease Enter Your Choice(1-4)\t";
    cin >> ch3;
    switch (ch3)
    {
        case '1': system("cls");
            menu();
            break;
        case '2':
            char name[20];
            system("cls");
            cout << "\n\n\tPlease Enter The Product Name ";
            cin >> name;
            display_sp(name);
            break;
        case '3'  :
            system("cls");
            file_orders();
            break;
        case '4' :
            admin_menu();
            break;
        default:
            cout << "\a";
    }

}

int main()
{
    char ch;
    do {
        system("cls");
        cout << "\n\n\n\tMain Menu ";
        cout << "\n\n\t 1. User";
        cout << "\n\n\t 2. Administrator";
        cout << "\n\n\t 3. Exit";
        cout << "\n\n\t Please Enter Your Choice (1-3) \t";
        cin >> ch;
        switch (ch)
        {
            case '1':
                system("cls");
                user_menu();
                break;
            case '2':
                admin_menu();
                break;
            case '3':
                exit(0);
                break;
            default:
                cout << "\a";

        }
    } while (ch != '3');
    return 0;
}
