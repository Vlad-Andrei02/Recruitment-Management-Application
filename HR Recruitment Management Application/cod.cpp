#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <limits>
#include <stdexcept>

using namespace std;

//Am ales să construiesc fluxul sub formă de aplicație care ajută echipa de HR a unei companii din domeniul IT să gestioneze procesul de recrutare al angajaților.
//Vom presupune că, după centralizarea CV-urilor, datele sunt introduse într-un fișier CSV; astfel, această clasă va citi datele din fișier pentru operații stabilite ulterior.

class CSV_DATE_CANDIDATI {
private:
    string fileName;
    vector<string> nume, prenume, nivel_studii, nr_telefon;
    vector<int> ani_experienta;

public:
    //metoda de citire din fisier
    void read() {
        ifstream file(fileName);

        if (!file.is_open()) {
            cerr << "Eroare la deschidere " << fileName << endl;
            exit(1);
        } 

        // Stergem datele din vectori in caz ca apelam functia de mai multe ori, iar datele se schimba
        nume.clear();
        prenume.clear();
        nivel_studii.clear();
        ani_experienta.clear();
        nr_telefon.clear();

        string line;
        getline(file, line); // Sarim peste antet

        while (getline(file, line)) {
            istringstream iss(line);
            string temp_nume, temp_prenume, temp_nivel_studii, temp_nr_telefon;
            int temp_ani_experienta;

            //extragem datele din fisier
            getline(iss, temp_nume, ';');
            getline(iss, temp_prenume, ';');
            getline(iss, temp_nivel_studii, ';');
            string temp_ani_experienta_str;
            getline(iss, temp_ani_experienta_str, ';');
            temp_ani_experienta = stoi(temp_ani_experienta_str);
            getline(iss, temp_nr_telefon);

            // Adaugam datele in vectori
            nume.push_back(temp_nume);
            prenume.push_back(temp_prenume);
            nivel_studii.push_back(temp_nivel_studii);
            ani_experienta.push_back(temp_ani_experienta);
            nr_telefon.push_back(temp_nr_telefon);
        }

        file.close(); //inchidem fisierul
    }

    //constructor
    CSV_DATE_CANDIDATI(string fileName) {
        this -> fileName = fileName;
    }

    //geteri
    vector<string> getNume(){
        return nume;
    }

    vector<string> getPrenume(){
        return prenume;
    }

    vector<string> getNivelStudii(){
        return nivel_studii;
    }

    vector<int> getAniExperienta(){
        return ani_experienta;
    }

    vector<string> getNrTelefon(){
        return nr_telefon;
    }
};

//clasa in care manipulam datele din fisierul unde trecem candidatii care au trecut de etapa preeliminara
class CSV_DATE_PRELIMINAR {
private:
    string fileName;
    vector<string> nume_preliminar, prenume_preliminar, nivel_studii_preliminar;
    vector<int> ani_experienta_preliminar;

public:
    //metoda de citire a datelor din fisierul in care vom trece candidatii care respecta baremul stabilit de utilizator(studii minime si ani de experienta minimi)
    void read() {
        ifstream file(fileName);

        if (!file.is_open()) {
            cerr << "Eroare la deschidere " << fileName << endl;
            exit(1);
        }

        // Stergem datele din vectori in caz ca functia va fi apelata de mai multe ori in cod
        nume_preliminar.clear();
        prenume_preliminar.clear();
        nivel_studii_preliminar.clear();
        ani_experienta_preliminar.clear();

        string line;
        getline(file, line); // Sarim peste antet

        while (getline(file, line)) {
            istringstream iss(line);
            string temp_nume, temp_prenume, temp_nivel_studii;
            int temp_ani_experienta;

            //extragem datele din fisier
            getline(iss, temp_nume, ';');
            getline(iss, temp_prenume, ';');
            getline(iss, temp_nivel_studii, ';');
            string temp_ani_experienta_str;
            getline(iss, temp_ani_experienta_str, ';');
            temp_ani_experienta = stoi(temp_ani_experienta_str);

            // Adaugam datele in vectori
            nume_preliminar.push_back(temp_nume);
            prenume_preliminar.push_back(temp_prenume);
            nivel_studii_preliminar.push_back(temp_nivel_studii);
            ani_experienta_preliminar.push_back(temp_ani_experienta);
        }

        file.close(); //inchidem fisierul
    }

