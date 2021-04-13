#include <iostream>
#include <string>

class Card
{
protected:
	std::string m_ownerName; // NUME PRENUME
	std::string m_cardNr; // de obicei 16 cifre
	std::string m_expirationDate; // DD/LL/AAAA
	int m_cvv; // 3 cifre
	double m_credit; // suma in RON

public:
	// Constructori
	Card() : m_ownerName(""), m_cardNr(""), m_expirationDate(""), m_cvv(0), m_credit(0) {}

	Card(std::string ownerName, std::string cardNr, std::string expirationDate, int cvv, double credit);


	//Constructor de copiere

	Card(const Card& card)
	{
		m_ownerName = card.m_ownerName;
		m_cardNr = card.m_cardNr;
		m_expirationDate = m_expirationDate;
		m_cvv = card.m_cvv;
		m_credit = card.m_credit;
	}

	// Destructor
	virtual ~Card()
	{
		m_ownerName = "";
		m_cardNr = "";
		m_expirationDate = "";
		m_cvv = 0;
		m_credit = 0;
	}

	// Getere&Setere
	std::string GetCardNr();
	std::string GetOwnerName();
	std::string GetExpirationDate();
	int GetCVV();
	double GetCredit();

	void SetCardNr(std::string cardNr);
	void SetOwnerName(std::string ownerName);
	void SetExpirationDate(std::string expirationDate);
	void SetCVV(int cvv);
	void SetCredit(double credit);

	// Operatori
	Card& operator= (const Card& card)
	{
		// atribuire valori noi
		m_ownerName = card.m_ownerName;
		m_cardNr = card.m_cardNr;
		m_expirationDate = card.m_expirationDate;
		m_cvv = card.m_cvv;
		m_credit = card.m_credit;

		return *this;
	}
	friend std::istream& operator>> (std::istream& in, Card& card);
	friend std::ostream& operator<< (std::ostream& out, const  Card& card);

	// Metode
	virtual void Withdraw(double moneyToWithdraw) {}
};

class CardStandard : public Card
{
protected:
	int m_withdrawalLimit; // numar intreg
	double m_commissionExceedingLimit; // comision in procente
public:
	// Constructor
	CardStandard() : Card(), m_withdrawalLimit(0), m_commissionExceedingLimit(0) {}
	// Constructor cu parametrii
	CardStandard(std::string ownerName, std::string cardNr, std::string expirationDate, int cvv, double credit,
		int m_withdrawalLimit, double m_commissionExceedingLimit) : Card(m_ownerName, m_cardNr, m_expirationDate, m_cvv, m_credit) {}

	// Constructor de copiere
	CardStandard(const CardStandard& cardStandard)
	{
		m_ownerName = cardStandard.m_ownerName;
		m_cardNr = cardStandard.m_cardNr;
		m_expirationDate = cardStandard.m_expirationDate;
		m_cvv = cardStandard.m_cvv;
		m_credit = cardStandard.m_credit;
		m_withdrawalLimit = cardStandard.m_withdrawalLimit;
		m_commissionExceedingLimit = cardStandard.m_commissionExceedingLimit;
	}

	// Destructor
	~CardStandard()
	{
		m_ownerName = "";
		m_cardNr = "";
		m_expirationDate = "";
		m_cvv = 0;
		m_credit = 0;
		m_withdrawalLimit = 0;
		m_commissionExceedingLimit = 0;
	}

    // Get, Set
    int GetWithdrawalLimit();
    double GetCommissionExceedingLimit();
    
    void SetWithdrawalLimit(int withdrawalLimit);
    void SetCommissionExceedingLimit (double commissionExceedingLimit);

	// Operatori
	CardStandard& operator= (const CardStandard& cardStandard)
	{
		// atribuire valori noi
		m_ownerName = cardStandard.m_ownerName;
		m_cardNr = cardStandard.m_cardNr;
		m_expirationDate = cardStandard.m_expirationDate;
		m_cvv = cardStandard.m_cvv;
		m_credit = cardStandard.m_credit;
        m_withdrawalLimit = cardStandard.m_withdrawalLimit;
        m_commissionExceedingLimit = cardStandard.m_commissionExceedingLimit;
		return *this;
	}
	friend std::istream& operator>> (std::istream& in, CardStandard& cardStandard);
	friend std::ostream& operator<< (std::ostream& out, const  CardStandard& cardStandard);

