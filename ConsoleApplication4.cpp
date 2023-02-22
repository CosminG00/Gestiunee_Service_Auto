#define _CRT_SECURE_NO_WARNINGS  
#define NR_ORDINE_DEFAULT 0
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include<list>
using namespace std;



class DataMining
{
	int Af;
	int Ct;
public:
	DataMining() {
		this->Af = 0;
		this->Ct = 0;
	}

	void nrAfisari() {
		this->Af++;
	}

	void nrCitiri() {
		this->Ct++;
	}

	void raportAfisari(ofstream& fout) {
		fout << "Fct de afisare s-a folosit de  " << this->Af << " ori " << endl;
	}

	void raportCitiri(ofstream& fout) {
		fout << "Fct de citire s-a folosit de  " << this->Ct << " ori " << endl;
	}
};

DataMining d;


class Meniu {
public:
	static void afisareMeniuPrincipal() {
		cout << "1)Afiseaza masina " << endl;
		cout << "2)citire de la tastura masina" << endl;
		cout << "3)Salveaza date" << endl;
		cout << "0)Iesire" << endl;
		cout << "Alege optiunea:";
	}
};


class reparatieAuto {

public:

	virtual void adaugaSoftStandard() = 0;
	virtual void masinaPericuloasa() = 0;
};



class Masina {
	int sasiuNumeric[10];
	char* brand = NULL;

	int CP;
	int nrPieseLipsa;

	int nrAccidente;
	int* pretReparatieAccidente = NULL;

public:

	Masina() { cout << "\nCONSTR FARA PARAMETRI MASINA"; }
		//GETTER+SETTER sasiuNumeric
	int* getsasiuNumeric() {
		return this->sasiuNumeric;
	}
	void setsasiuNumeric(int sasiuNumeric[10]) {

		for (int i = 0; i < 10; i++)
			if (sasiuNumeric[i] >= 0)
				this->sasiuNumeric[i] = sasiuNumeric[i];
	}


	//GETTER+SETTER brand
	char* getBrand() {
		return this->brand;
	}
	void setBrand(const char* brand) {
		if (brand != NULL) {
			delete[] this->brand;
		}

		this->brand = new char[strlen(brand) + 1];
		strcpy(this->brand, brand);
	}


	//GETTER+SETTER CP
	int getCP() {
		return this->CP;
	}
	void setCP(int CP) {
		if (CP > 15)
			this->CP = CP;
	}


	//GETTER+SETTER nrPieseLipsa
	int getNrPieseLipsa() {
		return this->nrPieseLipsa;
	}
	void setNrPieseLipsa(int nrPieseLipsa) {
		if (nrPieseLipsa > 0)
			this->nrPieseLipsa = nrPieseLipsa;
	}


	//GETTER+SETTER nrAccidente
	int getNrAccidente() {
		return this->nrAccidente;
	}
	void setNrAccidente(int nrAccidente) {
		if (nrAccidente > 0)
			this->nrAccidente = nrAccidente;
	}


	//GETTER+SETTER pretReparatieAccidente
	int* getPretReparatieAccidente() {
		return this->pretReparatieAccidente;
	}
	void setPretReparatieAccidente(int* pretReparatieAccidente, int nrAccidente) {
		if (this->pretReparatieAccidente != NULL) {
			delete[] this->pretReparatieAccidente;
		}

		if (nrAccidente > 0 && pretReparatieAccidente != NULL) {
			this->nrAccidente = nrAccidente;
			this->pretReparatieAccidente = new int[nrAccidente];

			for (int i = 0; i < nrAccidente; i++)
				this->pretReparatieAccidente[i] = pretReparatieAccidente[i];
		}
	}


	//METODA CARE AFISEAZA NR-UL DE CP POTENTIALI, BAZAT PE IDEEA CA FIECARE PIESA LIPSA COSTA 25CP POTENTIALI
	void CPpotentiali(int CP) {
		int CPperPiesaLipsa = 25;
		this->CP = CP;
		int CPpotentiali = this->CP;

		CPpotentiali = CPpotentiali + (CPperPiesaLipsa * nrPieseLipsa);

		cout << "\n CP POTENTIALI=" << CPpotentiali;
	}


	//METODA CARE SORTEAZA REPARATIILE IN FUNCTIE DE PRET;
	void OrdineReperatii(int nrAccidente, int* pretReparatieAccidente) {

		int poz[10];
		int k = 0;

		for (int i = 0; i < nrAccidente; i++)
			poz[k++] = i;

		for (int i = 0; i < nrAccidente - 1; i++)
			for (int j = i + 1; j < nrAccidente; j++)
				if (pretReparatieAccidente[i] > pretReparatieAccidente[i + 1]) {
					swap(pretReparatieAccidente[i], pretReparatieAccidente[i + 1]);
					swap(poz[i], poz[i + 1]);
				}

		cout << "\nORDINEA REPARATIILOR O SA FIE ASA  ";
		for (int i = 0; i < this->nrAccidente; i++) {
			cout << endl;
			cout << poz[i] << " in valoare de  " << pretReparatieAccidente[i] << endl;
		}

	}


	//CONSTRUCTOR CU 1 PARAMETRU
	Masina(const char* brand) {
		this->brand = new char[strlen("FaraNume") + 1];
		strcpy(this->brand, "FaraNume");

		this->CP = 0;
		this->nrPieseLipsa = 0;
		this->nrAccidente = 0;

		this->pretReparatieAccidente = NULL;

		for (int i = 0; i < 10; i++)
			this->sasiuNumeric[i] = 0;

	}


	//CONSTRUCTOR CU TOTI PARAMETRI
	Masina(const char* brand, int CP, int nrPieseLipsa, int nrAccidente, int* pretReparatieAccidente, int sasiuNumeric[10]) {

		if (CP > 15)
			this->CP = CP;
		else
			this->CP = 0;


		if (brand != NULL) {
			this->brand = new char[strlen(brand) + 1];
			strcpy(this->brand, brand);
		}
		else {
			this->brand = new char[strlen("FaraNume") + 1];
			strcpy(this->brand, "FaraNume");
		}


		if (nrPieseLipsa > 0)
			this->nrPieseLipsa = nrPieseLipsa;
		else
			this->nrPieseLipsa = 0;


		if (nrAccidente > 0 && pretReparatieAccidente != NULL) {
			this->nrAccidente = nrAccidente;
			this->pretReparatieAccidente = new int[nrAccidente];

			for (int i = 0; i < nrAccidente; i++)
				this->pretReparatieAccidente[i] = pretReparatieAccidente[i];
		}
		else {
			this->nrAccidente = 0;
			this->pretReparatieAccidente = NULL;
		}

		for (int i = 0; i < 10; i++)
			if (this->sasiuNumeric[i] >= 0)
				this->sasiuNumeric[i] = sasiuNumeric[i];



	}


	//CONSTRUCTOR COPIERE
	Masina(const Masina& m) {

		if (m.CP > 15)
			this->CP = m.CP;
		else
			this->CP = 0;


		if (m.brand != NULL) {
			this->brand = new char[strlen(m.brand) + 1];
			strcpy(this->brand, m.brand);
		}
		else {
			this->brand = new char[strlen("FaraNume") + 1];
			strcpy(this->brand, "FaraNume");
		}


		if (m.nrPieseLipsa > 0)
			this->nrPieseLipsa = m.nrPieseLipsa;
		else
			this->nrPieseLipsa = 0;


		if (m.nrAccidente > 0 && m.pretReparatieAccidente != NULL) {
			this->nrAccidente = m.nrAccidente;
			this->pretReparatieAccidente = new int[m.nrAccidente];

			for (int i = 0; i < m.nrAccidente; i++)
				this->pretReparatieAccidente[i] = m.pretReparatieAccidente[i];
		}
		else {
			this->nrAccidente = 0;
			this->pretReparatieAccidente = NULL;
		}

		for (int i = 0; i < 10; i++)
			if (this->sasiuNumeric[i] >= 0)
				this->sasiuNumeric[i] = m.sasiuNumeric[i];


	}


	//DESTRUCTOR
	~Masina() {
		if (brand != NULL)
			delete[] this->brand;

		if (pretReparatieAccidente != NULL)
			delete[] this->pretReparatieAccidente;

		cout << "\nAPELARE DESTRUCTOR";
	}


	//OPERATOR =
	Masina& operator=(const Masina& m) {
		if (this != &m) {

			if (brand != NULL)
				delete[] this->brand;

			if (pretReparatieAccidente != NULL)
				delete[] this->pretReparatieAccidente;

			if (m.CP > 15)
				this->CP = m.CP;
			else
				this->CP = 0;


			if (m.brand != NULL) {
				this->brand = new char[strlen(m.brand) + 1];
				strcpy(this->brand, m.brand);
			}
			else {
				this->brand = new char[strlen("FaraNume") + 1];
				strcpy(this->brand, "FaraNume");
			}


			if (m.nrPieseLipsa > 0)
				this->nrPieseLipsa = m.nrPieseLipsa;
			else
				this->nrPieseLipsa = 0;


			if (m.nrAccidente > 0 && m.pretReparatieAccidente != NULL) {
				this->nrAccidente = m.nrAccidente;
				this->pretReparatieAccidente = new int[m.nrAccidente];

				for (int i = 0; i < m.nrAccidente; i++)
					this->pretReparatieAccidente[i] = m.pretReparatieAccidente[i];
			}
			else {
				this->nrAccidente = 0;
				this->pretReparatieAccidente = NULL;
			}

			for (int i = 0; i < 10; i++)
				if (this->sasiuNumeric[i] >= 0)
					this->sasiuNumeric[i] = m.sasiuNumeric[i];

		}



		return *this;
	}


	//OPERATOR<<
	friend ostream& operator<<(ostream& out, const Masina& m) {
		d.nrAfisari();

		out << "\nBRAND=" << m.brand;

		out << "\nCP=" << m.CP;

		out << "\nNR. PIESE LIPSA=" << m.nrPieseLipsa;

		out << "\nNR ACCIDENTE=" << m.nrAccidente;

		for (int i = 0; i < m.nrAccidente; i++)
			out << "\nPRET REPARATIE AL ACCIDENTULUI " << i + 1 << " ESTE " << m.pretReparatieAccidente[i];

		out << "\nSASIUL NUMERIC=";
		for (int i = 0; i < 10; i++)
			out << m.sasiuNumeric[i];

		out << endl;

		return out;
	}


	//OPERATOR>>
	friend istream& operator>>(istream& in, Masina& m) {
		d.nrCitiri();
		if (m.brand != NULL)
			delete[] m.brand;

		if (m.pretReparatieAccidente != NULL)
			delete[] m.pretReparatieAccidente;


		cout << "\nBRAND=";
		m.brand = new char[200];
		in >> m.brand;

		cout << "\nCP=";
		in >> m.CP;

		cout << "\nNR. PIESE LIPSA=";
		in >> m.nrPieseLipsa;

		cout << "\nNR ACCIDENTE=";
		in >> m.nrAccidente;


		m.pretReparatieAccidente = new int[m.nrAccidente];
		for (int i = 0; i < m.nrAccidente; i++) {
			cout << "\nPRET REPARATIE AL ACCIDENTULUI " << i + 1 << " ESTE ";
			in >> m.pretReparatieAccidente[i];
		}

		cout << "\nSASIU NUMERIC=";
		for (int i = 0; i < 10; i++)
			in >> m.sasiuNumeric[i];



		return in;
	}

	friend ofstream& operator<<(ofstream& fout, const Masina& m) {
		d.nrAfisari();
		fout << "\n---------------------------------------------";

		fout << "\nBRAND=" << m.brand;

		fout << "\nCP=" << m.CP;

		fout << "\nNR. PIESE LIPSA=" << m.nrPieseLipsa;

		fout << "\nNR ACCIDENTE=" << m.nrAccidente;


		for (int i = 0; i < m.nrAccidente; i++)

			fout << "\nPRET REPARATIE AL ACCIDENTULUI " << i + 1 << " ESTE " << m.pretReparatieAccidente[i];


		fout << "\nSASIUL NUMERIC=";

		for (int i = 0; i < 10; i++)

			fout << m.sasiuNumeric[i];


		fout << "\n---------------------------------------------";


		fout << endl;


		return fout;

	}



	friend ifstream& operator>>(ifstream& fin, Masina& m) {
		d.nrCitiri();

		if (m.pretReparatieAccidente != NULL)
			delete[] m.pretReparatieAccidente;



		if (m.brand != NULL)
			delete[] m.brand;



		m.brand = new char[200];
		fin >> m.brand;

		fin >> m.CP >> m.nrPieseLipsa >> m.nrAccidente;

		m.pretReparatieAccidente = new int[m.nrAccidente];
		for (int i = 0; i < m.nrAccidente; i++) fin >> m.pretReparatieAccidente[i];


		for (int i = 0; i < 10; i++)
			fin >> m.sasiuNumeric[i];

		return fin;
	}


	void scrieBinar(ofstream& o) {
		d.nrAfisari();


		int lungime = strlen(this->brand) + 1;//  
		o.write((char*)&lungime, sizeof(int));//  
		o.write(this->brand, sizeof(char) * lungime);// 




		o.write((char*)&this->CP, sizeof(this->CP));



		o.write((char*)&this->nrPieseLipsa, sizeof(this->nrPieseLipsa));



		o.write((char*)&this->nrAccidente, sizeof(this->nrAccidente));
		for (int i = 0; i < this->nrAccidente; i++) {
			o.write((char*)&this->pretReparatieAccidente[i], sizeof(this->pretReparatieAccidente[i]));
		}



		for (int i = 0; i < 10; i++)
			o.write((char*)&this->sasiuNumeric[i], sizeof(this->sasiuNumeric[i]));

	}

	void citireBinar(ifstream& in) {
		d.nrCitiri();


		int lungime;
		in.read((char*)&lungime, sizeof(int));
		char s[2000];
		in.read(s, lungime);

		if (this->brand != NULL)
			delete[] this->brand;

		this->brand = new char[strlen(s) + 1];
		strcpy(this->brand, s);



		in.read((char*)&this->CP, sizeof(this->CP));


		in.read((char*)&this->nrPieseLipsa, sizeof(this->nrPieseLipsa));



		in.read((char*)&this->nrAccidente, sizeof(this->nrAccidente));

		delete[]  this->pretReparatieAccidente;
		this->pretReparatieAccidente = new int[this->nrAccidente];
		for (int i = 0; i < this->nrAccidente; i++) {
			in.read((char*)&this->pretReparatieAccidente[i], sizeof(int));
		}



		in.read((char*)this->sasiuNumeric, 10 * sizeof(int));


	}