    //metoda de scriere a datelor in fisier.Dupa ce gasim toti candidatii care indeplinesc baremul stabilit de utilizator, ii vom scrie in fisier in vederea programarii unui interview(pas ce va fi realizat ulterior)
    void scriere(vector<string> nume, vector<string> prenume, vector<string> nivel_studii, vector<int> ani_experienta) {
        ofstream file(fileName); // Aici deschidem un fișier nou pentru scriere

        if (!file.is_open()) {
            cerr << "Eroare la deschiderea fisierului de scriere" << endl;
            exit(1);
        } 

        // Scriem antetul în fișier
        file << "Nume;Prenume;Nivel_studii;Ani_experienta" << endl;

        // Scriem datele în fișier
        for (size_t i = 0; i < nume.size(); i++) {
            file << nume[i] << ";" << prenume[i] << ";" << nivel_studii[i] << ";" << ani_experienta[i] << endl;
        }

        file.close(); //inchidere fisier
    }
    
    //metoda de afisare a candidatilor
    void afisare_candidati() {
        read();

        int i;
        for (i = 0; i < nume_preliminar.size(); i++) {
        cout << "Nume: " << nume_preliminar[i] <<" , "<< "Prenume: " << prenume_preliminar[i] <<" , "<< "Nivel_studii: " << nivel_studii_preliminar[i] <<" , "<< "Ani_experienta: " << ani_experienta_preliminar[i] << endl;
        }
    }

    //metoda de cautare a candidatilor, o vom folosi atunci cand programa un interview(doar candidatii care au trecut baremul pot trece la interview)
    void cautare_candidat(string nume, string prenume) {
        read();
        
        int trecut = 0, i;
        for(i = 0; i < nume_preliminar.size(); i++) {
            if (nume_preliminar[i] == nume && prenume_preliminar[i] == prenume) {
                cout << "ANGAJATUL A TRECUT LA INTERVIEW" << endl;
                return;
            }
        }

        if (trecut == 0) {
            cout << "ANGAJATUL NU A TRECUT LA INTERVIEW" << endl;
        }

    }

    //constructor
    CSV_DATE_PRELIMINAR(string fileName) {
        
        this -> fileName = fileName;
    }

    //geteri
    vector<string> getNumePreliminar(){
        return nume_preliminar;
    }

    vector<string> getPreumePreliminar(){
        return prenume_preliminar;
    }

};

//clasa in care manipulam datele din fisierul unde trecem candidatii programati la interview si data/ora cand au interview
class CSV_DATE_INTERVIEW {
private:
    string fileName;
    vector<string> nume, prenume, data, ora;

public: 
    //citim date din fisier
    void read() {
        ifstream file(fileName);

        if (!file.is_open()) {
            cerr << "Eroare la deschidere " << fileName << endl;
            exit(1);
        }

        // Stergem datele din vectori in caz ca functia va fi apelata de mai multe ori in cod
        nume.clear();
        prenume.clear();
        data.clear();

        string line;
        getline(file, line); // Sarim peste antet

        while (getline(file, line)) {
            istringstream iss(line);
            string temp_nume, temp_prenume, temp_data, temp_ora;

            //extragem datele din fisier
            getline(iss, temp_nume, ';');
            getline(iss, temp_prenume, ';');
            getline(iss, temp_data, ';');
            getline(iss, temp_ora, ';');
            

            // Adaugam datele in vectori
            nume.push_back(temp_nume);
            prenume.push_back(temp_prenume);
            data.push_back(temp_data);
            ora.push_back(temp_ora);
        }

        file.close(); //inchidem fisierul
    }

