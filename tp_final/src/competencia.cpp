#include "../include/competencia.h"


Competencia::Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as) {

    _categoria = make_pair(d, g);  

    _participantes = as;

    _finalizada = false;

}

Categoria Competencia::categoria() const {

    return _categoria;
}

vector<Atleta> Competencia::participantes() const {

    return _participantes;
}

bool Competencia::finalizada() const {

    return _finalizada;
}

vector<Atleta> Competencia::ranking() const {

    return _ranking;
}

vector<Atleta> Competencia::lesTocoControlAntiDoping() const {

    unsigned int j = 0;

    vector<Atleta> lesTocoControl;

    while(j < _lesTocoControlAntiDoping.size()){

        lesTocoControl.push_back(_lesTocoControlAntiDoping[j].first);

        j++;

    }

    return lesTocoControl;

}

bool Competencia::leDioPositivo(const Atleta &a) const {

    unsigned int i = 0;

    while(i < _lesTocoControlAntiDoping.size() && not((lesTocoControlAntiDoping()[i]).operator==(a))) {

        i++;

    }

    return _lesTocoControlAntiDoping[i].second;
}

void Competencia::finalizar(const vector<int> &posiciones, const vector<pair<int, bool> > &control) {

    unsigned int i = 0;

    _finalizada = true;

    while(i < posiciones.size()){

        unsigned int j = 0;

        while(j < _participantes.size() and _participantes[j].ciaNumber() != posiciones[i]) {

            j++;

        }

        _ranking.push_back(_participantes[j]);

        i++;
    }

    unsigned int k = 0;

    while(k < control.size()) {

        unsigned int l = 0;

        while (l < _participantes.size() and _participantes[l].ciaNumber() != control[k].first) {

            l++;

        }

        pair<Atleta, bool> p = make_pair (_participantes[l], control[k].second);

        _lesTocoControlAntiDoping.push_back(p);

        k++;

    }

}

void Competencia::linfordChristie(const int &n) {

    unsigned int i = 0;

    vector<Atleta> nuevosParticipantes;

    while(i < _participantes.size()){

        if(_participantes[i].ciaNumber() != n){

            nuevosParticipantes.push_back(_participantes[i]);

        }

        i++;
    }

    _participantes = nuevosParticipantes;

}

bool Competencia::gananLosMasCapaces() const {

    unsigned int i = 0;

    bool gananOrdenCapacidad=true;

    if(_ranking.size()>0){

      while(i < (_ranking.size()-1) and _ranking[i].capacidad(_categoria.first) >= _ranking[i+1].capacidad(_categoria.first)){

        i++;

     }

     gananOrdenCapacidad=(i==_ranking.size()-1);

    }

    return gananOrdenCapacidad;

}

void Competencia::sancionarTramposos() {

    unsigned int j=0;

    vector <Atleta> nuevoRanking;

    while (j<_ranking.size()) {

        unsigned int i = 0;

        while (i < _lesTocoControlAntiDoping.size() and
               not(_ranking[j].operator==(_lesTocoControlAntiDoping[i].first))) {

            i++;
        }

        if (i == _lesTocoControlAntiDoping.size()) {

            nuevoRanking.push_back(_ranking[j]);

        } else if (not(_lesTocoControlAntiDoping[i].second)) { 

            nuevoRanking.push_back(_ranking[j]);
                }



        j++;

    }

    _ranking=nuevoRanking;
}

void Competencia::mostrar(std::ostream &os) const {

	os << *this << std::endl;
}

void Competencia::guardar(std::ostream &os) const {

	os << *this << std::endl;
}

