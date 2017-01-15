#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator> 
#include <vector>
#include <map>
#include <algorithm>
#include <initializer_list>

#include <valarray>

#include <random>
#include <chrono>

/* Type-deklarasjoner */
using Tall = double;
using Tekst = std::string;

/* forover-deklarasjoner */
template<class T> struct Liste;
template<class K,class V> struct Tabell;
struct TallListe;
struct OrdListe;



//
// ILese, skrive data.
//
void si(){std::cout << '\n';}

template<class T, class... Ts> void si(T value, Ts... rest){
    std::cout << value << " ";
    si(rest...);
}

void les(){}

template<class T, class... Ts> void les(T& a, Ts&... rest){
    std::cin >> a;
    les(rest...);
}


//
// Boolske verdier
//
struct Bool {
    bool val;
    Bool(bool b) : val{b}{};
    operator bool() const {return val;}
    Bool operator&&(const Bool& other){return Bool(this->val && other.val);}
    Bool operator||(const Bool& other){return Bool(this->val || other.val);}
    Bool operator!(){return Bool(!this->val);}
};

std::ostream& operator<<(std::ostream & out, Bool b) {
    if (b) out << "ja";
    else out << "nei";
    return out;
}

const Bool ja = Bool(true);
const Bool nei = Bool(false);



//
// Tilfeldige tall
//

// Tilfeldig heltall mellom 1 og n
Tall tilfeldig(int n){
    return (rand() % n) +1;
}

// Tilfeldig double-verdi fra intervallet [a,b],
// Uniformt fordelt.
Tall tilfeldig(Tall a, Tall b){
    std::minstd_rand gen(rand());
    std::uniform_real_distribution<Tall>dist (a,b);
    return dist(gen);
}




//
// LISTER
//

// wrapper omkring std::vector
template<class T>
struct Liste {
    std::vector<T> vector;

    Liste()=default;
    Liste(std::initializer_list<T> lst) : vector{lst}{};
    Liste(int n) :vector(n) {
        for(int i = 0; i != n; i++) {
            T tmp;
            std::cout << "Skriv inn tall nr." << (i+1) << "av" << n <<":";
            std::cin >> tmp;
            vector[i] = tmp;
        }
    }
    T& operator[](int i){return vector[i];}
    T& operator[](Tall x){return vector[static_cast<int>(std::floor(x))];}
    T& operator()(Tall x){return vector[static_cast<int>(std::floor(x))];}

    std::size_t size() const {return vector.size();}
    std::size_t lengde() const {return size();}
    typename std::vector<T>::iterator begin() {return vector.begin();}
    typename std::vector<T>::iterator end() {return vector.end();}


    void leggTil(T elem){ vector.push_back(elem);}
    Liste<T> operator<<(T elem){
        this->leggTil(elem);
        return *this;
    }
   

    T fjern(){
        T elem = vector.back();
        vector.pop_back();
        return elem;
    }
    
    T trekkTilfeldig() const {
        return vector[tilfeldig(size())-1];
    }
    
    T fjernTilfeldig(){
        int index = (rand() % vector.size());
        T out = vector[index];
        vector[index] = vector.back();
        vector.pop_back();
        return out;
    }

    template<class Function> 
        auto brukMetode(Function f) -> Liste<decltype(f((*this)[0]))> {
        Liste<decltype(f((*this)[0]))> out;
        for(T x : *this)
            out.leggTil(f(x));

        return out;
    }

};


struct OrdListe : public Liste<Tekst> {
    OrdListe()=default;
    OrdListe(std::initializer_list<Tekst> lst) : Liste<Tekst>{lst}{};
    OrdListe(int n) :Liste<Tekst>(n) {};
};


struct TallListe : public Liste<Tall> {
    TallListe()=default;
    TallListe(std::initializer_list<Tall> lst) : Liste<Tall>{lst}{};
    TallListe(int n) :Liste<Tall>(n) {};

    Tall operator()(Tall x){
        if (x <= 0)
            return NAN;//vector.front();
        if (x >= size()-1)
            return NAN;//vector.back();

        int a = static_cast<int>(std::floor(x)); 
        Tall d = x-a; 
        return (d==0) ? vector[a] : (1-d)*vector[a]+d*vector[1+a];
    }
};

