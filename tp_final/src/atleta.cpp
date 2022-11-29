#include "../include/atleta.h"


Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {

    _nombre=n;

    _genero=g;

    _anioNacimiento=a;

    _nacionalidad=p;

    _ciaNumber=c;

    pair<Deporte, int> tenis50 = make_pair("Tenis",50);

    _deportes.push_back(tenis50);

}

string Atleta::nombre() const {

    return _nombre;

}

Genero Atleta::genero() const {

    return _genero;

}

int Atleta::anioNacimiento() const {

    return _anioNacimiento;

}

Pais Atleta::nacionalidad() const {

    return _nacionalidad;

}

int Atleta::ciaNumber() const {

    return _ciaNumber;

}

vector<Deporte> Atleta::deportes() const {

    vector<Deporte> deportesAtleta;

    unsigned int i=0;

    while(i<_deportes.size()){

        deportesAtleta.push_back(_deportes[i].first);

        i++;

    }

    return deportesAtleta;

}

int Atleta::capacidad(const Deporte &d) const {

    unsigned int i=0;

    unsigned int c=0;

    while(d!=_deportes[i].first){

        i++;

    }

    c=_deportes[i].second;

    return c;

}


Deporte Atleta::especialidad() const {

pair<Deporte, int> deporteYCapacidad=make_pair(_deportes[0].first,_deportes[0].second);

unsigned int i=1;

while(i<_deportes.size()){

    if(deporteYCapacidad.second<_deportes[i].second){

         deporteYCapacidad=_deportes[i];
    }

i++;
}

return deporteYCapacidad.first;
}


bool Atleta::deportePertenece(Deporte d) const {

    unsigned int i=0;

    while(i<_deportes.size() and d!=_deportes[i].first){

        i++;

    }

return i<_deportes.size();

}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {

    pair<Deporte, int> deporteNuevo=make_pair(d,c);

    vector<pair<Deporte, int> > deportesAtleta;

    unsigned int i=0;

    if(deportePertenece(d)==false){

        while(i<_deportes.size() and _deportes[i].first<d){

        deportesAtleta.push_back(_deportes[i]);

        i++;
        }

    deportesAtleta.push_back(deporteNuevo);

      while (i<_deportes.size()) {

        deportesAtleta.push_back(_deportes[i]);

        i++;
      }

    }

    else{

        while(i<_deportes.size() and d!=_deportes[i].first){

            deportesAtleta.push_back(_deportes[i]);

            i++;
        }

        deportesAtleta.push_back(deporteNuevo);


        i++;

        while(i <_deportes.size()){

            deportesAtleta.push_back(_deportes[i]);

            i++;
        }

    }

    _deportes=deportesAtleta;

}


void Atleta::mostrar(std::ostream &os) const {

	os << *this << std::endl;

}

void Atleta::guardar(std::ostream &os) const {

	os << *this << std::endl;

}

void Atleta::cargar(std::istream &is) {

	char caracter;
  	is >> caracter;

  	if (caracter != 'A') {

		cerr << "[ERROR] No se ha podido cargar Atleta" << endl;

		return;
	}

	is.ignore(2);
	is >> _nombre;
	is.ignore(3);
	istream &operator>>(istream &is, Genero &_genero);
	is.ignore(2);
	is >> _anioNacimiento;
	is.ignore(2);
	is >> _nacionalidad;
	is.ignore(2);
	is >> _ciaNumber;
	is.ignore(3);

	vector<pair<Deporte, int> > deporteYCapacidad;
	pair<Deporte, int> par;

	while (is >> caracter){

		string deporte;
		is >> deporte;
		is.ignore(2);
		string capacidad;
		is >> capacidad;
		is.ignore(5);

		par = make_pair(deporte, atoi(capacidad.c_str()));

		deporteYCapacidad.push_back(par);


	}

	_deportes = deporteYCapacidad;

}

std::ostream &operator<<(std::ostream &os, const Atleta &a) {

	os << "A |" << a.nombre() << "| |" << a.genero() << "| " << a.anioNacimiento() << " |" << a.nacionalidad() << "| " << a.ciaNumber() << " [" 	<< "(|" << a.deportes()[0] << "|, " << a.capacidad(a.deportes()[0]) << ")";

	unsigned int i = 1;

	while(i < a.deportes().size()){

		os << " , (|" << a.deportes()[i] << "|, " << a.capacidad(a.deportes()[i]) << ")";

		i++;

	}

	os << "]";


	return os;
}

std::istream &operator>>(std::istream &is, Atleta &a) {

    a.cargar(is);

    return is;
}

bool Atleta::operator==(const Atleta &a) const {

   unsigned int i = 0;

    bool mismosDatosPersonales;

    bool mismosDeportesYCapacidades = false;

    mismosDatosPersonales =(_nombre == a.nombre() and _genero == a.genero() and _anioNacimiento == a.anioNacimiento() and _nacionalidad == a.nacionalidad() and _ciaNumber == a.ciaNumber());

    if(_deportes.size() == a.deportes().size()){

        while (i < _deportes.size() and (_deportes[i].first == a.deportes()[i] and _deportes[i].second == a.capacidad(a.deportes()[i]))){

            i++;
        }

        mismosDeportesYCapacidades = (i == _deportes.size());

    }

    return (mismosDatosPersonales and mismosDeportesYCapacidades);

}

Atleta Atleta::operator=(const Atleta &a) {
    _anioNacimiento = a._anioNacimiento;
    _ciaNumber = a._ciaNumber;
    _nacionalidad = a._nacionalidad;
    _nombre = a._nombre;
    _genero = a._genero;
    _deportes = a._deportes;
    return (*this);
}
