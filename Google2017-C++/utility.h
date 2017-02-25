#ifndef UTILITY_H
#define UTILITY_H

#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<ostream>
#include<string>
#include<unordered_map>
#include<vector>


int computeCost(Cache& cache , std::vector<EndPoint>& endPoints, int vidId) {

	int cost = 0;
	//Search video inside connected endPoints
	for (auto endPandLat : cache.endPointsAndLatencies) {
		
		int id = endPandLat.first;
		int lat = endPandLat.second;
		//if this endpoint makes request for this video, compute cost of video
		if (endPoints[id].videosAndRequests[vidId] != 0) {
			//Cost = (serverLat - cacheLat) * videoRequestCount
			cost += ((endPoints[id].serverLatency - lat) * endPoints[id].videosAndRequests[vidId]);
		}
	}
	return cost;
}

void KnapSack(Cache& cache, std::vector<EndPoint>& endPoints, std::vector<Video>& videos) {

	int capacity = cache.capacity;
	std::vector<int> relatedVideos;

	for (auto endPandLat : cache.endPointsAndLatencies) {
		for (auto vidAndReq : endPoints[endPandLat.first].videosAndRequests) {
			//std::cout << endPandLat.first << std::endl;
			if (std::find(relatedVideos.begin(), relatedVideos.end(), vidAndReq.first) == relatedVideos.end()) {
				relatedVideos.push_back(vidAndReq.first);
			}
		}
	}

	/*
	for (int i = 0; i < relatedVideos.size(); i++) {
		std::cout << videos[relatedVideos[i]].size << " ";
	}

	getchar();
	*/

	std::vector<std::vector<int>> knapsackMatrix(cache.capacity + 1, std::vector<int>(relatedVideos.size() + 1, 0));

	//Knapsack Implementation
	for (int curr_vid = 1; curr_vid < relatedVideos.size() + 1; curr_vid++) {
		for (int curr_cap = 0; curr_cap <= cache.capacity; curr_cap++) {
			
			int curr_vid_size = videos[relatedVideos[curr_vid - 1]].size;
			
			if ( curr_vid_size <= curr_cap) {

				int curr_video_cost = computeCost(cache, endPoints, relatedVideos[curr_vid - 1]);

				if (curr_video_cost + knapsackMatrix[curr_vid - 1][curr_cap - curr_vid_size] > knapsackMatrix[curr_vid - 1][curr_cap]) {
					knapsackMatrix[curr_vid][curr_cap] = curr_video_cost + knapsackMatrix[curr_vid - 1][curr_cap - curr_vid_size];
				}
				else {
					knapsackMatrix[curr_vid][curr_cap] = knapsackMatrix[curr_vid - 1][curr_cap];
				}
			}
			else {
				/*
				std::cout << curr_vid_size << " " << curr_cap << " " << cache.capacity << std::endl;
				std::cout << "curr vid index : " << curr_vid << std::endl;
				std::cout << "value : " << knapsackMatrix[curr_vid - 1][curr_cap] << std::endl;
				getchar();
				*/
				knapsackMatrix[curr_vid][curr_cap] = knapsackMatrix[curr_vid - 1][curr_cap];
			}
		}
	}
	
	//Find most efficient videos for the store inside cache
	
	int value = knapsackMatrix[relatedVideos.size()][capacity];
	int lastItemPos = relatedVideos.size();
	int lastCapacityPos = capacity;


	while (lastCapacityPos != 0 && lastCapacityPos != 0) {
		//If last values came from up, It means this video isn't efficient for the store
		if (knapsackMatrix[lastItemPos][lastCapacityPos] == knapsackMatrix[lastItemPos - 1][lastCapacityPos]) {
			//Go check previous video
			lastItemPos = lastItemPos - 1;
			lastCapacityPos = lastCapacityPos;
		}
		//Else , It means we have to store that video inside cache
		else {
			cache.videos.push_back(lastItemPos - 1);
			lastItemPos = lastItemPos - 1;
			lastCapacityPos = lastCapacityPos - videos[lastItemPos - 1].size;
		}
	}

	knapsackMatrix.clear();
	relatedVideos.clear();
}







#endif UTILITY_H