	// Metode
	void Withdraw(double moneyToWithdraw);


};

#pragma region Metode Card Standard

void CardStandard::Withdraw(double moneyToWithdraw)
{
	// Daca nu are credit suficient
	if (m_credit < moneyToWithdraw)
	{
		std::cout << "Nu s-a putut efectua extragerea! Motiv: credit insuficient" << std::endl;
		return;
	}
	// Daca nu intrece comisionul
	else if (m_withdrawalLimit > moneyToWithdraw)
		m_credit -= moneyToWithdraw;
	// Daca intrece comisionul
	else
	{
		m_credit -= moneyToWithdraw;
		m_credit -= m_commissionExceedingLimit / 100 * moneyToWithdraw;
	}
	std::cout << "Extragere reusita!" << std::endl;
	std::cout << "Credit ramas: " << m_credit << std::endl;

}

#pragma endregion

class CardPremium : public CardStandard
{
protected:
	double m_cashback; // in procente
public:
	// Constructor
	CardPremium() : CardStandard(), m_cashback(0) {}

	// Constructor cu parametrii
	CardPremium(std::string ownerName, std::string cardNr, std::string expirationDate, int cvv, double credit, int m_withdrawalLimit, double m_commissionExceedingLimit) :
		CardStandard(m_ownerName, m_cardNr, m_expirationDate, m_cvv, m_credit, m_withdrawalLimit, m_commissionExceedingLimit) {}

	// Constructor de copiere
	CardPremium(const CardPremium& cardPremium)
	{
		m_ownerName = cardPremium.m_ownerName;
		m_cardNr = cardPremium.m_cardNr;
		m_expirationDate = cardPremium.m_expirationDate;
		m_cvv = cardPremium.m_cvv;
		m_credit = cardPremium.m_credit;
		m_withdrawalLimit = cardPremium.m_withdrawalLimit;
		m_commissionExceedingLimit = cardPremium.m_commissionExceedingLimit;
		m_cashback = cardPremium.m_cashback;
	}

	// Destructor
	~CardPremium()
	{
		m_ownerName = "";
		m_cardNr = "";
		m_expirationDate = "";
		m_cvv = 0;
		m_credit = 0;
		m_withdrawalLimit = 0;
		m_commissionExceedingLimit = 0;
		m_cashback = 0;
	}

    CardStandard& operator= (const CardPremium& cardPremium)
	{
		// atribuire valori noi
		m_ownerName = cardPremium.m_ownerName;
		m_cardNr = cardPremium.m_cardNr;
		m_expirationDate = cardPremium.m_expirationDate;
		m_cvv = cardPremium.m_cvv;
		m_credit = cardPremium.m_credit;
        m_cashback = cardPremium.m_cashback;
		return *this;
	}

    friend std::istream& operator>> (std::istream& in, CardPremium& cardPremium);
	friend std::ostream& operator<< (std::ostream& out, const  CardPremium& cardPremium);

    // Get, Set
    double GetCashback();
    void SetCashback(double cashback);


	// Metode
	void Withdraw(double moneyToWithdraw);
};

#pragma region Metode Card Premium

void CardPremium::Withdraw(double moneyToWithdraw)
{
	double cashback;
	// Daca nu are credit suficient
	if (m_credit < moneyToWithdraw)
	{
		std::cout << "Nu s-a putut efectua extragerea! Motiv: credit insuficient" << std::endl;
		return;
	}
	// Daca nu intrece comisionul
	else
	{
		m_credit -= moneyToWithdraw;
		cashback = (m_cashback / 100) * moneyToWithdraw;
		SetCredit(m_credit + cashback);
	}

	std::cout << "Extragere reusita! Ati primit cashback in valoare de: " << cashback << " RON." << std::endl;
	std::cout << "Credit ramas: " << m_credit << std::endl;

}

#pragma endregion



#pragma region Constructori

// CARD
Card::Card(std::string ownerName, std::string cardNr, std::string expirationDate, int cvv, double credit)
{

	m_ownerName = ownerName;
	m_cardNr = cardNr;
	m_expirationDate = expirationDate;
	m_cvv = cvv;
	m_credit = credit;
}

