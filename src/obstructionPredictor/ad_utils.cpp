// Anomaly detection utilities
//
#include <string>
#include <iostream>
#include "obstructionPredictor/ad_utils.h"

double median(vector<double> v) {
    sort(v.begin(), v.end());
    int size = v.size();
    return (v[size / 2] + v[(size - 1) / 2]) / 2;
}

optional<bool> threshold_ad(const vector<double> &measurements, double abs_low, double abs_high) {
    if (measurements.empty()) {
        return {};
    }
    double v = measurements.back();
    return v < abs_low || v > abs_high;
}

optional<bool> persist_ad(const vector<double> &measurements, int window_size, double max_diff) {
    if (static_cast<int>(measurements.size()) < 2) {
        return {};
    }
    auto window_begin_it = measurements.begin();
    if (static_cast<int>(measurements.size()) > window_size + 1) {
        window_begin_it = measurements.end() - (window_size + 1);
    }
    vector<double> window(window_begin_it, measurements.end() - 1);
    double m1 = median(window);
    double m2 = measurements.back();
    return threshold_ad({abs(m2 - m1)}, numeric_limits<double>::lowest(), max_diff);
}

AnomalyData FullAnomalyDetector::add(uint64_t timestamp, double measurement) {
    uint64_t current_sampled_window_time = timestamp - timestamp % SAMPLING_SECONDS;
    if (!last_window.empty() && sampled_window_time != current_sampled_window_time) {
        resampled_measurements.push_back(median(last_window));
        if (static_cast<int>(resampled_measurements.size()) > HISTORY_SIZE) {
            resampled_measurements.pop_front();
        }
        last_window.clear();
        sampled_window_time = current_sampled_window_time;
    }
    last_window.push_back(measurement);

    vector<double> analyzed_window(resampled_measurements.begin(), resampled_measurements.end());
    analyzed_window.push_back(last_window.back());

    auto persist_long_detection = persist_ad(analyzed_window, PERSIST_LONG_WINDOW, PERSIST_LONG_MAX_DIFF);
    auto persist_short_detection = persist_ad(analyzed_window, PERSIST_SHORT_WINDOW, PERSIST_SHORT_MAX_DIFF);

    bool is_anomaly = false;
    int idx = 0;
    vector<std::string> names = {
            "persist_long",
            "persist_short",
    };
    for (auto res : {persist_long_detection, persist_short_detection}) {
        if (res.has_value() && res.value()) {
            is_anomaly = true;
            std::cerr << "Anomaly for " << timestamp << ": " << names[idx] << "\n";
        }
        idx++;
    }

    double diff = measurement - previous_measurement;
    if (is_anomaly) {
        obstruction += diff;
    } else {
        if(measurement - obstruction < 0){
            obstruction = measurement;
        }
        if(obstruction < 0){
            obstruction = std::min(0.0, measurement);
        }
    }
    previous_measurement = measurement;
    return AnomalyData{abs(obstruction) > 2, measurement - obstruction};
}
