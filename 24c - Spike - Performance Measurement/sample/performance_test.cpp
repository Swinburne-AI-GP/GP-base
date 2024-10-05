// performance_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include "includes/json.hpp"

// For convenience
using json = nlohmann::json;
using namespace std;

vector<string> olympian_names = {
	"Zeus",
	"Hera",
	"Poseidon",
	"Demeter",
	"Athena",
	"Apollo",
	"Artemis",
	"Ares",
	"Aphrodite",
	"Hephaestus",
	"Hermes",
	"Hestia",
	"Dionysus",
	"Hades"
};

// Function to read JSON from a file
json readJsonFromFile(const std::string& filename) {
	std::ifstream file(filename);
	json j;
	file >> j;
	return j;
}

// Method 1: Search using a simple loop
int searchJsonSimpleLoop(const json& jsonData) {
	int olympians_found = 0;
	for (const auto& olympian : olympian_names) {
		for (const auto& item : jsonData) {
			if (item.is_object() && item.contains("user")) {
				const auto& user = item["user"];
				if (user.is_object() && user.contains("name")) {
					const auto& name = user["name"];
					if (name.is_string() && name.get<std::string>() == olympian) {
						olympians_found++;
					}
				}
			}
		}
	}
	return olympians_found;
}

// Method 2: Inside-out simple loop
int searchJsonInsideOutSimpleLoop(const json& jsonData) {
	int olympians_found = 0;
	for (const auto& item : jsonData) {
		if (item.is_object() && item.contains("user")) {
			const auto& user = item["user"];
			if (user.is_object() && user.contains("name")) {
				const auto& name = user["name"];
				for (const auto& olympian : olympian_names) {
					if (name.is_string() && name.get<std::string>() == olympian) {
						olympians_found++;
					}
				}
			}
		}
	}
	return olympians_found;
}

// Method 3: Search using a recursive function
int searchJsonRecursive(const json& jsonData, int& olympians_found) {
	if (jsonData.is_string()) {
		auto it = std::find(olympian_names.begin(), olympian_names.end(), jsonData.get<std::string>());
		if (it != olympian_names.end()) {
			return olympians_found++;
		}
	}
	for (const auto& item : jsonData) {
		return searchJsonRecursive(item, olympians_found);
	}
}
int searchJsonRecursive(const json& jsonData) {
	int olympians_found = 0;
	return searchJsonRecursive(jsonData, olympians_found);
}

// Method 4: Search using string search
int searchString(const json& jsonData) {
	int olympians_found = 0;
	std::ifstream file("./data/social_posts.json");
	std::string line;
	while (std::getline(file, line)) {
		for (const auto& olympian : olympian_names) {
			if (line.find(olympian) != std::string::npos) {
				olympians_found++;
			}
		}
	}
	return olympians_found;
}

void measure_performance(
	//function to be tested
	string function_name,
	int (*test_function)(const json&),
	//data to pass into test function
	const json& j
) {
	auto start = chrono::high_resolution_clock::now();
	int olympians_found = test_function(j);
	cout << olympians_found << " olympians found" << endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << function_name << ": " << duration << " microseconds" << endl;
}

int main() {
	// Read JSON data from file
	json j;
	try {
		j = readJsonFromFile("./data/social_posts.json");
	}catch (const std::exception& e) {
		std::cerr << "Error reading JSON from file: " << e.what() << std::endl;
		std::cerr << "Please run generate_data first - and make sure you provide the command line parameters generate_data expects." << std::endl;
		return 1;
	}

	// Measure performance of simple loop
	measure_performance("Simple Loop", searchJsonSimpleLoop, j);
	measure_performance("Simple Loop", searchJsonSimpleLoop, j);
	measure_performance("Simple Loop", searchJsonSimpleLoop, j);
	measure_performance("Simple Loop", searchJsonSimpleLoop, j);

	// Measure performance of inside-out simple loop
	measure_performance("Inside-Out Simple Loop", searchJsonInsideOutSimpleLoop, j);
	measure_performance("Inside-Out Simple Loop", searchJsonInsideOutSimpleLoop, j);
	measure_performance("Inside-Out Simple Loop", searchJsonInsideOutSimpleLoop, j);
	measure_performance("Inside-Out Simple Loop", searchJsonInsideOutSimpleLoop, j);


	// Measure performance of string search
	measure_performance("String Search", searchString, j);
	measure_performance("String Search", searchString, j);
	measure_performance("String Search", searchString, j);
	measure_performance("String Search", searchString, j);

	// Measure performance of recursive function
	//measure_performance("Recursive Function", searchJsonRecursive, j);

	return 0;
}