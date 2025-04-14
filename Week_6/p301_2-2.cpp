#define MAXWORDS 100

class MyDic {
    WordPair words[MAXWORDS]; // 단어 저장 배열
    int nWords;               // 현재 등록된 단어 수

public:
    MyDic() { nWords = 0; }  // 생성자에서 초기화

    inline void add(string eng, string kor) {
        if (nWords < MAXWORDS) {
            words[nWords].eng = eng;
            words[nWords].kor = kor;
            nWords++;
        }
    }

    inline void load(string filename) {
        ifstream fin(filename);
        if (!fin) {
            cout << "파일 열기 실패: " << filename << endl;
            return;
        }

        string eng, kor;
        nWords = 0;
        while (fin >> eng >> kor && nWords < MAXWORDS) {
            words[nWords].eng = eng;
            words[nWords].kor = kor;
            nWords++;
        }
        fin.close();
    }

    inline void store(string filename) {
        ofstream fout(filename);
        for (int i = 0; i < nWords; i++) {
            fout << words[i].eng << " " << words[i].kor << endl;
        }
        fout.close();
    }

    inline void print() {
        for (int i = 0; i < nWords; i++) {
            cout << i << ": " << words[i].eng << " - " << words[i].kor << endl;
        }
    }

    inline string getEng(int id) {
        if (id >= 0 && id < nWords)
            return words[id].eng;
        else
            return "";
    }

    inline string getKor(int id) {
        if (id >= 0 && id < nWords)
            return words[id].kor;
        else
            return "";
    }
};