	void raporMasina(const char* f) {
		ofstream outMasina;
		outMasina.open(f, ofstream::out);

		outMasina << "\nMasina " << brand << " are " << CP << " cai putere " << " cu " << nrPieseLipsa << " piese lipsa " << " , cu " << nrAccidente << " fiecare accident costand: ";

		for (int i = 0; i < nrAccidente; i++)
			outMasina << "\nPretul accidentului " << i + 1 << " este " << pretReparatieAccidente[i];

		outMasina << "\nIar sasiul numeric este: ";
		for (int i = 0; i < 10; i++)
			outMasina << sasiuNumeric[i];
	}


	/*
	void readData(const string& filename) {
		// Open the CSV file for reading
		ifstream file("data.csv");

		// Check if the file was successfully opened
		if (!file.is_open()) {
			cerr << "\n*****************************************************Error: Could not open file" << endl;
			return;
		}

		// Read the data from the file, line by line
		string line;
		while (getline(file, line)) {
			// Split the line into separate values
			stringstream ss(line);

			// Read the values into member variables
			ss >> sasiuNumeric[0] >> brand >> CP >> nrPieseLipsa >> nrAccidente;

			// Read the remaining values in the sasiuNumeric array
			for (int i = 1; i < 10; i++) {
				ss >> sasiuNumeric[i];
			}
		}

		// Close the file
		file.close();
	}*/



	//OPERATOR ! NEGATIE
	bool operator!() {
		return !(nrPieseLipsa == 0);
	}


	//OPERATOR ++ PREINCREMENTARE
	Masina& operator++() {
		nrPieseLipsa = nrPieseLipsa + 1;
		return *this;
	}


	//OPERATOR ++ POSTINCREMENTARE
	Masina operator++(int fictiv) {
		Masina temp = *this;

		nrPieseLipsa++;

		return *this;

	}


	//OPERATOR==
	bool operator==(Masina& m) {
		if ((this->CP == m.CP) && (this->nrPieseLipsa = m.nrPieseLipsa) && (this->nrAccidente = m.nrAccidente) && strcmp(this->brand, m.brand) == 0) {
			for (int i = 0; i < m.nrAccidente; i++)
				if (this->pretReparatieAccidente[i] != m.pretReparatieAccidente[i])
					return false;

			for (int i = 0; i < 10; i++)
				if (this->sasiuNumeric[i] == m.sasiuNumeric[i])
					return false;
		}
		else
			return false;

		return true;
	}


	//OPERATOR[]
	float operator[](int poz) {
		if (poz >= 0 && poz < this->nrAccidente)
			return this->pretReparatieAccidente[poz];

		return -1;
	}


	//OPERATOR>=
	bool operator>=(const Masina& m) const {
		if (this->nrAccidente >= m.nrAccidente)
			return true;
		else
			return false;
	}


	//OPERATOR+
	Masina operator*(int i) {
		Masina copie = *this;
		copie.CP *= i;
		return copie;
	}


	//OPERATOR CAST
	explicit operator int() {
		return this->CP;
	}



};





class masinaSUV : public Masina, public reparatieAuto {
	;
	bool electrica = false;
	int capCilindrica = 0;

public:

	bool getElectrica() {
		return electrica;
	}

	int getCapCilindrica() {
		return capCilindrica;
	}

	masinaSUV() { cout << "\nCOSNTR masinaSUV"; };

	masinaSUV(bool electrica, int capCilindrica, const char* brand, int CP, int nrPieseLipsa, int nrAccidente, int* pretReparatieAccidente, int sasiuNumeric[10]) : Masina(brand, CP, nrPieseLipsa, nrAccidente, pretReparatieAccidente, sasiuNumeric) {

		if (electrica == false || electrica == true)
			this->electrica = electrica;

		if (capCilindrica > 0)
			this->capCilindrica = capCilindrica;
		else
			this->capCilindrica = 0;


	}

	masinaSUV(const masinaSUV& ms) {

		if (ms.electrica == false || ms.electrica == true)
			this->electrica = ms.electrica;

		if (ms.capCilindrica > 0)
			this->capCilindrica = ms.capCilindrica;
		else
			this->capCilindrica = 0;


	}

	~masinaSUV() {

		cout << "\nDESTRUCTOR CLASA DERIVATA masinaSUV";
	}

	masinaSUV& operator=(const masinaSUV& ms) {

		if (this != &ms) {

			if (ms.electrica == false || ms.electrica == true)
				this->electrica = ms.electrica;

			if (ms.capCilindrica > 0)
				this->capCilindrica = ms.capCilindrica;
			else
				this->capCilindrica = 0;
		}


		return *this;
	}

	friend ostream& operator<<(ostream& out, masinaSUV& ms) {
		d.nrAfisari();


		out << "\nBRAND=" << ms.getBrand();

		out << "\nCP=" << ms.getCP();

		out << "\nNR. PIESE LIPSA=" << ms.getNrPieseLipsa();

		out << "\nNR ACCIDENTE=" << ms.getNrAccidente();

		out << "\nPRET ACCIDENTE: " << ms.getPretReparatieAccidente();

		out << "\nSASIUL NUMERIC= " << ms.getsasiuNumeric();
		out << "\nELECTRICA: " << ms.electrica;
		out << "\nCAPACITATE CILINDRICA: " << ms.capCilindrica;

		return out;

	}

	void adaugaSoftStandard() {
		int CP = getCP();
		cout << "\n-----------Inaintea ADAUGARiii SOFTULUI STANDARD AVEM: " << CP;

		if (getCP() < 300)
			CP += 50;
		else
			CP += 100;



		cout << "\n-----------DUPA ADAUGAREA SOFTULUI STANDARD OBTINEM: " << CP;
	}

	void masinaPericuloasa() {
		if (getNrAccidente() > 5 && getNrPieseLipsa() > 10 && getCapCilindrica() > 5 && getCP() > 500)
			cout << "\nNU E DE MERS CU EA PE STRADA";
		else if (getCapCilindrica() > 5 && getCP() > 500)
			cout << "\nAI GRIJA LA VITEZA";
		else
			cout << "\nMERGI CU EA LINISTIT";

	}
};











class Angajat {
	int CNP[13];
	char* ocupatie = NULL;

	int salariu;
	char* nume = NULL;

	int nrSarcini;

public:
	Angajat() { cout << "\nconstr angajat fara param"; }

	//METODA DETERMINARE SEX PE BAZA CNP-ULUI
	void determinareSex(int CNP[13], int n) {
		int OK = 1;
		if (n == 13) {
			if (CNP[0] == 1 || CNP[0] == 5)
				OK = 0;
			else if (CNP[0] == 2 || CNP[0] == 6)
				OK = 1;
		}

		if (OK)
			cout << "\nFEMEIE!";
		else
			cout << "\nBARBAT!";
	}

	//METODA DETERMINARE VARSTA PE BAZA CNP-ULUI
	void determinareVarsta(int CNP[13], int n) {
		int varsta;
		int anNastere = 0;

		if (n == 13) {
			if (CNP[0] == 1 || CNP[0] == 2)
				anNastere = 1900 + CNP[1] * 10 + CNP[2];

			if (CNP[0] == 5 || CNP[0] == 6)
				anNastere = 2000 + CNP[1] * 10 + CNP[2];
		}

		varsta = 2022 - anNastere;
		cout << "\nVarsta angajatului este de " << varsta;
	}


	//GETTER+SETTER ocupatie
	char* getOcupatie() {
		return this->ocupatie;
	}
	void setOcupatie(const char* ocupatie) {
		if (ocupatie != NULL) {
			delete this->ocupatie;
		}

		this->ocupatie = new char[strlen(ocupatie) + 1];
		strcpy(this->ocupatie, ocupatie);
	}


	//GETTER+SETTER salariu
	int getSalariu() {
		return this->salariu;
	}
	void setSalariu(int salariu) {
		if (salariu > 0)
			this->salariu = salariu;
	}


	//GETTER+SETTER nume
	char* getNume() {
		return this->nume;
	}
	void setNume(const char* nume) {
		if (nume != NULL) {
			delete[] this->nume;
		}
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}


	//GETTER+SETTER CNP
	int* getCNP() {
		return this->CNP;
	}
	void setCNP(int CNP[13]) {
		for (int i = 0; i < 13; i++)
			if (CNP[i] >= 0)
				this->CNP[i] = CNP[i];
	}


	//GETTER+SETTER nrSarcini
	int getnrSarcini() {
		return this->nrSarcini;
	}
	void setnrSarcini(int nrSarcini) {
		if (nrSarcini > 0)
			this->nrSarcini = nrSarcini;
	}


	//CONSTRUCTOR CU 1 PARAMETRU
	Angajat(const char* nume) {
		this->salariu = 0;

		this->nume = new char[strlen("FaraNume") + 1];
		strcpy(this->nume, "FaraNume");

		this->ocupatie = new char[strlen("FaraNume") + 1];
		strcpy(this->ocupatie, "FaraNume");

		for (int i = 0; i < 13; i++)
			this->CNP[i] = 0;

		this->nrSarcini = 0;


	}


	Angajat(const char* nume, const char* ocupatie, int salariu, int CNP[13], int nrSarcini) {
		if (salariu > 0)
			this->salariu = salariu;
		else
			this->salariu = 0;

		if (nume != NULL) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else {
			this->nume = new char[strlen("FaraNume") + 1];
			strcpy(this->nume, "FaraNume");
		}

		if (ocupatie != NULL) {
			this->ocupatie = new char[strlen(ocupatie) + 1];
			strcpy(this->ocupatie, ocupatie);
		}
		else {
			this->ocupatie = new char[strlen("FaraNume") + 1];
			strcpy(this->ocupatie, "FaraNume");
		}

		for (int i = 0; i < 13; i++)
			this->CNP[i] = CNP[i];

		if (nrSarcini > 0)
			this->nrSarcini = nrSarcini;
		else
			this->nrSarcini = nrSarcini;


	}

	Angajat(const Angajat& a) {
		if (a.salariu > 0)
			this->salariu = a.salariu;
		else
			this->salariu = 0;

		if (a.nume != NULL) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
		}
		else {
			this->nume = new char[strlen("FaraNume") + 1];
			strcpy(this->nume, "FaraNume");
		}

		if (a.ocupatie != NULL) {
			this->ocupatie = new char[strlen(a.ocupatie) + 1];
			strcpy(this->ocupatie, a.ocupatie);
		}
		else {
			this->ocupatie = new char[strlen("FaraNume") + 1];
			strcpy(this->ocupatie, "FaraNume");
		}

		for (int i = 0; i < 13; i++)
			this->CNP[i] = a.CNP[i];

		if (a.nrSarcini > 0)
			this->nrSarcini = a.nrSarcini;
		else
			this->nrSarcini = a.nrSarcini;


	}

	~Angajat() {
		if (nume != NULL)
			delete[] this->nume;
		if (ocupatie != NULL)
			delete[] this->ocupatie;

		cout << "\nAPEL DESTRUCTOR";
	}

	Angajat& operator=(const Angajat& a) {

		if (this != &a) {
			if (nume != NULL)
				delete[] this->nume;
			if (ocupatie != NULL)
				delete[] this->ocupatie;

			if (a.salariu > 0)
				this->salariu = a.salariu;
			else
				this->salariu = 0;

			if (a.nume != NULL) {
				this->nume = new char[strlen(a.nume) + 1];
				strcpy(this->nume, a.nume);
			}
			else {
				this->nume = new char[strlen("FaraNume") + 1];
				strcpy(this->nume, "FaraNume");
			}

			if (a.ocupatie != NULL) {
				this->ocupatie = new char[strlen(a.ocupatie) + 1];
				strcpy(this->ocupatie, a.ocupatie);
			}
			else {
				this->ocupatie = new char[strlen("FaraNume") + 1];
				strcpy(this->ocupatie, "FaraNume");
			}

			for (int i = 0; i < 13; i++)
				this->CNP[i] = a.CNP[i];

			if (a.nrSarcini > 0)
				this->nrSarcini = a.nrSarcini;
			else
				this->nrSarcini = a.nrSarcini;

		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		d.nrAfisari();

		out << "\nNUME= " << a.nume;
		out << "\nOCUPATIE= " << a.ocupatie;

		out << "\nCNP= ";
		for (int i = 0; i < 13; i++)
			out << a.CNP[i];

		out << "\nSALARIU= " << a.salariu;
		out << "\nNR SARCINI= " << a.nrSarcini;

		return out;
	}

	friend istream& operator>>(istream& in, Angajat& a) {
		d.nrCitiri();

		if (a.nume != NULL)
			delete[] a.nume;
		if (a.ocupatie != NULL)
			delete[] a.ocupatie;

		cout << "\nNUME= ";
		a.nume = new char[100];
		in >> a.nume;

		cout << "\nOCUPATIE= ";
		a.ocupatie = new char[100];
		in >> a.ocupatie;

		cout << "\nCNP= ";
		for (int i = 0; i < 13; i++)
			in >> a.CNP[i];

		cout << "\nSALARIU= ";
		in >> a.salariu;

		cout << "\nNR SARCINI= ";
		in >> a.nrSarcini;


		return in;
	}


	friend ofstream& operator<<(ofstream& fout, const Angajat& a) {
		d.nrAfisari();


		fout << "\n---------------------------------------------";

		fout << "\nNUME= " << a.nume;
		fout << "\nOCUPATIE= " << a.ocupatie;

		fout << "\nCNP= ";
		for (int i = 0; i < 13; i++)
			fout << a.CNP[i];

		fout << "\nSALARIU= " << a.salariu;
		fout << "\nNR SARCINI= " << a.nrSarcini;

		fout << "\n---------------------------------------------";

		return fout;
	}


	friend ifstream& operator>>(ifstream& fin, Angajat& a) {
		d.nrCitiri();


		if (a.nume != NULL)
			delete[] a.nume;
		if (a.ocupatie != NULL)
			delete[] a.ocupatie;


		cout << "\nNUME= ";
		a.nume = new char[100];
		fin >> a.nume;

		cout << "\nOCUPATIE= ";
		a.ocupatie = new char[100];
		fin >> a.ocupatie;

		cout << "\nCNP= ";
		for (int i = 0; i < 13; i++)
			fin >> a.CNP[i];

		cout << "\nSALARIU= ";
		fin >> a.salariu;

		cout << "\nNR SARCINI= ";
		fin >> a.nrSarcini;


		return fin;
	}


	void scrieBinar(ofstream& o) {
		d.nrAfisari();



		int lungimeNume = strlen(this->nume) + 1;//  
		o.write((char*)&lungimeNume, sizeof(int));//  
		o.write(this->nume, sizeof(char) * lungimeNume);// 



		int lungimeOcupatie = strlen(this->ocupatie) + 1;//  
		o.write((char*)&lungimeOcupatie, sizeof(int));//  
		o.write(this->ocupatie, sizeof(char) * lungimeOcupatie);// 


		o.write((char*)&this->CNP, 13 * sizeof(int));


		o.write((char*)&this->salariu, sizeof(this->salariu));



		o.write((char*)&this->nrSarcini, sizeof(this->nrSarcini));

	}


	void citireBinar(ifstream& in) {
		d.nrCitiri();


		int lungimeNume;
		in.read((char*)&lungimeNume, sizeof(int));
		char a[2300];
		in.read(a, lungimeNume);

		delete[] this->nume;
		this->nume = new char[strlen(a) + 1];
		strcpy(this->nume, a);




		int lungimeOcupatie;
		in.read((char*)&lungimeOcupatie, sizeof(int));
		char b[2300];
		in.read(b, lungimeOcupatie);

		delete[] this->ocupatie;
		this->ocupatie = new char[strlen(b) + 1];
		strcpy(this->ocupatie, b);



		in.read((char*)&this->CNP, 13 * sizeof(int));


		in.read((char*)&this->salariu, sizeof(this->salariu));


		in.read((char*)&this->nrSarcini, sizeof(this->nrSarcini));

	}

	void raportAngajat(const char* f) {
		ofstream outAngajat;
		outAngajat.open(f, ofstream::out);

		outAngajat << "\nAngajatul " << nume << " cu ocupatia " << ocupatie << " cu salariul de " << salariu << " si nr-ul de sarcini " << nrSarcini << " , si are  CNP-UL: ";

		for (int i = 0; i < 13; i++)
			outAngajat << CNP[i];
	}


	//OPERATOR ! NEGATIE
	bool operator!() {
		return !(salariu == 0);
	}


	//OPERATOR ++ PREINCREMENTARE
	Angajat& operator++() {
		nrSarcini = nrSarcini + 1;
		return *this;
	}


	//OPERATOR ++ POSTINCREMENTARE
	Angajat operator++(int fictiv) {
		Angajat temp = *this;

		nrSarcini++;

		return *this;

	}


	//OPERATOR==
	bool operator==(Angajat& a) {
		if ((this->salariu == a.salariu) && (this->nrSarcini = a.nrSarcini) && strcmp(this->ocupatie, a.ocupatie) == 0 && strcmp(this->nume, a.nume) == 0) {

			for (int i = 0; i < 13; i++)
				if (this->CNP[i] != a.CNP[i])
					return false;
		}

		else {
			return false;
		}

		return true;
	}


	//OPERATOR[]
	float operator[](int poz) {
		if (poz >= 0 && poz < 13)
			return this->CNP[poz];

		return -1;
	}


	//OPERATOR<
	bool operator<(const Angajat& a) const {
		if (this->salariu < a.salariu)
			return true;
		else
			return false;
	}


	//OPERATOR+
	Angajat operator+(Angajat a) {
		Angajat copie = *this;
		copie.salariu = salariu + a.salariu;
		return copie;
	}


	//OPERATOR CAST
	explicit operator int() {
		return this->salariu;
	}

	virtual void salariuPotrivit() {
		cout << "\nESTE UN SALRIU CORECT PENTRU POZITIA OCUPATA IN SERVICE-UL AUTO?";
	}

	virtual void volumMunca() {
		cout << "\nAngajatul are un volum de munca atribuit profesiei sale";
	}

};