void Competencia::cargar(std::istream &is) {

  char caracter;
  	is >> caracter;

  	if (caracter != 'C') {

		cerr << "[ERROR] No se ha podido cargar Competencia" << endl;

		return;
    }

    is.ignore(3);
    getline(is, _categoria.first, '|');
    is.ignore(3);
    string s;
    getline(is, s, '|');
    if (s == "Femenino") {
        _categoria.second = Femenino;
    } else if (s == "Masculino") {
        _categoria.second = Masculino;
    } else {
        assert(false);
    }
    is.ignore(3);

    getline(is, s, '|');
    if (s == "True") {
        _finalizada = true;
    } else if (s == "False") {
        _finalizada = false;
    } else {
        assert(false);
    }
	is.ignore(1);
		
	//_participantes.clear();
	unsigned int i = 0;	
	while(caracter != ']'){
		is.ignore(2);
        is >> caracter;
		//cout << caracter <<endl;

		//_participantes[i].cargar(is);

        //operator>>(is, _participantes[i]);

    	if (caracter != 'A') {
        	cerr << "[ERROR] No se ha podido cargar Atleta" << endl;
        	return;
    	}

    	is.ignore(2);
		string nombre;
    	getline(is, nombre, '|');
		//cout << nombre <<endl;
    	is.ignore(2);
    	string genero;
    	getline(is, genero, '|');
		//cout << genero << endl;
		Genero genAtleta;
    	if (genero == "Femenino") {
    	    genAtleta = Femenino;
    	} else if (genero == "Masculino") {
    	    genAtleta = Masculino;
    	} else {
    	    assert(false);
    	}
		int anioNacimiento;
    	is >> anioNacimiento;
		//cout << anioNacimiento <<endl;
    	is.ignore(2);
		string nacionalidad;
    	getline(is, nacionalidad, '|');
		int ciaNumber;
    	is >> ciaNumber;
		//cout << ciaNumber <<endl;
    	is.ignore(1);

		Atleta participante (nombre, genAtleta, anioNacimiento, nacionalidad, ciaNumber);

		_participantes.push_back(participante);    

    	is >> caracter;
    	while (caracter != ']') {
        	if (caracter == '[') {
            	is.ignore(2);
        	} else {
            	is.ignore(3);
        	}
        	string deporte;
        	getline(is, deporte, '|');
			//cout << deporte <<endl;
        	is.ignore(2);
        	int capacidad;
        	is >> capacidad;
			//cout << capacidad << endl;
        	is.ignore(1);
        	is >> caracter;
			//cout << caracter << endl;
			_participantes[i].entrenarNuevoDeporte(deporte, capacidad);
    	
		}

		i++;

		//cout << i <<endl;
		is.ignore(1);
		is >> caracter;
		//cout << caracter <<endl;

	}

	if(_finalizada){

		is.ignore(2);
        caracter = '|';
		while(caracter != ']'){
			int ciaNumber;		
			is >> ciaNumber;
			unsigned int i = 0;
			while(_participantes[i].ciaNumber() != ciaNumber){
	
				i++;			
			} 
		
			_ranking.push_back(_participantes[i]);
			is >> caracter;
		}

		is.ignore(1);
        caracter = '|';
        while(caracter != ']'){
            is.ignore(2);
            int ciaNumber;
            is >> ciaNumber;
            unsigned int i = 0;
            while(_participantes[i].ciaNumber() != ciaNumber){

                i++;
            }
            is.ignore(3);
            bool resultControl;
            string control;
            getline(is, control, '|');
            if (control == "True") {
                resultControl = true;
            } else if (control == "False") {
                resultControl = false;
            } else {
                assert(false);
            }


            pair <Atleta, bool> par = make_pair(_participantes[i], resultControl);
            _lesTocoControlAntiDoping.push_back(par);
            is.ignore(1);
            is >> caracter;
        }

	} else {

        is.ignore(6);

    }
		
		

}

