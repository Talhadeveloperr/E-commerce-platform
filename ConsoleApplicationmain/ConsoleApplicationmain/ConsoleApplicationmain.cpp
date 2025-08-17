//header files
#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
#include <ctime>
#include <cstdio>
#include<cstdlib>
#include<windows.h>



using namespace std;


// Validation 
bool isValidLength( string& input, size_t minLength, size_t maxLength) {
    return input.length() >= minLength && input.length() <= maxLength;
}
string encryptDecrypt(const string& input, const string& key) {
    string output = input;
    for (int i = 0; i < input.size(); ++i)
        output[i] = input[i] ^ key[i % key.size()];
    return output;
}
int encrypt(int input, int key) {
    return input ^ key; 
}

/*********<<ADDRESS CLASS>>***********/
//aggregated by register class
class Address
{
private:
    string block;
    string houseName;
    string city;
    string zip;

public:
    // Default constructor
    Address(string b = "", string h = "", string c = "", string z = "")
    {
        block = b;
        houseName = h;
        city = c;
        zip = z;
    }

    // Mutator or set function
    void setAddress()
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 9);
        cout << "\t\tENTER YOUR BLOCK NO    :";
        cin >> block;
        cin.ignore();
        while (!isValidLength(block, 1, 3)) {
            cout << "Invalid input. Please enter a number with 4 to 10 digits: ";
            cin >> block;
        }
        cout << "\t\tENTER YOUR HOUSE NAME  :";
        getline(cin, houseName);
        cout << "\t\tENTER YOUR CITY NAME   :";
        getline(cin, city);
        cout << "\t\tENTER YOUR POST CODE   :";
        cin >> zip;
    }

    // Get function
    string getFullAddress()
    {
        return block + "," + houseName + "," + city + "," + zip + ".";
    }
};





class AdminRegister : public Address {
private:
    string fullName;
   
    string username;
    string password;
    string retrive_un;
    string retrive_pw;
   

public:
    AdminRegister(); // default constructor
    void setFullName();
    string getFullName();
    
    void enter(); // ask for registration
    void DoRegistration(); // user registration form
    void DoLogin(); // this function ask and verify id pass for user
    ~AdminRegister(); // destructor
};

AdminRegister::AdminRegister() {
    username = password = retrive_un = retrive_pw = "";
    
}

void AdminRegister::enter() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
    int choice;
    cout << endl
        << "\t\t(1) REGISTRATION \n"
        << "\t\t(2) LOG-IN\n"
        << "\t\tchoice an option :";
    cin >> choice;
    system("cls");
    if (choice == 1)
    {
        DoRegistration();
    }
    else if (choice == 2)
    {
        DoLogin();
    }
    else
    {
        DoLogin();
    }

}

void AdminRegister::DoRegistration() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 8);
    cout << "\t\t\t __________________________________" << endl
        <<  "\t\t\t |                                 |"<<endl
        <<  "\t\t\t |                                 |"<<endl
        <<  "\t\t\t |      ACCOUNT REGISTRATION       |" << endl
        <<  "\t\t\t |                                 |"<<endl
        <<  "\t\t\t |                                 |"<<endl
        <<  "\t\t\t |_________________________________|" << endl
        << endl
        << endl;
    setFullName();
    
    cout << endl
        << endl;
    
    SetConsoleTextAttribute(h, 6);
    cout << "\t\t ENTER ANY USER NAME :";
    cin >> username;
    cout << "\t\t ENTER ANY PASSWORD  :";
    string key = "mysecretkey";
    char ch;
    
    while ((ch = _getch()) != '\r') { 
            password.push_back(ch);
            cout << '*'; 
    }
    string encryptedPassword = encryptDecrypt(password, key);
    string decryptedPassword = encryptDecrypt(encryptedPassword, key);
    //cin >> password;
    while (!isValidLength(password, 4, 6)) {
        cout << "Invalid input. Please enter a number with 4 to 6 digits: "<<endl;
        cin >> password;
    }
    ofstream file;
    file.open("admindetails.txt", ios::binary | ios::app);
    if (!file) {
        SetConsoleTextAttribute(h, 4);
        cout << "\tunable to open file for writing" << endl;
    }
    file << username << endl;
    file << decryptedPassword << endl;
    file << getFullName() << endl;
    

    file.close();
    int choice;
    SetConsoleTextAttribute(h, 5);
    cout << "\n\t DEAR SIR ,YOUR REGISTRATION SUCCESSFULL" << endl;

B:
    SetConsoleTextAttribute(h, 6);
    cout << "\n\t Please choose what you would like to do"
        << "\n\t\t(1) LOG IN"
        << "\n\t\t(2) EXIT"
        << "\n\t\t Choose an option";
    cin >> choice;
    if (choice == 1)
    {

    }
    else if (choice == 2)
    {
        exit(0);
    }
    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\n Input Error \n";
        goto B;
    }

}

