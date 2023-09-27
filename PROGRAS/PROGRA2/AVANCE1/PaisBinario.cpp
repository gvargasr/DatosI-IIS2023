#include <iostream>
#include "Pila.cpp"
#include "NodoBinario.h"
#include "Binario.h"
#include <string>

using namespace std;

void NodoBinario::InsertaBinario(int num, string pais)
{
    if(num < valor){
        if(Hizq == NULL){
            Hizq = new NodoBinario(num, pais);
        }else{
            Hizq->InsertaBinario(num, pais);
        }
    }else{
        if(Hder == NULL){
            Hder = new NodoBinario(num, pais);
        }else{
            Hder->InsertaBinario(num, pais);
        }
    }
}

void Binario::InsertaNodo(int num, string pais)
{
    if(raiz == NULL){
        raiz = new NodoBinario(num, pais);
    }else{
        raiz->InsertaBinario(num, pais);
    }
}

void Binario::PreordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    while(!p.Vacia() || (Act != NULL)){
        if(Act != NULL){
            cout << Act->valor<<":"<<Act->pais << " - ";
            p.Push(Act);
            Act = Act->Hizq;
        }else{
            Act = p.Pop();
            Act = Act->Hder;
        }
    }
}

void Binario::InordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    bool band = true;
    while(band){

        while(Act != NULL){
            p.Push(Act);
            Act = Act->Hizq;
        }
        if(!p.Vacia()){
            Act = p.Pop();
            cout << Act->valor<<":"<<Act->pais << " - ";
            Act = Act->Hder;
        }
        if(p.Vacia() && Act == NULL){
            break;
        }
    }
}

void Binario::PostordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    Pila p2;
    while(!p.Vacia() || Act != NULL){
        if(Act != NULL){
            p2.Push(new NodoBinario(Act->valor, Act->pais));
            p.Push(Act);
            Act = Act->Hder;
        }else{
            Act = p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinario *salida = p2.Pop();
        cout << Act->valor<<":"<<Act->pais << " - ";
    }
}

