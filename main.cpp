
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
   
    /////////////////////////////////////////////////////////////////////////
    
    
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
   

   

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Soldat {
private:
    int hp = 100, damage = 10, armour = 5;

public:
    ~Soldat() = default;
    Soldat(int hp, int damage, int armour) {
        this->hp = hp;
        this->damage = damage;
        this->armour = armour;
    }
    Soldat(int damage, int armour) {
        this->armour = armour;
        this->damage = damage;
    }
    //Soldat(int armour) { this->armour = armour; }
    Soldat() {}

    int getDEF() const { return armour; }
    int getDMG() const { return damage; }
    int getHP() const { return hp; }
    void setHP(int hp) { this->hp = hp; }
    void setDEF(int armour) { this->armour = armour; }
    void setDMG(int damage) { this->damage = damage; }

    void Copiere_Soldat(Soldat& soldat1, Soldat const& soldat2) {
        soldat1.hp = soldat2.hp;
        soldat1.damage = soldat2.damage;
        soldat1.armour = soldat2.armour;
    }

    void Afisare_soldat() {
        cout << "HP: " << this->hp << "; DMG: " << this->damage
            << "; DEF: " << this->armour << endl;
    }
    Soldat operator=(Soldat const& x) {

        this->hp = x.hp;
        this->damage = x.damage;
        this->armour = x.armour;
        return Soldat();
    }

    friend std::istream& operator>>(std::istream& input, Soldat& x) {
        cout << "Dati stats-urile Soldatului \nHP  DMG  DEF" << endl;
        input >> x.hp >> x.damage >> x.armour;
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const Soldat& x) {
        output << "HP: " << x.hp << "; DMG: " << x.damage << "; DEF: " << x.armour
            << endl;
        return output;
    }

    Soldat operator+(Soldat const& x) {
        Soldat rez;
        rez.hp = x.hp + this->hp;
        rez.damage = x.damage + this->damage;
        rez.armour = x.armour + this->armour;
        return rez;
    }
    friend bool operator>(Soldat const& x, Soldat const& y);
};

bool operator>(Soldat const& x, Soldat const& y) {
    double round1, round2;
    round1 = x.getHP() * x.getDEF() / y.getDMG();
    round2 = y.getHP() * y.getDEF() / x.getDMG();
    if (round1 > round2) {
        return 1;
    }
    return 0;
}

class General {
private:
    string nume_party;
    Soldat id;
    Soldat party_stats;
    int party_size = 0;

public:
    friend std::istream& operator>>(std::istream& input, General& x) {
        int aux;
        string str;
        char kase;
        cout << "Cum vreti sa se numeasca party-ul generalului?\n";
        input >> str;
        x.setName(str);
        cout << "Dati stats-urile Generalului: " << endl << "HP= ";
        input >> aux;
        x.id.setHP(aux);
        cout << "\nDMG= ";
        input >> aux;
        x.id.setDMG(aux);
        cout << "\nDEF= ";
        input >> aux;
        x.id.setDEF(aux);
        cout << "\nDati cati soldati vreti sa conduca generalul: ";
        input >> x.party_size;
        cout << "\nDoriti ca soldatii sa aiba statistici default sau nu? (y/n)\n";
        input >> kase;
        if (tolower(kase) == 'n') {
            input >> x.party_stats;
            cout << "Soldatii generalului sunt acum de forma: " << x.party_stats;
            return input;
        }

        if (tolower(kase) != 'y') {
            cout << "Nu ati introdus corect caracterul. Soldatii vor fi initializati "
                "cu statisticile default\n";
        }
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, General& x) {
        output << "\n\n-------------\n\n"
            << "Nume party: " << x.nume_party << endl;
        output << "Stats-uri Generalului: " << endl;
        output << x.id << endl;
        output << "\nParty-ul " << x.nume_party << " are " << x.party_size << " soldati de forma " << x.party_stats << '\n';
        return output;
    }
    int getPS() { return party_size; }
    string getNume() { return nume_party; }
    Soldat getSoldat() { return party_stats; }
    void setSoldat(Soldat soldat, int i) { party_stats = soldat; }
    Soldat getID() const { return id; }
    void setName(const string& nume)
    {
        this->nume_party = nume; // Assuming nume_party is a member variable of type std::string

        for (char& c : this->nume_party)
        {
            c = toupper(c);
        }
    }
    Soldat statistici_party() const {
        Soldat aux;
        aux.setHP(this->party_stats.getHP() * party_size);
        aux.setDMG(this->party_stats.getDMG() * party_size);
        aux.setDEF(this->party_stats.getDEF() * party_size);
        return aux;
    }
    General(string const nume_party, Soldat id, Soldat party_stats, int party_size) {
        this->nume_party = nume_party;
        this->id = id;
        this->party_stats = party_stats;
        this->party_size = party_size;
    }
    General() {}
    ~General() = default;
};
bool operator>(General const& x, General const& y) {
    if (x.statistici_party() + x.getID() > y.statistici_party() + y.getID())
        return true;
    else
        return false;
}