void AdminRegister::DoLogin() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
    std::system("cls");
    cout << "\t\t\t________________________________________" << endl
        <<  "\t\t\t|                                       |"<<endl
        <<  "\t\t\t|          USER LOG IN                  |" << endl
        <<  "\t\t\t|                                       |"<<endl
        <<  "\t\t\t________________________________________" << endl
        << endl
        << endl;
    SetConsoleTextAttribute(h, 3);
    cout << "\t ENTER YOUR USER NAME :";
    cin >> username;
    cout << "\t ENTER YOUR PASSWORD  :";
    cin >> password;

    

    ifstream read("admindetails.txt", ios::binary);
    if (!read)
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\tunable to open file for reading" << endl;
    }
    getline(read, retrive_un);
    getline(read, retrive_pw);

    try //exception handling
    {
        if (retrive_un == username )
        {
            SetConsoleTextAttribute(h, 5);
            cout << endl
                << "\tCongratulations login successful..." << endl
                << endl;
            getline(read, fullName);
           
            SetConsoleTextAttribute(h, 8);
            cout << "\tFULL NAME    :" << fullName << endl;
            


        }
        else
        {
            throw 0;
        }
    }
    catch (...)
    {
        SetConsoleTextAttribute(h, 4);
        cout << endl
            << "\tSorry login unsuccessful (try again)" << endl;
        DoLogin();
    }
}




void AdminRegister::setFullName() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9);
    cout << "\t\tENTER YOUR FULL NAME   :";
    cin.ignore();
    getline(cin, fullName);

}

string AdminRegister::getFullName() {
    return fullName;
}


AdminRegister::~AdminRegister() {
   
}


class Register : public Address {
private:
    string fullName;
    string gender;
    string phoneNo;
    string email;
    Address* address; // aggregation
    string username;
    string password;
    string retrive_un;
    string retrive_pw;
    string Readdress = "";

public:
    Register(); // default constructor
    void setFullName();
    string getFullName();
    void setGender();
    string getGender();
    void setPhoneNo();
    string getPhoneNo();
    void setEmail();
    string getEmail();
    void setAddress();
    string getAddress();
    string getReAddress();
    void enter(); // ask for registration
    void DoRegistration(); // user registration form
    void DoLogin(); // this function ask and verify id pass for user
    ~Register(); // destructor
};

Register::Register() {
    username = password = retrive_un = retrive_pw = "";
    address = new Address; // Assuming Address class exists
}

void Register::enter() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
    int choice;
    cout << endl
        << "\t\t(1) REGISTRATION \n"
        << "\t\t(2) LOG-IN\n"
        << "\t\tchoice an option :";
    cin >> choice;
    system("cls");
    if (choice == 1)
    {
        DoRegistration();
    }
    else if (choice == 2)
    {
        DoLogin();
    }
    else
    {
        DoLogin();
    }

}

void Register::DoRegistration() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 8);
    cout << "\t\t\t __________________________________" << endl
        << "\t\t\t |                                 |" << endl
        << "\t\t\t |                                 |" << endl
        << "\t\t\t |      ACCOUNT REGISTRATION       |" << endl
        << "\t\t\t |                                 |" << endl
        << "\t\t\t |                                 |" << endl
        << "\t\t\t |_________________________________|" << endl
        << endl
        << endl;
    setFullName();
    setGender();
    setPhoneNo();
    setEmail();
    address->setAddress();
    cout << endl
        << endl;

    SetConsoleTextAttribute(h, 6);
    cout << "\t\t ENTER ANY USER NAME :";
    cin >> username;
    cout << "\t\t ENTER ANY PASSWORD  :";
    string key = "mysecretkey";
    char ch;

    while ((ch = _getch()) != '\r') {
        password.push_back(ch);
        cout << '*';
    }
    string encryptedPassword = encryptDecrypt(password, key);
    string decryptedPassword = encryptDecrypt(encryptedPassword, key);
    //cin >> password;
    while (!isValidLength(password, 4, 6)) {
        cout << "Invalid input. Please enter a number with 4 to 6 digits: " << endl;
        cin >> password;
    }
    ofstream file;
    file.open("aBook.txt", ios::binary | ios::app);
    if (!file) {
        SetConsoleTextAttribute(h, 4);
        cout << "\tunable to open file for writing" << endl;
    }
    file << username << endl;
    file << decryptedPassword << endl;
    file << getFullName() << endl;
    file << getGender() << endl;
    file << getPhoneNo() << endl;
    file << getEmail() << endl;
    file << getAddress() << endl;

    file.close();
    int choice;
    SetConsoleTextAttribute(h, 5);
    cout << "\n\t DEAR SIR ,YOUR REGISTRATION SUCCESSFULL" << endl;

