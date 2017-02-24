import file_io as io
from copy import deepcopy
import knapsack
import glob
import sys

def main():
    input_files = get_input_files()
    for filename in input_files:
        print("solving " + filename)
        solve_new_input(filename)

def solve_new_input(filename):
    print("file is reading...")
    descriptions, video_sizes, all_endpoints = io.read_file(filename)
    all_caches = get_cache_arr(descriptions, all_endpoints)
    calc_video_gain(all_caches, all_endpoints)
    print(sys.getsizeof(all_endpoints))
    print(sys.getsizeof(all_caches))
    all_solutions = {}

    print("doing knapsack...")
    for cache_id, cache in enumerate(all_caches):
        size, weight, index = prepare_knapsack(cache, video_sizes)
        capacity = descriptions["nof_cache_size"]
        solution = knapsack.knapsack(size, weight).solve(capacity)
        solution = prepare_solution(index, solution)
        all_solutions[cache_id] = solution
        print(solution)

    io.write_solution(all_solutions, filename)

def get_input_files():
    files = glob.glob("./inputs/*.in")
    return files


def get_cache_arr(descriptions, all_endpoints):
    a_cache = {'video_gain' : {}, 'lat' : {}}
    all_caches = []
    for _ in range(descriptions["nof_caches"]):
        all_caches.append(deepcopy(a_cache))

    for endpoint_id, endpoint in enumerate(all_endpoints):
        for cache_id, lat in endpoint["cache_and_lat"].items():
            all_caches[cache_id]["lat"][endpoint_id] = lat

    return all_caches

def calc_video_gain(all_caches, all_endpoint):
    for cache in all_caches:
        for endpoint_id, lat in cache["lat"].items():
            lat_diff = all_endpoint[endpoint_id]["dc_lat"] - lat

            for video_id, request in all_endpoint[endpoint_id]["requests"].items():
                if video_id not in cache["video_gain"]:
                    cache["video_gain"][video_id] = 0

                cache["video_gain"][video_id] += lat_diff * request

def prepare_knapsack(cache, video_sizes):
    sizes = []
    weights = list(cache["video_gain"].values())
    index = []

    for video_id in cache["video_gain"].keys():
        index.append(video_id)
        sizes.append(video_sizes[video_id])

    return sizes, weights, index

def prepare_solution(index, solution):
    index_of_index = solution[1]
    solution_index = []
    for i in index_of_index:
        solution_index.append(index[i])

    return solution_index

if __name__ == '__main__':
    main()