class Comandant {
private:
    vector<General> squad_member;
    string squad_Name;
    int squad_size = 0;

public:
    ~Comandant() = default;
    friend std::istream& operator>>(std::istream& input, Comandant& x)
    {

        cout << "Cum vreti sa se numeasca armata?\n";
        cin >> x.squad_Name;
        cout << "Dati cate party-uri vreti sa aiba armata?\n";
        input >> x.squad_size;
        for (int i = 0; i < x.squad_size; i++) {
            General aux;
            input >> aux;
            x.squad_member.push_back(aux);
            if (i + 1 != x.squad_size)
                cout << "Party-ul " << i + 1
                << " a fost memorat.\nAcum pentru urmatorul party.\n";
        }
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, Comandant& x)
    {
        output << "Armata " << x.squad_Name << " are " << x.squad_size << " party-uri ";
        for (int i = 0; i < x.squad_size; i++)
        {
            cout << " partr-ul " << i + 1 << " este urmatorul: ";
            cout << x.squad_member[i];
        }
        return output;
    }
    int getSize() const { return this->squad_size; }
    string getName() const { return this->squad_Name; }
    General getMember(int i) const { return this->squad_member[i]; }
    void add(General member) { this->squad_member.push_back(member); }
    void add(General member, string X) { this->squad_member.push_back(member); this->squad_member[this->squad_member.size() - 1].setName(X); }
    void Absorb(Comandant const& x)
    {
        bool contor;
        string aux;
        for (int i = 0; i < x.squad_size; i++)
        {
            contor = 0;
            for (int j = 0; j < this->squad_size; j++)
            {
                if (this->squad_member[j].getNume().compare(0, x.getMember(i).getNume().size(), x.getMember(i).getNume(), 0, x.getMember(i).getNume().size()) == 0)
                {
                    contor=true;

                    aux = this->squad_member[j].getNume();

                    if (aux[aux.size() - 1] == ')')
                    {
                        stringstream P;
                        P << aux[aux.size() - 2];
                        int y;
                        P>>y;
                        y++;
                        aux.erase(aux.size() - 1);
                        aux.erase(aux.size() - 1);
                        aux += (char(y + 48)); 
                        aux += ')';
                    }
                    else
                        aux = aux + "(2)"; 

                }
                if (!contor)
                {
                    aux = x.getMember(i).getNume(); 
                }
            }
            this->squad_size++;
            this->add(x.squad_member[i], aux);
            aux.clear();
        }

    }
};
bool operator>(Comandant const& x, Comandant const& y) {
    int a, b;
    a = b = 0;
    for (int i = 0; i < x.getSize(); i++) {
        if (x.getMember(i) > y.getMember(i)) {
            a++;
        }
        else if (y.getMember(i) > x.getMember(i)) {
            b++;
        }
    }
    if (a > b) {
        return true;
    }
    return false;
}

// citirea si afisarea a N armate.
void massive_input(int n)
{
    vector <Comandant> v;
    Comandant aux;
    for (int i = 0; i < n; i++)
    {
        cout << '\n';
        cin >> aux;
        v.push_back(aux);
    }
    for (int i = 0; i < n; i++)
        cout << v[i] << '\n';
}



void start(Comandant& X, Comandant& Y) {
    cout << "Programul acesta poate sa primeasca 2 armate si sa estimeze care "
        "dintre cele 2 armate ar putea castiga intr-o lupta iar la final armata castigatoare va absorbi cealalta armata\n";
    cout << "Cele 2 armate vor fi introduse de la tastatura, iar apoi se vor "
        "afisa pe ecran\n";
    cout << "Acestea sunt formate din numele armatei si o multime de generalti; "
        "acesti generali sunt reprezentantii, la randul lor de un party de "
        "soldati.\n\n\n\n\n\n";
    cin >> X;
    cout << X;
    cout << "\n\nAcum pentru a doua armata\n\n";
    cin >> Y;
    cout << Y;
}

int main() {
    Comandant X, Y;
    start(X, Y);
    if (X > Y)
    {
        X.Absorb(Y); cout <<"Armata castigatoare este"<<X.getName()<<"\n\n\n" << X;
    }
    else { Y.Absorb(X); cout << "Armata castigatoare este" << Y.getName() << "\n\n\n" << Y; }

    return 0;
}