B:
    SetConsoleTextAttribute(h, 6);
    cout << "\n\t Please choose what you would like to do"
        << "\n\t\t(1) LOG IN"
        << "\n\t\t(2) EXIT"
        << "\n\t\t Choose an option";
    cin >> choice;
    if (choice == 1)
    {

    }
    else if (choice == 2)
    {
        exit(0);
    }
    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\n Input Error \n";
        goto B;
    }

}

void Register::DoLogin() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
    std::system("cls");
    cout << "\t\t\t________________________________________" << endl
        << "\t\t\t|                                       |" << endl
        << "\t\t\t|          USER LOG IN                  |" << endl
        << "\t\t\t|                                       |" << endl
        << "\t\t\t________________________________________" << endl
        << endl
        << endl;
    SetConsoleTextAttribute(h, 3);
    cout << "\t ENTER YOUR USER NAME :";
    cin >> username;
    cout << "\t ENTER YOUR PASSWORD  :";
    cin >> password;



    ifstream read("aBook.txt", ios::binary);
    if (!read)
    {
        SetConsoleTextAttribute(h, 4);
        cout << "\tunable to open file for reading" << endl;
    }
    getline(read, retrive_un);
    getline(read, retrive_pw);

    try //exception handling
    {
        if (retrive_un == username)
        {
            SetConsoleTextAttribute(h, 5);
            cout << endl
                << "\tCongratulations login successful..." << endl
                << endl;
            getline(read, fullName);
            getline(read, gender);
            getline(read, phoneNo);
            getline(read, email);
            getline(read, Readdress);
            SetConsoleTextAttribute(h, 8);
            cout << "\tFULL NAME    :" << fullName << endl;
            cout << "\tGENDER       :" << gender << endl;
            cout << "\tPHONE NO     :" << phoneNo << endl;
            cout << "\tEMAIL ADDRESS: " << email << endl;
            cout << "\tADDRESS      :" << Readdress << endl;


        }
        else
        {
            throw 0;
        }
    }
    catch (...)
    {
        SetConsoleTextAttribute(h, 4);
        cout << endl
            << "\tSorry login unsuccessful (try again)" << endl;
        DoLogin();
    }
}




void Register::setFullName() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9);
    cout << "\t\tENTER YOUR FULL NAME   :";
    cin.ignore();
    getline(cin, fullName);

}

string Register::getFullName() {
    return fullName;
}

void Register::setGender() {
A:
    cout << "\t\tARE YOU MALE or FEMALE :";
    cin >> gender;
    if ((gender == "Male") || (gender == "male") || (gender == "Female") || (gender == "female"))
    {

    }
    else
    {

        cout << "\t\tInput Error!Please try again.\n";
        goto A;
    }
}

string Register::getGender() {
    return gender;
}

void Register::setPhoneNo() {
    cout << "\t\tENTER YOUR PHONE NO    :";
    cin >> phoneNo;
    while (!isValidLength(phoneNo, 11, 12)) {
        cout << "Invalid input. Please enter a number with 11 to 12 digits: ";
        cin >> phoneNo;
    }
}

string Register::getPhoneNo() {
    return phoneNo;
}

void Register::setEmail() {
    cout << "\t\tENTER YOUR EMAIL ADRS  :";
    cin.ignore();
    getline(cin, email);

}

string Register::getEmail() {
    return email;
}

void Register::setAddress() {
    address->setAddress();
}

string Register::getAddress() {
    return address->getFullAddress();
}

string Register::getReAddress() {
    return Readdress;
}

Register::~Register() {
    delete address;
}



/********************<<Product Class>>****************/
// Forward declaration of ProductList class
class ProductList;

class Product {
private:
    string productID;
    string productName;
    double productPrice;

public:
    Product(string ID = "", string Name = "", double Price = 0.0) {
        productID = ID;
        productName = Name;
        productPrice = Price;
    }

    void setID(string i) {
        productID = i;
    }

    void setNAME(string n) {
        productName = n;
    }

    void setPRICE(double p) {
        productPrice = p;
    }

    string getID() {
        return productID;
    }

    string getNAME() {
        return productName;
    }

    double getPRICE() {
        return productPrice;
    }

    void displayProduct() {
        cout << setw(10) << productID << setw(20) << productName << setw(20) << productPrice << endl;
    }
};

class ProductList :public Product {
private:
    vector<Product> productList;

public:
    void products(vector<Product>& p) {
        productList = p;
    }

    void displayProductList() {
        cout << setw(15) << "ProductID" << setw(17) << "ProductName" << setw(20) << "ProductPrice\n";
        for (int i = 0; i < productList.size(); i++) {
            productList[i].displayProduct();
        }
    }