    //metoda in care scriem in fisier
    void scriere(vector<string> nume_scris, vector<string> prenume_scris, vector<string> data_scrisa, vector<string> ora_scrisa) {
        ofstream file(fileName); // Aici deschidem un fișier nou pentru scriere

        if (!file.is_open()) {
            cerr << "Eroare la deschiderea fisierului de scriere" << endl;
            exit(1);
        } 

        // Scriem antetul în fișier
        file << "Nume;Prenume;Data;Ora" << endl;

        // Scriem datele în fișier
        for (size_t i = 0; i < nume.size(); i++) {
            file << nume_scris[i] << ";" << prenume_scris[i] << ";" << data_scrisa[i] << ";" << ora_scrisa[i] << endl;
        }

        file.close();
    }

    //metoda prin care adaugam o programare
    void adaugare_candidat(string nume_candidat_adaugat, string prenume_candidat_adaugat, string data_candidat_adaugat, string ora_candidat_adaugat) {  
    read();
    ofstream file(fileName, ios::app);

    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului de scriere" << endl;
        exit(1);
    }

    file.seekp(0, ios::end); // Setăm pointerul de scriere la sfârșitul fișierului

    if (file.tellp() == 0) {
        file << "Nume;Prenume;Data;Ora" << endl;
    }

    file << nume_candidat_adaugat << ";" << prenume_candidat_adaugat << ";" << data_candidat_adaugat << ";" << ora_candidat_adaugat << endl;
    file.close();  
    }

    //metoda prin care eliminam un candidat din lista(
    void eliminare_candidat(string nume_candidat_eliminat, string prenume_candidat_eliminat) {
        int gasit = 0;
        read();

        for (size_t i = 0; i < nume.size(); i++) {
            if(nume[i] == nume_candidat_eliminat && prenume[i] == prenume_candidat_eliminat ) {
                nume.erase(nume.begin() + i);
                prenume.erase(prenume.begin() + i);
                data.erase(data.begin() + i);
                ora.erase(ora.begin() + i);
                scriere(nume, prenume, data, ora);
                gasit = 1;
                return;
            }
        }

        if(gasit == 0) {
            cout << "Nu am gasit candidatul!" << endl;
        }    
    }

    //constructor
    CSV_DATE_INTERVIEW(string fileName) {
        
        this -> fileName = fileName;
    }

};

//Clas ce ne permite sa citim anuntul de angajare dintr-un document txt
class TXT_ANUNT {
private:
    string filename;

public:
    //metoda prin care citim date din fisier
    void read() {
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Eroare la deschidere " << filename << endl;
            exit(1);
        } else {
            cout << "Fisierul s-a deschis" << endl;
        }

        string line;
        while (getline(file, line)) {
            cout <<line <<endl;
        }

        file.close();

    }

    //constructor
    TXT_ANUNT(string filename) {
        this -> filename = filename;
    }
};

//clasa prin intermediul careia folosim functiile din flow, flow ul fiind facut sa-i ajute pe cei de a HR in procesul de angajare
class Angajator {
private:
    CSV_DATE_CANDIDATI fisier_date;
    TXT_ANUNT fisier_anunt;
    CSV_DATE_PRELIMINAR fisier_preliminar;
    CSV_DATE_INTERVIEW fisier_planificare;
    vector<string> nume, prenume, nivel_studii;
    vector<int> ani_experienta;

public:
    //constructor
    Angajator() : fisier_date("date_concurenti.csv"), fisier_anunt("anunt_angajare.txt"), fisier_preliminar("date_preliminar.csv"), fisier_planificare("date_interview.csv") {}

   //metoda prin care afisam anuntul de angajare
    void anunt_angajare() {
        fisier_anunt.read(); 
    }

