#include "../include/jjoo.h"

#include <utility>
#include <algorithm>


JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs) {

    _anio = a;
    _atletas = as;
    _cronograma = cs;
    _jornadaActual = 1;
}

int JJOO::anio() const {
    return _anio;
}

vector<Atleta> JJOO::atletas() const {
    return _atletas;
}

int JJOO::cantDias() const {
    return _cronograma.size();
}

int JJOO::jornadaActual() const {
    return _jornadaActual;
}

vector<Competencia> JJOO::cronograma(const int &d) const {
    return _cronograma[d-1];
}

vector<Competencia> JJOO::competencias() const {
    vector<Competencia> competenciasJuego;

    unsigned int i = 0;

    while (i < _cronograma.size()){

        unsigned int j = 0;

        while (j < _cronograma[i].size()){


            competenciasJuego.push_back(_cronograma[i][j]);

            j++;

        }

        i++;

    }

    return competenciasJuego;
}

vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {
    vector<Competencia> competenciasConOro;

    vector<Competencia> competenciasJuego = competencias();

    unsigned int i = 0;

    while(i < competenciasJuego.size()){

        if(competenciasJuego[i].finalizada() and competenciasJuego[i].ranking().size()>0){

            competenciasConOro.push_back(competenciasJuego[i]);

        }

        i++;

    }

    return competenciasConOro;
}

 bool JJOO::pertenece(Atleta a, vector<Atleta> participan ) const{

        unsigned int i = 0;

        while(i < participan.size() and not(a.operator==(participan[i]))){

            i++;

        }

        return (i < participan.size());

    }

vector<Atleta> JJOO::dePaseo() const {

    vector<Atleta> atletasDePaseo;

    vector<Competencia> competenciasJuego = competencias();

    vector<Atleta> participantesCompetencia;

    unsigned int i = 0;

    while (i < competenciasJuego.size()){

        unsigned int j = 0;

        while (j < competenciasJuego[i].participantes().size()){

            participantesCompetencia.push_back(competenciasJuego[i].participantes()[j]);

            j++;

        }

        i++;

    }

    unsigned int k = 0;

    if(participantesCompetencia.size()>0){

    while(k < _atletas.size()){   

        if(not(pertenece(atletas()[k], participantesCompetencia))){  

            atletasDePaseo.push_back(atletas()[k]);

        }

        k++;

    }

}else{

    unsigned int p=0;

    while(p<_atletas.size()){

        atletasDePaseo.push_back(_atletas[p]);

    }
}

    return atletasDePaseo;
}


vector<pair<Pais, vector<int> > > JJOO::medallero() const {

    vector<Pais> paisesConMedallas;

    vector<Pais> paisesConOro;

    vector<Pais> paisesConPlata;

    vector<Pais> paisesConBronce;

    vector<Competencia> competenciasConMedalla = competenciasFinalizadasConOroEnPodio();

    unsigned int i = 0;

    while (i<competenciasConMedalla.size()){

    	unsigned int k=0;

    	while (k< competenciasConMedalla[i].ranking().size() and k<3){

    		Pais paisConMedalla = competenciasConMedalla[i].ranking()[k].nacionalidad();

    		if  (not pertenecePais(paisConMedalla, paisesConMedallas)) {

                if(paisesConMedallas.size()==0 || paisConMedalla!=paisesConMedallas[0]){

    			     paisesConMedallas.push_back(paisConMedalla);

                 }
    		}

    		if (k==0){

        		paisesConOro.push_back(paisConMedalla);

        	} else if (k==1) {

        		paisesConPlata.push_back(paisConMedalla);

        	} else {

	        	paisesConBronce.push_back(paisConMedalla);
    		}

    		k++;
    	}


        i++;

    }

    unsigned int j=0;

    vector<int> medallero;

    vector<int> medallero0;

    vector<pair<Pais, vector<int> > > medallasPorPais;

    while (j< paisesConMedallas.size()) {

    	int oros= contarpais(paisesConMedallas[j], paisesConOro);

    	medallero.push_back(oros);

    	int platas = contarpais(paisesConMedallas[j], paisesConPlata);

 		medallero.push_back(platas);

    	int bronces = contarpais(paisesConMedallas[j], paisesConBronce);

    	medallero.push_back(bronces);

		pair <Pais,vector<int>> paisyMedallas= make_pair(paisesConMedallas[j], medallero);

		medallasPorPais.push_back(paisyMedallas);

		medallero = medallero0;

		j++;
    }

    vector<pair<Pais, vector<int> > > paisesYmedallas;



    if(medallasPorPais.size()>0){

    	paisesYmedallas=medalleroOrdenado(medallasPorPais);


    }

	return paisesYmedallas;

    }

    pair<Pais, vector <int>> JJOO::primerPais (vector<pair<Pais, vector <int>>> medallero) const {

      pair<Pais, vector <int>> paisPrimero=medallero[0];

      unsigned int i=1;

      while(i<medallero.size()){

        if((medallero[i].second[0]>paisPrimero.second[0]) || (medallero[i].second[0]==paisPrimero.second[0] && medallero[i].second[1]>paisPrimero.second[1]) || (medallero[i].second[0]==paisPrimero.second[0] && medallero[i].second[1]==paisPrimero.second[1] && medallero[i].second[2]>paisPrimero.second[2])){

          paisPrimero=medallero[i];

        }
        i++;

      }
    return paisPrimero;

    }

      vector<pair<Pais, vector <int>>> JJOO::medalleroSacoElemento(vector<pair<Pais, vector <int>>> medallero, pair<Pais, vector <int>> p ) const {

        vector<pair<Pais, vector <int>>> medalleroSinElemento;

        unsigned int i=0;

        while(i<medallero.size()){

          if(not(medallero[i]==p)){

            medalleroSinElemento.push_back(medallero[i]);

          }

          i++;

        }

        return medalleroSinElemento;
      }

      vector<pair<Pais, vector <int>>> JJOO::medalleroOrdenado(vector<pair<Pais, vector <int>>> medallero ) const {

        vector<pair<Pais, vector <int>>> medalleroConOrden;

        vector<pair<Pais, vector <int>>> medalleroAux;

        medalleroAux = medallero;

        pair<Pais, vector <int>> p;

        unsigned int i=0;

        while(i<medallero.size()){

          p = primerPais(medalleroAux);

          medalleroConOrden.push_back(p);

          medalleroAux=medalleroSacoElemento(medalleroAux,p);

          i++;

        }

        return medalleroConOrden;

      }







