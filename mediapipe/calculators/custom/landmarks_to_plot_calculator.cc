#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/port/ret_check.h"

namespace mediapipe {

namespace {

constexpr char kLandmarksTag[] = "LANDMARKS";
// constexpr char kLetterboxPaddingTag[] = "OUTPUT_LANDMARKS";

}  // namespace

//  Plot landmark
//
// Input:
//   LANDMARKS: An std::vector<NormalizedLandmark> representing landmarks on an
//   letterboxed image.
//
//   LETTERBOX_PADDING: An std::array<float, 4> representing the letterbox
//   padding from the 4 sides ([left, top, right, bottom]) of the letterboxed
//   image, normalized to [0.f, 1.f] by the letterboxed image dimensions.
//
// Output:
//   PLOT:
//
// Usage example:
// node {
//   calculator: "LandmarkLetterboxRemovalCalculator"
//   input_stream: "LANDMARKS:landmarks"
//   input_stream: "LETTERBOX_PADDING:letterbox_padding"
//   output_stream: "LANDMARKS:adjusted_landmarks"
// }

class LandmarksToPlotCalculator : public CalculatorBase {
 public:
  static ::mediapipe::Status GetContract(CalculatorContract* cc) {
    RET_CHECK(cc->Inputs().HasTag(kLandmarksTag))
        << "Missing one or more input streams.";

    cc->Inputs().Tag(kLandmarksTag).Set<std::vector<NormalizedLandmark>>();
    // cc->Inputs().Tag(kLetterboxPaddingTag).Set<std::array<float, 4>>();

    cc->Outputs().Tag(kLandmarksTag).Set<std::vector<NormalizedLandmark>>();


    return ::mediapipe::OkStatus();
  }

  ::mediapipe::Status Open(CalculatorContext* cc) override {
    cc->SetOffset(TimestampDiff(0));

    return ::mediapipe::OkStatus();
  }

  ::mediapipe::Status Process(CalculatorContext* cc) override {
    // Only process if there's input landmarks.
    if (cc->Inputs().Tag(kLandmarksTag).IsEmpty()) {
      return ::mediapipe::OkStatus();
    }

    const auto& input_landmarks =
        cc->Inputs().Tag(kLandmarksTag).Get<std::vector<NormalizedLandmark>>();


    auto output_landmarks =
        absl::make_unique<std::vector<NormalizedLandmark>>();


    LOG(INFO) << "hello landmark";
    for (const auto& landmark : input_landmarks) {
      NormalizedLandmark new_landmark;
      const float new_x = landmark.x();
      const float new_y = landmark.y();

      output_landmarks -> emplace_back(new_landmark);

      // Trying to printout input landmarks
      std::stringstream x,y;
      x << landmark.x();
      y << landmark.y();
      LOG(INFO) << x.str()+','+y.str();

      // output_landmarks->emplace_back(input_landmarks);

    }

    // End of a frame of hand landmarks
    LOG(INFO) << "end";


    cc->Outputs()
        .Tag(kLandmarksTag)
        .Add(output_landmarks.release(), cc->InputTimestamp());
    return ::mediapipe::OkStatus();
  }
};

REGISTER_CALCULATOR(LandmarksToPlotCalculator);

}  // namespace mediapipe