#pragma endregion

#pragma region Getere&Setere
// Getere
std::string Card::GetCardNr()
{
	return m_cardNr;
}
std::string Card::GetOwnerName()
{
	return m_ownerName;
}
std::string Card::GetExpirationDate()
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

int CardStandard::GetWithdrawalLimit()
{
    return m_withdrawalLimit;
}
double CardStandard::GetCommissionExceedingLimit()
{
    return m_commissionExceedingLimit;
}

double CardPremium::GetCashback()
{
    return m_cashback;
}

// Setere
void Card::SetCardNr(std::string cardNr)
{
	m_cardNr = cardNr;
}
void Card::SetOwnerName(std::string ownerName)
{
	m_ownerName = ownerName;
}
void Card::SetExpirationDate(std::string expirationDate)
{
	m_expirationDate = expirationDate;
}
void Card::SetCVV(int cvv)
{
	m_cvv = cvv;
}
void Card::SetCredit(double credit)
{
	m_credit = credit;
}

void CardStandard::SetWithdrawalLimit(int withdrawalLimit)
{
    m_withdrawalLimit = withdrawalLimit;
}
void CardStandard::SetCommissionExceedingLimit (double commissionExceedingLimit)
{
    m_commissionExceedingLimit = commissionExceedingLimit;
}

void CardPremium::SetCashback(double cashback)
{
    m_cashback = cashback;
}
#pragma endregion

#pragma region Operatori
// >>

// CARD
std::istream& operator>> (std::istream& in, Card& card)
{

	std::cout << "Numele detinatorului: ";
	std::getline(in, card.m_ownerName);
	std::cout << "Numerele cardului: ";
	std::getline(in, card.m_cardNr);

	std::cout << "Data expirarii: ";
	std::getline(in, card.m_expirationDate);

	std::cout << "CVV: ";
	in >> card.m_cvv;

	std::cout << "Credit: ";
	in >> card.m_credit;

	return in;
}
// CARD STANDARD
std::istream& operator>> (std::istream& in, CardStandard& cardStandard)
{
	// inca nu stiu de ce nu il ia pe primul
	std::getline(in, cardStandard.m_ownerName); // nu il ia

	std::cout << "Numele detinatorului: ";
	std::getline(in, cardStandard.m_ownerName);

	std::cout << "Numerele cardului: ";
	std::getline(in, cardStandard.m_cardNr);

	std::cout << "Data expirarii: ";
	std::getline(in, cardStandard.m_expirationDate);

	std::cout << "CVV: ";
	in >> cardStandard.m_cvv;

	std::cout << "Credit: ";
	in >> cardStandard.m_credit;

	std::cout << "Limita extragere fara comision: ";
	in >> cardStandard.m_withdrawalLimit;

	std::cout << "Comision la depasirea limitei (%): ";
	in >> cardStandard.m_commissionExceedingLimit;

	return in;
}
// CARD PREMIUM
std::istream& operator>> (std::istream& in, CardPremium& cardPremium)
{
	// inca nu stiu de ce nu il ia pe primul
	std::getline(in, cardPremium.m_ownerName); // nu il ia

	std::cout << "Numele detinatorului: ";
	std::getline(in, cardPremium.m_ownerName);

	std::cout << "Numerele cardului: ";
	std::getline(in, cardPremium.m_cardNr);

	std::cout << "Data expirarii: ";
	std::getline(in, cardPremium.m_expirationDate);

	std::cout << "CVV: ";
	in >> cardPremium.m_cvv;

	std::cout << "Credit: ";
	in >> cardPremium.m_credit;

	std::cout << "Cashback: ";
	in >> cardPremium.m_cashback;

	return in;
}
// <<

// CARD
std::ostream& operator<< (std::ostream& out, const Card& card)
{
	out << "Numele detinatorului:  " << card.m_ownerName;
	out << std::endl;
	out << "Numar Card: " << card.m_cardNr;
	out << std::endl;
	out << "Data expirare: " << card.m_expirationDate;
	out << std::endl;
	out << "CVV: " << card.m_cvv;
	out << std::endl;
	out << "Credit curent: " << card.m_credit;
	out << std::endl;

	return out;
}