bool JJOO::pertenecePais(Pais p, vector<Pais> paisesls ) const{

        unsigned int i = 0;

        while(i < paisesls.size() and not(p==(paisesls[i]))) {

            i++;

        }

        return (i < paisesls.size());

    }


int JJOO::contarpais(Pais p, vector<Pais> paisesls ) const{

        unsigned int i = 0;
        unsigned int s=0;

        while(i < paisesls.size()) {

        	if (p==paisesls[i]) {

        		s++;
        	}

            i++;

        }

        return s;

    }



int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {

	unsigned int i=0;

	vector <Atleta> participantesNoP;

	vector <int> rankingNoP;

	vector<pair<int, bool> > lesTocoNoP;

	vector <int> rankingNoP0;

	vector<pair<int, bool> > lesTocoNoP0;

	vector <Atleta> participantesNoP0;
	
	vector <Atleta> atletasDadosDeBaja;

	vector <Atleta> deBajaSinRepe;

	while (i<_cronograma.size()) {

		unsigned int j = 0;

		while (j<_cronograma[i].size()){

			participantesNoP = participantesNoP0;

			rankingNoP = rankingNoP0;

			lesTocoNoP = lesTocoNoP0;

			if (_cronograma[i][j].categoria() == c) {

				unsigned int k = 0;

				while (k<_cronograma[i][j].participantes().size()){

					if (_cronograma[i][j].participantes()[k].nacionalidad() != p) {

						participantesNoP.push_back(_cronograma[i][j].participantes()[k]);

					} else {

						atletasDadosDeBaja.push_back(_cronograma[i][j].participantes()[k]);

					}

					k++;

				}

				Competencia competenciaBoicot (c.first, c.second, participantesNoP);

				if (_cronograma[i][j].finalizada()) {

					unsigned int l = 0;

					while (l<_cronograma[i][j].ranking().size()) {

						if (_cronograma[i][j].ranking()[l].nacionalidad() != p) {

							rankingNoP.push_back(_cronograma[i][j].ranking()[l].ciaNumber());

						}

						l++;

					}

					unsigned int m = 0;

					while (m<_cronograma[i][j].lesTocoControlAntiDoping().size()){

						if (_cronograma[i][j].lesTocoControlAntiDoping()[m].nacionalidad() != p) {

							pair<int, bool> leTocoNoP = make_pair(_cronograma[i][j].lesTocoControlAntiDoping()[m].ciaNumber(),_cronograma[i][j].leDioPositivo(_cronograma[i][j].lesTocoControlAntiDoping()[m]));

							lesTocoNoP.push_back(leTocoNoP);

						}

						m++;

					}

					competenciaBoicot.finalizar(rankingNoP, lesTocoNoP);

				}

				_cronograma[i][j] = competenciaBoicot;

		}

			j++;

		}

		i++;

	}

	unsigned int n = 0;

	while (n<atletasDadosDeBaja.size()) {

		if (not pertenece (atletasDadosDeBaja[n], deBajaSinRepe)) {

			deBajaSinRepe.push_back(atletasDadosDeBaja[n]);

		}

		n++;

	}

    return deBajaSinRepe.size();

}

