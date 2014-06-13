// image completion using inpaint


#include<opencv2\opencv.hpp>
#include<iostream>

bool down = false;
bool done = false;
cv::Point* points=(cv::Point*)malloc(sizeof(cv::Point)*2000);

vector<cv::Point> vectorPoints;
int i = 0;


cv::Mat maskedImage,compImage,srcImage;
void mouseCallback(int event,int x,int y,int flags,void* images)
{
	switch(event){
	case CV_EVENT_LBUTTONDOWN :
		{
			if(!down)
			{
				cv::Mat *image = (cv::Mat*)images;
				srcImage = image[0];
				//maskedImage = cv::Mat(srcImage.rows,srcImage.cols,CV_8UC1);
				maskedImage = cv::Mat::zeros(srcImage.size(),CV_8U);
				//cv::imshow("masked Image",maskedImage);
			}
			down = true;
			
		}
		break;
	case CV_EVENT_LBUTTONUP:
		{
			if(!done){
				cv::fillConvexPoly(maskedImage,points,i,cv::Scalar(255));
				cv::inpaint(srcImage,maskedImage,compImage,1,CV_INPAINT_TELEA);

				
				cv::imshow("maskedImage",maskedImage);

				cv::imshow("completed image",compImage);
				done = true;
			}
			
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		{
			if(down && !done)
			{
				points[i++]= cv::Point(x,y);
				cout<<"its moving "<<x<<" "<<y<<" "<<i<<endl;
			}
		}
		break;


	}

}

int main()
{
	char c;
	cv::Mat inputImage,images[1];
	const char* inputWindowName = "input window";
	const char* outputWindowName = "output window";
	char* input = (char*)malloc(sizeof(char)*40);
	while(inputImage.empty())
	{
		cout<<"enter the image source path"<<endl;
		gets(input);
		inputImage = cv::imread(input);
	}
	

	images[0] = inputImage;

	cv::namedWindow(inputWindowName,CV_WINDOW_AUTOSIZE);

	cv::imshow(inputWindowName,inputImage);

	cv::setMouseCallback(inputWindowName,mouseCallback,(void*)images);
	while(1){
	c=cv::waitKey();
	if(c==27)
		return 0;
	}
	
	
	return 0;
}