template<class T>
std::ostream& operator<<(std::ostream& out, Liste<T> lst){
    if (lst.size() == 0) out << "()";
    std::ostream_iterator<T> oit{out,", "};
    auto first = lst.begin();
    auto last = lst.end();

    out << "(";
    std::copy(first,last-1,oit);
    out << *(last-1) << ")";
    return out;
}

template<class T> std::istream& operator>>(std::istream& in, Liste<T>& lst){
        std::istream_iterator<T> eos;
        std::istream_iterator<T> iit{in};
        std::copy(iit,eos,std::back_inserter(lst.vector));
        return in;
    }

template<class T>
Liste<T> operator+(Liste<T> A,T newElem){
    A.vector.push_back(newElem);
    return A;
}

template<class T>
Liste<T> operator+(T newElem, Liste<T> A){
    A.vector.insert(begin(A.vector),newElem);
    return A;
}

Liste<Tall> operator+(Liste<Tall> A, int newElem){
    A.vector.push_back(Tall(newElem));
    return A;
}

Liste<Tall> operator+(int newElem, Liste<Tall> A){
    A.vector.insert(begin(A.vector),Tall(newElem));
    return A;
}

template<class T>
Liste<T> operator+(Liste<T> A, const Liste<T>& B){
    std::copy(begin(B.vector),end(B.vector),std::back_inserter(A.vector));
    return A;
}

template<class T>
void sorter(Liste<T>& lst){
    std::sort(lst.begin(),lst.end());
}


//
// Symboltabeller
//


// Wrapper omkring std::map
template<class Key, class Value>
struct Tabell {
    std::map<Key,Value> map{};

    Value& operator[](Key key){return map[key];}
    Value operator[](Key key) const {return map[key];}
    auto begin(){return map.begin();}
    auto end(){return map.end();}
};

template<class Key, class Value>
std::ostream& operator <<(std::ostream& out,Tabell<Key,Value>& tbl){

    out << "\n+---TABELL----------------" << std::endl;
    auto it = tbl.map.begin();
    auto end = tbl.map.end();

    while(it!=end){
        out << "| " << it->first << " -> " << it->second << std::endl;
        it++;
    }
    out << "+-------------------------" << std::endl;
    return out;
}

// Hente nøkler ut av symboltabell
template<class Key, class Value>
Liste<Key> nokler(const Tabell<Key,Value>& tbl){
    Liste<Key> ut;
    auto it = tbl.map.begin();
    auto end = tbl.map.end();
    while(it != end){
        ut.leggTil((it++)->first);
    }
    return ut;
}


//
// Lagring av data
//

// Lagre symboltabell som tekstfil
template<class Key, class Value>
void leggTilFil(const Tabell<Key,Value>& tbl, std::string fileName){
    std::ofstream out(fileName+".tabell");
    auto it = tbl.map.begin();
    auto end = tbl.map.end();
    while(it!=end){
        out << it->first << " " << it->second << std::endl;
        it++;
    }
}

// Lagre ordliste som tekstfil
void leggTilFil(const Liste<Tekst>& lst, std::string fileName){
    std::ofstream out(fileName+".liste");
    auto it = lst.vector.begin();
    auto begin = lst.vector.begin();
    auto end = lst.vector.end();
    if (it != end)
        out << *(it++);
    while(it!=end){
        out << std::endl << *(it++);
    }
}

// Lagre liste som tekstfil
template<class T>
void leggTilFil(const Liste<T>& lst, std::string fileName){
    std::ofstream out(fileName+".liste");
    std::ostream_iterator<T> oit(out,"\n");
    std::copy(lst.vector.begin(),lst.vector.end(),oit);
}

// Laste inn symboltabell fra fil
template<class Key>
void hentFraFil(Tabell<Key,Tekst>& tbl, std::string fileName){
    std::ifstream in (fileName+".tabell");
     
    Key newKey;
    in >> newKey;
    while(!in.eof() && newKey !=std::string{}){
        in >> std::ws; // remove whitespace
        std::getline(in,tbl[newKey]);
        in >> newKey;
    }
}

