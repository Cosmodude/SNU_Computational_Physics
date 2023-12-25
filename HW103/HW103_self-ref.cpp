#include <iostream>
#include <vector>
#include <string>

struct CityInfo;

struct CityInfo {
    std::string cityName;
    uint64_t count;
    int64_t celsius;
    int64_t fahrenheit;
    CityInfo* next;

    CityInfo(const std::string& name, uint64_t c, int64_t cel) :
        cityName(name), count(c), celsius(cel), fahrenheit((celsius * 9 / 5) + 32), next(nullptr) {}
};

class CityStorage {
private:
    CityInfo* cities;

public:
    CityStorage() : cities(nullptr) {}

    void addCity(const std::string& cityName, uint64_t count, int64_t celsius) {
        CityInfo* newCity = new CityInfo(cityName, count, celsius);
        newCity->next = cities;
        cities = newCity;
    }

    CityInfo findCity(const std::string& cityName) {
        for (CityInfo* city = cities; city; city = city->next) {
            if (city->cityName == cityName) {
                return *city;
            }
        }
        throw std::runtime_error("City not found");
    }
};

int main() {
    CityStorage storage;

    // Adding city information
    storage.addCity("Seoul", 24, 24);
    storage.addCity("Incheon", 24, 24);
    storage.addCity("Daejeon", 25, 25);
    storage.addCity("Kwangju", 26, 26);
    storage.addCity("Daegu", 27, 27);
    storage.addCity("Pusan", 28, 28);

    // Finding city information
    try {
        CityInfo city = storage.findCity("Seoul");
        std::cout << "City: " << city.cityName << std::endl;
        std::cout << "Count: " << city.count << std::endl;
        std::cout << "Celsius: " << city.celsius << std::endl;
        std::cout << "Fahrenheit: " << city.fahrenheit << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}