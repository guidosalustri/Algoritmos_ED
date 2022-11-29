#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"
#include <fstream>
#include <iostream>

int main() {

    cout << "Hola" << endl;

    Atleta atleta("Nole", Genero::Masculino, 1983, "Serbia", 5);

    Atleta atleta2("Nora", Genero::Femenino, 1983, "Serbia", 6);


    atleta.mostrar(cout);

    ofstream archivo("Atleta1.txt");

    if (archivo.is_open()) {

        atleta.guardar(archivo);
        archivo.close();
    }

    atleta2.mostrar(cout);

    ofstream archivo5("Atleta2.txt");

    if (archivo5.is_open()) {

        atleta2.guardar(archivo5);
        archivo5.close();
    }

    Atleta a("Alexia", Genero::Femenino, 1987, "Estonia", 10);
    a.mostrar(cout);
    ifstream archivo2("Atleta2.txt");
    a.cargar(archivo2);
    archivo2.close();

    a.mostrar(cout);

    ofstream archivo1("Atleta3.txt");

    if (archivo1.is_open()) {

        a.guardar(archivo1);
        archivo1.close();
    }

    if (a.operator==(atleta2)) {
        cout << "mismos atletas" << endl;
    } else {

        cout << "distintos atletas" << endl;
    }

    vector<Atleta> atletas = {atleta, atleta2};

    Competencia comp = Competencia("Tenis", Genero::Femenino, std::vector<Atleta>());

    comp.mostrar(cout);

    ofstream archivo3("competencia1.txt");

    if (archivo3.is_open()) {

        comp.guardar(archivo3);
        archivo3.close();
    }

    Competencia comp2 = Competencia("Tenis", Genero::Femenino, atletas);

    vector<int> posiciones;

    posiciones.push_back(atleta.ciaNumber());

    posiciones.push_back(atleta2.ciaNumber());

    vector<pair<int, bool> > controles;

    bool resultTest = true;

    pair<int, bool> controlAtleta = make_pair(atleta.ciaNumber(), resultTest);

    controles.push_back(controlAtleta);

    comp2.finalizar(posiciones, controles);

    comp2.mostrar(cout);

    ofstream archivo4("competencia2.txt");

    if (archivo4.is_open()) {

        comp2.guardar(archivo4);
        archivo4.close();
    }


    ifstream archivo7("competencia2.txt");
    comp.cargar(archivo7);
    archivo7.close();
    comp.mostrar(cout);


    int anio = 2016;

    vector<Atleta> participantes = atletas;

    vector<vector<Competencia>> cronograma;

    vector<Competencia> competenciaDia1 = {comp};

    vector<Competencia> competenciaDia2 = {comp2};

    cronograma.push_back(competenciaDia1);

    cronograma.push_back(competenciaDia2);


    JJOO rio2016 = JJOO(anio, participantes, cronograma);

    rio2016.mostrar(cout);

    ofstream archivo6("jjoo.txt");

    if (archivo6.is_open()) {

        rio2016.guardar(archivo6);
        archivo6.close();

    }

      ifstream archivo8("jjoo.txt");
      rio2016.cargar(archivo8);
      archivo8.close();

    return 0;
}