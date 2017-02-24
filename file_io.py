def read_file(filename):
    fl = open(filename, "r")
    descriptions = read_descriptions(fl)

    video_sizes = read_video_sizes(fl)

    all_endpoints = read_endpoints(fl, descriptions)

    read_requests(fl, descriptions, all_endpoints)

    fl.close()

    return descriptions, video_sizes, all_endpoints

def write_solution(all_solutions, filename):
    fl = open(filename + ".sol", "w")
    fl.write(str(len(all_solutions)) + "\n")

    for cache_id, videos in all_solutions.items():
        cache_str = str(cache_id)
        video_str = " ".join(str(e) for e in videos)
        line = cache_str + " " + video_str + "\n"
        fl.write(line)

    fl.close()


def read_descriptions(fl):
    desc_line = fl.readline()
    desc_arr = desc_line.split()

    descriptions = {}
    descriptions["nof_videos"] = int(desc_arr[0])
    descriptions["nof_endpoints"] = int(desc_arr[1])
    descriptions["nof_requests"] = int(desc_arr[2])
    descriptions["nof_caches"] = int(desc_arr[3])
    descriptions["nof_cache_size"] = int(desc_arr[4])

    return descriptions

def read_video_sizes(fl):
    vs_line = fl.readline()
    vs_arr = vs_line.split()

    video_sizes = []
    for size in vs_arr:
        video_sizes.append(int(size))

    return video_sizes

def read_endpoints(fl, descriptions):
    all_endpoints = []
    for _ in range(descriptions["nof_endpoints"]):
        endpoint_line = fl.readline()
        endpoint_arr = endpoint_line.split()

        endpoint = {}
        endpoint["cache_and_lat"] = {}
        endpoint["dc_lat"] = int(endpoint_arr[0])
        endpoint["requests"] = {}

        endpoint_caches = int(endpoint_arr[1])
        for _ in range(endpoint_caches):
            cache_line = fl.readline()
            cache_arr = cache_line.split()

            endpoint["cache_and_lat"][int(cache_arr[0])] = int(cache_arr[1])

        all_endpoints.append(endpoint)

    return all_endpoints

def read_requests(fl, descriptions, all_endpoints):
    for _ in range(descriptions["nof_requests"]):
        request_line = fl.readline()
        request_arr = request_line.split()

        video_id = int(request_arr[0])
        endpoint_id = int(request_arr[1])
        total_requests = int(request_arr[2])

        if video_id not in all_endpoints[endpoint_id]["requests"]:
            all_endpoints[endpoint_id]["requests"][video_id] = total_requests
        else:
            all_endpoints[endpoint_id]["requests"][video_id] += total_requests





