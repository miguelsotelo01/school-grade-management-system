#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <cstdlib>
#include <limits>
#include <algorithm>

using namespace std;

struct Estudiante {
    string nombre;
    string apellido;
    string dni;
    float notas[3] = {0.0f, 0.0f, 0.0f}; 
    bool notas_cargadas = false;
    float nota_complementaria = 0.0f;
    float promedio_final = 0.0f;
    bool necesita_complementaria = false;
};


void mostrarMenu();
void ingresarEstudiante(vector<Estudiante>& estudiantes);
void cargarNotas(vector<Estudiante>& estudiantes);
void mostrarEstadisticasTrimestre(const vector<Estudiante>& estudiantes);
void generarInstanciaComplementaria(vector<Estudiante>& estudiantes);
void mostrarReporte(const vector<Estudiante>& estudiantes);
void exportarReporte(const vector<Estudiante>& estudiantes);
void manejarReportes(const vector<Estudiante>& estudiantes);
void calcularPromedioFinal(Estudiante& estudiante);

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    vector<Estudiante> estudiantes;
    int opcion;

    do {
        mostrarMenu();
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1: 
                ingresarEstudiante(estudiantes); 
                break;
            case 2: 
                cargarNotas(estudiantes); 
                break;
            case 3: 
                mostrarEstadisticasTrimestre(estudiantes); 
                break;
            case 4: 
                generarInstanciaComplementaria(estudiantes); 
                break;
            case 5:
                manejarReportes(estudiantes);
                break;
            case 6: 
                cout << "Saliendo del sistema...\n"; 
                break;
            default: 
                cout << "Opción invalida!\n";
        }
    } while(opcion != 6);

    return 0;
}

void mostrarMenu() {
    cout << "\n===== Sistema de Gestion Academica ====="
         << "\n1. Ingresar datos del estudiante"
         << "\n2. Cargar notas del trimestre"
         << "\n3. Ver estadisticas por trimestre"
         << "\n4. Generar instancia complementaria"
         << "\n5. Reportes"
         << "\n6. Salir\n";
}

void ingresarEstudiante(vector<Estudiante>& estudiantes) {
    Estudiante nuevo;
    cout << "\n=== Ingreso de Nuevo Estudiante ==="
         << "\nNombre: ";
    getline(cin, nuevo.nombre);
    cout << "Apellido: ";
    getline(cin, nuevo.apellido);
    cout << "DNI: ";
    getline(cin, nuevo.dni);
    
    estudiantes.push_back(nuevo);
    cout << "Estudiante registrado exitosamente!\n";
}

void cargarNotas(vector<Estudiante>& estudiantes) {
    if(estudiantes.empty()) {
        cout << "No hay estudiantes registrados!\n";
        return;
    }

    cout << "\n=== Carga de Notas ===";
    for(auto& est : estudiantes) {
        cout << "\nEstudiante: " << est.nombre << " " << est.apellido;
        for(int i = 0; i < 3; i++) {
            cout << "\nIngrese nota para el trimestre " << (i+1) << " (0-10): ";
            cin >> est.notas[i];
        }
        est.notas_cargadas = true;
        calcularPromedioFinal(est);
    }
    cout << "Notas cargadas exitosamente!\n";
}

void calcularPromedioFinal(Estudiante& estudiante) {
    float suma = 0;
    for(int i = 0; i < 3; i++) {
        suma += estudiante.notas[i];
    }
    estudiante.promedio_final = suma / 3;
    estudiante.necesita_complementaria = estudiante.promedio_final < 6.0;
}

void generarInstanciaComplementaria(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados!\n";
        return;
    }

    cout << "\n=== Carga de Nota Complementaria ===";
    for (auto& est : estudiantes) {
        if (est.necesita_complementaria) {
            cout << "\nEstudiante: " << est.nombre << " " << est.apellido
                 << "\nPromedio actual: " << est.promedio_final
                 << "\nIngrese nota complementaria (0-10): ";
            cin >> est.nota_complementaria;
           
            est.promedio_final = max(est.promedio_final, est.nota_complementaria);
        }
    }
    cout << "Notas complementarias cargadas!\n";
}

void mostrarEstadisticasTrimestre(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados!\n";
        return;
    }
    
    cout << "\n=== Estadisticas por Trimestre ===";
    for (const auto& est : estudiantes) {
        cout << "\nEstudiante: " << est.nombre << " " << est.apellido
             << "\nDNI: " << est.dni
             << "\nNotas por trimestre: " << est.notas[0] << " " << est.notas[1] << " " << est.notas[2]
             << "\nNota complementaria: " << est.nota_complementaria
             << "\nPromedio final: " << fixed << setprecision(2) << est.promedio_final
             << "\nEstado: " << (est.promedio_final >= 6.0 ? "APROBADO" : "REPROBADO") << "\n";
    }
}


void mostrarReporte(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados!\n";
        return;
    }
    
    cout << "\n=== Reporte Academico ===";
    for (const auto& est : estudiantes) {
        cout << "\nEstudiante: " << est.nombre << " " << est.apellido
             << "\nDNI: " << est.dni
             << "\nNotas: " << est.notas[0] << ", " << est.notas[1] << ", " << est.notas[2]
             << "\nNota complementaria: " << est.nota_complementaria
             << "\nPromedio final: " << fixed << setprecision(2) << est.promedio_final
             << "\nEstado: " << (est.promedio_final >= 6.0 ? "APROBADO" : "REPROBADO") << "\n";
    }
}


void exportarReporte(const vector<Estudiante>& estudiantes) {
    ofstream archivo("reporte_academico.csv");
    if (!archivo) {
        cout << "Error al crear el archivo de reporte.\n";
        return;
    }
    
    archivo << "Nombre,Apellido,DNI,Trim1,Trim2,Trim3,Complementaria,Promedio,Estado\n";
    for (const auto& est : estudiantes) {
        archivo << est.nombre << ","
                << est.apellido << ","
                << est.dni << ","
                << est.notas[0] << ","
                << est.notas[1] << ","
                << est.notas[2] << ","
                << est.nota_complementaria << ","
                << fixed << setprecision(2) << est.promedio_final << ","
                << (est.promedio_final >= 6.0 ? "Aprobado" : "Reprobado") << "\n";
    }
    archivo.close();
    cout << "Reporte exportado como 'reporte_academico.csv'.\n";
}


void manejarReportes(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados!\n";
        return;
    }
    
    int opcionReporte;
    cout << "\n=== Menu de Reportes ===\n"
         << "1. Mostrar reporte en pantalla\n"
         << "2. Exportar reporte a CSV\n"
         << "3. Mostrar y exportar reporte\n"
         << "4. Cancelar\n"
         << "Ingrese una opcion: ";
    cin >> opcionReporte;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (opcionReporte) {
        case 1:
            mostrarReporte(estudiantes);
            break;
        case 2:
            exportarReporte(estudiantes);
            break;
        case 3:
            mostrarReporte(estudiantes);
            exportarReporte(estudiantes);
            break;
        case 4:
            cout << "Operación cancelada.\n";
            break;
        default:
            cout << "Opcion invalida en el menu de reportes.\n";
    }
}