void PreordenR(NodoBinario *R){

    if(R == NULL){
        return;
    }else{
        cout << R->valor << " - ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InordenR(NodoBinario *R){

    if(R == NULL){
        return;
    }else{
        InordenR(R->Hizq);
        cout << R->valor << " - ";
        InordenR(R->Hder);
    }
}

void Binario::PostordenR(NodoBinario *R){

    if(R == NULL){
        return;
    }else{
        PostordenR(R->Hizq);
        PostordenR(R->Hder);
        cout << R->valor << " - ";
    }
}

void Binario::Borrar(NodoBinario* &D, bool Hh)
{
    NodoBinario *q;
    if(D->Hder != NULL){
        Borrar(D->Hder, Hh);
        if(Hh){
            Equilibrar2(D, Hh);
        }else{
            q->valor = D->valor;
            q = D;
            D = D->Hizq;
            Hh = true;
        }
    }
}

void Binario::BorrarBalanceado(NodoBinario* &raiz, bool &Hh, int x)
{
    NodoBinario *q;
    if(raiz != NULL){
        if(x < raiz->valor){
            BorrarBalanceado(raiz->Hizq, Hh, x);
            if(Hh){
                Equilibrar1(raiz, Hh);
            }
        }else{
            if(x > raiz->valor){
                BorrarBalanceado(raiz->Hder, Hh, x);
                if(Hh){
                    Equilibrar2(raiz, Hh);
                }
            }else{
                q = raiz;

                if(q->Hder == NULL){
                    raiz = q->Hizq;
                    Hh = true;
                }else{
                    if(q->Hizq == NULL){
                        raiz = q->Hder;
                        Hh = true;
                    }else{
                        Borrar(q->Hizq, Hh);
                    }
                    if(Hh){
                        Equilibrar1(raiz, Hh);
                    }
                }
            }
        }
    }
}

void Binario::Equilibrar1(NodoBinario* &n, bool &Hh){
    NodoBinario *n1;
    switch (n->FB){
        case -1: n->FB = 0;
        break;
        case 0: n->FB = 1;
        Hh = false;
        break;
        case 1: n1 = n->Hder;
        if(n1->FB >= 0){
            if(n1->FB == 0){
                Hh = false;
                RotacionSimpleDerecha(n, n1);
            }else{
                RotacionDobleDerecha(n, n1);
            }
        }
    }
}

void Binario::Equilibrar2(NodoBinario* &n, bool &Hh){
    NodoBinario *n1;
    switch (n->FB){
        case 1: n->FB = 0;
        break;
        case 0: n->FB = 1;
        Hh = false;
        break;
        case -1: n1 = n->Hizq;
        if(n1->FB <= 0){
            if(n1->FB == 0){
                Hh = false;
                RotacionSimpleIzquierda(n, n1);
            }else{
                RotacionDobleIzquierda(n, n1);
            }
        }
    }
}

void Binario::InsertarBalanceado(NodoBinario* &ra, bool &Hh, int x, string nombre){
    pNodoBinario n1;

    if(ra == NULL){
        ra = new NodoBinario(x, nombre);
        cout << ra->valor << "q as" << endl;
        Hh = true;
    }else{
        cout << "q as2" << endl;
        if(x < ra->valor){
            InsertarBalanceado(ra->Hizq, Hh, x, nombre);

            if(Hh){
                switch(ra->FB){
                    case 1: ra->FB = 0;
                    Hh = false;
                    break;
                    case 0: ra->FB = -1;
                    break;
                    case -1: n1 = ra->Hizq;
                    if(n1->FB == -1){
                        RotacionSimpleIzquierda(ra, n1);
                    }else{
                        RotacionDobleIzquierda(ra, n1);
                    }
                    Hh = false;
                    break;
                }
            }
        }else{
            if(x > ra->valor){
                cout << "Hh:" << Hh << endl;
                InsertarBalanceado(ra->Hder, Hh, x, nombre);

                if(Hh){
                    switch(ra->FB){
                        case -1: ra->FB = 0;
                        Hh = false;
                        cout << "sw-1" << endl;
                        break;
                        case 0: ra->FB = 1;
                        cout << "sw0" << endl;
                        break;
                        case 1: n1 = ra->Hder;
                        cout << "sw1" << endl;
                        if(n1->FB == 1){
                            RotacionSimpleDerecha(ra, n1);
                        }else{
                            RotacionDobleDerecha(ra, n1);
                        }
                        Hh = false;
                        break;
                    }
                }
            }
        }
    }
}

void Binario::RotacionDobleIzquierda(NodoBinario* &n, NodoBinario* &n1){
    NodoBinario *n2;
    n2 = n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder = n;
    n1->Hder = n2->Hizq;
    n2->Hizq = n1;

    if(n2->FB == 1){
        n1->FB = -1;
    }else{
        n1->FB = 0;
    }
    if(n2->FB == -1){
        n->FB = 1;
    }else{
        n->FB = 0;
    }
    n2->FB = 0;
    n = n2;
}

void Binario::RotacionDobleDerecha(NodoBinario* &n, NodoBinario* &n1){
    NodoBinario *n2;
    n2 = n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq = n;
    n1->Hizq = n2->Hder;
    n2->Hder = n1;

    if(n2->FB == 1){
        n->FB = -1;
    }else{
        n->FB = 0;
    }
    if(n2->FB == -1){
        n1->FB = 1;
    }else{
        n1->FB = 0;
    }
    n2->FB = 0;
    n = n2;
}

void Binario::RotacionSimpleDerecha(NodoBinario* &n, NodoBinario* &n1){
    n->Hder = n1->Hizq;
    n1->Hizq = n;

    if(n1->FB == 1){
        n->FB = 0;
        n1->FB = 0;
    }else{
        n->FB = 1;
        n1->FB = -1;
    }
    n = n1;
}

void Binario::RotacionSimpleIzquierda(NodoBinario* &n, NodoBinario* &n1){
    n->Hizq = n1->Hder;
    n1->Hder = n;

    if(n1->FB == -1){
        n->FB = 0;
        n1->FB = 0;
    }else{
        n->FB = -1;
        n1->FB = -1;
    }
    n = n1;
}
