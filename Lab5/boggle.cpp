#include <iostream>
#include "lexicon.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Boggle{
private:
    int size;
public:
    char **checkboard;
    int score;
    Lexicon Unfinded_word;
    int AIscore = 0;
    string filename = "EnglishWords.txt";
    Lexicon eLexicon;

    std::vector<std::string> Finded_Word;
    Boggle();
    Boggle(int N);
    ~Boggle();
    bool check(std::string word);
    bool findPath(std::string word);
    void AIround();
    void AIfound(int i,int j,string Word,bool **mark);
    bool solvePath(int i,int j,std::string word,int wordPos,bool **mark);
    void Print();
    bool checkFounded(string word);
   };


    Boggle::Boggle(int N){
        size = N;
        checkboard = new char* [N];
        for(int i = 0; i < size; ++i){
            checkboard[i] = new char [N];
        }
        eLexicon.addWordsFromFile("EnglishWords.txt");
        score = 0;
   }

   Boggle::~Boggle(){
       for(int i = 0;i < size; ++i){ 
           delete [] checkboard[i];
       }
       delete [] checkboard;
   }

   bool Boggle::check(std::string word){
       if(word.size() < 4){
        std::cout << word << " is too short." << endl;
        return false;
       }
       if(!eLexicon.contains(word)){
           std::cout << word << " is not a word." << endl;
           return false;
       }
        if(!findPath(word)){
            std::cout << word << " is not on board." << endl;
            return false;
        }
        for(int i = 0; i < Finded_Word.size(); ++i){
            if(Finded_Word[i] == word){
                std::cout << word << " is already found." << endl;
                return false;
            }
        }
        return true;
   }

   bool Boggle::solvePath(int i,int j,std::string word,int wordPos,bool **mark){
       if(wordPos == word.size()) return true;
       mark[i][j] = true;
       if(i - 1 >= 0){
           if(j - 1 >= 0 && !mark[i - 1][j - 1] && checkboard[i - 1][j - 1] == word[wordPos]){
               if(solvePath(i - 1,j - 1,word,wordPos++,mark));
               {
                   return true;
               }
           }
           if(!mark[i - 1][j] && checkboard[i - 1][j] == word[wordPos]){
               if(solvePath(i - 1,j,word,wordPos++,mark)){
                   return true;
               }
           }
           if(j + 1 < size && !mark[i - 1][j + 1] && checkboard[i - 1][j + 1] == word[wordPos]){
               if(solvePath(i - 1,j + 1,word,wordPos++,mark))
               return true;
           }
       }
       if(j - 1 >= 0 && !mark[i][j - 1] && checkboard[i][j - 1] == word[wordPos]){
           if(solvePath(i,j - 1,word,wordPos++,mark));
           return true;
       }
       if(j + 1 < size && !mark[i][j + 1] && checkboard[i][j + 1] == word[wordPos]){
           if(solvePath(i,j + 1,word,wordPos++,mark));
           return true;
       }
       if(i + 1 < size){
           if(j - 1 >= 0 && !mark[i + 1][j - 1] && checkboard[i + 1][j - 1] == word[wordPos]){
               if(solvePath(i + 1,j - 1,word,wordPos++,mark));
               {
                   return true;
               }
           }
           if(!mark[i + 1][j] && checkboard[i + 1][j] == word[wordPos]){
               if(solvePath(i + 1,j,word,wordPos++,mark)){
                   return true;
               }
           }
           if(j + 1 < size && !mark[i + 1][j + 1] && checkboard[i + 1][j + 1] == word[wordPos]){
               if(solvePath(i + 1,j + 1,word,wordPos++,mark));
               return true;
           }
       }
       mark[i][j] = false;
       return false;
   }

   bool Boggle::findPath(std::string word){
       bool **mark;
       mark = new bool* [size];
       transform(word.begin(),word.end(),word.begin(),::toupper);
        for(int i = 0; i < size; ++i){
            mark[i] = new bool [size];
            for(int j = 0; j < size; ++j){
                mark[i][j] = false;
            }
        }
       for(int i = 0;i < size; ++i){
           for(int j = 0;j < size; ++j){
               if(checkboard[i][j] == word[0]){
                    if(solvePath(i,j,word,1,mark)){
                        return true;
                    }
           }
       }
       }
       for(int k = 0; k < size; ++ k){
           delete [] mark[k];
       }
       delete [] mark;
       return false;
   }


   void Boggle::Print(){
       for(int i = 0; i < size; ++i){
           cout << checkboard[i] << endl;
       }
       cout << "Your Score: " << score << endl;
       cout << "Your Words: ";
       for(int i = 0;i < Finded_Word.size();++i){
           cout << Finded_Word[i] << " ";
       }
       cout << endl;
   }

   bool Boggle::checkFounded(string word){
       transform(word.begin(),word.end(),word.begin(),::tolower);
       for(int i = 0;i < Finded_Word.size();++i){
           if(Finded_Word[i] == word) return true;
       }
       return  false;
   }

   void Boggle::AIfound(int i, int j, string Word, bool **mark){
       Word += checkboard[i][j];
       if(!eLexicon.containsPrefix(Word)) return;
       if(Word.size() >= 4 && eLexicon.contains(Word) && !checkFounded(Word)){
               Unfinded_word.add(Word);
       }
       mark[i][j] = true;
       if(i - 1 >= 0){
           if(j - 1 >= 0 && !mark[i - 1][j - 1]){
               AIfound(i - 1,j - 1,Word,mark);
           }
           if(!mark[i - 1][j]){
               AIfound(i - 1,j,Word,mark);
           }
           if(j + 1 < size && !mark[i - 1][j + 1]){
               AIfound(i - 1,j + 1,Word,mark);
           }
       }
       if(j - 1 >= 0 && !mark[i][j - 1]){
           AIfound(i,j - 1,Word,mark);
       }
       if(j + 1 < size && !mark[i][j + 1]){
           AIfound(i,j + 1,Word,mark);
       }
       if(i + 1 < size){
           if(j - 1 >= 0 && !mark[i + 1][j - 1]){
               AIfound(i + 1,j - 1,Word,mark);
           }
           if(!mark[i + 1][j]){
               AIfound(i + 1,j,Word,mark);
           }
           if(j + 1 < size && !mark[i + 1][j + 1]){
               AIfound(i + 1,j + 1,Word,mark);
            }
       }
       mark[i][j] = false;
       return;
   }

    void Boggle::AIround(){
        for(int i = 0;i < size; ++i){
            for(int j = 0;j < size; ++j){
                bool **mark;
                mark = new bool* [size];
                 for(int i = 0; i < size; ++i){
                     mark[i] = new bool [size];
                     for(int j = 0; j < size; ++j){
                         mark[i][j] = false;
                     }
                 }
                 string Word;
                 AIfound(i,j,Word,mark);
                 for(int k = 0;k < size; ++k){
                     delete [] mark[k];
                 }
                 delete [] mark;
            }
        }
        for(auto i: Unfinded_word){
            AIscore += i.size() - 3;
        }
        cout << "Computer Score: " << AIscore << endl;
        cout << "Computer Words: ";
        for(auto i : Unfinded_word){
            transform(i.begin(),i.end(),i.begin(),::toupper);
            cout << i << " ";
        }
    }

int main(){
    int N;
    cin >> N;
    Boggle B(N);
    for(int i = 0;i < N; ++i){
        char *s = new char [N];
        cin >> s;
        B.checkboard[i] = s;
    }
    while(true){
        B.Print();
        string command;
        cin >> command;
        if(command == "???"){
            B.AIround();
            break;
        }
        else{
            if(B.check(command)){
                transform(command.begin(),command.end(),command.begin(),::tolower);
                B.Finded_Word.push_back(command);
                B.score += command.size() - 3;
            }
        }
    }
    return 0;
}
