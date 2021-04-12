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

	// Operatori

	CardStandard& operator= (const CardStandard& cardStandard)
	{
		// atribuire valori noi
		m_ownerName = cardStandard.m_ownerName;
		m_cardNr = cardStandard.m_cardNr;
		m_expirationDate = cardStandard.m_expirationDate;
		m_cvv = cardStandard.m_cvv;
		m_credit = cardStandard.m_credit;

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
		cashback = m_cashback / 100 * moneyToWithdraw;
		m_credit += cashback;
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

// TODO: getere+setere standard+premium
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
#pragma endregion

#pragma region Operatori
// TODO: >> << Card Premium
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

#pragma endregion

void Demo()
{
	//Card card("9837983798379837", "POPESCU ION SIMION", "12/10/2023", 453, 0.0);
	CardStandard cardS;
	Card* card;
	card = &cardS;

	card->Withdraw(3);


	// ShowDetails_Demo(card);

}




void MainMenu()
{
    CardStandard* cardS_aux = nullptr;
    CardPremium* cardP_aux = nullptr;

	CardStandard* cardS = nullptr;
	CardPremium* cardP = nullptr;
	int numberOfSCards;
	int numberOfPCards;
    static int numberOfTotalCards;

	int comanda = -1;

	while (comanda != 0)
	{
		std::cout << std::endl;
		std::cout << "Intoduceti numarul operatiunii pe care doriti sa o executati: " << std::endl;
		std::cout << "0. Iesire" << std::endl;
		std::cout << "1. Citire si memorare a N carduri. " << std::endl;
		std::cout << "2. Afisare detalii card " << std::endl;
		std::cout << "3. Extragere credit de pe card. " << std::endl;
		std::cout << "4. Stergere carduri." << std::endl;
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

				cardP = new CardPremium[numberOfPCards];
				for (int i = 0; i < numberOfPCards; i++)
				{
					std::cout << "~Cardul curent de citit: " << i + 1 << std::endl;
					std::cin >> cardP[i];
				}
			}
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
			if (tipCard == 'a')
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
		
        else if (comanda == 4)
        {

        }
        
        else std::cout << "Comanda introdusa nu e acceptata!" << std::endl;

	}
	std::cout << "Iesire..";
}

int main()
{
	// CardStandard* card = new CardStandard[2];
	// for(int i = 0; i<2;i++)
	//     std::cin>>card[i];

	// Mesaj la inceput
	// std::cout<<"Neagu Marian-Madalin - Tema 8. Clasa ~Multime~"<<std::endl<<std::endl;
	// std::cout<<"Introdu y pentru a porni sau n pentru a iesi: ";
	// char comanda;
	// std::cin>>comanda;
	// while(toupper(comanda) != 'Y')
	// {
	// 	if(toupper(comanda) == 'N')
	// 		return 0;
	// 	else
	// 		std::cout<<"Comanda neacceptata.."<<std::endl;
	// 	std::cout<<"Introdu y pentru a porni sau n pentru a iesi: ";
	// 	std::cin>>comanda;
	// }

	 //Demo();



	// CardStandard* cardS = new CardStandard[2];
	// std::cin>>cardS[1];
	// std::cout<<cardS[1];


	MainMenu();
	return 0;
}