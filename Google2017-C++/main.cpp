#include "Agent.h"
#include "utility.h"

int main() {

	int videoCount;
	int endPointCount;
	int totalRequestCount;
	int cacheCount;
	int eachCacheSize;

	std::vector<EndPoint> endPoints;
	std::vector<Video> videos;
	std::vector<Cache> caches;

	/*
	std::vector<std::vector<int>> knapsackMatrix(100, std::vector<int>(100, 0));
	knapsackMatrix[1][19] = 1;
	knapsackMatrix[1][19] = knapsackMatrix[0][19];
	std::cout << knapsackMatrix[1][19];
	*/

	//FILE READING
	std::string line;
	std::ifstream file("me_at_the_zoo.in");
	
	if (file.is_open()) {

		//First Line : Information
		std::getline(file, line);
		
		std::istringstream splitter(line);
		
		std::string s;

		std::getline(splitter, s, ' ');
		videoCount = std::atoi(s.c_str());

		std::getline(splitter, s, ' ');
		endPointCount = std::atoi(s.c_str());
		
		std::getline(splitter, s, ' ');
		totalRequestCount = std::atoi(s.c_str());
		
		std::getline(splitter, s, ' ');
		cacheCount = std::atoi(s.c_str());

		std::getline(splitter, s, ' ');
		eachCacheSize = std::atoi(s.c_str());

		//Create empty Caches
		for (int i = 0; i < cacheCount; i++) {
			caches.push_back(Cache(i,eachCacheSize));
		}
		
		//Second Line : Videos And Sizes
		std::getline(file, line);
		std::istringstream splitter2(line);
		
		for (int i = 0; i < videoCount; i++) {
			std::getline(splitter2, s, ' ');
			videos.push_back(Video(i, std::atoi(s.c_str())));
		}
		
		//Read End Point Information
		for (int endID = 0; endID < endPointCount; endID++) {
			
			std::getline(file, line);
			std::istringstream splitter3(line);
			
			//End Point to Server Latency
			std::getline(splitter3, s, ' ');
			int serverLatency = std::atoi(s.c_str());
			
			//Connected Cache Count
			std::getline(splitter3, s, ' ');
			int cacheCount = std::atoi(s.c_str());

			//Create new End Point
			endPoints.push_back(EndPoint(endID, serverLatency, cacheCount));
			
			//Read Cache Connection Speeds
			for (int j = 0; j < endPoints.back().cacheCount; j++) {

				std::getline(file, line);
				std::istringstream splitter4(line);

				//Connected Cache Id
				std::getline(splitter4, s, ' ');
				int cacheId = std::atoi(s.c_str());

				//Latency to Cache
				std::getline(splitter4, s, ' ');
				int latToCache = std::atoi(s.c_str());

				endPoints[endID].cachesAndLatencies[cacheId] = latToCache;
				caches[cacheId].endPointsAndLatencies[endID] = latToCache;
			}

		}
		
		//Request Reading
		for (int reqID = 0; reqID < totalRequestCount; reqID++) {
			std::getline(file, line);
			std::istringstream splitter5(line);

			std::getline(splitter5, s, ' ');
			int vidID = std::atoi(s.c_str());

			std::getline(splitter5, s, ' ');
			int endID = std::atoi(s.c_str());

			std::getline(splitter5, s, ' ');
			int reqCount = std::atoi(s.c_str());

			endPoints[endID].videosAndRequests[vidID] = reqCount;
			videos[vidID].endPointsAndRequests[endID] = reqCount;
		}
		
		file.close();
	}

	std::cout << "Destroyed" << std::endl;
	/*
	for (int vid = 0; vid < videos.size(); vid++) {
		std::cout << videos[vid].size << "\t";
	}
	std::cout << std::endl;
	getchar();
	*/

	for (int cacheID = 0; cacheID < cacheCount; cacheID++) {
		KnapSack(caches[cacheID], endPoints, videos);
	}
	
	for (int i = 0; i < caches.size(); i++) {
		std::cout << "Cache_" + std::to_string(i) + " stores that videos" << std::endl;
		for (int vid = 0; vid < caches[i].videos.size(); vid++) {
			std::cout << caches[i].videos[i] << "  ";
		}
		std::cout << std::endl;
	}

	std::cout << "Completely Destroyed" << std::endl;

	getchar();
	return 0;
}