class Inginer : public Angajat {
	char* facultate = NULL;


public:

	char* getFacultate() {
		return this->facultate;
	}

	Inginer() { cout << "constr inginer fara param"; }

	Inginer(const char* facultate, const char* nume, const char* ocupatie, int salariu, int CNP[13], int nrSarcini) : Angajat(nume, ocupatie, salariu, CNP, nrSarcini) {

		if (facultate != NULL) {
			this->facultate = new char[strlen(facultate) + 1];
			strcpy(this->facultate, facultate);
		}
		else {
			this->facultate = new char[strlen("FaraNume") + 1];
			strcpy(this->facultate, "FaraNume");
		}

	}

	Inginer(const Inginer& i) {

		if (i.facultate != NULL) {
			this->facultate = new char[strlen(i.facultate) + 1];
			strcpy(this->facultate, i.facultate);
		}
		else {
			this->facultate = new char[strlen("FaraNume") + 1];
			strcpy(this->facultate, "FaraNume");
		}

	}

	~Inginer() {
		if (facultate != NULL)
			delete[] this->facultate;

		cout << "\nDESTRUCTOR CLASA DERIVATA";
	}

	Inginer& operator=(const Inginer& i) {

		if (this != &i) {
			if (facultate != NULL)
				delete[] this->facultate;


			if (i.facultate != NULL) {
				this->facultate = new char[strlen(i.facultate) + 1];
				strcpy(this->facultate, i.facultate);
			}
			else {
				this->facultate = new char[strlen("FaraNume") + 1];
				strcpy(this->facultate, "FaraNume");
			}




		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, Inginer& i) {
		d.nrAfisari();
		out << "\nNUME= " << i.getNume();
		out << "\nOCUPATIE= " << i.getOcupatie();

		out << "\nCNP= " << i.getCNP();

		out << "\nSALARIU= " << i.getSalariu();
		out << "\nNR SARCINI= " << i.getnrSarcini();

		out << "\nFACULTATE: " << i.facultate;

	}

	void salariuPotrivit() {

		if (getSalariu() > 5000 && getSalariu() < 10000)
			cout << "\nSALARIUL INGINERULUI ESTE PORTIVIT";

		else

			if (getSalariu() < 5000 || getSalariu() > 10000)
				cout << "\nSALARIUL INGINERULUI NU ESTE POTRIVIT";

	}

	void volumMunca() {

		if (getnrSarcini() > 6)
			cout << "\nVOLUMUL DE MUNCA ESTE PREA MARE";

		else

			if (getnrSarcini() < 3)
				cout << "\nVOLUMUL DE MUNCA ESTE PREA MIC";
	}
};







class InginerSEF : public Inginer {
	int nrMuncitoriCondusi = 0;

public:
	InginerSEF() { cout << "cpnstr inginersef fara param"; }

	InginerSEF(int nrMuncitoriCondusi, const char* facultate, const char* nume, const char* ocupatie, int salariu, int CNP[13], int nrSarcini) : Inginer(facultate, nume, ocupatie, salariu, CNP, nrSarcini) {

		if (nrMuncitoriCondusi > 0)
			this->nrMuncitoriCondusi = nrMuncitoriCondusi;
		else
			this->nrMuncitoriCondusi = 0;


	}

	InginerSEF(const InginerSEF& is) {

		if (is.nrMuncitoriCondusi > 0)
			this->nrMuncitoriCondusi = is.nrMuncitoriCondusi;
		else
			this->nrMuncitoriCondusi = 0;



	}

	~InginerSEF() {


	}

	InginerSEF& operator=(const InginerSEF& is) {

		if (this != &is) {
			if (is.nrMuncitoriCondusi > 0)
				this->nrMuncitoriCondusi = is.nrMuncitoriCondusi;
			else
				this->nrMuncitoriCondusi = 0;
		}


		return *this;
	}

	friend ostream& operator<<(ostream& out, InginerSEF& is) {

		d.nrAfisari();

		out << "\nNUME= " << is.getNume();
		out << "\nOCUPATIE= " << is.getOcupatie();

		out << "\nCNP= " << is.getCNP();

		out << "\nSALARIU= " << is.getSalariu();
		out << "\nNR SARCINI= " << is.getnrSarcini();

		out << "\nFACULTATE: " << is.getFacultate();
		out << "\nNR MUNCITORI CONDUSI: " << is.nrMuncitoriCondusi;

	}
};









class Factura {
	const int nrOrdine;

	char* adresa = NULL;
	int sumaColectata;
	char* denumireServiciu = NULL;

	static float TVA;

	int nrServicii;
	int pretServiciu[10];

public:

	Factura() : nrOrdine(NR_ORDINE_DEFAULT) {
		cout << "\nconstr factura fara parametri";
	}

	//METODA CARE AFLA PRETUL UNUI PACHET COMPLET(CONTINE TOATE SERVICIILE)
	void pachetComplet(int pretServiciu[10], int nrServicii) {
		int suma = 0;
		for (int i = 0; i < nrServicii; i++)
			if (pretServiciu[i] > 0)
				suma += pretServiciu[i];


		cout << "\nPACHETU COMPLET ESTE: " << suma;
	}

	//METODA CARE AFLA SUMA COLECTATA CU TVA
	void sumaColectataTVA(int sumaColectata) {
		float sumaTVA = 0;

		sumaTVA = this->sumaColectata + this->sumaColectata * TVA;

		cout << "\nSUMA COLECTATA CU TVA ESTE= " << sumaTVA;
	}


	//GETTER+SETTER adresa
	char* getAdresa() {
		return this->adresa;
	}
	void setAdresa(const char* adresa) {
		if (adresa != NULL)
			delete[] this->adresa;

		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
	}


	//GETTER+SETTER sumaColectata
	int getSumaColectata() {
		return this->sumaColectata;
	}
	void setSumaColectata(int sumaColectata) {
		if (sumaColectata > 0)
			this->sumaColectata = sumaColectata;
	}

	//GETTER+SETTER denumireSerbiciu
	char* getDenumireServicii() {
		return this->denumireServiciu;
	}
	void setDenumireServicii(const char* denumireServicii) {
		if (denumireServicii != NULL)
			delete[] this->denumireServiciu;

		this->denumireServiciu = new char[strlen(denumireServicii) + 1];
		strcpy(this->denumireServiciu, denumireServicii);
	}

	//GETTER+SETTER nrServicii
	int getNrServicii() {
		return this->nrServicii;
	}
	void setNrServicii(int nrServicii) {
		if (nrServicii > 0)
			this->nrServicii = nrServicii;
	}

	//GETTER nrOrdine
	int getnrOrdine() {
		return this->nrOrdine;
	}

	//GETTER+SETTER TVA
	int getTVA() {
		return this->TVA;
	}
	void setTVA(float TVA) {
		if (TVA > 0)
			this->TVA = TVA;
	}

	//GETTER+SETTER pretServiciu
	int* getPretServiciu() {
		return this->pretServiciu;
	}
	void setPretServiciu(int pretServiciu[10]) {
		for (int i = 0; i < 8; i++)
			if (pretServiciu[i] >= 0)
				this->pretServiciu[i] = pretServiciu[i];
	}

	//CONSTRUCTOR CU 1 PARAMETRU
	Factura(int nrOrdinee) :nrOrdine(0) {

		this->adresa = new char[strlen("FaraNume") + 1];
		strcpy(this->adresa, "FaraNume");

		this->sumaColectata = 0;

		this->denumireServiciu = new char[strlen("FaraNume") + 1];
		strcpy(this->denumireServiciu, "FaraNume");

		this->nrServicii = 0;

		for (int i = 0; i < 10; i++)
			this->pretServiciu[i] = 0;


	}

	//CONSTRUCTOR CU TOTI PARAMETRI
	Factura(int nrOrdinee, const char* adresa, int sumaColectata, const char* denumireServiciu, int nrServicii, int pretServiciu[10]) : nrOrdine(nrOrdinee) {

		if (strlen(adresa) > 0) {
			this->adresa = new char[strlen(adresa) + 1];
			strcpy(this->adresa, adresa);
		}
		else {
			this->adresa = new char[strlen("FaraNume") + 1];
			strcpy(this->adresa, "FaraNume");
		}


		if (sumaColectata > 0)
			this->sumaColectata = sumaColectata;
		else
			this->sumaColectata = 0;


		if (strlen(denumireServiciu) > 0) {
			this->denumireServiciu = new char[strlen(denumireServiciu) + 1];
			strcpy(this->denumireServiciu, denumireServiciu);
		}
		else {
			this->denumireServiciu = new char[strlen("FaraNume") + 1];
			strcpy(this->denumireServiciu, "FaraNume");
		}


		if (nrServicii > 0)
			this->nrServicii = nrServicii;
		else
			this->nrServicii = 0;


		for (int i = 0; i < nrServicii; i++)
			this->pretServiciu[i] = pretServiciu[i];




	}

	//CONSTRUCTOR COPIERE
	Factura(const Factura& f) : nrOrdine(f.nrOrdine) {

		if (strlen(f.adresa) > 0) {
			this->adresa = new char[strlen(f.adresa) + 1];
			strcpy(this->adresa, f.adresa);
		}
		else {
			this->adresa = new char[strlen("FaraNume") + 1];
			strcpy(this->adresa, "FaraNume");
		}


		if (f.sumaColectata > 0)
			this->sumaColectata = f.sumaColectata;
		else
			this->sumaColectata = 0;


		if (strlen(f.denumireServiciu) > 0) {
			this->denumireServiciu = new char[strlen(f.denumireServiciu) + 1];
			strcpy(this->denumireServiciu, f.denumireServiciu);
		}
		else {
			this->denumireServiciu = new char[strlen("FaraNume") + 1];
			strcpy(this->denumireServiciu, "FaraNume");
		}


		if (f.nrServicii > 0)
			this->nrServicii = f.nrServicii;
		else
			this->nrServicii = 0;


		for (int i = 0; i < f.nrServicii; i++)
			this->pretServiciu[i] = f.pretServiciu[i];



	}

	//DESTRUCTOR
	~Factura() {

		if (adresa != NULL)
			delete[] this->adresa;

		if (denumireServiciu != NULL)
			delete[] this->denumireServiciu;

		cout << "\nAPELARE DESTRUCTOR";
	}

	//OPERATOR =
	Factura& operator=(const Factura& f) {

		if (this != &f) {

			if (adresa != NULL)
				delete[] this->adresa;

			if (denumireServiciu != NULL)
				delete[] this->denumireServiciu;

			if (strlen(f.adresa) > 0) {
				this->adresa = new char[strlen(f.adresa) + 1];
				strcpy(this->adresa, f.adresa);
			}
			else {
				this->adresa = new char[strlen("FaraNume") + 1];
				strcpy(this->adresa, "FaraNume");
			}


			if (f.sumaColectata > 0)
				this->sumaColectata = f.sumaColectata;
			else
				this->sumaColectata = 0;


			if (strlen(f.denumireServiciu) > 0) {
				this->denumireServiciu = new char[strlen(f.denumireServiciu) + 1];
				strcpy(this->denumireServiciu, f.denumireServiciu);
			}
			else {
				this->denumireServiciu = new char[strlen("FaraNume") + 1];
				strcpy(this->denumireServiciu, "FaraNume");
			}


			if (f.nrServicii > 0)
				this->nrServicii = f.nrServicii;
			else
				this->nrServicii = 0;


			for (int i = 0; i < f.nrServicii; i++)
				this->pretServiciu[i] = f.pretServiciu[i];

		}

		;
		return *this;
	}

	//OPERATOR << AFISARE
	friend ostream& operator<<(ostream& out, const Factura& f) {

		d.nrAfisari();

		out << "\nADRESA: " << f.adresa;

		out << "\nDENUMIRE SERVICIU: " << f.denumireServiciu;

		out << "\nSUMA COLECTATA: " << f.sumaColectata;

		out << "\nNR ORDINE: " << f.nrOrdine;

		out << "\nTVA: " << f.TVA;

		out << "\nNR SERVICII: " << f.nrServicii;

		for (int i = 0; i < f.nrServicii; i++)
			out << "\nPRETUL SERVICIULUI " << i + 1 << " ESTE " << f.pretServiciu[i];


		return out;
	}

