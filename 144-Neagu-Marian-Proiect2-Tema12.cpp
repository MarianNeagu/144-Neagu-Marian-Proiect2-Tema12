#include <iostream>
#include <cstring>

#pragma region Clase
class Card
{
    char* m_cardNr; // Cele 16 cifre
    char* m_ownerName; // NUME PRENUME
    char* m_expirationDate; // DD/LL/AAAA
    int m_cvv; // 3 cifre
    double m_credit; // suma in RON

    public:
    // Constructori
    Card(): m_ownerName(nullptr), m_cardNr(new char[16]), m_expirationDate(new char[10]) {}

    Card(const char* cardNr, const char* ownerName, const char* expirationDate, int cvv, double credit);


    //Constructor de copiere

    Card(const Card &card)
    {
        m_cardNr = new char[strlen(card.m_cardNr)];
        m_ownerName = new char[strlen(card.m_ownerName)];
        m_expirationDate = new char[strlen(card.m_expirationDate)];

        strcpy(m_cardNr, card.m_cardNr);
        strcpy(m_ownerName, card.m_ownerName);
        strcpy(m_expirationDate, card.m_expirationDate);
        m_cvv = card.m_cvv;
        m_credit = card.m_credit;
    }

    // Destructor
    ~Card()
    {
        delete[] m_ownerName;
        m_ownerName = nullptr;
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
Card::Card(const char* cardNr, const char* ownerName, const char* expirationDate, int cvv, double credit)
{
    m_cardNr = new char[strlen(cardNr)];
    m_ownerName = new char[strlen(cardNr)];
    m_expirationDate = new char[strlen(cardNr)];

    strcpy(m_cardNr, cardNr);
    strcpy(m_ownerName, ownerName);
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
    Card card("9837983798379837", "POPESCU ION SIMION", "12/10/2023", 453, 0.0);
    Card cardCopy(card);

    ShowDetails_Demo(card);
    ShowDetails_Demo(cardCopy);

}

int main()
{

    Demo();
    return 0;
}