// Anomaly detection utilities
//

#ifndef WISENE_AD_UTILS_H
#define WISENE_AD_UTILS_H

#include <optional>
#include <deque>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <cmath>
using std::numeric_limits;
using std::optional;
using std::deque;
using std::vector;
using std::abs;
using std::signbit;

struct AnomalyData {
    bool is_anomaly;
    double predicted_measurement;
};

const int SAMPLING_SECONDS = 3 * 60 * 60;

const int PERSIST_LONG_WINDOW = 20;
const double PERSIST_LONG_MAX_DIFF = 4.0;

const int PERSIST_SHORT_WINDOW = 1;
const double PERSIST_SHORT_MAX_DIFF = 4.0;
const double EPS = 1e-9;

const double AUTO_MAX_DIFF = 9.0818077799217;
const vector<double> AUTO_COEFFICIENTS = {
        0.49054706907117435,
        0.08608668328370997,
        0.06815650585517882,
        0.07829836807624971,
        -0.0027073984766913944,
        0.006124270362605197,
        0.05992480996163359,
        0.10601268598458446,
        -0.032855110549157726,
        -0.012479075823271929,
        -0.020921253719577808,
        0.041396735513775415,
        -0.03223361591869012,
        0.004657588004546787,
        0.01418610357373774,
        0.07031286874671484,
        -0.004733443192322797,
        -0.013733606166212824,
        -0.006506484561642108,
        0.023387212781956133};

struct FullAnomalyDetector {
    const int HISTORY_SIZE = 500;

    time_t sampled_window_time;
    vector<double> last_window;
    double previous_measurement = 0;
    double obstruction = 0;

    deque<double> resampled_measurements;
    // measurement to jest różnica bazy od pomiaru
    AnomalyData add(time_t timestamp, double measurement);
};

#endif //WISENE_AD_UTILS_H
