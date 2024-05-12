#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class Senzor // pentru masurarea calitatii apei potabile
{
private:
	string producator;
	int nrMasuratori_pH;
	float* valori_pH = nullptr;
	float concentratieClor;
	float temperaturiApa[5];     // ultimele 5 masuratori ale temperaturii apei in grade Celsius
	int turbiditate;            // masoara transparenta apei ; unitate de masura-UNT (Unitati Nefelometrice de Turbiditate)
	char* cartier = nullptr;   // locatia in care este amplasat senzorul
	unsigned int stareSenzor; // masoara durata de viata a senzorului in procente ; sub un anumit prag se va recomanda inlocuirea
	int adancimeSenzor;
	bool remoteAccess;
	const int id;
	static int nrSenzori;

public:
	//Constructor DEFAULT
	Senzor() :id(nrSenzori++)
	{
		this->producator = "Standard";
		this->nrMasuratori_pH = 0;
		this->valori_pH = NULL;
		this->concentratieClor = 0;
		for (int i = 0; i < 5; i++)
			this->temperaturiApa[i] = i;
		this->turbiditate = 5;
		this->cartier = new char[strlen("Necunoscut") + 1];
		strcpy_s(cartier, strlen("Necunoscut") + 1, "Necunoscut");
		this->stareSenzor = 100;
		this->adancimeSenzor = 20;
		this->remoteAccess = true;
	}
	//Constructor cu toti parametrii
	Senzor(string producator, int nrMasuratori_pH, float* valori_pH, float concentratieClor, const float(&temperaturiApa)[5], int turbiditate, const char* cartier,
		unsigned int stareSenzor, int adancimeSenzor, bool remoteAccess) :id(nrSenzori++)
	{
		this->producator = producator;
		this->nrMasuratori_pH = nrMasuratori_pH;
		this->valori_pH = new float[this->nrMasuratori_pH];
		for (int i = 0; i < this->nrMasuratori_pH; i++)
			this->valori_pH[i] = valori_pH[i];
		this->concentratieClor = concentratieClor;
		for (int i = 0; i < 5; i++)
			this->temperaturiApa[i] = temperaturiApa[i];
		this->turbiditate = turbiditate;
		this->cartier = new char[strlen(cartier) + 1];
		strcpy_s(this->cartier, strlen(cartier) + 1, cartier);
		this->stareSenzor = stareSenzor;
		this->adancimeSenzor = adancimeSenzor;
		this->remoteAccess = remoteAccess;
	}
	//Constructor de copiere
	Senzor(const Senzor& s) :id(nrSenzori++)
	{
		this->producator = s.producator;
		this->nrMasuratori_pH = s.nrMasuratori_pH;

		if (this->valori_pH != nullptr) delete[]this->valori_pH;
		this->valori_pH = new float[this->nrMasuratori_pH];
		for (int i = 0; i < this->nrMasuratori_pH; i++)
			this->valori_pH[i] = s.valori_pH[i];

		this->concentratieClor = s.concentratieClor;
		for (int i = 0; i < 5; i++)
			this->temperaturiApa[i] = s.temperaturiApa[i];

		this->turbiditate = s.turbiditate;
		if (this->cartier != nullptr) delete[]this->cartier;
		this->cartier = new char[strlen(s.cartier) + 1];
		strcpy_s(this->cartier, strlen(s.cartier) + 1, s.cartier);

		this->stareSenzor = s.stareSenzor;
		this->adancimeSenzor = s.adancimeSenzor;
		this->remoteAccess = s.remoteAccess;
	}
	//DESTRUCTOR
	~Senzor()
	{
		if (valori_pH!=NULL)
			delete[]valori_pH;
	}
	//Supraincarcarea operatorului =
	Senzor operator=(const Senzor& s)
	{
		this->producator = s.producator;
		this->nrMasuratori_pH = s.nrMasuratori_pH;

		if (this->valori_pH != nullptr) delete[]this->valori_pH;
		this->valori_pH = new float[this->nrMasuratori_pH];
		for (int i = 0; i < this->nrMasuratori_pH; i++)
			this->valori_pH[i] = s.valori_pH[i];

		this->concentratieClor = s.concentratieClor;
		for (int i = 0; i < 5; i++)
			this->temperaturiApa[i] = s.temperaturiApa[i];

		this->turbiditate = s.turbiditate;
		if (this->cartier != nullptr) delete[]this->cartier;
		this->cartier = new char[strlen(s.cartier) + 1];
		strcpy_s(this->cartier, strlen(s.cartier) + 1, s.cartier);

		this->stareSenzor = s.stareSenzor;
		this->adancimeSenzor = s.adancimeSenzor;
		this->remoteAccess = s.remoteAccess;

		return *this;
	}
	//Functie de afisare senzor in consola
	void afisareSenzor()
	{
		cout << this->id << ". " << "\tSenzorul marca " << this->producator << " este amplasat in cartierul " << this->cartier << " la adancimea de " << this->adancimeSenzor <<
			" metri ; are gradul de uzura " << 100 - this->stareSenzor << "%. ";
		if (this->remoteAccess == true)
			cout << "Permite conectarea de la distanta.";
		else cout << "Nu permite conectarea de la distanta.";
		cout << endl << endl << "\t\tValorile masurate de senzorul " << this->producator << ":" << endl << "----> Concentratie clor: " << this->concentratieClor << " mg/l" << endl << "----> Turbiditatea apei: "
			<< this->turbiditate << " UNT" << endl << "----> Valorile pH-ului inregistrate in ultimele " << this->nrMasuratori_pH << " zile:";
		for (int i = 0; i < this->nrMasuratori_pH; i++)
			cout << " | " << this->valori_pH[i]; if (this->nrMasuratori_pH) cout << " | ";
		cout << endl << "----> Ultimele 5 masuratori ale temperaturii apei in grade Celsius: | ";
		for (int i = 0; i < 5; i++)
			cout << this->temperaturiApa[i] << " | ";
		cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	//Supraincarcarea operatorului <<
	friend ostream& operator<<(ostream& afisare, Senzor& s)
	{
		afisare << s.id << ". " << "\tSenzorul marca " << s.producator << " este amplasat in cartierul " << s.cartier << " la adancimea de " << s.adancimeSenzor <<
			" metri ; are gradul de uzura " << 100 - s.stareSenzor << "%. ";
		if (s.remoteAccess == true)
			afisare << "Permite conectarea de la distanta.";
		else afisare << "Nu permite conectarea de la distanta.";
		afisare << endl << endl << "\t\tValorile masurate de senzorul " << s.producator << ":" << endl << "----> Concentratie clor: " << s.concentratieClor << " mg/l" << endl << "----> Turbiditatea apei: "
			<< s.turbiditate << " UNT" << endl << "----> Valorile pH-ului inregistrate in ultimele " << s.nrMasuratori_pH << " zile:";
		for (int i = 0; i < s.nrMasuratori_pH; i++)
			afisare << " | " << s.valori_pH[i]; if (s.nrMasuratori_pH) afisare << " | ";
		afisare << endl << "----> Ultimele 5 masuratori ale temperaturii apei in grade Celsius: | ";
		for (int i = 0; i < 5; i++)
			afisare << s.temperaturiApa[i] << " | ";
		afisare << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return afisare;
	}
	//Supraincarcarea operatorului >>
	friend istream& operator>>(istream& citire, Senzor& s)
	{
		cout << "Producator: ";
		getline(citire, s.producator);
		
		cout << "Adancime senzor: ";
		citire >> s.adancimeSenzor;

		cout << "Stare senzor (in procente): ";
		citire >> s.stareSenzor;

		cin.ignore();
		cout << "Cartier: ";
		s.cartier = new char[32];
		cin.getline(s.cartier, 32);

		cout << "Permite remote access? (1/0): ";
		citire >> s.remoteAccess;

		cout << "Concentratie clor: ";
		citire >> s.concentratieClor;

		cout << "Turbiditate: ";
		citire >> s.turbiditate;

		cout << "Nr. zile in care s-a masurat pH-ul: ";
		citire >> s.nrMasuratori_pH;
		s.valori_pH = new float[s.nrMasuratori_pH];
		for (int i = 0; i < s.nrMasuratori_pH; i++)
		{
			cout << "Valoarea pH-ului in ziua " << i + 1 << ": ";
			citire >> s.valori_pH[i];
		
		}
		cout << "Ultimele 5 temperaturi ale apei: ";
		for (int i = 0; i < 5; i++) citire >> s.temperaturiApa[i];

		cin.ignore(); // necesar daca este nevoie sa citim 2 obiecte consecutiv de la tastatura
		return citire;
	}
	
	//GETTERI	
	void getValori_pH() { for (int i = 0; i < this->nrMasuratori_pH; i++)	cout << this->valori_pH[i] << " "; cout << endl; }
	float getValori_pH_Index(int pozitie)
	{
		if (pozitie >= 0 && pozitie < this->nrMasuratori_pH)
			return this->valori_pH[pozitie];
		else throw "Index invalid";
	}

	void getTemperaturiApa() { for (int i = 0; i < 5; i++) cout << this->temperaturiApa[i] << " "; cout << endl; }
	float getTemperaturiApaIndex(int pozitie)
	{
		if (pozitie >= 0 && pozitie < 5)
			return this->temperaturiApa[pozitie];
		else throw "Index invalid";
	}

	string getProducator() { return this->producator; }
	int getNrMasuratori_pH() { return this->nrMasuratori_pH; }
	float getConcentratieClor() { return this->concentratieClor; }
	int getTurbiditate() { return this->turbiditate; }
	char* getCartier() { return this->cartier; }
	unsigned int getStareSenzor() { return this->stareSenzor; }
	int getAdancimeSenzor() { return this->adancimeSenzor; }
	bool getRemoteAccess() { return this->remoteAccess; }
	int getID() { return this->id; }
	int getNrSenzori() { return nrSenzori - 1; }

	//SETTERI
	void setProducator(string producatorNou)
	{
		if (producatorNou.length() > 0) this->producator = producatorNou;
	}
	void setConcentratieClor(float concentratieClorNoua)
	{
		if (concentratieClorNoua >= 0) this->concentratieClor = concentratieClorNoua;
	}
	void setTurbiditate(int turbiditateNoua)
	{
		if (turbiditateNoua >= 0) this->turbiditate = turbiditateNoua;
	}
	void setCartier(const char* cartierNou)
	{
		if (strlen(cartierNou) > 0)
		{
			delete[]this->cartier;
			this->cartier = new char[strlen(cartierNou) + 1];
			strcpy_s(this->cartier, strlen(cartierNou) + 1, cartierNou);
		}
	}
	void setStareSenzor(unsigned int stareSenzorNoua)
	{
		if (stareSenzorNoua >= 0) this->stareSenzor = stareSenzorNoua;
	}
	void setRemoteAccess(bool remoteAccessNou)
	{
		if (remoteAccessNou == 1) this->remoteAccess = 1;
		else if (remoteAccessNou == 0) this->remoteAccess = 0;
	}
	void setAdancimeSenzor(int adancimeSenzorNoua)
	{
		if (adancimeSenzorNoua >= 0) this->adancimeSenzor = adancimeSenzorNoua;
	}
	static void setNrSenzori(int nrSenzoriNou)
	{
		if (nrSenzoriNou > 0) nrSenzori = nrSenzoriNou;
	}
	void setNrMasuratori_pH(int nrMasuratori_pH_Nou)
	{
		if (nrMasuratori_pH_Nou > 0) this->nrMasuratori_pH = nrMasuratori_pH_Nou;
	}
	void setValori_pH(int nrMasuratoriNou, float* valori_pH_Noi)
	{
		if (nrMasuratoriNou > 0 && valori_pH_Noi[0] != NULL)
		{
			setNrMasuratori_pH(nrMasuratoriNou);
			delete[]this->valori_pH;
			this->valori_pH = new float[nrMasuratori_pH];
			for (int i = 0; i < nrMasuratoriNou; i++)
				this->valori_pH[i] = valori_pH_Noi[i];
		}
	}
	void setValoare_pH_Index(float valoare_pH, int pozitie)
	{
		if (pozitie >= 0 && pozitie < this->nrMasuratori_pH)
			this->valori_pH[pozitie] = valoare_pH;
	}
	void setValoriTemperaturiApa(const float(&temperaturiApaNoi)[5]) // se actualizeaza exact ultimele 5 valori ale temperaturii 
	{
		if (temperaturiApaNoi[0] != NULL)
			for (int i = 0; i < 5; i++)
				this->temperaturiApa[i] = temperaturiApaNoi[i];
	}
	void setValoareTemperaturaIndex(int pozitie, float temperaturaNoua)
	{
		if (pozitie >= 0 && pozitie <= 4)
			this->temperaturiApa[pozitie] = temperaturaNoua;
	}
	//Supraincarcarea operatorului + in cazul obiect+int: se aduna o valoare la fiecare dintre ultimele 5 masuratori ale temperaturii
	Senzor operator+(float temp)
	{
		Senzor aux = *this;
		for (int i = 0; i < 5; i++)
			aux.temperaturiApa[i] += temp;

		return aux;
	}
	//Supraincarcarea operatorului -- (forma pre-fixata)
	Senzor operator--() 
	{
		adancimeSenzor--;
		return *this;
	}
	//Supraincarcarea operatorului [] cu aruncare de exceptii
	float operator[](int index) 
	{
		try
		{
			if (index >= 0 && index < nrMasuratori_pH)
				return this->valori_pH[index];
			else  throw out_of_range("Index invalid");
		}
		catch (const exception& e)
		{
			cerr << "Eroare: " << e.what() << endl;
		}
		
	}
	//Supraincarcarea operatorului ++ (forma post-fixata)
	Senzor operator++(int)
	{
		for (int i = 0; i < 5; i++)
			temperaturiApa[i]++;
		return *this;
	}

	float get_pH_Mediu()
	{
		try
		{
			float suma = 0;
			if (this->nrMasuratori_pH == 0) throw runtime_error("Nu exista valori inregistrate ale pH-ului (nu se poate face impartirea la zero)");

			for (int i = 0; i < this->nrMasuratori_pH; i++)
				suma += valori_pH[i];
			
			return suma / this->nrMasuratori_pH;
		}
		catch (const exception& e)
		{
			cerr << "Eroare: " << e.what() << endl;
		}
	}
	//Supraincarcarea operatorului ()
	float operator()()
	{
		return get_pH_Mediu();
	}

	//SCRIERE Senzor in FISIER
	friend fstream& operator<<(fstream& fout, Senzor& s)
	{
		fout << s.id << ". " << "\tSenzorul marca " << s.producator << " este amplasat in cartierul " << s.cartier << " la adancimea de " << s.adancimeSenzor <<
			" metri ; are gradul de uzura " << 100 - s.stareSenzor << "%. ";
		if (s.remoteAccess == true)
			fout << "Permite conectarea de la distanta.";
		else fout << "Nu permite conectarea de la distanta.";
		fout << endl << endl << "\t\tValorile masurate de senzorul " << s.producator << ":" << endl << "----> Concentratie clor: " << s.concentratieClor << " mg/l" << endl << "----> Turbiditatea apei: "
			<< s.turbiditate << " UNT" << endl << "----> Valorile pH-ului inregistrate in ultimele " << s.nrMasuratori_pH << " zile:";
		for (int i = 0; i < s.nrMasuratori_pH; i++)
			fout << " | " << s.valori_pH[i]; if (s.nrMasuratori_pH) fout << " | ";
		fout << endl << "----> Ultimele 5 masuratori ale temperaturii apei in grade Celsius: | ";
		for (int i = 0; i < 5; i++)
			fout << s.temperaturiApa[i] << " | ";
		fout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return fout;
	}
	//CITIRE Senzor din FISIER
	friend fstream& operator>>(fstream& fin, Senzor& s)
	{
		getline(fin, s.producator);
		fin >> s.adancimeSenzor;
		fin >> s.stareSenzor;
		fin.ignore();
		s.cartier = new char[32];
		fin.getline(s.cartier, 32);
		fin >> s.remoteAccess;
		fin >> s.concentratieClor;
		fin >> s.turbiditate;
		fin >> s.nrMasuratori_pH;
		s.valori_pH = new float[s.nrMasuratori_pH];
		for (int i = 0; i < s.nrMasuratori_pH; i++)
			fin >> s.valori_pH[i];

		for (int i = 0; i < 5; i++)
			fin >> s.temperaturiApa[i];

		fin.ignore(); fin.ignore(); // necesar daca este nevoie sa citim mai multe obiecte consecutiv
		return fin;
	}

};

int Senzor::nrSenzori = 1;

class SenzorPremium : public Senzor
{
private: 
	float nitrati;                 // masurat in mg/l
	bool eColi;                   // neaparat zero, altfel apa nu este potabila
	int* conductivitate=nullptr; // conductivitatea apei indica totalitatea sarurilor minerale (K, Ca, Mg, Fe) dizolvate in apa - ultimele "dim" masuratori
	int dim;

public:
	//Constructor default
	SenzorPremium() :Senzor()
	{
		this->nitrati = 0;
		this->eColi = 0;
		this->dim = 0;
		this->conductivitate = nullptr;
	}
	//Constructor cu toti parametrii
	SenzorPremium(string producator, int nrMasuratori_pH, float* valori_pH, float concentratieClor, const float(&temperaturiApa)[5], int turbiditate, const char* cartier,
		unsigned int stareSenzor, int adancimeSenzor, bool remoteAccess, float nitrati, bool eColi, int dim, int* conductivitate):Senzor( producator,  nrMasuratori_pH,  valori_pH,
			concentratieClor, temperaturiApa,  turbiditate, cartier, stareSenzor,  adancimeSenzor,  remoteAccess)
	{
		this->nitrati = nitrati;
		this->eColi = eColi;
		this->dim = dim;
		this->conductivitate = new int[this->dim];
		for (int i = 0; i < this->dim; i++)
			this->conductivitate[i] = conductivitate[i];
	}
	//Constructor de copiere
	SenzorPremium(const SenzorPremium& s) :Senzor(s)
	{
		this->nitrati = s.nitrati;
		this->eColi = s.eColi;
		this->dim = s.dim;
		if (conductivitate != nullptr) delete[]this->conductivitate;
		this->conductivitate = new int[this->dim];
		for (int i = 0; i < this->dim; i++)
			this->conductivitate[i] = s.conductivitate[i];
	}
	//Destructor
	~SenzorPremium()
	{
		if (conductivitate!=NULL)
			delete[]conductivitate;
	}

	//Supraincarcarea operatorului =
	SenzorPremium& operator=(const SenzorPremium& s)
	{
		Senzor::operator=(s);

		this->nitrati = s.nitrati;
		this->eColi = s.eColi;
		this->dim = s.dim;
		for (int i = 0; i < this->dim; i++)
			this->conductivitate[i] = s.conductivitate[i];

		return *this;
	}

	//Supraincarcarea operatorului <<
	friend ostream& operator<<(ostream& afisare, SenzorPremium& s)
	{
		afisare << s.getID() << ". " << "\tSenzorul PREMIUM marca " << s.getProducator() << " este amplasat in cartierul " << s.getCartier() << " la adancimea de " << s.getAdancimeSenzor() <<
			" metri ; are gradul de uzura " << 100 - s.getStareSenzor() << "%. ";
		if (s.getRemoteAccess() == true)
			afisare << "Permite conectarea de la distanta.";
		else afisare << "Nu permite conectarea de la distanta.";
		afisare << endl << endl << "\t\tValorile masurate de senzorul " << s.getProducator() << ":" << endl << "----> Concentratie clor: " << s.getConcentratieClor() << " mg/l" << endl << "----> Turbiditatea apei: "
			<< s.getTurbiditate() << " UNT" << endl << "----> Valorile pH-ului inregistrate in ultimele " << s.getNrMasuratori_pH() << " zile:";
		for (int i = 0; i < s.getNrMasuratori_pH(); i++)
			afisare << " | " << s.getValori_pH_Index(i); if (s.getNrMasuratori_pH()) afisare << " | ";
		afisare << endl << "----> Ultimele 5 masuratori ale temperaturii apei in grade Celsius: | ";
		for (int i = 0; i < 5; i++)
			afisare << s.getTemperaturiApaIndex(i) << " | ";
		
		afisare << endl << "\t\tIndicatori **PREMIUM**: " << endl << "----> Nitrati: " << s.nitrati << " mg/l" << endl << "----> Bacterii e-Coli: ";
		if (s.eColi == true) afisare << "Apa contine bacteria E.Coli - NU CONSUMATI";
						else afisare << "Apa NU contine bacteria E.Coli";
		afisare <<endl<< "----> Valorile conductivitatii apei in ultimele " << s.dim << " zile:";
		for (int i = 0; i < s.dim; i++)
			afisare << " | " << s.conductivitate[i]; if (s.dim) afisare << " | ";
		afisare << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		
		return afisare;
	}
	//Supraincarcarea operatorului >>
	friend istream& operator>>(istream& citire, SenzorPremium& s)
	{
		Senzor& a = s;
		citire >> a;

		cout << "Nitrati: ";
		citire >> s.nitrati;
		cout << "Exista E.Coli? (1/0): ";
		citire >> s.eColi;
		cout << "Nr. masuratori conductivitate: ";
		citire >> s.dim;
		s.conductivitate = new int[s.dim];
		for (int i = 0; i < s.dim; i++)
		{
			cout << "Valoarea conductivitatii in ziua " << i + 1 << ": ";
			citire >> s.conductivitate[i];
		}
		cin.ignore(); // necesar daca este nevoie sa citim 2 obiecte consecutiv de la tastatura
		return citire;
	}
	//GETTERI
	float getNitrati() { return this->nitrati; }
	bool getEcoli() { return this->eColi; }
	int getDimensiune() { return this->dim; }
	void getConductivitate() { for (int i = 0; i < this->dim; i++) cout << this->conductivitate[i] << " "; }
	int getConductivitateIndex(int pozitie)
	{
		try
		{
			if (pozitie >= 0 && pozitie < this->dim)
				return this->conductivitate[pozitie];
			else  throw  out_of_range("Index invalid");
		}
		catch (const exception& e)
		{
			cerr << "Eroare: " <<e.what() << endl;
		}
	}
	//SETTERI
	void setNitrati(float nitratiNoi)
	{
		if (nitratiNoi > 0)	this->nitrati = nitratiNoi;
	}
	void setEcoli(bool EcoliNou)
	{
		if (EcoliNou == 1) this->eColi = 1;
		else if (EcoliNou == 0) this->eColi = 0;
	}
	void setDimensiune(int dimNoua)
	{
		if (dimNoua > 0) this->dim = dimNoua;
	}
	void setConductivitate(int dimNoua, int* conductivitateNoua)
	{
		if (dimNoua > 0 && conductivitateNoua[0] != NULL)
		{
			setDimensiune(dimNoua);
			delete[]this->conductivitate;
			this->conductivitate = new int[dimNoua];
			for (int i = 0; i < dimNoua; i++)
				this->conductivitate[i] = conductivitateNoua[i];
		}
	}
	void setConductivitateIndex(int valoareConductivitate, int pozitie)
	{
		if (pozitie >= 0 && pozitie < this->dim)
			this->conductivitate[pozitie] = valoareConductivitate;
	}
	
	//Supraincarcarea operatorului + (cazul obiect+obiect)
	SenzorPremium operator+(const SenzorPremium& s)
	{
		SenzorPremium aux;
		aux.nitrati = this->nitrati + s.nitrati; 
		return aux;
	}
	//Supraincarcarea operatorului -=
	SenzorPremium operator-=(int valoare)
	{
		SenzorPremium aux = *this;
		for (int i = 0; i < this->dim; i++)
		{
			this->conductivitate[i] -= valoare;
		}
		return aux;
	}
	//Supraincarcarea opeartorului !
	bool operator!() 
	{
		SenzorPremium aux = *this;
		if (aux.eColi == true) aux.eColi = false;
		else if (aux.eColi == false) aux.eColi = true;

		return aux.eColi;
	}
	//Supraincarcarea operatorului () - returneaza media conductivitatii apei pentru un interval dat
	float operator()(int x, int y)
	{
		if (x >= 0 && x < this->dim && y <= this->dim && x < y)
		{
			float suma = 0;
			for (int i = x - 1; i < y; i++)
				suma += this->conductivitate[i];
			return suma / (y - x + 1);
		}
		else return 0;
	}
	//Supraincarcarea operatorului ++ (forma pre-fixata)
	SenzorPremium operator--()
	{
		
		this->nitrati++;
		return *this;
	}

	//SCRIERE SenzorPremium in fisier
	friend fstream& operator<<(fstream& fout, SenzorPremium& s)
	{

		fout << s.getID() << ". " << "\tSenzorul PREMIUM marca " << s.getProducator() << " este amplasat in cartierul " << s.getCartier() << " la adancimea de " << s.getAdancimeSenzor() <<
			" metri ; are gradul de uzura " << 100 - s.getStareSenzor() << "%. ";
		if (s.getRemoteAccess() == true)
			fout << "Permite conectarea de la distanta.";
		else fout << "Nu permite conectarea de la distanta.";
		fout << endl << endl << "\t\tValorile masurate de senzorul " << s.getProducator() << ":" << endl << "----> Concentratie clor: " << s.getConcentratieClor() << " mg/l" << endl << "----> Turbiditatea apei: "
			<< s.getTurbiditate() << " UNT" << endl << "----> Valorile pH-ului inregistrate in ultimele " << s.getNrMasuratori_pH() << " zile:";
		for (int i = 0; i < s.getNrMasuratori_pH(); i++)
			fout << " | " << s.getValori_pH_Index(i); if (s.getNrMasuratori_pH()) fout << " | ";
		fout << endl << "----> Ultimele 5 masuratori ale temperaturii apei in grade Celsius: | ";
		for (int i = 0; i < 5; i++)
			fout << s.getTemperaturiApaIndex(i) << " | ";

		fout << endl << "\t\tIndicatori **PREMIUM**: " << endl << "----> Nitrati: " << s.nitrati << " mg/l" << endl << "----> Bacterii e-Coli: ";
		if (s.eColi == true) fout << "Apa contine bacteria E.Coli - NU CONSUMATI";
		else fout << "Apa NU contine bacteria E.Coli";
		fout << endl << "----> Valorile conductivitatii apei in ultimele " << s.dim << " zile:";
		for (int i = 0; i < s.dim; i++)
			fout << " | " << s.conductivitate[i]; if (s.dim) fout << " | ";
		fout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		return fout;
	}

	//CITIRE Senzorpremium din fisier
	friend fstream& operator>>(fstream& fin, SenzorPremium& s)
	{
		fin.ignore();
		fin >> static_cast<Senzor&>(s);
	
		fin >> s.nitrati;
		fin >> s.eColi;
		fin >> s.dim;
		s.conductivitate = new int[s.dim];
		for (int i = 0; i < s.dim; i++)
			fin >> s.conductivitate[i];
		
		//fin.ignore();
		return fin;
	}

	//CITIREA tututor senzorilor premium dintr-un fisier dat
	static void citireListaSenzoriPremium(string fisierInput, SenzorPremium*& listaSenzoriPremium, int& nrSenzoriPremium)
	{
		fstream fisier(fisierInput, ios::in);
		if (fisier.is_open())
		{
			fisier >> nrSenzoriPremium;

			if (listaSenzoriPremium != nullptr)
			{
				for (int i = 0; i < nrSenzoriPremium; i++)
				{
					delete[] listaSenzoriPremium[i].conductivitate;
				}
				delete[]listaSenzoriPremium;
			}

			listaSenzoriPremium = new SenzorPremium[nrSenzoriPremium];
			for (int i = 0; i < nrSenzoriPremium; i++)
			{
				fisier >> listaSenzoriPremium[i];
			}
		}
		else cout << "Eroare: fisierul " << fisierInput << " nu a putut fi deschis.";


		fisier.close();
	}

	 float get_conductivitate_medie()
	{
		try
		{
			float suma = 0;
			if (this->dim == 0) throw runtime_error("Nu exista valori inregistrate ale pH-ului (nu se poate face impartirea la zero)");

			for (int i = 0; i < this->dim; i++)
				suma += conductivitate[i];

			return suma / this->dim;
		}
		catch (const exception& e)
		{
			cerr << "Eroare: " << e.what() << endl;
		}
	}
};


class ListaSenzoriPremium
{
private:
	int nrSenzoriPremium;
	SenzorPremium* listaSenzoriPremium;

public:
	ListaSenzoriPremium(int nrSenzoriPremium, SenzorPremium* listaSenzoriPremium)
	{
		this->nrSenzoriPremium = nrSenzoriPremium;
		this->listaSenzoriPremium = listaSenzoriPremium;
	}
	~ListaSenzoriPremium()
	{
		if (listaSenzoriPremium != NULL)
			delete[]listaSenzoriPremium;
	}
	void afisareLista()
	{
		for (int i = 0; i < nrSenzoriPremium; i++)
		{
			cout << listaSenzoriPremium[i];
		}
	}

	

	void SigurantaSistemuluiDeApaPotabila(string cale_fisier)
	{
		string text;
		//Alerta E.coli
		for (int i = 0; i < nrSenzoriPremium; i++)
		{
			if (listaSenzoriPremium[i].getEcoli() == 1)
				text += "ALERTA: Sursa de apa monitorizata de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + " este CONTAMINATA cu BACTERIA E.Coli -> A se opri imediat furnizarea apei!\n\n";
		}
		text += "---------------------------------------------------------------\n";
		ListaSenzoriPremium::scriereRezultateInFisier(cale_fisier, text);

		//Conductivitatea medie a apei
		int avertisment = 0;
		for (int i = 0; i < nrSenzoriPremium; i++)
		{
			text += "Conductivitatea medie inregistrata de senzorul " + to_string(i + 1) + ": " + to_string(listaSenzoriPremium[i].get_conductivitate_medie()) + " microSiemens/cm \n";
			if (listaSenzoriPremium[i].get_conductivitate_medie() > 2500)
				avertisment = 1;
		}
		if (avertisment == 1) text += "Atentie: conductivitatea apei este peste limita admisa acolo unde media depaseste 2500 microSiemens/cm";
		else text += "\nConductivitatea medie se afla in limita admisa in toate locatiile analizate!\n---------------------------------------------------------------\n";
		ListaSenzoriPremium::scriereRezultateInFisier(cale_fisier, text);
		
		//Recomandari de inlocuire senzori
		for (int i = 0; i < nrSenzoriPremium; i++)
		{
			if (listaSenzoriPremium[i].getStareSenzor() < 50)
				text += "Starea senzorului " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + " este sub 50%. Se recomanda inlocuirea acestuia cat mai in curand.\n\n";
		}
		text += "Toti ceilalti senzori au o stare buna de functionare!\n---------------------------------------------------------------\n";
		ListaSenzoriPremium::scriereRezultateInFisier(cale_fisier, text);
		
		// Clasificare dupa turbiditate
		for (int i = 0; i < nrSenzoriPremium; i++)
		{
			if (listaSenzoriPremium[i].getTurbiditate() == 1)
				text += "Turbiditate = 1 UNT -> valoare perfecta pentru apa monitorizata de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + "\n";

			else if (listaSenzoriPremium[i].getTurbiditate() == 2)
				text += "Turbiditate = 2 UNT -> valoare foarte buna pentru apa monitorizata de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + "\n";
			else if (listaSenzoriPremium[i].getTurbiditate() == 3)
				text += "Turbiditate = 3 UNT -> valoare buna pentru apa monitorizata de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + "\n";
			else if (listaSenzoriPremium[i].getTurbiditate() == 4)
				text += "Turbiditate = 4 UNT -> valoare  la limita pentru apa monitorizata de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + "\n";
			else if (listaSenzoriPremium[i].getTurbiditate() == 5)
				text += "Turbiditate = 5 UNT -> valoare maxim admisa pentru apa monitorizata de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + "\n";
			else if (listaSenzoriPremium[i].getTurbiditate() >5 )
				text += "Turbiditate > 5 UNT -> NU se recomanda consumul apei monitorizate de senzorul " + listaSenzoriPremium[i].getProducator() + " cu id-ul "
				+ to_string(listaSenzoriPremium[i].getID()) + "\n";

		}
		text += "\n---------------------------------------------------------------\n";
		ListaSenzoriPremium::scriereRezultateInFisier(cale_fisier, text);
	}

	
	static void scriereRezultateInFisier(string cale_fisier, string text)
	{
		ofstream output(cale_fisier);
		if (output.is_open())
		{
			output << text;
		}
		else cout << "Eroare: fisierul nu a putut fi deschis pentru scriere.";
	}
};

//Exemplificarea conceptului de CLASA ABSTRACTA cu o functie virtuala pura
class ConvertorUnitati
{
	virtual float DensitateSenzor() = 0;
};
class DimensiuniSenzor: public ConvertorUnitati
{
private:
	float volumSenzorCm3;
	float greutateSenzorKg;
public:
	DimensiuniSenzor(float volumSenzorCm3, float greutateSenzorKg)
	{
		this->volumSenzorCm3 = volumSenzorCm3;
		this->greutateSenzorKg = greutateSenzorKg;
	}
	float DensitateSenzor()
		
	{
		float volumSenzorM3 = volumSenzorCm3 / 1000000;
		float densitate = greutateSenzorKg / volumSenzorCm3;
		return densitate;
	}
};
//Definirea unei CLASE TEMPLATE
template<class SenzorTemplate>
class ColectieSenzori
{
private:
	int numarSenzori;
	SenzorTemplate* pretSenzori;
public:
	ColectieSenzori()
	{
		this->numarSenzori = 0;
		this->pretSenzori = NULL;
	}
	ColectieSenzori(int numarSenzori, SenzorTemplate* pretSenzori)
	{
		this->numarSenzori = numarSenzori;
		this->pretSenzori = new SenzorTemplate[numarSenzori];
		for (int i = 0; i < this->numarSenzori; i++)
			this->pretSenzori[i] = pretSenzori[i];
	}
	~ColectieSenzori()
	{
		if (pretSenzori != NULL)
			delete[]pretSenzori;
	}
	float mediePreturiSenzori()
	{
		float medie = 0;
		for (int i = 0; i < this->numarSenzori; i++)
		{
			medie += pretSenzori[i];
		}
		medie = medie / numarSenzori;
		return medie;
	}
};
void main()
{
	SenzorPremium* listaSenzoriPremium = nullptr;
	int nrSenzoriPremium;

	//Citirea tuturor senzorilor premium din fisier
	SenzorPremium::citireListaSenzoriPremium("inputSenzoriPremium.txt", listaSenzoriPremium, nrSenzoriPremium);
	
	ListaSenzoriPremium lista(nrSenzoriPremium, listaSenzoriPremium);
	lista.afisareLista(); // afiseaza in consola toti senzorii cititi din fisier
	
	//Scrierea rezultatelor analizei efectuate intr-un fisier text. Calea este citita de la tastarura.
	cout << endl << "Introduceti calea fisierului de iesire, inclusiv denumirea. Exemplu - 'C:\\Users\\Gabi\\Desktop\\exemplu.txt'" << endl;
	string cale_fisier;
	cin >> cale_fisier;

	//Scrierea raportului final in fisierul ales despre siguranta apei potabile din sistemul public.
	lista.SigurantaSistemuluiDeApaPotabila(cale_fisier);



	//Exemplificarea utilitatii unei functii virtuale.
	DimensiuniSenzor exemplu(1500, 0.5);
	cout << endl << "Densitatea senzorului: " << exemplu.DensitateSenzor() << " kg/m^3 (exemplu clasa abstracta - functie virtuala)";
	
	//Exemplificarea utilitatii unei clase template.
	
	ColectieSenzori<float> colectie(4, new float[10]{ 130, 450, 220.15, 55.8, 130.99, 43, 85.10, 166.5, 74.3 ,83.10 });
	cout << endl << "Pretul colectiei de senzori detinuti este de: " << colectie.mediePreturiSenzori() << " euro. (exemplu clasa template)" << endl;


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EXEMPLE DE APELURI PENTRU FUNCTIONALITATILE IMPLEMENTATE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
	Senzor s1;
	s1.afisareSenzor();
	Senzor s2("Exemplu1", 3, new float[3]{ 1.1, 2.5, 3.7 }, 0.25, { 3.6, 4.5, 6.9, 8.3, 9.5 }, 30, "Crangasi", 44, 12, true);
	cout << s2;
	Senzor s3 = s2;
	s3.setProducator("Hidro");
	//cout << s3;

	SenzorPremium a1("Exemplu2", 3, new float[3]{ 1.1, 2.5, 3.7 }, 0.25, { 3.6, 4.5, 6.9, 8.3, 9.5 }, 30, "Pipera", 44, 12, true, 3.66, true, 2, new int[2]{ 3,6 });
	SenzorPremium a2("Exemplu3", 3, new float[3]{ 1.1, 2.5, 3.7 }, 0.25, { 3.6, 4.5, 6.9, 8.3, 9.5 }, 30, "Pipera", 44, 12, true, 6.44, true, 2, new int[2]{ 3,6 });
	a2 -= 4;
	cout << a2;

	fstream fisier("outputSenzori.txt", ios::app);
	fisier << a1; //scriere senzor premium in fisier
	fisier << s2; //scriere senzor normal in fisier
	Senzor a3, a4;
	fstream fisier2("inputSenzori.txt", ios::in);
	fisier2 >> a3; // citire senzor normal din fisier
	cout << a3;
	fisier2 >> a4; //citire senzor normal din fisier
	cout << a4;


	//Apeluri 5 operatori supraincarcati
	Senzor s4 = s2 + 10.1;
	--s4;
	s4++;
	cout << s4() << endl;
	cout << s4[0];

	//Apeluri 5 operatori supraincarcati CLASA PREMIUM
	SenzorPremium a8=a1+a2;
	a8 -= 5;
	cout << a8;
	if (!a1) cout << "true";
		else cout << "false";
	cout << a1(1, 2);
	a2++;
  */
}