    virtual void addProduct(string i, string n, double p) {
        productList.push_back(Product(i, n, p)); // Use Product constructor directly
    }

    void removeProduct(string z) {
        int RE = -1;
        for (int i = 0; i < productList.size(); i++) {
            if (productList[i].getID() == z) {
                RE = i;
                break;
            }
        }
        if (RE != -1) {
            productList.erase(productList.begin() + RE);
        }
        else {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            cout << "\tProduct with ID " << z << " not found." << endl;
        }
    }
    void  modifyProduct(string z) {

        int RE = -1;
        for (int i = 0; i < productList.size(); i++) {
            if (productList[i].getID() == z) {
                RE = i;
                productList.erase(productList.begin() + RE);

                string id, n;
                double p;
                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, 2);
                cout << "\n\tGive product Id   :";
                cin >> id;
                cout << "\n\tGive product name :";
                cin >> n;
                cout << "\n\tGive Product price:";
                cin >> p;
                productList.push_back(Product(id, n, p));
                
                SetConsoleTextAttribute(h, 1);
                cout << "\t\t Result Updated " << endl;

                


            }
        }


    }
};

/******************Admin class>>********************/
class Administrator :public AdminRegister, public ProductList
    //inheritance,polymorphism
{
private:
    string adminID;
public:
    Administrator() {

    }

    void Adminlogin()
    {
        AdminRegister::enter();
    }
    

    virtual void addProduct()//poly
    {
        int count;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 3);
        cout << "\n\t       ADD PRODUCTS       \n"
            << "\tHow many products do you want to add :";
        cin >> count;

        for (int i = 0; i < count; i++)
        {
            SetConsoleTextAttribute(h, 5);
            string id, name;
            double price;
            cout << "\t#" << i + 1 << endl
                <<  "\tGive product Id     :";
            cin >> id; 
            cout << "\tGive product name   :";
            cin >> name;
            cout << "\tGive Product price  :";
            cin >> price;

            ProductList::addProduct(id, name, price);

        }
        cout << endl;
    }
    void removeProduct()
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 6);
        int count;
        string id;
        system("cls");
        cout << "\n\t      REMOVE PRODUCT         \n"
            << "\tHow Many Products You Want To Remove :";
        cin >> count;

        for (int i = 0; i < count; i++)
        {
            ProductList::displayProductList();

            cout << "\tMention Product id :";
            cin >> id;
            ProductList::removeProduct(id);
            cout << endl;
        }
    }
    void modifyProduct()
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 8);
        int count;
        string id;
        system("cls");
        cout << "\n\t       Modify Product          \n"
            << "\tHow Many Products You Want To modify :";
        cin >> count;
        for (int i = 0; i < count; i++)
        {
            ProductList::displayProductList();

            cout << "\tMention Product id :";
            cin >> id;
            ProductList::modifyProduct(id);
            cout << endl;
        }

    }
    void viewAllProducts()
    {
        ProductList::displayProductList();
    }
};

/**********************<<ShoppingCart Class>>******************/
class ShoppingCart {
protected:
    vector<Product> SelectedProduct;
    double TotalPrice = 0.0;

public:
    ShoppingCart() {
    }

    void CalcTotalPrice() {
        for (int i = 0; i < SelectedProduct.size(); i++) {
            TotalPrice += SelectedProduct[i].getPRICE();
        }
    }

    double getTotalPrice() {
        return TotalPrice;
    }

    int getTotalQuantity() {
        return SelectedProduct.size();
    }

    void addSelectedProduct(vector<Product> p) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 9);
        int count;
        cout << "\n\n\t ADD TO SHOPPING CART \n"
            << "\tHOW MANY PRODUCTS YOU WANT TO PURCHASE ?"<<endl;
        cin >> count;

        for (int i = 0; i < count; i++) {
            cout << "\t#" << i + 1 << endl
                << "\tWRITE PRODUCT ID :";
            string id;
            cin >> id;

            for (int j = 0; j < p.size(); j++) {
                if (p[j].getID() == id) {
                    SelectedProduct.push_back(Product(p[j].getID(), p[j].getNAME(), p[j].getPRICE()));
                }
            }
        }
        cout << endl;
    }

    void removeProduct() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 2);
        string id;
        cout << "\tWRITE PRODUCT ID :";
        cin >> id;

        for (int i = 0; i < SelectedProduct.size(); i++) {
            if (SelectedProduct[i].getID() == id) {
                SelectedProduct.erase(SelectedProduct.begin() + i);
                break;
            }
        }
        cout << endl;
    }

    void displaySelectedProduct() {
        system("cls");
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 5);
        cout << "\t\t------------------------------" << endl
             << "\t\t|                             |" << endl
             << "\t\t|             MY              |" << endl
             << "\t\t---------SHOPPING CART -------" << endl
             << "\t\t|                             |" << endl
             << "\t\t|                             |" << endl
             << "\t\t|_____________________________|" << endl
             << endl
            << endl;
        SetConsoleTextAttribute(h, 6);
        cout << setw(15) << "PRODUCT-ID" << setw(17) << "PRODUCT-NAME" << setw(20) << "PRODUCT-PRICE\n";

        for (int i = 0; i < SelectedProduct.size(); i++) {
            SelectedProduct[i].displayProduct();
        }
        cout << endl;
    }
};