    //metoda prin care selectam candidatii in functie de nivelul de pregatire minim pe care dorim sa l aiba si ii afisam
    void filtrare_automata(string nivel_studii_minim, int ani_experienta_minimi) {
        //citim din fisierul cu toti candidatii pentru a obtine datele pe care trebuie sa le filtram
        fisier_date.read();

        //atribuim vectorilor valorile din fisierul cu datele candidatilor
        nume = fisier_date.getNume();
        prenume = fisier_date.getPrenume();
        nivel_studii = fisier_date.getNivelStudii();
        ani_experienta = fisier_date.getAniExperienta();

        //vectori in care vom adauga datele ce vor fi scrise ulterior in fisierul cu candidati care respecta baremul
        vector<string> nume_preliminar, prenume_preliminar, nivel_studii_preliminar;
        vector<int> ani_experienta_preliminar;

        int i, j = 0;

        cout << "LISTA DE POTENTIALI CANDIDATI ESTE:" << endl; 

        //aici are loc filtrarea propriu-zisa, in functie de ce preferintele utilizatorului
        if (nivel_studii_minim == "STUDENT") {
            for(i = 0; i < nume.size(); i++) {
                if (ani_experienta[i] >= ani_experienta_minimi && (nivel_studii[i] == "STUDENT" || nivel_studii[i] == "LICENTA" || nivel_studii[i] == "MASTER" || nivel_studii[i] == "DOCTORAT")) {
                    nume_preliminar.push_back(nume[i]);
                    prenume_preliminar.push_back(prenume[i]);
                    nivel_studii_preliminar.push_back(nivel_studii[i]);
                    ani_experienta_preliminar.push_back(ani_experienta[i]);
                    j++;
                }
            }
        }

        else if (nivel_studii_minim == "LICENTA") {
            for(i = 0; i < nume.size(); i++) {
                if (ani_experienta[i] >= ani_experienta_minimi && (nivel_studii[i] == "LICENTA" || nivel_studii[i] == "MASTER" || nivel_studii[i] == "DOCTORAT")) {
                    nume_preliminar.push_back(nume[i]);
                    prenume_preliminar.push_back(prenume[i]);
                    nivel_studii_preliminar.push_back(nivel_studii[i]);
                    ani_experienta_preliminar.push_back(ani_experienta[i]);
                    j++;   
                }
            }
        }

        else if (nivel_studii_minim == "MASTER") {
            for(i = 0; i < nume.size(); i++) {
                if (ani_experienta[i] >= ani_experienta_minimi && (nivel_studii[i] == "MASTER" || nivel_studii[i] == "DOCTORAT")) {
                    nume_preliminar.push_back(nume[i]);
                    prenume_preliminar.push_back(prenume[i]);
                    nivel_studii_preliminar.push_back(nivel_studii[i]);
                    ani_experienta_preliminar.push_back(ani_experienta[i]);
                    j++;    
                }
            }
        }

        else if (nivel_studii_minim == "DOCTORAT") {
            for(i = 0; i < nume.size(); i++) {
                if (ani_experienta[i] >= ani_experienta_minimi && nivel_studii[i] == "DOCTORAT") {
                    nume_preliminar.push_back(nume[i]);
                    prenume_preliminar.push_back(prenume[i]);
                    nivel_studii_preliminar.push_back(nivel_studii[i]);
                    ani_experienta_preliminar.push_back(ani_experienta[i]);
                    j++;     
                }
            }
        }
        //scriem datele in fisier si le afisam
        fisier_preliminar.scriere(nume_preliminar, prenume_preliminar, nivel_studii_preliminar, ani_experienta_preliminar);
        fisier_preliminar.afisare_candidati();
         
    }

        //afisam candidatii care respecta baremul
        void afisare_candidati_preliminari() {
             fisier_preliminar.read();
        }

