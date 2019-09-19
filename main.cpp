#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
    if(argc != 2 && argc != 3){
        printf("使用法: %s 元画像ファイル 貼付画像ファイル\
        \n", argv[0]);
        return -1;
    }

    Mat img = imread(argv[1]);
    Mat hsv = img.clone();
    cvtColor(hsv, hsv, CV_BGR2HSV);
    int height = img.rows, width = img.cols;
    Mat alpha(height, width, CV_8UC1, 255);
    
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            int h = hsv.at<Vec3b>(i, j)[0];
            int s = hsv.at<Vec3b>(i, j)[1];
            int v = hsv.at<Vec3b>(i, j)[2];
            if( 40 < h && h < 90 && 70 < s && 70 < v ){
                alpha.at<uchar>(i, j) = 0;
            }
        }
    }

    //アルファーチャンネル追加
    Mat bgra(height, width, CV_8UC4);
    Mat out[] = { img, alpha };
    int from_to[] = { 0,0,  1,1,  2,2,  3,3 };
    mixChannels( out, 2, &bgra, 1, from_to, 4 );

    imwrite(argv[2], bgra);

    return 0;
}