/***************<<Payment class>>******************/
class Payment //composition class
{
private:
    double PayNetAmmount;
    string cardNumber, digit;
    int pinNumber;int payment;
    string ibankUserId, ibankingPassword;

public:
    Payment()
    {
    }
    Payment(double PayNetAmmount, string cardNumber, int pinNumber, string ibankUserId, string ibankingPassword)
    {
        this->PayNetAmmount = PayNetAmmount;
        this->cardNumber = cardNumber;
        this->pinNumber = pinNumber;
        this->ibankUserId = ibankUserId;
        this->ibankingPassword = ibankingPassword;
    }

    void setPayNetAmmount(double PayNetAmmount)
    {
        this->PayNetAmmount = PayNetAmmount;
    }

    void setCaardNumber(string cardNumber)
    {
        this->cardNumber = cardNumber;
    }

    void setPinNumber(int pinNumber)
    {
        this->pinNumber = pinNumber;
    }

    void setIbankUserId(string ibankUserId)
    {
        this->ibankUserId = ibankUserId;
    }

    double getPayNetAmmount()
    {
        return PayNetAmmount;
    }

    string getCardNumber()
    {
        return cardNumber;

    }

    int getPinNumber()
    {
        return pinNumber;
    }

    int getpayment()
    {
        return payment;
    }

    string getIbankUserId()
    {
        return ibankUserId;
    }

    string getIbankingPassword()
    {
        return ibankingPassword;
    }

    string getdigit()
    {
        return digit;
    }

    void paymentpreference()
    {

    A:
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 3);
        cout << "\t\t\t------------------------------------------" << endl
            <<  "\t\t\t|                                         |" << endl
            <<  "\t\t\t|    PLEASE CHOOSE ANY PAYMENGT GATEWAY   |" << endl
            <<  "\t\t\t|                                         |"<<endl
            <<  "\t\t\t|                                         |" << endl
            <<  "\t\t\t|_________________________________________|" << endl
            <<  "\t\t(1) DEBIT/CREDIT CARD" << endl
            <<  "\t\t(2) ON-LINE BANKING " << endl
            <<  "\t\t Choose any option-";
        cin >> payment;
        std::system("cls");

        switch (payment)
        {
        case 1:
            SetConsoleTextAttribute(h, 5);
            cout << "\t\t------------------------------------" << endl
                 << "\t\t|                                  |" << endl
                 << "\t\t|    DEBIT/CREDIT CARD PAYMENT     |" << endl
                 << "\t\t|                                  |" << endl
                 << "\t\t------------------------------------" << endl
                << endl;
            SetConsoleTextAttribute(h, 6);
            cout << "\tENTER YOUR CARD NO :";
            cin >> cardNumber;
            while (!isValidLength(cardNumber, 4, 11)) {
                cout << "Invalid input. Please enter a number with 4 to 11 digits: ";
                cin >> cardNumber;
            }
            cout << "\tENTER YOUR PIN NO  :";

            
            
            cin >> pinNumber;
            
            
            SetConsoleTextAttribute(h, 7);
            cout << "\n \tNET-AMOUNT :" << PayNetAmmount << "RM.CARD NO:*******************";
            for (int i = (cardNumber.length() - 4.0); i <= cardNumber.length(); i++)
            {
                digit += cardNumber[i];
            }
            SetConsoleTextAttribute(h, 8);
            cout << "\t" << digit << "\n";
            cout << "\tRM" << PayNetAmmount << "HAS BEEN DEDUCTED FROM YOUR ACCOUNT \n\n\n"
                <<  "\t\t -------------------------------" << endl
                <<  "\t\t|                              |" << endl
                <<  "\t\t|   [PAYMENT SUCCESSFUL]       |" << endl
                <<  "\t\t|                              |" << endl
                <<  "\t\t -------------------------------" << endl
                << endl
                << endl;

            SetConsoleTextAttribute(h, 9);
            cout << "\tFOR RECEIPT";
            system("pause");
            system("cls");
            break;

        case 2:
            SetConsoleTextAttribute(h, 2);
            cout << "\t\t -------------------------------" << endl
                <<  "\t\t|                               |" << endl
                <<  "\t\t|    ONLINE BANKING SYSTEM      |" << endl
                <<  "\t\t|                               |" << endl
                <<  "\t\t -------------------------------" << endl
                << endl;
            SetConsoleTextAttribute(h, 3);
            cout << "\t  ENTER YOUR ON-LINE BANKING ID  :";
            cin >> ibankUserId;
            while (!isValidLength(ibankUserId, 4, 10)) {
                cout << "Invalid input. Please enter a number with 4 to 10 digits: ";
                cin >> ibankUserId;
            }
            cout << "\t  ENTER YOUR PASSWORD            :";
            cin >> ibankingPassword;
            while (!isValidLength(ibankingPassword, 4, 5)) {
                cout << "Invalid input. Please enter a number with 4 to 5 digits: ";
                cin >> ibankingPassword;
            }
            SetConsoleTextAttribute(h, 5);
            cout << "\n\t RM " << PayNetAmmount << "HAS BEEN DEDUCTED FROM YOUR ACCOUNT \n\n\n";
            SetConsoleTextAttribute(h, 6);
            cout << "\t\t-------------------------------" << endl
                <<  "\t\t|                             |" << endl
                <<  "\t\t|    [PAYMENT SUCCESSFUL]     |" << endl
                <<  "\t\t|                             |" << endl
                <<  "\t\t-------------------------------" << endl
                << endl
                << endl;
            SetConsoleTextAttribute(h, 7);
            cout << "\tFOR RECEIPT";
            std::system("pause");
            break;


        default:
            goto A;
            SetConsoleTextAttribute(h, 4);
            cout << "\n\t Input Error!";

        }
    }

};

