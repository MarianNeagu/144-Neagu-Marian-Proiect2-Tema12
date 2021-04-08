#include <iostream>
#include <cstring>
#include <string>

#pragma region Clase
class Card
{
    std::string m_ownerName; // NUME PRENUME
    char* m_cardNr; // de obicei 16 cifre
    char* m_expirationDate; // DD/LL/AAAA
    int m_cvv; // 3 cifre
    double m_credit; // suma in RON

    public:
    // Constructori
    Card(): m_ownerName(NULL), m_cardNr(nullptr), m_expirationDate(nullptr), m_cvv(-1), m_credit(-1) {}

    Card(std::string ownerName, char* cardNr, const char* expirationDate, int cvv, double credit);


    //Constructor de copiere

    Card(const Card &card)
    {
        m_cardNr = new char[strlen(card.m_cardNr)];
        m_expirationDate = new char[strlen(card.m_expirationDate)];

        strcpy(m_cardNr, card.m_cardNr);
        m_ownerName = card.m_ownerName;
        strcpy(m_expirationDate, card.m_expirationDate);
        m_cvv = card.m_cvv;
        m_credit = card.m_credit;
    }

    // Destructor
    ~Card()
    {
        delete[] m_cardNr;
        m_cardNr = nullptr;
        delete[] m_expirationDate;
        m_expirationDate = nullptr;
    }

    // Getere&Setere
    char* GetCardNr();
    char* GetOwnerName();
    char* GetExpirationDate();
    int GetCVV();
    double GetCredit();

    void SetCardNr(const char* cardNr);
    void SetOwnerName(const char* ownerName);
    void SetExpirationDate(const char* expirationDate);
    void SetCVV(int cvv);
    void SetCredit(double credit);

    // Operatori
    Card& operator= (const Card &card)
    {
        // dezalocare memorie 
        delete[] m_cardNr;
        delete[] m_expirationDate;

        m_expirationDate = new char[10];
        m_cardNr = new char[strlen(card.m_cardNr)];

        // atribuire valori noi
        strcpy(m_expirationDate, card.m_expirationDate);
        strcpy(m_cardNr, card.m_cardNr);
        m_ownerName = card.m_ownerName;

        m_cvv = card.m_cvv;
        m_credit = card.m_credit;

        return *this;
    }
    friend std::istream& operator>> (std::istream& in,  Card& card);
    friend std::ostream& operator<< (std::ostream& out,  Card& card);

    // Metode

};

class CardStandard: public Card
{

};

class CardPremium: public CardStandard
{

};
#pragma endregion

#pragma region Constructori

// CARD
Card::Card(std::string ownerName, char* cardNr, const char* expirationDate, int cvv, double credit)
{
    m_cardNr = new char[strlen(cardNr)];
    m_expirationDate = new char[strlen(cardNr)];

    strcpy(m_cardNr, cardNr);
    m_ownerName = ownerName;
    strcpy(m_expirationDate, expirationDate);
    m_cvv = cvv;
    m_credit = credit;
}

#pragma endregion

#pragma region Getere&Setere
// Getere
char* Card::GetCardNr()
{
    return m_cardNr;
}
char* Card::GetOwnerName()
{
    return m_ownerName;
}
char* Card::GetExpirationDate()
{
    return m_expirationDate;
}
int Card::GetCVV()
{
    return m_cvv;
}
double Card::GetCredit()
{

    return m_credit;
}

// Setere
void Card::SetCardNr(const char* cardNr)
{
    strcpy(m_cardNr, cardNr);
}
void Card::SetOwnerName(const char* ownerName)
{
    m_ownerName = new char[strlen(ownerName)];
    strcpy(m_ownerName, ownerName);
}
void Card::SetExpirationDate(const char* expirationDate)
{
    strcpy(m_expirationDate, expirationDate);
}
void Card::SetCVV(int cvv)
{
    m_cvv = cvv;
}
void Card::SetCredit(double credit)
{
    m_credit = credit;
}
#pragma endregion

#pragma region Operatori

std::istream& operator>> (std::istream& in,  Card& card)
{
	// delete[] multime.m_set;
	// multime.m_numberOfNumbers = 0;
	// multime.m_set = nullptr;
    
    // dezalocare
    delete[] card.m_cardNr;
    delete[] card.m_expirationDate;

    card.m_cardNr = nullptr;
    card.m_ownerName = nullptr;
    card.m_expirationDate = nullptr;

    card.m_cvv = -1;
    card.m_credit = -1;

    std::string name;
    char* cardNr = nullptr; 
    char* expDate = nullptr;

    std::cout<<"~Introduceti datele~"<<std::endl;
    std::cout<<"Numele detinatorului: ";
    in>>name;
    card.m_ownerName = name;

    std::cout<<"Numerele cardului: ";
    in>>cardNr;
    card.m_cardNr = new char[strlen(cardNr)];
    strcpy(card.m_cardNr, cardNr);

    std::cout<<"Data expirarii: ";
    in>>expDate;
    card.m_expirationDate = new char[strlen(expDate)];
    strcpy(card.m_expirationDate, expDate);

    std::cout<<"CVV: ";
    in>>card.m_cvv;

    std::cout<<"Credit: ";
    in>>card.m_credit;


	// multime.m_set = new int[multime.m_numberOfNumbers];
    // for(int i = 0; i < multime.m_numberOfNumbers; i++)
	// 	in>>multime.m_set[i];
    

	return in;
}

std::ostream& operator<< (std::ostream& out, const Card& card)
{
	

	return out;
}

#pragma endregion
// CARD
void ShowDetails_Demo(Card card)
{
    std::cout<<"Nume: "<<card.GetOwnerName();
    std::cout<<std::endl;
    std::cout<<"Numar Card: "<<card.GetCardNr();
    std::cout<<std::endl;
    std::cout<<"Data expirare: "<<card.GetExpirationDate();
    std::cout<<std::endl;
    std::cout<<"CVV: "<<card.GetCVV();
    std::cout<<std::endl;
    std::cout<<"Credit curent: "<<card.GetCredit();
    std::cout<<std::endl;
}

void Demo()
{
    //Card card("9837983798379837", "POPESCU ION SIMION", "12/10/2023", 453, 0.0);
    Card card2;

    std::cin>>card2;

    //ShowDetails_Demo(card);
    ShowDetails_Demo(card2);

}

void test()
{
    std::string test;
    std::cout<<"Test: ";
    std::cin>>test;
    std::cout<<test;
}
int main()
{
    test();
    //Demo();
    return 0;
}