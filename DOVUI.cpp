#include <iostream> //dauvao/ra
#include <string>	//chuoi ky tu
#include <vector>	//dsach dong
#include <conio.h>	//de sd ham _getch() cho viec doc 1 phim nguoi dung ma khong hien thi no
#include <algorithm>//de sd cac ham thuat toan nhu find
#include <ctime>	//de sd ham time
#include <cstdlib>	//de sd ham srand va exit
#include <limits>	//de sd gtri numeric_limits

//lop player
class Player {
	private:
    	char key;
    	int score;
	public:
		//key: bieu dien ki tu dai dien cho nguoi choi
		//score: diem so cua nguoi choi
  		Player(char key) : key(key), score(0) {}
  	  
  		//cac pthuc truy xuat thong tin: Ham lay ra key, lay ra diem
  	  	char getKey() const { return key; }
  	 	int getScore() const { return score; }
  	  
 	  	 //Ham tang diem
 	   	void increaseScore() { score++; }
};

//lop quizgame
class QuizGame {
	private:
    	Player player1{'a'}; //a: la ktu dai dien cho nguoi choi 1
    	Player player2{'b'}; //b: la ktu dai dien cho nguoi choi 2
   	 	int currentQuestionIndex{0}; //chi so cau hoi hien tai
    	std::vector<int> askedQuestions; // De theo doi cau hoi da hoi
    
    	//struct question de luu tru cau hoi va cau tra loi
    	struct Question {
    	    std::string question;
    	    std::string answer;
   		};
    
   		// Them cau hoi moi su dung push_back
    	std::vector<Question> questions;
    
    	//Ham hien thi diem
    	void displayScore() const;
    	//Ham hoi cau hoi ngau nhien
    	void askRandomQuestions();
    	//Ham cho nguoi choi tra loi
    	char waitForAnswer() const;
    	//Ham ktra cau tra loi
    	void checkAnswer(char answerKey);
    	//Ham cong bo nguoi chien thang
    	void announceWinner() const;
    	//Ham reset diem
    	void resetScores();
    	//Ham ktra nguoi choi co muon choi round nua khong
    	bool askToPlayAnotherRound() const;
	public:
    	QuizGame() {}  // Hàm t?o công c?ng
    	void initializeQuestions(); //Ham khoi tao cau hoi
   		void startGame(); //Ham startgame
};

//Ham khoi tao cau hoi
void QuizGame::initializeQuestions() {
	// khoi tao cau hoi sd push_back
    questions.push_back({"What is 2 + 2?", "4"});
    questions.push_back({"Bo ngoai nuong trong, an ngoai bo trong la gi?", "nuong bap ngo"});
    questions.push_back({"Benh gi bac si bo tay?", "benh gay tay"});
    questions.push_back({"Con cho den nguoi ta goi la con cho muc. Con cho vang, nguoi ta goi la con cho phen. Con cho sanh nguoi ta goi la con cho de. Vay con cho do, nguoi ta goi la con cho gi?", "con cho do"});
    questions.push_back({"Ba do ba chet bar bay len troi. Hoi ba ay chet nam bao nhieu tuoi va tai sao ba ay chet?", "73 va bo da"});
    questions.push_back({"Co 1 dan chim dau tren canh, nguoi tho san ban cai ramwf. Hoi chet may con?", "15 con"});
    questions.push_back({"Tren nhaaps duoi giat la dang lam gi?", "cau ca"});
    questions.push_back({"Quan rong nhat la quan gi?", "quan dao"});
    questions.push_back({"Cang choi cang ra nuoc?", "choi co"});
    questions.push_back({"Lich nao dai nhat?", "Lich su"});
	questions.push_back({"Ben trai duong co mot can nha blue, ben phai duong co mot can nha red. Vay nha White(Trang) o dau?", "O My"});
	questions.push_back({"Xa nao dong nhat?", "xa hoi"});
	questions.push_back({"Lam sao cai can tu can chinh no?", "lat nguoc cai can lai"});
	questions.push_back({"Tu gi ma 100% nguoi dan Vietnam deu phat am sai?", "tu sai"});
	questions.push_back({"Cai gi khi ban mua thi den(black), do(red) khi dung no va xam(grey) xit khi vut di?", "than"});
}

//Ham batdau game
void QuizGame::startGame() {
    std::srand(std::time(0)); // Seed for random number generation (seed de tao so ngau nhien)
    int questionCount = 0;

    // Hien thi thong bao chao mung
    std::cout << "CHAO MUNG BAN DA DEN VOI GAME DO VUI" << std::endl;
        
    // Hoi nguoi choi san sang chua
    std::cout << "BAN DA SAN SANG CHUA? (y/n): ";
    char ready;
    std::cin >> ready;

    if (ready != 'y' && ready != 'Y') {
    	std::cout << "Thanks for playing!" << std::endl;
        return;
    }
	// Xoa bo dem dau vao (Clear the input buffer)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
       	//Ham hien thi diem
        displayScore();
        //Ham hoi cau hoi ngau nhien
        askRandomQuestions();

        // Cho nguoi choi tra loi
        char answerKey = waitForAnswer();

    	// Kiem tra cau tra loi va cap nhat diem
        checkAnswer(answerKey);
		// Dem cau hoi
        questionCount++;

        // Kiem tra neu nguoi choi da tra loi 5 cau hoi
    	if (questionCount % 5 == 0) {
            displayScore();  //ham hien thi diem
            announceWinner(); //ham cong bo nguoi chien thang
            resetScores(); //ham reset diem

            // Hoi nguoi choi co muon choi round nua khong
            if (!askToPlayAnotherRound()) {
                std::cout << "Thanks for playing! Game over." << std::endl;
                break;
            }
        }
    }
}

