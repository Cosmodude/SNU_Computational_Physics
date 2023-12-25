#include <iostream>
#include <vector>
#include <string>

struct CityInfo {
    std::string cityName;
    uint64_t count;
    int64_t celsius;
    int64_t fahrenheit;
};

class CityStorage {
private:
    std::vector<CityInfo> cities;

public:
    void addCity(const std::string& cityName, uint64_t count, int64_t celsius) {
        int64_t fahrenheit = (celsius * 9 / 5) + 32;
        cities.push_back({cityName, count, celsius, fahrenheit});
    }

    CityInfo findCity(const std::string& cityName) {
        for (const CityInfo& city : cities) {
            if (city.cityName == cityName) {
                return city;
            }
        }
        throw std::runtime_error("City not found");
    }
};

int main() {
    CityStorage storage;

    // Adding city information
    storage.addCity("Seoul", 1, 24);
    storage.addCity("Incheon", 2, 24);
    storage.addCity("Msocow", 3, 24);
    storage.addCity("Daejeon", 4, 25);
    storage.addCity("Tokyo", 5, 26);
    storage.addCity("Singapore",6, 27);
    storage.addCity("Pusan", 7, 28);

    // Finding city information
    try {
        CityInfo city = storage.findCity("Seoul");
        std::cout << "City: " << city.cityName << std::endl;
        std::cout << "Count: " << city.count << std::endl;
        std::cout << "Celsius: " << city.celsius << std::endl;
        std::cout << "Fahrenheit: " << city.fahrenheit << std::endl;
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
    }

    return 0;
}