int JJOO::contarAtleta(Atleta a, vector<Atleta> als) const{

        unsigned int i = 0;

        unsigned int s=0;

        while(i < als.size()) {

        	if (a.operator==(als[i])) {

        		s++;
        	}

            i++;

        }

        return s;

    }

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {

    vector<Atleta> fracasados;

    vector <Atleta> todosParticipantes;

    vector<Atleta> masParticipantes;

    vector<Atleta> participantesSinRepSinGan;

    vector<Atleta> ganadores;

    int cuentaParticipadas = 0;

    unsigned int i = 0;

    while (i<_cronograma.size()){

    	unsigned int j = 0;

    	while (j<_cronograma[i].size()){

    		unsigned int k = 0;

    		while (k<_cronograma[i][j].participantes().size()){

    			if (_cronograma[i][j].participantes()[k].nacionalidad() == p){
    				todosParticipantes.push_back(_cronograma[i][j].participantes()[k]);
    			}

    			if (_cronograma[i][j].participantes()[k].nacionalidad() == p && _cronograma[i][j].finalizada() && 0<_cronograma[i][j].ranking().size() && _cronograma[i][j].participantes()[k] == _cronograma[i][j].ranking()[0]){
    				ganadores.push_back(_cronograma[i][j].participantes()[k]);
    			}

    			if (_cronograma[i][j].participantes()[k].nacionalidad() == p && _cronograma[i][j].finalizada() && 1<_cronograma[i][j].ranking().size() && _cronograma[i][j].participantes()[k] == _cronograma[i][j].ranking()[1]){
    				ganadores.push_back(_cronograma[i][j].participantes()[k]);
    			}

    			if (_cronograma[i][j].participantes()[k].nacionalidad() == p && _cronograma[i][j].finalizada() && 2<_cronograma[i][j].ranking().size() && _cronograma[i][j].participantes()[k] == _cronograma[i][j].ranking()[2]){
    				ganadores.push_back(_cronograma[i][j].participantes()[k]);
    			}

    			k++;

    		}

    		j++;

    	}

    	i++;

    }

    unsigned int l = 0;

    while (l<todosParticipantes.size()){

    	if (not pertenece(todosParticipantes[l], participantesSinRepSinGan) && not pertenece (todosParticipantes[l], ganadores)){

    		participantesSinRepSinGan.push_back(todosParticipantes[l]);

    	}

    	l++;
    }

    unsigned int m = 0;

    while (m<participantesSinRepSinGan.size()){

    	if (contarAtleta(participantesSinRepSinGan[m], todosParticipantes) > cuentaParticipadas){

    		cuentaParticipadas = contarAtleta(participantesSinRepSinGan[m], todosParticipantes);

    	}

    	m++;

    }

    unsigned int n = 0;

    while (n<participantesSinRepSinGan.size()){

    	if (contarAtleta(participantesSinRepSinGan[n], todosParticipantes) == cuentaParticipadas){

    		fracasados.push_back(participantesSinRepSinGan[n]);

    	}

    	n++;

    }

     return fracasados;

}

void JJOO::liuSong(const Atleta &a, const Pais &p){

    Atleta liuCambiado(a.nombre(),a.genero(),a.anioNacimiento(),p,a.ciaNumber());

    vector<pair<Deporte, int>> deportesDeLiu;

    unsigned int q=0;

    while (q< a.deportes().size()) {

    	pair<Deporte, int> deporteDeLiu = make_pair(a.deportes()[q],a.capacidad(a.deportes()[q]));

    	deportesDeLiu.push_back(deporteDeLiu);

    	q++;
    }

	unsigned int f=0;

	while (f<deportesDeLiu.size()) {

		liuCambiado.entrenarNuevoDeporte(deportesDeLiu[f].first,deportesDeLiu[f].second);
		f++;

	}

    vector <Atleta> atletasConLiuCambiado;

    unsigned int i=0;

    while(i<_atletas.size() and not(_atletas[i].operator==(a))){

        atletasConLiuCambiado.push_back(_atletas[i]);

        i++;
    }

    atletasConLiuCambiado.push_back(liuCambiado);

    i++;

    while(i<_atletas.size()){

        atletasConLiuCambiado.push_back(_atletas[i]);

        i++;
    }

    _atletas=atletasConLiuCambiado;

    vector<Competencia> nuevasCompetencias;

    vector<Competencia> nuevasCompetencias0;

    vector<vector<Competencia> > nuevoCronograma;

    vector <Atleta> participantesNuevos;

    vector <Atleta> participantesNuevos0;

    vector <int> rankingNuevo;

    vector <int> rankingNuevo0;

    vector<pair<int,bool>> lesTocoNuevo;

    vector<pair<int,bool>> lesTocoNuevo0;

    unsigned int j=0;

    while(j<_cronograma.size()){

        unsigned int k=0;

        while(k<_cronograma[j].size()){

            if(pertenece(a,_cronograma[j][k].participantes())){

                unsigned int l=0;

                while(l<_cronograma[j][k].participantes().size() and not(_cronograma[j][k].participantes()[l].operator==(a))){

                    participantesNuevos.push_back(_cronograma[j][k].participantes()[l]);

                    l++;

                }

                participantesNuevos.push_back(liuCambiado);

                l++;

                while(l<_cronograma[j][k].participantes().size()){

                    participantesNuevos.push_back(_cronograma[j][k].participantes()[l]);

                    l++;
                }

               Competencia competenciaDiaJnumeroK(_cronograma[j][k].categoria().first,_cronograma[j][k].categoria().second, participantesNuevos);

                if(_cronograma[j][k].finalizada()){

                    if(pertenece(a,_cronograma[j][k].ranking())){

                        unsigned int m=0;

                        while(m<_cronograma[j][k].ranking().size() and not(_cronograma[j][k].ranking()[m].operator==(a))){

                            rankingNuevo.push_back(_cronograma[j][k].ranking()[m].ciaNumber());

                            m++;
                        }

                        rankingNuevo.push_back(liuCambiado.ciaNumber());

                        m++;

                        while(m<_cronograma[j][k].ranking().size()){

                            rankingNuevo.push_back(_cronograma[j][k].ranking()[m].ciaNumber());

                            m++;
                        }

                    }else{

                           unsigned int o = 0;

                          while(o <_cronograma[j][k].ranking().size()){

                            rankingNuevo.push_back(_cronograma[j][k].ranking()[o].ciaNumber());

                            o++;
                          }


                    }

                    if(pertenece(a,_cronograma[j][k].lesTocoControlAntiDoping())){

                        unsigned int n=0;

                        while(n<_cronograma[j][k].lesTocoControlAntiDoping().size() and not(_cronograma[j][k].lesTocoControlAntiDoping()[n].operator==(a))){

                            pair<int,bool> atletaControl = make_pair(_cronograma[j][k].lesTocoControlAntiDoping()[n].ciaNumber(),_cronograma[j][k].leDioPositivo(_cronograma[j][k].lesTocoControlAntiDoping()[n]));

                            lesTocoNuevo.push_back(atletaControl);

                            n++;

                        }

                          pair<int,bool> controlLiu = make_pair(liuCambiado.ciaNumber(),_cronograma[j][k].leDioPositivo(a));

                          lesTocoNuevo.push_back(controlLiu);


                          n++;

                        while(n<_cronograma[j][k].lesTocoControlAntiDoping().size()){

                            pair<int,bool> atletaControl2 = make_pair(_cronograma[j][k].lesTocoControlAntiDoping()[n].ciaNumber(),_cronograma[j][k].leDioPositivo(_cronograma[j][k].lesTocoControlAntiDoping()[n]));

                            lesTocoNuevo.push_back(atletaControl2);

                            n++;

                        }

                    }else{

                      unsigned int p = 0;

                      while(p<_cronograma[j][k].lesTocoControlAntiDoping().size()){

                          pair<int,bool> atletaControl3 = make_pair(_cronograma[j][k].lesTocoControlAntiDoping()[p].ciaNumber(),_cronograma[j][k].leDioPositivo(_cronograma[j][k].lesTocoControlAntiDoping()[p]));

                          lesTocoNuevo.push_back(atletaControl3);

                          p++;

                        }
                     }


                    competenciaDiaJnumeroK.finalizar(rankingNuevo,lesTocoNuevo);
                }

                nuevasCompetencias.push_back(competenciaDiaJnumeroK);

                participantesNuevos=participantesNuevos0;

                rankingNuevo=rankingNuevo0;

                lesTocoNuevo=lesTocoNuevo0;

            }else{

            nuevasCompetencias.push_back(_cronograma[j][k]);

            }

            k++;

        }


        _cronograma[j]=nuevasCompetencias;

        nuevasCompetencias=nuevasCompetencias0;

        nuevoCronograma.push_back(_cronograma[j]);

        j++;
    }



    _cronograma=nuevoCronograma;

}



