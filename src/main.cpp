#include <iostream>
#include <opencv2/opencv.hpp>
#include "fpdw_detector.h"
#include "imagemanager.h"


int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " model.xml directory";
		exit(-1);
	}
	
  
    cv::Mat frame;
    fpdw::detector::FPDWDetector detector(argv[1], 30.);
    
    ImageManager img(argv[2]); 
    uint end = img.getEnd();
    
    for(uint i = 0; i < end; ++i)
    {
      std::string name = img.next(1);
      frame = cv::imread(name);
      detector.process(frame);
      const std::vector<cv::Rect>& rect = detector.getBBoxes();
      for(const auto &i : rect)
      {
	      cv::rectangle(frame, i, cv::Scalar(255, 0, 0), 2);
      }
      cv::imshow("frame", frame);
      cv::waitKey(30);
    }
    return 0;
}
