#include "Agent.h"

Video::Video() {

}

Video::Video(int _id, int _size) {
	id = _id;
	size = _size;
}


EndPoint::EndPoint() {

}

EndPoint::EndPoint(int _id, int _serverLatency, int _cacheCount) {
	id = _id;
	serverLatency = _serverLatency;
	cacheCount = _cacheCount;
}

Cache::Cache() {

}

Cache::Cache(int _id, int _capacity) {
	id = _id;
	capacity = _capacity;
}