Atleta JJOO::stevenBradbury() const {

    int i=1;

    vector<Competencia> competenciasConOro;

    vector <Atleta> ganadores;

    vector <Categoria> categoriasDeGanadores;

    vector <pair<Atleta, Categoria>> ganadoresPorCategorias;


    while(i<=_jornadaActual){

        unsigned int j=0;

        while(j<cronograma(i).size()){

            if(cronograma(i)[j].finalizada() and (cronograma(i)[j].ranking().size()>0)){

                competenciasConOro.push_back(cronograma(i)[j]);
            }
            j++;
        }

        i++;

    }

    unsigned int k=0;

    while(k<competenciasConOro.size()){

        ganadores.push_back(competenciasConOro[k].ranking()[0]);
    }

    unsigned int l=0;

    while(l<competenciasConOro.size()){

        categoriasDeGanadores.push_back(competenciasConOro[l].categoria());

        l++;

    }

    unsigned int m=0;

    while(m<competenciasConOro.size()){

        pair <Atleta, Categoria> ganadorYCategoria = make_pair(ganadores[m],categoriasDeGanadores[m]);

        ganadoresPorCategorias.push_back(ganadorYCategoria);

        m++;
    }

    pair<Atleta,Deporte> elPeor=make_pair(ganadores[0],categoriasDeGanadores[0].first);

    unsigned int n=1;

    while(n < ganadoresPorCategorias.size()){

        if(ganadoresPorCategorias[n].first.capacidad(ganadoresPorCategorias[n].second.first)<elPeor.first.capacidad(elPeor.second)){

            elPeor= make_pair(ganadoresPorCategorias[n].first,ganadoresPorCategorias[n].second.first);
        }

        n++;
    }

    return elPeor.first;

}