/*************<<Customer class>>************************/
class Customer :public  Register, public ShoppingCart//inheritance
{
private:
    Payment payment;
    int count;
public:
    Customer()
    {

    }
   
    void setCustomerDetails()
    {
        Register::enter();
    }

    void print()

    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 8);
        time_t now = time(0);
        char dt[26]; 
        ctime_s(dt, sizeof(dt), &now);
        system("cls");
        cout << "\t\t**************************************" << endl
            <<  "\t\t|                                    |" << endl
            <<  "\t\t|           Customer Invoice         |" << endl
            <<  "\t\t|                                    |" << endl
            <<  "\t\t**************************************" << endl
            <<  "\t\t|                                    |" << endl
            <<endl
            <<  "\t\t E Commerce Shopping Management System" << endl
             << endl
             << endl
             << endl
            << endl;
        for (int i = 0; i < 1; i++)
        {
            int value = rand();
            cout << "\t\tTransaction Number    :XX783RGFH" << value << "\n";

        }
        SetConsoleTextAttribute(h, 9);
        cout << "\t\tDate and Time is        : " << dt << endl;
        cout << "\t\tCustomter Name          :" << Register::getFullName() << endl
            <<  "\t\tCustomer Gender         :" << Register::getGender() << endl
            <<  "\t\tCustomerr Contact number:" << Register::getPhoneNo() << endl
            <<  "\t\tCustomer Emails         :" << Register::getEmail() << endl
            <<  "\t\tShipping Address        :" << Register::getReAddress() << endl
            << endl
            << setw(15) 
            <<  "\t\tPRODUCT-ID " << setw(17) << " PRODUCT-NAME " << setw(20) << " PRODUCT-PRICE \n";

        for (int i = 0; i < SelectedProduct.size(); i++)
        {
            cout <<"\t\t" << setw(10) << ShoppingCart::SelectedProduct[i].getID() << setw(20)
                 <<"\t\t" << ShoppingCart::SelectedProduct[i].getNAME() << setw(20)
                 <<"\t\t" << ShoppingCart::SelectedProduct[i].getPRICE() << endl;
        }
        SetConsoleTextAttribute(h, 2);
        cout << "\n\t\tTotal Item     :" << ShoppingCart::getTotalQuantity() << endl
            <<  "\t\tTotal Cost       :" << ShoppingCart::getTotalPrice() << " RM" << endl
            << endl;
        if (payment.getpayment() == 1)
        {
            cout << "\t\tCart payment  :" << ShoppingCart::getTotalPrice() << endl
                <<  "\t\tCart Digit    : *************";
            cout << "\t\t" << payment.getdigit();
            cout << "\n\n";

        }
        else {
            SetConsoleTextAttribute(h, 3);
            cout << "\t\tYour On-line banking ID";
            cout << "\t\t" << payment.getIbankUserId() << endl;
            cout << "\t\tRM" << ShoppingCart::getTotalPrice() << "has been deducted from your account" << endl;
        }
        SetConsoleTextAttribute(h, 5);
        cout << "\n\n\t\t**********************" << endl
            << endl
            << "\t\tExchange and refund may be applied   \n"
            << "\t\twihtin 3 days with original tax invoice"
            << "\t\t       Thanks FOR YOUR PATIENCE   \n";
        Customer::Receipt();
        Customer::ReadReceiptFromFile();
        std::system("pause");
        exit(0);

    }

    void ShoppingCartDetails(vector<Product> p)
    {
        ShoppingCart::addSelectedProduct(p);
        ShoppingCart::displaySelectedProduct();
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 6);
        cout << "\n\tDo You Want to remove any product?\n"
            <<  "\t  (1) NO \n"
            <<  "\t  (2) Yes \n"
            <<  "\t Choose an option";
        cin >> count;
        if (count == 2)
        {
            ShoppingCart::removeProduct();
        }
        
        ShoppingCart::displaySelectedProduct();
        ShoppingCart::CalcTotalPrice();
        SetConsoleTextAttribute(h, 7);
        cout << "\n\t\t Total Item   :" << ShoppingCart::getTotalQuantity() << endl
            <<  "\n\t\t total Cost   :" << ShoppingCart::getTotalPrice() << "RS " << endl
            << endl;

    }

    void PaymentWork()
    {
        payment.setPayNetAmmount(ShoppingCart::getTotalPrice());
        payment.paymentpreference();
    }

    void Receipt() {
        time_t now = time(0);
        char dt[26]; // ctime_s requires a buffer of at least 26 bytes
        ctime_s(dt, sizeof(dt), &now);

        ofstream outfile("receipt.txt", ios::binary | ios::app);
        if (!outfile.is_open()) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            cout << "\tUnable to open file for writing" << endl;
            return;
        }
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 7);

        outfile << "*********************************************\n"
                << "|            CUSTOMER INVOICE                  |\n"
                << "*********************************************\n"
                << "     E-COMMERCE SHOPPING MANAGEMENT SYSTEM\n\n";

        outfile << "Date and Time is            : " << dt << endl;
        outfile << "Customer Name               : " << Register::getFullName() << endl
                << "Customer Gender             : " << Register::getGender() << endl
                << "Customer Contact number     : " << Register::getPhoneNo() << endl
                << "Customer Email              : " << Register::getEmail() << endl
                << "Shipping Address            : " << Register::getAddress() << endl
                << endl
               << setw(15) << "PRODUCT-ID" << setw(17) << "PRODUCT-NAME" << setw(20) << "PRODUCT-PRICE\n";

        for (size_t i = 0; i < ShoppingCart::SelectedProduct.size(); i++) {
            outfile << setw(10) << ShoppingCart::SelectedProduct[i].getID() << setw(20)
                << ShoppingCart::SelectedProduct[i].getNAME() << setw(20)
                << ShoppingCart::SelectedProduct[i].getPRICE() << endl;
        }

        outfile << "\nTotal Item     :" << ShoppingCart::getTotalQuantity() << endl
                << "Total Cost       :" << ShoppingCart::getTotalPrice() << " RS" << endl
               << endl;

        if (payment.getpayment() == 1) {
            outfile << "Card payment  :" << ShoppingCart::getTotalPrice() << endl
                    << "Card Digits   : *************" << endl;
        }
        else {
            outfile << "Your Online Banking ID: " << payment.getIbankUserId() << endl
                    << "RM " << ShoppingCart::getTotalPrice() << " has been deducted from your account" << endl;
        }

        outfile << "\n\n********************************************\n\n"
                << "Exchange and refund may be applied within 3 days with original tax invoice.\n"
                << "       Thanks FOR YOUR PATIENCE\n";

        cout << "Receipt saved successfully.\n";
        outfile.close();
    }

    void ReadReceiptFromFile() {
        ifstream infile("receipt.txt",ios::binary);
        if (!infile.is_open()) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            cout << "\tUnable to open file for reading" << endl;
            return;
        }

        string line;
        
            while (getline(infile, line)) {
                
                //cout << line << endl;
            }
        

        infile.close();
    }
};




