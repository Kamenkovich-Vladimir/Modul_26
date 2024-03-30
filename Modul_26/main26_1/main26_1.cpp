#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>

class Track
{
public:
	void setNameTrack(std::string strValue) {
		nameTrack = strValue;
	}
	void setCreationDate(std::tm tmValue) {
		creationDate = tmValue;
	}
	void setDurationRecord(int value) {
		durationRecord = value;
	}
	std::string getNameTrack() {
		return nameTrack;
	}
	std::tm* getCreationDate() {
		return &creationDate;
	}
	int getDurationRecord() {
		return durationRecord;
	}
private:
	std::string nameTrack = "Unknown";
	std::tm creationDate{};
	int durationRecord = 0;
};

class Player
{
public:
	void setPlay(bool isPlay) {
		boolPlay = isPlay;
	}
	void setPause(bool isPause) {
		boolPause = isPause;
	}

	bool getPlay() {
		return boolPlay;
	}
	bool getPause() {
		return boolPause;
	}
private:
	std::vector<Track> vecPlaylist{};
	bool boolPlay = false;
	bool boolPause = false;
};

std::vector<Track> vecTrack;	//Плейлист

void trackСreate(std::vector<Track>& vecTrack, std::string strValue, std::tm tmValue, int value) {
	//Метод используется для формирования плейлиста
	Track track;
	track.setNameTrack(strValue);
	track.setCreationDate(tmValue);
	track.setDurationRecord(value);
	vecTrack.push_back(track);
}

Track currTrack;	//Текущий трек

void player_play(Player& player) {		//Воспроизводим трек сначала или с паузы
	if (!player.getPlay() && !player.getPause()) {
		std::string strNameTrack;
		std::cout << "Specify the name of the track: ";
		std::cin >> strNameTrack;
		bool isTrack = false;
		for (int i = 0; i < vecTrack.size(); i++) {
			if (vecTrack[i].getNameTrack() == strNameTrack) {
				std::cout << "It is being played track " << vecTrack[i].getNameTrack() << ", " <<
					std::put_time(vecTrack[i].getCreationDate(), "%d.%m.%Y") <<
					", " << vecTrack[i].getDurationRecord() << "sec. \n\n";
				currTrack = vecTrack[i];	//Для возможности установки на паузу и дальнейшего воспроизведения
				player.setPlay(true);
				isTrack = true;
				break;
			}
		}
		if (!isTrack) std::cout << "The track - " << strNameTrack << " is missing!\n\n";
	}
	else if (!player.getPlay() && player.getPause()) {
		std::cout << "The track " << currTrack.getNameTrack() << ", " <<
			std::put_time(currTrack.getCreationDate(), "%d.%m.%Y") <<
			", " << currTrack.getDurationRecord() << "sec. continues to play\n\n";
		player.setPlay(true);
		player.setPause(false);
	}
}

int main()
{
	std::cout << "***************** Implementation of an audio player simulation *****************\n\n";

	std::tm tm{};
	Player player{};

	//Для упрощения создадим плейлист из трёх треков
	tm.tm_year = 124; tm.tm_mon = 2; tm.tm_mday = 20;
	trackСreate(vecTrack, "Song1", tm, 20);

	tm.tm_year = 124; tm.tm_mon = 2; tm.tm_mday = 21;
	trackСreate(vecTrack, "Song2", tm, 30);

	tm.tm_year = 124; tm.tm_mon = 2; tm.tm_mday = 23;
	trackСreate(vecTrack, "Song3", tm, 25);

	
	
	std::string command = "";
	std::cout << "The playlist contains 3 tracks: Song1, Song2, Song3.\n\n";
	while (true) {
		std::cout << "Enter the command for the player (play, pause, next, stop) or 'exit' to exit the program: ";
		std::cin >> command;

		if (command == "play") { 
			player_play(player);		
		}
		else if (command == "pause") {
			if (player.getPlay() && !player.getPause()) {
				std::cout << "On pause!\n\n";
				player.setPlay(false);
				player.setPause(true);
			}
		}
		else if (command == "next") {
			srand(time(0));
			int i = std::rand() % 3;
			//Высока вероятность воспроизвести тот же трек. Обычно в режиме shuffle это встречается, если треков мало
			//Можно обойти это проверкой, но в данном случае такой задачи нет.
			std::cout << "It is being played track " << vecTrack[i].getNameTrack() << ", " <<
				std::put_time(vecTrack[i].getCreationDate(), "%d.%m.%Y") <<
				", " << vecTrack[i].getDurationRecord() << "sec. \n\n";
			currTrack = vecTrack[i];	//Для возможности установки на паузу и дальнейшего воспроизведения
			player.setPlay(true);
			player.setPause(false);
		}
		else if (command == "stop") {
			if (player.getPlay() || player.getPause()) {
				std::cout << "The player is stopped!\n\n";
				player.setPlay(false);
				player.setPause(false);
			}
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			std::cerr << "Invalid command!\n\n";
		}
	}
}