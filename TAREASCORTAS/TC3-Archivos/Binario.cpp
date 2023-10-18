#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

using namespace std;

class NodoBinario {
public:
    string valor;
    string valor2;
    NodoBinario* izq;
    NodoBinario* der;

    NodoBinario(string v, string v2) {
    	valor = v;
        valor2 = v2;
        izq = NULL;
        der = NULL;
    }
};

class Binario {

public:
	NodoBinario* raiz;
    Binario() {
        raiz = NULL;
    }
    
    void Bandera(string cedula) {
    ifstream archivoEntrada("Clientes.txt");
    ofstream archivoTemporal("temp.txt");

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        if (linea.find(cedula) != string::npos) {
            linea += ";1";
            cedula = "NO AGREGAR MAS BANDERAS";
        }
        archivoTemporal << linea << endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();
    
    if (remove("Clientes.txt") != 0) {
        cout << "Error al eliminar el archivo original." << endl;
    }
    if (rename("temp.txt", "Clientes.txt") != 0) {
        cout << "Error al renombrar el archivo temporal." << endl;
    }
}

    
    NodoBinario* MenorDeMayores(NodoBinario* nodo) {
    while (nodo->izq != NULL) {
        nodo = nodo->izq;
    }
    return nodo;
	}	

    NodoBinario* EliminaNodo(NodoBinario*& R, string v) {
    	string cedula;
    	string nombre;
        if (R == NULL) {
            cout<<"El cliente "<<v<<" no se encuentra en el arbol."<<endl<<endl;
        }
        else if (stoi(v) < stoi(R->valor)) {
            EliminaNodo(R->izq, v);
        }
        else if (stoi(v) > stoi(R->valor)) {
            EliminaNodo(R->der, v);
        }
        else {
        	cedula = R->valor;
        	nombre = R->valor2;
        	
        	if(R->izq == NULL){
        		NodoBinario* temp = R->der;
        		delete R;
        		R = temp;
			}else if(R->der == NULL){
				NodoBinario* temp = R->izq;
				delete R;
				R = temp;
			}else{
        		NodoBinario* temp = MenorDeMayores(R->der);
        		R->valor = temp->valor;
        		R->valor2 = temp->valor2;
        		R->der = EliminaNodo(R->der, temp->valor);        	
        	}    	
        cout << "Cliente eliminado: "<<"\nCedula: "<<cedula<<"\nNombre: "<<nombre << endl;
        Bandera(cedula);
        }
        return R;
    }    
    
    void BuscaNodo(NodoBinario*& R, string v) {
        if (R == NULL) {
            cout<<"El cliente "<<v<<" no se encuentra en el arbol."<<endl<<endl;
        }
        else if (stoi(v) < stoi(R->valor)) {
            BuscaNodo(R->izq, v);
        }
        else if (stoi(v) > stoi(R->valor)) {
            BuscaNodo(R->der, v);
        }
        else {
            cout << "Cliente encontrado: "<<"\nCedula: "<<R->valor<<"\nNombre: "<<R->valor2 << endl;
        }
    }    

    void InsertaNodo(NodoBinario*& R, string v, string v2) {
        if (R == NULL) {
            R = new NodoBinario(v,v2);
        cout << "El cliente "<<v<<":"<<v2<<" ha sido agregado al arbol." << endl;
        }
        else if (stoi(v) < stoi(R->valor)) {
            InsertaNodo(R->izq, v,v2);
        }
        else if (stoi(v) > stoi(R->valor)) {
            InsertaNodo(R->der, v,v2);
        }
        else {
            cout << "El cliente con cedula "<<v<<" ya existe en el arbol." << endl;
        }
    }

    void PreordenR(NodoBinario* R) {
        if (R != NULL) {
            cout << R->valor<<":"<<R->valor2<< " - ";
            PreordenR(R->izq);
            PreordenR(R->der);
        }
    }

    void InordenR(NodoBinario* R) {
        if (R != NULL) {
            InordenR(R->izq);
            cout << R->valor<<":"<<R->valor2<< " - ";
            InordenR(R->der);
        }
    }

    void PostordenR(NodoBinario* R) {
        if (R != NULL) {
            PostordenR(R->izq);
            PostordenR(R->der);
            cout << R->valor<<":"<<R->valor2<< " - ";
        }
    }

    void Insertar(string v, string v2) {
        InsertaNodo(raiz, v, v2);
    }
    
