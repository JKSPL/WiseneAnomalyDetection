// stdin tool for testing obstruction predictor
#include <iostream>
#include <fstream>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::ifstream;

#include "obstructionPredictor/ad_utils.h"

int main() {
    FullAnomalyDetector fd_ad;
    time_t timestamp;
    cout << std::fixed << std::setprecision(1);

    double measurement;
    while (cin >> timestamp >> measurement) {
        auto r = fd_ad.add(timestamp, measurement);
        cout << timestamp << " " << r.is_anomaly << " " << r.predicted_measurement <<" " << measurement << "\n";
    }
    return 0;
}