        //metoda de tip bool de carene vom folosi si pentru a programa interview uri(nu putem programa un interview pentru un candidat care n a trecut de filtrarea preeliminara)
        bool cautare_candidat(string nume, string prenume) {
            //citim din fisier
            fisier_preliminar.read();
            vector<string> nume_vector, prenume_vector;
            nume_vector = fisier_preliminar.getNumePreliminar();
            prenume_vector = fisier_preliminar.getPreumePreliminar();

            //verificam daca candidatul a trecut la interview, daca a trecut ulterior ii putem programa un interview
            for (size_t i = 0; i < nume_vector.size(); i++) {
                if (nume_vector[i] == nume && prenume_vector[i] == prenume) {
                    cout << "ANGAJATUL A TRECUT LA INTERVIEW" << endl;
                    return true;
                }
            }

            cout << "ANGAJATUL NU A TRECUT LA INTERVIEW" << endl;
            return false;
        }

        //metoda in care programam interviewuri pentru angajatii care au trecut de etapa preeliminara
        void programare_interview(string nume_candidat, string prenume_candidat, string data_interview, string ora_interview) {
            if (cautare_candidat(nume_candidat, prenume_candidat) == true) {
                fisier_planificare.adaugare_candidat(nume_candidat, prenume_candidat, data_interview, ora_interview);  
        }   
        }

        //metoda de eliminare a candidatului de la interview
        void eliminare_candidat(string nume_candidat_eliminat, string prenume_candidat_eliminat) { 
            fisier_planificare.eliminare_candidat(nume_candidat_eliminat, prenume_candidat_eliminat);
        }  
        
};

//clasa flow
class Flow_Date {
private:
    string titlu;
  
public:
    //constructor
    Flow_Date(string titlu) {
        this -> titlu = titlu;
    }

    //setter
    void set_titlu(string titlu_flow){
        titlu = titlu_flow;
    }
   //getter
    string get_titlu(){
        return titlu;
    }

    vector <int> steps; //vector in care adaugam numarul pasului pe care dorim sa-l executam(vom folosi acest vector intr-un switch in cadrul functiei de run_flow)
   
    int numar_start = 0 ;
    int erori_step1 = 0, erori_step2 = 0, erori_step3 = 0, erori_step4 = 0, erori_step5 = 0, erori_step6 = 0, erori_total = 0;
};


//clasa in care implementam actiunile din flow
class Actiuni_Flows{
private:
    Angajator racolare;
    vector <Flow_Date> vector_Flows; //vector de flowuri
    int i = 0; //numarul de flowuri pe care il avem
public:
    //metoda de afisare a flowurilor
    void afisare_flows(){
        cout<<"\nToate flows disponibile:\n";
        for(Flow_Date flow : vector_Flows){
            cout<< flow.get_titlu() << "\n";
        }
        cout<<"\n";
    }