    void cargaInicial(){
    Indexar();
	ifstream archivo;

	try{
	ifstream archivo("Clientes.txt");
    if (!archivo.is_open())
        cout << "Error al abrir el archivo." << endl;

    ofstream archivoNuevo("Clientes_temp.txt");
    if (!archivoNuevo.is_open())
        cout << "Error al crear el archivo temporal." << endl;

    string codigo;
    string pais;
    while (getline(archivo, codigo, ';')) {
        getline(archivo, pais);
        if (!codigo.empty() && pais.find(";1") != pais.length() - 2) {
        	this->Insertar(codigo,pais);
            archivoNuevo << codigo << ";" << pais << endl;
        }
    }

    archivo.close();
    archivoNuevo.close();

    if (remove("Clientes.txt") != 0) {
        cout << "Error al eliminar el archivo original." << endl;
    }
    if (rename("Clientes_temp.txt", "Clientes.txt") != 0) {
        cout << "Error al renombrar el archivo temporal." << endl;
    }

    cout << endl << "*********************************************************************************" << endl << endl;
    
		} catch(const std::exception &e) {
	        std::cerr << "Error: " << e.what() << std::endl;
	        return ; 
	    }
	    
	
}	


void Purgar(){
	ifstream archivo;

	try{
	ifstream archivo("Clientes.txt");
    if (!archivo.is_open())
        cout << "Error al abrir el archivo." << endl;

    ofstream archivoNuevo("Clientes_temp.txt");
    if (!archivoNuevo.is_open())
        cout << "Error al crear el archivo temporal." << endl;

    string codigo;
    string pais;
    while (getline(archivo, codigo, ';')) {
        getline(archivo, pais);
        if (!codigo.empty() && pais.find(";1") != pais.length() - 2) {
            archivoNuevo << codigo << ";" << pais << endl;
        }else{
        	cout<<"Cliente purgado: "<< codigo << ";" << pais<<endl;
		}
    }

    archivo.close();
    archivoNuevo.close();

    if (remove("Clientes.txt") != 0) {
        cout << "Error al eliminar el archivo original." << endl;
    }
    if (rename("Clientes_temp.txt", "Clientes.txt") != 0) {
        cout << "Error al renombrar el archivo temporal." << endl;
    }

    cout << endl << "*********************************************************************************" << endl << endl;
    
		} catch(const std::exception &e) {
	        std::cerr << "Error: " << e.what() << std::endl;
	        return ; 
	    }
	    
	
}	
	
	//Indexar
void Indexar() {
    map<int, pair<string, set<string>>> Indices;
    int Indice = 1;

    try {
        ifstream archivo("Clientes.txt");
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo." <<endl<<endl;
            return;
        }

        string cedula;
        string nombre;
        while (getline(archivo, cedula, ';') && getline(archivo, nombre)) {
        	if (!cedula.empty() && nombre.find(";1") != nombre.length() - 2){
    
            if (!cedula.empty()) {
                bool repetido = false;
			for (pair<const int, pair<string, set<string>>>& pair : Indices) {
    			if (pair.second.first == cedula) {
        		repetido = true;
        		break;
    			}
			}

                if (repetido == false) {
                    Indices[Indice] = make_pair(cedula, set<string>{nombre});
                    Indice++;
                }
            }
        }
        }
        archivo.close();

        ofstream archivoIndices("Indices.txt");
        if (!archivoIndices.is_open()) {
            cout << "Error al crear el archivo temporal." <<endl<<endl;
            return;
        }

        for (const auto& pair : Indices) {
            archivoIndices << pair.first << ";" << pair.second.first <<endl;
        }

        archivoIndices.close();

        cout << endl << "\nSe han indexado los datos y guardado en Indices.txt." <<endl<<endl;

    } catch(const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    return 0;
}
	void Menu(){
	while(true){
	    cout << endl << "----------------------------" << endl;
        cout << endl << "      Menu Principal  " << endl;
        cout << endl << "----------------------------" << endl;
		cout << endl;
		cout << "1. Buscar Cliente"<<endl;
		cout << "2. Insertar Cliente"<<endl;
		cout << "3. Eliminar Cliente"<<endl;
		cout << "4. Purgar Archivo Clientes"<<endl;
		cout << "5. Reindexar Clientes"<<endl;
		cout << "6. Imprimir Arbol Clientes"<<endl;
		cout << "7. Imprimir Cache"<<endl;
		cout << "8. Salir"<<endl;
		cout <<endl<<endl;
		cout <<"Seleccione una opcion: ";
		
		char opt;
		cin >> opt;
    
    switch(opt) {
    	case '1' : 
			SubMenu1();
			Menu();
			break;
    	case '2':
    		SubMenu2();
    		Menu();
    		break;
    	case '3':
    		SubMenu3();
    		Menu();
			break;
    	case '4':
    		SubMenu4();
    		Menu();
    		break;
    	case '5':
    		SubMenu5();
    		Menu();
			break;
		case '6':
    		SubMenu6();
    		Menu();
			break;
		case '7':
    		cout<<"Ingresando a Submenu 7..."<<endl;
    		Menu();
			break;
		case '8':
    		cout<<endl<<endl<<endl<<"##################      Good Bye!!     ####################"<<endl;
    		exit(1);
			break;		
    default: 
    cout<<"!!! Valor incorrecto, ingresar un valor dentro del rango !!!"<<endl;
	Menu();
	}
	break;
	}
	}
	
