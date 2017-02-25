#ifndef AGENT_H
#define AGENT_H

#include<vector>
#include<iostream>
#include<unordered_map>

class Video {

public:
	Video();
	Video(int _id, int _size);
	

	int id;
	int size;
	std::unordered_map<int, int> endPointsAndRequests;
};


class EndPoint {

public:

	EndPoint();	
	EndPoint(int _id, int _serverLatency, int _cacheCount);

	int id;
	int cacheCount;
	int serverLatency;

	std::unordered_map<int, int> videosAndRequests;
	std::unordered_map<int, int> cachesAndLatencies;
};

class Cache {

public:

	Cache();
	Cache(int _id, int _capacity);

	int id;
	int capacity;

	std::unordered_map<int, int> endPointsAndLatencies;
	std::vector<int> videos;
};


#endif AGENT_H