int main() {
    Administrator admin;
    Customer customer;
    ProductList pList;
    Product pdt;
    vector<Product> product(10);
    product[0] = Product("11", "Shirt", 130.50);
    product[1] = Product("12", "Jeans", 200.30);
    product[2] = Product("13", "Mobile", 4500.00);
    product[3] = Product("14", "Keyboard", 72.70);
    product[4] = Product("15", "Mouse", 55.90);
    product[5] = Product("16", "Body spray", 28.80);
    product[6] = Product("17", "Facewash", 18.50);
    product[7] = Product("18", "Headphone", 900.00);
    product[8] = Product("19", "Watch", 599.99);
    product[9] = Product("20", "Belt", 99.99);

    admin.products(product);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "\t\t\t\t***********************************************" << endl;
    cout << "\t\t\t\t|                                             |" << endl;
    cout << "\t\t\t\t|                                             |" << endl;
    cout << "\t\t\t\t|   WELCOME TO E-COMMERCE MANAGEMENT SYSTEM   |" << endl;
    cout << "\t\t\t\t|                                             |" << endl;
    cout << "\t\t\t\t|                                             |" << endl;
    cout << "\t\t\t\t***********************************************" << endl << endl;
    cout << endl;
    cout << endl;
    cout << "\t\t\tSubmitted to:" << endl;
    cout << endl;
    cout << "\t\t\t\tDr Muhammad Usman Ali" << endl;
    cout << endl;
    cout << endl;
    int loginChoice;
    do {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 3);
        cout << "\t\tLogin Options:" << endl;
        cout << "\t\t1. Customer Login" << endl;
        cout << "\t\t2. Admin Login" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> loginChoice;

        if (loginChoice == 1)
        {
            // Customer login
            
            bool Clogin = false;
            do {
                
                if (!Clogin) {

                   customer.enter();
                    Clogin = true;
                    //customer.DoLogin();
                    // Proceed if logged in successfully
                    if (Clogin) {
                        SetConsoleTextAttribute(h, 6);
                        cout << "\n\t\tWelcome back, " << customer.getFullName() << "!" << endl << endl;

                        // Display available products after login
                        SetConsoleTextAttribute(h, 7);
                        cout <<"\t\tAvailable Products:" << endl;
                        //for (size_t i = 0; i < product.size(); ++i) {
                       //     cout << "\t\tProduct ID: " << product[i].getID() << ", Name: " << product[i].getNAME() << ", Price: " << product[i].getPRICE() << " RM" << endl;
                       // }
                        admin.viewAllProducts();

                        // Shopping
                        int buyChoice;
                        SetConsoleTextAttribute(h, 8);
                        cout << "\n\tDo you want to buy products? (1: Yes, 0: No): ";
                        cin >> buyChoice;


                        if (buyChoice == 1) {


                            customer.ShoppingCartDetails(product);


                            // Proceed to payment
                            int paymentChoice;
                            SetConsoleTextAttribute(h, 8);
                            cout << "\n\tDo you want to proceed to payment? (1: Yes, 0: No): ";
                            cin >> paymentChoice;

                            if (paymentChoice == 1) {
                                customer.PaymentWork();
                                cout << "\n\tPayment Successful!" << endl;
                                //customer.Receipt();
                                //customer.ReadReceiptFromFile();
                                customer.print();

                            }
                            else {
                                return 0;
                            }
                        }
                        else {
                            return 0;
                        }

                    }
                    else {
                        SetConsoleTextAttribute(h, 4);
                        cout << "\n\tLogin failed. Please try again." << endl;
                    }
                }
                

            } while (loginChoice > 2 && loginChoice <0);
        }
        else if (loginChoice == 2) {
            // Admin login
            SetConsoleTextAttribute(h, 3);
            cout << "\n\t\t\tAdmin Login:" << endl;
            admin.Adminlogin();
            // Proceed with admin operations
            // ...
            int adminChoice;
            do {
                SetConsoleTextAttribute(h, 4);
                cout << "\n\t\tAdmin Menu:" << endl;
                SetConsoleTextAttribute(h, 5);
                cout << "\t1. Add Product" << endl;
                cout << "\t2. Remove Product" << endl;
                cout << "\t3. View All Products" << endl;
                cout << "\t4. Modify the Product" << endl;
                cout << "\t5. Logout" << endl;
                cout << "\tEnter your choice: ";
                cin >> adminChoice;




                switch (adminChoice) {
                case 1:
                    admin.addProduct();
                    break;
                case 2:
                    admin.removeProduct();
                    break;
                case 3:
                    // Display available products after login
                    admin.viewAllProducts();
                    break;
                case 4:
                    admin.modifyProduct();
                    break;
                case 5:
                    exit(0);
                    break;
                default:
                    SetConsoleTextAttribute(h, 4);
                    cout << "\tInvalid choice. Please try again." << endl;
                }

            } while (adminChoice != 5);
        }
        else {
            SetConsoleTextAttribute(h, 4);
            cout << "\tInvalid choice. Please try again." << endl;
        }

    } while (loginChoice != 1 && loginChoice != 2);
    SetConsoleTextAttribute(h, 2);
    cout << "\n\t\tThank you for using our system. Goodbye!" << endl;

    return 0;
}
//0 Bla 1 blu 2 green 3 aqua 4 r 5 pur 6 y 7 white 8 gray 9 blue
//  system 1 b 2 g 3 a 4 r 5  pur 6 y 7 white a g b r e b f y g magento h cyn e g
//time_t now=time(0);
//char *dt=ctime(&now);