// Laste inn tabell fra fil
template<class Key, class Value>
void hentFraFil(Tabell<Key,Value>& tbl, std::string fileName){
    std::ifstream in (fileName+".tabell");
     
    Key newKey;
    in >> newKey;
    while(!in.eof() && newKey !=std::string{}){
        in >> tbl[newKey];
        in >> newKey;
    }
}

// Laste inn ordliste fra fil
void hentFraFil(Liste<Tekst>& lst, std::string fileName){
    std::ifstream in(fileName+".liste");
     
    while(!in.eof()){
        Tekst newElement;
        std::getline(in,newElement);
        if (newElement != std::string{})
            lst.leggTil(newElement);
    }
}

// Laste inn generisk liste fra fil
template<class T>
void hentFraFil(Liste<T>& lst, std::string fileName){
    std::ifstream in (fileName+".liste");
    auto it = std::istream_iterator<T>{in};
    auto end = std::istream_iterator<T>{};
    for(;it!=end; it++){
        lst.leggTil(*it);
    }
}



//
// Par
//
template<class A,class B>
struct Par {
    A hode;
    B hale;
    Par()=default;
    Par(A a, B b) : hode{a}, hale{b}{};
};

template<class A, class B>
std::ostream& operator<<(std::ostream& o, const Par<A,B>& par){
    o << par.hode << " : " << par.hale;
    return o;
}

template<class A, class B>
std::istream& operator>>(std::istream& in, Par<A,B>& par){
    char colon;
    in >> par.hode;
    in >> colon;
    if (colon != ':')
        in.putback(colon);
    in >> par.hale;
    return in;
}

template<class A, class B> bool operator==(Par<A,B> X, Par<A,B> Y){ return X.hode==Y.hode && X.hale == Y.hale;}
template<class A, class B> bool operator!=(Par<A,B> X, Par<A,B> Y){ return X.hode!=Y.hode || X.hale != Y.hale;}
template<class A, class B> bool operator<(Par<A,B> X, Par<A,B> Y){ return X.hode < Y.hode || (X.hode== Y.hode && X.hale < Y.hale);}
template<class A, class B> bool operator>(Par<A,B> X, Par<A,B> Y){ return X.hode > Y.hode || (X.hode == Y.hode && X.hale > Y.hale);}

// 
// Blokker: Sammensatte inhomogene datastrukturer
//
template<class A>
A lagBlokk(A a){
    return a;
}

template<class A,class B>
Par<A,B> lagBlokk(A a, B b) {
    return Par<A,B>(a,b);
}

template<class A,class B, class... Ts>
auto lagBlokk(A a, B b, Ts... params) -> Par<A,decltype(lagBlokk(b,params...))>
{
    return Par<A,decltype(lagBlokk(b,params...))>(a,lagBlokk(b,params...));
}

// 
// Konvertering mellom tabeller og lister av par
//

template<class Key, class Value>
Liste<Par<Key,Value>> liste(Tabell<Key,Value> tabell){
    Liste<Par<Key,Value>> out;
    for(Key k : nokler(tabell))
        out.leggTil(Par<Key,Value>(k,tabell[k]));
    return out;
}

template<class Key, class Value>
Tabell<Key,Value> tabell(Liste<Par<Key,Value>> lst){
    Tabell<Key,Value> out;
    for(Par<Key,Value> p : lst)
        out[p.hode] = p.hale;
    return out;
}

template<class A, class B>
Liste<Par<B,A>> vend(Liste<Par<A,B>> lst){
    Liste<Par<B,A>> out;
    for(auto par : lst){
        out.leggTil(Par<B,A>(par.hale,par.hode));
    }
    return out;
}

template<class A,class B>
Liste<Par<B,A>> vend(Tabell<A,B> tbl){
    return vend(liste(tbl));
}

template<class A, class B>
Par<Liste<A>,Liste<B>> splitt(Liste<Par<A,B>> lst){
    Liste<A> xs;
    Liste<B> ys;
    for(Par<Tall,Tall> par: lst){
        xs.leggTil(par.hode);
        ys.leggTil(par.hale);
    }
    return Par<Liste<A>,Liste<B>>(xs,ys);
}

