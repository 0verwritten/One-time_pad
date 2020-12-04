#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


bool save(string path, string key, string text){

    ofstream writer;

    writer.open(path);

    writer << key << endl << text;

    writer.close();

    return true;
}

void restore(string path, string* key, string* text){

    ifstream reader;

    reader.open(path, ios::in);

    if(reader){
        reader >> (*key);
        reader >> (*text);

    }
    reader.close();
}

void encrypt(bool autoSave, string path){
    string text;
    cout <<"Enter your text ( only letters without spaces ): ";
    cin >> text;
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    cout<<"\nKey:";

    int* key = new int(text.length());
    string keyLine;

    // encrypt
    for(int i = 0;i<text.length();i++){
        int a;
        key[i] = rand()%26+1;
        a = int(text[i])-65;
        int calculation = a+key[i];
        text[i] = char(calculation % 26 + 65);
        cout<<char(key[i]+65);
        keyLine += char(key[i]+65);
    }

    if(autoSave){
        save(path, keyLine, text);
    }

    cout<<endl<<text<<endl;

    delete key;
}

void decrypt(bool autoRestore, string path){
    string text;
    string key;
    if(autoRestore){

        restore(path, &key, &text);

    }
    else{

        cout << "Enter encoded text: ";
        cin >> text;
        transform(text.begin(), text.end(), text.begin(), ::toupper);

        cout << "Enter your key: ";
        cin >> key;

    }

    for(int i = 0;i<text.length();i++){
        int a = int(text[i])-65;
        int k = int(key[i])-65;
        int calculation = (a-k) < 0 ? 26 + (a-k) : (a-k);
        text[i] = char(calculation + 65);
    }
    cout << endl << text << endl;


}

int main(int argN, char* args[]){

    srand(time(NULL));

    string path = "";
    bool    save = false,
            restore = false;

    for( int i = 1;i < argN; i++ ){
        if( string("-o").compare(args[i]) == 0 && argN != i + 1 ){
            path = args[i+1];
            save = true;
        }
        else if( string("-i").compare(args[i]) == 0 && argN != i + 1 ){
            path = args[i+1];
            restore = true;
        }
    }

    char ans;
    cout << "Decrypt or encrypt (D/E) ";
    cin >> ans;
    ans = toupper(ans);
    if(ans == 'D')
        decrypt( restore, path);
    else if(ans == 'E')
        encrypt( save, path );
    

    return 0;
}