	//OPERATOR >> CITIRE
	friend istream& operator>>(istream& in, Factura& f) {

		d.nrCitiri();

		if (f.adresa != NULL)
			delete[] f.adresa;

		if (f.denumireServiciu != NULL)
			delete[] f.denumireServiciu;


		f.adresa = new char[200];
		cout << "\nADRESA: ";
		in >> f.adresa;

		f.denumireServiciu = new char[200];
		cout << "\nDENUMIRE SERVICIU";
		in >> f.denumireServiciu;

		cout << "\nSUMA COLECTATA: ";
		in >> f.sumaColectata;

		cout << "\nNR SERVICII: ";
		in >> f.nrServicii;

		for (int i = 0; i < f.nrServicii; i++) {
			cout << "\nPRETUL SERVICIULUI " << i + 1 << " ESTE: ";
			in >> f.pretServiciu[i];
		}


		return in;
	}


	//OPERATOR >> OFstream
	friend ofstream& operator<<(ofstream& fout, const Factura& f) {

		d.nrAfisari();

		fout << "\n---------------------------------------------";

		fout << "\nADRESA: " << f.adresa;
		fout << "\nDENUMIRE SERVICIU: " << f.denumireServiciu;

		fout << "\nSUMA COLECTATA: " << f.sumaColectata;

		fout << "\nNR ORDINE: " << f.nrOrdine;
		fout << "\nTVA: " << f.TVA;

		fout << "\nNR SERVICII: " << f.nrServicii;
		for (int i = 0; i < f.nrServicii; i++)
			fout << "\nPRETUL SERVICIULUI " << i + 1 << " ESTE " << f.pretServiciu[i];

		fout << "\n---------------------------------------------";


		return fout;
	}

	//OPERATOR >> IFstream
	friend ifstream& operator>>(ifstream& fin, Factura& f) {

		d.nrCitiri();


		if (f.adresa != NULL)
			delete[] f.adresa;
		if (f.denumireServiciu != NULL)
			delete[] f.denumireServiciu;


		f.adresa = new char[200];
		cout << "\nADRESA: ";
		fin >> f.adresa;

		f.denumireServiciu = new char[200];
		cout << "\nDENUMIRE SERVICIU";
		fin >> f.denumireServiciu;

		cout << "\nSUMA COLECTATA: ";
		fin >> f.sumaColectata;

		cout << "\nNR SERVICII: ";
		fin >> f.nrServicii;


		for (int i = 0; i < f.nrServicii; i++) {
			cout << "\nPRETUL SERVICIULUI " << i + 1 << " ESTE: ";
			fin >> f.pretServiciu[i];
		}


		return fin;
	}


	void scrieBinar(ofstream& o) {

		d.nrAfisari();



		int lungimeAdresa = strlen(this->adresa) + 1;//  
		o.write((char*)&lungimeAdresa, sizeof(int));//  
		o.write(this->adresa, sizeof(char) * lungimeAdresa);// 



		int lungimeDenumireServiciu = strlen(this->denumireServiciu) + 1;//  
		o.write((char*)&lungimeDenumireServiciu, sizeof(int));//  
		o.write(this->denumireServiciu, sizeof(char) * lungimeDenumireServiciu);// 



		o.write((char*)&this->sumaColectata, sizeof(this->sumaColectata));


		o.write((char*)&this->nrOrdine, sizeof(this->nrOrdine));


		o.write((char*)&this->TVA, sizeof(this->TVA));


		o.write((char*)&this->nrServicii, sizeof(this->nrServicii));



		for (int i = 0; i < this->nrServicii; i++) {

			o.write((char*)&this->pretServiciu[i], sizeof(nrServicii));
		}

	}


	void citireBinar(ifstream& in) {

		d.nrCitiri();


		int lungimeAdresa;
		in.read((char*)&lungimeAdresa, sizeof(int));
		char a[2300];
		in.read(a, lungimeAdresa);

		delete[] this->adresa;
		this->adresa = new char[strlen(a) + 1];
		strcpy(this->adresa, a);



		int lungimeDenumireServiciu;
		in.read((char*)&lungimeDenumireServiciu, sizeof(int));
		char b[2300];
		in.read(b, lungimeDenumireServiciu);

		delete[] this->denumireServiciu;
		this->denumireServiciu = new char[strlen(b) + 1];
		strcpy(this->denumireServiciu, b);



		in.read((char*)&this->sumaColectata, sizeof(this->sumaColectata));



		in.read((char*)&this->nrServicii, sizeof(this->nrServicii));


		for (int i = 0; i < this->nrServicii; i++) {
			in.read((char*)&this->pretServiciu[i], sizeof(nrServicii));
		}

	}


	//OPERATOR ! NEGATIE
	bool operator!() {
		return !(sumaColectata == 0);
	}


	//OPERATOR ++ PREINCREMENTARE
	Factura& operator++() {
		nrServicii = nrServicii + 1; //nrServicii++
		return *this;
	}


	//OPERATOR ++ POSTINCREMENTARE
	Factura operator++(int fictiv) {
		Factura temp = *this;

		nrServicii++;

		return *this;

	}


	//OPERATOR==
	bool operator==(Factura& f) {
		if ((this->nrOrdine == f.nrOrdine) && (this->sumaColectata == f.sumaColectata) && (this->TVA == f.TVA) && strcmp(this->adresa, f.adresa) == 0 && strcmp(this->denumireServiciu, f.denumireServiciu) == 0 && (this->nrServicii == f.nrServicii)) {

			for (int i = 9; i < f.nrServicii; i++)
				if (this->pretServiciu[i] != f.pretServiciu[i])
					return false;

		}
		else {
			return false;
		}

		return true;
	}


	//OPERATOR[]
	float operator[](int poz) {
		if (poz >= 0 && poz < this->nrServicii)
			return this->pretServiciu[poz];

		return -1;
	}


	//OPERATOR<
	bool operator<(const Factura& f) const {
		if (this->nrServicii < f.nrServicii)
			return true;
		else
			return false;
	}


	//OPERATOR+
	Factura operator+(Factura f) {
		Factura copie = *this;
		copie.sumaColectata = sumaColectata + f.sumaColectata;
		return copie;
	}


	//OPERATOR CAST
	explicit operator int() {
		return this->sumaColectata;
	}

};

float Factura::TVA = 0.19;









class Programari {

	char* ziua = NULL;
	char* numeClient = NULL;

	int nrProbleme;
	int durataRezolvareProbleme[100];

	bool reducere;
	int ora;

public:
	Programari() { cout << "constr programari fara param"; }

	//METODA CARE CALCULEAZA DURATA DE REZOLVARE TOTALA,A TUTUROR PROBLEMELOR
	void rezolvareTotatala(int nrProbleme, int durataRezolvareProbleme[100]) {
		int rT = 0;
		for (int i = 0; i < nrProbleme; i++)
			rT += durataRezolvareProbleme[i];

		cout << "\nDURATA TOTALA DE REZOLVARE A TUTUROR PROBLEMELOR ESTE DE" << rT;
	}

	//METODA CARE AFLA DACA PROBLEME SE POATE REZOLVA INTR-O ZI
	void timpProblema(int nrProbleme, int durataRezolvareProbleme[100]) {
		int nrOrePosibile = 0;

		if (ora >= 7 && ora <= 23) {
			nrOrePosibile = 17;
			if (nrProbleme > 0 && durataRezolvareProbleme != NULL)
				for (int i = 0; i < nrProbleme; i++)
					nrOrePosibile = nrOrePosibile - durataRezolvareProbleme[i];
		}

		if (nrOrePosibile >= 0)
			cout << "\nProblemele masinii se pot rezolva intr-o zi";
		else
			cout << "\nProblemele masinii nu se pot rezolva intr-o zi";
	}

	//GETTER+SETTER ziua
	char* getZiua() {
		return this->ziua;
	}
	void setZiua(const char* ziua) {
		if (ziua != NULL) {
			delete[] this->ziua;
		}

		this->ziua = new char[strlen(ziua) + 1];
		strcpy(this->ziua, ziua);
	}

	//GETTER+SETTER numeClient
	char* getNumeClient() {
		return this->numeClient;
	}
	void setNumeClient(const char* numeClient) {
		if (numeClient != NULL) {
			delete[] this->numeClient;
		}

		this->numeClient = new char[strlen(numeClient) + 1];
		strcpy(this->numeClient, numeClient);
	}

	//GETTER+SETTER nrProbleme
	int getNrProbleme() {
		return this->nrProbleme;
	}
	void setNrProbleme(int nrProbleme) {
		if (nrProbleme > 0)
			this->nrProbleme = nrProbleme;
	}


	//GETTER+SETTER durataRezolvareProbleme
	int* getDurataRezolvareProbleme() {
		return this->durataRezolvareProbleme;
	}
	void setDurataRezolvareProbleme(int durataRezolvareProbleme[100], int nrPorbleme) {

		if (nrPorbleme > 0) {
			this->nrProbleme = nrPorbleme;
			for (int i = 0; i < nrPorbleme; i++)
				this->durataRezolvareProbleme[i] = durataRezolvareProbleme[i];
		}
	}


	//GETTER+SETTER reducere
	bool getReducere() {
		return this->reducere;
	}
	void setReducere(bool reducere) {
		this->reducere = reducere;
	}


	//GETTER+SETTER ora
	int getOra() {
		return this->ora;
	}
	void setOra(int ora) {
		if (ora >= 7 && ora <= 23)
			this->ora = ora;
	}


	//CONSTRUCTOR CU 1 PARAMETRU
	Programari(const char* ziua) {

		this->ziua = new char[strlen("FaraNume") + 1];
		strcpy(this->ziua, "FaraNume");

		this->numeClient = new char[strlen("FaraNume") + 1];
		strcpy(this->numeClient, "FaraNume");

		this->nrProbleme = 0;

		for (int i = 0; i < 10; i++)
			this->durataRezolvareProbleme[i] = 0;

		this->reducere = false;


	}


	//CONSTRUCTOR CU TOTI PARAMETRI
	Programari(const char* ziua, const char* numeClient, int nrProbleme, int durataRezolvareProbleme[100], bool reducere, int ora) {

		if (strlen(ziua) > 0) {
			this->ziua = new char[strlen(ziua) + 1];
			strcpy(this->ziua, ziua);
		}
		else {
			this->ziua = new char[strlen("FaraNume") + 1];
			strcpy(this->ziua, "FaraNume");
		}


		if (strlen(numeClient) > 0) {
			this->numeClient = new char[strlen(numeClient) + 1];
			strcpy(this->numeClient, numeClient);
		}
		else {
			this->numeClient = new char[strlen("FaraNume") + 1];
			strcpy(this->numeClient, "FaraNume");
		}


		if (durataRezolvareProbleme != NULL && nrProbleme > 0) {
			this->nrProbleme = nrProbleme;

			for (int i = 0; i < nrProbleme; i++)
				this->durataRezolvareProbleme[i] = durataRezolvareProbleme[i];
		}
		else {
			this->nrProbleme = 0;
			this->durataRezolvareProbleme[100] = { 0 };
		}

		if (reducere == true || reducere == false)
			this->reducere = reducere;

		if (ora >= 7 && ora <= 23)
			this->ora = ora;
		else
			this->ora = 0;




	}


	//COPY CONSTRUCTOR PROGRAMARI
	Programari(const Programari& p) {

		if (strlen(p.ziua) > 0) {
			this->ziua = new char[strlen(p.ziua) + 1];
			strcpy(this->ziua, p.ziua);
		}
		else {
			this->ziua = new char[strlen("FaraNume") + 1];
			strcpy(this->ziua, "FaraNume");
		}


		if (strlen(p.numeClient) > 0) {
			this->numeClient = new char[strlen(p.numeClient) + 1];
			strcpy(this->numeClient, p.numeClient);
		}
		else {
			this->numeClient = new char[strlen("FaraNume") + 1];
			strcpy(this->numeClient, "FaraNume");
		}


		if (p.durataRezolvareProbleme != NULL && p.nrProbleme > 0) {
			this->nrProbleme = p.nrProbleme;

			for (int i = 0; i < p.nrProbleme; i++)
				this->durataRezolvareProbleme[i] = p.durataRezolvareProbleme[i];
		}
		else {
			this->nrProbleme = 0;
			this->durataRezolvareProbleme[100] = { 0 };
		}

		if (p.reducere == true || p.reducere == false)
			this->reducere = p.reducere;

		if (p.ora >= 7 && p.ora <= 23)
			this->ora = p.ora;
		else
			this->ora = 0;




	}


	//DESTRUCTOR
	~Programari() {

		if (numeClient != NULL)
			delete[] this->numeClient;

		if (ziua != NULL)
			delete[] this->ziua;

		cout << "\nAPELARE DESTRUCTOR";
	}


	//OPERATOR =
	Programari& operator=(const Programari& p) {

		if (this != &p) {

			if (numeClient != NULL)
				delete[] this->numeClient;

			if (ziua != NULL)
				delete[] this->ziua;

			if (strlen(p.ziua) > 0) {
				this->ziua = new char[strlen(p.ziua) + 1];
				strcpy(this->ziua, p.ziua);
			}
			else {
				this->ziua = new char[strlen("FaraNume") + 1];
				strcpy(this->ziua, "FaraNume");
			}


			if (strlen(p.numeClient) > 0) {
				this->numeClient = new char[strlen(p.numeClient) + 1];
				strcpy(this->numeClient, p.numeClient);
			}
			else {
				this->numeClient = new char[strlen("FaraNume") + 1];
				strcpy(this->numeClient, "FaraNume");
			}


			if (p.durataRezolvareProbleme != NULL && p.nrProbleme > 0) {
				this->nrProbleme = p.nrProbleme;

				for (int i = 0; i < p.nrProbleme; i++)
					this->durataRezolvareProbleme[i] = p.durataRezolvareProbleme[i];
			}
			else {
				this->nrProbleme = 0;
				this->durataRezolvareProbleme[100] = { 0 };
			}

			if (p.reducere == true || p.reducere == false)
				this->reducere = p.reducere;

			if (p.ora >= 7 && p.ora <= 23)
				this->ora = p.ora;
			else
				this->ora = 0;
		}


		return *this;
	}


	//OPERATOR<<
	friend ostream& operator<<(ostream& out, const Programari& p) {

		d.nrAfisari();

		out << "\nZIUA: " << p.ziua;

		out << "\nNUME CLIENT: " << p.numeClient;

		out << "\nNR PROBLEME: " << p.nrProbleme;

		out << "\nDURATA REZOLVARII PROBLEMELOR: ";
		for (int i = 0; i < p.nrProbleme; i++)
			out << p.durataRezolvareProbleme[i] << "	";

		out << "\nREDUCERE: " << p.reducere;

		out << "\nORA: " << p.ora;

		return out;
	}