//Ham hien thi diem
void QuizGame::displayScore() const {
    system("cls");
    std::cout << "Score - Player " << player1.getKey() << ": " << player1.getScore()
              << "   Player " << player2.getKey() << ": " << player2.getScore() << std::endl;
	//player1.getKey(): lay ra khoa, ktu cua nguoi choi 1
    //player1.getScore(): lay ra diem cua nguoi choi 1
}

//Ham hoi cau hoi ngau nhien
void QuizGame::askRandomQuestions() {
    if (currentQuestionIndex < questions.size()) {
        // Tao mot chi so ngau nhien de chon cau hoi (Generate a random index to select a question)
        int randomIndex;
        do {
            randomIndex = std::rand() % questions.size();
        } while (std::find(askedQuestions.begin(), askedQuestions.end(), randomIndex) != askedQuestions.end());
			
		//them chi so ngau nhien do (ung voi cau hoi da duoc hoi o tren) vao vector cau hoi da hoi
        askedQuestions.push_back(randomIndex);

        std::cout << "Question " << currentQuestionIndex + 1 << ": " << questions[randomIndex].question << std::endl;
        currentQuestionIndex++; //chi so cau hoi hien hanh
    } else {
        // Ket thuc tro choi neu khong con cau hoi nao
        std::cout << "No more questions. Game over!" << std::endl;
        exit(0);
    }
}

//Ham cho nguoi choi tra loi
char QuizGame::waitForAnswer() const {
    char key;
    //an player1.getKey() or player2.getKey() de tra loi
    std::cout << "Press " << player1.getKey() << " or " << player2.getKey() << " to answer." << std::endl;
        
	// Cho player 1 or player 2 an mot phim
    do {
        key = _getch(); //doc phim player
    } while (key != player1.getKey() && key != player2.getKey());

    return key;
}

//Ham ktra cau tra loi
void QuizGame::checkAnswer(char answerKey) {
    std::string playerAnswer;
    std::cout << "Player " << answerKey << ", enter your answer: ";
    std::getline(std::cin, playerAnswer);

    // Chuyen cau tra loi cua nguoi choi thanh chu thuong de so sanh khong phan biet hoa thuong va loai bo khoang trang
    playerAnswer.erase(std::remove_if(playerAnswer.begin(), playerAnswer.end(), ::isspace), playerAnswer.end());
    std::transform(playerAnswer.begin(), playerAnswer.end(), playerAnswer.begin(), ::tolower);

    // Lay cau tra loi dung tu danh sach cau hoi
    int currentQuestion = askedQuestions.back();
    std::string correctAnswer = questions[currentQuestion].answer;

    // Chuyen cau tra loi dung thanh chu thuong de so sanh khong phan biet hoa thuong va loai bo khoang trang
    correctAnswer.erase(std::remove_if(correctAnswer.begin(), correctAnswer.end(), ::isspace), correctAnswer.end());
    std::transform(correctAnswer.begin(), correctAnswer.end(), correctAnswer.begin(), ::tolower);

    if (playerAnswer == correctAnswer) {
        std::cout << "Correct! Player " << answerKey << " gets a point." << std::endl;
        if (answerKey == player1.getKey()) {
            player1.increaseScore();
        } else {
            player2.increaseScore();
        }
    } else {
        std::cout << "Incorrect! No point awarded." << std::endl;
    }

    // Cho 1 khoang thoi gian truoc khi hien thi cau hoi tiep thep
    // an 1 phim bat ky de tiep tuc
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
}

//Ham cong bo nguoi chien thang
void QuizGame::announceWinner() const {
    int scorePlayer1 = player1.getScore();
    int scorePlayer2 = player2.getScore();

    if (scorePlayer1 > scorePlayer2) {
        std::cout << "Player " << player1.getKey() << " wins!" << std::endl;
    }else if (scorePlayer1 < scorePlayer2) {
        	std::cout << "Player " << player2.getKey() << " wins!" << std::endl;
    	}else {
        	std::cout << "Hoa roi!" << std::endl;
    	}

    if (!askToPlayAnotherRound()) {
        std::cout << "Thanks for playing! Game over." << std::endl;
        exit(0);
    }
}


//Ham reset diem
void QuizGame::resetScores() {
    player1 = Player('a');
    player2 = Player('b');
    currentQuestionIndex = 0; //chi so cau hoi hien tai = 0
    askedQuestions.clear(); //xoa all cau hoi trong cau hoi da hoi
}

//Ham ktra nguoi choi co muon choi round nua khong
bool QuizGame::askToPlayAnotherRound() const {
    std::cout << "Do you want to play another round? (y/n): ";
    char playAgain;
    std::cin >> playAgain;

    // Xoa bo dem dau vao de tranh van de voi getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return (playAgain == 'y' || playAgain == 'Y');
}

int main() {
    QuizGame quizGame; //tao doi tuong quizGame
    quizGame.initializeQuestions(); //Khoi tao cau hoi
    quizGame.startGame(); //Bat dau tro choi
    
    return 0;
}