    //metoda de creare a unui flow
    void creare_flow() {
    string nume_flow = "Flow_" + to_string(i + 1); //nume setat de baza, il putem schimba daca dorim
    Flow_Date flow_nou(nume_flow);
    i++; //creste numarul de flowuri

    int alegere;
    
    //adaugam pasi in flow
    while (1) {
        cout << "\n--Alegeti tipul de STEP pe care doriti sa-l adaugati--\n";
        cout << "1.DISPLAY step (afiseaza anuntul de angajare)\n";
        cout << "2.FILTER step (filtrare automata si afisarea candidatilor care indeplinesc baremul)\n";
        cout << "3.SEARCH step (cautare candidat)\n";
        cout << "4.TEXT INPUT step (programare interview)\n";
        cout << "5.MODIFY step (Eliminare candidat din lista de interview)\n";
        cout << "6.TITLE step (schimbati titlul flowului)\n";
        cout << "7.END step (finalul flow-ului)\n\n";

        //bloc try care gestioneaza situatiile in care utilizatorul adauga date gresite
        try {
            cin >> alegere;

            switch (alegere) {
            case 1:
                flow_nou.steps.push_back(1);
                break;
            case 2:
                flow_nou.steps.push_back(2);
                break;
            case 3:
                flow_nou.steps.push_back(3);
                break;
            case 4:
                flow_nou.steps.push_back(4);
                break;
            case 5:
                flow_nou.steps.push_back(5);
                break;
            case 6:
                flow_nou.steps.push_back(6);
                break;
            
            case 7:
                flow_nou.steps.push_back(7);
                break;

            default:
                throw invalid_argument("Optiune invalida! Alege un numar de la 1 la 7");
            }

            if (alegere == 7)
                break;
        } catch (const invalid_argument& e) {
            cout << "Eroare: " << e.what() << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    vector_Flows.push_back(flow_nou);
}
    //metoda de stergere a unui flow
    void sterge_flow(){
        cout<<"numele flow-ului pe care vrei sa-l stergi:\n";
        string titlu_flow;
        cin >> titlu_flow;
        int ok = 0, index;

        auto it = find_if(vector_Flows.begin(), vector_Flows.end(), [&](Flow_Date flow){
            return flow.get_titlu() == titlu_flow;
        });

        if (it != vector_Flows.end()){
            ok = 1;
            vector_Flows.erase(it);
            cout << "Flow-ul a fost sters.\n";
        }

        if (ok == 0){
            cout << "Flow-ul nu exista.\n";
        }
    }

    //metoda prin care vedem numarul de erori la fiecare pas, numarul total de erori si de cate ori am rulat flow ul
    void analitics_flow(){
        string titlu_flow;
        int ok = 0;

        cout<<"Numele flow-ului pentru care vreti sa afisati analitics.\n";
        cin >> titlu_flow;

        for(Flow_Date flow : vector_Flows) {
            if( flow.get_titlu() == titlu_flow) {
                ok = 1;
                
                cout << "Flow-ul a fost rulat de " <<flow.numar_start<<" ori\n";
                cout << "\n--Erori afisate pentru fiecare step--\n";
                cout << "Erori Step 1:" << flow.erori_step1 << endl;
                cout << "Erori Step 2:" << flow.erori_step2 << endl;
                cout << "Erori Step 3:" << flow.erori_step3 << endl;
                cout << "Erori Step 4:" << flow.erori_step4 << endl;
                cout << "Erori Step 5:" << flow.erori_step5 << endl;
                cout << "Erori Step 6:" << flow.erori_step6 << endl;
                cout << "Numarul total de erori este:" << flow.erori_total << endl;
            }
        }

        if(ok == 0) {
            cout << "Nu s-a gasit flow-ul cu numele specificat.\n";
        }
    }


    //metoda prin care executam un flw
    void run_flow() {
    string nume;
    int ok = 0; //verificam daca exista flow ul

    cout << "Numele flow-ului caruia vreti sa-i dati run:\n";
    cin >> nume;

    //verificam daca flow ul exista, si daca da atunci il executam, altfem avem mesaj in care ni se spune ca nu s-a gasit flow ul specificat
    for (Flow_Date& flow : vector_Flows) {
        if (flow.get_titlu() == nume) {
            ok = 1; //daca exista flow ul ok devine 1
            flow.numar_start++;

            for (int i = 0; i < flow.steps.size(); ++i) {
                cout << "Pasul numarul " << i + 1 << endl;

                int alegere_step;

                switch (flow.steps[i]) {
                    case 1: {
                        cout << "Afiseaza anuntul de angajare. Press 1 to skip, press 2 to proceed\n";

                        //introducem o alegere pana cand este corecta, putem continua pasul sau putem sari peste el
                        while (true) {
                            cout << "Introduceti alegerea pentru acest step: ";
                            cin >> alegere_step;

                            if (alegere_step == 1 || alegere_step == 2) {
                                break;
                            } else {
                                flow.erori_step1++;
                                flow.erori_total++;
                                cout << "Optiune invalida! Alege un numar de la 1 la 2\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }

                        //daca am ales sa continuam, executam pasul, altfel sarim peste el
                        if (alegere_step == 2) {
                            racolare.anunt_angajare();
                        }
                        break;
                    }

                    case 2: {
                        cout << "Afisarea candidatilor care indeplinesc baremul. Press 1 to skip, press 2 to proceed\n";

                        //introducem o alegere pana cand este corecta, putem continua pasul sau putem sari peste el
                        while (true) {
                            cout << "Introduceti alegerea pentru acest step: ";
                            cin >> alegere_step;

                            if (alegere_step == 1 || alegere_step == 2) {
                                break;
                            } else {
                                flow.erori_step2++;
                                flow.erori_total++;
                                cout << "Optiune invalida! Alege un numar de la 1 la 2\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }

                        //daca am ales sa continuam, executam pasul, altfel sarim peste el
                        if (alegere_step == 2) {
                            string nivel_studii_minim;
                            int ani_experienta_minimi;

                            //ne asiguram ca utilizatorul introduce un tip de date corect la ani_experienta_minimi, in cadrul functiei filtrare_automata vom verifica daca numarul este mai mare ca 0
                            while (true) {
                                try {
                                    cout << "Introduceti nivelul minim de studii: ";
                                    cin >> nivel_studii_minim;

                                    cout << "Introduceti ani de experienta minimi: ";
                                    cin >> ani_experienta_minimi;

                                    if (cin.fail() || ani_experienta_minimi < 0 || (nivel_studii_minim != "DOCTORAT" && nivel_studii_minim != "MASTER" && nivel_studii_minim != "LICENTA" && nivel_studii_minim != "STUDENT")) {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        throw 10;
                                    } else {
                                        break;
                                    }
                                }catch (int x) {
                                    flow.erori_step2++;
                                    flow.erori_total++;
                                    cout << "Datele sunt introduse gresit! Introdu un numar natural mai mare ca 0 si un nivel de studii recunoscut, te rog!\n";
                                }
                            }
                            racolare.filtrare_automata(nivel_studii_minim, ani_experienta_minimi);
                        }

                        break;
                    }

                    case 3: {
                        cout << "Cautare candidat. Press 1 to skip, press 2 to proceed\n";
                        
                        //introducem o alegere pana cand este corecta, putem continua pasul sau putem sari peste el
                        while (true) {
                            cout << "Introduceti alegerea pentru acest step: ";
                            cin >> alegere_step;

                            if (alegere_step == 1 || alegere_step == 2) {
                                break;
                            } else {
                                flow.erori_step3++;
                                flow.erori_total++;
                                cout << "Optiune invalida! Alege un numar de la 1 la 2\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                        
                        //daca am ales sa continuam, executam pasul, altfel sarim peste el
                        if (alegere_step == 2) {
                            string nume, prenume;

                            cout << "Introduceti numele candidatului: ";
                            cin >> nume;
                            cout << "Introduceti prenumele candidatului: ";
                            cin >> prenume;

                            racolare.cautare_candidat(nume, prenume);
                        }
                        break;
                    }

                    case 4: {
                        cout << "Programare interview. Press 1 to skip, press 2 to proceed\n";

                        //introducem o alegere pana cand este corecta, putem continua pasul sau putem sari peste el
                        while (true) {
                            cout << "Introduceti alegerea pentru acest step: ";
                            cin >> alegere_step;

                            if (alegere_step == 1 || alegere_step == 2) {
                                break;
                            } else {
                                flow.erori_step4++;
                                flow.erori_total++;
                                cout << "Optiune invalida! Alege un numar de la 1 la 2\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }

                        //daca am ales sa continuam, executam pasul, altfel sarim peste el
                        if (alegere_step == 2) {
                            string nume_candidat, prenume_candidat, data_interview, ora_interview;

                            cout << "Introduceti numele candidatului: ";
                            cin >> nume_candidat;
                            cout << "Introduceti prenumele candidatului: ";
                            cin >> prenume_candidat;
                            cout << "Introduceti data interviului: ";
                            cin >> data_interview;
                            cout << "Introduceti ora interviului: ";
                            cin >> ora_interview;

                            racolare.programare_interview(nume_candidat, prenume_candidat, data_interview, ora_interview);
                        }
                        break;
                    }

                    case 5: {
                        cout << "Eliminare candidat. Press 1 to skip, press 2 to proceed\n";

                        //introducem o alegere pana cand este corecta, putem continua pasul sau putem sari peste el
                        while (true) {
                            cout << "Introduceti alegerea pentru acest step: ";
                            cin >> alegere_step;

                            if (alegere_step == 1 || alegere_step == 2) {
                                break;
                            } else {
                                flow.erori_step5++;
                                flow.erori_total++;
                                cout << "Optiune invalida! Alege un numar de la 1 la 2\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }

                        //daca am ales sa continuam, executam pasul, altfel sarim peste el
                        if (alegere_step == 2) {
                            string nume_candidat_eliminat, prenume_candidat_eliminat;
                            cout << "Introduceti numele candidatului de eliminat: ";
                            cin >> nume_candidat_eliminat;
                            cout << "Introduceti prenumele candidatului de eliminat: ";
                            cin >> prenume_candidat_eliminat;
                            racolare.eliminare_candidat(nume_candidat_eliminat, prenume_candidat_eliminat);
                        }
                        break;
                    }

                    case 6: {
                        cout<<"Step TITLE. Press 1 to skip, press 2 to proceed\n";

                        //introducem o alegere pana cand este corecta, putem continua pasul sau putem sari peste el
                        while (true){
                            cout << "Introduceti alegerea pentru step TITLE: ";
                            cin >> alegere_step;

                            if (alegere_step == 1 || alegere_step == 2) {
                                break;
                            } else {
                                flow.erori_step6++;
                                flow.erori_total++;
                                cout << "Optiune invalida! Alege un numar de la 1 la 2\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                            //daca am ales sa continuam, executam pasul, altfel sarim peste el
                            if(alegere_step == 2) {
                
                                cout<<"titlu:\n";
                                string titlu_nou;
                                cin >> titlu_nou;
                            
                                flow.set_titlu(titlu_nou);
                            }
                                break;
                    }   

                    case 7: {
                        cout << "Step END. Sfarsitul flow-ului.\n";
                        break;
                        // semnaleaza sfarsitul unui flow
                    }
                }
            }

        }
    }
            if (ok == 0) {
                cout << "Nu s-a gasit flow-ul cu numele specificat.\n";
            }
}
};

//clasa meniu in care implementam meniul principal
class Meniu {
public:
    Meniu(Actiuni_Flows obiect) {
        int alegere;

        while (1) {
            //optiunile utilizatorului
            cout << "\nCu ce va putem ajuta?\n";
            cout << "1.Creare flow now\n";
            cout << "2.Run la flow existent\n";
            cout << "3.Sterge un flow din sistem\n";
            cout << "4.Analitics pentru un flow existent\n";
            cout << "5.Afisare flows\n";
            cout << "6.Incheiere program\n\n";

            //bloc try in care manageriem erorile in cazul in care utilizatorul introduce date gresite de la tastatura
            try {
                cin >> alegere;

                switch (alegere) {
                    case 1:
                        obiect.creare_flow();
                        break;
                    case 2:
                        obiect.afisare_flows();
                        obiect.run_flow();
                        break;
                    case 3:
                        obiect.afisare_flows();
                        obiect.sterge_flow();
                        break;
                    case 4:
                        obiect.afisare_flows();
                        obiect.analitics_flow();
                        break;
                    case 5:
                        obiect.afisare_flows();
                        break;
                    case 6:
                        break;  // Exit the loop for option 6
                    default:
                        throw invalid_argument("Optiune invalida! Alege un numar de la 1 la 6");
                }
            } catch (const std::exception& e) {
                cout << "Eroare: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (alegere == 6) {
                break;
            }
        }
    }
};

int main() {

    Actiuni_Flows actiuni_flows;
    Meniu meniu(actiuni_flows);

    return 0;
}