bool JJOO::uyOrdenadoAsiHayUnPatron() const {

    int i = 0;

    vector <Pais> ganadoresDelDia;

    Pais masGanadorDelDia;

    vector<Pais> masGanadoresPorDia;

    bool hayPatron = true;

    bool hayRepeticion = false;

    while (i<(_jornadaActual-1)){

		unsigned int j = 0;

		while (j<_cronograma[i].size()){

			if (_cronograma[i][j].finalizada() && _cronograma[i][j].ranking().size()>0){

				ganadoresDelDia.push_back(_cronograma[i][j].ranking()[0].nacionalidad());

				}

			j++;

			}

            if (ganadoresDelDia.size()>0){

                masGanadorDelDia = ganadoresDelDia[0];

                unsigned int k = 1;

                while (k<ganadoresDelDia.size()){

                    if (contarpais(masGanadorDelDia, ganadoresDelDia)<contarpais(ganadoresDelDia[k], ganadoresDelDia)){

                        masGanadorDelDia = ganadoresDelDia[k];

                        }

                    k++;

                    }

                unsigned int l = 0;

                while (l<ganadoresDelDia.size()){

                    if (contarpais(masGanadorDelDia, ganadoresDelDia) == contarpais(ganadoresDelDia[l], ganadoresDelDia) && ganadoresDelDia[l]<masGanadorDelDia){

                        masGanadorDelDia = ganadoresDelDia[l];

                        }
                    l++;

                    }

                masGanadoresPorDia.push_back(masGanadorDelDia);

            }

		i++;

		}

        unsigned int x=0;

        unsigned int m = 0;

        while (x<masGanadoresPorDia.size() && not hayRepeticion){

            m = 0;

            while (m<masGanadoresPorDia.size() && not hayRepeticion){

                if (m!=x && masGanadoresPorDia[0] == masGanadoresPorDia[m]){

                    hayRepeticion = true;

                    }

                m++;

            }

            x++;

        }

		if (x>1 && hayRepeticion){

            hayPatron = false;

        }

        if (m>0){

            m--;

        }

		unsigned int n = m;

		if (hayRepeticion && hayPatron){

			while (n<masGanadoresPorDia.size() && hayPatron){

				if (not (masGanadoresPorDia[n-m] == masGanadoresPorDia[n])){

					hayPatron = false;

					}

				n++;

				}

			}

	return hayPatron;

}

int JJOO::sequedadOlimpica(Pais p) const {

    vector<Pais> ganaronHoy;

    vector<Pais> ganaronHoy0;

    unsigned int sequiaActual = 1;

    unsigned int sequiaRecord = 0;

    unsigned int i = 0;

    int m = 0;

    while (i<_cronograma.size() && m<=(_jornadaActual-2)){

		unsigned int j = 0;

		while (j<_cronograma[i].size()){

            ganaronHoy = ganaronHoy0;

			if (_cronograma[i][j].finalizada() && 0<_cronograma[i][j].ranking().size()){

				ganaronHoy.push_back(_cronograma[i][j].ranking()[0].nacionalidad());

			}

			if (_cronograma[i][j].finalizada() && 1<_cronograma[i][j].ranking().size()){

				ganaronHoy.push_back(_cronograma[i][j].ranking()[1].nacionalidad());

			}

			if (_cronograma[i][j].finalizada() && 2<_cronograma[i][j].ranking().size()){

				ganaronHoy.push_back(_cronograma[i][j].ranking()[2].nacionalidad());

			}

			j++;

		}

		if (not (pertenecePais(p,ganaronHoy))){

			sequiaActual++;

		}else{

			sequiaActual = 1;
    

		}

		if (sequiaActual>sequiaRecord){

			sequiaRecord = sequiaActual;

		}

		i++;

		m++;

	}

	return sequiaRecord;

}

vector<Pais> JJOO::sequiaOlimpica() const {

    vector<Pais> paisesTotalesConRepetidos;

    vector<Pais> paisesTotales;

    vector<Pais> secos;

    unsigned int i = 0;

    while(i<_atletas.size()){

		paisesTotalesConRepetidos.push_back(_atletas[i].nacionalidad());

		i++;

	}

	unsigned int j = 0;

	while (j<paisesTotalesConRepetidos.size()){

		if (not (pertenecePais (paisesTotalesConRepetidos[j], paisesTotales))){

			paisesTotales.push_back(paisesTotalesConRepetidos[j]);

		}

		j++;

	}

    if (paisesTotales.size()>0){

        Pais paisSeco = paisesTotales[0];

        unsigned int k = 0;

        while (k<paisesTotales.size()){

            if (sequedadOlimpica(paisSeco)<sequedadOlimpica(paisesTotales[k])){
                
                paisSeco = paisesTotales [k];

            }


            k++;

        }

        unsigned int l = 0;

        while (l<paisesTotales.size()){

            if (sequedadOlimpica(paisSeco)==sequedadOlimpica(paisesTotales[l])){

                secos.push_back(paisesTotales[l]);

            }

            l++;

        }
    }

    return secos;
}

Atleta JJOO::atletaMaxCapacidad (vector<Atleta> participantes, Categoria c) const {

    Atleta atletaMayorCap=participantes[0];

    unsigned int i=1;

    while(i<participantes.size()){

        if(participantes[i].capacidad(c.first)>atletaMayorCap.capacidad(c.first)){

        atletaMayorCap=participantes[i];

        }
        i++;

    }
    return atletaMayorCap;

}

vector<Atleta> JJOO::rankingSacoElemento(vector <Atleta> ranking, Atleta a) const{

    vector<Atleta> rankingSinElemento;

    unsigned int i=0;

    while(i<ranking.size()){

      if(not(ranking[i].operator==(a))){

        rankingSinElemento.push_back(ranking[i]);

      }

      i++;

    }

    return rankingSinElemento;
}