	//OPERATPR >>
	friend istream& operator>>(istream& in, Programari& p) {
		d.nrCitiri();

		if (p.ziua != NULL)
			delete[] p.ziua;

		if (p.numeClient != NULL)
			delete[] p.numeClient;


		p.ziua = new char[200];
		cout << "\nZIUA: ";
		in >> p.ziua;

		p.numeClient = new char[200];
		cout << "\nNUME CLIENT: ";
		in >> p.numeClient;

		cout << "\nNR PROBLEME: ";
		in >> p.nrProbleme;

		cout << "\nDURATA REZOLVARII PROBLEMELOR: ";
		for (int i = 0; i < p.nrProbleme; i++)
			in >> p.durataRezolvareProbleme[i];

		cout << "\nREDUCERE: ";
		in >> p.reducere;

		cout << "\nORA: ";
		in >> p.ora;

		return in;
	}


	//OPERATOR << OFSTREAM
	friend ofstream& operator<<(ofstream& out, const Programari& p) {

		d.nrAfisari();

		out << "\n---------------------------------------------";

		out << "\nZIUA: " << p.ziua;
		out << "\nNUME CLIENT: " << p.numeClient;

		out << "\nNR PROBLEME: " << p.nrProbleme;

		out << "\nDURATA REZOLVARII PROBLEMELOR: ";
		for (int i = 0; i < p.nrProbleme; i++)
			out << p.durataRezolvareProbleme[i] << "	";

		out << "\nREDUCERE: " << p.reducere;
		out << "\nORA: " << p.ora;

		out << "\n---------------------------------------------";

		out << endl;


		return out;
	}


	//OPERATOR >> IFSTREAM
	friend ifstream& operator>>(ifstream& in, Programari& p) {

		d.nrCitiri();

		if (p.ziua != NULL)
			delete[] p.ziua;
		if (p.numeClient != NULL)
			delete[] p.numeClient;


		p.ziua = new char[200];
		cout << "\nZIUA: ";
		in >> p.ziua;

		p.numeClient = new char[200];
		cout << "\nNUME CLIENT: ";
		in >> p.numeClient;

		cout << "\nNR PROBLEME: ";
		in >> p.nrProbleme;

		cout << "\nDURATA REZOLVARII PROBLEMELOR: ";
		for (int i = 0; i < p.nrProbleme; i++)
			in >> p.durataRezolvareProbleme[i];

		cout << "\nREDUCERE: ";
		in >> p.reducere;

		cout << "\nORA: ";
		in >> p.ora;



		return in;
	}



	void scrieBinar(ofstream& o) {

		d.nrAfisari();


		int lungimeAdresa = strlen(this->ziua) + 1;
		o.write((char*)&lungimeAdresa, sizeof(int));
		o.write(this->ziua, sizeof(char) * lungimeAdresa);



		int lungimeNumeClient = strlen(this->numeClient) + 1;
		o.write((char*)&lungimeNumeClient, sizeof(int));
		o.write(this->numeClient, sizeof(char) * lungimeNumeClient);




		o.write((char*)&this->nrProbleme, sizeof(this->nrProbleme));


		for (int i = 0; i < this->nrProbleme; i++) {

			o.write((char*)&this->durataRezolvareProbleme[i], sizeof(int));
		}


		o.write((char*)&this->ora, sizeof(this->ora));



		o.write((char*)&this->reducere, sizeof(this->reducere));

	}


	void citireBinar(ifstream& in) {

		d.nrCitiri();


		int lungimeZiua;
		in.read((char*)&lungimeZiua, sizeof(int));
		char a[2300];
		in.read(a, lungimeZiua);

		delete[] this->ziua;
		this->ziua = new char[strlen(a) + 1];
		strcpy(this->ziua, a);




		int lungimeNumeClient;
		in.read((char*)&lungimeNumeClient, sizeof(int));
		char b[2300];
		in.read(b, lungimeNumeClient);

		delete[] this->numeClient;
		this->numeClient = new char[strlen(b) + 1];
		strcpy(this->numeClient, b);



		in.read((char*)&this->nrProbleme, sizeof(this->nrProbleme));


		for (int i = 0; i < this->nrProbleme; i++) {
			in.read((char*)&this->durataRezolvareProbleme[i], sizeof(int));
		}



		in.read((char*)&this->ora, sizeof(this->ora));


		in.read((char*)&this->reducere, sizeof(this->reducere));

	}


	void raportProgramare(const char* f) {
		ofstream outProgramare;
		outProgramare.open(f, ofstream::out);

		outProgramare << "\nZiua " << ziua << " a inceput cu clientu " << numeClient << " cu nr-ul de probleme " << nrProbleme << " la ora " << ora << " , si cu durata problemelor de: ";

		for (int i = 0; i < nrProbleme; i++)
			outProgramare << endl << durataRezolvareProbleme[i] << endl;

		outProgramare << "\nAre reducere? " << reducere;
	}

	//OPERATOR ! NEGATIE
	bool operator!() {
		return !(reducere == false);
	}


	//OPERATOR==
	bool operator==(Programari& p) {
		if (strcmp(this->ziua, p.ziua) == 0 && (this->reducere == p.reducere) && (this->ora == p.ora) && strcmp(this->numeClient, p.numeClient) == 0 && (this->nrProbleme == p.nrProbleme)) {

			for (int i = 0; i < p.nrProbleme; i++)
				if (this->durataRezolvareProbleme[i] != p.durataRezolvareProbleme[i])
					return false;
		}
		else {
			return false;
		}

		return true;
	}


	//OPERATOR[]
	float operator[](int poz) {
		if (poz >= 0 && poz < this->nrProbleme)
			return this->durataRezolvareProbleme[poz];

		return -1;
	}


	//OPERATOR ++ PREINCREMENTARE
	Programari& operator++() {
		ora = ora + 1;
		return *this;
	}


	//OPERATOR ++ POSTINCREMENTARE
	Programari operator++(int fictiv) {
		Programari temp = *this;

		ora++;

		return *this;

	}

	//OPERATOR<
	bool operator<(const Programari& p) const {
		if (this->nrProbleme < p.nrProbleme)
			return true;
		else
			return false;
	}

	//OPERATOR+
	Programari operator+(int i) {
		Programari copie = *this;
		copie.nrProbleme += i;

		return copie;
	}

	//OPERATOR CAST
	explicit operator int() {
		return this->ora;
	}
};









class OperareFisier {

public:

	void writeToFile(ofstream& fout, Masina sursa) {

		sursa.scrieBinar(fout);

	}

	void readFromFile(ifstream& fin, Masina& sursa) {

		sursa.citireBinar(fin);

	}





	void writeToFile(ofstream& fout, Angajat sursa) {

		sursa.scrieBinar(fout);

	}

	void readFromFile(ifstream& fin, Angajat& sursa) {

		sursa.citireBinar(fin);

	}




	void writeToFile(ofstream& fout, Factura sursa) {

		sursa.scrieBinar(fout);

	}

	void readFromFile(ifstream& fin, Factura& sursa) {

		sursa.citireBinar(fin);

	}




	void writeToFile(ofstream& fout, Programari sursa) {

		sursa.scrieBinar(fout);

	}

	void readFromFile(ifstream& fin, Programari& sursa) {

		sursa.citireBinar(fin);

	}
};










class ServiceAuto {

	int nrAngajati;
	int nrMasini;

	char* numeService = NULL;
	int* pretMasini = NULL;


	int oreDeschidereZi[7];
	float profit;

	Masina* listaMasini = NULL;
	Angajat* listaAngajati = NULL;

	Programari* listaProgramari = NULL;
	int nrProgramari;

	Factura* listaFacturi = NULL;
	int nrFacturi;

public:

	//GETTER+SETTER nrAngajati
	int getnrAngajati() {
		return this->nrAngajati;
	}

	void setnrAngajati(int nrAngajati) {
		if (nrAngajati > 0)
			this->nrAngajati = nrAngajati;
	}



	//GETTER+SETTER nrMasini
	int getnrMasini() {
		return this->nrMasini;
	}

	void setnrMasini(int nrMasini) {
		if (nrMasini > 0)
			this->nrMasini = nrMasini;
	}



	//GETTER+SETTER numeService
	char* getnumeService() {
		return this->numeService;
	}

	void setNumeService(const char* numeService) {
		if (numeService != NULL) {
			delete[] this->numeService;
		}

		this->numeService = new char[strlen(numeService) + 1];
		strcpy(this->numeService, numeService);
	}



	//GETTER+SETTER pretMasini
	int* getpretMasini() {
		return this->pretMasini;
	}

	void setpretMasini(int* pretMasini, int nrMasini) {
		if (pretMasini != NULL) {
			delete[] this->pretMasini;
		}


		if (pretMasini != NULL && nrMasini > 0) {
			this->nrMasini = nrMasini;
			this->pretMasini = new int[nrMasini];

			for (int i = 0; i < nrMasini; i++)
				this->pretMasini = pretMasini;
		}
	}



	//GETTER+SETTER oreDeschidereZi
	int* getOreDeschidereZi() {
		return this->oreDeschidereZi;
	}

	void setOreDeschidereZi(int oreDeschidereZi[7]) {
		for (int i = 0; i < 7; i++)
			if (oreDeschidereZi[i] > 8)
				this->oreDeschidereZi[i] = oreDeschidereZi[i];
	}



	//GETTER+SETTER profit
	float getProfit() {
		return this->profit;
	}

	void setProfit(float profit) {
		if (profit > 0)
			this->profit = profit;
	}


	//METODA CARE CALCULEAZA VALOAREA TOTALA A MASINILOR
	void valoareVanzari(int nrMasini, int* pretMasini) {
		int valoare = 0;
		if (nrMasini > 0 && pretMasini != NULL) {
			for (int i = 0; i < nrMasini; i++)
				valoare += pretMasini[i];

			cout << "\nVALOAREA TOTALA A MASINILOR ESTE (nrMasini*pretMasini): " << valoare;
		}
	}


	//METODA CARE CALCULEZA CATI ANGAJATI SUNT ALOCATI LUCRULUI ASUPREA UNEI MASINI
	void alocareAngatiperMasini(int nrAngajati, int nrMasini) {
		int rezultat = 0;
		if (nrAngajati > 0 && nrMasini > 0)
			rezultat = nrAngajati / nrMasini;

		cout << "\nALOCARE ANGATI PER MASINI: " << rezultat;
	}

	ServiceAuto() { cout << "\nconstr service fara param"; }

	//CONSTRUCTOR CU 1 PARAMETRU
	ServiceAuto(int nrAngajati) {
		this->nrAngajati = 0;
		this->nrMasini = 0;

		this->numeService = new char[strlen("FaraNume") + 1];
		strcpy(this->numeService, "FaraNume");

		this->pretMasini = NULL;

		for (int i = 0; i < 7; i++)
			this->oreDeschidereZi[i] = 0;

		this->profit = 0;

		this->listaMasini = NULL;
		this->listaAngajati = NULL;
		this->listaFacturi = NULL;
		this->listaProgramari = NULL;


	}


	//CONSTRUCTOR CU TOTI PARAMETRI
	ServiceAuto(int nrAngajati, int nrMasini, const char* numeService, int* pretMasini, int oreDeschidereZi[7], float profit, Masina* listaMasini, Angajat* listaAngajati, Factura* listaFacturi, Programari* listaProgramari, int nrFacturi, int nrProgramari) {
		if (nrAngajati > 0 && listaAngajati != NULL) {
			this->nrAngajati = nrAngajati;

			this->listaAngajati = new Angajat[nrAngajati];
			for (int i = 0; i < nrAngajati; i++)
				this->listaAngajati[i] = listaAngajati[i];
		}


		else {
			this->nrAngajati = 0;
			this->listaAngajati = NULL;
		}


		if (strlen(numeService) > 0) {
			this->numeService = new char[strlen(numeService) + 1];
			strcpy(this->numeService, numeService);
		}
		else {
			this->numeService = new char[strlen("FaraNume") + 1];
			strcpy(this->numeService, "FaraNume");
		}


		if (nrMasini > 0 && pretMasini != NULL && listaMasini != NULL) {

			this->nrMasini = nrMasini;
			this->pretMasini = new int[nrMasini];
			this->listaMasini = new Masina[nrMasini];

			for (int i = 0; i < nrMasini; i++)
				this->pretMasini[i] = pretMasini[i];

			for (int i = 0; i < nrMasini; i++)
				this->listaMasini[i] = listaMasini[i];
		}
		else {
			this->nrMasini = 0;
			this->pretMasini = NULL;
			this->listaMasini = NULL;
		}


		if (nrFacturi > 0 && listaFacturi != NULL) {
			this->nrFacturi = nrFacturi;
			this->listaFacturi = new Factura[nrFacturi];

			for (int i = 0; i < nrFacturi; i++)
				this->listaFacturi[i] = listaFacturi[i];
		}
		else {
			this->nrFacturi = 0;
			this->listaFacturi = NULL;

		}

		if (nrProgramari > 0 && listaProgramari != NULL) {
			this->nrProgramari = nrProgramari;
			this->listaProgramari = new Programari[nrProgramari];

			for (int i = 0; i < nrProgramari; i++)
				this->listaProgramari[i] = listaProgramari[i];
		}
		else {
			this->nrProgramari = 0;
			this->listaProgramari = NULL;

		}



		for (int i = 0; i < 7; i++)
			if (oreDeschidereZi[i] > 8)
				this->oreDeschidereZi[i] = oreDeschidereZi[i];

		if (profit > 0)
			this->profit = profit;
		else
			this->profit = 0;




	}


	//CONSTRUCTOR COPIERE
	ServiceAuto(const ServiceAuto& s) {
		if (s.nrAngajati > 0 && s.listaAngajati != NULL) {
			this->nrAngajati = s.nrAngajati;

			this->listaAngajati = new Angajat[s.nrAngajati];
			for (int i = 0; i < s.nrAngajati; i++)
				this->listaAngajati[i] = s.listaAngajati[i];
		}


		else {
			this->nrAngajati = 0;
			this->listaAngajati = NULL;
		}


		if (strlen(s.numeService) > 0) {
			this->numeService = new char[strlen(s.numeService) + 1];
			strcpy(this->numeService, s.numeService);
		}
		else {
			this->numeService = new char[strlen("FaraNume") + 1];
			strcpy(this->numeService, "FaraNume");
		}


		if (s.nrMasini > 0 && s.pretMasini != NULL && s.listaMasini != NULL) {

			this->nrMasini = s.nrMasini;
			this->pretMasini = new int[s.nrMasini];
			this->listaMasini = new Masina[s.nrMasini];

			for (int i = 0; i < s.nrMasini; i++)
				this->pretMasini[i] = s.pretMasini[i];

			for (int i = 0; i < s.nrMasini; i++)
				this->listaMasini[i] = s.listaMasini[i];
		}
		else {
			this->nrMasini = 0;
			this->pretMasini = NULL;
			this->listaMasini = NULL;
		}


		if (s.nrFacturi > 0 && s.listaFacturi != NULL) {
			this->nrFacturi = s.nrFacturi;
			this->listaFacturi = new Factura[s.nrFacturi];

			for (int i = 0; i < s.nrFacturi; i++)
				this->listaFacturi[i] = s.listaFacturi[i];
		}
		else {
			this->nrFacturi = 0;
			this->listaFacturi = NULL;
		}

		if (s.nrProgramari > 0 && s.listaProgramari != NULL) {
			this->nrProgramari = s.nrProgramari;
			this->listaProgramari = new Programari[s.nrProgramari];

			for (int i = 0; i < s.nrProgramari; i++)
				this->listaProgramari[i] = s.listaProgramari[i];
		}
		else {
			this->nrProgramari = 0;
			this->listaProgramari = NULL;

		}



		for (int i = 0; i < 7; i++)
			if (s.oreDeschidereZi[i] > 8)
				this->oreDeschidereZi[i] = s.oreDeschidereZi[i];

		if (s.profit > 0)
			this->profit = s.profit;
		else
			this->profit = 0;


	}


