#ifndef OBSTRUCTION_PREDICTOR_HPP_
#define OBSTRUCTION_PREDICTOR_HPP_

#include <cstdint>
#include "ad_utils.h"

// wrapper for FullAnomalyDetector 
class ObstructionPredictor{
 private:
  double lastDeflection = 0;
  bool isReady = false;
  FullAnomalyDetector detector;
  AnomalyData result;
  int32_t counter = 0;
  
 public:
  static const int32_t minHistoryLength = PERSIST_LONG_WINDOW;
  
  ObstructionPredictor();
  void Insert(uint64_t timestamp, double measured_value, double base_value);
  bool IsReady() const;
  bool IsObstructed() const;
  double ObstructionValue() const;
};

#endif