vector<int> JJOO::rankingOrdenado(vector<Atleta> participantes, Categoria c) const {

    vector<Atleta> rankingAux=participantes;

    vector<int> rankingConOrden;

    while(rankingConOrden.size()<participantes.size()){

      Atleta atletaAux = atletaMaxCapacidad(rankingAux,c);

      rankingConOrden.push_back(atletaAux.ciaNumber());

      rankingAux=rankingSacoElemento(rankingAux, atletaAux);

    }

    return rankingConOrden;
}

void JJOO::transcurrirDia() {

   vector<Competencia> nuevasCompetencias;

   vector<vector<Competencia> > nuevoCronograma;

    unsigned int i=0;

    int l=0;


   while(i<_cronograma.size() and l<(_jornadaActual-1)){

        nuevoCronograma.push_back(_cronograma[i]);

        i++;

        l++;

    }

	
    unsigned int j=0;

    while(j<_cronograma[i].size()){

        if(not(_cronograma[i][j].finalizada())){

            if(_cronograma[i][j].participantes().size()==0){

                vector <int> posiciones0;

                vector<pair<int,bool>> controlado0;

                _cronograma[i][j].finalizar(posiciones0,controlado0);


            }else{

            vector <int> posiciones =rankingOrdenado(_cronograma[i][j].participantes(), _cronograma[i][j].categoria());

            bool positivoParticipante=false;

            pair<int,bool> atletaControlado=make_pair(_cronograma[i][j].participantes()[0].ciaNumber(),positivoParticipante);

            vector<pair<int,bool>> controlado;

            controlado.push_back(atletaControlado);

            _cronograma[i][j].finalizar(posiciones,controlado);


            }

        } 

        nuevasCompetencias.push_back(_cronograma[i][j]);

        j++;


    }

    nuevoCronograma.push_back(nuevasCompetencias);

    i++;

    while(i<_cronograma.size()){

        nuevoCronograma.push_back(_cronograma[i]);

        i++;
    }

    _jornadaActual=(_jornadaActual+1);

    _cronograma=nuevoCronograma;


}

void JJOO::mostrar(std::ostream &os) const {

    os << *this << std::endl;

}

void JJOO::guardar(std::ostream &os) const {

    os << *this << std::endl;
}