std::ostream &operator<<(std::ostream &os, const Competencia &c) {

	os << "C (|" << c.categoria().first << "|, |" << c.categoria().second << "|) |";

	if(c.finalizada()){

	os << "True";

	} else {

    os << "False";

    }

	os << "| [(";

	if(c.participantes().size()>0){

		os << "A |" << c.participantes()[0].nombre() << "| |" << c.participantes()[0].genero() << "| " << c.participantes()[0].anioNacimiento() 		<< " |" << c.participantes()[0].nacionalidad() << "| " << c.participantes()[0].ciaNumber() << " [(|"
		<<c.participantes()[0].deportes()[0] << "|, " << c.participantes()[0].capacidad(c.participantes()[0].deportes()[0]) << ")";

		unsigned int i = 1;

		while(i < c.participantes()[0].deportes().size()){

			os << " , (|" << c.participantes()[0].deportes()[i] << "|, " << c.participantes()[0].capacidad(c.participantes()[0].deportes()[i]) 	<< ")";

			i++;

		}

		os << "])";

		unsigned int j = 1;

		while (j < c.participantes().size()){

			os << ", (A |" << c.participantes()[j].nombre() << "| |" << c.participantes()[j].genero() << "| "
			<< c.participantes()[j].anioNacimiento() << " |" << c.participantes()[j].nacionalidad() << "| " << c.participantes()[j].ciaNumber()
			<< " [" 	<< "(|" << c.participantes()[j].deportes()[0] << "|, "
			<< c.participantes()[j].capacidad(c.participantes()[j].deportes()[0]) << ")";

			unsigned int i = 1;

			while(i < c.participantes()[0].deportes().size()){

				os << " , (|" << c.participantes()[0].deportes()[i] << "|, "
				<< c.participantes()[0].capacidad(c.participantes()[0].deportes()[i]) << ")";

				i++;

			}

			os << "])";

			j++;

		}

		os << "] ";

		if(c.finalizada()){

			os << "[" << c.ranking()[0].ciaNumber();

			unsigned int k = 1;

			while(k < c.ranking().size()){

				os << ", " << c.ranking()[k].ciaNumber();

				k++;

			}

			os << "] [(" << c.lesTocoControlAntiDoping()[0].ciaNumber() << ", |" ;

            if(c.leDioPositivo(c.lesTocoControlAntiDoping()[0])) {

                os << "True";

            } else{

                os << "False";
            }

            os << "|)";

			unsigned int l = 1;

			while(l < c.lesTocoControlAntiDoping().size()){

				os << ", (" << c.lesTocoControlAntiDoping()[l].ciaNumber() << ", |";

                if(c.leDioPositivo(c.lesTocoControlAntiDoping()[l])){

                    os << "True";

                } else{

                    os << "False";
                }

                 os << "|)";

				l++;

			}

			os << "]";

		} else {

			os << " [] []";

		}


	}else {

		os << ")]";

	}




    return os;
}

std::istream &operator>>(std::istream &is, Competencia &c) {
	
	c.cargar(is);	
	
    return is;
}

bool Competencia::operator==(const Competencia &c) const {

    bool mismosParticipantesYCategoria = false;

    unsigned int i = 0;

    bool participantePertenece=true;

    if (_participantes.size() == c.participantes().size()) {

        while (i < _participantes.size() and participantePertenece) {

            unsigned int j = 0;

            while (j < c.participantes().size() and not(_participantes[i].operator==(c.participantes()[j]))) {
                j++;

            }

            participantePertenece = (j < c.participantes().size());

            i++;

        }

    
        mismosParticipantesYCategoria = ((i==_participantes.size()) and (_categoria.first==c.categoria().first) and (_categoria.second==c.categoria().second));


    }


    bool implicacionFinalizada= true;

    if (_finalizada and _finalizada==c.finalizada()){

        unsigned int k=0;

        bool igualRankings=false;

        if(_ranking.size()==c.ranking().size()){

            while (k<_ranking.size() and _ranking[k].operator==(c.ranking()[k])){

                k++;

            }

            igualRankings = (k==_ranking.size());

        }

        bool coincideControlAntiDoping= false;

        if (_lesTocoControlAntiDoping.size()==c.lesTocoControlAntiDoping().size()){

            unsigned  int l=0;

            bool encontroElMismoAtleta=true;

            while (l<_lesTocoControlAntiDoping.size() and encontroElMismoAtleta){

                unsigned  int q=0;

                while(q < c.lesTocoControlAntiDoping().size() and not(_lesTocoControlAntiDoping[l].first).operator==(c.lesTocoControlAntiDoping()[q])){

                    q++;

                }

                encontroElMismoAtleta= (q < c.lesTocoControlAntiDoping().size() and _lesTocoControlAntiDoping[l].second==leDioPositivo(c.lesTocoControlAntiDoping()[q]));

                l++;
            }
            coincideControlAntiDoping= (l == _lesTocoControlAntiDoping.size()); 

        }

        implicacionFinalizada= igualRankings and coincideControlAntiDoping;

    }

    return mismosParticipantesYCategoria and _finalizada==c.finalizada() and implicacionFinalizada;

}




Competencia Competencia::operator=(const Competencia &c) {
    _categoria = c._categoria;
    _participantes = c._participantes;
    _finalizada = c._finalizada;
    _ranking = c._ranking;
    _lesTocoControlAntiDoping = c._lesTocoControlAntiDoping;
    return (*this);
}