	//Menu Buscar Cliente
	void SubMenu1(){
		cout<<"Digite la cedula que desea buscar: "<<endl;
		string cedula;
		cin >> cedula;
		this->BuscaNodo(raiz, cedula);
		cout<<endl<<endl;
		this->PreordenR(raiz);		
		//AQUI VA PARA ACTUALIZAR LA CACHE
		//AQUI VA PARA IMPRIMIR CACHE
	}
	
	//Menu Insertar Cliente
	void SubMenu2(){
		cout<<"Digite la cedula que desea insertar: "<<endl;
		string cedula;
		cin >> cedula;
		cout<<"Digite el nombre del cliente: "<<endl;
		string nombre;
		cin.ignore();
		getline(cin, nombre);
		this->Insertar(cedula,nombre);
		cout<<endl<<endl;
		cout<<"\n\t .:Arbol:."<<endl<<endl;
		this->PreordenR(raiz);	
		cout<<"\n\t .:Cache:."<<endl<<endl;
		//AQUI VA PARA IMPRIMIR CACHE
	}
	
	//Menu Eliminar Cliente	
	void SubMenu3(){
		cout<<"Digite la cedula que desea eliminar: "<<endl;
		string cedula;
		cin >> cedula;
		this->EliminaNodo(raiz, cedula);
		cout<<endl<<endl;
		cout<<"\n\t .:Arbol:."<<endl<<endl;
		this->PreordenR(raiz);	
		cout<<"\n\t .:Cache:."<<endl<<endl;
		//AQUI VA PARA IMPRIMIR CACHE
	}
	
	//Menu Purgar Archivo
	void SubMenu4(){
		cout<<"\t .:Purgar Archivo Clientes.txt:. "<<endl;
		cout<<"\n\t .:Arbol:."<<endl<<endl;
		Purgar();
		this->PreordenR(raiz);
		cout<<"\n\t .:Cache:."<<endl<<endl;
		//AQUI VA PARA IMPRIMIR CACHE
		
	}
	
	//Menu Reindexar Clientes
	void SubMenu5(){
		cout<<"\t .:Reindexar Clientes:. "<<endl;
		cout<<"\n\n\t .:Arbol:."<<endl<<endl;
		this->PreordenR(raiz);
		this->Indexar();
		cout<<"\n\n\t .:Cache:."<<endl<<endl;
		//AQUI VA PARA IMPRIMIR CACHE
	}
	
	//Menu Imprimir Arbol
	void SubMenu6(){
		cout<<"\t .:Imprimiendo Arbol:. "<<endl<<endl;
		this->PreordenR(raiz);
	}
	
	//Menu Imprimir Cache
	void SubMenu7(){
		cout<<"\t .:Imprimiendo Cache:. "<<endl<<endl;
		//AQUI IMPRIME LA CACHE
	}
	
};

int main() {
    Binario arbol;
    arbol.cargaInicial();
    arbol.Menu();
    
    
    
  /* 
    
    cout<<endl<<endl<<endl;
    arbol.Insertar("5","A");
    arbol.Insertar("3","B");
    arbol.Insertar("7","C");
    arbol.Insertar("1","D");
    arbol.Insertar("4","E");
    arbol.Insertar("6","F");
    arbol.Insertar("8","G");

    cout << "Preorden: ";
    arbol.PreordenR(arbol.raiz);
    cout << endl;

    cout << "Inorden: ";
    arbol.InordenR(arbol.raiz);
    cout << endl;

    cout << "Postorden: ";
    arbol.PostordenR(arbol.raiz);
    cout << endl;
*/
    return 0;
}
