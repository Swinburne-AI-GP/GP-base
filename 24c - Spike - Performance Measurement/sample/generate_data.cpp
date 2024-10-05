#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include "includes/json.hpp"

// For convenience
using json = nlohmann::json;
using namespace std;

random_device rd;
mt19937 generator(rd());

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

// Function to generate a random string of given length
string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }
    return randomString;
}

// Function to generate a random social_post JSON object
json generateRandomsocial_post() {
    std::uniform_int_distribution<> dis(1, 200);

    json social_post;
    social_post["id"] = generateRandomString(10);
    int random_number = dis(generator);
	if (random_number < 14) {
        social_post["user"]["name"] = olympian_names[random_number - 1];
	}
	else {
        social_post["user"]["name"] = generateRandomString(10);
	}
    social_post["text"] = generateRandomString(200);
    social_post["created_at"] = "Wed Oct 10 20:19:24 +0000 2024";
    return social_post;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_social_posts>" << std::endl;
        return 1;
    }

    int numberOfsocial_posts = std::stoi(argv[1]);
    std::vector<json> social_posts;

    for (int i = 0; i < numberOfsocial_posts; ++i) {
        social_posts.push_back(generateRandomsocial_post());
    }

    json output = social_posts;
    // Check if the directory exists, and create it if it does not
    std::string directory = "./data";
    if (!filesystem::exists(directory)) {
        if (!filesystem::create_directories(directory)) {
            std::cerr << "Error creating directory: " << directory << std::endl;
            return 1;
        }
    }

    std::ofstream file(directory + "/social_posts.json");
    file << output.dump(4); // Pretty print with 4 spaces
    file.close();

    std::cout << "Generated " << numberOfsocial_posts << " social_posts and saved to social_posts.json" << std::endl;
    return 0;
}