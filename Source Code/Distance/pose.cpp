/**
Copyright 2017 Rafael Muñoz Salinas. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Rafael Muñoz Salinas.
*/

#include "/usr/local/include/aruco/aruco.h"
#include <fstream>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <sstream>
#include <string>
#include <stdexcept>

#if  CV_MAJOR_VERSION >= 4
#define CV_CAP_PROP_FRAME_COUNT cv::CAP_PROP_FRAME_COUNT
#endif
using namespace std;
using namespace cv;
using namespace aruco;

MarkerDetector MDetector;
VideoCapture TheVideoCapturer;
vector<Marker> TheMarkers;
Mat TheInputImage,TheInputImageGrey, TheInputImageCopy;
CameraParameters TheCameraParameters;
string dictionaryString;
int iDetectMode=0,iMinMarkerSize=0,iCorrectionRate=0,iShowAllCandidates=0,iEnclosed=0,iThreshold,iCornerMode,iDictionaryIndex,iTrack=0;

int waitTime = 0;

cv::Mat resize(const cv::Mat& in, cv::Size s){
if(s.width==-1 || s.height==-1)return in;
cv::Mat im2;
cv::resize(in, im2, s);
return im2;
}



cv::Mat resize(const cv::Mat& in, int width)
{
    if (in.size().width <= width)
        return in;
    float yf = float(width) / float(in.size().width);
    cv::Mat im2;
    cv::resize(in, im2, cv::Size(width, static_cast<int>(in.size().height * yf)));
    return im2;
}
cv::Mat resizeImage(cv::Mat &in,float resizeFactor){
    if (fabs(1-resizeFactor)<1e-3 )return in;
    float nc=float(in.cols)*resizeFactor;
    float nr=float(in.rows)*resizeFactor;
    cv::Mat imres;
    cv::resize(in,imres,cv::Size(nc,nr));
    cout<<"Imagesize="<<imres.size()<<endl;
    return imres;
}
/************************************
 *
 *
 *
 *
 ************************************/
void setParamsFromGlobalVariables(aruco::MarkerDetector &md){


    md.setDetectionMode((DetectionMode)iDetectMode,float(iMinMarkerSize)/1000.);
    md.getParameters().setCornerRefinementMethod( (aruco::CornerRefinementMethod) iCornerMode);

    md.getParameters().detectEnclosedMarkers(iEnclosed);
    md.getParameters().ThresHold=iThreshold;
    md.getParameters().trackingMinDetections=(iTrack?3:0);
    if ( aruco::Dictionary::getTypeFromString( md.getParameters().dictionary)!=Dictionary::CUSTOM)
            md.setDictionary((aruco::Dictionary::DICT_TYPES) iDictionaryIndex,float(iCorrectionRate)/10. );  // sets the dictionary to be employed (ARUCO,APRILTAGS,ARTOOLKIT,etc)
}


/************************************
 *
 *
 *
 *
 ************************************/
cv::Size parseSize(const string &strsize  ){
    if(strsize.size()==0)return cv::Size(-1,-1);
    cv::Size s;
    string ssaux=strsize;
    for(auto &c:ssaux){
        if(c==':'){
            c=' ';
        }
    }
    stringstream sstr;sstr<<ssaux;
    if( sstr>>s.width>>s.height)
        return s;
    return cv::Size(-1,-1);

}
int main(int argc, char** argv)
{
    try
    {
	char key = 0;
        int index=0,indexSave=0,vIdx=1;
	float TheMarkerSize=0.168275, resizeFactor=1;
	float x, y, z, distance;

	TheCameraParameters.readFromXMLFile("config.yml");
        TheVideoCapturer.open(vIdx);
	iMinMarkerSize=0.0;
        waitTime = 10;

        // check video is open
        if (!TheVideoCapturer.isOpened())
            throw std::runtime_error("Could not open video");

        // read first image to get the dimensions
        TheVideoCapturer >> TheInputImage;
        if (TheCameraParameters.isValid())
            TheCameraParameters.resize(TheInputImage.size());

        dictionaryString="ALL_DICTS";
        iDictionaryIndex=(uint64_t)aruco::Dictionary::getTypeFromString(dictionaryString);
        MDetector.setDictionary(dictionaryString,float(iCorrectionRate)/10. ); 
        iThreshold=MDetector.getParameters().ThresHold;
        iCornerMode= MDetector.getParameters().cornerRefinementM;
        setParamsFromGlobalVariables(MDetector);

        do{
	    x = y = z = distance = 0;
            TheVideoCapturer.retrieve(TheInputImage);
            TheInputImage=resizeImage(TheInputImage,resizeFactor);
            TheMarkers = MDetector.detect(TheInputImage, TheCameraParameters, TheMarkerSize);

            for (unsigned int i = 0; i < TheMarkers.size(); i++){
                x = TheMarkers[0].Tvec.ptr<float>(0)[0];
	    	y = TheMarkers[0].Tvec.ptr<float>(0)[1];
	    	z = TheMarkers[0].Tvec.ptr<float>(0)[2];
	    	if(x != 0 && y != 0 && z != 0){
		    distance = sqrt(x*x + y*y + z*z);
		    cout<< "\r"<<distance<<endl;
	    	}
            }
            if ( TheVideoCapturer.grab()==false) 
		key=27;
        } while (key != 27 );
    } catch (std::exception& ex){
        cout << "Exception :" << ex.what() << endl;
    }
}
