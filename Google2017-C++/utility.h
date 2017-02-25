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
			if (std::find(relatedVideos.begin(), relatedVideos.end(), vidAndReq.first) == relatedVideos.end()) {
				relatedVideos.push_back(vidAndReq.first);
			}
		}
	}

	std::vector<std::vector<int>> knapsackMatrix(relatedVideos.size() + 1, std::vector<int>(cache.capacity + 1, 0));

	//Knapsack Implementation
	for (int curr_vid = 1; curr_vid < relatedVideos.size() + 1; curr_vid++) {
		for (int curr_cap = 0; curr_cap <= cache.capacity; curr_cap++) {
			
			int curr_vid_size = videos[relatedVideos[curr_vid - 1]].size;
			
			if ( curr_vid_size <= curr_cap) {

				int curr_video_cost = computeCost(cache, endPoints, relatedVideos[curr_vid - 1]);
				int total_cost_with_video = curr_video_cost + knapsackMatrix[curr_vid - 1][curr_cap - curr_vid_size];

				if (total_cost_with_video > knapsackMatrix[curr_vid - 1][curr_cap]) {
					knapsackMatrix[curr_vid][curr_cap] = total_cost_with_video;
				}
				else {
					knapsackMatrix[curr_vid][curr_cap] = knapsackMatrix[curr_vid - 1][curr_cap];
				}
			}
			else {
				knapsackMatrix[curr_vid][curr_cap] = knapsackMatrix[curr_vid - 1][curr_cap];
			}
		}
	}
	
	//Find most efficient videos for the store inside cache
	
	std::cout << "Matrix Complete" << std::endl;
	int value = knapsackMatrix[relatedVideos.size()][capacity];
	int lastItemPos = relatedVideos.size();
	int lastCapacityPos = cache.capacity;
	
	while (lastItemPos > 0 && lastCapacityPos > 0) {
		//If last values came from up, It means this video isn't efficient for the store
		if (knapsackMatrix[lastItemPos][lastCapacityPos] == knapsackMatrix[lastItemPos - 1][lastCapacityPos]) {
			//Go check previous video
			lastItemPos = lastItemPos - 1;
			lastCapacityPos = lastCapacityPos;
		}
		//Else , It means we have to store that video inside cache
		else {
			cache.videos.push_back(lastItemPos - 1);
			lastCapacityPos = lastCapacityPos - videos[lastItemPos - 1].size;
			lastItemPos = lastItemPos - 1;
		}
	}
	
	knapsackMatrix.clear();
	relatedVideos.clear();
}







#endif UTILITY_H