	//DESTRUCTOR
	~ServiceAuto() {
		if (pretMasini != NULL) {
			delete[] this->pretMasini;
		}

		if (numeService != NULL) {
			delete[] this->numeService;
		}

		if (listaMasini != NULL) {
			delete[] this->listaMasini;
		}

		if (listaAngajati != NULL) {
			delete[] this->listaAngajati;
		}

		if (listaFacturi != NULL)
			delete[] this->listaFacturi;

		if (this->listaProgramari != NULL)
			delete[] this->listaProgramari;


		cout << "\nAPELARE DESTRUCTOR SERVICE";
	}


	//OPERATOR =
	ServiceAuto& operator=(const ServiceAuto& s) {
		if (this != &s) {

			if (pretMasini != NULL) {
				delete[] this->pretMasini;
			}

			if (numeService != NULL) {
				delete[] this->numeService;
			}

			if (listaMasini != NULL) {
				delete[] this->listaMasini;
			}

			if (listaAngajati != NULL) {
				delete[] this->listaAngajati;
			}

			if (listaFacturi != NULL)
				delete[] this->listaFacturi;

			if (this->listaProgramari != NULL)
				delete[] this->listaProgramari;



			if (s.nrAngajati > 0 && s.listaAngajati != NULL) {
				this->nrAngajati = s.nrAngajati;

				this->listaAngajati = new Angajat[s.nrAngajati];
				for (int i = 0; i < s.nrAngajati; i++)
					this->listaAngajati[i] = s.listaAngajati[i];
			}


			else {
				this->nrAngajati = 0;
				this->listaAngajati = NULL;
			}


			if (strlen(s.numeService) > 0) {
				this->numeService = new char[strlen(s.numeService) + 1];
				strcpy(this->numeService, s.numeService);
			}
			else {
				this->numeService = new char[strlen("FaraNume") + 1];
				strcpy(this->numeService, "FaraNume");
			}


			if (s.nrMasini > 0 && s.pretMasini != NULL && s.listaMasini != NULL) {

				this->nrMasini = s.nrMasini;
				this->pretMasini = new int[s.nrMasini];
				this->listaMasini = new Masina[s.nrMasini];

				for (int i = 0; i < s.nrMasini; i++)
					this->pretMasini[i] = s.pretMasini[i];

				for (int i = 0; i < s.nrMasini; i++)
					this->listaMasini[i] = s.listaMasini[i];
			}
			else {
				this->nrMasini = 0;
				this->pretMasini = NULL;
				this->listaMasini = NULL;
			}


			if (s.nrFacturi > 0 && s.listaFacturi != NULL) {
				this->nrFacturi = s.nrFacturi;
				this->listaFacturi = new Factura[s.nrFacturi];

				for (int i = 0; i < s.nrFacturi; i++)
					this->listaFacturi[i] = s.listaFacturi[i];
			}
			else {
				this->nrFacturi = 0;
				this->listaFacturi = NULL;
			}

			if (s.nrProgramari > 0 && s.listaProgramari != NULL) {
				this->nrProgramari = s.nrProgramari;
				this->listaProgramari = new Programari[s.nrProgramari];

				for (int i = 0; i < s.nrProgramari; i++)
					this->listaProgramari[i] = s.listaProgramari[i];
			}
			else {
				this->nrProgramari = 0;
				this->listaProgramari = NULL;

			}



			for (int i = 0; i < 7; i++)
				if (s.oreDeschidereZi[i] > 8)
					this->oreDeschidereZi[i] = s.oreDeschidereZi[i];

			if (s.profit > 0)
				this->profit = s.profit;
			else
				this->profit = 0;


		}
		cout << "\nOPERATOR = SERVICE AUTO";
		return *this;
	}


	//OPERATOR<<
	friend ostream& operator<<(ostream& out, const ServiceAuto& s) {

		d.nrAfisari();

		out << "\nNR ANGATI=" << s.nrAngajati;
		out << "\nNUME SERVICE=" << s.numeService;
		out << "\nNR MASINI=" << s.nrMasini;

		for (int i = 0; i < s.nrMasini; i++)
			out << "\nPRETUL MASINII " << i + 1 << " =" << s.pretMasini[i];

		for (int i = 0; i < 7; i++)
			out << "\nNr de ore in care e deschis service-ul in a " << i + 1 << " zi a saptamii = " << s.oreDeschidereZi[i];

		out << "\nPROFIT=" << s.profit;


		out << "\nLista Masini:	";
		for (int i = 0; i < s.nrMasini; i++)
			out << s.listaMasini[i] << "	";


		out << "\nLista Angajati:		";
		for (int i = 0; i < s.nrAngajati; i++)
			out << s.listaAngajati[i] << "	";


		out << "\nNR FACTURI= " << s.nrFacturi;
		out << "\nLista Facturi:		";
		for (int i = 0; i < s.nrFacturi; i++)
			out << s.listaFacturi[i] << "		";


		out << "\nNR PROGRAMARI= " << s.nrProgramari;
		out << "\nLista Programari:	";
		for (int i = 0; i < s.nrProgramari; i++)
			out << s.listaProgramari[i] << "	";


		return out;
	}


	//OPERATOR>>
	friend istream& operator>>(istream& in, ServiceAuto& s) {

		d.nrCitiri();

		if (s.numeService != NULL)
			delete[] s.numeService;

		if (s.pretMasini != NULL)
			delete[] s.pretMasini;

		if (s.listaMasini != NULL)
			delete[] s.listaMasini;

		if (s.listaAngajati != NULL)
			delete[] s.listaAngajati;

		if (s.listaProgramari != NULL)
			delete[] s.listaProgramari;

		if (s.listaFacturi != NULL)
			delete[] s.listaFacturi;


		cout << "\nNR ANGAJATI= ";
		in >> s.nrAngajati;

		cout << "\nNR MASINI= ";
		in >> s.nrMasini;

		s.pretMasini = new int[s.nrMasini];

		for (int i = 0; i < s.nrMasini; i++) {
			cout << "\nPRETUL MASINII CU NR-UL " << i + 1 << " ESTE ";
			in >> s.pretMasini[i];
		}


		s.numeService = new char[200];
		cout << "\nNUME SERVICE= ";
		in >> s.numeService;

		cout << "PROFIT= ";
		in >> s.profit;


		for (int i = 0; i < 7; i++) {
			cout << "\nCATE ORE E DESCHIS IN ZIUA " << i + 1 << " : ";
			in >> s.oreDeschidereZi[i];
		}


		cout << "\nLista de masini este:	";
		for (int i = 0; i < s.nrMasini; i++)
			in >> s.listaMasini[i];


		cout << "\nLista de programari este:	";
		for (int i = 0; i < s.nrProgramari; i++)
			in >> s.listaProgramari[i];


		cout << "\nLista de facturi este:	";
		for (int i = 0; i < s.nrFacturi; i++)
			in >> s.listaFacturi[i];


		cout << "\nLista de angajati este:	";
		for (int i = 0; i < s.nrAngajati; i++)
			in >> s.listaAngajati[i];

		return in;
	}

	void afisareMasini() {

		for (int i = 0; i < this->nrMasini; i++)
			cout << this->listaMasini[i];
	}

	void afisareAngajati() {

		for (int i = 0; i < this->nrAngajati; i++)
			cout << this->listaAngajati[i];
	}

	void afisareFacturi() {

		for (int i = 0; i < this->nrFacturi; i++)
			cout << this->listaFacturi[i];
	}

	void afisareProgramari() {

		for (int i = 0; i < this->nrProgramari; i++)
			cout << this->listaProgramari[i];
	}

	//OPERATOR ! NEGATIE
	bool operator!() {
		return !(profit == 0);
	}


	//OPERATOR==
	bool operator==(const ServiceAuto& s) {


		if ((this->nrAngajati == s.nrAngajati) && (this->nrMasini == s.nrMasini) && (this->profit == s.profit) && (strcmp(this->numeService, s.numeService) == 0)) {
			for (int i = 0; i < nrMasini; i++)
				if (this->pretMasini[i] != s.pretMasini[i])
					return false;
			for (int i = 0; i < 7; i++)
				if (this->oreDeschidereZi[i] != oreDeschidereZi[i])
					return false;
		}
		else return false;

		return true;

	}


	//OPERATOR[]
	float operator[](int poz) {
		if (poz >= 0 && poz < this->nrMasini)
			return this->pretMasini[poz];

		return -1;
	}


	//OPERATOR ++ PREINCREMENTARE
	ServiceAuto& operator++() {
		this->nrAngajati = nrAngajati + 1;
		return *this;
	}


	//OPERATOR ++ POSTINCREMENTARE
	/*ServiceAuto operator++(int fictiv) {
		ServiceAuto temp = *this;
		
		nrAngajati++;

		return temp;

	}*/
	ServiceAuto  operator++(int) {
		
		ServiceAuto temp;
		
		
		temp.nrAngajati = this->nrAngajati++;
		cout << "\n------------------------------------------------------------------------------------------------";
		return temp;
	}

	//OPERATOR>
	bool operator>(const ServiceAuto& s) const {
		if (this->nrMasini > s.nrMasini)
			return true;
		else
			return false;
	}

	//OPERATOR-
	ServiceAuto operator-(ServiceAuto s) {
		ServiceAuto copie = *this;
		copie.profit = profit - s.profit;
		return copie;
	}


