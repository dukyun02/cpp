int main() {
    MyDic dic;

    // 단어 등록
    dic.add("apple", "사과");
    dic.add("banana", "바나나");
    dic.add("computer", "컴퓨터");

    // 파일로 저장
    dic.store("words.txt");

    // 새로운 객체로 불러오기 테스트
    MyDic newDic;
    newDic.load("words.txt");

    // 출력
    newDic.print();

    // 특정 인덱스 단어 테스트
    cout << "1번째 영어 단어: " << newDic.getEng(1) << endl;
    cout << "1번째 한글 설명: " << newDic.getKor(1) << endl;

    return 0;
}