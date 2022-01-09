#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int ALPHABET_SIZE = 26;

//trie node
struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];

    //isEndOfWord is true if the node represents
    bool isEndOfWord;
    string value = "";
};

//returns new trie node(initialized to NULLs)
struct TrieNode *getNode(void){
    struct TrieNode *pNode = new TrieNode;
    pNode->isEndOfWord=false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i]=NULL;
    }
    return pNode;
}

struct TrieNode *root = getNode();

// inserting new element
void insert(string key, string value){
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
            pCrawl->children[index]=getNode();
        }
        pCrawl=pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
    pCrawl->value = value;
}

// getting value of the key. it may be "". take care!
string getValue(string key){
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
            pCrawl->children[index]=getNode();
        }
        pCrawl=pCrawl->children[index];
    }
    return pCrawl->value;
}

// returns true if key presents in trie, else false
bool search(string key){
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl->isEndOfWord);
}

// searching every char in trie. if there is a word returns true. endofworld not important.
bool searchChars(string key){
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return true;
}

// just looking first char inside of root
bool searchFirstChar(string key){
    struct TrieNode *pCrawl = root;
    int index = key[0] - 'a';
    if (!pCrawl->children[index]){
        return false;
    }else {
        return true;
    }
}

//returns true if root has no children, else false
bool isEmpty(TrieNode* root){
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]){
            return false;
        }
    }
    return true;
}

TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
    if (!root)
        return NULL;

    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }
        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] =
            remove(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }
    return root;
}

int main(int argc, char *argv[]) {
    string inputTxt = argv[1];
    string outputTxt = argv[2];

    //gerekli tanımlamalar yapılacak
    ifstream file(inputTxt);
    string str;
    ofstream myfile;
    myfile.open (outputTxt);

    // tüm işlemler burada yapılacak
    while (getline(file, str))
    {
        char firstDigit = str[0];

        if (firstDigit=='i'){
            int posBracket = str.find('(');
            str = str.substr(posBracket+1,str.length()-8);
            int posComma = str.find(',');
            string key = str.substr(0,posComma);
            string value = str.substr(posComma+1,str.length()-posComma-1);
            if (search(key)){
                if (value == getValue(key)){
                    myfile << "\"" << key << "\"" << " already exist\n";
                }
                else{
                    insert(key,value);
                    myfile << "\"" << key << "\"" << " was updated\n";
                }
            }
            else{
                insert(key,value);
                myfile << "\"" << key << "\"" <<" was added\n";
            }
        }

        else if (firstDigit=='s'){
            int posBracket = str.find('(');
            string key = str.substr(posBracket+1,str.length()-8);
            //ilk karakter var mı yok mu diye bakıyoruz
            if (!searchFirstChar(key)){
                myfile << "\"no record\"\n";
            }
            // ilk karakter var ama diğer durumlara bakıyoruz. "incorrect Dothraki word" - “not enough Dothraki word”
            else{
                if (!searchChars(key)){
                    myfile << "\"incorrect Dothraki word\"\n" ;
                }
                else{
                    if (search(key)){
                        myfile << "\"The English equivalent is "<< getValue(key) << "\"\n";
                    }
                    else{
                        myfile << "\"not enough Dothraki word\"\n" ;
                    }
                }
            }
        }

        else if (firstDigit=='l'){
            myfile << "\n";
        }

        else if (firstDigit=='d'){
            int posBracket = str.find('(');
            string key = str.substr(posBracket+1,str.length()-8);

            if (!searchFirstChar(key)){
                myfile << "\"no record\"\n";
            }
            else{
                if (!searchChars(key)){
                    myfile << "\"incorrect Dothraki word\"\n";
                }
                else{
                    if (search(key)){
                        remove(root,key);
                        myfile << "\"" << key << "\" deletion is successful\n";
                    }
                    else{
                        myfile << "\"not enough Dothraki word\"\n";
                    }
                }
            }
        }
    }
    return 0;
}