	//OPERATOR CAST
	explicit operator float() {
		return this->profit;
	}

};













int main() {
	/*
			cout << endl;
			cout << "\n	                            APELARE CONSTRUCTOR 1 PARAMETRU	";
			cout << endl;

			ServiceAuto s1(10);	//APELARE CONSTR 1 PARAM
			cout << s1;
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";*/











	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR 1 PARAMETRU	";
	cout << endl;

	Masina m1("BMW");	//APELARE CONSTR 1 PARAM
	cout << m1;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR TOTI	";
	cout << endl;

	int pretAccidente[] = { 500,1000,1500 };
	int sasiuNumeric[10] = { 1,1,1,1,1,1,1,1,1,1 };
	Masina m2("AUDI", 300, 5, 3, pretAccidente, sasiuNumeric);
	cout << m2;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR COPY	";
	cout << endl;

	Masina m3 = m2;
	cout << m3;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE OPERATOR=	";
	cout << endl;

	Masina m4("MERCEDES");
	m4 = m3;//APELARE OPERATOR =
	cout << m4;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE METODA 1 ";
	cout << endl;

	m2.CPpotentiali(300);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE METODA 2	";
	cout << endl;

	m2.OrdineReperatii(3, pretAccidente);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE OPERATOR >>	";
	cout << endl;

	Masina m5("AUDI");
	cout << "\nDATI VALORI PENTRU S5:";
	//cin >> m5;
	cout << m5;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n TEST OPERATORI";
	cout << endl;


	//OPERATOR !
	cout << endl;
	cout << "\n	                            APELARE OPERATOR ! ";
	cout << endl;

	if (m2.operator!() == 1)
		cout << "\nEXISTA PIESE LIPSA";
	else
		cout << "\nNU EXISTA PIESE LIPSA";
	cout << endl;



	//OPERATOR++
	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR OPERATOR ++	";
	cout << endl;

	cout << "\nVALOAREA NR PIESE LIPSA INAINTE DE MODIFICARE(PREINCREMENTARE): " << m2.getNrPieseLipsa();
	cout << endl;
	m2.operator++();
	cout << "\nVALOAREA NR PIESE LIPSA DUPA MODIFICARE(PREINCREMENTARE): " << m2.getNrPieseLipsa();
	cout << endl;

	cout << "\nVALOAREA NR PIESE LIPSA INAINTE DE MODIFICARE(POSTINCREMENTARE): " << m2.getNrPieseLipsa();
	cout << endl;
	m2.operator++(1);
	cout << "\nVALOAREAA NR PIESE LIPSA DUPA MODIFICARE(POSTINCREMENTARE): " << m2.getNrPieseLipsa();
	cout << endl;



	//OPERATOR==
	cout << endl;
	cout << "\n	                            APELARE OPERATOR ==	";
	cout << endl;

	if (m2 == m3)
		cout << "\nOBIECTELE SUNT EGALE";
	else
		cout << "\nOBIECTELE NU SUNT EGALE";
	cout << endl;



	//OPERATOR[]
	cout << endl;
	cout << "\n	                            APELARE OPERATOR []	";
	cout << endl;

	cout << "\nValoarea elementului de pe pozitia dorita este: " << m2[2] << endl;
	cout << endl;



	//OPERATOR>=
	cout << endl;
	cout << "\n	                            APELARE  OPERATOR >=	";
	cout << endl;

	if (m2 >= m3)
		cout << "\nOBIECTUL M2 ARE MAI MULTE SAU ACELASI NR DE ACCIDENTE CA M3";
	else
		cout << "\nOBIECTUL M2 NU ARE MAI MULTE SAU ACELASI NR DE ACCIDENTE CA M3";
	cout << endl;

	//OPERATOR*
	cout << endl;
	cout << "\n	                            APELARE OPERATOR *	";
	cout << endl;
	m4 = m3 * 2;
	cout << "\nM4 E DE 2 ORI MAI PUTERNICA DECAT M3 " << m4 << endl;

	// OPERATOR CAST
	cout << endl;
	cout << "\n	                            APELARE OPERATOR CAST EXPLICIT ";
	cout << endl;

	int CP = int(m2);
	cout << "\nVALOAREA CP  RETURNATA DE OPERATORUL CAST ESTE: " << CP << endl;

	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;



	cout << endl;
	cout << "\n	                            TEST GETTERI + SETTERI 	";
	cout << endl;

	cout << endl;

	//cout << "\nSasiul Numeric: " << m2.getsasiuNumeric() << endl;  //imi afiseaza adresa

	cout << "\nBRAND: " << m2.getBrand();
	m2.setBrand("MAZDA");
	cout << "\nBRAND: " << m2.getBrand();

	cout << "\nCP: " << m2.getCP();
	m2.setCP(500);
	cout << "\nCP: " << m2.getCP();

	cout << "\nNR PIESE LIPSA: " << m2.getNrPieseLipsa();
	m2.setNrPieseLipsa(10);
	cout << "\nNR PIESE LIPSA: " << m2.getNrPieseLipsa();

	cout << "\n NR ACCIDENTE: " << m2.getNrAccidente();
	m2.setNrAccidente(4);
	cout << "\n NR ACCIDENTE: " << m2.getNrAccidente();







	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR 1 PARAMETRU	";
	cout << endl;

	Angajat a1("Dorel");
	cout << a1;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;



	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR CU TOTI PARAMETRI	";
	cout << endl;

	int CNP[13] = { 5,1,1,1,1,1,1,1,1,1,1,1,1 };
	Angajat a2("Andrei", "contabil", 2000, CNP, 5);
	cout << a2;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;



	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR COPY	";
	cout << endl;

	Angajat a3 = a2;
	cout << a3;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;



	cout << endl;
	cout << "\n	                            APELARE OPERATOR =	";
	cout << endl;

	Angajat a4("Bogdan");
	a4 = a3;
	cout << a4;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;

	cout << endl;
	cout << "\n	                            APELARE METODA 1	";
	cout << endl;

	a2.determinareSex(CNP, 13);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;

	cout << endl;
	cout << "\n	                            APELARE METODA 2	";
	cout << endl;

	a2.determinareVarsta(CNP, 13);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            APELARE OPERATOR >> ";
	cout << endl;


	Angajat a5("Andrei");
	cout << "\nDATI VALORI PENTRU a5: ";
	//cin >> a5;
	cout << a5;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";



	cout << endl;
	cout << "\n	                            TEST OPERATORI	";
	cout << endl;

	cout << endl;


	//OPERATOR!
	cout << endl;
	cout << "\n	                            APELARE OPERATOR ! ";
	cout << endl;

	if (a2.operator!() == 1)
		cout << "\nSALARIUL NU ESTE 0";
	else
		cout << "\nSALARIUL ESTE 0";
	cout << endl;



	//OPERATOR ++
	cout << endl;
	cout << "\n	                            APELARE OPERATOR ++ ";
	cout << endl;

	cout << "\nVALOARE NR SARCINI INAINTE DE MODIFICARE(PREINCREMENTARE): " << a2.getnrSarcini();
	cout << endl;
	a2.operator++();
	cout << "\nVALOAREA NR SARCINI DUPA MODIFICARE(PREINCREMENTARE): " << a2.getnrSarcini();
	cout << endl;

	cout << "\nVALOARE NR SARCINI INAINTE DE MODIFICARE(POSTINCREMENTARE): " << a2.getnrSarcini();
	cout << endl;
	a2.operator++(1);
	cout << "\nVALOAREA NR SARCINI DUPA MODIFICARE(POSTINCREMENTARE): " << a2.getnrSarcini();
	cout << endl;



	//OPERATOR []
	cout << endl;
	cout << "\n	                            APELARE OPERATOR [] ";
	cout << endl;

	cout << "\nValoarea elementului de pe pozitia dorita este: " << a2[2] << endl;



	//OPERATOR==
	cout << endl;
	cout << "\n	                            APELARE OPERATOR == ";
	cout << endl;

	if (a2 == a3)
		cout << "\nCELE 2 OBIECTE SUNT EGALE";
	else
		cout << "\nCEI 2 OBIECTE SUNT EGALE";
	cout << endl;



	//OPETAROR<
	cout << endl;
	cout << "\n	                            APELARE OPERATOR < ";
	cout << endl;

	if (a2 < a3)
		cout << "\nSALARIUL ANAGAJATULUI A3 ESTE MAI MARE DECAT SALARIUL ANGAJATULUI A2";
	else
		cout << "\nSALARIUL ANGAJATULUI A3 NU ESTE MAI MARE DECAT SALARIUL ANGAJATULUI A2";
	cout << endl;



	//OPERATOR+
	cout << endl;
	cout << "\n	                            APELARE OPERATOR + ";
	cout << endl;

	cout << "\nSALARIUL TOTAL AL ANGAJATIILOR A2 SI A3(A2+A3) ESTE :  " << a2.operator+(a3) << endl;


	// OPERATOR CAST
	cout << endl;
	cout << "\n	                            APELARE OPERATOR CAST EXPLICIT ";
	cout << endl;

	int salariu = int(a2);
	cout << "\nVALOAREA SALARIU  RETURNATA DE OPERATORUL CAST ESTE: " << salariu << endl;


	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;



	cout << endl;
	cout << "\n	                            TEST GETTERI + SETTERI	";
	cout << endl;


	cout << "\nCNP: " << a2.getCNP();

	cout << "\nNUME: " << a2.getNume();
	a2.setNume("Ion");
	cout << "\nNUME: " << a2.getNume();

	cout << "\nOCUPATIE: " << a2.getOcupatie();
	a2.setOcupatie("muncitor");
	cout << "\nOCUPATIE: " << a2.getOcupatie();

	cout << "\nSALARIU: " << a2.getSalariu();
	a2.setSalariu(3000);
	cout << "\nSALARIU: " << a2.getSalariu();

	cout << "\nNR SARCINI: " << a2.getnrSarcini();
	a2.setnrSarcini(10);
	cout << "\nNR SARCINI: " << a2.getnrSarcini();







	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR 1 PARAMETRU	";
	cout << endl;

	Factura f1(30);
	cout << f1;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR CU TOTI PARAMETRI	";
	cout << endl;

	int pretServiciu[3]{ 100,200,300 };
	Factura f2(30, "Pitesti", 1000, "ReparatieAuto", 3, pretServiciu);
	cout << f2;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR COPY ";
	cout << endl;

	Factura f3 = f2;
	cout << f3;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            APELARE OPERATOR =	";
	cout << endl;

	Factura f4(10);
	f4 = f3;
	cout << f4;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE OPERATOR >>	";
	cout << endl;

	Factura f5(11);
	cout << "\nDATI VALORI PENTRU f5: ";
	//cin >> f5;
	cout << f5;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE METODA 1	";
	cout << endl;

	f2.pachetComplet(pretServiciu, 3);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE METODA 2	";
	cout << endl;

	f2.sumaColectataTVA(100);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";



	//OPERATOR!
	cout << endl;
	cout << "\n	                            APELARE OPERATOR !	";
	cout << endl;

	if (f2.operator!() == 1)
		cout << "\nSUMA COLECTATA NU ESTE 0";
	else
		cout << "\nSUMA COLECTATA ESTE 0";
	cout << endl;


	//OPERATOR==
	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR ==	";
	cout << endl;

	if (f2 == f3)
		cout << "\nCele 2 obiecte sunt egale";
	else
		cout << "\nCele 2 obiecte nu sunt egale";
	cout << endl;



	//OPERATOR ++
	cout << endl;
	cout << "\n	                            APELARE OPERATOR ++	";
	cout << endl;

	cout << "\nVALOARE NR SERVICII INAINTE DE MODIFICARE(PREINCREMENTARE): " << f2.getNrServicii();
	cout << endl;
	f2.operator++();
	cout << "\nVALOAREA NR SERVICII DUPA MODIFICARE(PREINCREMENTARE): " << f2.getNrServicii();
	cout << endl;

	cout << "\nVALOARE NR SERVICII INAINTE DE MODIFICARE(POSTINCREMENTARE): " << f2.getNrServicii();
	cout << endl;
	f2.operator++(1);
	cout << "\nVALOAREA NR SERVICII DUPA MODIFICARE(POSTINCREMENTARE): " << f2.getNrServicii();
	cout << endl;



	//OPERATOR []
	cout << endl;
	cout << "\n	                            APELARE OPERATOR []	";
	cout << endl;

	cout << "\nValoarea elementului de pe pozitia dorita este: " << f2[2] << endl;    //*********************8



	//OPETAROR<
	cout << endl;
	cout << "\n	                            APELARE OPERATOR <	";
	cout << endl;

	if (f2 < f3)
		cout << "\nSUNT MAI MULTE SERVICII IN F3";
	else
		cout << "\nNU SUNT MAI MULTE SERVICII IN F3";
	cout << endl;



	//OPERATOR+
	cout << endl;
	cout << "\n	                            APELARE OPERATOR +	";
	cout << endl;

	cout << "\nSUMA COLECTATA f2+f3 ESTE: " << f2.operator+(f3) << endl;



	// OPERATOR CAST
	cout << endl;
	cout << "\n	                            APELARE OPERATOR CAST EXPLICIT ";
	cout << endl;

	int sumaColectata = int(f2);
	cout << "\nVALOAREA sumaColectata  RETURNATA DE OPERATORUL CAST ESTE: " << sumaColectata << endl;


	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;

	cout << endl;
	cout << "\n	                            TEST GETTERI + SETTERI	";
	cout << endl;



	cout << "\nAdresa: " << f2.getAdresa();
	f2.setAdresa("acolo");
	cout << "\nAlta Adresa: " << f2.getAdresa();

	cout << endl;

	cout << "\nSuma Colecatat: " << f2.getSumaColectata();
	f2.setSumaColectata(2000);
	cout << "\nSuma Colectata: " << f2.getSumaColectata();

	cout << endl;

	cout << "\nDenumire Serviciu: " << f2.getDenumireServicii();
	f2.setDenumireServicii("tunning");
	cout << "\nDenumire Serviciu: " << f2.getDenumireServicii();

	cout << endl;

	cout << "\nNumar Servicii: " << f2.getNrServicii();
	f2.setNrServicii(5);
	cout << "\nNumar Servicii: " << f2.getNrServicii();

	cout << endl;

	cout << "\nNr Ordine: " << f2.getnrOrdine();

	cout << endl;

	cout << "\nTVA: " << f2.getTVA();
	f2.setTVA(0.21);
	cout << "\nTVA: " << f2.getTVA();







	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR 1 PARAMETRU	";
	cout << endl;


	Programari p1("Luni");	//APELARE CONSTR 1 PARAM
	cout << p1;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR CU TOTI PARAMETRI	";
	cout << endl;

	int durataRezolvareProbleme[3] = { 1,2,3 };
	Programari p2("Marti", "Ionut", 3, durataRezolvareProbleme, true, 12);  //APELARE CONSTR TOTI PARAM
	cout << p2;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            METODA 1	";
	cout << endl;

	p2.rezolvareTotatala(3, durataRezolvareProbleme);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            METODA 2	";
	cout << endl;

	p2.timpProblema(3, durataRezolvareProbleme);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            APELARE COPY CONSTRUCTOR	";
	cout << endl;

	Programari p3 = p2;
	cout << p3;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            OPERATOR =	";
	cout << endl;

	Programari p4("Vineri");
	p4 = p3;//APELARE OPERATOR =
	cout << p4;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;


	cout << endl;
	cout << "\n	                            APELARE OPERATOR >>	";
	cout << endl;

	Programari p5("Miercuri");
	cout << "\nDATI VALORI PENTRU p5: ";
	//cin >> p5;
	cout << p5;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                         TEST   OPERATORI	";
	cout << endl;


	//OPERATOR !
	cout << endl;
	cout << "\n	                            OPERATOR !	";
	cout << endl;

	if (p2.operator!() == 1)
		cout << "\nAVEM REDUCERE";
	else
		cout << "\nNU AVEM REDUCERE";
	cout << endl;


	//OPERATOR==
	cout << endl;
	cout << "\n	                            OPERATOR ==	";
	cout << endl;

	if (p2 == p3)
		cout << "\nCELE 2 OBIECTE SUNT EGALE";
	else
		cout << "\nCELE 2 OBIECTE NU SUNT EGALE";
	cout << endl;


	//OPERATOR []
	cout << endl;
	cout << "\n	                            OPERATOR []	";
	cout << endl;

	cout << "\nValoarea elementului de pe pozitia dorita este: " << p2[2] << endl;


	//OPERATOR<
	cout << endl;
	cout << "\n	                            OPERATOR <	";
	cout << endl;

	if (p2 < p3)
		cout << "\nP3 ARE MAI MULTE PROBLEME DECAT P2";
	else
		cout << "\nP2 NU ARE MAI MULTE PROBLEME DECAT P3";


	//OPERATOR+
	cout << endl;
	cout << "\n	                            OPERATOR +	";
	cout << endl;
	p4 = p2 + 1;
	cout << "\n ADUNAREA PROBLEMELOR A 2 CLIENTI P2+P3" << p4 << endl;



	//OPERATOR ++
	cout << endl;
	cout << "\n	                            OPERATOR ++	";
	cout << endl;

	cout << "\nVALOARE ORA INAINTE DE MODIFICARE(PREINCREMENTARE): " << p2.getOra();
	cout << endl;
	p2.operator++();
	cout << "\nVALOARE ORA DUPA MODIFICARE(PREINCREMENTARE): " << p2.getOra();
	cout << endl;

	cout << "\nVALOARE ORA INAINTE DE MODIFICARE(POSTINCREMENTARE): " << p2.getOra();
	cout << endl;
	p2.operator++(1);
	cout << "\nVALOARE ORA DUPA MODIFICARE(POSTINCREMENTARE): " << p2.getOra();
	cout << endl;


	// OPERATOR CAST
	cout << endl;
	cout << "\n	                            APELARE OPERATOR CAST EXPLICIT ";
	cout << endl;

	int ora = int(p2);
	cout << "\nVALOAREA ORA RETURNATA DE OPERATORUL CAST ESTE: " << ora << endl;


	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl;

	cout << endl;
	cout << "\n	                            TEST GETTERI + SETTERI	";
	cout << endl;

	cout << "\nZIUA: " << p2.getZiua();
	p2.setZiua("SAMBATA");
	cout << "\nZIUA: " << p2.getZiua();

	cout << "\nNUME CLIENT: " << p2.getNumeClient();
	p2.setNumeClient("BOGDAN");
	cout << "\nNUME CLIENT: " << p2.getNumeClient();

	cout << "\nNR PROBLEME: " << p2.getNrProbleme();
	p2.setNrProbleme(4);
	cout << "\nNR PROBLEME: " << p2.getNrProbleme();

	cout << "\nREDUCERE: " << p2.getReducere();
	p2.setReducere(true);
	cout << "\nREDUCERE: " << p2.getReducere();

	cout << "\nORA: " << p2.getOra();
	p2.setOra(15);
	cout << "\nORA: " << p2.getOra();





	cout << "\nkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";




	ifstream inMasina;
	inMasina.open("MasinaIN.txt", ios::in);

	ofstream outMasina;
	outMasina.open("MasinaOUT.txt", ios::out);

	int pretAccidenTe[] = { 500,1000,1500 };
	int sasiuNumerIc[10] = { 1,1,1,1,1,1,1,1,1,1 };
	Masina m10("AUDI", 300, 5, 3, pretAccidenTe, sasiuNumerIc);
	outMasina << m10;

	int pretAccidenTee[] = {600,1200,1800};
	int sasiuNumerIcc[10] = { 2,1,1,1,1,1,1,1,1,1 };
	Masina m20("BMW", 300, 5, 3, pretAccidenTee, sasiuNumerIcc);
	outMasina << m20;

	int pretAccidenTeee[] = { 700,1400,2100 };
	int sasiuNumerIccc[10] = { 3,1,1,1,1,1,1,1,1,1 };
	Masina m50("CIELO", 300, 5, 3, pretAccidenTeee, sasiuNumerIccc);

	Masina m30;
	Masina m40;

	masinaSUV ms1(true, 3, "vw", 400, 2, 3, pretAccidenTe, sasiuNumerIc);
	cout << ms1;
	ms1.adaugaSoftStandard();
	ms1.masinaPericuloasa();

	masinaSUV mrezultat(true, 4, "vw", 500, 2, 3, pretAccidenTee, sasiuNumerIcc);
	masinaSUV ms3(true, 5, "vw", 600, 2, 3, pretAccidenTeee, sasiuNumerIccc);


	reparatieAuto* vectorPointeri[100] = { &ms1, &mrezultat, &ms3 };
	for (int i = 0; i < 3; i++)
	{
		vectorPointeri[i]->adaugaSoftStandard();

	}
	cout << "\nkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";

	inMasina >> m40;
	outMasina << m40;
	cout << "\nkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
	m20.raporMasina("RaportMasina.txt");

	inMasina.close();
	outMasina.close();
	Masina listaMasini[2] = { m10,m20 };

	Masina m60;
	cout << "\nkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
	inMasina.open("Masina.dat", ifstream::binary);
	if (inMasina.is_open()) {
		m60.citireBinar(inMasina);
		inMasina.close();
	}
	else { cout << "\nNU AI DESCHIS FISERU**********************************************************"; }


	outMasina.open("Masina.dat", ofstream::binary | ofstream::app);
	if (outMasina.is_open()) {
		m50.scrieBinar(outMasina);
		outMasina.close();
	}


	cout << "\nzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzk";

	





	ifstream inAngajat;
	inAngajat.open("AngajatIN.txt", ios::in);

	ofstream outAngajat;
	outAngajat.open("AngajatOUT.txt", ios::out);

	int cNP[13] = { 3,1,1,1,1,1,1,1,1,1,1,1,1 };
	Angajat a10("Andrei", "contabil", 2000, cNP, 5);
	outAngajat << a10;

	int cNPp[13] = { 5,1,1,1,1,1,1,1,1,1,1,1,1 };
	Angajat a20("Ionut", "programator", 2000, cNPp, 5);
	outAngajat << a20;
	
	int cNPpp[13] = { 7,1,1,1,1,1,1,1,1,1,1,1,1 };
	Angajat a50("Octavian", "pescar", 2000, cNPpp, 5);
	outAngajat << a50;

	Angajat a30();
	Angajat a40;
	inAngajat >> a40;
	outAngajat << a40;

	inAngajat.close();
	outAngajat.close();

	a10.raportAngajat("RaportAngajat.txt");

	Inginer("CONSTRUCTII", "Flavius", "Inginer", 6000, cNPp, 10);
	Angajat listaAngajati[2] = { a10,a20 };

	
	Angajat a60;
	inAngajat.open("Angajat.dat", ifstream::binary);
	if (inAngajat.is_open()) {
		a60.citireBinar(inAngajat);
		inAngajat.close();
	}

	else { cout << "\nNU AI DESCHIS FISERU**********************************************************"; }


	outAngajat.open("Angajat.dat", ofstream::binary | ofstream::app);
	if (outAngajat.is_open()) {
		a50.scrieBinar(outAngajat);
		outAngajat.close();
	}





	cout << "\nkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";




	ifstream inProgramare;
	inProgramare.open("ProgramareIN.txt", ios::in);

	ofstream outProgramare;
	outProgramare.open("ProgramareOUT.txt", ios::out);


	int durataRezolvareProbleMe[3] = { 1,2,3 };
	Programari p10("Marti", "Albert", 3, durataRezolvareProbleMe, true, 12);  //APELARE CONSTR TOTI PARAM
	outProgramare << p10;

	int durataRezolvareProbleMee[3] = { 3,3,3 };
	Programari p20("Joi", "Mihai", 3, durataRezolvareProbleMee, true, 12);  //APELARE CONSTR TOTI PARAM
	outProgramare << p20;

	
	int durataRezolvareProbleMeee[3] = { 7,7,7 };
	Programari p50("Duminica", "Cosmin", 3, durataRezolvareProbleMeee, true, 12);
	outProgramare << p50;

	Programari p30();
	Programari p40;
	inProgramare >> p40;
	outProgramare << p40;

	p10.raportProgramare("RaportProgramare.txt");

	Programari listaProgramari[2] = { p10,p20 };

	
	Programari p60;
	inProgramare.open("Angajat.dat", ifstream::binary);
	if (inProgramare.is_open()) {
		p60.citireBinar(inProgramare);
		inProgramare.close();
	}

	else { cout << "\nNU AI DESCHIS FISERU**********************************************************"; }


	outProgramare.open("Programare.dat", ofstream::binary | ofstream::app);
	if (outProgramare.is_open()) {
		p50.scrieBinar(outProgramare);
		outProgramare.close();
	}





	

	ifstream inFactura;
	inFactura.open("FacturaIN.txt", ios::in);

	ofstream outFactura;
	outFactura.open("FacturaOUT.txt", ios::out);

	int pretServicIu[3]{ 100,200,300 };
	Factura f10(30, "Pitesti", 1000, "ReparatieAuto", 3, pretServicIu);
	outFactura << f10;


	int pretServicIuu[3]{ 500,600,700 };
	Factura f20(30, "Bucuresti", 1000, "ReparatieAuto", 3, pretServicIuu);
	outFactura << f20;
	
	int pretServicIuuu[3] = { 700,800,900 };
	Factura  f50(40, "Ploiesti", 2000, "LaMititelu", 3, pretServicIuuu);
	outFactura << f50;


	Factura f30();
	Factura f40;
	inFactura >> f40;
	outFactura << f40;

	Factura listaFacturi[2] = { f10,f20 };

	
	Factura f60;
	inFactura.open("Factura.dat", ifstream::binary);
	if (inFactura.is_open()) {
		f60.citireBinar(inFactura);
		inFactura.close();
	}

	else { cout << "\nNU AI DESCHIS FISERU**********************************************************"; }
	cout << f60;


	outFactura.open("Factura.dat", ofstream::binary | ofstream::app);
	if (outFactura.is_open()) {
		f50.scrieBinar(outFactura);
		outFactura.close();
	}







	const char* numeService = { "MasinistulSRL" };
	int pretMasini[3] = { 100,200,300 };
	int oreDeschidere[7] = { 12,12,12,12,12,12,12 };
	ServiceAuto s1;

	ServiceAuto rezultat(2, 2, numeService, pretMasini, oreDeschidere, 1000, listaMasini, listaAngajati, listaFacturi, listaProgramari, 2, 2);
	cout << rezultat;
	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR TOTI PARAMETRI	";
	cout << endl;

	cout << rezultat;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE CONSTRUCTOR COPY	";
	cout << endl;

	ServiceAuto s3 = rezultat;
	cout << s3;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE OPERATOR=	";
	cout << endl;

	ServiceAuto s4(15);
	s4 = s3;//APELARE OPERATOR =
	cout << s4;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE METODA 1";
	cout << endl;

	rezultat.valoareVanzari(3, pretMasini);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            APELARE METODA 2	";
	cout << endl;

	rezultat.alocareAngatiperMasini(10, 3);
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";



	cout << endl;
	cout << "\n	                            APELARE OPERATOR >> ";
	cout << endl;

	ServiceAuto s5(20);
	cout << "\nDATI VALORI PENTRU S5:";
	//cin >> s5;
	cout << s5;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


	cout << endl;
	cout << "\n	                            TEST OPERATORI ";
	cout << endl;


	//OPERATOR !
	cout << endl;
	cout << "\n	                            APELARE OPERATOR !	";
	cout << endl;

	if (rezultat.operator!() == 1)
		cout << "\nAM OBTINUT PROFIT";
	else
		cout << "\nNU AM OBTINUT PROFIT";
	cout << endl;


	//OPERATOR==
	cout << endl;
	cout << "\n	                            APELARE OPERATOR ==	";
	cout << endl;

	if (rezultat == s3)
		cout << "\nCELE 2 OBIECTE SUNT EGALE";
	else
		cout << "\nCELE 2 OBIECTE NU SUNT EGALE";
	cout << endl;

	//OPERATOR []
	cout << endl;
	cout << "\n	                            APELARE OPERATOR []	";
	cout << endl;

	cout << "\nValoarea elementului de pe pozitia dorita este: " << rezultat[2] << endl;


	//OPERATOR>
	cout << endl;
	cout << "\n	                            APELARE OPERATOR > ";
	cout << endl;

	if (rezultat > s3)
		cout << "\nrezultat ARE MAI MULTE MASINI DECAT S3";
	else
		cout << "\nrezultat NU ARE MAI MULTE MASINI DECAT S3";





	//OPERATOR ++
	cout << endl;
	cout << "\n	                            APELARE OPRATOR++ ";
	cout << endl;

	cout << "\nVALOAREA NR ANGAJATI DUPA MODIFICARE(PREINCREMENTARE): " << rezultat.getnrAngajati();
	rezultat.operator++();
	cout << "\nVALOAREA NR ANGAJATI DUPA MODIFICARE(PREINCREMENTARE): " << rezultat.getnrAngajati();
	cout << endl;

	cout << "\nVALOARE NR ANGAJATI INAINTE DE MODIFICARE(POSTINCREMENTARE): " << rezultat.getnrAngajati();
	cout << endl;
	//ServiceAuto temp=rezultat++;
	
	cout << "\nVALOAREA NR ANGAJATI DUPA MODIFICARE(POSTINCREMENTARE): " << rezultat.getnrAngajati();
	cout << endl;


	//OPERATOR CAST
	cout << endl;
	cout << "\n	                            APELARE OPRATOR CAST EXPLICIT ";
	cout << endl;

	int profit = float(rezultat);
	cout << "\nPROFITUL RESTURNAT DE OPERATORU CAST ESTE: " << profit << endl;



	cout << endl;
	cout << "\n	                            TEST GETTERI+SETTERI";
	cout << endl;


	cout << endl;

	cout << "\nNr ANGAJATI: " << rezultat.getnrAngajati();
	rezultat.setnrAngajati(20);
	cout << "\nNr ANGAJATI: " << rezultat.getnrAngajati();

	cout << endl;

	cout << "\nNr MASINI: " << rezultat.getnrMasini();
	rezultat.setnrMasini(5);
	cout << "\nNr MASINI: " << rezultat.getnrMasini();

	cout << endl;

	cout << "\nNUME SERVICE: " << rezultat.getnumeService();
	rezultat.setNumeService("PYP");
	cout << "\nNUME SERVICE: " << rezultat.getnumeService();

	cout << endl;

	cout << "\nPROFIT: " << rezultat.getProfit();
	rezultat.setProfit(3000);
	cout << "\nPROFIT: " << rezultat.getProfit();


	OperareFisier opfisier;

	int pretAccidenteeee[3] = { 900,1800,2700 };
	int sasiuNumericccc[10] = { 3,1,1,1,1,1,1,1,1,1 };
	Masina m70("Porsche", 1000, 1, 3, pretAccidenteeee, sasiuNumericccc);

	ifstream finbin;

	finbin.open("fisierFinal.bin", ifstream::binary);
	if (finbin.is_open()) {
		opfisier.readFromFile(finbin, m70);
		finbin.close();

		bool startMeniuActivat = true;
		while (startMeniuActivat) {

			int optiune;

			Meniu::afisareMeniuPrincipal();

			cin >> optiune;

			switch (optiune) {

			case 0: {
				system("cls");
				cout << "Aplicatia a fost inchisa" << endl;
				break;
			}

			case 1: {
				system("cls");
				cout << m70;
				break;
			}

			case 2: {
				system("cls");
				cin >> m70;
				break;
			}

			case 3: {
				system("cls");

				ofstream foutbin1;

				foutbin1.open("fisierFinal.bin", ofstream::binary);

				if (foutbin1.is_open()) {
					opfisier.writeToFile(foutbin1, m70);
				}
				foutbin1.close();
				cout << "FisierSalvat" << endl;
				break;
			}

			default: {
				system("cls");
				cout << "Optiune invaida" << endl << endl;
				break;
			}

			}
		}
	}


	Angajat* pa = &a10;
	Inginer i10("cosntructii","Iancu","inginer",6000,cNPp,5);

	Inginer* pi = &i10;
	pa->salariuPotrivit();
	cout << endl;
	pi->salariuPotrivit();
	cout << endl;

	pa->volumMunca();
	cout << endl;
	pi->volumMunca();
	cout << endl; 

	ofstream afisari;
	afisari.open("AFISARI.txt", ios::in);
	d.raportAfisari(afisari);
	d.raportCitiri(afisari);




	vector <Angajat> vectorAngajati;
	vectorAngajati.push_back(a10);
	vectorAngajati.push_back(a20);
	vectorAngajati.push_back(a50);

	for (int i = 0; i < vectorAngajati.size(); i++)
		cout <<"\nAngajatul din vector cu nr-ul "<<i+1<<" este : "<< vectorAngajati[i];

	
	
	list <Masina> listaMasina;
	listaMasina.push_back(m10);
	listaMasina.push_front(m20);
	listaMasina.push_back(m50);
	listaMasina.pop_back();
	listaMasina.pop_front();

	

	list<Masina>::iterator it;
	for (it = listaMasina.begin(); it != listaMasina.end(); it++)
			cout <<"\nMasina din lisa este"<< * it;
	



	


	
	map< int, Angajat  > mapAngajat;
	mapAngajat.insert(pair<int, Angajat>(3, a50));
	mapAngajat.insert(pair<int, Angajat>(2, a20));
	mapAngajat.insert(pair<int, Angajat>(1, a10));
	

	map <int, Angajat>::iterator it1;
	for (it1 = mapAngajat.begin(); it1 != mapAngajat.end(); it1++) {
		cout << it1->first << "    ~~~~~~~    " << it1->second << endl;
			
	}



	
	/*set <Masina> setMasina;
	setMasina.insert(m10);
	setMasina.insert(m20);
	setMasina.insert(m50);



	set <Masina>::reverse_iterator it3;
	
	for (auto it3 = setMasina.begin(); it3 != setMasina.end(); it++)
		cout << *it3 << " ";*/

		
}
