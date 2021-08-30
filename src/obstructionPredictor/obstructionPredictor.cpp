#include "obstructionPredictor/obstructionPredictor.hpp"

bool ObstructionPredictor::IsReady() const {
  return isReady;
}

ObstructionPredictor::ObstructionPredictor() { }

bool ObstructionPredictor::IsObstructed() const {
  return result.is_anomaly;
}

double ObstructionPredictor::ObstructionValue() const {
  return lastDeflection-result.predicted_measurement;
}

void ObstructionPredictor::Insert(uint64_t timestamp, double measured_value, double base_value){
  if(counter < minHistoryLength - 1){
    counter++;
  } else {
    isReady = true;
  }
  
  lastDeflection = base_value - measured_value;
  result = detector.add(timestamp, lastDeflection);
}
