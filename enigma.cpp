#include <iostream>
#include <map>

using namespace std;

int rotor1[] = {5,17,0,25,23, 8,21,12,9,14, 20,1,3,15,4, 18,19,6,10,7, 11,2,13,16,22, 24};
int rotor2[] = {18,10,4,0,9, 15,1,19,25,8, 20,14,13,7,12, 5,3,21,24,17, 11,22,2,16,6, 23};
int rotor3[] = {13,6,20,24,10, 16,23,9,7,5, 19,12,0,22,3, 18,11,4,17,21, 15,1,2,8,25, 14};
int reflector[] = {8,18,7,15,9,24,10,2,0,4,6,16,17,21,25,3,11,12,1,22,23,13,19,20,5,14};
int* rotorPosition[] = {rotor1,rotor2,rotor3};
int rotorConfiguration[] = {0,0,0};
int plugboardMasking[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
map<int,int> plugboard;

void updatePlugboard(char a, char b){
    if(plugboard.size() == 20){
        cout << "You have ran out of plugs.\n";
        return;
    }

    if(plugboard[a - 97] != NULL){
        cout << a;
        cout << " has already been plugged.\n";
        return;
    }

    if(plugboard[b - 97] != NULL){
        cout << b;
        cout << " has already been plugged.\n";
        return;
    }

    if(a == b){
        cout << "you cannot plug a letter to itself. \n";
        return;
    }

    plugboard[a - 96] = b - 96;
    plugboard[b - 96] = a - 96;
}

void MaskPlugboard(){
    for(char i = 0; i < 26; i++){
        if(plugboard[i+1] != 0){
            plugboardMasking[i] = plugboard[i+1]-1;
        }
    }
}

void reflectedRoute(int cur, int rotor[]){

}

int encode(int input){
    int cur = input - 97;
    rotorConfiguration[2] = (rotorConfiguration[2] + 1)%26;
    if(rotorConfiguration[2] == 0){
        rotorConfiguration[1] = (rotorConfiguration[1] + 1)%26;
        if(rotorConfiguration[1] == 0){
            rotorConfiguration[0] = (rotorConfiguration[0] + 1)%26;
        }
    }

    cur = plugboardMasking[cur];
    cur =  *(rotorPosition[2] + (rotorConfiguration[2] + cur)% 26);    
    cur =  *(rotorPosition[1] + (rotorConfiguration[1] + cur)% 26);
    cur =  *(rotorPosition[0] + (rotorConfiguration[0] + cur)% 26);
    cur = reflector[cur];

    for(int i = 0; i < 26; ++i){
        if( *(rotorPosition[0] + i) == cur){
            cur = i - rotorConfiguration[0];
            if(cur < 0){
                cur = 26 + cur;
            }
            break;
        }
    }

    for(int i = 0; i < 26; ++i){
        if( *(rotorPosition[1] + i) == cur){
            cur = i - rotorConfiguration[1];
            if(cur < 0){
                cur = 26 + cur;
            }
            break;
        }
    }

    for(int i = 0; i < 26; ++i){
        if( *(rotorPosition[2] + i) == cur){
            cur = i - rotorConfiguration[2];
            if(cur < 0){
                cur = 26 + cur;
            }
            break;
        }
    }

    cur = plugboardMasking[cur];
    return cur; 
}

void resetRotors(){
    rotorConfiguration[0] = 0;
    rotorConfiguration[1] = 0;
    rotorConfiguration[2] = 0;
    cout << "Rotors resetted. \n";
}

int main(){
    string b = "bswtxmqcsqrbtuqafqynocvlrqrpxaqlmqvsnv";
    string result;

    for(int i = 0; i < b.size(); ++i){
        result = result + (char)((encode(b[i])) + 97);
    }

    cout << "origional: ";
    cout << b << endl;
    cout << "encrypted: ";
    cout << result << endl;

    string decrypted;

    resetRotors();

    for(int i = 0; i < result.size(); ++i){
        decrypted = decrypted + (char)((encode(result[i])) + 97);
    }   
    
    cout << "decrypted: ";
    cout << decrypted << endl;


}