// CARD STANDARD
std::ostream& operator<< (std::ostream& out, const CardStandard& cardStandard)
{
	out << "Numele detinatorului:  " << cardStandard.m_ownerName;
	out << std::endl;
	out << "Numar Card: " << cardStandard.m_cardNr;
	out << std::endl;
	out << "Data expirare: " << cardStandard.m_expirationDate;
	out << std::endl;
	out << "CVV: " << cardStandard.m_cvv;
	out << std::endl;
	out << "Credit curent: " << cardStandard.m_credit;
	out << std::endl;
	out << "Limita extragere fara comision: " << cardStandard.m_withdrawalLimit;
	out << std::endl;
	out << "Comision la depasirea limitei (%): " << cardStandard.m_commissionExceedingLimit;
	out << std::endl;

	return out;
}

// CARD PREMIUM
std::ostream& operator<< (std::ostream& out, const CardPremium& cardPremium)
{
	out << "Numele detinatorului:  " << cardPremium.m_ownerName;
	out << std::endl;
	out << "Numar Card: " << cardPremium.m_cardNr;
	out << std::endl;
	out << "Data expirare: " << cardPremium.m_expirationDate;
	out << std::endl;
	out << "CVV: " << cardPremium.m_cvv;
	out << std::endl;
	out << "Credit curent: " << cardPremium.m_credit;
	out << std::endl;
	out << "Cashback: " << cardPremium.m_cashback;
	out << std::endl;

	return out;
}

#pragma endregion


