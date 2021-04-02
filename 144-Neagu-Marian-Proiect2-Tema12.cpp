#include <iostream>
#include <cstring>

#pragma region Clase
class Card
{
    char* m_cardNr; // "1234567890123456"
    char* m_ownerName; // "NUME PRENUME"
    char m_expirationDate[10]; // DD/LL/AAAA
    int m_cvv; // 123
    double m_credit; 

    public:
    // Constructori, destructor
    Card(){m_ownerName = nullptr; m_cardNr = new char[16];}

    ~Card()
    {
        delete[] m_ownerName;
        m_ownerName = nullptr;
        delete[] m_cardNr;
        m_cardNr = nullptr;
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
}

void Demo()
{
    Card card;
    card.SetCardNr("9837983798379837");
    card.SetOwnerName("POPESCU ION SIMION");
    card.SetExpirationDate("12/10/2023");
    card.SetCVV(453);
    card.SetCredit(14.45);

    ShowDetails_Demo(card);

}

int main()
{

    Demo();
    return 0;
}