void JJOO::cargar(std::istream &is) {

    char caracter;
    is >> caracter;

    if (caracter != 'J') {

        cerr << "[ERROR] No se ha podido cargar Juego Olimpico" << endl;

        return;
    }

    is >> _anio >> _jornadaActual;
    is.ignore(3);
    Atleta a("Alexia", Genero::Femenino, 1987, "Estonia", 10);
    _atletas.clear();
    while(caracter != ']'){
        a.cargar(is);
        _atletas.push_back(a);
        is.ignore(1);
        is >> caracter;
        if(caracter == ','){
            is.ignore(2);
        }
    }
    //is.ignore(1);
    is >> caracter;
    _cronograma.clear();
    Competencia comp = Competencia("Tenis", Genero::Femenino, std::vector<Atleta>());
    vector <Competencia> compDelDia;
    while(caracter != ']') {
        is.ignore(1);
        is >> caracter;
        if(caracter != ']') {
            while (caracter != ']') {
                comp.cargar(is);
                compDelDia.push_back(comp);
                is.ignore(1);
                is >> caracter;
                if (caracter == ',') {
                    is.ignore(2);
                }
            }

            _cronograma.push_back(compDelDia);
        }
        is >> caracter;


    }





}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {

    os << "J " << j.anio() << " " << j.jornadaActual() << " [(";

    if (j.atletas().size() > 0) {

        os << "A |" << j.atletas()[0].nombre() << "| |" << j.atletas()[0].genero() << "| "
           << j.atletas()[0].anioNacimiento() << " |"
           << j.atletas()[0].nacionalidad() << "| " << j.atletas()[0].ciaNumber() << " [" << "(|"
           << j.atletas()[0].deportes()[0] << "|, " << j.atletas()[0].capacidad(j.atletas()[0].deportes()[0]) << ")";

        unsigned int i = 1;

        while (i < j.atletas()[0].deportes().size()) {

            os << " , (|" << j.atletas()[0].deportes()[i] << "|, "
               << j.atletas()[0].capacidad(j.atletas()[0].deportes()[i]) << ")";

            i++;

        }

        os << "])";

        unsigned int n = 1;

        while (n < j.atletas().size()) {

            os << ", (A |" << j.atletas()[n].nombre() << "| |" << j.atletas()[n].genero() << "| "
               << j.atletas()[n].anioNacimiento() << " |" << j.atletas()[n].nacionalidad() << "| "
               << j.atletas()[n].ciaNumber()
               << " [" << "(|" << j.atletas()[n].deportes()[0] << "|, "
               << j.atletas()[n].capacidad(j.atletas()[n].deportes()[0]) << ")";

            unsigned int i = 1;

            while (i < j.atletas()[0].deportes().size()) {

                os << " , (|" << j.atletas()[0].deportes()[i] << "|, "
                   << j.atletas()[0].capacidad(j.atletas()[0].deportes()[i]) << ")";

                i++;

            }

            os << "])";

            n++;

        }

        os << "]";

    } else {

        os << ")]";

    }

    os << "[";

    if (j.cantDias() > 0) {

        os << "[";

        int d = 1;

        while (d <= j.cantDias()) {

            if (d != 1) {

                os << ", ";

            }

            if (j.cronograma(d).size() > 0) {


                os << "(";

                os << "C (|" << j.cronograma(d)[0].categoria().first << "|, |" << j.cronograma(d)[0].categoria().second
                   << "|) |";

                if (j.cronograma(d)[0].finalizada()) {

                    os << "True";

                } else {

                    os << "False";

                }

                os << "| [(";

                if (j.cronograma(d)[0].participantes().size() > 0) {

                    os << "A |" << j.cronograma(d)[0].participantes()[0].nombre() << "| |"
                       << j.cronograma(d)[0].participantes()[0].genero() << "| "
                       << j.cronograma(d)[0].participantes()[0].anioNacimiento() << " |"
                       << j.cronograma(d)[0].participantes()[0].nacionalidad() << "| "
                       << j.cronograma(d)[0].participantes()[0].ciaNumber() << " [(|"
                       << j.cronograma(d)[0].participantes()[0].deportes()[0] << "|, "
                       << j.cronograma(d)[0].participantes()[0].capacidad(
                               j.cronograma(d)[0].participantes()[0].deportes()[0]) << ")";

                    unsigned int i = 1;

                    while (i < j.cronograma(d)[0].participantes()[0].deportes().size()) {

                        os << " , (|" << j.cronograma(d)[0].participantes()[0].deportes()[i] << "|, "
                           << j.cronograma(d)[0].participantes()[0].capacidad(
                                   j.cronograma(d)[0].participantes()[0].deportes()[i]) << ")";

                        i++;

                    }

                    os << "])";

                    unsigned int p = 1;

                    while (p < j.cronograma(d)[0].participantes().size()) {

                        os << ", (A |" << j.cronograma(d)[0].participantes()[p].nombre() << "| |"
                           << j.cronograma(d)[0].participantes()[p].genero() << "| "
                           << j.cronograma(d)[0].participantes()[p].anioNacimiento() << " |"
                           << j.cronograma(d)[0].participantes()[p].nacionalidad() << "| "
                           << j.cronograma(d)[0].participantes()[p].ciaNumber()
                           << " [" << "(|" << j.cronograma(d)[0].participantes()[p].deportes()[0] << "|, "
                           << j.cronograma(d)[0].participantes()[p].capacidad(
                                   j.cronograma(d)[0].participantes()[p].deportes()[0]) << ")";

                        unsigned int i = 1;

                        while (i < j.cronograma(d)[0].participantes()[0].deportes().size()) {

                            os << " , (|" << j.cronograma(d)[0].participantes()[0].deportes()[i] << "|, "
                               << j.cronograma(d)[0].participantes()[0].capacidad(
                                       j.cronograma(d)[0].participantes()[0].deportes()[i]) << ")";

                            i++;

                        }

                        os << "])";

                        p++;

                    }

                    os << "]";

                    if (j.cronograma(d)[0].finalizada()) {

                        os << " [" << j.cronograma(d)[0].ranking()[0].ciaNumber();

                        unsigned int k = 1;

                        while (k < j.cronograma(d)[0].ranking().size()) {

                            os << ", " << j.cronograma(d)[0].ranking()[k].ciaNumber();

                            k++;

                        }

                        os << "] [(" << j.cronograma(d)[0].lesTocoControlAntiDoping()[0].ciaNumber() << ", |";
                        if(j.cronograma(d)[0].leDioPositivo(j.cronograma(d)[0].lesTocoControlAntiDoping()[0])) {

                            os << "True";

                        }else{

                            os << "False";
                        }


                        os << "|)";

                        unsigned int l = 1;

                        while (l < j.cronograma(d)[0].lesTocoControlAntiDoping().size()) {

                            os << ", (" << j.cronograma(d)[0].lesTocoControlAntiDoping()[l].ciaNumber() << ", |";
                            if(j.cronograma(d)[0].leDioPositivo(j.cronograma(d)[0].lesTocoControlAntiDoping()[l])){

                                os << "True";

                            }else {

                                os << "False";
                            }

                            os << "|)";

                            l++;

                        }

                        os << "]";

                    } else {

                        os << " [] []";

                    }


                } else {

                    os << ")]";

                }

                os << ")";

                unsigned int q = 1;

                while (q < j.cronograma(d).size()) {

                    os << ", (";

                    os << "C (|" << j.cronograma(d)[q].categoria().first << "|, |"
                       << j.cronograma(d)[q].categoria().second << "|) |";

                    if (j.cronograma(d)[q].finalizada()) {

                        os << "True";

                    } else {

                        os << "False";

                    }

                    os << "| [(";

                    if (j.cronograma(d)[q].participantes().size() > 0) {

                        os << "A |" << j.cronograma(d)[q].participantes()[0].nombre() << "| |"
                           << j.cronograma(d)[q].participantes()[0].genero() << "| "
                           << j.cronograma(d)[q].participantes()[0].anioNacimiento() << " |"
                           << j.cronograma(d)[q].participantes()[0].nacionalidad() << "| "
                           << j.cronograma(d)[q].participantes()[0].ciaNumber() << " [(|"
                           << j.cronograma(d)[q].participantes()[0].deportes()[0] << "|, "
                           << j.cronograma(d)[q].participantes()[0].capacidad(
                                   j.cronograma(d)[q].participantes()[0].deportes()[0]) << ")";

                        unsigned int i = 1;

                        while (i < j.cronograma(d)[q].participantes()[0].deportes().size()) {

                            os << " , (|" << j.cronograma(d)[q].participantes()[0].deportes()[i] << "|, "
                               << j.cronograma(d)[0].participantes()[0].capacidad(
                                       j.cronograma(d)[q].participantes()[0].deportes()[i]) << ")";

                            i++;

                        }

                        os << "])";

                        unsigned int p = 1;

                        while (p < j.cronograma(d)[q].participantes().size()) {

                            os << ", (A |" << j.cronograma(d)[q].participantes()[p].nombre() << "| |"
                               << j.cronograma(d)[q].participantes()[p].genero() << "| "
                               << j.cronograma(d)[q].participantes()[p].anioNacimiento() << " |"
                               << j.cronograma(d)[q].participantes()[p].nacionalidad() << "| "
                               << j.cronograma(d)[q].participantes()[p].ciaNumber()
                               << " [" << "(|" << j.cronograma(d)[q].participantes()[p].deportes()[0] << "|, "
                               << j.cronograma(d)[q].participantes()[p].capacidad(
                                       j.cronograma(d)[q].participantes()[p].deportes()[0]) << ")";

                            unsigned int i = 1;

                            while (i < j.cronograma(d)[q].participantes()[0].deportes().size()) {

                                os << " , (|" << j.cronograma(d)[q].participantes()[0].deportes()[i] << "|, "
                                   << j.cronograma(d)[q].participantes()[0].capacidad(
                                           j.cronograma(d)[q].participantes()[0].deportes()[i]) << ")";

                                i++;

                            }

                            os << "])";

                            p++;

                        }

                        os << "]";

                        if (j.cronograma(d)[q].finalizada()) {

                            os << "[" << j.cronograma(d)[q].ranking()[0].ciaNumber();

                            unsigned int k = 1;

                            while (k < j.cronograma(d)[q].ranking().size()) {

                                os << ", " << j.cronograma(d)[q].ranking()[k].ciaNumber();

                                k++;

                            }

                            os << "] [(" << j.cronograma(d)[q].lesTocoControlAntiDoping()[0] << ", |"
                               << j.cronograma(d)[q].leDioPositivo(j.cronograma(d)[q].lesTocoControlAntiDoping()[0])
                               << "|)";

                            unsigned int l = 1;

                            while (l < j.cronograma(d)[q].lesTocoControlAntiDoping().size()) {

                                os << ", (" << j.cronograma(d)[q].lesTocoControlAntiDoping()[l] << ", |"
                                   << j.cronograma(d)[q].leDioPositivo(j.cronograma(d)[q].lesTocoControlAntiDoping()[l])
                                   << "|)";

                                l++;

                            }

                            os << "]";

                        } else {

                            os << " [] []";

                        }


                    } else {

                        os << ")]";

                    }

                    os << ")";

                }

                os << "]";


            } else {

                os << "[]";

            }

            d++;

        }

        os << "]";

    }else {
        
        os << "]";

    }


    return os;
}