void MainMenu()
{
    CardStandard* cardS_aux = nullptr;
    CardPremium* cardP_aux = nullptr;

	CardStandard* cardS = nullptr;
	CardPremium* cardP = nullptr;
	int numberOfSCards;
	int numberOfPCards;
    static int numberOfTotalCards = 0;

	int comanda = -1;

	while (comanda != 0)
	{
		std::cout << std::endl;
		std::cout << "Intoduceti numarul operatiunii pe care doriti sa o executati: " << std::endl;
		std::cout << "0. Iesire" << std::endl;
		std::cout << "1. Citire si memorare a N carduri. " << std::endl;
		std::cout << "2. Afisare detalii card " << std::endl;
		std::cout << "3. Extragere credit de pe card. " << std::endl;
		std::cout << "4. Introducere carduri" << std::endl;
		std::cin >> comanda;

		// comanda 0
		if (comanda == 0)
			break;

		// comanda 1
		else if (comanda == 1)
		{
			int tipCard = 0;
			std::cout << "Introduceti tipul de carduri pe care sa le introduceti: " << std::endl;
			std::cout << "1. Card Standard" << std::endl;
			std::cout << "2. Card Premium" << std::endl;

			while (tipCard < 1 || tipCard > 2)
			{
				std::cout << "Comanda: ";
				std::cin >> tipCard;
				if (tipCard < 1 || tipCard > 2)
					std::cout << "Comanda necunoscuta! Reincercati" << std::endl;
			}

			if (tipCard == 1)
			{
				std::cout << "~Introduceti numarul de carduri pe care sa le introduceti: " << std::endl;
				std::cin >> numberOfSCards;
                numberOfTotalCards += numberOfSCards;
				cardS = new CardStandard[numberOfSCards];
				std::cout << "~Introduceti detaliile cardurilor: " << std::endl;
				for (int i = 0; i < numberOfSCards; i++)
				{
					std::cout << "~Cardul curent de citit: " << i + 1 << std::endl;
					std::cin >> cardS[i];
				}
			}
			else
			{

				std::cout << "~Introduceti numarul de carduri pe care sa le introduceti: " << std::endl;
				std::cin >> numberOfPCards;
                numberOfTotalCards += numberOfPCards;
				cardP = new CardPremium[numberOfPCards];
				for (int i = 0; i < numberOfPCards; i++)
				{
					std::cout << "~Cardul curent de citit: " << i + 1 << std::endl;
					std::cin >> cardP[i];
				}
			}
            std::cout<<"Cardurile au fost inregistrate cu succes. Au fost inregistrate in total "<<numberOfTotalCards<<" carduri"<<std::endl;
		}
		// comanda 2
		else if (comanda == 2)
		{

			int cardToDisplayIndex = -1;
			char tipCard = 'c';
			std::cout << "Alegeti cardul la care doriti afisate detaliile:" << std::endl;
			if (cardS)
			{
				std::cout << "a) Carduri standard:" << std::endl;
				for (int i = 0; i < numberOfSCards; i++)
				{
					std::cout << i + 1 << ". ";
					std::cout << cardS[i].GetOwnerName() << std::endl;

				}
			}
			if (cardP)
			{
				std::cout << "b) Carduri premium:" << std::endl;
				for (int i = 0; i < numberOfPCards; i++)
				{
					std::cout << i + 1 << ". ";
					std::cout << cardP[i].GetOwnerName() << std::endl;
				}
			}

			std::cout << "Tipul cardului (litera): ";
			std::cin >> tipCard;
			while (tipCard < 'a' || tipCard > 'b')
			{
				std::cout << "Tipul cardului (litera): ";
				std::cin >> tipCard;
				if (tipCard < 'a' || tipCard > 'b')
					std::cout << "Comanda necunoscuta! Reincercati" << std::endl;
			}
			std::cout << "Cardul de afisat (numar): ";
			std::cin >> cardToDisplayIndex;
			while (cardToDisplayIndex < 1)
			{
				std::cout << "Cardul de afisat (numar): ";
				std::cin >> cardToDisplayIndex;
				if (cardToDisplayIndex < 1)
					std::cout << "Comanda necunoscuta! Reincercati" << std::endl;
			}
			if (tipCard == 'a')
			{
				if (cardToDisplayIndex > numberOfSCards)
				{
					std::cout << "Cardul nu exista! Reincercati.." << std::endl;
				}
				else
				{
					std::cout << std::endl << "~Detaliile cardului~" << std::endl;
					std::cout << cardS[cardToDisplayIndex-1];
				}
			}
			else
			{
				if (cardToDisplayIndex > numberOfPCards)
				{
					std::cout << "Cardul nu exista! Reincercati.." << std::endl;
				}
				else
				{
					std::cout << std::endl << "Detaliile cardului:" << std::endl;
					std::cout << cardP[cardToDisplayIndex - 1];
				}
			}


		}
		
        // comanda 3
		else if (comanda == 3)
        {
            int cardToDisplayIndex = -1;
			char tipCard = 'c';
            double moneyToExtract = 0;
			std::cout << "Alegeti cardul din care doriti sa extrageti credit" << std::endl;
			if (cardS)
			{
				std::cout << "a) Carduri standard:" << std::endl;
				for (int i = 0; i < numberOfSCards; i++)
				{
					std::cout << i + 1 << ". ";
					std::cout << cardS[i].GetOwnerName() << std::endl;

				}
			}
			if (cardP)
			{
				std::cout << "b) Carduri premium:" << std::endl;
				for (int i = 0; i < numberOfPCards; i++)
				{
					std::cout << i + 1 << ". ";
					std::cout << cardP[i].GetOwnerName() << std::endl;
				}
			}

			std::cout << "Tipul cardului (litera): ";
			std::cin >> tipCard;
			while (tipCard < 'a' || tipCard > 'b')
			{
				std::cout << "Tipul cardului (litera): ";
				std::cin >> tipCard;
				if (tipCard < 'a' || tipCard > 'b')
					std::cout << "Comanda necunoscuta! Reincercati" << std::endl;
			}
			std::cout << "Cardul din care sa extrageti (numar): ";
			std::cin >> cardToDisplayIndex;
			while (cardToDisplayIndex < 1)
			{
				std::cout << "Cardul din care sa extrageti (numar): ";
				std::cin >> cardToDisplayIndex;
				if (cardToDisplayIndex < 1)
					std::cout << "Comanda necunoscuta! Reincercati" << std::endl;
			}
            std::cout<<"Introduceti suma de extras: ";
            std::cin>>moneyToExtract;
			if (toupper(tipCard) == 'A')
			{
				if (cardToDisplayIndex > numberOfSCards)
				{
					std::cout << "Cardul nu exista! Reincercati.." << std::endl;
				}
				else // EXTRAGERE
				{
                    cardS->Withdraw(moneyToExtract);
				}
			}
			else 
			{
				if (cardToDisplayIndex > numberOfPCards)
				{
					std::cout << "Cardul nu exista! Reincercati.." << std::endl;
				}
				else // EXTRAGERE
				{
					cardP->Withdraw(moneyToExtract);
				}
			}
        }

    	// comanda 4
        else if (comanda == 4)
        {
            
            int tipCard = 0;
            std::cout << "Alegeti tipul de carduri pe care sa le introduceti: "<<std::endl;
			std::cout << "1. Card Standard" << std::endl;
			std::cout << "2. Card Premium" << std::endl;

			while (tipCard < 1 || tipCard > 2)
			{
				std::cout << "Comanda: ";
				std::cin >> tipCard;
				if (tipCard < 1 || tipCard > 2)
					std::cout << "Comanda necunoscuta! Reincercati" << std::endl;
			}

			if (tipCard == 1)
			{
                int numberOfSCards_copy = numberOfSCards;
				std::cout << "~Introduceti numarul de carduri pe care sa le introduceti: " << std::endl;
				std::cin >> numberOfSCards;
                cardS_aux = new CardStandard[numberOfSCards + numberOfSCards_copy]; // in el pun toate valorile
                
                for(int i = 0; i < numberOfSCards_copy; i++)
                    cardS_aux[i] = cardS[i];  // pun element cu element in aux, mai raman numberOfSCards elemente
                delete[] cardS;

                cardS = new CardStandard[numberOfSCards + numberOfSCards_copy];
				
				std::cout << "~Introduceti detaliile cardurilor: " << std::endl;

				for (int i = numberOfSCards_copy; i < numberOfSCards + numberOfSCards_copy; i++)
				{
					std::cout << "~Cardul curent de citit: " << i + 1 << std::endl;
					std::cin >> cardS[i];
				}
                
                // acum le pun si pe cele dinainte
                 for(int i = 0; i < numberOfSCards_copy; i++)
                    cardS[i] = cardS_aux[i];

                delete[] cardS_aux;

                numberOfTotalCards += numberOfSCards;
                numberOfSCards += numberOfSCards_copy; // totalul cardurilor standarde citite
			}
			else
			{
                int numberOfPCards_copy = numberOfPCards;
				std::cout << "~Introduceti numarul de carduri pe care sa le introduceti: " << std::endl;
				std::cin >> numberOfPCards;
                cardP_aux = new CardPremium[numberOfPCards + numberOfPCards_copy]; // in el pun toate valorile
                
                for(int i = 0; i < numberOfPCards_copy; i++)
                    cardP_aux[i] = cardP[i];  // pun element cu element in aux, mai raman numberOfSCards elemente
                delete[] cardP;

                cardP = new CardPremium[numberOfPCards + numberOfPCards_copy];
				
				std::cout << "~Introduceti detaliile cardurilor: " << std::endl;

				for (int i = numberOfPCards_copy; i < numberOfPCards + numberOfPCards_copy; i++)
				{
					std::cout << "~Cardul curent de citit: " << i + 1 << std::endl;
					std::cin >> cardP[i];
				}
                
                // acum le pun si pe cele dinainte
                 for(int i = 0; i < numberOfPCards_copy; i++)
                    cardP[i] = cardP_aux[i];

                delete[] cardP_aux;

                numberOfTotalCards += numberOfPCards;
                numberOfPCards += numberOfPCards_copy; // totalul cardurilor premium citite
            }
        }
        
        else std::cout << "Comanda introdusa nu e acceptata!" << std::endl;

	}
	std::cout << "Iesire..";
}

int main()
{
	//Mesaj la inceput
	std::cout<<"Neagu Marian-Madalin - Tema 8. Clasa ~Multime~"<<std::endl<<std::endl;
	std::cout<<"Introdu y pentru a porni sau n pentru a iesi: ";
	char comanda;
	std::cin>>comanda;
	while(toupper(comanda) != 'Y')
	{
		if(toupper(comanda) == 'N')
			return 0;
		else
			std::cout<<"Comanda neacceptata.."<<std::endl;
		std::cout<<"Introdu y pentru a porni sau n pentru a iesi: ";
		std::cin>>comanda;
	}

	MainMenu();
	return 0;
}