template<class A, class B>
Liste<Par<A,B>> samle(Liste<A> lstA, Liste<B> lstB){
    std::size_t n = std::min(lstA.size(),lstB.size());
    Liste<Par<A,B>> out;
    for(int i = 0; i!=n ; i++)
        out.leggTil(Par<A,B>(lstA[i],lstB[i]));
    return out;
}

template<class A, class B>
Par<Liste<A>,Liste<B>> splitt(Tabell<A,B> tbl){
    Liste<A> xs;
    Liste<B> ys;
    for(A key: nokler(tbl)){
        xs.leggTil(key);
        ys.leggTil(tbl[key]);
    }
    return Par<Liste<A>,Liste<B>>(xs,ys);
}

//
// Tid
//

struct Klokke {

    std::chrono::steady_clock::time_point tNull;
    Klokke() : tNull{std::chrono::steady_clock::now()}{};
};

Tall tid(const Klokke& klokke){
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    std::chrono::duration<double> dt = std::chrono::duration_cast<std::chrono::duration<double>>(t-klokke.tNull);
    return std::floor(dt.count()*100)/100;
}

std::ostream& operator<<(std::ostream& out,const Klokke& klokke){
    out << tid(klokke) << " s";
    return out;
}

//
// Aritmetikk
//

Tall sum(Liste<Tall> lst){
    return accumulate(begin(lst.vector),end(lst.vector),0.0);
}

Tall produkt(Liste<Tall> lst){
    return accumulate(begin(lst.vector),end(lst.vector),1.0,[](Tall a, Tall b){return a*b;});
}


//
// Generering av tallLister
//
TallListe tallMellom(Tall a, Tall b,Tall step = 1.0){
    TallListe out;
    for(; a <= b ; a+=step)
        out.leggTil(a);
    return out;
}

TallListe lesInnTall(int n){
    TallListe out;
    Tall tmp;
    for(int i = 0; i < n; i++){
        std::cin >> tmp;
        out << tmp;
    }
    return out;
}

template<class T>
Liste<T> trekkUt(const Liste<T>& lst, Tall n){
    Liste<T> out;
    for (int i = 0; i < n ; i++){
       out.leggTil(lst.trekkTilfeldig());
    }
    return out;
}

template<class T>
Liste<T> utvalg(Liste<T> lst, Tall n){ // Call by copy
    TallListe out;
    while ( n-- > 0 &&  lst.lengde() > 0){
        out.leggTil(lst.fjernTilfeldig());
    }
    return out;
}

// 
// Konvertering til tekst
//
Tekst tilTekst(Liste<Tekst> lst){
    std::ostringstream oss;

    std::ostream_iterator<Tekst> oit{oss," "};
    auto first = begin(lst.vector);
    auto last = end(lst.vector);
    std::copy(first,last-1,oit);
    oss << *(last-1);
    return oss.str();
}

Tekst tilTekst(Tall x){
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

Tekst tilTekst(Liste<Tall> lst){
    std::ostringstream oss;
    if (lst.vector.size() == 0) oss << "()";
    
    std::ostream_iterator<Tall> oit{oss,", "};
    auto first = begin(lst.vector);
    auto last = end(lst.vector);

    oss << "(";
    std::copy(first,last-1,oit);
    oss << *(last-1) << ")";
    return oss.str();
}

//
// Makroer for kontrollstrukturer
//
#define slutt return 0;
#define gjenta(x,y) for(auto x : y)
#define repeter while(1)
#define bryt break
#define hvis(x) if(x)
#define ellers else
#define og &&
#define eller ||
#define ikke !
#define svar return
#define Metode auto
#define metode  [&]
#define lagre(tabell) leggTilFil(tabell,#tabell)
#define hent(tabell) hentFraFil(tabell,#tabell)

#define Magisk auto

#define Trio(a,b,c) Par<a,Par<b,c>>
#define ParListe(a,b) Liste<Par<a,b>>
#define TrioListe(a,b,c) Liste<Par<a,Par<b,c>>>