std::istream &operator>>(std::istream &is, JJOO &j) {

    j.cargar(is);

    return is;
}

bool JJOO::operator==(const JJOO &j) const {

  bool mismoAnio=(_anio==j.anio());

  unsigned int n = j.cantDias();

  bool mismaCantDias=(_cronograma.size()==n);

  bool mismaJornadaActual=( _jornadaActual==j.jornadaActual());


    bool mismosAtletas = false;

    unsigned int i = 0;

    bool atletaPertenece=true;

    if (_atletas.size() == j.atletas().size()) {

        while (i < _atletas.size() and atletaPertenece) {

            unsigned int k = 0;

            while (k < j.atletas().size() and not(_atletas[i].operator==(j.atletas()[k]))) {
                k++;

            }

            atletaPertenece = (k < j.atletas().size());

            i++;

        }

        mismosAtletas=(i==_atletas.size());

    }

    bool mismoCronograma=false;

    unsigned int q = j.cantDias();

    if(_cronograma.size()==q){

        unsigned int i=0;

        bool competenciasIguales=true;

        bool competenciaPertenece=true;

        while(i<_cronograma.size() and competenciasIguales){

          competenciasIguales=false;

            unsigned int k=0;

            while(k<_cronograma[i].size() and competenciaPertenece){


              if(_cronograma[i].size()==j.cronograma(i+1).size()){

                unsigned int l=0;


                while(l<j.cronograma(i+1).size() and not(_cronograma[i][k].operator==(j.cronograma(i+1)[l]))){

                  l++;

              }

              competenciaPertenece=(l<cronograma(i+1).size());

              k++;

            }

            competenciasIguales=(k<_cronograma[i].size());

        }

        i++;

    }

    mismoCronograma=(i<_cronograma.size());
  }

return (mismoAnio and mismaCantDias and mismaJornadaActual and mismosAtletas and mismoCronograma);
}


JJOO JJOO::operator=(const JJOO &j) {
    _anio = j._anio;
    _atletas = j._atletas;
    _cronograma = j._cronograma;
    _jornadaActual = j._jornadaActual;
    return (*this);
}
