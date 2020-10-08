#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using um = unordered_map<string, ll>;
string letras = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ";

void generaTXT(string datatxt);

void word_count(string datatxt, ll tam_bloque, 
                int i, vector<um> &palabras_de_procesos, ll ram);


int main(int argc, char **argv) 
{
    string datatxt=argv[1];//"hola.txt";
    //generaTXT(datatxt);
    
    ifstream f;
    f.open(datatxt, ios_base::ate|ios_base::binary);   
    ll tam_archivo =  f.tellg();
    f.close();
    
    int num_procesos=8;
    ll tam_bloque = ceil((float)tam_archivo/num_procesos);
    cout<<"tam_bloque="<<tam_bloque<<"\n";
    ll ram =tam_bloque; //300*1024*1024;//tam_bloque;
    
    vector<thread> procesos;
    vector<um> palabras_de_procesos(num_procesos);
    
    for(int i=0; i<num_procesos; i++){
        procesos.push_back(thread(word_count, datatxt, tam_bloque,
                             i, ref(palabras_de_procesos), ram));
    }
    
    for (auto &t:procesos){
        t.join();
    }
    
    string consulta;
    cout<<"\nConsulta: ";
    cin>>consulta;
    int frecuencia=0;
    for (auto &palabras:palabras_de_procesos){
        for (auto &palabra:palabras){
            if (palabra.first==consulta) frecuencia+=palabra.second;
        }
    }
    
    cout<<consulta<<" "<<frecuencia<<"\n";

    return 0;
}

void word_count(string datatxt, ll tam_bloque,
                int i, vector<um> &palabras_de_procesos, ll ram){
   
    ifstream f;
    f.open(datatxt);
    
    int partes = ceil((float)tam_bloque/ram);
    cout<<"partes="<<partes<<"\n";
    char *bf = new char[ram+25+1];
    
    ll puntero = tam_bloque*i;   
    for (int parte=0; parte<partes; parte++){
        ll ram_ = ram;  
        if (i==0){
            f.seekg(puntero, ios_base::beg); 
        }else{
            f.seekg(puntero-1, ios_base::beg);
            ram_++;
        }
        f.read(bf,ram+25); 
        
        stringstream ss;
        ss<<string(bf);
        
        char c;
        while (i!=0 && ss.get(c) && letras.find(c)!=string::npos){       
            continue;
        }        
        
        string palabra;
        while (ss>>palabra && ((ll)ss.tellg()-palabra.length())<ram_) {
            
            if (palabras_de_procesos[i].find(palabra) == palabras_de_procesos[i].end()){
                palabras_de_procesos[i][palabra] = 1;
            }
            else{
                palabras_de_procesos[i][palabra] += 1;  
            }
        }
        puntero = tam_bloque*i+(parte+1)*ram;
    }
    
    f.close();
    
}

void generaTXT(string datatxt){
    fstream f;
    
    f.open("el_quijote.txt", ios_base::in | ios_base::binary | ios_base::ate);
    ll tam = f.tellg();
    char *bf = new char[tam];
    
    f.seekg(0,ios_base::beg);
    f.read(bf, tam);
    f.close();
    
    f.open(datatxt, ios_base::out);
    ll veces = 1*1024*9;
    for (int i=0; i<veces; i++){
        f.write(bf, tam);
    }
    f.close();
    
    delete[] bf;
}
